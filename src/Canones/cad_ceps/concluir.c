int cad_ceps_concluir_fun(){

  char query[MAX_QUERY_LEN];
  if(cad_ceps_code_fun()!=0)
    return 1;

  if(cad_ceps_cep_fun()!=0)
    return 1;

  if(cad_ceps_descr_fun()!=0)
    return 1;

  if(cad_ceps_tipo_fun()!=0)
    return 1;

  if(cad_ceps_bairro_fun()!=0)
    return 1;

  if(cad_ceps_cid_code_fun()!=0)
    return 1;

  if(cad_ceps_uf_fun()!=0)
    return 1;

  if(cad_ceps_alterando==0){
    sprintf(query,"insert into logradouro(code, CEP, tipo, descricao, id_cidade, UF, complemento, descricao_sem_numero, descricao_cidade, codigo_cidade_ibge, descricao_bairro) values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
    cad_ceps_code_gchar,
    cad_ceps_cep_gchar,
    tip_logds[cad_ceps_tipo_int],
    cad_ceps_descr_gchar,
    cad_ceps_cid_code_gchar,
    uf_list[cad_ceps_uf_int],
    "","",
    cad_cid_descr_gchar,
    cad_cid_ibge_gchar,
    cad_ceps_bairro_gchar);
  }else{
    sprintf(query,"update logradouro set CEP = '%s', tipo = '%s', descricao = '%s', id_cidade = '%s', UF = '%s', complemento = '%s', descricao_sem_numero = '%s', descricao_cidade = '%s', codigo_cidade_ibge = '%s', descricao_bairro = '%s' where code = '%s'",
    cad_ceps_cep_gchar,
    tip_logds[cad_ceps_tipo_int],
    cad_ceps_descr_gchar,
    cad_ceps_cid_code_gchar,
    uf_list[cad_ceps_uf_int],
    "","",
    cad_cid_descr_gchar,
    cad_cid_ibge_gchar,
    cad_ceps_bairro_gchar,
    cad_ceps_code_gchar);
  }
  if(enviar_query(query)){
    popup(NULL,"Não foi possível enviar dados");
    return 1;
  }
  if(cad_ceps_alterando==0)
    popup(NULL,"CEP cadastrado com sucesso");
  else
    popup(NULL,"CEP atualizado com sucesso");

  cad_ceps_cancelar_fun();
  return 0;
}
