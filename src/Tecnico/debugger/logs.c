int tecn_logger_remove_fun(){

  GFile *file = g_file_new_for_path(LOGGER);
  if(!g_file_delete(file, NULL, NULL)){
    autologger("Não foi possível deletar arquivo logger");
    return 1;
  }
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tecn_logger_textview));
  gtk_text_buffer_set_text(buffer, "", strlen(""));

  return 0;
}

int tecn_logger_wnd(){
  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"logger");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Logger");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  janelas_gerenciadas.vetor_janelas[REG_TNCLOG_WND].reg_id = REG_TNCLOG_WND;
  janelas_gerenciadas.vetor_janelas[REG_TNCLOG_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_TNCLOG_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_TNCLOG_WND].janela_pointer = janela;

  tecn_logger_remove_button = gtk_button_new_with_label("Deletar");
  tecn_logger_textview = gtk_text_view_new();
  GtkWidget *tecn_logger_scroll = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *tecn_logger_box = gtk_box_new(1,0);
  GtkWidget *tecn_logger_headerbox = gtk_box_new(0,0);
  GtkWidget *tecn_logger_bodybox = gtk_box_new(0,0);

  gtk_container_add(GTK_CONTAINER(tecn_logger_scroll), tecn_logger_textview);

  gtk_box_pack_start(GTK_BOX(tecn_logger_headerbox), tecn_logger_remove_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(tecn_logger_bodybox), tecn_logger_scroll,0,0,5);

  gtk_box_pack_start(GTK_BOX(tecn_logger_box), tecn_logger_headerbox,0,0,5);
  gtk_box_pack_start(GTK_BOX(tecn_logger_box), tecn_logger_bodybox,0,0,5);

  gtk_container_add(GTK_CONTAINER(janela), tecn_logger_box);

  gtk_widget_set_size_request(tecn_logger_scroll, 1000, 600);
  gtk_widget_set_size_request(tecn_logger_textview, 1000, 600);

	//gtk_widget_set_size_request(janela,);
  FILE *arquivo = fopen(LOGGER, "r");
  if(!arquivo){
    popup(NULL,"Não foi possível abrir arquivo logs");
    return 1;
  }

  gchar *logger_content = malloc(sizeof(char) * 1024 * 1024 * 4);
  fread(logger_content, 1024*1024*4, 1, arquivo);
  gchar *logger_valid_content = g_utf8_make_valid (logger_content, strlen(logger_content) );

  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tecn_logger_textview));
  gtk_text_buffer_set_text(buffer, logger_valid_content, strlen(logger_valid_content));

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_TNCLOG_WND]);
  g_signal_connect(tecn_logger_remove_button,"clicked",G_CALLBACK(tecn_logger_remove_fun),NULL);

  gtk_widget_show_all(janela);
  return 0;
}
