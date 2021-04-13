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



struct _forma_pagamento_list *get_formas_pags_list(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	sprintf(query, "select * from forma_pagamento");
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar forma pagamento");
		return NULL;
	}
	int fpg_num_rows = mysql_num_rows(res);
	if(!fpg_num_rows){
		return NULL;
	}

	int fpg_qnt=0;
	struct _forma_pagamento_list *fpg_list = malloc( sizeof(struct _forma_pagamento_list *));
	
	fpg_list->fpags = malloc( sizeof(struct _forma_pagamento *) *fpg_num_rows);
	fpg_list->qnt_fpags = 0;

	while((row = mysql_fetch_row(res))){
		if(fpg_list->qnt_fpags >= MAX_FORMPG_CAD){
			return fpg_list;
		}	
		fpg_list->fpags[fpg_list->qnt_fpags] = malloc(sizeof(struct _forma_pagamento));
		fpg_list->fpags[fpg_list->qnt_fpags]->code = atoi(row[FORMA_PAG_CODE]);
		fpg_list->fpags[fpg_list->qnt_fpags]->nome = strdup(row[FORMA_PAG_NOME]);		
		fpg_list->qnt_fpags++;
	}

	return fpg_list;
}