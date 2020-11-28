int carrega_posts(MYSQL_RES *res){

  MYSQL_ROW row;
  GtkTextBuffer **buffer = malloc(MAX_POST_QNT*sizeof(GtkTextBuffer*));
  GtkWidget **descr_scrolls = malloc(MAX_POST_QNT*sizeof(GtkScrolledWindow*));

  gchar title_text[MAX_SUP_TITLE_LEN];
  gchar descr_text[MAX_SUP_DESC_LEN];

  while((row = mysql_fetch_row(res))!=NULL){

      sup_posts_pos = atoi(row[0]);
      char post_name[30];
      if(sup_posts_pos<MAX_POST_QNT&&sup_posts_pos>=0){

        sup_vet_posts_ativos[sup_posts_pos] = 1;
        sup_vet_posts_qnt[sup_posts_pos] = sup_posts_pos;
        postlist[sup_posts_pos] = gtk_box_new(1,0);
        titulo_list[sup_posts_pos] = gtk_entry_new();
        titulo_list_frame[sup_posts_pos] = gtk_frame_new("Título");
        descr_list[sup_posts_pos] = gtk_text_view_new();
        sup_atualiza_button[sup_posts_pos] = gtk_button_new();
        sup_deleta_button[sup_posts_pos] = gtk_button_new();
        sup_prioridade_frame[sup_posts_pos] = gtk_frame_new("Prioridade");

        gtk_button_set_image(GTK_BUTTON(sup_atualiza_button[sup_posts_pos]),gtk_image_new_from_icon_name("view-refresh",GTK_ICON_SIZE_SMALL_TOOLBAR));
        gtk_button_set_image(GTK_BUTTON(sup_deleta_button[sup_posts_pos]),gtk_image_new_from_icon_name("user-trash",GTK_ICON_SIZE_SMALL_TOOLBAR));

        descr_scrolls[sup_posts_pos] = gtk_scrolled_window_new(NULL,NULL);
        sup_opcoes_box[sup_posts_pos] = gtk_box_new(0,0);
        sup_status_combo[sup_posts_pos] = gtk_combo_box_text_new();
        sup_priorit_spin[sup_posts_pos] = gtk_spin_button_new_with_range(1,sup_prior_qnt,1);
        sup_tipo_combo[sup_posts_pos] = gtk_combo_box_text_new();

        gtk_widget_set_name(sup_tipo_combo[sup_posts_pos],"combo-box-pequeno");
        gtk_widget_set_name(sup_status_combo[sup_posts_pos],"combo-box-pequeno");

        for(int cont=0;cont<sup_tipo_nomes_qnt;cont++)
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_tipo_combo[sup_posts_pos]),sup_tipo_nomes[cont]);

        gtk_combo_box_set_active(GTK_COMBO_BOX(sup_tipo_combo[sup_posts_pos]),atoi(row[SUP_TIP])-1);

        for(int cont=0;cont<sup_status_nomes_qnt;cont++)
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_status_combo[sup_posts_pos]),sup_status_nomes[cont]);

        gtk_combo_box_set_active(GTK_COMBO_BOX(sup_status_combo[sup_posts_pos]),atoi(row[SUP_STAT])-1);

        gtk_spin_button_set_value(GTK_SPIN_BUTTON(sup_priorit_spin[sup_posts_pos]),atoi(row[SUP_PRIOR]));

        sprintf(post_name,"Post: %i",atoi(row[SUP_CODE]));
        sup_posts_frame[sup_posts_pos] = gtk_frame_new(post_name);

        gtk_widget_set_size_request(descr_scrolls[sup_posts_pos],0,100);

        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(descr_list[sup_posts_pos]),GTK_WRAP_WORD);

        gtk_entry_set_width_chars(GTK_ENTRY(titulo_list[sup_posts_pos]),70);
        gtk_widget_set_size_request(descr_list[sup_posts_pos],0,100);

        gtk_widget_set_name(descr_list[sup_posts_pos],"textview");

        buffer[sup_posts_pos] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(descr_list[sup_posts_pos]));

        suporte_list[sup_posts_pos].id = malloc(strlen(row[SUP_CODE]));
        suporte_list[sup_posts_pos].titulo = malloc(strlen(row[SUP_TIT]));
        suporte_list[sup_posts_pos].descricao = malloc(strlen(row[SUP_DESCR]));
        suporte_list[sup_posts_pos].data = malloc(strlen(row[SUP_DATA]));
        suporte_list[sup_posts_pos].status = malloc(strlen(row[SUP_STAT]));
        suporte_list[sup_posts_pos].prioridade = malloc(strlen(row[SUP_PRIOR]));
        suporte_list[sup_posts_pos].tipo = malloc(strlen(row[SUP_TIP]));

        strcpy(suporte_list[sup_posts_pos].id,row[SUP_CODE]);
        strcpy(suporte_list[sup_posts_pos].titulo,row[SUP_TIT]);
        strcpy(suporte_list[sup_posts_pos].descricao,row[SUP_DESCR]);
        strcpy(suporte_list[sup_posts_pos].data,row[SUP_DATA]);
        strcpy(suporte_list[sup_posts_pos].status, row[SUP_STAT]);
        strcpy(suporte_list[sup_posts_pos].prioridade, row[SUP_PRIOR]);
        strcpy(suporte_list[sup_posts_pos].tipo, row[SUP_TIP]);
        suporte_list[sup_posts_pos].ativo = 1;
        strcpy(title_text,row[SUP_TIT]);
        strcpy(descr_text,row[SUP_DESCR]);

        gtk_entry_set_text(GTK_ENTRY(titulo_list[sup_posts_pos]),title_text);
        gtk_text_buffer_set_text(buffer[sup_posts_pos],descr_text,strlen(descr_text));

        gtk_container_add(GTK_CONTAINER(descr_scrolls[sup_posts_pos]),descr_list[sup_posts_pos]);

        gtk_container_add(GTK_CONTAINER(titulo_list_frame[sup_posts_pos]),titulo_list[sup_posts_pos]);
        gtk_box_pack_start(GTK_BOX(postlist[sup_posts_pos]),titulo_list_frame[sup_posts_pos],0,0,5);
        gtk_box_pack_start(GTK_BOX(postlist[sup_posts_pos]),descr_scrolls[sup_posts_pos],0,0,5);

        gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_atualiza_button[sup_posts_pos],0,0,5);
        gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_deleta_button[sup_posts_pos],0,0,5);
        gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_status_combo[sup_posts_pos],0,0,5);

        gtk_container_add(GTK_CONTAINER(sup_prioridade_frame[sup_posts_pos]),sup_priorit_spin[sup_posts_pos]);
        gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_prioridade_frame[sup_posts_pos],0,0,5);

        gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_tipo_combo[sup_posts_pos],0,0,5);

        gtk_box_pack_start(GTK_BOX(postlist[sup_posts_pos]),sup_opcoes_box[sup_posts_pos],0,0,5);

        gtk_container_add(GTK_CONTAINER(sup_posts_frame[sup_posts_pos]),postlist[sup_posts_pos]);

        gtk_grid_attach(GTK_GRID(suport_grid),sup_posts_frame[sup_posts_pos],0,sup_posts_pos,1,1);

        #pragma GCC diagnostic ignored "-Wint-conversion"
        g_signal_connect(titulo_list[sup_posts_pos],"activate",G_CALLBACK(passar_campo),descr_list[sup_posts_pos]);

        g_signal_connect(sup_atualiza_button[sup_posts_pos],"clicked",G_CALLBACK(suporte_princ_atualiza),sup_vet_posts_qnt[sup_posts_pos]);

        g_signal_connect(sup_deleta_button[sup_posts_pos],"clicked",G_CALLBACK(suporte_princ_exclui_post),sup_vet_posts_qnt[sup_posts_pos]);
        #pragma GCC diagnostic warning "-Wint-conversion"

      }else{
        popup(NULL,"Não foi possivel receber quadro");
        return 1;
      }
      sup_posts_qnt++;
  }
  gtk_widget_show_all(suport_grid);
  return 0;
}

