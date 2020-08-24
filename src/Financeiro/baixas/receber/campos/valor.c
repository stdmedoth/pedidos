int cad_bxs_rec_vlr_fun(){

  MYSQL_RES *res,*res2;
  MYSQL_ROW row,row2;
  float valor, vlr_tit, baixados;
  char query[MAX_QUERY_LEN];

  cad_bxs_rec_valor_gchar = (gchar* ) gtk_entry_get_text(GTK_ENTRY(cad_bxs_rec_valor_entry));

  if(critica_real(cad_bxs_rec_valor_gchar,cad_bxs_rec_valor_entry))
    return 1;

  rec_baixas.valor = atof(cad_bxs_rec_valor_gchar);

  valor = atof(cad_bxs_rec_valor_gchar);

  sprintf(query,"select SUM(valor) from parcelas_tab where parcelas_id = %i",
  rec_baixas.titulo_code);

  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar existencia da parcela");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Não Há valores no título");
    return 1;
  }
  if(row[0]){
    vlr_tit = atof(row[0]);
    rec_baixas.valor_titulo = vlr_tit;
  }

  if(cad_bxs_rec_alterando){
    sprintf(query,"select SUM(valor) from baixas_titulos where parcelas_id = %i and posicao != %i",
    rec_baixas.titulo_code,
    rec_baixas.id);
  }else{
    sprintf(query,"select SUM(valor) from baixas_titulos where parcelas_id = %i",
    rec_baixas.titulo_code);
  }

  if(!(res2 = consultar(query))){
    popup(NULL,"Erro ao consultar valor das baixas");
    return 1;
  }

  if((row2 = mysql_fetch_row(res2))){
    if(row2[0]){

      rec_baixas.valor_baixas = atof(row2[0]);
      rec_baixas.valor_baixas += valor;
      if(rec_baixas.valor_titulo < valor+atof(row2[0])){
        popup(NULL,"Valor da baixa atual supera valor do título");
        return 1;
      }
    }else
    if(rec_baixas.valor_titulo < valor){
      popup(NULL,"Valor da baixa atual supera valor do título");
      return 1;
    }
  }

  gtk_widget_grab_focus(cad_bxs_rec_concluir_button);
  return 0;
}
