int mkt_mail_body_fun(){

  GtkTextIter inicio, fim;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_corpo_view));
  gtk_text_buffer_get_bounds(buffer, &inicio, &fim);
  mkt_mail_body_gchar = gtk_text_buffer_get_text(buffer, &inicio, &fim, TRUE);

  return 0;
}
