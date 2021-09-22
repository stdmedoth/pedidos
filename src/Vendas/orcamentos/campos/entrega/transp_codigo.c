int orc_transp_codigo_fun()
{
	char code[10];
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	transp_verified=1;

	orc_transp_codigo = (gchar *) gtk_entry_get_text(GTK_ENTRY(orc_transp_codigo_entry));

	if(strlen(orc_transp_codigo)<=0){
		popup(NULL,"Código do transportador deve ser inserido");
		return 1;
	}

	if(!concluindo_orc){
		sprintf(query,"select * from terceiros where code = %s",orc_transp_codigo);
		if(!(res = consultar(query))){
			popup(NULL,"Verifique query de transportador com suporte");
			return 1;
		}
		if(!(row = mysql_fetch_row(res))){
			popup(NULL,"Nenhum transportador para o código indicado");
			return 1;
		}

		if(row[RAZ_TER_COL])
			gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),row[RAZ_TER_COL]);
		if(row[DOC_TER_COL])
			gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),row[DOC_TER_COL]);
		if(row[IE_TER_COL])
			gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),row[IE_TER_COL]);
	}

	gtk_widget_grab_focus(orc_transp_nome_entry);
	return 0;
}
