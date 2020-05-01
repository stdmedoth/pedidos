int fornecedor_prod()
{
	int err=0;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[100];
	fornecedores_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(fornecedor_prod_field));
	if(strlen(fornecedores_prod)>50)
	{
		popup(NULL,"Nome do fornecedor\n muito grande");
		gtk_widget_grab_focus(fornecedor_prod_field);
		vet_erro[FOR_ERR] = 1;
		return 1;
	}
	else
	if(strlen(fornecedores_prod)<=0)
	{
		if(produtos.criticar.fornecedor!=0)
		{
			gtk_widget_grab_focus(GTK_WIDGET(observacao_prod_field));
			vet_erro[FOR_ERR] = 0;
			return 0; 
		}
		popup(NULL,"Por favor, insira um Fornecedor");
		gtk_widget_grab_focus(fornecedor_prod_field);
		vet_erro[FOR_ERR] = 1;
		return 1;	
	}
	g_print("fornecedor: %s\n",fornecedores_prod);
	sprintf(query,"select * from terceiros where code = '%s'",fornecedores_prod);
	g_print("Query a ser enviada %s\n",query);
	g_print("estado da query %i\n",err);
	vetor = consultar(query); 
	campos = mysql_fetch_row(vetor);
	if(campos==NULL)
	{
		g_print("Fornecedor não existe ou o código esta incorreto\n");
		popup(NULL,"Fornecedor não existe ou o código esta incorreto");
		gtk_widget_grab_focus(fornecedor_prod_field);
		return 1;
	}
	g_print("codigo do fornecedor: %s\n",campos[0]);
	g_print("nome do fornecedor: %s\n",campos[1]);
	gtk_entry_set_text(GTK_ENTRY(campo_nome_fornecedor),campos[1]);
	fornecedores_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(fornecedor_prod_field));
	g_print("endereco do fornecedor: %s\n",campos[2]);
	g_print("tipo de fornecedor: %s\n",campos[3]);
	gtk_widget_grab_focus(fator_prod_field);
	vet_erro[FOR_ERR] = 0;
	return 0;
}
