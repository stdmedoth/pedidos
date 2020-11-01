struct _CFe *get_cupons_from_ped(struct _pedido *pedido){
  static struct _CFe CFe;
  struct _CFe *pCFe = &CFe;

  ini_cupom_xml(pCFe);
  add_ide_xml(pCFe);
  add_emit_xml(pCFe);

  return pCFe;
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
    xmlSetProp(infCFe, (xmlChar*)"Id", (xmlChar*)"1");
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
  xmlNodeAddContent(CNPJ, (xmlChar*)cfe_struct->ide.CNPJ);

  xmlAddChild(ide,CNPJ);
  xmlNode *signAC = xmlNewNode(NULL, (xmlChar*)"signAC");
  xmlNodeAddContent(signAC, (xmlChar*)cfe_struct->ide.signAC);
  xmlAddChild(ide,signAC);
  xmlNode *numeroCaixa = xmlNewNode(NULL, (xmlChar*)"numeroCaixa");
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
  xmlNodeAddContent(CNPJ, (xmlChar*)cad_emp_strc.CNPJ);
  xmlAddChild(emit,CNPJ);

  xmlAddChild(infCFe,emit);

  return emit;
}
