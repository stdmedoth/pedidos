void encerrando()
{
	GtkWidget *janela, *label;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	label = gtk_label_new("Encerrando...");
	gtk_widget_set_size_request(janela,100,100);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_container_add(GTK_CONTAINER(janela),label);
	gtk_widget_show_all(janela);
	
	g_usleep ( 100000 );
	gtk_main_quit();
}
void passa_nome()
{
	gtk_widget_grab_focus(senha_entry);
}

void passa_senha()
{
	gtk_widget_grab_focus(enviar_login);
}

void verifica_senha()
{
	
	char *query;
	MYSQL_RES *res;
	MYSQL_ROW row;	
	gchar *nome_gchar,*senha_gchar;

	nome_gchar = malloc(MAX_OPER_LEN);
	senha_gchar = malloc(MAX_SEN_LEN);
	query = malloc(MAX_QUERY_LEN);

	nome_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(nome_entry));
	senha_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(senha_entry));

	sprintf(query,"select code,senha from operadores where nome = '%s';",nome_gchar);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro de comunicacao com banco");
		return;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Usuário não existente");
		gtk_widget_grab_focus(nome_entry);
		return;
	}
	if(strcmp(row[1],senha_gchar)==0)
	{
		oper_code = malloc(MAX_OPER_LEN);
		strcpy(oper_code,row[0]);

		g_signal_handler_disconnect(janela_login,g_handle_janela_login);
		gtk_widget_destroy(janela_login);

		desktop();
		return;
	}
	else
	{
		popup(NULL,"Senha incorreta");
		gtk_widget_grab_focus(senha_entry);
		return;
	}	
	return;
}

void login()
{
	GtkWidget *nome_label,*senha_label;
	GtkWidget *caixa_login,*caixa_nome,*caixa_senha,*caixa_opcoes;
	
	GtkWidget *nome_fixed, *senha_fixed;
	janela_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela_login,200,200);
	gtk_window_set_decorated(GTK_WINDOW(janela_login),FALSE);
	gtk_window_set_deletable(GTK_WINDOW(janela_login),FALSE);
	gtk_window_set_icon_name(GTK_WINDOW(janela_login),"system-users");
	gtk_window_set_title(GTK_WINDOW(janela_login),"Login");
	gtk_window_set_resizable(GTK_WINDOW(janela_login),FALSE);
	
	if( personalizacao.janela_keep_above == 1 )
	{	
		gtk_window_set_keep_above(GTK_WINDOW(janela_login),TRUE);
	}
	
	gtk_window_set_position(GTK_WINDOW(janela_login),3);
	
	nome_fixed = gtk_fixed_new();
	senha_fixed = gtk_fixed_new();
	
	nome_label = gtk_label_new("Usuário");
	senha_label = gtk_label_new("Senha");
	enviar_login = gtk_button_new_with_label("Logar");
	fechar_login = gtk_button_new_with_label("Cancelar");
	
	nome_entry = gtk_entry_new();
	senha_entry = gtk_entry_new();
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(nome_entry),"Login:");
	gtk_entry_set_placeholder_text(GTK_ENTRY(senha_entry),"Senha:");
	gtk_entry_set_input_purpose(GTK_ENTRY(senha_entry),GTK_INPUT_PURPOSE_PIN);
	gtk_entry_set_visibility(GTK_ENTRY(senha_entry),FALSE);
	caixa_nome = gtk_box_new(1,0);
	caixa_senha = gtk_box_new(1,0);
	caixa_opcoes = gtk_box_new(0,0);
	caixa_login = gtk_box_new(1,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_nome),nome_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_nome),nome_entry,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_senha),senha_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_senha),senha_entry,0,0,0);

	#ifdef __linux__
	gtk_fixed_put(GTK_FIXED(nome_fixed),caixa_nome,15,10);
	gtk_fixed_put(GTK_FIXED(senha_fixed),caixa_senha,15,10);
	#endif
	#ifdef WIN32
	gtk_fixed_put(GTK_FIXED(nome_fixed),caixa_nome,25,10);
	gtk_fixed_put(GTK_FIXED(senha_fixed),caixa_senha,25,10);
	#endif
	gtk_entry_set_width_chars(GTK_ENTRY(nome_entry),20);
	gtk_entry_set_width_chars(GTK_ENTRY(senha_entry),20);

	gtk_box_pack_start(GTK_BOX(caixa_opcoes),enviar_login,0,0,20);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),fechar_login,0,0,10);	
	
	gtk_box_pack_start(GTK_BOX(caixa_login),nome_fixed,0,0,15);
	gtk_box_pack_start(GTK_BOX(caixa_login),senha_fixed,0,0,5);	
	gtk_box_pack_start(GTK_BOX(caixa_login),caixa_opcoes,0,0,10);	

	gtk_widget_set_name(janela_login,"janela_login");
	gtk_container_add(GTK_CONTAINER(janela_login),caixa_login);
	
	g_signal_connect(enviar_login,"clicked",G_CALLBACK(verifica_senha),NULL);
	g_signal_connect(fechar_login,"clicked",G_CALLBACK(encerrar),NULL);
	g_signal_connect(nome_entry,"activate",G_CALLBACK(passa_nome),NULL);
	g_signal_connect(senha_entry,"activate",G_CALLBACK(passa_senha),NULL);
	
	g_handle_janela_login = g_signal_connect(janela_login,"destroy",G_CALLBACK(encerrando),NULL);
	
	gtk_widget_grab_focus(nome_entry);
	return ;
}
