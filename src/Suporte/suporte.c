int suporte_princ_wnd(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *filtro_status_frame, *filtro_prioridade_frame, *envio_email_button;
  GtkWidget *box = gtk_box_new(1,0);
  GtkWidget *frame = gtk_frame_new("Posts:");
  GtkWidget *caixa_opcoes = gtk_box_new(0,0);
  MYSQL_RES *res;
  MYSQL_ROW row;
  gchar sup_prior_gchar[30];
  char query[MAX_QUERY_LEN];
  int cont=0;

  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Suporte");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"applications-development");
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  gtk_window_set_default_size(GTK_WINDOW(janela),600,500);
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));

  caixa_postlist = gtk_box_new(1,0);
  scroll_postlist = gtk_scrolled_window_new(NULL,NULL);
  suport_grid = gtk_grid_new();

  cont=0;
  sup_posts_pos=0;
  sup_posts_qnt=0;
  sup_vet_posts_qnt = malloc(MAX_POST_QNT*sizeof (int*));
  sup_vet_posts_ativos = malloc(MAX_POST_QNT*sizeof (int*));
  suporte_list = malloc(sizeof(struct _suporte_list*)*MAX_POST_QNT);

  for(int cont=0;cont<MAX_POST_QNT;cont++){
    sup_vet_posts_qnt[cont] = 0;
    sup_vet_posts_ativos[cont] = 0;
  }

  sup_adiciona_button = gtk_button_new_with_label("Adicionar");
  gtk_button_set_image(GTK_BUTTON(sup_adiciona_button),gtk_image_new_from_icon_name("tab-new",GTK_ICON_SIZE_DIALOG));

  filtro_status_frame = gtk_frame_new("Status");
  filtro_prioridade_frame = gtk_frame_new("Prioridade");
  envio_email_button = gtk_button_new_with_label("Enviar Email");

  postlist = malloc(MAX_POST_QNT*sizeof(GtkBox*));
  titulo_list = malloc(MAX_POST_QNT*sizeof(GtkEntry*));
  titulo_list_frame = malloc(MAX_POST_QNT*sizeof(GtkEntry*));
  descr_list = malloc(MAX_POST_QNT*sizeof(GtkTextView*));
  sup_atualiza_button = malloc(MAX_POST_QNT*sizeof(GtkButton*));
  sup_deleta_button = malloc(MAX_POST_QNT*sizeof(GtkButton*));
  sup_opcoes_box = malloc(MAX_POST_QNT*sizeof(GtkBox*));
  sup_status_combo = malloc(MAX_POST_QNT*sizeof(GtkComboBoxText*));
  sup_posts_frame = malloc(MAX_POST_QNT*sizeof(GtkFrame*));
  sup_status_nomes = malloc(MAX_POST_QNT*sizeof(char*)*MAX_SUP_STATUS_LEN);
  sup_tipo_nomes = malloc(MAX_POST_QNT*sizeof(char*)*MAX_SUP_TIPO_LEN);
  sup_priorit_spin = malloc(MAX_POST_QNT*sizeof(GtkSpinButton*));
  sup_tipo_combo = malloc(MAX_POST_QNT*sizeof(GtkComboBoxText*));
  sup_prioridade_frame = malloc(MAX_POST_QNT*sizeof(GtkFrame*));

  sprintf(query,"select nome from suporte_status;");
  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao receber lista de postss");
    return 1;
  }

  sup_status_nomes_qnt=0;
  while((row = mysql_fetch_row(res))!=NULL){
    sup_status_nomes[sup_status_nomes_qnt] = malloc(MAX_SUP_STATUS_LEN);
    strcpy(sup_status_nomes[sup_status_nomes_qnt],row[0]);
    sup_status_nomes_qnt++;
  }

  sprintf(query,"select nome from suporte_tipos;");
  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao receber lista de postss");
    return 1;
  }

  sup_tipo_nomes_qnt=0;
  while((row = mysql_fetch_row(res))!=NULL){
    sup_tipo_nomes[sup_tipo_nomes_qnt] = malloc(MAX_SUP_TIPO_LEN);
    strcpy(sup_tipo_nomes[sup_tipo_nomes_qnt],row[0]);
    sup_tipo_nomes_qnt++;
  }

  sup_psq_status_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(sup_psq_status_combo),0,"Todos");
  gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(sup_psq_status_combo),2);

  sup_prior_combo = gtk_combo_box_text_new();
  gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(sup_prior_combo),2);
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_prior_combo),"Todos");

  for(int cont=1;cont<sup_prior_qnt;cont++){
    sprintf(sup_prior_gchar,"Prioridade %i",cont);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_prior_combo),sup_prior_gchar);
  }

  for(int cont=0;cont<sup_status_nomes_qnt;cont++)
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_psq_status_combo),sup_status_nomes[cont]);

  gtk_widget_set_name(sup_prior_combo,"combo-box-medio");
  gtk_widget_set_name(sup_psq_status_combo,"combo-box-medio");

  gtk_combo_box_set_active(GTK_COMBO_BOX(sup_psq_status_combo),0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(sup_prior_combo),sup_prior);

  sup_status = 0;

  if(sup_status == 0)
    sprintf(status_end_query,"status > 0");
  else
    sprintf(status_end_query,"status = %i",sup_status);

  if(sup_prior == 0)
    sprintf(prioridade_end_query,"prioridade > 0");
  else
    sprintf(prioridade_end_query,"prioridade = %i",sup_prior);


  sprintf(query,"select * from suporte_posts where operador = %i and %s and %s",sessao_oper->operador->code, status_end_query, prioridade_end_query);

  g_print("%s\n",query);

  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao receber lista de postss");
    return 1;
  }
  carrega_posts(res);

  janelas_gerenciadas.vetor_janelas[REG_SUP_WIN].reg_id = REG_SUP_WIN;
  janelas_gerenciadas.vetor_janelas[REG_SUP_WIN].aberta = 1;

  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_SUP_WIN]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_SUP_WIN].janela_pointer = janela;

  gtk_box_pack_start(GTK_BOX(caixa_postlist),suport_grid,0,0,0);

  gtk_widget_set_size_request(scroll_postlist,600,500);
  gtk_widget_set_size_request(caixa_postlist,600,500);

  gtk_container_add(GTK_CONTAINER(scroll_postlist),caixa_postlist);
  gtk_box_pack_start(GTK_BOX(box),scroll_postlist,0,0,10);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),sup_adiciona_button,0,0,10);

  gtk_container_add(GTK_CONTAINER(filtro_status_frame),sup_psq_status_combo);
  gtk_container_add(GTK_CONTAINER(filtro_prioridade_frame),sup_prior_combo);

  gtk_box_pack_start(GTK_BOX(caixa_opcoes),filtro_status_frame,0,0,10);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),filtro_prioridade_frame,0,0,10);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),envio_email_button,0,0,10);

  gtk_box_pack_end(GTK_BOX(box),caixa_opcoes,0,0,10);
  gtk_container_add(GTK_CONTAINER(frame),box);

  g_signal_connect(sup_adiciona_button,"clicked",G_CALLBACK(suporte_princ_add),NULL);
  g_signal_connect(sup_prior_combo,"changed",G_CALLBACK(post_recarregar_posts),scroll_postlist);
  g_signal_connect(sup_psq_status_combo,"changed",G_CALLBACK(post_recarregar_posts),scroll_postlist);
  g_signal_connect(envio_email_button,"clicked",G_CALLBACK(suporte_envia_email),scroll_postlist);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_SUP_WIN]);

  gtk_container_add(GTK_CONTAINER(janela),frame);
  gtk_widget_show_all(janela);
  return 0;
}
