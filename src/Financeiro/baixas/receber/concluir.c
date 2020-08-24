int cad_bxs_rec_concluir_fun(){

  char query[MAX_QUERY_LEN];
  cad_bxs_rec_concluindo = 1;

  if(cad_bxs_rec_tit_fun())
    return 1;

  if(cad_bxs_rec_parc_fun())
    return 1;

  if(cad_bxs_rec_id_fun())
    return 1;

  if(cad_bxs_rec_dtc_fun())
    return 1;

  if(cad_bxs_rec_vlr_fun())
    return 1;

  if(cad_bxs_rec_alterando == 0)
    sprintf(query,"insert into baixas_titulos(parcelas_id,posicao,id_baixa,data_criacao,valor) values(%i,%i,%i,STR_TO_DATE('%s','%%d/%%m/%%Y'),%s)",
    rec_baixas.titulo_code,
    rec_baixas.parcela,
    rec_baixas.id,
    rec_baixas.data,
    cad_bxs_rec_valor_gchar);
  else{
    sprintf(query,"update baixas_titulos set data_criacao = STR_TO_DATE('%s','%%d/%%m/%%Y'), valor = %s where parcelas_id = %i and posicao = %i and id_baixa = %i",
    rec_baixas.data,
    cad_bxs_rec_valor_gchar,
    rec_baixas.titulo_code,
    rec_baixas.parcela,
    rec_baixas.id);
  }

  if(enviar_query(query)){
      popup(NULL,"Não foi possível baixar parcela");
      return 1;
  }


  if(rec_baixas.valor_titulo==rec_baixas.valor_baixas){
    sprintf(query,"update titulos set status = %i where code = %i",STAT_QUITADO,rec_baixas.titulo_code);
  }else
  if(rec_baixas.valor_baixas>0){
    sprintf(query,"update titulos set status = %i where code = %i",STAT_PARC_BAIXA,rec_baixas.titulo_code);
  }
  else{
    sprintf(query,"update titulos set status = %i where code = %i",STAT_PENDENTE,rec_baixas.titulo_code);
  }
  if(enviar_query(query)){
      popup(NULL,"Não foi possível mudar status do título");
      return 1;
  }


  cad_bxs_rec_cancelar_fun();
  return 0;
}
