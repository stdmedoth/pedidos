int orcamentos_get_orc_itens_qnt(int orc_code){
  MYSQL_RES *res;
  char *query = malloc(MAX_QUERY_LEN);
  sprintf(query,"select * from Produto_Orcamento where code = %i",orc_code);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar itens do orçamento");
    autologger(query);
    return 0;
  }
  return mysql_num_rows(res);
}

struct _orc *rec_orc_infos(struct _orc *orc){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);

  if(!orc)
    orc = malloc(sizeof(struct _orc));

  carregar_navimps();

	if(!imps_qnt && !navs_qnt){
		popup(NULL,"Não há impressoras ou navegadores configurados!");
		return NULL;
	}

  sprintf(query,"select * from orcamentos where code = %i",orc->infos.code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		return NULL;
	}
  if(!(row = mysql_fetch_row(res)))
  {
    popup(NULL,"Orcamento não existe");
    return NULL;
  }

  //informações basicas
  orc->infos.code = atoi(row[ORC_COD_COL]);
  orc->infos.tipo_mov = atoi(row[ORC_TIPMOV_COL]);
  //orc.infos.vendedor = atoi(row[ORC_VENDD_COL]);
  orc->infos.cliente = atoi(row[ORC_CLI_COL]);
  orc->infos.data = strdup(row[ORC_DATE_COL]);
  orc->infos.total = atoi(row[ORC_TOTAL_COL]);

  //informações financeiras
  orc->parcelas.condpag.code = atoi(row[ORC_PAGCOND_COL]);
  orc->parcelas.banco = atoi(row[ORC_BANC_COL]);
  orc->parcelas.total_geral = atoi(row[ORC_TOTAL_COL]);

  sprintf(query,"select * from pag_cond where code = %i",orc->parcelas.condpag.code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar condição de pagamento");
		autologger("Erro na query para buscar condição de pagamento\n");
		autologger(query);
		return NULL;
	}
  if(!(row = mysql_fetch_row(res)))
  {
    popup(NULL,"Condição de pagamento não existe");
    return NULL;
  }

  if(row[PAGCND_TIP_COL])
    orc->parcelas.condpag.tipo_parc = atoi(row[PAGCND_TIP_COL]);
  else{
    file_logger("Tipo de parcela nulo");
    return NULL;
  }
  if(row[PAGCND_DIAFLAG_COL])
    orc->parcelas.condpag.dia_inicial_flag = atoi(row[PAGCND_DIAFLAG_COL]);
  else{
    file_logger("Tipo de parcela nulo");
    return NULL;
  }
  if(row[PAGCND_DIA_COL])
    orc->parcelas.condpag.dia_inicial = atoi(row[PAGCND_DIA_COL]);
  else{
    file_logger("Tipo de parcela nulo");
    return NULL;
  }
  if(row[PAGCND_INT_COL])
    orc->parcelas.condpag.intervalos = atoi(row[PAGCND_INT_COL]);
  else{
    file_logger("Tipo de parcela nulo");
    return NULL;
  }
  if(row[PAGCOND_QNT_COL])
    orc->parcelas.condpag.parcelas_qnt = atoi(row[PAGCOND_QNT_COL]);
  else{
    file_logger("Tipo de parcela nulo");
    return NULL;
  }

  sprintf(query,"select t.razao, st.cep_entrega, st.num_entrega, st.vlr_frete, st.valor_desconto_frete, st.observacoes_entrega from servico_transporte as st inner join terceiros as t on st.transportador = t.code where orcamento = %i", orc_infos.code);
  if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao buscar existencia de transporte");
		autologger("Erro na query para buscar existencia de transporte\n");
		autologger(query);
		return NULL;
	}

  if((row = mysql_fetch_row(res)))
  {
    if(row[TRANSP_CODE_COL])
      orc->entrega.code = atoi(row[TRANSP_CODE_COL]);
    if(row[TRANSP_TRSP_COL])
    	orc->entrega.transportador = atoi(row[TRANSP_TRSP_COL]);
    if(row[TRANSP_CLI_COL])
    	orc->entrega.cliente = atoi(row[TRANSP_CLI_COL]);
    if(row[TRANSP_CEP1_COL])
    	strcpy(orc->entrega.cep_inicio,row[TRANSP_CEP1_COL]);
    if(row[TRANSP_CEP2_COL])
    	strcpy(orc->entrega.cep_entrega,row[TRANSP_CEP2_COL]);
    if(row[TRANSP_NUM_COL])
    	orc->entrega.num = atoi(row[TRANSP_NUM_COL]);
    if(row[TRANSP_ORC_COL])
    	orc->entrega.orcamento = atoi(row[TRANSP_ORC_COL]);
    if(row[TRANP_VLR_COL])
    	orc->entrega.vlr = atof(row[TRANP_VLR_COL]);
    if(row[TRANP_VLR_DESC_COL])
    	orc->entrega.vlr_desc = atof(row[TRANP_VLR_DESC_COL]);
    if(row[TRANP_OBS_COL])
    	strcpy(orc->entrega.obs,row[TRANP_OBS_COL]);
  }

  return orc;
}
