int req_prod_descr_fun(){

  GtkTextIter inicio, fim;
  GtkTextBuffer * buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(req_prod_descr_text));
  gtk_text_buffer_get_bounds(buffer, &inicio, &fim);
  req_prod_descr_gchar = gtk_text_buffer_get_text(buffer,&inicio,&fim, TRUE);

  return 0;
}
