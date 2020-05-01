int code_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
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
	sprintf(query,"select code from produtos where code = '%s'",codigos_prod);
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
	if(alterando_prod==0)
	{
		if((vetor = consultar(query))!=NULL)
		{
			campos = mysql_fetch_row(vetor);
			if(campos!=NULL)
			{
				popup(NULL,"Este código ja foi incluído\nPor favor tente com o próximo");
				g_print("Código ja foi incluído\n");
				g_print("%s\n",campos[0]);
				vet_erro[COD_ERR] = 1;
				return 1;
			}
		}
	}
	vet_erro[COD_ERR] = 0;
	g_print("codigo: %s\n",codigos_prod);
	gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
	return 0;
}

