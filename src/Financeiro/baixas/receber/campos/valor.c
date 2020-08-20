int cad_bxs_rec_vlr_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  float valor, vlr_tit, baixados;
  char query[MAX_QUERY_LEN];

  cad_bxs_rec_valor_gchar = (gchar* ) gtk_entry_get_text(GTK_ENTRY(cad_bxs_rec_valor_entry));

//  if(critica_real(cad_bxs_rec_valor_gchar,cad_bxs_rec_valor_entry))
//    return 1;

  rec_baixas.valor = atof(cad_bxs_rec_valor_gchar);

  valor = atof(cad_bxs_rec_valor_gchar);

  sprintf(query,"select SUM(valor) + %.2f from baixas_titulos where parcelas_id = %i and posicao != %i",
  valor,
  rec_baixas.titulo_code,
  rec_baixas.id);

  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar valor das baixas");
    return 1;
  }

  if((row = mysql_fetch_row(res))){
    if(row[0])
      baixados = atof(row[0]);
    else
      baixados = valor;
  }

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

  if(row[0])
    vlr_tit = atof(row[0]);

  if(baixados>vlr_tit){
    popup(NULL,"O valor da baixa supera o valor à receber");
    return 1;
  }

  gtk_widget_grab_focus(cad_bxs_rec_concluir_button);
  return 0;
}
