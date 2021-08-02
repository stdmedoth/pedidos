static void criar_janela_princ(){

	janela_principal = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	gtk_window_set_position(GTK_WINDOW(janela_principal),0);
	gtk_window_set_resizable(GTK_WINDOW(janela_principal),TRUE);
	gtk_window_set_title(GTK_WINDOW(janela_principal),"Pedidos");
	gtk_container_set_border_width(GTK_CONTAINER(janela_principal),0);

	gtk_window_maximize(GTK_WINDOW(janela_principal));

	gtk_window_set_default_size(GTK_WINDOW(janela_principal), desktop_width, desktop_heigth);

	gtk_window_set_icon_name(GTK_WINDOW(janela_principal),"accessories-dictionary");
	gtk_window_set_deletable (GTK_WINDOW(janela_principal), FALSE);

	janelas_gerenciadas.principal.reg_id = REG_PRINC_WIN;

	if(ger_janela_aberta(janela_principal, &janelas_gerenciadas.principal))
		return ;

	janelas_gerenciadas.principal.aberta = 1;
	janelas_gerenciadas.aplicacao.criada = 1;
	janelas_gerenciadas.principal.janela_pointer = janela_principal;

	gtk_widget_show_all(janela_principal);

	//keybinds made on code
	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(sobre_infos_keyfun),NULL);
	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(tecla_menu),NULL);
	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(atalho_fechar_sessao),NULL);
	g_signal_connect(GTK_WIDGET(janela_principal),"delete-event",G_CALLBACK(desktop_window_delete_event),NULL);


	if(param_funcionalidades.inatividade_fecha)
		g_timeout_add (100, atualizar_inatividade_label, NULL);

	//g_signal_connect(janela_principal,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.principal); //works only on gtk_window_set_deletable = TRUE
	//g_signal_connect(janela_principal,"destroy",G_CALLBACK(encerrar),janela_principal); //works only on gtk_window_set_deletable = TRUE
	return ;
}

