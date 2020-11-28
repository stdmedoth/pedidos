xmlNode *add_dets_xml(struct _CFe *cfe_struct){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  for(int item=0;item<cfe_struct->det->itens_qnt;item++){

    xmlNode *det = xmlNewNode(NULL, (xmlChar*)"det");
    xmlSetProp(det, (xmlChar*)"nItem", (xmlChar*)cfe_struct->det->produtos[item].nItem);

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

    xmlNodeAddContent(cProd, (xmlChar*)cfe_struct->det->produtos[item].cProd);
    xmlNodeAddContent(cEAN, (xmlChar*)cfe_struct->det->produtos[item].cEAN);
    xmlNodeAddContent(xProd, (xmlChar*)cfe_struct->det->produtos[item].xProd);
    xmlNodeAddContent(NCM, (xmlChar*)cfe_struct->det->produtos[item].NCM);
    xmlNodeAddContent(CFOP, (xmlChar*)cfe_struct->det->produtos[item].CFOP);
    xmlNodeAddContent(uCom, (xmlChar*)cfe_struct->det->produtos[item].uCom);
    xmlNodeAddContent(qCom, (xmlChar*)cfe_struct->det->produtos[item].qCom);
    xmlNodeAddContent(vUnCom, (xmlChar*)cfe_struct->det->produtos[item].vUnCom);
    xmlNodeAddContent(indRegra, (xmlChar*)cfe_struct->det->produtos[item].indRegra);
    xmlNodeAddContent(vDesc, (xmlChar*)cfe_struct->det->produtos[item].vDesc);
    xmlNodeAddContent(vOutro, (xmlChar*)cfe_struct->det->produtos[item].vOutro);

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

    gchar *icmscst = malloc(sizeof(char) * strlen(cfe_struct->det->impostos[item].ICMSCST)+10);
    gchar *piscst = malloc(sizeof(char) * strlen(cfe_struct->det->impostos[item].PISCST)+10);
    gchar *cofinscst = malloc(sizeof(char) * strlen(cfe_struct->det->impostos[item].COFINSCST)+10);

    sprintf(icmscst,"ICMS%s", cfe_struct->det->impostos[item].ICMSCST);
    xmlNode *ICMSNUM = xmlNewNode(NULL, (xmlChar*)icmscst);

    xmlNode *ICMSOrig = xmlNewNode(NULL, (xmlChar*)"Orig");
    xmlNode *ICMSCST = xmlNewNode(NULL, (xmlChar*)"CST");
    xmlNode *pICMS = xmlNewNode(NULL, (xmlChar*)"pICMS");

    xmlNodeAddContent(ICMSOrig, (xmlChar*)cfe_struct->det->impostos[item].Orig);
    sprintf(icmscst,"%s",cfe_struct->det->impostos[item].ICMSCST);
    xmlNodeAddContent(ICMSCST, (xmlChar*)icmscst);
    xmlNodeAddContent(pICMS, (xmlChar*)cfe_struct->det->impostos[item].pICMS);

    xmlAddChild(ICMSNUM,ICMSOrig);
    xmlAddChild(ICMSNUM,ICMSCST);
    xmlAddChild(ICMSNUM,pICMS);

    xmlAddChild(ICMS, ICMSNUM);

    xmlNode *PIS = xmlNewNode(NULL, (xmlChar*)"PIS");
    xmlNode *PISAliq = xmlNewNode(NULL, (xmlChar*)"PISAliq");
    xmlNode *PISCST = xmlNewNode(NULL, (xmlChar*)"CST");
    xmlNode *PISvBC = xmlNewNode(NULL, (xmlChar*)"vBC");
    xmlNode *pPIS = xmlNewNode(NULL, (xmlChar*)"pPIS");

    xmlAddChild(PISAliq, PISCST);
    xmlAddChild(PISAliq, PISvBC);
    xmlAddChild(PISAliq, pPIS);

    xmlNodeAddContent(PISCST, (xmlChar*)cfe_struct->det->impostos[item].PISCST);
    xmlNodeAddContent(PISvBC, (xmlChar*)cfe_struct->det->impostos[item].PISvBC);
    xmlNodeAddContent(pPIS, (xmlChar*)cfe_struct->det->impostos[item].PISAliq);

    xmlAddChild(PIS, PISAliq);

    xmlNode *COFINS = xmlNewNode(NULL, (xmlChar*)"COFINS");
    xmlNode *COFINSAliq = xmlNewNode(NULL, (xmlChar*)"COFINSAliq");
    xmlNode *COFINSCST = xmlNewNode(NULL, (xmlChar*)"CST");
    xmlNode *COFINSvBC = xmlNewNode(NULL, (xmlChar*)"vBC");
    xmlNode *pCOFINS = xmlNewNode(NULL, (xmlChar*)"pCOFINS");

    xmlNodeAddContent(COFINSCST, (xmlChar*)cfe_struct->det->impostos[item].COFINSCST);
    xmlNodeAddContent(COFINSvBC, (xmlChar*)cfe_struct->det->impostos[item].COFINSvBC);
    xmlNodeAddContent(pCOFINS, (xmlChar*)cfe_struct->det->impostos[item].COFINSAliq);

    xmlAddChild(COFINSAliq, COFINSCST);
    xmlAddChild(COFINSAliq, COFINSvBC);
    xmlAddChild(COFINSAliq, pCOFINS);

    xmlAddChild(COFINS, COFINSAliq);

    xmlAddChild(imposto,ICMS);
    xmlAddChild(imposto,PIS);
    xmlAddChild(imposto,COFINS);

    xmlAddChild(det,prod);
    xmlAddChild(det,imposto);

    xmlAddChildList(infCFe,det);
  }

  return infCFe;
}
