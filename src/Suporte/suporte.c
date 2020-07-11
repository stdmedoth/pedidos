int suporte_princ_wnd(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  GtkWidget *box = gtk_box_new(1,0);
  GtkTextBuffer **buffer;
  GtkWidget **descr_scrolls;
  int psq_suporte_status = 1,cont=0;
  gchar title_text[MAX_SUP_TITLE_LEN];
  gchar descr_text[MAX_SUP_DESC_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Suporte");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"applications-development");
  gtk_application_add_window(aplicacao,GTK_WINDOW(janela));
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  gtk_window_set_default_size(GTK_WINDOW(janela),460,500);

  if(personalizacao.janela_keep_above==1)
    gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);

  janelas_gerenciadas.vetor_janelas[REG_SUP].reg_id = REG_SUP;
  janelas_gerenciadas.vetor_janelas[REG_SUP].aberta = 1;

  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_SUP]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_SUP].janela_pointer = janela;

  caixa_postlist = gtk_box_new(1,0);
  scroll_postlist = gtk_scrolled_window_new(NULL,NULL);
  suport_grid = gtk_grid_new();
  gtk_widget_set_size_request(scroll_postlist,450,500);

  if(psq_suporte_status == 0)
    sprintf(query,"select code, titulo, descricao, data, status from suporte_posts where operador = %i and  status > 0",sessao_oper.code);
  else
    sprintf(query,"select code, titulo, descricao, data, status from suporte_posts where operador = %i and status = %i",sessao_oper.code,psq_suporte_status);

  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao receber lista de postss");
    return 1;
  }

  cont=0;
  sup_posts_qnt=1;
  sup_vet_posts_qnt = malloc(MAX_POST_QNT*sizeof (int*));

  sup_adiciona_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(sup_adiciona_button),gtk_image_new_from_icon_name("tab-new",GTK_ICON_SIZE_DIALOG));

  postlist = malloc(MAX_POST_QNT*sizeof(GtkBox*));
  titulo_list = malloc(MAX_POST_QNT*sizeof(GtkEntry*));
  descr_list = malloc(MAX_POST_QNT*sizeof(GtkTextView*));
  buffer = malloc(MAX_POST_QNT*sizeof(GtkTextBuffer*));
  sup_deleta_button = malloc(MAX_POST_QNT*sizeof(GtkButton*));
  descr_scrolls = malloc(MAX_POST_QNT*sizeof(GtkScrolledWindow*));
  sup_vet_posts_qnt[sup_posts_qnt] = sup_posts_qnt;

  while((row = mysql_fetch_row(res))!=NULL){
      sup_posts_qnt = atoi(row[0]);
      g_print("inserindo %s\n",row[1]);
      if(sup_posts_qnt<=MAX_POST_QNT){
        sup_vet_posts_qnt[sup_posts_qnt] = sup_posts_qnt;
        postlist[sup_posts_qnt] = gtk_box_new(1,0);
        titulo_list[sup_posts_qnt] = gtk_entry_new();
        descr_list[sup_posts_qnt] = gtk_text_view_new();
        sup_deleta_button[sup_posts_qnt] = gtk_button_new();
        gtk_button_set_image(GTK_BUTTON(sup_deleta_button[sup_posts_qnt]),gtk_image_new_from_icon_name("user-trash",GTK_ICON_SIZE_SMALL_TOOLBAR));
        descr_scrolls[sup_posts_qnt] = gtk_scrolled_window_new(NULL,NULL);
        gtk_widget_set_size_request(descr_scrolls[sup_posts_qnt],400,100);

        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(descr_list[sup_posts_qnt]),GTK_WRAP_WORD);

        gtk_entry_set_width_chars(GTK_ENTRY(titulo_list[sup_posts_qnt]),35);
        //gtk_widget_set_size_request(descr_list[sup_posts_qnt],400,80);

        gtk_widget_set_name(descr_list[sup_posts_qnt],"textview");

        buffer[sup_posts_qnt] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(descr_list[sup_posts_qnt]));

        strcpy(title_text,row[1]);
        strcpy(descr_text,row[2]);

        gtk_entry_set_text(GTK_ENTRY(titulo_list[sup_posts_qnt]),title_text);
        gtk_text_buffer_set_text(buffer[sup_posts_qnt],descr_text,strlen(descr_text));

        gtk_container_add(GTK_CONTAINER(descr_scrolls[sup_posts_qnt]),descr_list[sup_posts_qnt]);

        gtk_box_pack_start(GTK_BOX(postlist[sup_posts_qnt]),titulo_list[sup_posts_qnt],0,0,5);
        gtk_box_pack_start(GTK_BOX(postlist[sup_posts_qnt]),descr_scrolls[sup_posts_qnt],0,0,5);
        gtk_box_pack_start(GTK_BOX(postlist[sup_posts_qnt]),sup_deleta_button[sup_posts_qnt],0,0,5);

        gtk_grid_attach(GTK_GRID(suport_grid),postlist[sup_posts_qnt],0,sup_posts_qnt,1,1);

        #pragma GCC diagnostic ignored "-Wint-conversion"
        g_signal_connect(titulo_list[sup_posts_qnt],"activate",G_CALLBACK(suporte_princ_atualiza_title),sup_vet_posts_qnt[sup_posts_qnt]);
        g_signal_connect(titulo_list[sup_posts_qnt],"focus-out-event",G_CALLBACK(suporte_princ_atualiza_title),sup_vet_posts_qnt[sup_posts_qnt]);
        
        g_signal_connect(descr_list[sup_posts_qnt],"focus-out-event",G_CALLBACK(suporte_princ_atualiza_descr),sup_vet_posts_qnt[sup_posts_qnt]);
        g_signal_connect(sup_deleta_button[sup_posts_qnt],"clicked",G_CALLBACK(suporte_princ_exclui_post),sup_vet_posts_qnt[sup_posts_qnt]);
        #pragma GCC diagnostic warning "-Wint-conversion"

        sup_vet_posts_qnt[sup_posts_qnt] = sup_posts_qnt;
        sup_posts_qnt++;
      }

  }

  gtk_box_pack_start(GTK_BOX(caixa_postlist),suport_grid,0,0,10);
  gtk_widget_set_size_request(scroll_postlist,460,500);
  gtk_container_add(GTK_CONTAINER(scroll_postlist),caixa_postlist);
  gtk_box_pack_start(GTK_BOX(box),scroll_postlist,0,0,10);
  gtk_box_pack_end(GTK_BOX(box),sup_adiciona_button,0,0,10);

  g_signal_connect(sup_adiciona_button,"clicked",G_CALLBACK(suporte_princ_add),NULL);
	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_SUP]);

  gtk_container_add(GTK_CONTAINER(janela),box);
  gtk_widget_show_all(janela);
  return 0;
}
