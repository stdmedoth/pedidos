int cad_relat_code()
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	char query[MAX_QUERY_LEN];
	
	cad_rel_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_rel_code_entry));
	if(strlen(cad_rel_code_gchar)<=0)
	{
		popup(NULL,"Insira o código do relatorio");
		gtk_widget_grab_focus(cad_rel_code_entry);
		return 1;
	}
	
	if(strlen(cad_rel_code_gchar)>=MAX_CODE_LEN)
	{
		popup(NULL,"Código do relatório excede limite");
		gtk_widget_grab_focus(cad_rel_code_entry);
		return 1;	
	}
	
	if(alterando_cad_rel==0&&concluindo_cad_rel==0)
	{
		sprintf(query,"select * from criador_relat where code = %s",cad_rel_code_gchar);
		if((res = consultar(query))==NULL)
			return 1;
		if((row = mysql_fetch_row(res))!=NULL)
		{
			cad_relat_alterar();
		}
	}
	
	relat_struct.codigo = atoi(cad_rel_code_gchar);
	
	gtk_widget_grab_focus(cad_rel_nome_entry);
	return 0;
}
