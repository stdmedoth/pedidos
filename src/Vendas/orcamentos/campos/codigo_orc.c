int codigo_orc()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[MAX_QUERY_LEN];

	codigo_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_orc_entry));
	if(strlen(codigo_orc_gchar)<=0){
		popup(NULL,"O código do orcamento deve ser inserido");
		gtk_widget_grab_focus(codigo_orc_entry);
		return 1;
	}

	if(stoi(codigo_orc_gchar)==-1)
	{
		popup(NULL,"O código do orcamento deve ser numérico");
		gtk_widget_grab_focus(codigo_orc_entry);
		return 1;
	}

	if( !alterando_orc && !concluindo_orc && !copiando_orc && !excluindo_orc ){
		sprintf(query,"select code from orcamentos where code = '%s'",codigo_orc_gchar);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			return 1;
		}

		if((campos = mysql_fetch_row(vetor))!=NULL){
			altera_orc();
		}
	}
	if(cliente_orc_gchar && strlen(cliente_orc_gchar)){
		for(int cont=1;cont<=MAX_PROD_ORC;cont++){
			if(ativos[cont].id){
				gtk_widget_grab_focus(codigo_prod_orc_entry[cont]);
				return 0;
			}
		}	
	}else{
		gtk_widget_grab_focus(cliente_orc_entry);
	}
	

	return 0;
}
