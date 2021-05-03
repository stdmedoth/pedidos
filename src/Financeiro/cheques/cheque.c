struct _cheque *cheque_get_simple_cheque(int cheque_code){

	MYSQL_ROW row;
	MYSQL_RES *res;
	char query[MAX_QUERY_LEN];

	sprintf(query, "select *, DATE_FORMAT(data_emissao, '%%d/%%m/%%Y') from cheque where code = %i", cheque_code);
	if(!(res = consultar(query))){
		return NULL;
	}

	if(!(row = mysql_fetch_row(res))){
		return NULL;
	}

	struct _cheque *cheque = malloc(sizeof(struct _cheque));

	cheque->code = atoi(row[CHEQUE_CODE_COL]);
	
	struct _banco *banco = malloc(sizeof(struct _banco ));
	banco->code = atoi(row[CHEQUE_BNC_COL]);
	cheque->banco = banco;
	
	cheque->conta = strdup(row[CHEQUE_CONTA_COL]);
	cheque->serie = strdup(row[CHEQUE_SERIE_COL]);
	cheque->numero = strdup(row[CHEQUE_NUM_COL]);
	
	struct _terc_infos *pagante = malloc(sizeof(struct _terc_infos));
	pagante->code = atoi(row[CHEQUE_PAGNT_COL]);
	cheque->pagante = pagante;
	
	cheque->data_emissao = strdup(row[CHEQUE_NUM_ROWS]);
	cheque->valor = atof(row[CHEQUE_VLR_COL]);
	return cheque;
}

struct _cheque *cheque_get_cheque(int cheque_code){

	MYSQL_ROW row;
	MYSQL_RES *res;
	char query[MAX_QUERY_LEN];

	sprintf(query, "select * from cheque where code = %i", cheque_code);
	if(!(res = consultar(query))){
		return NULL;
	}

	if(!(row = mysql_fetch_row(res))){
		return NULL;
	}

	struct _cheque *cheque = malloc(sizeof(struct _cheque));
	cheque->code = atoi(row[CHEQUE_CODE_COL]);
	
	cheque->banco = get_banco(atoi(row[CHEQUE_BNC_COL]));
	if(!cheque->banco)
		return NULL;

	cheque->conta = strdup(row[CHEQUE_CONTA_COL]);
	cheque->serie = strdup(row[CHEQUE_SERIE_COL]);
	cheque->numero = strdup(row[CHEQUE_NUM_COL]);
	cheque->pagante = terceiros_get_simp_terceiro(atoi(row[CHEQUE_PAGNT_COL]));
	cheque->data_emissao = strdup(row[CHEQUE_DT_EMSSAO_COL]);
	cheque->valor = atof(row[CHEQUE_VLR_COL]);
	return cheque;
}