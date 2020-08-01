int orc_transp_concluir_fun(){
  char query[MAX_QUERY_LEN];

  if(codigo_orc())
    return 1;

  if(codigo_cli_orc())
    return 1;

  if(orc_transp_codigo_fun())
    return 1;

  if(orc_transp_cepc())
    return 1;

  if(orc_transp_logr_fun())
    return 1;

  if(orc_transp_estado_fun())
    return 1;

  if(orc_transp_cidadec())
    return 1;

  if(orc_transp_bairroc())
    return 1;

  if(alterando_orc==0){
    sprintf(query,"insert into servico_transporte(transportador,cliente,cep_inicio,cep_entrega,num_entrega,orcamento,vlr_frete,observacoes_entrega) values('%i','%i','%s','%s','%i','%i','%s','%s')",
    atoi(orc_transp_codigo),
    atoi(cliente_orc_gchar),
    cad_emp_strc.cep,
    orc_transp_cep,
    atoi(orc_transp_num),
    atoi(codigo_orc_gchar),
    "0.0",
    "");
  }else{
    sprintf(query,"update servico_transporte set transportador = '%i', cliente = '%i', cep_inicio = '%s', cep_entrega = '%s', num_entrega = '%i', vlr_frete = '%s', observacoes_entrega = '%s' where orcamento = %i",
    atoi(orc_transp_codigo),
    atoi(cliente_orc_gchar),
    cad_emp_strc.cep,
    orc_transp_cep,
    atoi(orc_transp_num),
    "0.0",
    "",
    atoi(codigo_orc_gchar));
  }
  if(enviar_query(query)){
    popup(NULL,"Erro ao enviar dados de transporte");
    return 1;
  }

  return 0;
}
