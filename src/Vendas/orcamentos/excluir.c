static int excluir_orc(){
  MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

  if(codigo_orc()!=0)
    return 1;

  excluindo_orc = 1;
  sprintf(query,"select * from pedidos where code = %i",atoi(codigo_orc_gchar));
  if((res = consultar(query))==NULL){
    popup(NULL,"Erro ao consultar status do orçamento");
    return 1;
  }
  if((row = mysql_fetch_row(res) )!=NULL){
    if(atoi(row[PED_STATUS_COL]) == STATUS_PED_EMIT){
      popup(NULL,"O orçamento possui pedido com status emitido");
      return 1;
    }
  }

  sprintf(query,"delete from Produto_Orcamento where code = %i",atoi(codigo_orc_gchar));
  if( enviar_query(query) != 0 )
  {
    popup(NULL,"Erro ao tentar excluir orçamento");
    return 1;
  }

  sprintf(query,"delete from orcamentos where code = %i",atoi(codigo_orc_gchar));
  if( enviar_query(query) != 0 )
  {
    popup(NULL,"Erro ao tentar excluir orçamento");
    return 1;
  }

  popup(NULL,"Excluído com sucesso");

  cancela_orc();
  return 0;
}
