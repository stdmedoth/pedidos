int orc_transp_concluir_fun(){
  char query[MAX_QUERY_LEN];

  if(orc_transp_codigo_fun())
    return 1;

  if(orc_transp_cepc())
    return 1;

  if(orc_transp_logr_fun())
    return 1;

  if( orc_transp_num_fun())
    return 1;

  if(orc_transp_estado_fun())
    return 1;

  if(orc_transp_cidadec())
    return 1;

  if(orc_transp_bairroc())
    return 1;

  if(orc_transp_valor_frete())
    return 1;

  if(orc_transp_desconto_frete())
    return 1;

  if(alterando_transp==0){
    sprintf(query,"insert into servico_transporte(transportador,cliente,cep_inicio,cep_entrega,num_entrega,orcamento,vlr_frete,valor_desconto_frete,frete_pago, observacoes_entrega) values('%i','%i','%s','%s','%i','%i','%s','%s',%i,'%s')",
    atoi(orc_transp_codigo),
    atoi(cliente_orc_gchar),
    cad_emp_strc.CEP,
    orc_transp_cep,
    atoi(orc_transp_num),
    atoi(codigo_orc_gchar),
    orc_transp_valor,
    orc_transp_desconto,
    orc_transp_frete_pago_int,
    " ");
  }else{
    sprintf(query,"update servico_transporte set transportador = '%i', cliente = '%i', cep_inicio = '%s', cep_entrega = '%s', num_entrega = '%i', vlr_frete = '%s', valor_desconto_frete = '%s', frete_pago = %i , observacoes_entrega = '%s' where orcamento = %i",
    atoi(orc_transp_codigo),
    atoi(cliente_orc_gchar),
    cad_emp_strc.CEP,
    orc_transp_cep,
    atoi(orc_transp_num),
    orc_transp_valor,
    orc_transp_desconto,
    orc_transp_frete_pago_int,
    " ",
    atoi(codigo_orc_gchar));
  }

  if(enviar_query(query)){
    popup(NULL,"Erro ao enviar dados de transporte");
    return 1;
  }

  return 0;
}
