struct _orc *rec_orc_infos(int orc_code){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  struct _orc *orc = malloc(sizeof(struct _orc));

  sprintf(query,"select * from orcamentos where code = %i",orc_code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		vet_erro[COD_ERR] = 0;
		gtk_widget_grab_focus(codigo_orc_entry);
		return NULL;
	}
  if(!(row = mysql_fetch_row(res)))
  {
    popup(NULL,"Orcamento não existe");
    return NULL;
  }
  //informações basicas
  orc->infos.code = atoi(row[ORC_COD_COL]);
  orc->infos.cliente_code = atoi(row[ORC_TIPMOV_COL]);
  //orc.infos.vendedor = atoi(row[ORC_VENDD_COL]);
  orc->infos.cliente_code = atoi(row[ORC_CLI__COL]);
  strcpy(orc->infos.data,row[ORC_DATE_COL]);
  orc->infos.total = atoi(row[ORC_TOTAL_COL]);

  //informações financeiras
  orc->parcelas.pagcond_code = atoi(row[ORC_PAGCOND_COL]);
  orc->parcelas.banco = atoi(row[ORC_BANC_COL]);
  orc->parcelas.total_geral = atoi(row[ORC_TOTAL_COL]);

  sprintf(query,"select * from pag_cond where code = %i",orc->parcelas.pagcond_code);
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
  orc->parcelas.parcelas_qnt = atoi(row[PAGCOND_QNT_COL]);

  return 0;
}
