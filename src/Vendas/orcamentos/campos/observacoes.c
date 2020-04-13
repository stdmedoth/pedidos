int observacoes_orc_get()
{
	GtkTextIter inicio,fim;
	buffer = malloc(sizeof(GtkTextBuffer*));
	observacoes_orc_gchar = malloc(sizeof(gchar*)*MAX_OBS_LEN);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);
	observacoes_orc_gchar = gtk_text_buffer_get_text(buffer,&inicio,&fim,TRUE);
	return 0;
}
