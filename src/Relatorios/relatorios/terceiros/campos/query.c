int relat_ter_query_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int campos_qnt=0;
	char ini_query[] = "select";
	char end_query[MAX_QUERY_LEN];
	char query[MAX_QUERY_LEN];
	char campo_query_cp[MAX_QUERY_ELM_LEN];
	sprintf(query,"select b.query,t.inner_query from criador_relat as a inner join relat_tab_campos as b inner join relat_tabelas_id as t on a.campos = b.code and a.tabela = t.code where a.code = %s",relat_ter_codigo_gchar);
	
	if((res = consultar(query))==NULL){
		popup(NULL,"Não foi possivel receber campos do relatorio");
		return 1;
	}
	
	while((row = mysql_fetch_row(res))!=NULL){
		
		if(campos_qnt==0)
			sprintf(ter_query.campos," %s,",row[0]);
		else
		{
			sprintf(ter_query.campos," %s %s,",campo_query_cp,row[0]);
		}
		
		strcpy(campo_query_cp,ter_query.campos); 
		
		strcpy(ter_query.campo_query[campos_qnt],row[0]);
		
		g_print("%s\n",ter_query.campo_query[campos_qnt]);
		sprintf(end_query,"%s",row[1]);
		campos_qnt++;
	}
	
	ter_query.campos_qnt = campos_qnt;

	ter_query.campos[strlen(ter_query.campos)-1] = '\0';
	
	relat_ter_query_gchar = malloc(strlen(ini_query)+strlen(ter_query.campos)+strlen(end_query));
	sprintf(relat_ter_query_gchar,"%s%s%s",ini_query,ter_query.campos,end_query);
	gtk_entry_set_text(GTK_ENTRY(relat_ter_query_entry),relat_ter_query_gchar);
	gtk_widget_set_sensitive(relat_ter_query_entry,TRUE);
	
	return 0;
}
