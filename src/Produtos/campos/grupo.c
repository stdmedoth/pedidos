int grupo_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	grupos_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(grupo_prod_field));
	if(strlen(grupos_prod)<=0)
	{
		if(produtos.criticar.grupo==0)
		{
			gtk_widget_grab_focus(fornecedor_prod_field);
			return 0;
		}
		popup(NULL,"Por favor, Insira um grupo para o produto");
		return 1;
	}
	else
	if(strlen(grupos_prod)>=MAX_GRP_LEN)
	{
		popup(NULL,"Código do grupo é muito grande");
		return 1;
	}
	sprintf(query,"select nome from grupos where code = '%s'",grupos_prod);
	if(!(vetor = consultar(query)))
		return 1;
	if((campos = mysql_fetch_row(vetor))==NULL)
	{
		popup(NULL,"Este código para grupo não existe\n\tUse a pesquisa");
		g_print("Esta código para grupo não existe:%s\n",grupos_prod);
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(campo_nome_grupo),campos[0]);

	g_print("grupo: %s\n",grupos_prod);

	if(concluindo_prod==0)
	{
		notebook_preco_grupo();
		if(precos_produtos[1].ativo==1)
			if(GTK_IS_WIDGET(entry_preco_grupo_prcvist[1]))
				gtk_widget_grab_focus(entry_preco_grupo_prcvist[1]);
	}


	return 0;

}
