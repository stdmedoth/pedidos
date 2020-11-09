int janela_abrir_caixa(struct _maquina *maquina, struct _caixa *caixa){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	GtkWidget *janela, *fields;
	int resultado;

	janela = gtk_dialog_new_with_buttons("Preencha os campos para abertura do caixa",NULL,4,"Abrir",GTK_RESPONSE_ACCEPT,"Cancelar",GTK_RESPONSE_CANCEL,NULL);

	gtk_window_set_title(GTK_WINDOW(janela),"Abrindo Caixa");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"user-availables");

	gtk_window_set_position(GTK_WINDOW(janela),GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);

  gtk_window_set_position(GTK_WINDOW(janela),3);

	GtkWidget *caixa_combo = gtk_combo_box_text_new();
	sprintf(query,"select * from caixas where status = %i;", CAIXA_FECHADO);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao consultar caixas");
		return 0;
	}
  int cont=0;
	while((row = mysql_fetch_row(res))){
		gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(caixa_combo),cont,row[0],row[1]);
    cont++;
	}
  gtk_combo_box_set_active(GTK_COMBO_BOX(caixa_combo),0);

	GtkWidget *caixa_frame = gtk_frame_new("Caixa");
	gtk_container_add(GTK_CONTAINER(caixa_frame), caixa_combo);

	GtkWidget *operador_combo = gtk_combo_box_text_new();
  sprintf(query,"select * from operadores;");
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar operadores");
    return 0;
  }
  cont=0;
  while((row = mysql_fetch_row(res))){
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(operador_combo),cont,row[0],row[1]);
    if(atoi(row[0]) == sessao_oper.code){
      gtk_combo_box_set_active(GTK_COMBO_BOX(operador_combo),cont);
    }
    cont++;
  }
  gtk_widget_set_sensitive (operador_combo, FALSE);

  GtkWidget *operador_frame = gtk_frame_new("Operador");
	gtk_container_add(GTK_CONTAINER(operador_frame), operador_combo);

	GtkWidget *maquina_combo = gtk_combo_box_text_new();
  sprintf(query,"select * from maquinas;");
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar máquinas");
    return 0;
  }
  cont=0;
  while((row = mysql_fetch_row(res))){
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(maquina_combo),cont,row[0],row[1]);
    if(atoi(row[0]) == maquina->id){
      gtk_combo_box_set_active(GTK_COMBO_BOX(maquina_combo),cont);
    }
    cont++;
  }
  gtk_widget_set_sensitive (maquina_combo, FALSE);

  GtkWidget *maquina_frame = gtk_frame_new("Máquina");
	gtk_container_add(GTK_CONTAINER(maquina_frame), maquina_combo);

	GtkWidget *box = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(box),caixa_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(box),operador_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(box),maquina_frame,0,0,5);

	GtkWidget *frame = gtk_frame_new("Abertura do caixa:");
	gtk_container_add(GTK_CONTAINER(frame),box);

	GtkWidget *fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(fixed),frame,5,5);

	fields = gtk_bin_get_child(GTK_BIN(janela));

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);
	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(janela);

  gchar *maquina_int, *operador_int, *caixa_int;
	resultado = gtk_dialog_run(GTK_DIALOG(janela));
	switch (resultado) {
		case GTK_RESPONSE_ACCEPT:
      caixa_int = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(caixa_combo));
      maquina_int = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(maquina_combo));
      operador_int = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(operador_combo));
			sprintf(query,"insert into eventos_caixa(caixa,operador,maquina,data,tipo) values(%s, %s, %s, now(), %i)",caixa_int,operador_int,maquina_int,CX_ABERTURA);
			gtk_widget_destroy(janela);
			if(enviar_query(query)){
        return 1;
      }
      sprintf(query,"update caixas set status = %i where code = %s",CAIXA_ABERTO,caixa_int);
      if(enviar_query(query)){
        gtk_widget_destroy(janela);
        return 1;
      }
			return 0;

	}

	return 1;
}

