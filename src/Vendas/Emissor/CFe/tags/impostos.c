struct _cfe_imposto *get_cupom_impostos(struct _CFe *cupom){
  if(!cupom)
    return NULL;

  struct _cfe_imposto *imposto = malloc(sizeof(struct _cfe_imposto) *MAX_PROD_ORC);

  //int origem = get_terceiro_origem(cupom->pedido->infos->cliente_code);

  gchar *prod_origem = strdup("0");
  gchar *csticms = strdup("00");
  gchar *cfop_venda = strdup("5102");
  gchar *cfop_devol_venda = strdup("1202");

  gchar *valor = malloc(sizeof(char) * 20);
  sprintf(valor,"%03.2f",15.00);
  gchar *cAlICMS = strdup(valor);
  float fAlICMS = 15;

  sprintf(valor,"%03.2f",0.65);
  gchar *cAlPIS = strdup(valor);
  float fAlPIS = 0.65;


  for(int item=0;item<cupom->det->itens_qnt;item++){


    float valortotalitem = atof(cupom->det->produtos[item].qCom) * atof(cupom->det->produtos[item].vUnCom);
    float vicms = valortotalitem * fAlICMS / 100;

    imposto[item].ICMSCST = strdup(csticms);
    imposto[item].Orig = strdup(prod_origem);
    imposto[item].pICMS = strdup(cAlICMS);

    imposto[item].PISAliqCST = strdup(cAlICMS);
    sprintf(valor,"%010.2f",valortotalitem * fAlICMS / 100);
    imposto[item].PISAliqvBC = strdup(valor);

    sprintf(valor,"%010.2f",atof(cAlPIS));
    imposto[item].PISAliqpPIS = strdup(valor);

  }

  return imposto;
}
