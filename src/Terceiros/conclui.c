int conclui_ter(GtkWidget* nome, gpointer *botao)
{
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW campos;
	char *code;
	code = malloc(10);
	char *query;
	int cont;
	for(cont=0;cont<=CAMPOS_QNT;cont++)
	{
		if(vet_erro[cont]!=0)
		{
			popup(NULL,"Você tem campos incorretos\n\tRepasse com tecla ENTER");
			g_print("Tentou concluir cadastro com campos incorretos: campo %i\n",cont);
			autologger("Tentou concluir cadastro com campos incorretos");
			return 1;
		}
	}
	g_print("alocando memoria para query %i\n",(int)(QUERY_LEN+INSERT_QUERY));
	query = malloc((int)(QUERY_LEN+INSERT_QUERY));
	if(query==NULL)
	{
			popup(NULL,"Erro de memoria");
			autologger("Erro de memoria");
			return 1;
	}
	g_print("iniciando concluir_ter()\n");
	
	if(alterando==0)
	{
		sprintf(query,
		"insert into terceiros(razao,doc,tipo_doc,tipoc,tipo,endereco,celular,contatoc,telefone,contatot,email,contatoe,obs) values('%s','%s',%i,'%s',%i,'%s','%s','%s','%s','%s','%s','%s','%s');",	
		nomes_ter,doc_ter,tipo_doc,tipo_ter,terci_tipo,endereco_ter,/*cep,*/celular_ter,contatoc_ter,telefone_ter,contatot_ter,email_ter,contatoe_ter,observacoes_ter);	
	}
	else
	{
		sprintf(query,"update terceiros set razao = '%s', doc = '%s', tipo_doc = %i, tipoc = '%s', tipo = %i,telefone = '%s',contatot = '%s',celular = '%s',contatoc = '%s', email = '%s',obs = '%s' where code = %s;"
		,nomes_ter,doc_ter,tipo_doc,tipo_ter,terci_tipo,telefone_ter,contatot_ter,celular_ter,contatoc_ter,email_ter,observacoes_ter,codigos_ter);	
	}
	g_print("[...] Criando conexão com o banco\n\n");
	MYSQL connect;
	mysql_init(&connect);
	g_print("[...] Tentando conexão com o banco\n\n");
	if(mysql_real_connect(&connect,"localhost",USER,PASS,"erp",0,NULL,0))
	{
		g_print("[!] conectado ao banco com sucesso\n\n");
	}
	else
	{
		popup(NULL,"Algum erro no servidor\nLigue para suporte");
		
		g_print("[!] Erro ao tentar se conectar %s\n",mysql_error(&connect));
		autologger("[!] Erro ao tentar se conectar\n");
		autologger((char*)mysql_error(&connect));
		return 1;
	}	
	if(stoi(codigos_ter)==-1)
	{
		if(strlen(codigos_ter)>8)
		{
			g_print("Codigo terceiro muito grande %s\n",codigos_ter);
			autologger("Codigo terceiro muito grande %s");
			popup(NULL,"O código do terceiro deve ser menor\n");
			return -1;
		}
		else
		{
			g_print("Codigo do terceiro incorreto %s\n",codigos_ter);
			popup(NULL,"Codigo terceiro deve ser numérico\nPor favor corrija");
			gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
			return 1;
		}
	}
	g_print("%s\n",query);
	autologger(query);
	err = mysql_query(&connect,query);
	if(err!=0)
	{
		g_print("Query para tabela terceiros\n");
		autologger("Query para tabela terceiros");
		g_print("codigo do erro %i\n",err);
		g_print("%s\n",mysql_error(&connect));
		g_print("%s\n\n",query);
		autologger(query);
		gtk_button_set_label(GTK_BUTTON(botao),"erro");
		popup(NULL,(gchar*)mysql_error(&connect));
		return 1;
	}
	else
	{
		autologger(query);
		g_print("Query para tabela terceiros\n");
		g_print("Query envida com sucesso\n");
		sprintf(query,"select code from terceiros where code = '%s'",codigos_ter);
		resultado = consultar(query);
		campos = mysql_fetch_row(resultado);
		if(campos!=NULL)
		{
			autologger(query);
			g_print("Query envida com sucesso\n");
			gtk_button_set_label(GTK_BUTTON(botao),"concluido");
			popup(NULL,"Concluido");
			gtk_label_set_text(GTK_LABEL(acao_atual2),"Cadastrando");
			alterar=0;
			code[0] = '\0';
			sprintf(code,"%i",tasker("terceiros"));
			gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(celular_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(email_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),"");
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
			gtk_text_buffer_get_start_iter (buffer,&inicio);
			gtk_text_buffer_get_end_iter (buffer,&fim);
			gtk_text_buffer_delete (buffer,&inicio,&fim);	
			gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),FALSE);		
		}
		else
		{
			popup(NULL,"O cadastro nao foi feito\nverifique os campos");
			autologger("O cadastro nao foi feito\nverifique os campos");
		}
	}
	
	printf("finalizando conclui_ter()\n");
	autologger("O cadastro nao foi feito\nverifique os campos");
//	gtk_widget_grab_focus (GTK_WIDGET(name_ter_field));
	return 0;
}
