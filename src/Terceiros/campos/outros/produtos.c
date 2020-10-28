int produto_ter()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	prods_ter = (gchar*) gtk_entry_get_text(GTK_ENTRY(prod_ter_field));

	if(strlen(prods_ter)<=0)
	{
		popup(NULL,"Por favor, Insira produto que deseja vincular");
		gtk_widget_grab_focus(prod_ter_field);
		return 1;
	}
	else
	if(strlen(prods_ter)>=MAX_GRP_LEN)
	{
		popup(NULL,"Código do produto é muito grande");
		return 1;
	}

	sprintf(query,"select grupo , nome from produtos where code = '%s'",prods_ter);

	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos==NULL)
		{
			popup(NULL,"Este código para produto não existe\n\tUse a pesquisa");
			g_print("Esta código para produto não existe:%s\n",prods_ter);
			return 1;
		}
	}
	else
	{
		g_print("Erro no MYSQL_RES* para produtos\n");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(campo_nome_prod_ter),campos[1]);

	gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_prcfat),"");
	gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_prcvist),"");

	gtk_widget_grab_focus(entry_preco_ter_prcfat);

	return 0;

}
