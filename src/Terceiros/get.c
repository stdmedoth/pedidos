struct _terc_infos *terceiros_get_simp_terceiro(int code){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	struct _terc_infos *terceiros = malloc(sizeof(struct _terc_infos));
	terceiros->contatos = malloc(sizeof(struct _Contato)*MAX_CNTTS_QNT);

	sprintf(query,"select * from terceiros where code = %i", code);
	if(!(res = consultar(query))){
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_simp_terceiro() -> consultar()");
		return NULL;
	}

	if((row = mysql_fetch_row(res))){
		terceiros->code = atoi(row[COD_TER_COL]);
		terceiros->razao = strdup(row[RAZ_TER_COL]);
		terceiros->ie = strdup(row[IE_TER_COL]);
		terceiros->doc = strdup(row[IE_TER_COL]);
		terceiros->tipo_terc = atoi(row[TIPI_TER_COL]);
		terceiros->cep = strdup(row[CEP_TER_COL]);
		terceiros->i_nro = atoi(row[REND_TER_COL]);
		terceiros->c_nro = strdup(row[REND_TER_COL]);
	}else{
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_simp_terceiro() -> mysql_fetch_row() -> Infos Básicas");
		return NULL;
	}

	int contatos_qnt = 0;
	sprintf(query,"select * from contatos where terceiro = %i", code);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar contatos do terceiro");
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_simp_terceiro() -> consultar() -> Contatos");
		return NULL;
	}
	while((row = mysql_fetch_row(res))){
		terceiros->contatos[contatos_qnt].id = atoi(row[CTTO_ID_COL]);
		terceiros->contatos[contatos_qnt].nome = strdup(row[CTTO_NOME_COL]);
		terceiros->contatos[contatos_qnt].celular = strdup(row[CTTO_CEL_COL]);
		terceiros->contatos[contatos_qnt].telefone = strdup(row[CTTO_TEL_COL]);
		terceiros->contatos[contatos_qnt].email = strdup(row[CTTO_EMAIL_COL]);
		contatos_qnt++;
	}
	terceiros->contatos_qnt = contatos_qnt;
	return terceiros;
}



struct _terc_infos *terceiros_get_terceiro(int code){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	struct _terc_infos *terceiros = malloc(sizeof(struct _terc_infos));
	terceiros->contatos = malloc(sizeof(struct _Contato)*MAX_CNTTS_QNT);

	sprintf(query,"select * from terceiros where code = %i", code);
	if(!(res = consultar(query))){
	 file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_terceiro() -> consultar() -> Infos Básicas");
	 return NULL;
	}

	if((row = mysql_fetch_row(res))){
		terceiros->code = atoi(row[COD_TER_COL]);
		terceiros->razao = strdup(row[RAZ_TER_COL]);
		terceiros->ie = strdup(row[IE_TER_COL]);
		terceiros->doc = strdup(row[IE_TER_COL]);
		terceiros->tipo_terc = atoi(row[TIPI_TER_COL]);
		terceiros->cep = strdup(row[CEP_TER_COL]);
		terceiros->i_nro = atoi(row[REND_TER_COL]);
		terceiros->c_nro = strdup(row[REND_TER_COL]);
	}else{
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_terceiro() -> mysql_fetch_row() -> Infos Básicas");
		return NULL;
	}

	sprintf(query,"select * from logradouro where CEP = '%s'", terceiros->cep);
	if(!(res = consultar(query))){
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_terceiro() -> consultar() -> Endereço");
		return NULL;
  }

	if((row = mysql_fetch_row(res))){
		terceiros->xLgr = strdup(row[CEP_DESCR_COL]);
		terceiros->xCpl = strdup(row[CEP_COMPLEM_COL]);
		terceiros->xBairro = strdup(row[CEP_DESCR_BAIRRO]);
		terceiros->xMun = strdup(row[CEP_DESCRCID_COL]);
		terceiros->UF = strdup(row[CEP_UF_COL]);
	}else{
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_terceiro() -> mysql_fetch_row() -> Endereço");
		return NULL;
	}

	int contatos_qnt = 0;
	sprintf(query,"select * from contatos where terceiro = %i", code);
	if(!(res = consultar(query))){
		file_logger("Estrutura de Cliente/Fornecedor não criada! terceiros_get_terceiro() -> consultar() -> Contatos");
		return NULL;
	}
	while((row = mysql_fetch_row(res))){
		terceiros->contatos[contatos_qnt].id = atoi(row[CTTO_ID_COL]);
		terceiros->contatos[contatos_qnt].nome = strdup(row[CTTO_NOME_COL]);
		terceiros->contatos[contatos_qnt].celular = strdup(row[CTTO_CEL_COL]);
		terceiros->contatos[contatos_qnt].telefone = strdup(row[CTTO_TEL_COL]);
		terceiros->contatos[contatos_qnt].email = strdup(row[CTTO_EMAIL_COL]);
		contatos_qnt++;
	}
	terceiros->contatos_qnt = contatos_qnt;
	return terceiros;
}
