int est_said_produto_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_said_prod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_prod_entry));

	if(strlen(est_said_prod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_said_prod_entry);
		return 1;
	}

	sprintf(query,"select grupo , nome from produtos where code = %i",atoi(est_said_prod_gchar));

	if((vetor = consultar(query))!=NULL)
	{
		campo = mysql_fetch_row(vetor);
		if(campo==NULL)
		{
			popup(NULL,"Este código para produto não existe\n\tUse a pesquisa");
			return 1;
		}
	}
	else
	{
		g_print("Erro no MYSQL_RES* para produtos\n");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(est_said_campo_nome_prod),campo[1]);

	find_subgrupos_restrict->grupo = atoi(campo[0]);
	find_subgrupos_restrict->posicao = 0;
	find_subgrupos_restrict->entry = est_said_subgrp_entry;

	gtk_widget_grab_focus(est_said_subgrp_entry);

	return 0;
}
