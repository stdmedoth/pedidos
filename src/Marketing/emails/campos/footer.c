int mkt_mail_footer_fun(){

  GtkTextIter inicio, fim;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_footer_view));
  gtk_text_buffer_get_bounds(buffer, &inicio, &fim);
  mkt_mail_footer_gchar = gtk_text_buffer_get_text(buffer, &inicio, &fim, TRUE);
  return 0;
}
