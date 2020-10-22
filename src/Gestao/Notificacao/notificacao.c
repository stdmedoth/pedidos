int notificacoes_receber(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query,"select p.parcelas_id, p.posicao, DATE_FORMAT(p.data_vencimento,'%%d/%%m/%%Y'), t.razao, tit.status, tit.tipo_titulo  from parcelas_tab as p inner join titulos as tit inner join terceiros as t on p.parcelas_id = tit.code  and tit.cliente = t.code where p.data_vencimento >= CURDATE() and p.data_vencimento <= CURDATE()+1");
  if((res = consultar(query))){
  	if((row = mysql_fetch_row(res))!=NULL){
      notificacao_pendencias = 1;
    }else{
      notificacao_pendencias = 0;
    }
  }

  return 0;
}

int notificacoes_criar(){

  return 0;
}

void notificacoes_wnd(){
  GtkWidget *notf_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  enum{
    NOME_COL,
    DESCR_COL,
    STAT_COL
  };

  /*registrando a janela para o reg_win*/
	janelas_gerenciadas.vetor_janelas[REG_NOTIF].reg_id = REG_NOTIF;
	if(ger_janela_aberta(notf_wnd, &janelas_gerenciadas.vetor_janelas[REG_NOTIF]))
		return ;
	janelas_gerenciadas.vetor_janelas[REG_NOTIF].janela_pointer = notf_wnd;

  GtkWidget *notf_box = gtk_box_new(1,0);
  GtkWidget *notf_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *notf_tree_view = gtk_tree_view_new();
  GtkWidget *notf_frame = gtk_frame_new("Notificações");
  GtkTreeIter campos;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  GtkTreeViewColumn *coluna_nome = gtk_tree_view_column_new_with_attributes(
    "Nome",
    gtk_cell_renderer_text_new (),
    "text",
    NOME_COL,
    NULL);

  GtkTreeViewColumn *coluna_descr = gtk_tree_view_column_new_with_attributes(
    "Descrição",
  gtk_cell_renderer_text_new (),
    "text",
    DESCR_COL,
    NULL );
  GtkTreeViewColumn *coluna_status = gtk_tree_view_column_new_with_attributes(
    "Status",
  gtk_cell_renderer_text_new (),
    "text",
    STAT_COL,
    NULL );

  gtk_tree_view_append_column(GTK_TREE_VIEW(notf_tree_view), coluna_nome);
  gtk_tree_view_append_column(GTK_TREE_VIEW(notf_tree_view), coluna_descr);
  gtk_tree_view_append_column(GTK_TREE_VIEW(notf_tree_view), coluna_status);

  GtkTreeStore *modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  sprintf(query,"select p.parcelas_id, p.posicao, DATE_FORMAT(p.data_vencimento,'%%d/%%m/%%Y'), t.razao, tit.status, tit.tipo_titulo  from parcelas_tab as p inner join titulos as tit inner join terceiros as t on p.parcelas_id = tit.code  and tit.cliente = t.code where p.data_vencimento >= CURDATE() and p.data_vencimento <= CURDATE()+2");
	if((res = consultar(query))){
  	while((row = mysql_fetch_row(res))!=NULL){
      char nome[20];
      char descr[100];
      char status[30];
      char terceiro[15];

      switch (atoi(row[5])) {
        case 1:
          sprintf(nome,"Título à Receber");
          sprintf(terceiro,"Cliente");
          break;
        case 2:
          sprintf(nome,"Título à Pagar");
          sprintf(terceiro,"Fornecedor");
          break;
        default:
          sprintf(nome,"Título sem Tipo");
          break;
      }

      sprintf(descr,"Parcela %s do Título %s - %s '%s'com vencimento em %s", row[1], row[0], terceiro, row[3], row[2]);
      switch (atoi(row[4])) {
        case STAT_QUITADO:
          sprintf(status,"Título já Quitado");
          break;
        case STAT_PARC_BAIXA:
          sprintf(status,"Título parcialmente Baixado");
          break;
        case STAT_PENDENTE:
          sprintf(status,"Título pendente");
          break;
        default:
          sprintf(status,"Erro");
          break;
      }
      gtk_tree_store_append(modelo,&campos,NULL);
      g_print("Inserindo codigo: %s nome: %s\n",row[0],row[1]);
      gtk_tree_store_set(modelo,&campos,
      NOME_COL,nome,
      DESCR_COL,descr,
      STAT_COL,status
      ,-1);
  	}
  }
  gtk_tree_view_set_model(GTK_TREE_VIEW(notf_tree_view),GTK_TREE_MODEL(modelo));

  gtk_box_pack_start(GTK_BOX(notf_box),notf_tree_view,0,0,10);
  gtk_container_add(GTK_CONTAINER(notf_scroll),notf_box);
  gtk_container_add(GTK_CONTAINER(notf_frame),notf_scroll);
  gtk_container_add(GTK_CONTAINER(notf_wnd),notf_frame);

  gtk_widget_set_size_request(notf_scroll,600,300);
  gtk_widget_set_size_request(notf_box,600,300);
  gtk_widget_set_size_request(notf_wnd,600,300);

  gtk_widget_show_all(notf_wnd);

  g_signal_connect(notf_wnd,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_NOTIF]);
  return ;
}
