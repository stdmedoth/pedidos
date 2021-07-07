int init(){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	inicializando=1;
	GtkWidget *imagem_inicializacao;
	GtkWidget *layout = gtk_layout_new(NULL,NULL);

	enum{
		CODE,
		PATH_IMG_INIT,
		SCRIPT_BIN_PATH
	};

	if(!primeira_conexao){
		if( conectar_mysql() ){
			popup(NULL,"Não foi possível conectar ao servidor de banco de dados");
			return 1;
		}	
	}
	

	load_styles();
	param_dev_defs();
	get_monitor_sizes();


	if(check_directorys()){
		return 1;
	}

	if(check_compat_version()){
		char msg[300];
		sprintf(msg, "Versão do banco de dados não é compativel com a versão do App ( ver. %s )", GET_APP_VERSION());
		popup(NULL,msg);
		return 1;
	}

	if(check_tables()){
		return 1;
	}
	
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
		strcpy(cad_emp_strc.init_image_path,row[PATH_IMG_INIT]);
	}

	imagem_inicializacao = gtk_image_new_from_file(cad_emp_strc.init_image_path);
	gtk_widget_set_size_request(imagem_inicializacao, desktop_width, desktop_heigth);

	janela_inicializacao = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_layout_put(GTK_LAYOUT(layout),imagem_inicializacao,0,0);
	gtk_container_add(GTK_CONTAINER(janela_inicializacao),layout);

	gtk_window_set_icon_name(GTK_WINDOW(janela_inicializacao),"preferences-desktop-screensaver");
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_resizable(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_deletable(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_maximize(GTK_WINDOW(janela_inicializacao));

	gtk_window_set_default_size(GTK_WINDOW(janela_inicializacao), monitor_width, monitor_heigth);

	janelas_gerenciadas.fundo_inicializacao.janela_pointer = janela_inicializacao;
	gtk_widget_show_all(janelas_gerenciadas.fundo_inicializacao.janela_pointer);

	enum{
		JANELA_INIT,
		TEMA
	};

	sprintf(query,"select janela_init, tema from perfil_desktop");
	if(!(res = consultar(query))){
		file_logger("init() -> consultar() -> tabela perfil_desktop");
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		return 1;
	}
	
	if(!(row = mysql_fetch_row(res))){
		file_logger("init() -> mysql_fetch_row() -> tabela perfil_desktop");
		popup(NULL,"Sem dados para personalizar o sistema");
		return 1;
	}

	GtkSettings *settings = gtk_settings_get_default();
	icone = gtk_icon_theme_get_default();
	gtk_icon_theme_append_search_path(icone, ICON_PATH);
	g_object_set(settings, "gtk-theme-name","Adwaita",NULL);

	carregar_interface();

	personalizacao.tema = atoi(row[TEMA]);

	ler_theme_dir();

	if( !atoi(row[JANELA_INIT]) ){
		sessao_oper = criar_sessao_default();
		gtk_widget_destroy(janela_inicializacao);
		if(desktop()){
			file_logger("init() -> desktop()");
			popup(NULL,"Erro de inicializacao");
			inicializando=0;
			return 1;
		}
	}else{
		janelas_gerenciadas.fundo_inicializacao.reg_id = REG_INIT_FUN_WIN;
		if(ger_janela_aberta(janela_inicializacao, &janelas_gerenciadas.fundo_inicializacao)){
			file_logger("init() -> ger_janela_aberta() -> janela_inicializacao");
			return 1;
		}

		if(login())
			return 1;
		gtk_widget_show_all(janela_login);
	}
	carregar_interface();

	inicializando=0;
	return 0;
}
