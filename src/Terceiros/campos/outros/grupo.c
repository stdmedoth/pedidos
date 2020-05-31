int grupo_ter()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	grupos_ter = (gchar*) gtk_entry_get_text(GTK_ENTRY(subgrp_ter_field));
	if(strlen(grupos_ter)<=0)
	{
		if(terceiros.criticar.grupo==0)
		{
			
			return 0;	
		}
		popup(NULL,"Por favor, Insira um grupo para o produto"); 
		return 1;
	}
	else
	if(strlen(grupos_ter)>=MAX_GRP_LEN)
	{
		popup(NULL,"Código do grupo é muito grande");
		return 1;
	}
	sprintf(query,"select nome from grupos where code = '%s'",grupos_ter);
	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos==NULL)
		{
			popup(NULL,"Este código para grupo não existe\n\tUse a pesquisa");
			g_print("Esta código para grupo não existe:%s\n",grupos_ter);
			return 1;
		}
	}
	else
	{
		g_print("Erro no MYSQL_RES* para grupos\n");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(campo_nome_subgrp_ter),campos[0]);	
	g_print("grupo: %s\n",grupos_ter);
	if(concluindo_ter==0&&grupos_ter_load==0)
	{
		notebook_preco_ter_grupo();
		if(precos_cliente[1].ativo == 1)
		{
			gtk_widget_grab_focus(entry_preco_ter_grupo_prcvist[1]);
		}
	}

	return 0;

}
	
