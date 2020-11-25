struct _cfe_produto *get_cupom_itens_from_orc(int orc_code){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  int itens_qnt=0;

  struct _cfe_produto *cupom_itens = malloc(sizeof(struct _cfe_produto) *MAX_PROD_ORC);

  sprintf(query,"select op.code, op.item, p.nome, u.sigla, op.unidades, op.valor_unit, op.desconto, ped.tipo_mov from Produto_Orcamento as op inner join produtos as p inner join unidades as u inner join pedidos as ped on op.produto = p.code and p.unidades  = u.code and ped.code = op.code where op.code = %i",orc_code);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar itens do orçamento");
    return NULL;
  }

  gchar *formatar_valor = malloc(sizeof(char) * 30);

  while((row = mysql_fetch_row(res))){

    if(itens_qnt >= MAX_PROD_ORC)
      return cupom_itens;

    cupom_itens[itens_qnt].nItem = strdup(row[1]);

    cupom_itens[itens_qnt].cProd = strdup(row[0]);

    cupom_itens[itens_qnt].cEAN = strdup(" ");

    cupom_itens[itens_qnt].xProd = strdup(row[2]);

    cupom_itens[itens_qnt].NCM = strdup("22011000");

    switch(atoi(row[7])){
      case VENDA:
        cupom_itens[itens_qnt].CFOP = strdup("5102");
        break;
      case DEV_VENDA:
        cupom_itens[itens_qnt].CFOP = strdup("1202");
        break;
      default:
        cupom_itens[itens_qnt].CFOP = strdup(" ");
        break;
    }

    cupom_itens[itens_qnt].uCom = strdup(row[3]);

    sprintf(formatar_valor,"%010.4f",atof(row[4]));
    cupom_itens[itens_qnt].qCom = strdup(formatar_valor);

    sprintf(formatar_valor,"%010.2f",atof(row[5]));
    cupom_itens[itens_qnt].vUnCom = strdup(formatar_valor);

    cupom_itens[itens_qnt].indRegra = strdup("A");

    sprintf(formatar_valor,"%010.2f",atof(row[6]));
    cupom_itens[itens_qnt].vDesc = strdup(formatar_valor);

    float outras_deducoes = 0;
    sprintf(formatar_valor,"%010.2f",outras_deducoes);
    cupom_itens[itens_qnt].vOutro = strdup(formatar_valor);
    itens_qnt++;
  }

  return cupom_itens;
}
