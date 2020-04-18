int conclui_ter(GtkWidget* nome, gpointer *botao)
{
	
	int err;
	char *code;
	code = malloc(10);
	char *query;
	int cont;
	if(code_terc()!=0)
	{
		gtk_widget_grab_focus(code_ter_field);
		return 1;	
	}
	if(name_terc()!=0)
	{
		gtk_widget_grab_focus(name_ter_field);
		return 1;
	}
	if(escolha_doc()!=0)
	{
		gtk_widget_grab_focus(doc_combo);
		return 1;
	}
	
	if(cep_terc()!=0)
	{
		gtk_widget_grab_focus(cep_ter_field);
		return 1;
	}
	if(address_terc()!=0)
	{
		gtk_widget_grab_focus(address_ter_field);
		return 1;
	}
	if(cel()!=0)
	{
		gtk_widget_grab_focus(celular_ter_field);
		return 1;
	}
	if(tel()!=0)
	{
		gtk_widget_grab_focus(telefone_ter_field);
		return 1;
	}
	
	if(contc()!=0)
	{
		gtk_widget_grab_focus(contatoc_ter_field);
		return 1;
	}
	if(contt()!=0)
	{
		gtk_widget_grab_focus(contatot_ter_field);
		return 1;
	}
	if(email_fun()!=0)
	{
		gtk_widget_grab_focus(email_ter_field);
		return 1;
	}
	if(contato_email()!=0)
	{
		gtk_widget_grab_focus(contatoe_ter_field);
		return 1;
	}
	if(prazo_fun()!=0)
	{
		gtk_widget_grab_focus(prazo_ter_field);
		return 1;
	}
	if(obs()!=0)
	{
		gtk_widget_grab_focus(observacoes_ter_field);
		return 1;
	}
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
	tipo_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(type_ter_field));
	g_print("alocando memoria para query %i\n",(int)(QUERY_LEN+INSERT_QUERY));
	query = malloc((int)(QUERY_LEN+INSERT_QUERY));
	if(query==NULL)
	{
			popup(NULL,"Erro de memoria");
			autologger("Erro de memoria");
			return 1;
	}
	g_print("iniciando concluir_ter()\n");
	
	if(alterando_ter==0)
	{
		sprintf(query,CAD_QUERY_TER,CAD_QUERY_TER_VAR);	
	}
	else
	{
		sprintf(query,UPDATE_QUERY_TER,UPDATE_QUERY_TER_VAR);
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
	g_print("Query para tabela terceiros\n");
	g_print("Query envida com sucesso\n");
	gtk_button_set_label(GTK_BUTTON(botao),"concluido");
	popup(NULL,"Concluido");
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Cadastrando");
	alterando_ter=0;
	code[0] = '\0';
	sprintf(code,"%i",tasker("terceiros"));
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
	gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(cep_ter_field),"");
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

	printf("finalizando conclui_ter()\n");
	autologger("O cadastro nao foi feito\nverifique os campos");
//	gtk_widget_grab_focus (GTK_WIDGET(name_ter_field));
	return 0;
}
