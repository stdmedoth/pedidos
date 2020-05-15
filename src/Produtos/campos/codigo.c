int code_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[MAX_QUERY_LEN];
	char code[10];
	codigos_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_prod_field));
	if(strlen(codigos_prod)<=0)
	{
		g_print("Inserir um código para o produto");
		popup(NULL,"Por favor, Insira um código para o produto");
		sprintf(code,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),code);
		return 1;
	}
	if(strlen(codigos_prod)>=MAX_CODE_LEN)
	{
		g_print("Código do produto muito grande");
		popup(NULL,"Por favor, Insira um código menor\n\tpara o produto");
		sprintf(code,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),code);
		return 1;
	}

	if(alterando_prod==0&&concluindo_prod==0)
	{
		sprintf(query,"select code from produtos where code = '%s'",codigos_prod);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			return 1;
		}
		if((campos = mysql_fetch_row(vetor))!=NULL)
		{
			altera_prod();
			return 0;
		}
	
	}
	if(stoi(codigos_prod)==-1)
	{
		if(strlen(codigos_prod)>8)
		{
			g_print("O codigo deve ser menor");
			popup(NULL,"O codigo deve ser menor");
			return 1;
		}
		else
		{
			g_print("Codigo do produto incorreto: %s\n",codigos_prod);
			popup(NULL,"O código do produto deve ser numérico\n");
			code[0] = '\0';
			sprintf(code,"%i",tasker("produtos"));
			gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),code);
			gtk_entry_set_text(GTK_ENTRY(nome_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(preco_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),"");
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
			gtk_text_buffer_get_start_iter (buffer,&inicio);
			gtk_text_buffer_get_end_iter (buffer,&fim);
			gtk_text_buffer_delete (buffer,&inicio,&fim);	
		}
		return 1;
	}

	g_print("codigo: %s\n",codigos_prod);
	gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
	return 0;
}

