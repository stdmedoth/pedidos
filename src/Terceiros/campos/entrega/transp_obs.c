int transp_obs_fun(){
  GtkTextBuffer *buffer;
  GtkTextIter inicio,fim;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(transp_obs_entry));

  gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);

  transp_obs = (gchar*)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&inicio,&fim,FALSE);
  if(strlen(transp_obs)>=OBS_MAX_LEN){
      popup(NULL,"As observações ultrapassam o limite");
      return 1;
  }
  return 0;
}
