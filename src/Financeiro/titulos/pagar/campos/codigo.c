int cad_pag_code_fun(){

	cad_pag_code_gchar = (gchar*  )gtk_entry_get_text(GTK_ENTRY(cad_pag_code_entry));

	if(!strlen(cad_pag_code_gchar)){
	popup(NULL,"Insira o código do título");
	return 1;
	}

	char query[MAX_QUERY_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;
	sprintf(query,"select tipo_titulo from titulos where code = %i",atoi(cad_pag_code_gchar));
	if(!(res=consultar(query))){
	  popup(NULL,"Erro ao confirmar existencia do título");
	  return 1;
	}

	if((row=mysql_fetch_row(res))){
	  if(atoi(row[0]) != TP_TIT_PAG){
	  	popup(NULL,"Selecione um Título a pagar");
	 	cad_pag_cancelar_fun();
	  	return 1;
	  }
	}

	gtk_widget_grab_focus(cad_pag_parcela_spin);
	return 0;
}
