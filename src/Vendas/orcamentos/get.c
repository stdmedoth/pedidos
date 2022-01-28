struct _orc_valores *orc_get_valores(struct _orc *orc){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	struct _orc_valores *valores = malloc(sizeof(struct _orc_valores));
	struct _orc_itens **itens = NULL;

	int itens_qnt = orc_get_itens_qnt(orc->infos->code);
	if(!itens_qnt){
		file_logger("Orçamento não recebeu itens em orc_get_valores() -> orc_get_itens_qnt()");
	}
	itens = orc_get_itens(orc);
	if(!itens){
		file_logger("Estrutura de valores do orçamento não criada!  orc_get_valores() -> orc_get_itens()");
		return NULL;
	}
	valores->valor_prds = 0;
	valores->valor_prds_desc = 0;
	valores->valor_prds_liquido = 0;

	valores->valor_frete = 0;
	valores->desconto_frete = 0;
	valores->valor_frete_liquido = 0;

	valores->valor_total = 0;
	valores->desconto_total = 0;

	for(int cont=0;cont<itens_qnt; cont++){
		valores->valor_prds += itens[cont]->preco_f * itens[cont]->qnt_f;
		valores->valor_prds_desc += itens[cont]->desconto_f;
	}

	valores->valor_prds_liquido = valores->valor_prds - valores->valor_prds_desc;

	if(orc->entrega){
		valores->valor_frete = orc->entrega->vlr;
		valores->desconto_frete = orc->entrega->vlr_desc;
		valores->valor_frete_liquido = valores->valor_frete - valores->desconto_frete;
	}

	valores->valor_total = valores->valor_prds + valores->valor_frete;
	valores->desconto_total = valores->valor_prds_desc + valores->desconto_frete;

	valores->valor_total_liquido = valores->valor_total - valores->desconto_total;
	return valores;
}

struct _orc_parcelas *orc_get_parcelas(struct _orc *orc){

	struct _orc_parcelas *parcelas = malloc(sizeof(struct _orc_parcelas));

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int itens_qnt = orc_get_itens_qnt(orc->infos->code);

	enum{
		PAG_COND,
		FORM_PAG
	};
	sprintf(query, "select pag_cond, forma_pagamento from orcamentos where code = %i", orc->infos->code);

	if(!(res = consultar(query))){
		file_logger("Estrutura de parcelas do orçamento não criada! consultar() em orc_get_parcelas()");
		return NULL;
	}
	if(!(row = mysql_fetch_row(res))){
		file_logger("Estrutura de parcelas do orçamento não criada! mysql_fetch_row() em orc_get_parcelas()");
		return NULL;
	}

	parcelas->condpag = cond_pag_get(atoi(row[PAG_COND]));
	if(!parcelas->condpag){
		file_logger("Estrutura de condição de pagamento do orçamento não criada! cond_pag_get() em orc_get_parcelas()");
		return NULL;
	}
	parcelas->parcelas_qnt = parcelas->condpag->parcelas_qnt;
	char **datas = cond_pag_get_datas(parcelas->condpag, orc->infos->data);
	if(!datas){
		file_logger("Estrutura de condição de pagamento do orçamento não criada! cond_pag_get_datas() em orc_get_parcelas()");
		return NULL;
	}
	for(int cont=0;cont<parcelas->condpag->parcelas_qnt; cont++){
			parcelas->datas[cont] = strdup(datas[cont]);
	}

	float *vlrs = cond_pag_get_valores(parcelas->condpag, orc->valores->valor_total );
	if(!vlrs){
		file_logger("Estrutura de condição de pagamento do orçamento não criada! cond_pag_get_valores() em orc_get_parcelas()");
		return NULL;
	}
	for(int cont=0;cont<parcelas->condpag->parcelas_qnt; cont++){
			parcelas->vlrs[cont] = vlrs[cont];
	}

	if(row[FORM_PAG]){
		parcelas->forma_pagamento = get_forma_pagamento(atoi(row[1]));
		if(!parcelas->forma_pagamento){
			file_logger("Estrutura de valores em get_forma_pagamento(orc) retornada nula");
			return NULL;
		}
	}else{
		parcelas->forma_pagamento = NULL;
	}



	return parcelas;
}

struct _transporte *orc_get_entrega(struct _orc *orc){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	struct _transporte *entrega = malloc(sizeof(struct _transporte));

	sprintf(query, "select * from servico_transporte where orcamento = %i", orc->infos->code);
	if(!(res = consultar(query))){
		file_logger("Estrutura de entrega do orçamento não criada! consultar() em orc_get_entrega()");
		return NULL;
	}
	if(!(row = mysql_fetch_row(res))){
		file_logger("Estrutura de entrega do orçamento não criada! mysql_fetch_row() em orc_get_entrega()");
		return NULL;
	}

