int check_tables(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	FILE *fp = fopen(DB_TABLES_LIST_FILE, "r");
	if(!fp){
		char url[strlen(PEDIDOS_APP_URL_FILES) + 200];
		sprintf(url, "%s/data/db_tables_list", PEDIDOS_APP_URL_FILES);
		if(download_from_to(url, DB_TABLES_LIST_FILE)){
			popup(NULL,"Não foi possível efetuar download da verificação de tabelas");
			return 1;
		}
		if(!(fp = fopen(DB_TABLES_LIST_FILE, "r"))){
			popup(NULL,"Ainda não foi possível abrir arquivo de verificação das tabelas");
			return 1;
		}
	}

	int pos_line = 0;
	size_t line_buf_size = 0;
	pedidos_db_tables = malloc(MAX_TABLE_LEN * MAX_TABLE_QNT);
	pedidos_db_tables[pos_line] = malloc(MAX_TABLE_LEN);
	sprintf(query, "SHOW TABLES");
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível verificar tabelas");
		return 1;
	}

	while((getline(&pedidos_db_tables[pos_line], &line_buf_size, fp))>0){
		if(!strcmp(pedidos_db_tables[pos_line], "\n")){
			continue;
		}
		remover_barra_n(pedidos_db_tables[pos_line]);

		int table_exists = 0;

		while((row = mysql_fetch_row(res))){
			if( !strcmp(lowernize(row[0]), lowernize(pedidos_db_tables[pos_line])) ){
				table_exists = 1;
			}
		}
		mysql_data_seek(res, 0);
		if(!table_exists){
			char msg[27 + strlen(pedidos_db_tables[pos_line])];
			sprintf(msg, "Tabela %s ausente no sistema!", pedidos_db_tables[pos_line]);
			popup(NULL,msg);
			return 1;
		}
		pos_line++;
		pedidos_db_tables[pos_line] = malloc(MAX_TABLE_LEN);
		pedidos_db_tables_qnt++;
	}

	return 0;
}
