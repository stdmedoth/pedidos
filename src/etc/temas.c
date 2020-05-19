int temas()
{
	GtkWidget *tema_window;
	if(inicializando==0)
	{
		ler_personalizacao();
	}
	GtkSettings *settings;
	gchar *nome_tema;
	settings = gtk_settings_get_default();
	switch(personalizacao.tema)
	{
		case 1:
			g_object_set(settings, "gtk-theme-name","Adwaita-dark",NULL);
			break;
		case 2:
			g_object_set(settings, "gtk-theme-name","Xfce",NULL);
			break;
		case 3:
			g_object_set(settings, "gtk-theme-name","Arc",NULL);
			break;
	}
	g_object_get(settings, "gtk-theme-name",&nome_tema,NULL);
	
	g_print("Tema escolhido: %s\n",nome_tema);
	return 0;
}
