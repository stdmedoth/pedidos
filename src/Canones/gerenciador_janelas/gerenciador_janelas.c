int wnd_logger(janelas_info *struct_wnd)
{

  char query[MAX_QUERY_LEN];
  char janela_nome[200];
	int err=1;
	if(primeira_conexao==0){
		if(!mysql_init(&conectar)){
			popup(NULL,"Não foi possivel conectar ao servidor");
			autologger("Não foi possivel conectar ao servidor");
			autologger((char*)mysql_error(&conectar));
			primeira_conexao=0;
			return 1;
		}
		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0)){
			popup(NULL,"Não foi possivel conectar ao servidor");
			file_logger("Não foi possivel conectar ao servidor");
			file_logger((char*)mysql_error(&conectar));
			primeira_conexao=0;
			return 1;
		}
		if (mysql_set_character_set(&conectar, "utf8")){
			file_logger("Não foi possivel setar novo caracter");
		}
    primeira_conexao=1;
	}
  strcpy(janela_nome,"");

  if(struct_wnd->reg_id <= REG_WIN_QNT){
    strcpy(janela_nome,janelas_nomes[struct_wnd->reg_id]);
  }
  else{
    switch (struct_wnd->reg_id) {
      case REG_PRINC_WIN:
        strcpy(janela_nome,"Janela Principal");
        break;

      case REG_INIT_FUN_WIN:
        strcpy(janela_nome,"Janela de Inicialização");
        break;

      case REG_WIN_ENCERRA:
        strcpy(janela_nome,"Janela de encerramento");
        break;
    }
  }

  if(sessao_oper && sessao_oper->operador){
    sprintf(query,"insert into wnd_logger(id_janela,nome_janela,estado,qnt_aberta,operador,tempo) values(%i,'%s',%i,%i,%i,NOW())",

    struct_wnd->reg_id,
    janela_nome,
    struct_wnd->aberta,
    struct_wnd->qnt_aberta,
    sessao_oper->operador->code);

    if(mysql_query(&conectar,query)){
  		popup(NULL,"Erro de formato\n");
			file_logger(query);
			file_logger((char*)mysql_error(&conectar));
  		return 1;
  	}
  }else{
    file_logger("----------------------");
    file_logger("Janela aberta");
    file_logger(janela_nome);
    file_logger("----------------------");
  }

	return 0;
}

int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd){
  char msg[200];


  if(janela){
    tracelog_ultima_janela = janela;
  //  gtk_widget_add_events(janela, GDK_KEY_PRESS_MASK);
  //  gtk_widget_add_events(janela, GDK_FOCUS_CHANGE_MASK);
  //  g_signal_connect(janela, "focus-in-event", G_CALLBACK(atualizar_inatividade), NULL);
  //  g_signal_connect(janela, "key-press-event", G_CALLBACK(atualizar_inatividade), NULL);
  }

  if(validar_sessao_criada())
    return 1;

  struct_wnd->aberta = 1;
  struct_wnd->qnt_aberta++;

  if(struct_wnd->reg_id == REG_PRINC_WIN){
    file_logger("Janela principal aberta\nResetando gerenciador de janelas\n");
    iniciar_gerenciador_janela();
  }

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id < REG_WIN_QNT){
    sprintf(msg,"Id Janela aberta: %i",struct_wnd->reg_id);
    autologger(msg);

    sprintf(msg,"Nome Janela aberta: %s",janelas_nomes[struct_wnd->reg_id]);
    autologger(msg);

  }

  wnd_logger(struct_wnd);

  return 0;
}

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd){
  char msg[200];

  if(validar_sessao_criada())
    return 1;

  if(sessao_oper){
    sessao_oper->ult_ativ = g_date_time_new_now_local();
  }
  struct_wnd->aberta = 0;
  struct_wnd->qnt_aberta--;

  if(struct_wnd->reg_id == REG_PRINC_WIN){
    file_logger("Janela principal fechada\nResetando gerenciador de janelas\n");
    iniciar_gerenciador_janela();
  }

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id < REG_WIN_QNT){
    sprintf(msg,"Id Janela aberta: %i",struct_wnd->reg_id);
    autologger(msg);
    sprintf(msg,"Nome Janela aberta: %s",janelas_nomes[struct_wnd->reg_id]);
    autologger(msg);
  }

  wnd_logger(struct_wnd);
  return 0;
}

int iniciar_gerenciador_janela(){

  inativar_debug_fun();

  if(validar_sessao_criada())
    return 1;

  for(int cont=0;cont<REG_WIN_QNT;cont++){

    if(janelas_gerenciadas.vetor_janelas[cont].aberta){
      g_print("gerenciador finalizando %s ID: %i Contador %i\n",
      janelas_nomes[janelas_gerenciadas.vetor_janelas[cont].reg_id],
      janelas_gerenciadas.vetor_janelas[cont].reg_id,
      cont);


      if(!GTK_IS_WIDGET(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)){
        g_print("Janela '%s' já estava fechada\n",
        janelas_nomes[janelas_gerenciadas.vetor_janelas[cont].reg_id]);
      }
      else{
        gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[cont].janela_pointer);
      }

    }

    janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_fechada = 0;
    janelas_gerenciadas.vetor_janelas[cont].aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].janela_pointer = NULL;

  }

  janelas_gerenciadas.principal.aberta = 1;
  janelas_gerenciadas.principal.qnt_aberta = 1;
  janelas_gerenciadas.fundo_inicializacao.aberta = 0;
  janelas_gerenciadas.fundo_inicializacao.qnt_aberta = 0;

  gerenciador_load_funcs();

  return 0;
}