int janela_criar_caixa(){
	GtkWidget *janela = gtk_dialog_new_with_buttons("Preencha os campos para criação do caixa",NULL,4,"Criar",GTK_RESPONSE_ACCEPT,"Cancelar",GTK_RESPONSE_CANCEL,NULL);

	gtk_window_set_title(GTK_WINDOW(janela),"Criando Caixa");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"user-availables");

	gtk_window_set_position(GTK_WINDOW(janela),GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);

  gtk_window_set_position(GTK_WINDOW(janela),3);

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  GtkWidget *nome_frame = gtk_frame_new("Nome");
  GtkWidget *nome_entry = gtk_entry_new();
  gtk_container_add(GTK_CONTAINER(nome_frame), nome_entry);

  GtkWidget *box = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(box),nome_frame,0,0,5);

  GtkWidget *frame = gtk_frame_new("Novo caixa");
  gtk_container_add(GTK_CONTAINER(frame),box);

  GtkWidget *fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed),frame,5,5);

	GtkWidget *fields = gtk_bin_get_child(GTK_BIN(janela));

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);
	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(janela),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(janela);

  int resultado = gtk_dialog_run(GTK_DIALOG(janela));
  gchar *nome;
  int ativo=0;
	switch (resultado) {
		case GTK_RESPONSE_ACCEPT:
      nome = (gchar*)gtk_entry_get_text(GTK_ENTRY(nome_entry));
			sprintf(query,"insert into caixas(nome,status) values('%s', %i)", nome, CAIXA_FECHADO);
      if(enviar_query(query)){
        popup(NULL,"Não foi possível criar caixa");
        gtk_widget_destroy(janela);
        return 1;
      }
			gtk_widget_destroy(janela);
			return 0;
	}
	gtk_widget_destroy(janela);
  return 0;

}

int caixas_qnt(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  int caixas_qnt=0;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from caixas");
  if(!(res = consultar(query))){
    popup(NULL,"Erro buscar baixas");
    return 0;
  }
  while((row = mysql_fetch_row(res))){
    caixas_qnt++;
  }
  return caixas_qnt;
}

void signal_caixa_encerramento(GtkWidget *button, struct _caixa *caixa){

	janela_caixa_encerrar(caixa);
	return ;
}


int janela_caixa_encerrar(struct _caixa *caixa){
  if(!caixa){
    popup(NULL,"Erro ao processar caixa atual");
    return 1;
  }
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	struct _maquina *maquina = maquinas_get_atual();

	sprintf(query,"insert into eventos_caixa(caixa,operador,maquina,data,tipo) values(%i, %i, %i, now(), %i)",caixa->id, sessao_oper.code, maquina->id,CX_FECHAMENTO);
	if(enviar_query(query)){
		popup(NULL,"Não foi possível encerrar caixa");
		return 1;
	}

	sprintf(query,"update caixas set status = %i where code = %i",CAIXA_FECHADO,caixa->id);
	if(enviar_query(query)){
		popup(NULL,"Não foi possível encerrar caixa");
		return 1;
	}

	if(janelas_gerenciadas.vetor_janelas[REG_PDV_WND].janela_pointer)
		gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[REG_PDV_WND].janela_pointer);

  return 0;
}


struct _caixa *caixa_get_aberto(struct _maquina *maquina){

  if(!maquina){
    popup(NULL,"Erro ao processar máquina atual");
    return NULL;
  }

  static struct _caixa caixa;
  struct _caixa *CaixaPtr = &caixa;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select c.code, c.nome, e.operador, c.status from eventos_caixa as e inner join caixas as c where e.maquina = '%i' order by data desc limit 1",maquina->id);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao identificar caixa");
    return NULL;
  }

  if((row = mysql_fetch_row(res))){
    caixa.id = atoi(row[0]);
    strcpy(caixa.nome,row[1]);
    caixa.operador = atoi(row[2]);
    caixa.status = atoi(row[3]);
  }else{
    caixa.status = CAIXA_FECHADO;
  }

  return CaixaPtr;
}
