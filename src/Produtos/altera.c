int conclui_alter_prod()
{
	g_print("Iniciando conclui_alter_prod()\n");
	MYSQL_ROW campos;
	MYSQL_RES *resultado;
	char query[100], code[20];
	if(strlen(codigos_prod)<1||
			strlen(nomes_prod)<1||
			strlen(preco_prod)<1||
			strlen(fornecedor_prod)<1||
			strlen(unidade_prod)<1)
	{
		code[0] = '\0';
		sprintf(code,"%i",tasker("produtos"));
		//gtk_entry_set_text(GTK_ENTRY(code_field),code);
		//gtk_entry_set_text(GTK_ENTRY(name_field),"");
		//gtk_entry_set_text(GTK_ENTRY(price_field),"");
		//gtk_entry_set_text(GTK_ENTRY(supp_field),"");
		gtk_widget_grab_focus(code_field);
		popup(NULL,"Voce deve preencher todos os campos");	
		return 1;
	}
	else
	if(codigos_prod_err!=1&&
			codigos_prod_err!=1&&
			nomes_prod_err!=1&&
			preco_prod_err!=1&&
			fornecedor_prod_err!=1&&
			unidade_prod_err!=1)
	{
		sprintf(query,"update table produtos set nome = '%s', preco = '%s', fornecedor = '%s',unidade = '%s';",
		nomes_prod,preco_prod,fornecedor_prod,unidade_prod);
		resultado = consultar(query);
		sprintf(query,"select code from produtos where code = '%s'",codigos_prod);
		resultado = consultar(query);
		campos = mysql_fetch_row(resultado);
		if(campos!=NULL)
		{
			autologger(query);
			printf("Query envida com sucesso\n");
			gtk_button_set_label(GTK_BUTTON(concluir),"concluido");
			popup(NULL,"Concluido");
			code[0] = '\0';
			sprintf(code,"%i",tasker("produtos"));
			gtk_entry_set_text(GTK_ENTRY(code_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_field),"");
			gtk_entry_set_text(GTK_ENTRY(price_field),"");
			gtk_entry_set_text(GTK_ENTRY(supp_field),"");
			gtk_entry_set_text(GTK_ENTRY(und_field),"");
		//	gtk_widget_grab_focus (GTK_WIDGET(name_field));
		//	gtk_widget_destroy(janela);
		}
		else
		{
			popup(NULL,"O cadastro nao foi feito\nverifique os campos");
		}
	}
	return 0;
}
	
int altera_prod()
{
	char task[10];
	char query[100];
	gchar *cod_delel,*nome_delel;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_field));
	nome_delel = (gchar *)gtk_entry_get_text(GTK_ENTRY(name_field));
	sprintf(query,"select * from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		g_print("produto não existe para ser alterado\n");
		popup(NULL,"Produto não existe");
		sprintf(task,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(code_field),task);
		gtk_entry_set_text(GTK_ENTRY(name_field),"");
		gtk_entry_set_text(GTK_ENTRY(price_field),"");
		gtk_entry_set_text(GTK_ENTRY(supp_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_field));
		tipo_ter = NULL;
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(code_field),campo[0]);
	code_prod();
	gtk_entry_set_text(GTK_ENTRY(name_field),campo[1]);
	name_prod();
	gtk_entry_set_text(GTK_ENTRY(price_field),campo[2]);
	price_prod();
	gtk_entry_set_text(GTK_ENTRY(supp_field),campo[3]);
	supp_prod();
	sprintf(query,"update produtos set name = "" where code = '%s' or name = '%s';",cod_delel,nome_delel);
	autologger("Alterou o produto abaixo");
	autologger(query);
	autologger(campo[0]);
	autologger(campo[1]);
	autologger(campo[2]);
	autologger(campo[3]);
	consultar(query);
	query[0] = '\0';
	sprintf(query,"select * from produtos where code = '%s' or name = '%s';",cod_delel,nome_delel);
	estado = consultar(query);
	campo = mysql_fetch_row(estado);
	if(campo!=NULL)
	{
		popup(NULL,"Não será possivel alterar");
		return 1;
	}
	else
	{
		autologger("Alterado com sucesso");
	}
	//tipo_ter = NULL;
	return 0;
}

