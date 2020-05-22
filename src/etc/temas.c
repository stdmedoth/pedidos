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
			#ifdef WIN32
			g_object_set(settings, "gtk-theme-name","Blumix",NULL);
			#endif
			#ifdef __linux__
			g_object_set(settings, "gtk-theme-name","Adwaita",NULL);
			#endif
			break;
		case 2:
			#ifdef WIN32
			g_object_set(settings, "gtk-theme-name","Plane",NULL);
			#endif
			#ifdef __linux__
			g_object_set(settings, "gtk-theme-name","Adwaita-dark",NULL);
			#endif
			
			break;
		case 3:
			g_object_set(settings, "gtk-theme-name","Default",NULL);
			break;
	}
	g_object_get(settings, "gtk-theme-name",&nome_tema,NULL);
	
	g_print("Tema escolhido: %s\n",nome_tema);
	return 0;
}
