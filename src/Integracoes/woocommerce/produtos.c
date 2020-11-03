struct _WC_Product **get_wc_produtos(){

  MYSQL_RES *res;
  MYSQL_ROW row;


  if(!(res = consultar(wp_all_prod_query))){
    popup(NULL,"Não foi possível consultar os produtos");
    return NULL;
  }
  int cont=0;
  int prod_qnt = mysql_num_rows(res);
  struct _WC_Product **ProdutosPtr = malloc(sizeof(struct _WC_Product)*prod_qnt);
  while((row = mysql_fetch_row(res))){
    static struct _WC_Product produtos;
    ProdutosPtr[cont] = &produtos;
    produtos.ID = atoi(row[0]);
    produtos.nome = strdup(row[1]);
    produtos.descricao = strdup(row[2]);
    produtos.Category =  strdup(row[3]);
    produtos.SKU = strdup(row[4]);
    produtos.Price = atof(row[5]);
    produtos.Weight = atof(row[6]);
    produtos.Stock = atof(row[7]);
    cont++;
  }

  return ProdutosPtr;
}


int enviar_wc_produtos(struct _WC_Product **produtos){


  return 0;
}
