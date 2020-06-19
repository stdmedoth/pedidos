#define OBS_MAX_LEN 500
int obs()
{
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	buffer = gtk_text_buffer_new(NULL);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
	if(buffer == NULL)
	{
		popup(NULL,"erro");
		vet_erro[OBS_ERR] = 1;
		return 1;
	}

	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);

	observacoes_ter = (gchar*)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&inicio,&fim,FALSE);
	if(strlen(observacoes_ter)>=OBS_MAX_LEN)
	{
			popup(NULL,"As observações podem ter até 500 caracteres");
			vet_erro[OBS_ERR] = 1;
			return 1;
	}
	vet_erro[OBS_ERR] = 0;
	gtk_widget_grab_focus(concluir_ter_buttom);
	return 0;
}
