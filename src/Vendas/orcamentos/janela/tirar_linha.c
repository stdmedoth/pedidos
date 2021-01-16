int tirar_linha(int id_ponteiro)
{

	file_logger("Removendo linha do Orçamento tirar_linha()...");
	if(ativos[id_ponteiro].id == 1){
			gtk_grid_remove_row(GTK_GRID(orc_prods_grid),id_ponteiro);
	}

	ativos[id_ponteiro].id = 0;
	excluidos[id_ponteiro].id = 1;
	find_subgrupos_restrict->posicao = 0;

	ativos_qnt--;

	if(ativos_qnt>1)
	{
		gtk_widget_set_sensitive(cliente_orc_entry,FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
	}

	return 0;
}

static int remover_linha_orc(GtkWidget *widget,int id_ponteiro)
{
	int erro;
	char *query;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	query = malloc(MAX_QUERY_LEN);

	sprintf(query,"select * from Produto_Orcamento where code = %s and item = %i",codigo_orc_gchar,id_ponteiro);

	vetor = consultar(query);
	if(vetor!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos!=NULL)
		{
			sprintf(query,"delete from Produto_Orcamento where code = %s and item = %i",codigo_orc_gchar,id_ponteiro);
			erro = enviar_query(query);
			if(erro!=0)
			{
				popup(NULL,"Erro ao tentar excluir o item");
				return 1;
			}
		}
	}

	if(ativos[id_ponteiro].id == 1){
		gtk_grid_remove_row(GTK_GRID(orc_prods_grid),id_ponteiro);
	}
	ativos[id_ponteiro].id = 0;
	excluidos[id_ponteiro].id = 1;
	find_subgrupos_restrict->posicao = 0;
	ativos_qnt--;

	if(ativos_qnt>1)
	{
		gtk_widget_set_sensitive(cliente_orc_entry,FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
	}

	cont=1;
	for(int pos=1;pos<=MAX_PROD_ORC;pos++)
	{
		if(ativos[pos].id == 1){
			gtk_widget_set_sensitive(botao_menos[pos],TRUE);
			cont = pos;
		}
	}
	if(cont<MAX_PROD_ORC)
		gtk_widget_set_sensitive(botao_menos[cont],FALSE);

	return 0;
}
