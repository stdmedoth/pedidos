int orc_begin_print(GtkPrintOperation *operation, GtkPrintContext   *context, struct _orc *orc){

  file_logger("Iniciando impressao\n");
  if(!orc){
    file_logger("Não foi possível receber estrutura do orcamento na impressao");
    return 1;
  }

  //exportando arquivo de configuração da impressao
  if(!fopen(PRINT_SETTING_FILE, "r")){
    GError *error = NULL;
    if(!gtk_print_settings_to_file (print_settings, PRINT_SETTING_FILE, &error)){
      gchar *msg = malloc(strlen(error->message) + 40);
      sprintf(msg,"Erro em gtk_print_settings_to_file() : %s", error->message);
      file_logger(msg);
    }
  }

  gtk_print_operation_set_n_pages (operation, 1);
  g_signal_connect (operation, "draw_page", G_CALLBACK(orc_draw_page), orc);

  return 0;
}

int orc_draw_page(GtkPrintOperation *operation, GtkPrintContext *context, gint page_nr, struct _orc *orc){

  //exportando arquivo de configuração das paginas
  if(!fopen(PRINT_SETUP_FILE, "r")){
    GError *error = NULL;
    if(!gtk_page_setup_to_file (print_pagesetup, PRINT_SETUP_FILE, &error)){
      gchar *msg = malloc(strlen(error->message) + 40);
      sprintf(msg,"Erro em gtk_print_settings_to_file() : %s", error->message);
      file_logger(msg);
    }
  }

  file_logger("Iniciando desenho da impressao\n");
  if(!orc){
    file_logger("Não foi possível receber estrutura do orcamento na impressao");
    return 1;
  }
  if(gera_doc_orc(orc, context))
    return 1;
  return 0;

}


int orc_print_operation_fun(struct _orc *orc, int tipo ){

  GtkPrintOperation *operation = gtk_print_operation_new();
  GtkPrintOperationResult res;
  GError *error=NULL;

  if(!orc){
    file_logger("Não foi possível receber estrutura do orcamento na impressao");
    return 1;
  }

  //lendo arquivo de configuração da impressao
  if(!(print_settings = gtk_print_settings_new_from_file(PRINT_SETTING_FILE, &error))){
    gchar *msg = malloc(strlen(error->message) + 40);
    sprintf(msg,"Erro em gtk_print_settings_load_file() : %s", error->message);
    file_logger(msg);
    print_settings = gtk_print_settings_new();
  }

  //exportando arquivo de configuração das paginas
  error=NULL;
  if(!(print_pagesetup = gtk_page_setup_new_from_file(PRINT_SETUP_FILE, &error))){
    gchar *msg = malloc(strlen(error->message) + 40);
    sprintf(msg,"Erro em gtk_page_setup_new_from_file() : %s", error->message);
    file_logger(msg);
    print_pagesetup = gtk_page_setup_new ();
  }

  gtk_print_operation_set_print_settings (operation, print_settings);
  gtk_print_operation_set_use_full_page (operation, TRUE);

  gtk_print_operation_set_embed_page_setup (operation, TRUE);
  gtk_print_operation_set_default_page_setup (operation, print_pagesetup);

  g_signal_connect (operation, "begin_print", G_CALLBACK (orc_begin_print), orc);

  res = gtk_print_operation_run (operation, tipo, NULL, &error);
  file_logger("Iniciando operação gtk_print_operation_run()\n");
  if (res == GTK_PRINT_OPERATION_RESULT_ERROR){
     GtkWidget *error_dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error printing file:\n%s", error->message);
     g_signal_connect (error_dialog, "response", G_CALLBACK (gtk_widget_destroy), NULL);
     gtk_widget_show (error_dialog);
     g_error_free (error);
     return 1;
  }
  else if (res == GTK_PRINT_OPERATION_RESULT_APPLY){
    file_logger("Impressao feita com sucesso\n");

    if(print_settings != NULL)
      g_object_unref(print_settings);
    print_settings = g_object_ref (gtk_print_operation_get_print_settings (operation));
  }
  g_object_unref (operation);
  return 0;
}
