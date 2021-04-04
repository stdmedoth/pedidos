int pag_excluir_fun(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	pag_cod_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(pag_cod_entry));
  if(strlen(pag_cod_gchar)<=0){
    popup(NULL,"O código deve ser inserido");
    return 1;
  }
 
  sprintf(query,"select * from pag_cond where code = %s",pag_cod_gchar);
  if(!(res = consultar(query))){
  	popup(NULL,"Não foi possível consultar existencia");
  	return 1;
  }
  if(!mysql_num_rows(res)){
  	popup(NULL,"Condição não existe para ser excluida");
  	return 1;
  }

	sprintf(query,"delete from pag_cond where code = %s",pag_cod_gchar);
	if(enviar_query(query)){
		popup(NULL,"Não foi possível deletar");
		return 1;
	}

	popup(NULL,"Excluido com sucesso");
	pag_cancelar_fun();
	return 0;
}
