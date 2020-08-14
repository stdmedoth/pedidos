static GtkWidget  *fixed_razao, *fixed_endereco, *fixed_cnpj;
static GtkWidget  *razao,*endereco,*cnpj, *caixa_infos;
static GtkWidget *janela_inicializacao;

static void criar_janela_princ(){

	janela_principal = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(janela_principal),"Petitto");
	//if(personalizacao.janela_keep_above==1)
	//gtk_window_set_keep_above(GTK_WINDOW(janela_principal), TRUE);
	gtk_window_set_icon_name(GTK_WINDOW(janela_principal),"accessories-dictionary");
	gtk_container_set_border_width(GTK_CONTAINER(janela_principal),0);
	gtk_window_set_resizable(GTK_WINDOW(janela_principal),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela_principal),0);
	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(tecla_menu),NULL);
	gtk_window_set_default_size(GTK_WINDOW(janela_principal),1366,768);
	gtk_window_maximize(GTK_WINDOW(janela_principal));

	janelas_gerenciadas.principal.reg_id = REG_PRINC_WIN;
	if(ger_janela_aberta(janela_principal, &janelas_gerenciadas.principal))
		return ;
	janelas_gerenciadas.principal.aberta = 1;

	janelas_gerenciadas.principal.janela_pointer = janela_principal;

	return ;
}