int suporte_get_livre_pos(){
  int index=0;

  for(int cont=0; cont<MAX_POST_QNT; cont++){
    if(sup_vet_posts_ativos[cont] == 0)
      return cont;
  }
  popup(NULL, "Limite atingido");
  return MAX_POST_QNT;
}

int suporte_princ_add(){
  char post_name[30];
  GtkWidget *descr_scrolls = gtk_scrolled_window_new(NULL,NULL);;

  sup_posts_pos = suporte_get_livre_pos();

  sup_vet_posts_qnt[sup_posts_pos] = sup_posts_pos;
  sup_vet_posts_ativos[sup_posts_pos] = 1;

  postlist[sup_posts_pos] = gtk_box_new(1,0);
  titulo_list[sup_posts_pos] = gtk_entry_new();
  titulo_list_frame[sup_posts_pos] = gtk_frame_new("Título");
  descr_list[sup_posts_pos] = gtk_text_view_new();
  sup_atualiza_button[sup_posts_pos] = gtk_button_new();
  sup_deleta_button[sup_posts_pos] = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(sup_atualiza_button[sup_posts_pos]),gtk_image_new_from_icon_name("view-refresh",GTK_ICON_SIZE_SMALL_TOOLBAR));
  gtk_button_set_image(GTK_BUTTON(sup_deleta_button[sup_posts_pos]),gtk_image_new_from_icon_name("user-trash",GTK_ICON_SIZE_SMALL_TOOLBAR));
  descr_scrolls = gtk_scrolled_window_new(NULL,NULL);
  sup_opcoes_box[sup_posts_pos] = gtk_box_new(0,0);
  sup_status_combo[sup_posts_pos] = gtk_combo_box_text_new();
  sup_priorit_spin[sup_posts_pos] = gtk_spin_button_new_with_range(1,sup_prior_qnt,1);
  sup_tipo_combo[sup_posts_pos] = gtk_combo_box_text_new();
  sup_prioridade_frame[sup_posts_pos] = gtk_frame_new("Prioridade");

  for(int cont=0;cont<sup_tipo_nomes_qnt;cont++)
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_tipo_combo[sup_posts_pos]),sup_tipo_nomes[cont]);

  gtk_combo_box_set_active(GTK_COMBO_BOX(sup_tipo_combo[sup_posts_pos]),0);

  gtk_widget_set_name(sup_tipo_combo[sup_posts_pos],"combo-box-pequeno");
  gtk_widget_set_name(sup_status_combo[sup_posts_pos],"combo-box-pequeno");

  sprintf(post_name,"Post: %i",sup_posts_pos);
  sup_posts_frame[sup_posts_pos] = gtk_frame_new(post_name);

  for(int cont=0;cont<sup_status_nomes_qnt;cont++)
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sup_status_combo[sup_posts_pos]),sup_status_nomes[cont]);

  gtk_combo_box_set_active(GTK_COMBO_BOX(sup_status_combo[sup_posts_pos]),0);

  gtk_entry_set_width_chars(GTK_ENTRY(titulo_list[sup_posts_pos]),70);
  gtk_widget_set_size_request(descr_list[sup_posts_pos],0,100);
  gtk_widget_set_size_request(descr_scrolls,0,100);
  gtk_widget_set_name(descr_list[sup_posts_pos],"textview");
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(descr_list[sup_posts_pos]),GTK_WRAP_WORD);

  gtk_container_add(GTK_CONTAINER(descr_scrolls),descr_list[sup_posts_pos]);

  gtk_container_add(GTK_CONTAINER(titulo_list_frame[sup_posts_pos]),titulo_list[sup_posts_pos]);
  gtk_box_pack_start(GTK_BOX(postlist[sup_posts_pos]),titulo_list_frame[sup_posts_pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(postlist[sup_posts_pos]),descr_scrolls,0,0,5);

  gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_atualiza_button[sup_posts_pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_deleta_button[sup_posts_pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_status_combo[sup_posts_pos],0,0,5);

  gtk_container_add(GTK_CONTAINER(sup_prioridade_frame[sup_posts_pos]),sup_priorit_spin[sup_posts_pos]);
  gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_prioridade_frame[sup_posts_pos],0,0,5);

  gtk_box_pack_start(GTK_BOX(sup_opcoes_box[sup_posts_pos]),sup_tipo_combo[sup_posts_pos],0,0,5);

  gtk_box_pack_start(GTK_BOX(postlist[sup_posts_pos]),sup_opcoes_box[sup_posts_pos],0,0,5);

  gtk_container_add(GTK_CONTAINER(sup_posts_frame[sup_posts_pos]),postlist[sup_posts_pos]);

  gtk_grid_attach(GTK_GRID(suport_grid),sup_posts_frame[sup_posts_pos],0,sup_posts_pos,1,1);

  gtk_widget_grab_focus(titulo_list[sup_posts_pos]);

  #pragma GCC diagnostic ignored "-Wint-conversion"
  g_signal_connect(titulo_list[sup_posts_pos],"activate",G_CALLBACK(passar_campo),descr_list[sup_posts_pos]);

  g_signal_connect(sup_atualiza_button[sup_posts_pos],"clicked",G_CALLBACK(suporte_princ_atualiza),sup_vet_posts_qnt[sup_posts_pos]);

  g_signal_connect(sup_deleta_button[sup_posts_pos],"clicked",G_CALLBACK(suporte_princ_exclui_post),sup_vet_posts_qnt[sup_posts_pos]);
  #pragma GCC diagnostic warning "-Wint-conversion"
  sup_posts_qnt++;

  gtk_widget_show_all(suport_grid);
  return 0;
}

