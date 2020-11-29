struct _WC_Product **get_wc_produtos(){

  MYSQL_RES *res;
  MYSQL_ROW row;

  if(intgr_params_testar())
    return NULL;

  int err = mysql_query(&intgr_con,wp_all_prod_query);
	if(err!=0)
	{
		file_logger((char*)mysql_error(&intgr_con));
		file_logger(wp_all_prod_query);
		autologger((char*)mysql_error(&intgr_con));
		autologger(wp_all_prod_query);
		popup(NULL,"Erro de formato\n");
		return NULL;
	}
	res = mysql_store_result(&intgr_con);
	if(!res)
	{
    popup(NULL,"Não foi possível consultar os produtos");
    return NULL;
  }

  int cont=0;
  int prod_qnt = mysql_num_rows(res);
  struct _WC_Product **ProdutosPtr = malloc(sizeof(struct _WC_Product)*prod_qnt);
  while((row = mysql_fetch_row(res))){

    static struct _WC_Product produtos;
    ProdutosPtr[cont] = &produtos;

    if(row[0])
      produtos.ID = atoi(row[0]);
    if(row[1])
      produtos.nome = strdup(row[1]);
    if(row[2])
      produtos.descricao = strdup(row[2]);
    if(row[3])
      produtos.Category =  strdup(row[3]);
    if(row[4])
      produtos.SKU = strdup(row[4]);
    if(row[5])
      produtos.Price = atof(row[5]);
    if(row[6])
      produtos.Weight = atof(row[6]);
    if(row[7])
      produtos.Stock = atof(row[7]);
    cont++;
  }
  ProdutosPtr[cont] = NULL;
  if(!cont)
    return NULL;

  return ProdutosPtr;
}


int enviar_wc_produtos(struct _WC_Product **produtos){


  return 0;
}
