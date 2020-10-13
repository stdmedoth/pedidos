int cad_bxs_pag_concluir_fun(){

  char query[MAX_QUERY_LEN];
  cad_bxs_pag_concluindo = 1;

  if(cad_bxs_pag_tit_fun())
    return 1;

  if(cad_bxs_pag_parc_fun())
    return 1;

  if(cad_bxs_pag_id_fun())
    return 1;

  if(cad_bxs_pag_dtc_fun())
    return 1;

  if(cad_bxs_pag_vlr_fun())
    return 1;

  if(cad_bxs_pag_alterando == 0)
    sprintf(query,"insert into baixas_titulos(parcelas_id,posicao,id_baixa,data_criacao,valor) values(%i,%i,%i,STR_TO_DATE('%s','%%d/%%m/%%Y'),%s)",
    pag_baixas.titulo_code,
    pag_baixas.parcela,
    pag_baixas.id,
    pag_baixas.data,
    cad_bxs_pag_valor_gchar);
  else{
    sprintf(query,"update baixas_titulos set data_criacao = STR_TO_DATE('%s','%%d/%%m/%%Y'), valor = %s where parcelas_id = %i and posicao = %i and id_baixa = %i",
    pag_baixas.data,
    cad_bxs_pag_valor_gchar,
    pag_baixas.titulo_code,
    pag_baixas.parcela,
    pag_baixas.id);
  }

  if(enviar_query(query)){
      popup(NULL,"Não foi possível baixar parcela");
      return 1;
  }


  if(pag_baixas.valor_titulo==pag_baixas.valor_baixas){
    sprintf(query,"update titulos set status = %i where code = %i",STAT_QUITADO,pag_baixas.titulo_code);
  }else
  if(pag_baixas.valor_baixas>0){
    sprintf(query,"update titulos set status = %i where code = %i",STAT_PARC_BAIXA,pag_baixas.titulo_code);
  }
  else{
    sprintf(query,"update titulos set status = %i where code = %i",STAT_PENDENTE,pag_baixas.titulo_code);
  }
  if(enviar_query(query)){
      popup(NULL,"Não foi possível mudar status do título");
      return 1;
  }


  cad_bxs_pag_cancelar_fun();
  return 0;
}
