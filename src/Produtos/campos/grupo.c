int grupo_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	grupos_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(grupo_prod_field));
	if(strlen(grupos_prod)<=0&&criticar.grupo==1)
	{
		popup(NULL,"Por favor, Insira um grupo para o produto");
		return 1;
	}
	else
	if(strlen(grupos_prod)>=MAX_GRP_LEN)
	{
		popup(NULL,"Código do grupo é muito grande");
		vet_erro[GRP_ERR] = 1;
		return 1;
	}
	sprintf(query,"select nome from grupos where code = '%s'",grupos_prod);
	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos==NULL)
		{
			popup(NULL,"Este código para grupo não existe\n\tUse a pesquisa");
			g_print("Esta código para grupo não existe:%s\n",grupos_prod);
			vet_erro[GRP_ERR] = 1;
			return 1;
		}
	}
	else
	{
		g_print("Erro no MYSQL_RES* para grupos\n");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(campo_nome_grupo),campos[0]);	
	vet_erro[GRP_ERR] = 0;
	g_print("grupo: %s\n",grupos_prod);
	gtk_widget_grab_focus(GTK_WIDGET(fornecedor_prod_field));
	return 0;

}
	