int gerenciador_janela(){

  if(validar_sessao_criada())
    return 1;

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

void gerenciador_load_funcs(){

  janelas_gerenciadas.vetor_janelas[REG_MENU_WND].fun = menu_icon_views_wnd;

  //cadastros
  janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].fun = cad_prod;
  janelas_gerenciadas.vetor_janelas[REG_CAD_TER].fun = cad_terc;
  janelas_gerenciadas.vetor_janelas[REG_CAD_CEP].fun = cad_cep;
  janelas_gerenciadas.vetor_janelas[REG_CAD_OPER].fun = cad_oper;
  janelas_gerenciadas.vetor_janelas[REG_CAD_UND].fun = cad_und;
  janelas_gerenciadas.vetor_janelas[REG_CAD_GRP].fun = cad_grupo;
  janelas_gerenciadas.vetor_janelas[REG_CAD_COND].fun = cad_pag;
  janelas_gerenciadas.vetor_janelas[REG_CAD_CEP].fun = cad_cep;
  janelas_gerenciadas.vetor_janelas[REG_CAD_RELAT].fun = cad_relat;
  janelas_gerenciadas.vetor_janelas[CAD_BANCOS_WND].fun = cad_bancos_fun;

  //Compras
  janelas_gerenciadas.vetor_janelas[REG_SOLIT_WND].fun = solicitacao;
  janelas_gerenciadas.vetor_janelas[REG_COTAC_WND].fun = cotacao_fun;
  janelas_gerenciadas.vetor_janelas[REG_ORDCMP_WND].fun= ordem_cmp;
  janelas_gerenciadas.vetor_janelas[REG_ENTCMP_WND].fun = entradas_fun;

  //vendas
  janelas_gerenciadas.vetor_janelas[REG_CAD_ORC].fun = vnd_orc;
  janelas_gerenciadas.vetor_janelas[REG_CAD_PED].fun = vnd_ped;
  janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND].fun = trsp_cad_fun;
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].fun = pdv_princ_wnd;

  //financeiro
  janelas_gerenciadas.vetor_janelas[CAD_TIT_REC_WND].fun = cad_titulos_receber;
  janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND].fun = cad_titulos_pagar;
  janelas_gerenciadas.vetor_janelas[CAD_BX_REC_WND].fun = cad_baixas_receber;
  janelas_gerenciadas.vetor_janelas[CAD_BX_PAG_WND].fun = cad_baixas_pagar;
  janelas_gerenciadas.vetor_janelas[CAD_CONT_FIX_WND].fun = cad_conta_fixa;
  janelas_gerenciadas.vetor_janelas[CAD_CHEQUES_WND].fun = cheque_wnd_fun;
  janelas_gerenciadas.vetor_janelas[IMPORT_TITS_WND].fun = import_tits;

  //materiais
  janelas_gerenciadas.vetor_janelas[REG_CAD_EST].fun = cad_est;
  janelas_gerenciadas.vetor_janelas[REG_ENTS].fun = est_entradas;
  janelas_gerenciadas.vetor_janelas[REG_SAIDS].fun = est_saidas;
  janelas_gerenciadas.vetor_janelas[REG_SALD].fun = cad_est_sld;

  //marketing
  janelas_gerenciadas.vetor_janelas[REG_ANLMKT_WND].fun = mkt_analise;
  janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND].fun = mkt_email_models;
  janelas_gerenciadas.vetor_janelas[REG_MAILDSTRB_WND].fun = mkt_cad_distrib_fun;
  janelas_gerenciadas.vetor_janelas[REG_ENVMAIL_WND].fun = mkt_models_envia_emails;

  //relatórios montados
  janelas_gerenciadas.vetor_janelas[REG_PROD_RELAT].fun = relat_prod_fun;
  janelas_gerenciadas.vetor_janelas[REG_TER_RELAT].fun = relat_ter_fun;
  janelas_gerenciadas.vetor_janelas[REG_MOV_RELAT].fun = relat_mov_fun;
  janelas_gerenciadas.vetor_janelas[CAD_BX_REC_WND].fun = relat_orc_prod_fun;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].fun = relat_icon_view_wnd;
  janelas_gerenciadas.vetor_janelas[REG_ORCPROD_RELAT].fun = relat_orc_prod_fun;
  //relatorios fixos
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].fun = relat_icon_view_wnd;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].fun = relat_fix_prod;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_VND_WIN].fun = relat_fix_vnd;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].fun = relat_fix_est;
  janelas_gerenciadas.vetor_janelas[CAD_BX_REC_WND].fun = cad_baixas_receber;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].fun = rel_fix_fin_rec;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINPAG_WIN].fun = rel_fix_fin_pag;
  janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND].fun = trsp_cad_fun;

  //relatórios planilhas 
  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_ICONS_WIN].fun = planilha_icon_view_wnd;
  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_PRODS_WIN].fun = planilha_init_export; //module PLANL_MOD_PRODUTOS
  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_TER_WIN].fun = planilha_init_export; //module PLANL_MOD_TERCEIROS
  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_MOV_WIN].fun = planilha_init_export; //module PLANL_MOD_MOVIMENTOS

  //opcoes tecnicas
  janelas_gerenciadas.vetor_janelas[REG_CAD_EMPRESA].fun = cadastro_empresa;
  janelas_gerenciadas.vetor_janelas[REG_CAD_CNTRATS].fun = cad_contratos;
  janelas_gerenciadas.vetor_janelas[REG_TNCLOG_WND].fun = tecn_logger_wnd;
  janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].fun = backup_fun;
  

}
