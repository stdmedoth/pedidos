int relat_prod_codigo_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int cont=0;

	relat_prod_codigo_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(relat_prod_code_entry));

	if(strlen(relat_prod_codigo_gchar)<=0)
	{
		popup(NULL,"Insira o código do relatório");
		return 1;
	}

	sprintf(query,"select nome from criador_relat where code = %s",relat_prod_codigo_gchar);
	if((res = consultar(query))==NULL)
	{
		popup(NULL,"Erro ao buscar nome do relatorio");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Relatório não existente");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(relat_prod_nome_entry),row[0]);

	sprintf(query,"select b.nome, b.query from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s",relat_prod_codigo_gchar);

	if((res = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber nome dos campos do relatorio");
		return 1;
	}



	if(relat_prod_gerando==0){
		gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(relat_prod_ordem_combo));
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_prod_ordem_combo),"Selecionar Ordem");
		gtk_combo_box_set_active(GTK_COMBO_BOX(relat_prod_ordem_combo),0);
		while((row = mysql_fetch_row(res))!=NULL){

			if(cont>MAX_RELAT_CAMPOS)
				break;

			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_prod_ordem_combo),row[0]);
			strcpy(campos_query[cont],row[1]);
			cont++;

		}
	}

	return 0;
}
