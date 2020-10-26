int calcula_saldo(){
  char query[MAX_QUERY_LEN],valor[MAX_PRECO_LEN*2];
  MYSQL_RES *estado;
	MYSQL_ROW campo;

  if(est_sald_est()){
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(est_sld_prod_entry),"");

  sprintf(query,"select SUM(entradas) - SUM(saidas),(select date_format(data_mov,'%cd/%cm/%cY') from movimento_estoque order by data_mov desc limit 1) from movimento_estoque where produto = %s and subgrupo = %s and estoque = %i",
  37,37,37,
  est_sld_prod_cod_gchar,
  est_sld_subgrp_cod_gchar,
  est_sld_prod_est_int);

  if(!(estado = consultar(query))){
    popup(NULL,"Erro ao consultar saldo");
    return 1;
  }

  if((campo = mysql_fetch_row(estado))==NULL)
  {
    popup(NULL,"O produto está sem saldo no estoque");
    gtk_entry_set_text(GTK_ENTRY(est_sld_prod_entry),"");
    gtk_entry_set_text(GTK_ENTRY(est_sld_data_entry),"");
    return 1;
  }
  if(campo[0]){
    sprintf(valor,"%.3f",atof(campo[0]));
    gtk_entry_set_text(GTK_ENTRY(est_sld_prod_entry),valor);
    gtk_entry_set_text(GTK_ENTRY(est_sld_data_entry),campo[1]);
  }
  else
  {
    popup(NULL,"O produto nunca foi movimentado");
    return 1;
  }

  sprintf(query,"select saldo_min from saldo_min_grupo where produto = %i and grupo = %i",atoi(est_sld_prod_cod_gchar),atoi(est_sld_subgrp_cod_gchar));
  if(!(estado = consultar(query))){
    return 1;
  }
  if((campo = mysql_fetch_row(estado))){
    sprintf(valor,"%.3f",atof(campo[0]));
    gtk_entry_set_text(GTK_ENTRY(est_sld_min_entry),valor);
  }else{
    sprintf(valor,"%.3f",atof("0"));
    gtk_entry_set_text(GTK_ENTRY(est_sld_min_entry),valor);
  }
  return 0;
}
