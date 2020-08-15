int wnd_logger(janelas_info *struct_wnd)
{
  char query[MAX_QUERY_LEN];
  char janela_nome[200];
	int err=1;
	if(primeira_conexao==0)
	{
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			autologger("Não foi possivel conectar ao servidor");
			autologger((char*)mysql_error(&conectar));
			primeira_conexao=0;
			return 1;
		}
		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			file_logger("Não foi possivel conectar ao servidor");
			file_logger((char*)mysql_error(&conectar));
			primeira_conexao=0;
			return 1;
		}
		if (mysql_set_character_set(&conectar, "utf8"))
		{
			file_logger("Não foi possivel setar novo caracter");
		}
    primeira_conexao=1;
	}
  strcpy(janela_nome,"");

  if(struct_wnd->reg_id <= REG_WIN_QNT)
    strcpy(janela_nome,janelas_nomes[struct_wnd->reg_id]);

  sprintf(query,"insert into wnd_logger(id_janela,nome_janela,estado,qnt_aberta,operador,tempo) values(%i,'%s',%i,%i,%i,NOW())",
  struct_wnd->reg_id,
  janela_nome,
  struct_wnd->aberta,
  struct_wnd->qnt_aberta,
  sessao_oper.code);

  #ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif

  err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Erro de formato\n");
		if(logging == 0){
			file_logger(query);
			file_logger((char*)mysql_error(&conectar));
		}
		return err;
	}
	return 0;
}

int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd){
  char msg[200];

  struct_wnd->aberta = 1;
  struct_wnd->qnt_aberta++;

  if(struct_wnd->reg_id == REG_PRINC_WIN)
    iniciar_gerenciador_janela();

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id <= REG_WIN_QNT){
    sprintf(msg,"Janela aberta: %s\n",janelas_nomes[struct_wnd->reg_id]);
    autologger(msg);
  }
  wnd_logger(struct_wnd);

  return 0;
}

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd){
  char msg[200];

  struct_wnd->aberta = 0;
  struct_wnd->qnt_aberta--;

  if(struct_wnd->reg_id == REG_PRINC_WIN)
    iniciar_gerenciador_janela();

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id <= REG_WIN_QNT){
    sprintf(msg,"Janela fechada: %s\n",janelas_nomes[struct_wnd->reg_id]);
    autologger(msg);
  }

  wnd_logger(struct_wnd);
  return 0;
}

int iniciar_gerenciador_janela(){

  for(int cont=0;cont<=REG_WIN_QNT;cont++){
    janelas_gerenciadas.vetor_janelas[cont].reg_id  = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_fechada = 0;
    janelas_gerenciadas.vetor_janelas[cont].aberta = 0;

    if(janelas_gerenciadas.vetor_janelas[cont].aberta){
        g_print("gerenciador finalizando %s\n",janelas_nomes[janelas_gerenciadas.vetor_janelas[cont].reg_id]);
        gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[cont].janela_pointer);
      }
    janelas_gerenciadas.vetor_janelas[cont].janela_pointer = NULL;
  }
  janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].fun = cad_prod;
  janelas_gerenciadas.vetor_janelas[REG_CAD_TER].fun = cad_terc;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].fun = relat_fix_prod;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_VND_WIN].fun = relat_fix_vnd;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].fun = relat_fix_est;

  janelas_gerenciadas.principal.aberta = 1;
  janelas_gerenciadas.principal.qnt_aberta = 1;
  janelas_gerenciadas.fundo_inicializacao.aberta = 0;
  janelas_gerenciadas.fundo_inicializacao.qnt_aberta = 0;

  return 0;
}

int gerenciador_janela(){

  for(int cont=0;cont<=REG_WIN_QNT;cont++){
      if(janelas_gerenciadas.vetor_janelas[cont].qnt_aberta>MAX_WND1_ABRT){
        if(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)
          if(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)){
            janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = MAX_WND1_ABRT;
            gtk_window_present(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer));
            return 1;
          }
      }
  }

  return 0;
}
