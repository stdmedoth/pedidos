int concluido_prod()
{
	g_print("Iniciando concluido_prod()\n");
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
		sprintf(query,"insert into produtos(code,name,price,supplier) values('%s','%s','%s','%s');",codigos_prod,nomes_prod,preco_prod,fornecedor_prod);
		resultado = consultar(query);
		if(stoi(codigos_prod)==-1)
		{
			if(strlen(codigos_prod)>8)
			{
				g_print("O codigo deve ser menor");
				popup(NULL,"O codigo deve ser menor");
				
			}
			else
			{
				g_print("Codigo do produto incorreto: %s\n",codigos_prod);
				popup(NULL,"O código do produto deve ser numérico\n");
				code[0] = '\0';
				sprintf(code,"%i",tasker("produtos"));
				gtk_entry_set_text(GTK_ENTRY(code_field),code);
				gtk_entry_set_text(GTK_ENTRY(name_field),"");
				gtk_entry_set_text(GTK_ENTRY(price_field),"");
				gtk_entry_set_text(GTK_ENTRY(supp_field),"");
				gtk_entry_set_text(GTK_ENTRY(und_field),"");
			}			return -1;
		}
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

