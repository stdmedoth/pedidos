int und_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	unidades_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(unidade_prod_field));
	if(strlen(unidades_prod)<=0&&criticar.unidade==1)
	{
		g_print("Inserir uma unidade para o produto");
		popup(NULL,"Por favor, Insira uma unidade para o produto");
		return 1;
	}
	else
	if(strlen(unidades_prod)>=MAX_UND_LEN)
	{
		g_print("Sigla muito grande inserida: %s\n",unidades_prod);
		popup(NULL,"Sigla muito grande");
		vet_erro[UND_ERR] = 1;
		return 1;
	}
	sprintf(query,"select code from unidades where sigla = '%s'",unidades_prod);
	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos==NULL)
		{
			popup(NULL,"Esta sigla ainda não existe\nUse a pesquisa");
			g_print("Esta sigla ainda não existe\nUse a pesquisa :%s\n",unidades_prod);
			vet_erro[UND_ERR] = 1;
			return 1;
		}
	}
	else
	{
		g_print("Erro no MYSQL_RES* para unidades\n");
		return 1;
	}
	vet_erro[UND_ERR] = 0;
	g_print("unidade: %s\n",unidades_prod);
	gtk_widget_grab_focus(GTK_WIDGET(grupo_prod_field));
	return 0;
}


