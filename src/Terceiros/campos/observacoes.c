GtkTextBuffer *buffer;
GtkTextIter inicio,fim;
#define OBS_MAX_LEN 500
int obs(gpointer textviewer)
{
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewer));
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);
	observacoes_ter = (gchar*)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&inicio,&fim,FALSE);
	if(strlen(observacoes_ter)>=500)
	{
			popup(NULL,"As observações podem ter até 500 caracteres");
			vet_erro[OBS_ERR] = 1;
			return 1;
	}
	gtk_widget_grab_focus(concluir);
	return 0;
}