int desktop(){
	int err=0;
	GtkWidget  *juncao;
	GtkWidget  *layout;
	GtkWidget *fixed_menu;

	GtkWidget *hostname_fixed, *hostname_label;
	GtkWidget *nome_usuario_label,*nome_usuario_fixed;
	GtkWidget *nivel_usuario_fixed ,*nivel_usuario_label;
	gchar *nome_usuario_gchar;

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char markup[500];

	if(!janelas_gerenciadas.aplicacao.criada){

		check_encerramento_file();
		create_encerramento_file();

	}


	if(validar_sessao_criada()){
		file_logger("desktop() -> validar_sessao_criada()");
		return 1;
	}

	if(janelas_gerenciadas.fundo_inicializacao.aberta)
		gtk_widget_destroy(janelas_gerenciadas.fundo_inicializacao.janela_pointer);


	gchar *sessao_criacao_gchar = malloc(MAX_DATE_LEN + 40);
	gchar *sessao_expiracao_gchar = malloc(MAX_DATE_LEN + 40);
	gchar *sessao_inatividade_gchar = malloc(MAX_DATE_LEN + 40);

	GtkWidget *sessao_criacao_fixed = gtk_fixed_new();
	GtkWidget *sessao_expiracao_fixed = gtk_fixed_new();
	GtkWidget *sessao_inatividade_fixed = gtk_fixed_new();

	sprintf(sessao_criacao_gchar,"Entrou em : %s", g_date_time_format (sessao_oper->criacao, "%H:%M:%S"));
	sprintf(sessao_expiracao_gchar,"Expira em : %s", g_date_time_format (sessao_oper->expiracao, "%H:%M:%S"));

	#ifdef APP_32BIT
	sprintf(sessao_inatividade_gchar,"Limite Inatividade: %ld segundos", (G_TIME_SPAN_MINUTE * SESSAO_MAX_INATIVIDADE)/G_TIME_SPAN_SECOND);
	#else
	sprintf(sessao_inatividade_gchar,"Limite Inatividade: %lld segundos", faltante);
	#endif

	sessao_criacao_label = gtk_label_new(sessao_criacao_gchar);
	gtk_fixed_put(GTK_FIXED(sessao_criacao_fixed), sessao_criacao_label, 100,5);
	gtk_widget_set_name(sessao_criacao_label,"sessao_infos");

	sessao_expiracao_label = gtk_label_new(sessao_expiracao_gchar);
	gtk_fixed_put(GTK_FIXED(sessao_expiracao_fixed), sessao_expiracao_label, 100,0);
	gtk_widget_set_name(sessao_expiracao_label,"sessao_infos");

	sessao_inatividade_label = gtk_label_new(sessao_inatividade_gchar);
	gtk_fixed_put(GTK_FIXED(sessao_inatividade_fixed), sessao_inatividade_label, 100,0);
	gtk_widget_set_name(sessao_inatividade_label,"sessao_infos");

	app = gtk_application_new ("calisto.pedidos", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (criar_janela_princ), NULL);
	int status = g_application_run (G_APPLICATION (app), 0, NULL);
	if(status){
		popup(NULL,"Não foi possível carregar App");
		return 1;
	}
	g_object_unref (app);
	carregar_interface();

	if(sessao_oper->status_sessao == SESSAO_LOGADA){
		sprintf(query,"select *, data_vencimento - now() from contratos where ativo = 1");
		if(!(res = consultar(query))){
			popup(NULL,"Erro ao buscar status do serviço");
			return 1;
		}
		if(!(row = mysql_fetch_row(res))){
			autologger("Não existem contratos ativos");
			ativar.ativo = 0;
		}else{
			if(atoi(row[CONTRATOS_COLS_QNT])<=0){
				popup(NULL,"Serviço Expirado");
				ativar.ativo = 0;
			}else
				ativar.ativo = 1;
		}
	}

	sessao_set_nonemodules();

	if( ativar.ativo && sessao_oper->status_sessao == SESSAO_LOGADA ){
		ativar.cadastro = atoi( row[CONTRATOS_CAD_COL] );
		ativar.compras = atoi( row[CONTRATOS_CMP_COL] );
		ativar.faturamento = atoi( row[CONTRATOS_FAT_COL] );
		ativar.estoque = atoi( row[CONTRATOS_EST_COL] );
		ativar.financeiro = atoi( row[CONTRATOS_FIN_COL] );
		ativar.marketing = atoi( row[CONTRATOS_MARKT_COL] );
		ativar.relatorios = atoi( row[CONTRATOS_REL_COL] );
	}

	if(sessao_oper->operador->nivel>=NIVEL_TECNICO){
		sessao_set_allmodules();
	}

	fixed_menu = gtk_fixed_new();

	pegar_data();

	layout = gtk_layout_new(NULL,NULL);
	enum{
		CODE,
		DESKTOP_IMG,
		TEMA,
		JANELA_INIT,
		JANELAS_KEEP_ABOVE
	};
	sprintf(query,"select * from perfil_desktop where code = %i",sessao_oper->operador->code);
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro ao receber dados para personalizacao do sistema");
		gtk_main_quit();
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Sem dados para personalizar o sistema");
		gtk_main_quit();
		return 1;
	}

	personalizacao.tema = atoi(row[TEMA]);
	personalizacao.janela_init = atoi(row[JANELA_INIT]);
	personalizacao.janela_keep_above = atoi(row[JANELAS_KEEP_ABOVE]);

	nome_usuario_gchar = malloc(MAX_OPER_LEN+10);
	imagem_desktop = gtk_image_new_from_file(DESKTOP);
	sprintf(nome_usuario_gchar,"Operador: %s",sessao_oper->operador->nome);
	nome_usuario_label = gtk_label_new(nome_usuario_gchar);
	gtk_widget_set_name(nome_usuario_label,"nome_operador");
	trocar_desktop(NULL,NULL,atoi(row[DESKTOP_IMG]));


	GtkSettings *settings;
	settings = gtk_settings_get_default();

	if(personalizacao.tema>=0){
		if(nomes_temas[personalizacao.tema])
			g_object_set(settings, "gtk-theme-name",nomes_temas[personalizacao.tema],NULL);
	}else{
		g_object_set(settings, "gtk-theme-name","Adwaita",NULL);
	}

	if(sessao_oper->operador->nivel==NIVEL_TECNICO){
		GtkSettings *settings;
		imagem_desktop = gtk_image_new_from_file(OPER_DESKTOP_IMG);
		settings = gtk_settings_get_default();
		g_object_set(settings, "gtk-theme-name",NIVEL_TECNICO_THEME,NULL);
	}

	if(sessao_oper->operador->nivel>=NIVEL_CRIADOR){
		GtkSettings *settings;
		imagem_desktop = gtk_image_new_from_file(GOD_DESKTOP_IMG);
		settings = gtk_settings_get_default();
		g_object_set(settings, "gtk-theme-name",NIVEL_TECNICO_THEME,NULL);
	}

	caixa_infos = gtk_box_new(1,0);

	superior = gtk_box_new(0,0);
	superior_1 = gtk_box_new(1,0);
	superior_2 = gtk_box_new(0,0);

	inferior = gtk_box_new(0,0);
	inferior_1 = gtk_box_new(1,0);
	inferior_2 = gtk_box_new(1,0);

	barra = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	gtk_widget_set_name(barra,"barra");

	juncao = gtk_box_new(1,0);
	area_de_trabalho = gtk_box_new(0,0);

	cad_emp_recebe();

	razao = gtk_label_new(cad_emp_strc.xNome);
	endereco = gtk_label_new(cad_emp_strc.xLgr);
	cnpj = gtk_label_new(cad_emp_strc.CNPJ);
	gtk_label_set_selectable(GTK_LABEL(cnpj),TRUE);

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

	if(!(res = consultar(query))){
		file_logger("desktop() -> consultar() -> tabela niveis_gerenciais");
		return 1;
	}

	while((row = mysql_fetch_row(res))!=NULL){

		niveis_gerenciais[oper_perm_qnt_niveis] = malloc(MAX_NIVEL_GER_NOME);

		strcpy(niveis_gerenciais[oper_perm_qnt_niveis],row[1]);

		oper_perm_qnt_niveis++;

		if(oper_perm_qnt_niveis>=MAX_NIVEL_GER_QNT)
			break;
	}

	if(oper_perm_qnt_niveis<=0){
		file_logger("desktop() -> mysql_fetch_row() -> tabela niveis_gerenciais");
		popup(NULL,"Faltam dados para niveis gerenciais");
		return 1;
	}

	nivel_usuario_label = gtk_label_new("Nível Indefinido");

	nivel_usuario_fixed = gtk_fixed_new();

	if(sessao_oper->operador->nivel<oper_perm_qnt_niveis)
		gtk_label_set_text(GTK_LABEL(nivel_usuario_label), niveis_gerenciais[sessao_oper->operador->nivel]);

	if(sessao_oper->operador->nivel >= NIVEL_TECNICO && sessao_oper->operador->nivel < OPER_MAX_NIVEL )
		gtk_label_set_text(GTK_LABEL(nivel_usuario_label), "Nível Técnico");

	if(sessao_oper->operador->nivel >= OPER_MAX_NIVEL)
		gtk_label_set_text(GTK_LABEL(nivel_usuario_label),"O Criador");

	gtk_widget_set_name(nivel_usuario_label,"nivel_operador");

	hostname_fixed = gtk_fixed_new();
	maquina_atual = maquinas_get_atual();
	printf("%p\n", (void* )maquina_atual);
	char *endereco_maquina;
	if(maquina_atual){
		endereco_maquina = malloc(strlen(server_confs.server_endereco) + strlen(maquina_atual->hostname) + 2);
	}else{
		file_logger("desktop() -> maquinas_get_atual()");
		return 1;
	}

	sprintf(endereco_maquina,"%s@%s", server_confs.server_endereco, maquina_atual->hostname);

	hostname_label = gtk_label_new(endereco_maquina);
	gtk_label_set_selectable(GTK_LABEL(hostname_label),TRUE);

	while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

	gtk_widget_set_name(hostname_label,"hostname-label");

	nome_usuario_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(nome_usuario_fixed),nome_usuario_label,100,200);
	gtk_fixed_put(GTK_FIXED(nivel_usuario_fixed),nivel_usuario_label,100,220);

	gtk_fixed_put(GTK_FIXED(hostname_fixed),hostname_label,100,240);

	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_razao,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_endereco,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),fixed_cnpj,0,0,0);

	if(param_funcionalidades.expirar_sessao){
		gtk_box_pack_start(GTK_BOX(caixa_infos),sessao_criacao_fixed,0,0,0);
		gtk_box_pack_start(GTK_BOX(caixa_infos),sessao_expiracao_fixed,0,0,0);
	}

	if(param_funcionalidades.inatividade_fecha){
		gtk_box_pack_start(GTK_BOX(caixa_infos),sessao_inatividade_fixed,0,0,0);
	}


	gtk_box_pack_start(GTK_BOX(superior),superior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(superior),superior_2,0,0,0);

	gtk_box_pack_start(GTK_BOX(inferior),inferior_1,0,0,0);
	gtk_box_pack_end(GTK_BOX(inferior),inferior_2,0,0,0);

	gtk_widget_set_size_request(GTK_WIDGET(superior),desktop_width,0);
	gtk_widget_set_size_request(GTK_WIDGET(inferior),desktop_width,0);

	gtk_widget_set_size_request(GTK_WIDGET(area_de_trabalho),desktop_width,desktop_heigth);
	gtk_widget_set_size_request(GTK_WIDGET(juncao),desktop_width,desktop_heigth);
	gtk_box_pack_start(GTK_BOX(juncao),superior,0,0,0);
	gtk_box_pack_start(GTK_BOX(juncao),inferior,0,0,0);

	gtk_box_pack_start(GTK_BOX(area_de_trabalho),juncao,0,0,0);

	gtk_widget_set_size_request(barra,80, desktop_heigth);

	notificacoes_receber();

	GtkWidget *barra_icones = barra_icones_wnd();
	gtk_widget_set_size_request(barra_icones,80,desktop_heigth);
	gtk_container_add(GTK_CONTAINER(barra),barra_icones);

	GtkWidget *caixa_calendario = get_desktop_calendario();
	gtk_box_pack_end(GTK_BOX(area_de_trabalho),barra,0,0,0);
	gtk_widget_set_size_request(imagem_desktop, desktop_width, desktop_heigth);

	gtk_layout_put(GTK_LAYOUT(layout), imagem_desktop, 0, 0);
	gtk_layout_put(GTK_LAYOUT(layout),nome_usuario_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),nivel_usuario_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),hostname_fixed,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),caixa_infos,0,0);
	if(sessao_oper->operador->nivel >= NIVEL_GERENCIAL)
		gtk_layout_put(GTK_LAYOUT(layout),caixa_calendario,400,200);
	gtk_layout_put(GTK_LAYOUT(layout),area_de_trabalho,0,0);

	gtk_container_add(GTK_CONTAINER(janela_principal),layout);

	carregar_interface();

	gtk_box_pack_end(GTK_BOX(superior_2),fixed_menu,0,0,0);

	gtk_widget_show_all(janela_principal);

	configurar_parametros();

	iniciar_gerenciador_janela();

	if(encerramento_brusco){
		reportar_encerramento_brusco();
		encerramento_brusco = 0;
	}

	janelas_gerenciadas.aplicacao.criada = 1;
	return 0;
}
