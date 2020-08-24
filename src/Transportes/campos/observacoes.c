int trsp_cad_obs_fun(){
  GtkTextBuffer *buffer;
  GtkTextIter inicio,fim;

  buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(trsp_cad_obs_entry));
  gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);

  trsp_cad_obs_gchar = gtk_text_buffer_get_text(buffer,&inicio,&fim,TRUE);

  gtk_widget_grab_focus(trsp_cad_nument_entry);
  return 0;
}
