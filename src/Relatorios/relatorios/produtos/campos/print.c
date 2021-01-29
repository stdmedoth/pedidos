void relat_prod_begin_print(GtkPrintOperation *operation, GtkPrintContext *context, gpointer nul){

  g_print("Iniciando relat_prod_begin_print()\n");
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
  gtk_print_operation_set_n_pages (operation, 1);

  return ;
}

void relat_prod_draw_page(GtkPrintOperation *operation, GtkPrintContext *context, gint page_nr, gpointer nul){

  g_print("Iniciando relat_prod_draw_page()\n");
  relat_prod_gerar_fun(context);
  return ;
}