	entrega->code = atoi(row[TRSP_CODE_COL]);
	entrega->transportador = terceiros_get_simp_terceiro(atoi(row[TRSP_TRANSP_COL]));
	if(!entrega->transportador){
		file_logger("terceiros_get_simp_terceiro() em orc_get_entrega()");
		return NULL;
	}
	entrega->cliente = terceiros_get_simp_terceiro(atoi(row[TRSP_CLI_COL]));
	if(!entrega->transportador){
		file_logger("terceiros_get_simp_terceiro() em orc_get_entrega()");
		return NULL;
	}
	entrega->cep_inicio = strdup(row[TRSP_CEPINI_COL]);
	entrega->cep_entrega = strdup(row[TRSP_CEPFIM_COL]);
	entrega->num = atoi(row[TRSP_NUM_COL]);
	entrega->orcamento = atoi(row[TRSP_ORC_COL]);
	entrega->vlr = atof(row[TRSP_VLR_COL]);
	entrega->vlr_desc = atof(row[TRSP_DESC_COL]);
	entrega->obs = strdup(row[TRSP_OBS_COL]);

	return entrega;
}

struct _orc_itens **orc_get_itens(struct _orc *orc){

	struct _orc_itens **itens = malloc(sizeof(struct _orc_itens *) * MAX_PROD_ORC);

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int cont=0;
	sprintf(query, "select * from produto_orcamento where code = %i", orc->infos->code);
	if(!(res = consultar(query))){
		file_logger("Estrutura de do orçamento não criada! consultar() em orc_get_itens()");
		return NULL;
	}
	while((row = mysql_fetch_row(res))){
		itens[cont] = malloc(sizeof(struct _orc_itens));
		itens[cont]->id = atoi(row[ORC_PROD_COD_COL]);
		itens[cont]->item  = atoi(row[ORC_PROD_ITM_COL]);
		itens[cont]->produto  = atoi(row[ORC_PROD_PROD_COL]);
		itens[cont]->qnt_f  = atof(row[ORC_PROD_UND_COL]);
		itens[cont]->preco_f  = atof(row[ORC_PROD_VLR_COL]);
		itens[cont]->origem_preco  = atoi(row[ORC_PROD_VLR_ORIG_COL]);
		itens[cont]->tipodesc  = atoi(row[ORC_PROD_TIP_DESC_COL]);
		itens[cont]->desconto_f  = atof(row[ORC_PROD_DESC_COL]);
		itens[cont]->total_f  = atof(row[ORC_PROD_TOTAL_COL]);
		itens[cont]->observacao = strdup(row[ORC_PROD_OBS_COL]);

		itens[cont]->_produto = get_cad_prod(atoi(row[ORC_PROD_PROD_COL]));
		if(!itens[cont]->_produto){
			file_logger("Estrutura de do produto não criada! get_cad_prod() em orc_get_itens()");
			return NULL;
		}
		cont++;
	}


	return itens;
}

int orc_get_itens_qnt(int orc_code){
	int itens_qnt=0;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int cont=0;
	sprintf(query, "select * from produto_orcamento where code = %i", orc_code);
	if(!(res = consultar(query))){
		return 0;
	}
	itens_qnt = mysql_num_rows(res);

	return itens_qnt;
}

struct _orc *orc_get_orc(int orc_code){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	struct _orc *orc = malloc(sizeof(struct _orc));
	orc->infos = NULL;
	orc->itens = NULL;
	orc->entrega = NULL;
	orc->valores = NULL;

	sprintf(query, "select * from orcamentos where code = %i", orc_code);
	if(!(res = consultar(query))){
		file_logger("Erro ao consultar query de orçamento");
		return NULL;
	}
	if(!(row = mysql_fetch_row(res))){
		file_logger("Orçamento não encontrado");
		return NULL;
	}

	orc->infos = malloc(sizeof(struct _orc_infos));
	orc->infos->code = atoi(row[ORC_COD_COL]);
	orc->infos->tipo_mov = atoi(row[ORC_TIPMOV_COL]);
	//orc->infos->vendedor = terceiros_get_terceiro(atoi(row[ORC_VENDD_COL]));
	//if(!orc->infos->vendedor)
	//	return NULL;

	orc->infos->cliente = terceiros_get_terceiro(atoi(row[ORC_CLI_COL]));
	if(!orc->infos->cliente)
		return NULL;

	gchar *formated_date = get_db_formated_date(row[ORC_DATE_COL]);
	if(!formated_date){
		file_logger("Erro ao formatar data");
		return NULL;
	}
	orc->infos->data = strdup(formated_date);

	if(row[ORC_CHEQUE_COL]){
		orc->infos->cheque = cheque_get_simple_cheque(atoi(row[ORC_CHEQUE_COL]));
	}else{
		orc->infos->cheque = NULL;
	}

	orc->infos->total = atof(row[ORC_TOTAL_COL]);
	orc->infos->observacoes = strdup(row[ORC_OBS_COL]);

	orc->itens_qnt = orc_get_itens_qnt(orc->infos->code);
	orc->itens = orc_get_itens(orc);
	if(!orc->itens){
		file_logger("Estrutura de itens em orc_get_itens(orc) retornada nula");
		return NULL;
	}
	orc->entrega = orc_get_entrega(orc);

	orc->valores = orc_get_valores(orc);
	if(!orc->valores){
		file_logger("Estrutura de valores em orc_get_valores(orc) retornada nula");
		return NULL;
	}

	orc->parcelas = orc_get_parcelas(orc);
	if(!orc->parcelas){
		file_logger("Estrutura de valores em orc_get_parcelas(orc) retornada nula");
		return NULL;
	}

	return orc;
}
