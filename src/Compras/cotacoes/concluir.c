int cotacao_concluir_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(cotac_code_fun())
    return 1;

  if(cotac_get_participante())
    return 1;

  if(cotac_data_fun())
    return 1;

  if(cotac_validade_fun())
    return 1;

  if(cotac_tipo_fun())
    return 1;

  if(cotac_status_fun())
    return 1;

  if(cotac_alterando)
    sprintf(query,"update cotacoes set   ");
  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    if(cotac_ativo[cont] && cotac_produto_inserido[cont]){

      if(cotat_itens_prod_fun(GTK_ENTRY(cotac_prod_cod_entry[cont]), cont))
        return 1;

      if(cotat_itens_prc_fun(GTK_ENTRY(cotac_prod_cod_entry[cont]), cont))
        return 1;

      if(cotat_itens_qnt_fun(GTK_ENTRY(cotac_prod_qnt_entry[cont]), cont))
        return 1;

    }
  }



  //sprintf()

  if(cotac_alterando)
    popup(NULL,"Atualizado com sucesso");
  else
    popup(NULL,"Criado com sucesso");
  return 0;
}