int post_recarregar_posts(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  for(int cont=0;cont<MAX_POST_QNT;cont++){
    if(sup_vet_posts_qnt[cont]){
      gtk_grid_remove_row(GTK_GRID(suport_grid),cont);
      free(sup_status_nomes[cont]);
    }
    sup_vet_posts_ativos[cont] = 0;
    sup_vet_posts_qnt[cont] = 0;
  }

  sup_posts_pos=0;
  sup_posts_qnt=0;

  gtk_grid_remove_column(GTK_GRID(suport_grid),0);

  postlist = malloc(MAX_POST_QNT*sizeof(GtkBox*));
  titulo_list = malloc(MAX_POST_QNT*sizeof(GtkEntry*));
  titulo_list_frame = malloc(MAX_POST_QNT*sizeof(GtkFrame*));
  descr_list = malloc(MAX_POST_QNT*sizeof(GtkTextView*));
  sup_atualiza_button = malloc(MAX_POST_QNT*sizeof(GtkButton*));
  sup_deleta_button = malloc(MAX_POST_QNT*sizeof(GtkButton*));
  sup_opcoes_box = malloc(MAX_POST_QNT*sizeof(GtkBox*));
  sup_status_combo = malloc(MAX_POST_QNT*sizeof(GtkComboBoxText*));
  sup_posts_frame = malloc(MAX_POST_QNT*sizeof(GtkFrame*));
  sup_status_nomes = malloc(MAX_POST_QNT*sizeof(char*)*MAX_SUP_STATUS_LEN);

  sup_status = gtk_combo_box_get_active(GTK_COMBO_BOX(sup_psq_status_combo));

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

  sup_prior = gtk_combo_box_get_active(GTK_COMBO_BOX(sup_prior_combo));

  if(sup_status == 0)
    sprintf(status_end_query,"status > 0");
  else
    sprintf(status_end_query,"status = %i",sup_status);

  if(sup_prior == 0)
    sprintf(prioridade_end_query,"prioridade > 0");
  else
    sprintf(prioridade_end_query,"prioridade = %i",sup_prior);

  sprintf(query,"select * from suporte_posts where operador = %i and %s and %s",sessao_oper.code,status_end_query,prioridade_end_query);

  g_print("%s\n",query);

  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao receber lista de postss");
    return 1;
  }

  carrega_posts(res);

  return 0;
}
