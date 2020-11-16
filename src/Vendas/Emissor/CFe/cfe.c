struct _cfe_produto *get_cupom_itens(int orc_code){
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

  gchar *formatar_valor = malloc(30);

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

struct _cfe_imposto *get_cupom_impostos(struct _CFe *cupom){
  if(!cupom)
    return NULL;

  struct _cfe_imposto *imposto = malloc(sizeof(struct _cfe_imposto) *MAX_PROD_ORC);

  //int origem = get_terceiro_origem(cupom->pedido->infos->cliente_code);

  gchar *prod_origem = strdup("0");
  gchar *csticms = strdup("00");
  gchar *cfop_venda = strdup("5102");
  gchar *cfop_devol_venda = strdup("1202");

  gchar *valor = malloc(20);
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

struct _CFe *get_cupons_from_ped(struct _pedido *pedido){
  static struct _CFe CFe;
  struct _CFe *pCFe = &CFe;

  if(!pedido)
    return NULL;

  pCFe = cupom_get_base_infos(pCFe);

  if(!pCFe)
    return NULL;

  if(!ini_cupom_xml(pCFe))
    return NULL;

  if(!add_ide_xml(pCFe))
    return NULL;

  if(!add_emit_xml(pCFe))
    return NULL;

  struct _terc_infos *destino = terceiros_get_terceiro(pedido->infos->cliente_code);
  if(!destino)
    return NULL;

  if(!add_dest_xml(pCFe, destino))
    return NULL;

  if(!add_entrega_xml(pCFe, destino))
    return NULL;

  pCFe->pedido = pedido;

  struct _cfe_det *detalhamentos = malloc(sizeof(struct _cfe_det));
  pCFe->det = detalhamentos;

  int itens_qnt = orcamentos_get_orc_itens_qnt(pedido->infos->ped_code);
  pCFe->det->itens_qnt = itens_qnt;
  struct _cfe_produto *itens = get_cupom_itens(pedido->infos->ped_code);
  if(!itens)
    return NULL;
  detalhamentos->produtos = itens;

  struct _cfe_imposto *impostos = get_cupom_impostos(pCFe);
  if(!impostos)
    return NULL;
  detalhamentos->impostos = impostos;

  if(!add_dets_xml(pCFe, detalhamentos, itens_qnt))
    return NULL;

  return pCFe;
}

struct _CFe *cupom_get_base_infos(struct _CFe *cfe_struct){

  strcpy(cfe_struct->ide.CNPJ,cad_software_house.CNPJ);
  strcpy(cfe_struct->ide.signAC,cad_software_house.signAC);
  struct _maquina *maquina = maquinas_get_atual();

  if(!maquina)
    return NULL;
  struct _caixa *caixa = caixa_get_aberto(maquina);
  if(!caixa)
    return NULL;

  if(caixa->status == CAIXA_ABERTO){
    sprintf(cfe_struct->ide.numeroCaixa, "%03d" , caixa->id);
  }
  else{
    sprintf(cfe_struct->ide.numeroCaixa, "000");
  }

  strcpy(cfe_struct->emit.CNPJ,cad_emp_strc.CNPJ);
  strcpy(cfe_struct->emit.IE,cad_emp_strc.IE);
  strcpy(cfe_struct->emit.cRegTribISSQN,cad_emp_strc.cRegTribISSQN);
  strcpy(cfe_struct->emit.indRatISSQN,cad_emp_strc.indRatISSQN);

  return cfe_struct;
}

xmlDoc *ini_cupom_xml(struct _CFe *cfe_struct){
  xmlChar *version = (xmlChar *)"1.0";
  xmlDoc *cfe_xml = xmlNewDoc(version);
  if(cfe_xml){
    xmlNode *cfe = xmlNewNode(NULL,(xmlChar *)"CFe");
    xmlDocSetRootElement(cfe_xml,cfe);
    cfe_struct->xml = cfe_xml;
  }

  return cfe_xml;
}

xmlNode *criar_InfCFeNode(xmlDoc *xml){

  xmlNode *CFe = xmlDocGetRootElement(xml);
  xmlNode *infCFe = NULL;
  xmlXPathContextPtr contxt = xmlXPathNewContext(xml);
  xmlXPathObjectPtr node_contxt= xmlXPathEval((xmlChar*)"/CFe/infCFe[1]",contxt);

  if(node_contxt){
    if(node_contxt->nodesetval && node_contxt->nodesetval->nodeTab){
      g_print("Node encontrado\n");
      infCFe = node_contxt->nodesetval->nodeTab[0];
    }
  }

  if(!node_contxt || !infCFe){
    infCFe = xmlNewNode(NULL, (xmlChar*)"infCFe");
    //xmlSetProp(infCFe, (xmlChar*)"Id", (xmlChar*)"1");
    xmlSetProp(infCFe, (xmlChar*)"versaoDadosEnt", (xmlChar*)"0.06");
    xmlAddChild(CFe,infCFe);
  }
  return infCFe;
}


xmlNode *add_ide_xml(struct _CFe *cfe_struct){

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *ide = xmlNewNode(NULL, (xmlChar*)"ide");
  xmlNode *CNPJ = xmlNewNode(NULL, (xmlChar*)"CNPJ");
  xmlNode *signAC = xmlNewNode(NULL, (xmlChar*)"signAC");
  xmlNode *numeroCaixa = xmlNewNode(NULL, (xmlChar*)"numeroCaixa");

  xmlNodeAddContent(CNPJ, (xmlChar*)cfe_struct->ide.CNPJ);
  xmlNodeAddContent(signAC, (xmlChar*)cfe_struct->ide.signAC);
  xmlNodeAddContent(numeroCaixa, (xmlChar*)cfe_struct->ide.numeroCaixa);

  xmlAddChild(ide,CNPJ);
  xmlAddChild(ide,signAC);
  xmlAddChild(ide,numeroCaixa);

  xmlAddChild(infCFe,ide);

  return ide;
}

xmlNode *add_emit_xml(struct _CFe *cfe_struct){

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *emit = xmlNewNode(NULL, (xmlChar*)"emit");
  xmlNode *CNPJ = xmlNewNode(NULL, (xmlChar*)"CNPJ");
  xmlNode *IE = xmlNewNode(NULL, (xmlChar*)"IE");
  xmlNode *cRegTribISSQN = xmlNewNode(NULL, (xmlChar*)"cRegTribISSQN");
  xmlNode *indRatISSQN = xmlNewNode(NULL, (xmlChar*)"indRatISSQN");

  xmlNodeAddContent(CNPJ, (xmlChar*)cfe_struct->emit.CNPJ);
  xmlNodeAddContent(IE, (xmlChar*)cfe_struct->emit.IE);
  xmlNodeAddContent(cRegTribISSQN, (xmlChar*)cfe_struct->emit.cRegTribISSQN);
  xmlNodeAddContent(indRatISSQN, (xmlChar*)cfe_struct->emit.indRatISSQN);

  xmlAddChild(emit,CNPJ);
  xmlAddChild(emit,IE);
  xmlAddChild(emit,cRegTribISSQN);
  xmlAddChild(emit,indRatISSQN);

  xmlAddChild(infCFe,emit);

  return emit;

}


xmlNode *add_dest_xml(struct _CFe *cfe_struct, struct _terc_infos *destinatario){

    if(!cfe_struct->xml)
      return NULL;

    xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

    xmlNode *dest = xmlNewNode(NULL, (xmlChar*)"dest");
    xmlNode *CPF = xmlNewNode(NULL, (xmlChar*)"CPF");
    xmlNode *xNome = xmlNewNode(NULL, (xmlChar*)"xNome");

    xmlNodeAddContent(xNome,(xmlChar*)destinatario->razao);
    xmlNodeAddContent(CPF,(xmlChar*)destinatario->doc);

    xmlAddChild(dest,xNome);
    xmlAddChild(dest,CPF);

    xmlAddChild(infCFe,dest);

    return dest;
}


xmlNode *add_entrega_xml(struct _CFe *cfe_struct, struct _terc_infos *destinatario){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *entrega = xmlNewNode(NULL, (xmlChar*)"entrega");
  xmlNode *xLgr = xmlNewNode(NULL, (xmlChar*)"xLgr");
  xmlNode *nro = xmlNewNode(NULL, (xmlChar*)"nro");
  xmlNode *xCpl = xmlNewNode(NULL, (xmlChar*)"xCpl");
  xmlNode *xBairro = xmlNewNode(NULL, (xmlChar*)"xBairro");
  xmlNode *xMun = xmlNewNode(NULL, (xmlChar*)"xMun");
  xmlNode *UF = xmlNewNode(NULL, (xmlChar*)"UF");

  xmlNodeAddContent(xLgr,(xmlChar*)destinatario->xLgr);
  xmlNodeAddContent(nro,(xmlChar*)destinatario->c_nro);
  xmlNodeAddContent(xCpl,(xmlChar*)destinatario->xCpl);
  xmlNodeAddContent(xBairro,(xmlChar*)destinatario->xBairro);
  xmlNodeAddContent(xMun,(xmlChar*)destinatario->xMun);
  xmlNodeAddContent(UF,(xmlChar*)destinatario->UF);


  xmlAddChild(entrega,xLgr);
  xmlAddChild(entrega,nro);
  if(strlen(destinatario->xCpl))
    xmlAddChild(entrega,xCpl);
  xmlAddChild(entrega,xBairro);
  xmlAddChild(entrega,xMun);
  xmlAddChild(entrega,UF);

  xmlAddChild(infCFe,entrega);

  return entrega;
}

xmlNode *add_dets_xml(struct _CFe *cfe_struct, struct _cfe_det *detalhamentos, int itens_qnt){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  for(int item=0;item<itens_qnt;item++){

    xmlNode *det = xmlNewNode(NULL, (xmlChar*)"det");
    xmlSetProp(det, (xmlChar*)"nItem", (xmlChar*)detalhamentos->produtos[item].nItem);

    xmlNode *prod = xmlNewNode(NULL, (xmlChar*)"prod");
    xmlNode *cProd = xmlNewNode(NULL, (xmlChar*)"cProd");
    xmlNode *cEAN = xmlNewNode(NULL, (xmlChar*)"cEAN");
    xmlNode *xProd = xmlNewNode(NULL, (xmlChar*)"xProd");
    xmlNode *NCM = xmlNewNode(NULL, (xmlChar*)"NCM");
    xmlNode *CFOP = xmlNewNode(NULL, (xmlChar*)"CFOP");
    xmlNode *uCom = xmlNewNode(NULL, (xmlChar*)"uCom");
    xmlNode *qCom = xmlNewNode(NULL, (xmlChar*)"qCom");
    xmlNode *vUnCom = xmlNewNode(NULL, (xmlChar*)"vUnCom");
    xmlNode *indRegra = xmlNewNode(NULL, (xmlChar*)"indRegra");
    xmlNode *vDesc = xmlNewNode(NULL, (xmlChar*)"vDesc");
    xmlNode *vOutro = xmlNewNode(NULL, (xmlChar*)"vOutro");

    xmlNodeAddContent(cProd, (xmlChar*)detalhamentos->produtos[item].cProd);
    xmlNodeAddContent(cEAN, (xmlChar*)detalhamentos->produtos[item].cEAN);
    xmlNodeAddContent(xProd, (xmlChar*)detalhamentos->produtos[item].xProd);
    xmlNodeAddContent(NCM, (xmlChar*)detalhamentos->produtos[item].NCM);
    xmlNodeAddContent(CFOP, (xmlChar*)detalhamentos->produtos[item].CFOP);
    xmlNodeAddContent(uCom, (xmlChar*)detalhamentos->produtos[item].uCom);
    xmlNodeAddContent(qCom, (xmlChar*)detalhamentos->produtos[item].qCom);
    xmlNodeAddContent(vUnCom, (xmlChar*)detalhamentos->produtos[item].vUnCom);
    xmlNodeAddContent(indRegra, (xmlChar*)detalhamentos->produtos[item].indRegra);
    xmlNodeAddContent(vDesc, (xmlChar*)detalhamentos->produtos[item].vDesc);
    xmlNodeAddContent(vOutro, (xmlChar*)detalhamentos->produtos[item].vOutro);

    xmlAddChild(prod,cProd);
    xmlAddChild(prod,cEAN);
    xmlAddChild(prod,xProd);
    xmlAddChild(prod,NCM);
    xmlAddChild(prod,CFOP);
    xmlAddChild(prod,uCom);
    xmlAddChild(prod,qCom);
    xmlAddChild(prod,vUnCom);
    xmlAddChild(prod,indRegra);
    xmlAddChild(prod,vDesc);
    xmlAddChild(prod,vOutro);

    xmlNode *imposto = xmlNewNode(NULL, (xmlChar*)"imposto");
    xmlNode *ICMS = xmlNewNode(NULL, (xmlChar*)"ICMS");

    gchar *icmscst = malloc(strlen(detalhamentos->impostos[item].ICMSCST)+10);
    sprintf(icmscst,"ICMS%s", detalhamentos->impostos[item].ICMSCST);
    xmlNode *ICMSNUM = xmlNewNode(NULL, (xmlChar*)icmscst);

    xmlNode *ICMSOrig = xmlNewNode(NULL, (xmlChar*)"Orig");
    xmlNode *ICMSCST = xmlNewNode(NULL, (xmlChar*)"CST");
    xmlNode *pICMS = xmlNewNode(NULL, (xmlChar*)"pICMS");

    xmlNodeAddContent(ICMSOrig, (xmlChar*)detalhamentos->impostos[item].Orig);
    sprintf(icmscst,"%s",detalhamentos->impostos[item].ICMSCST);
    xmlNodeAddContent(ICMSCST, (xmlChar*)icmscst);
    xmlNodeAddContent(pICMS, (xmlChar*)detalhamentos->impostos[item].pICMS);

    xmlAddChild(ICMSNUM,ICMSOrig);
    xmlAddChild(ICMSNUM,ICMSCST);
    xmlAddChild(ICMSNUM,pICMS);

    xmlAddChild(ICMS, ICMSNUM);
    /*
    PISAliq
    CST
    vBC
    pPIS
    PISST
    vBC
    pPIS
    COFINS
    COFINSAliq
    CST
    vBC
    pCOFINS
    COFINSST
    vBC
    pCOFINS
    */
    xmlAddChild(imposto,ICMS);


    xmlAddChild(det,prod);
    xmlAddChild(det,imposto);

    xmlAddChild(infCFe,det);
  }

  return infCFe;
}
