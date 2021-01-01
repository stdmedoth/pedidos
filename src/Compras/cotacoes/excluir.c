int cotacao_excluir_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  cotac_excluindo = 1;

  int status=0;
  if(cotac_code_fun())
    return 1;

  sprintf(query,"select status from cotacoes where code = %i", cotacao_new->code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar status da cotação");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Cotação não existente");
    return 1;
  }
  status = atoi(row[0]);
  if(status != COTAC_STAT_CRIACAO){
    if(!PopupBinario("A cotação não está mais em criação, deseja excluir ainda?", "Sim! Desejo excluir", "Não! Manter a cotação"))
      return 1;
  }

  sprintf(query,"select * from itens_ordens_compra as ioc inner join itens_cotacoes as ic on ioc.itens_cotacao = ic.code where ic.cotacoes_id = %i", cotacao_new->code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar ordens de compra com essa cotação");
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    popup(NULL,"Existem ordens de compra vinculadas a essa cotação");
    return 1;
  }

  sprintf(query,"delete from cotacoes_participantes where cotacoes_id = %i", cotacao_new->code);
  if(enviar_query(query)){
    popup(NULL,"Não foi possivel excluir itens da cotação");
    return 1;
  }

  sprintf(query,"delete from itens_cotacoes where cotacoes_id = %i", cotacao_new->code);
  if(enviar_query(query)){
    popup(NULL,"Não foi possivel excluir itens da cotação");
    return 1;
  }

  sprintf(query,"delete from cotacoes where code = %i", cotacao_new->code);
  if(enviar_query(query)){
    popup(NULL,"Não foi possivel excluir cotação");
    return 1;
  }

  popup(NULL,"Cotação deletada com sucesso");
  cotacao_cancelar_fun();
  return 0;
}