int desktop()
{
	int err=0;
	GtkWidget  *juncao;
	GtkWidget  *layout;
	GtkWidget *fixed_menu;
	GtkWidget *param_button;
	GtkWidget *sair_button;
	GtkWidget *logoff_button;
	GtkWidget *suport_button;

	GtkWidget *hostname_fixed, *hostname_label;
	GtkWidget *nome_usuario_label,*nome_usuario_fixed;
	GtkWidget *nivel_usuario_fixed ,*nivel_usuario_label;
	gchar *nome_usuario_gchar;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query = malloc(MAX_QUERY_LEN);
	char markup[500];

	if(janelas_gerenciadas.fundo_inicializacao.aberta)
			gtk_widget_destroy(janelas_gerenciadas.fundo_inicializacao.janela_pointer);

	if(!janelas_gerenciadas.aplicacao.criada){
		sprintf(query,"select * from wnd_logger where operador = %i and id_janela = %i order by tempo desc limit 1",sessao_oper.code,REG_WIN_ENCERRA);
		if(!(res = consultar(query))){
			popup(NULL,"Falha ao verificar dados da sessão anterior");
			return 1;
		}

		if((row = mysql_fetch_row(res))){
			if(atoi(row[2])!=0)
				encerramento_brusco = 1;
		}else{
				encerramento_brusco = 0;
		}
	}

	criar_janela_princ();

	sprintf(query,"select data_vencimento - now() from contratos");
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro ao buscar status do serviço");
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"Serviço sem contrato definido, verifique!");
	}else{
		if(atof(row[0])<=0){
			popup(NULL,"Serviço Expirado");
			return 1;
		}
	}

	sprintf(query,"select * from contratos");
	if((res = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber lista de permissões");
		return 1;
	}

	if((row = mysql_fetch_row(res))!=NULL){
		ativar.cadastro=atoi(row[CONTRATO_CAD_COL]);
		ativar.compras=atoi(row[CONTRATO_CMP_COL]);
		ativar.faturamento=atoi(row[CONTRATO_FAT_COL]);
		ativar.estoque=atoi(row[CONTRATO_EST_COL]);
		ativar.financeiro=atoi(row[CONTRATO_FIN_COL]);
		ativar.relatorios=atoi(row[CONTRATO_REL_COL]);
	}else{
		popup(NULL,"Não há lista de permissões");
		return 1;
	}
	if(sessao_oper.nivel>=TECNICO_LEVEL)
		ativar.tecnicos=1;
	else
		ativar.tecnicos=0;

	fixed_menu = gtk_fixed_new();
	param_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(param_button),gtk_image_new_from_icon_name("emblem-system",GTK_ICON_SIZE_DIALOG));

	sair_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(sair_button),gtk_image_new_from_icon_name("application-exit",GTK_ICON_SIZE_DIALOG));

	logoff_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(logoff_button),gtk_image_new_from_icon_name("emblem-synchronizing",GTK_ICON_SIZE_DIALOG));

	suport_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(suport_button),gtk_image_new_from_icon_name("task-due",GTK_ICON_SIZE_DIALOG));

	pegar_data();

	layout = gtk_layout_new(NULL,NULL);

	sprintf(query,"select * from perfil_desktop where code = %i",sessao_oper.code);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		gtk_main_quit();
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem dados para personalizar o sistema");
		gtk_main_quit();
		return 1;
	}

	personalizacao.tema = atoi(row[2]);
	personalizacao.janela_init = atoi(row[3]);
	personalizacao.janela_keep_above = atoi(row[4]);

	GtkSettings *settings;
	settings = gtk_settings_get_default();
	g_object_set(settings, "gtk-theme-name",nomes_temas[personalizacao.tema],NULL);

	sprintf(query,"select a.nome,b.desktop_img from perfil_desktop as b join operadores as a on a.code = b.code where b.code = %i",sessao_oper.code);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Personalizacao com erro");
		gtk_main_quit();
		return 1;
	}

	nome_usuario_gchar = malloc(MAX_OPER_LEN+10);
	row = mysql_fetch_row(res);
	if(row!=NULL)
	{
		imagem_desktop = gtk_image_new_from_file(DESKTOP);
		sprintf(nome_usuario_gchar,"Operador: %s",row[0]);
		nome_usuario_label = gtk_label_new(nome_usuario_gchar);
		gtk_widget_set_name(nome_usuario_label,"nome_operador");
		trocar_desktop(NULL,NULL,atoi(row[1]));
	}
	else
	{
		popup(NULL,"Login sem personalizacao");
		gtk_main_quit();
		return 1;
	}

	if(sessao_oper.nivel>=4)
	{
		GtkSettings *settings;
		imagem_desktop = gtk_image_new_from_file(OPER_DESKTOP);
		settings = gtk_settings_get_default();
		g_object_set(settings, "gtk-theme-name","Adwaita-dark",NULL);
	}

	imagem_barra = gtk_box_new(1,0);
	gtk_widget_set_name(imagem_barra,"barra");
	layout_barra  = gtk_layout_new(NULL,NULL);
	botao_iniciar = gtk_button_new_with_label("Menu");
	gtk_button_set_image(GTK_BUTTON(botao_iniciar),gtk_image_new_from_icon_name("help-contents",GTK_ICON_SIZE_SMALL_TOOLBAR));
	gtk_widget_set_name(GTK_WIDGET(botao_iniciar),"botao");

	//criacao
	caixa_infos = gtk_box_new(1,0);

	superior = gtk_box_new(0,0);
	superior_1 = gtk_box_new(1,0);
	superior_2 = gtk_box_new(0,0);

	inferior = gtk_box_new(0,0);
	inferior_1 = gtk_box_new(1,0);
	inferior_2 = gtk_box_new(1,0);

	barra = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	gtk_widget_set_name(barra,"barra");
	gtk_widget_set_name(botao_iniciar,"botao_iniciar");

	juncao = gtk_box_new(1,0);
	area_de_trabalho = gtk_box_new(0,0);
	//fixed_sup_border = gtk_fixed_new();

	cad_emp_recebe();

	razao = gtk_label_new(cad_emp_strc.xNome);
	endereco = gtk_label_new(cad_emp_strc.xLgr);
	cnpj = gtk_label_new(cad_emp_strc.CNPJ);

	gtk_widget_set_name(razao,"infos");
	gtk_widget_set_name(cnpj,"infos");
	gtk_widget_set_name(endereco,"infos");

	fixed_razao = gtk_fixed_new();
	fixed_endereco = gtk_fixed_new();
	fixed_cnpj = gtk_fixed_new();

	gtk_fixed_put(GTK_FIXED(fixed_razao),razao,50,300);
	gtk_fixed_put(GTK_FIXED(fixed_endereco),endereco,50,5);
	gtk_fixed_put(GTK_FIXED(fixed_cnpj),cnpj,50,5);

	sprintf(query, "select code, nome, nivel from niveis_gerenciais;");

	niveis_gerenciais = malloc(MAX_NIVEL_GER_NOME*MAX_NIVEL_GER_QNT);
	oper_perm_qnt_niveis = 0;

	if((res = consultar(query))==NULL)
		return 1;

	while((row = mysql_fetch_row(res))!=NULL){

		niveis_gerenciais[oper_perm_qnt_niveis] = malloc(MAX_NIVEL_GER_NOME);

		strcpy(niveis_gerenciais[oper_perm_qnt_niveis],row[1]);

		oper_perm_qnt_niveis++;

		if(oper_perm_qnt_niveis>=MAX_NIVEL_GER_QNT)
			break;
	}

	if(oper_perm_qnt_niveis<=0){
		popup(NULL,"Faltam dados para niveis gerenciais");
		return 1;
	}

	nivel_usuario_fixed = gtk_fixed_new();

	if(sessao_oper.nivel-1<oper_perm_qnt_niveis)
		nivel_usuario_label = gtk_label_new(niveis_gerenciais[sessao_oper.nivel-1]);
	else
		nivel_usuario_label = gtk_label_new("Nivel Ilimitado");

	gtk_widget_set_name(nivel_usuario_label,"nivel_operador");

	hostname_fixed = gtk_fixed_new();
	hostname_label = gtk_label_new(server_confs.server_endereco);

	gtk_widget_set_name(hostname_fixed,"hostname-label");
	gtk_widget_set_name(hostname_label,"hostname-label");

	nome_usuario_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(nome_usuario_fixed),nome_usuario_label,100,200);
	gtk_fixed_put(GTK_FIXED(nivel_usuario_fixed),nivel_usuario_label,100,220);

	gtk_fixed_put(GTK_FIXED(hostname_fixed),hostname_label,100,240);

	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_razao,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_endereco,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_cnpj,0,0,0);

	gtk_box_pack_start(GTK_BOX(superior),superior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(superior),superior_2,0,0,0);

	gtk_box_pack_start(GTK_BOX(inferior),inferior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(inferior),inferior_2,0,0,0);

	gtk_widget_set_size_request(GTK_WIDGET(superior),1291,0);
	gtk_widget_set_size_request(GTK_WIDGET(inferior),1291,0);

	gtk_widget_set_size_request(GTK_WIDGET(juncao),1290,750);
	gtk_widget_set_size_request(GTK_WIDGET(area_de_trabalho),1290,750);
	gtk_box_pack_start(GTK_BOX(juncao),superior,0,0,0);
	gtk_box_pack_start(GTK_BOX(juncao),inferior,0,0,0);

	gtk_box_pack_start(GTK_BOX(area_de_trabalho),juncao,0,0,0);

	gtk_layout_put(GTK_LAYOUT(layout_barra),imagem_barra,0,0);
	gtk_layout_put(GTK_LAYOUT(layout_barra),botao_iniciar,0,1);
	gtk_layout_put(GTK_LAYOUT(layout_barra),suport_button,0,470);
	gtk_layout_put(GTK_LAYOUT(layout_barra),param_button,0,530);
	gtk_layout_put(GTK_LAYOUT(layout_barra),logoff_button,0,590);
	gtk_layout_put(GTK_LAYOUT(layout_barra),sair_button,0,650);

	gtk_widget_set_size_request(GTK_WIDGET(botao_iniciar),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(param_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(logoff_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(sair_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(suport_button),75,60);

	gtk_widget_set_size_request(barra,80,750);
	gtk_widget_set_size_request(layout_barra,80,750);

	gtk_container_add(GTK_CONTAINER(barra),layout_barra);

	gtk_box_pack_end(GTK_BOX(area_de_trabalho),barra,0,0,0);

	gtk_widget_set_size_request(imagem_desktop,1290,750);
	gtk_layout_put(GTK_LAYOUT(layout), imagem_desktop, 0, 0);
	gtk_layout_put(GTK_LAYOUT(layout),nome_usuario_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),nivel_usuario_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),hostname_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),caixa_infos,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),area_de_trabalho,0,0);

	gtk_container_add(GTK_CONTAINER(janela_principal),layout);

	if(menu()!=0)
		return 1;

	gtk_fixed_put(GTK_FIXED(fixed_menu),frame_lista_abas,0,0);
	gtk_box_pack_end(GTK_BOX(superior_2),fixed_menu,0,0,0);

	g_signal_connect(janela_principal,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.principal);

	g_signal_connect(GTK_WIDGET(botao_iniciar),"clicked",G_CALLBACK(clique_menu),NULL);

	g_signal_connect(GTK_BUTTON(sair_button),"clicked",G_CALLBACK(botao_encerrar),janela_principal);

	g_signal_connect(GTK_BUTTON(param_button),"clicked",G_CALLBACK(parametrizar),NULL);

	g_signal_connect(GTK_BUTTON(suport_button),"clicked",G_CALLBACK(suporte_princ_wnd),NULL);

	g_signal_connect(GTK_BUTTON(logoff_button),"clicked",G_CALLBACK(fechar_sessao),NULL);

	g_signal_connect(janela_principal,"destroy",G_CALLBACK(encerrar),janela_principal);

	gtk_widget_show_all(janela_principal);

	configurar_parametros();

	iniciar_gerenciador_janela();

	gtk_widget_hide(lista_abas);
	if(encerramento_brusco){
		reportar_encerramento_brusco();
		encerramento_brusco = 0;
	}

	janelas_gerenciadas.aplicacao.criada = 1;
	return 0;
}

