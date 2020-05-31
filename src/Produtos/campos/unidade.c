int und_unt_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	unidades_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(unidade_prod_field));
	if(strlen(unidades_prod)<=0)
	{
		if(produtos.criticar.unidade==0)
		{
			gtk_widget_grab_focus(qnt_atacado_field);
			return 0;
		}
		g_print("Inserir uma unidade para o produto");
		popup(NULL,"Por favor, Insira uma unidade para o produto");
		gtk_widget_grab_focus(GTK_WIDGET(unidade_prod_field));
		return 1;
	}
	else
	if(strlen(unidades_prod)>=MAX_CODE_LEN)
	{
		g_print("Código muito grande inserido: %s\n",unidades_prod);
		popup(NULL,"Sigla muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(unidade_prod_field));
		return 1;
	}
	
	sprintf(query,"select nome from unidades where code = %s",unidades_prod);
	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos==NULL)
		{
			popup(NULL,"Esta unidade ainda não existe\nUse a pesquisa");
			g_print("Esta unidade ainda não existe\nUse a pesquisa :%s\n",unidades_prod);
			gtk_widget_grab_focus(GTK_WIDGET(unidade_prod_field));
			return 1;
		}
		gtk_entry_set_text(GTK_ENTRY(campo_nome_unidade),campos[0]);
	}
	else
	{
		g_print("Erro no MYSQL_RES* para unidades\n");
		return 1;
	}
	g_print("unidade: %s\n",unidades_prod);
	gtk_widget_grab_focus(GTK_WIDGET(qnt_atacado_field));
	return 0;
}

int und_atac_prod()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	unidades_atac_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_atacado_field));
	if(strlen(unidades_atac_prod)<=0)
	{
		if(produtos.criticar.unidade==0)
		{
			gtk_widget_grab_focus(grupo_prod_field);
			return 0;
		}
		g_print("Inserir uma unidade para o produto");
		popup(NULL,"Por favor, Insira uma unidade para o produto");
		gtk_widget_grab_focus(GTK_WIDGET(qnt_atacado_field));
		return 1;
	}
	else
	if(strlen(unidades_atac_prod)>=MAX_CODE_LEN)
	{
		g_print("Sigla muito grande inserida: %s\n",unidades_atac_prod);
		popup(NULL,"Sigla muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(qnt_atacado_field));
		return 1;
	}
	sprintf(query,"select nome from unidades where code = %s",unidades_atac_prod);
	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos==NULL)
		{
			popup(NULL,"Esta unidade ainda não existe\nUse a pesquisa");
			g_print("Esta unidade ainda não existe\nUse a pesquisa :%s\n",unidades_atac_prod);
			gtk_widget_grab_focus(GTK_WIDGET(qnt_atacado_field));
			return 1;
		}
		gtk_entry_set_text(GTK_ENTRY(campo_nome_qnt_atacado),campos[0]);
	}
	else
	{
		g_print("Erro no MYSQL_RES* para unidades\n");
		gtk_widget_grab_focus(GTK_WIDGET(qnt_atacado_field));
		return 1;
	}
	vet_erro[UND_ERR] = 0;
	g_print("unidade: %s\n",unidades_atac_prod);
	gtk_widget_grab_focus(GTK_WIDGET(grupo_prod_field));
	return 0;
}

