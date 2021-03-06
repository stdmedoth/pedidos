struct _operador *get_operador(int oper_code){
	struct _operador *operador = malloc(sizeof(struct _operador));

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	sprintf(query, "select * from operadores where code = %i", oper_code);
	if(!(res = consultar(query))){
		return NULL;
	}
	if(!(row = mysql_fetch_row(res))){
		return NULL;
	}

	operador->code = atoi(row[OPER_CODE]);
	operador->nome = strdup(row[OPER_NOME]);
	operador->senha = strdup(row[OPER_SENHA]);
	operador->nivel = atoi(row[OPER_NIVEL]);

	return operador;
}
void oper_ver_senha(GtkWidget *button, GtkWidget *senha_entry){
	if(senha_entry){
		GtkInputPurpose tipo = gtk_entry_get_input_purpose(GTK_ENTRY(senha_entry));
		if((gtk_entry_get_visibility(GTK_ENTRY(senha_entry)))){
			gtk_entry_set_visibility(GTK_ENTRY(senha_entry),FALSE);
		}else{
			gtk_entry_set_visibility(GTK_ENTRY(senha_entry),TRUE);
		}
	}
}

void passa_nome(){

	oper_nome_login = malloc(MAX_OPER_LEN);
	oper_nome_login =(gchar*) gtk_entry_get_text(GTK_ENTRY(nome_entry));
	if(!strlen(oper_nome_login)){
		popup(janela_login,"Insira o operador");
		gtk_widget_grab_focus(nome_entry);
		return ;
	}

	if(!strcmp(oper_nome_login, login_bindings[LOGIN_BIND_ENTRAR])){

		g_signal_handler_disconnect(janela_login,g_handle_janela_login);

		if(GTK_IS_WIDGET(janela_login))
			gtk_widget_destroy(janela_login);

		criar_sessao_anon();

		if(desktop()!=0)
			encerrando();
		return ;
	}

	if(!strcmp(oper_nome_login, login_bindings[LOGIN_BIND_SAIR])){
		encerrando();
		return ;
	}
	gtk_widget_grab_focus(senha_entry);
}

void passa_senha(){
	gtk_widget_grab_focus(enviar_login);
}

void verifica_senha(){

	char query[MAX_QUERY_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;
	char unvulned_nome[MAX_OPER_LEN];
	char unvulned_senha[MAX_SEN_LEN];
	oper_nome_login = malloc(MAX_OPER_LEN);
	oper_senha_login = malloc(MAX_SEN_LEN);

	oper_nome_login = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_entry));
	oper_senha_login = (gchar*) gtk_entry_get_text(GTK_ENTRY(senha_entry));

	if(!strlen(oper_nome_login)){
		oper_nome_login = strdup("");
	}
	if(!strlen(oper_senha_login)){
		oper_senha_login = strdup("");
	}

	mysql_real_escape_string(&conectar,unvulned_nome,oper_nome_login,strlen(oper_nome_login));
	mysql_real_escape_string(&conectar,unvulned_senha,oper_senha_login,strlen(oper_senha_login));

	sprintf(query,"select * from operadores where nome = '%s' and senha = MD5('%s');",unvulned_nome,unvulned_senha);
	if(!(res = consultar(query))){
		file_logger("verifica_senha() -> consultar() -> tabela operadores");
		popup(janela_login,"Erro de comunicacao com banco");
		encerrando();
		return ;
	}

	if((row = mysql_fetch_row(res))){

		g_signal_handler_disconnect(janela_login, g_handle_janela_login);

		sessao_oper = get_new_sessao_from_oper( atoi(row[OPER_CODE]) );
		if(!sessao_oper){
			file_logger("verifica_senha() -> get_new_sessao_from_oper()");
			popup(NULL,"Não foi possível carregar sessão pelo operador");
			return ;
		}

		if(GTK_IS_WIDGET(janela_login))
			gtk_widget_destroy(janela_login);

		if(desktop()!=0){
			file_logger("verifica_senha() -> desktop()");
			encerrando();
			return ;
		}

	}else{

		popup(janela_login,"Usuário ou Senha incorretos");
		gtk_widget_grab_focus(senha_entry);
		return;

	}

	return;
}

