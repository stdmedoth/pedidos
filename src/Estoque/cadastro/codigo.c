int est_cad_code()
{
	est_cad_cod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_cod_entry));

	if(!strlen(est_cad_cod_gchar)){
		popup(NULL,"Insira o código");
		est_cad_cancelar();
		return 1;
	}

	if(est_cad_alterando == 0){
		MYSQL_RES *res;
		MYSQL_ROW row;
		char query[MAX_QUERY_LEN];
		sprintf(query,"select * from estoques where code = %i",atoi(est_cad_cod_gchar));
		if((res = consultar(query))==NULL)
			return 1;

		if((row = mysql_fetch_row(res))!=NULL){
			est_cad_alterar();
		}
	}

	gtk_widget_grab_focus(est_nome_entry);
	return 0;
}
