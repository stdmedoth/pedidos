int obs_prod_orc_fun(GtkWidget *widget,int  posicao)
{
	GtkTextIter inicio,fim;
	obs_prod_orc_buffer[posicao] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(obs_prod_orc_view[posicao]));
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(obs_prod_orc_buffer[posicao]),&inicio,&fim);
	obs_prod_orc_gchar[posicao] = gtk_text_buffer_get_text(obs_prod_orc_buffer[posicao],&inicio,&fim,TRUE);

	if(strlen(obs_prod_orc_gchar[posicao])<=0)
	{
			obs_prod_orc_gchar[posicao] = malloc(2);
			strcpy(obs_prod_orc_gchar[posicao],"");
	}

	return 0;
}