int login()
{
	GtkWidget *oper_psq_button, *oper_nome_box;
	GtkWidget *nome_label,*senha_label;
	GtkWidget *caixa_login,*caixa_nome,*caixa_senha,*caixa_opcoes;
	GtkWidget *caixa_senha_visubutton, *senha_visubutton;

	GtkWidget *nome_fixed, *senha_fixed;

	janela_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela_login,230,200);
	gtk_window_set_decorated(GTK_WINDOW(janela_login),FALSE);
	gtk_window_set_deletable(GTK_WINDOW(janela_login),FALSE);
	gtk_window_set_icon_name(GTK_WINDOW(janela_login),"system-users");
	gtk_window_set_title(GTK_WINDOW(janela_login),"Login");
	gtk_window_set_resizable(GTK_WINDOW(janela_login),FALSE);

	janelas_gerenciadas.login.reg_id = REG_WIN_LOGIN;
	janelas_gerenciadas.login.aberta = 1;
	//if(ger_janela_aberta(janela_login, &janelas_gerenciadas.login))
	//	return 1;
	janelas_gerenciadas.login.janela_pointer = janela_login;

	gtk_window_set_transient_for(GTK_WINDOW(janela_login),GTK_WINDOW(janelas_gerenciadas.fundo_inicializacao.janela_pointer));

	gtk_window_set_keep_above(GTK_WINDOW(janela_login),TRUE);

	gtk_window_set_position(GTK_WINDOW(janela_login),3);

	oper_nome_box = gtk_box_new(0,0);
	oper_psq_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(oper_psq_button),gtk_image_new_from_file(IMG_PESQ));

	nome_fixed = gtk_fixed_new();
	senha_fixed = gtk_fixed_new();

	nome_label = gtk_label_new("Usuário");
	senha_label = gtk_label_new("Senha");
	enviar_login = gtk_button_new_with_label("Logar");
	fechar_login = gtk_button_new_with_label("Cancelar");
	senha_visubutton = gtk_button_new();
	caixa_senha_visubutton = gtk_box_new(0,0);

	gtk_button_set_image(GTK_BUTTON(senha_visubutton),gtk_image_new_from_icon_name("security-low",GTK_ICON_SIZE_BUTTON));

	nome_entry = gtk_entry_new();
	senha_entry = gtk_entry_new();

	gtk_entry_set_placeholder_text(GTK_ENTRY(nome_entry),"Login:");
	gtk_entry_set_placeholder_text(GTK_ENTRY(senha_entry),"Senha:");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(nome_entry),GTK_ENTRY_ICON_PRIMARY,"user-info");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(senha_entry),GTK_ENTRY_ICON_PRIMARY,"dialog-password");
	gtk_entry_set_input_purpose(GTK_ENTRY(senha_entry),GTK_INPUT_PURPOSE_PASSWORD);
	gtk_entry_set_visibility(GTK_ENTRY(senha_entry),FALSE);
	caixa_nome = gtk_box_new(1,0);
	caixa_senha = gtk_box_new(1,0);
	caixa_opcoes = gtk_box_new(0,0);
	caixa_login = gtk_box_new(1,0);

	gtk_box_pack_start(GTK_BOX(caixa_nome),nome_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(oper_nome_box),nome_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(oper_nome_box),oper_psq_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_nome),oper_nome_box,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixa_senha_visubutton),senha_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_senha_visubutton),senha_visubutton,0,0,5);

	gtk_box_pack_start(GTK_BOX(caixa_senha),senha_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_senha),caixa_senha_visubutton,0,0,0);

	gtk_fixed_put(GTK_FIXED(nome_fixed),caixa_nome,15,10);
	gtk_fixed_put(GTK_FIXED(senha_fixed),caixa_senha,15,10);

	gtk_entry_set_width_chars(GTK_ENTRY(senha_entry),20);

	gtk_box_pack_start(GTK_BOX(caixa_opcoes),enviar_login,0,0,20);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),fechar_login,0,0,10);

	gtk_box_pack_start(GTK_BOX(caixa_login),nome_fixed,0,0,15);
	gtk_box_pack_start(GTK_BOX(caixa_login),senha_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_login),caixa_opcoes,0,0,10);

	gtk_widget_set_name(janela_login,"janela_login");
	gtk_container_add(GTK_CONTAINER(janela_login),caixa_login);

	g_signal_connect(enviar_login,"clicked",G_CALLBACK(verifica_senha),NULL);
	g_signal_connect(fechar_login,"clicked",G_CALLBACK(encerrar),janela_login);
	g_signal_connect(nome_entry,"activate",G_CALLBACK(passa_nome),NULL);
	g_signal_connect(senha_entry,"activate",G_CALLBACK(passa_senha),NULL);

	g_signal_connect(senha_visubutton,"clicked",G_CALLBACK(oper_ver_senha),senha_entry);
	g_signal_connect(oper_psq_button,"clicked",G_CALLBACK(psq_oper),nome_entry);

	g_handle_janela_login = g_signal_connect(janela_login,"destroy",G_CALLBACK(encerrando),NULL);
	//g_signal_connect(janela_login,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.login.janela_pointer);

	gtk_widget_grab_focus(nome_entry);
	return 0;
}
