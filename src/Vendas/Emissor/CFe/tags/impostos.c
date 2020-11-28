struct _cfe_imposto *get_cupom_impostos(struct _CFe *cupom){
  if(!cupom)
    return NULL;

  struct _cfe_imposto *imposto = malloc(sizeof(struct _cfe_imposto) *MAX_PROD_ORC);

  //int origem = get_terceiro_origem(cupom->pedido->infos->cliente_code);
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
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

  float base=0;
  for(int item=0;item<cupom->det->itens_qnt;item++){
    base += cupom->det->produtos[item].dtotal;
  }

  for(int item=0;item<cupom->det->itens_qnt;item++){

    float valortotalitem = atof(cupom->det->produtos[item].qCom) * atof(cupom->det->produtos[item].vUnCom);
    float vicms = valortotalitem * fAlICMS / 100;

    imposto[item].ICMSCST = strdup(cupom->det->produtos[item].ICMSCST);

    imposto[item].PISCST = strdup(cupom->det->produtos[item].PISCST);
    imposto[item].PISAliq = strdup(cupom->det->produtos[item].PISAliq);
    imposto[item].PISvBC = strdup(floattochar(base));

    imposto[item].COFINSCST = strdup(cupom->det->produtos[item].COFINSCST);
    imposto[item].COFINSAliq = strdup(cupom->det->produtos[item].COFINSAliq);
    imposto[item].COFINSvBC = strdup(floattochar(base));

    imposto[item].Orig = strdup(cupom->det->produtos[item].Orig);

    if(cad_emp_strc.RegTribInt == SIMPLES_NACIONAL)
      imposto[item].pICMS = strdup(cAlICMS);
    else
    if(cad_emp_strc.RegTribInt == REGIME_NORMAL){
      sprintf(query, "SELECT * FROM IcmsInterestadual where origem = '%s' and destino = '%s'", cad_emp_strc.UF, cupom->dest.UF);
      if(!(res = consultar(query))){
        popup(NULL,"Não foi possível buscar alíquota interstadual de ICMS");
        return NULL;
      }
      if(!(row = mysql_fetch_row(res))){
        gchar *msg = malloc(strlen(cad_emp_strc.UF) + strlen(cupom->dest.UF) + 60);
        sprintf(msg,"Alíquota interestadual de ICMS não definida de '%s' para '%s'", cad_emp_strc.UF, cupom->dest.UF);
        popup(NULL,msg);
        return NULL;
      }
      imposto[item].pICMS = strdup(row[INTERICMS_ALIQ_COL]);
    }
  }

  return imposto;
}
