int est_sld_min_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  int status=0;
  est_sld_min_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(est_sld_min_entry));
  sprintf(query,"select saldo_min from saldo_min_grupo where produto = %i and grupo = %i and estoque = %i",
  atoi(est_sld_prod_cod_gchar),
  atoi(est_sld_subgrp_cod_gchar),
  est_sld_prod_est_int);
  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao consultar existencia de saldo mínimo");
    return 1;
  }
  if((row = mysql_fetch_row(res))!=NULL){
    sprintf(query,"update saldo_min_grupo set saldo_min = '%s' where produto = %i and grupo = %i and estoque = %i",
    est_sld_min_gchar,
    atoi(est_sld_prod_cod_gchar),
    atoi(est_sld_subgrp_cod_gchar),
    est_sld_prod_est_int);
  }else{
    sprintf(query,"insert into saldo_min_grupo(produto,grupo,saldo_min,estoque) values(%i, %i, %s, %i)",
    atoi(est_sld_prod_cod_gchar),
    atoi(est_sld_subgrp_cod_gchar),
    est_sld_min_gchar,
    est_sld_prod_est_int);
  }

  if((status = enviar_query(query))!=0){
    popup(NULL,"Não foi possível atualizar saldo mínimo");
    return 1;
  }
  est_sld_prod_fun();
  est_sald_subgrp_fun();
  return 0;
}
