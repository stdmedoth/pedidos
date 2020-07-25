int est_cad_alterar()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	est_cad_alterando = 1;
	sprintf(query,"select * from estoques");

	if((res = consultar(query))==NULL)
		return 1;

	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"Estoque não existente");
		return 1;
	}
	gtk_widget_set_sensitive(est_cod_entry,FALSE);
	gtk_widget_set_sensitive(est_alterar_button,FALSE);

	gtk_entry_set_text(GTK_ENTRY(est_nome_entry),row[1]);
	gtk_widget_grab_focus(est_nome_entry);
	return 0;
}
