int init(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	inicializando=1;
	GtkWidget *imagem_inicializacao;

	query = malloc(MAX_QUERY_LEN);

	sprintf(query,"select * from tecn_pers_elem");

	if(!(res = consultar(query))){
		person_tecn_prim = 1;
		popup(NULL,"Falha ao receber dados técnicos personalizados");
		return 1;
	}

	if(!(row = mysql_fetch_row(res))){
		person_tecn_prim = 1;
		strcpy(cad_emp_strc.init_image_path,"");
	}
	else{
		person_tecn_prim = 0;
		strcpy(cad_emp_strc.init_image_path,row[1]);
	}

	imagem_inicializacao = gtk_image_new_from_file(cad_emp_strc.init_image_path);
	gtk_widget_set_size_request(GTK_WIDGET(imagem_inicializacao),1366,768);

	janela_inicializacao = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_add(GTK_CONTAINER(janela_inicializacao),imagem_inicializacao);
	gtk_window_set_icon_name(GTK_WINDOW(janela_inicializacao),"preferences-desktop-screensaver");
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_resizable(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_deletable(GTK_WINDOW(janela_inicializacao),FALSE);
	//gtk_window_set_keep_above(GTK_WINDOW(janela_inicializacao),TRUE);

	janelas_gerenciadas.fundo_inicializacao.janela_pointer = janela_inicializacao;
	gtk_widget_show_all(janela_inicializacao);

	sprintf(query,"select janela_init,tema from perfil_desktop");
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"Sem dados para personalizar o sistema");
		return 1;
	}

	GtkSettings *settings = gtk_settings_get_default();
	gchar **path;
	int n_elements;

	icone = gtk_icon_theme_get_default();
	g_object_set(settings, "gtk-theme-name","Adwaita",NULL);

	gtk_icon_theme_get_search_path(icone,&path,&n_elements);

	if(path && n_elements){
		path[n_elements-1] = malloc(strlen(ICON_PATH));
		strcpy((char*)path[n_elements-1],ICON_PATH);
		gtk_icon_theme_set_search_path(icone, (const gchar**)path, n_elements);
	}

	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

	personalizacao.tema = atoi(row[1]);
	ler_theme_dir();

	if( !atoi(row[0]) ){
		criar_sessao_default();
		gtk_widget_destroy(janela_inicializacao);
		if(desktop()){
			popup(NULL,"Erro de inicializacao");
			inicializando=0;
			return 1;
		}
	}
	else{
		login();
		gtk_widget_show_all(janela_login);
	}
	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

	janelas_gerenciadas.fundo_inicializacao.reg_id = REG_INIT_FUN_WIN;
	if(ger_janela_aberta(janela_inicializacao, &janelas_gerenciadas.fundo_inicializacao))
		return 1;

	inicializando=0;

	return 0;
}