int init()
{
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
		popup(NULL,"Sem dados técnicos personalizados");
		strcpy(cad_emp_strc.init_image_path,"");
	}
	else{
		person_tecn_prim = 0;
		strcpy(cad_emp_strc.init_image_path,row[1]);
	}

	imagem_inicializacao = gtk_image_new_from_file(cad_emp_strc.init_image_path);
	gtk_widget_set_size_request(GTK_WIDGET(imagem_inicializacao),1366,768);

	janela_inicializacao = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_resizable(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_icon_name(GTK_WINDOW(janela_inicializacao),"preferences-desktop-screensaver");
	gtk_container_add(GTK_CONTAINER(janela_inicializacao),imagem_inicializacao);
	gtk_window_set_decorated(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_deletable(GTK_WINDOW(janela_inicializacao),FALSE);
	gtk_window_set_keep_above(GTK_WINDOW(janela_inicializacao),TRUE);
	janelas_gerenciadas.fundo_inicializacao.janela_pointer = janela_inicializacao;
	gtk_widget_show_all(janela_inicializacao);

	sprintf(query,"select janela_init,tema from perfil_desktop");
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Sem dados para personalizar o sistema");
		return 1;
	}

	GtkSettings *settings = gtk_settings_get_default();
	gchar **path;
	int n_elements;

	g_object_set(settings, "gtk-theme-name","Adwaita",NULL);
	icone = gtk_icon_theme_get_default();

	gtk_icon_theme_get_search_path(icone,&path,&n_elements);
	n_elements = n_elements+1;
	path[n_elements-1] = malloc(strlen(ICON_PATH));
	strcpy((char*)path[n_elements-1],ICON_PATH);

	gtk_icon_theme_set_search_path(icone, (const gchar**)path, n_elements);

	//return 1;

	personalizacao.tema = atoi(row[1]);
	ler_theme_dir();

	if(atoi(row[0])==0)
	{
		sessao_oper.code = default_user_code;
		sessao_oper.nivel = 3;
		gtk_widget_destroy(janela_inicializacao);
		if(desktop()!=0)
		{
			popup(NULL,"Erro na inicializacao");
			inicializando=0;
			return 1;
		}
	}
	else
	{
		login();
		gtk_widget_show_all(janela_login);
	}

	janelas_gerenciadas.fundo_inicializacao.reg_id = REG_INIT_FUN_WIN;
	janelas_gerenciadas.fundo_inicializacao.aberta = 1;
	if(ger_janela_aberta(janela_inicializacao, &janelas_gerenciadas.fundo_inicializacao))
		return 1;

	inicializando=0;

	return 0;
}
