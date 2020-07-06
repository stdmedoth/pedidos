int est_ent_produto_fun()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *estado;
	MYSQL_ROW campo;

	est_ent_prod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_prod_entry));

	if(strlen(est_ent_prod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		est_ent_prod_gchar = malloc(MAX_CODE_LEN);
		strcpy(est_ent_prod_gchar,"");
		gtk_widget_grab_focus(est_ent_prod_entry);
		return 1;
	}

	sprintf(query,"select grupo , nome from produtos where code = %i",atoi(est_ent_prod_gchar));

	if((estado = consultar(query))==NULL){
		popup(NULL,"Erro ao buscar grupo padrao do produto");
		return 1;
	}

	if((campo = mysql_fetch_row(estado))==NULL){
		popup(NULL,"O Produto não existe");
		return 1;
	}


	find_subgrupos_restrict->grupo = atoi(campo[0]);
	find_subgrupos_restrict->posicao = 0;
	find_subgrupos_restrict->entry = est_ent_subgrp_entry;

	gtk_entry_set_text(GTK_ENTRY(est_ent_campo_nome_prod),campo[1]);


	gtk_widget_grab_focus(est_ent_subgrp_entry);

	return 0;
}
