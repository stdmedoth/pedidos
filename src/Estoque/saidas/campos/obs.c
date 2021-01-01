int est_said_obs_fun(){
  GtkTextIter inicio,fim;
	GtkTextBuffer *buffer;
	est_said_obs_gchar = malloc(sizeof(gchar*)*MAX_OBS_LEN);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(est_said_obs_view));
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);

	est_said_obs_gchar = gtk_text_buffer_get_text(buffer,&inicio,&fim,TRUE);

	return 0;
}
