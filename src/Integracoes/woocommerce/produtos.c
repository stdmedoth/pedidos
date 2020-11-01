struct _WC_Product *get_wc_produtos(){

  MYSQL_RES *res;
  MYSQL_ROW row;

  if(!(res = consultar(wp_all_prod_query))){
    popup(NULL,"Não foi possível consultar os produtos");
    return NULL;
  }

  while((row = mysql_fetch_row(res))){
    g_print("Id %s\n", row[0]);
    g_print("Nome %s\n", row[1]);
    g_print("Descricao %s\n", row[2]);
    g_print("Categoria %s\n", row[3]);
    g_print("SKU %s\n", row[4]);
    g_print("Preço %s\n", row[5]);
    g_print("Peso %s\n", row[6]);
    g_print("Estoque %s\n", row[7]);
  }

  return NULL;
}
