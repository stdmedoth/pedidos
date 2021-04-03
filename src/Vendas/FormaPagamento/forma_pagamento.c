
struct _forma_pagamento *get_forma_pagamento(int code_fp){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	sprintf(query, "select * from forma_pagamento where id = %i", code_fp);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar forma pagamento");
		return NULL;
	}

	if(!(row = mysql_fetch_row(res))){
		file_logger(" get_forma_pagamento -> !mysql_fetch_row()");
		return NULL;
	}

	struct _forma_pagamento *forma_pagamento = malloc(sizeof(struct _forma_pagamento));
	forma_pagamento->code = atoi(row[FORMA_PAG_CODE]);
	forma_pagamento->nome = strdup(row[FORMA_PAG_NOME]);

	return forma_pagamento;
}