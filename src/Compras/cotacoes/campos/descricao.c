int cotac_descricao_fun(){

  GtkTextIter inicio, fim;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cotac_descricao_view));
  gtk_text_buffer_get_bounds(buffer, &inicio, &fim);
  cotac_descricao_gchar = gtk_text_buffer_get_text(buffer,&inicio,&fim, TRUE);
  cotacao_new->descricao = strdup("");
  if(strlen(cotac_descricao_gchar)){
    cotacao_new->descricao = strdup(cotac_descricao_gchar);
  }

  return 0;
}
