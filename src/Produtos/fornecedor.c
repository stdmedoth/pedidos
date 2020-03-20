int supp_prod()
{
	int err=0;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[100];
	fornecedor_prod = malloc(51);
	fornecedor_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(supp_field));
	if(strlen(fornecedor_prod)>50)
	{
		popup(NULL,"Nome do fornecedor\n muito grande");
		gtk_widget_grab_focus(supp_field);
		fornecedor_prod_err=1;
		return 1;
	}
	else
	if(strlen(fornecedor_prod)<1)
	{
		popup(NULL,"Por favor, insira um Fornecedor");
		gtk_widget_grab_focus(supp_field);
		fornecedor_prod_err=1;
		return 1;	
	}
	else
	{
		fornecedor_prod_err=0;
		gtk_widget_grab_focus(und_field);
	}
	g_print("fornecedor: %s\n",fornecedor_prod);
	sprintf(query,"select * from terceiros where name='%s' or code = '%s'",fornecedor_prod,fornecedor_prod);
	g_print("Query a ser enviada %s\n",query);
	g_print("estado da query %i\n",err);
	vetor = consultar(query); 
	campos = mysql_fetch_row(vetor);
	if(campos!=NULL)
	{
		g_print("codigo do fornecedor: %s\n",campos[0]);
		g_print("nome do fornecedor: %s\n",campos[1]);
		gtk_entry_set_text(GTK_ENTRY(supp_field),campos[1]);
		fornecedor_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(supp_field));
		g_print("endereco do fornecedor: %s\n",campos[2]);
		g_print("tipo de fornecedor: %s\n",campos[3]);
		fornecedor_prod_err=0;
		return 0;
	}
	else
	{
		if(strlen(fornecedor_prod)<1)
		{
			fornecedor_prod_err=1;
			return 1;
		}
		else
		{
			g_print("Fornecedor não existe ou o código esta incorreto\n");
			popup(NULL,"Fornecedor não existe ou o código esta incorreto");
			gtk_widget_grab_focus(supp_field);
			fornecedor_prod_err=1;
			return 1;
		}
	}
	return 0;
}
