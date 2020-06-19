#define OBS_MAX_LEN 500
int obs_prod()
{
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	buffer = gtk_text_buffer_new(NULL);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
	if(buffer == NULL)
	{
		popup(NULL,"Erro em Observações");
		return 1;
	}

	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&inicio,&fim);
	observacoes_prod = (gchar*)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&inicio,&fim,FALSE);

	if(strlen(observacoes_prod)>=OBS_MAX_LEN)
	{
			popup(NULL,"As observações podem ter até 500 caracteres");
			return 1;
	}
	gtk_widget_grab_focus(prod_concluir_button);
	return 0;
}
