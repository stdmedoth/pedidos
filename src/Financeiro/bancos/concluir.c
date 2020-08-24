int cad_bancos_concluir_fun(){

  char query[MAX_QUERY_LEN];
  cad_bancos_concluindo = 1;
  if(cad_bancos_code_fun())
    return 1;

  if(cad_bancos_nome_fun())
    return 1;

  if(cad_bancos_doc_fun())
    return 1;

  if(cad_bancos_usuario_fun())
    return 1;

  if(cad_bancos_conta_fun())
    return 1;

  if(cad_bancos_agencia_fun())
    return 1;

  if(cad_bancos_saldoini_fun())
    return 1;

  if(cad_bancos_tipoconta_fun())
    return 1;

  if(cad_bancos_saldoini_fun())
    return 1;

  if( cad_bancos_alterando ){
    sprintf(query,"update bancos set nome = '%s', conta = '%s', tipoconta = %i, agencia = '%s', nome_usuario = '%s', documento = '%s', saldo_inicial = '%s' where code = %s",
    cad_bancos_nome_gchar,
    cad_bancos_conta_gchar,
    cad_bancos_tipoconta_int,
    cad_bancos_agencia_gchar,
    cad_bancos_usuario_gchar,
    cad_bancos_doc_gchar,
    cad_bancos_saldoini_gchar,
    cad_bancos_code_gchar);
  }else{
    sprintf(query,"insert into bancos(code,nome,conta,tipoconta,agencia,nome_usuario,documento,saldo_inicial) values(%s,'%s','%s',%i,'%s','%s','%s','%s')",
    cad_bancos_code_gchar,
    cad_bancos_nome_gchar,
    cad_bancos_conta_gchar,
    cad_bancos_tipoconta_int,
    cad_bancos_agencia_gchar,
    cad_bancos_usuario_gchar,
    cad_bancos_doc_gchar,
    cad_bancos_saldoini_gchar);
  }
  if(enviar_query(query)){
    popup(NULL,"Houve erro ao enviar banco");
    return 1;
  }

  if( cad_bancos_alterando )
    popup(NULL,"Banco atualizado com sucesso");
  else
    popup(NULL,"Banco criado com sucesso");

  cad_bancos_cancelar_fun();
  return 0;
}
