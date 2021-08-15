int criar_terceiro_importador(char *razao){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	if(!razao){
		razao = strdup(TERCEIRO_IMPORTADOR_RAZAO);
	}
	sprintf(query, "INSERT INTO terceiros(razao, ie, uf) values('%s', '', '')", razao);
	if(enviar_query(query)){
		popup(NULL, "Não foi possível cadastrar terceiros importador");
		return 0;
	}

	return mysql_insert_id(&conectar);
}
