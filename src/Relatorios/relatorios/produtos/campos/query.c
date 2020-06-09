int relat_prod_query_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int campos_qnt=0;
	char ini_query[] = "select";
	char end_query[] = " from produtos as p inner join unidades as u inner join grupos as g inner join terceiros as t on p.fornecedor = t.code and p.grupo = g.code and p.unidades = u.code";
	char query[MAX_QUERY_LEN];
	char campo_query_cp[MAX_QUERY_ELM_LEN];
	sprintf(query,"select b.query from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s",relat_prod_codigo_gchar);
	
	if((res = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber campos do relatorio");
		return 1;
	}
	
	while((row = mysql_fetch_row(res))!=NULL){
		
		if(campos_qnt==0)
			sprintf(prod_query.campos,"%s, ",row[0]);
		else
		{
			sprintf(prod_query.campos," %s %s,",campo_query_cp,row[0]);//backup + campo novo
		}
		
		strcpy(campo_query_cp,prod_query.campos); //pega backup query
		
		strcpy(prod_query.campo_query[campos_qnt],row[0]);
		
		g_print("%s\n",prod_query.campo_query[campos_qnt]);
		campos_qnt++;
	}
	prod_query.campos_qnt = campos_qnt;

	prod_query.campos[strlen(prod_query.campos)-1] = '\0';
	relat_prod_query_gchar = malloc(strlen(ini_query)+strlen(prod_query.campos)+strlen(end_query));
	sprintf(relat_prod_query_gchar,"%s%s%s",ini_query,prod_query.campos,end_query);
	gtk_entry_set_text(GTK_ENTRY(relat_prod_query_entry),relat_prod_query_gchar);
	return 0;
}
