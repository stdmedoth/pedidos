int cad_bxs_pag_parc_fun(){

  MYSQL_RES *res,*res2;
  MYSQL_ROW row,row2;
  char query[MAX_QUERY_LEN];
  char float_text[MAX_PRECO_LEN];

  cad_bxs_pag_parcela_gchar = (gchar* ) gtk_entry_get_text(GTK_ENTRY(cad_bxs_pag_parcela_spin));
  pag_baixas.parcela = atoi(cad_bxs_pag_parcela_gchar);

  sprintf(query,"select DATE_FORMAT(data_vencimento,'%%d/%%m/%%Y'),valor from parcelas_tab where parcelas_id = %i and posicao = %i",
  pag_baixas.titulo_code,
  pag_baixas.parcela);

  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar existencia da parcela");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Parcela não existe para ser baixada");
    return 1;
  }

  sprintf(query,"select SUM(valor) from baixas_titulos where parcelas_id = %i and posicao = %i",
  pag_baixas.titulo_code,
  pag_baixas.parcela);

  if(!(res2 = consultar(query))){
    popup(NULL,"Erro ao consultar valor das baixas");
    return 1;
  }

  if((row2 = mysql_fetch_row(res2))){
    if(row2[0])
      pag_baixas.valor_baixas = atof(row2[0]);
    else
      pag_baixas.valor_baixas = 0;
  }else
    pag_baixas.valor_baixas = 0;

  pag_baixas.abaixar = atof(row[1]) - pag_baixas.valor_baixas;

  sprintf(float_text,"%.2f",pag_baixas.abaixar);
  if(!cad_bxs_pag_alterando && !cad_bxs_pag_concluindo){
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),"");
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_valor_entry),"");
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datavencimento_entry),row[0]);
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_parcvalor_entry),row[1]);
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_bxrvalor_entry),float_text);
  }

  gtk_widget_grab_focus(cad_bxs_pag_code_id_spin);
  return 0;
}
