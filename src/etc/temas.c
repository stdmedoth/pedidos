int ler_theme_dir()
{
	GDir *temas_dir;
	GError *erro;
	gchar *temas_dir_char,*tema_name;
	temas_dir_char = malloc(strlen(TEMA_PATH));
	nomes_temas = malloc(MAX_TEMA_LEN*MAX_TEMA_QNT);
	tema_name = malloc(MAX_TEMA_LEN);
	strcpy(temas_dir_char,TEMA_PATH);

	temas_dir = g_dir_open(temas_dir_char,0,&erro);
	temas_qnt=0;

	while((tema_name = (gchar* ) g_dir_read_name(temas_dir))!=NULL)
	{
		if( strlen(tema_name) <= MAX_TEMA_LEN )
		{
			nomes_temas[temas_qnt] = malloc(MAX_TEMA_LEN);
			strcpy(nomes_temas[temas_qnt],tema_name);
			g_print("temas: %s\n",nomes_temas[temas_qnt]);
			temas_qnt++;
			if(temas_qnt>MAX_TEMA_QNT)
				break;
		}
	}
	if(temas_qnt==0)
	{
		nomes_temas[temas_qnt] = malloc(MAX_TEMA_LEN);
		strcpy(nomes_temas[temas_qnt],"Adwaita-dark");
	}
	return 0;
}

int temas()
{
	GtkWidget *tema_window;
	gchar *tema_atual = malloc(MAX_TEMA_LEN);
	if(inicializando==0)
	{
		ler_personalizacao();
	}
	GtkSettings *settings;
	settings = gtk_settings_get_default();

	g_object_set(settings, "gtk-theme-name",nomes_temas[personalizacao.tema],NULL);
	g_object_get(settings, "gtk-theme-name",&tema_atual,NULL);

	g_print("Tema escolhido: %s\n",tema_atual);
	return 0;
}
