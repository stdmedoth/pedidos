xmlDocPtr consulta_contrib_cria_xml(gchar *cnpj, gchar *uf){

  xmlDocPtr doc = xmlNewDoc( (xmlChar*)"1.0");

  xmlNodePtr ConsCad = xmlNewNode(NULL,(xmlChar*)"ConsCad");
  xmlNewProp(ConsCad, (xmlChar*)"xmlns", (xmlChar*)"http://www.portalfiscal.inf.br/nfe");
  xmlNewProp(ConsCad, (xmlChar*)"versao", (xmlChar*)"2.00");

  xmlNodePtr infCons = xmlNewNode(NULL,(xmlChar*)"infCons");
  xmlNodePtr xServ = xmlNewNode(NULL,(xmlChar*)"xServ");
  xmlNodePtr UF = xmlNewNode(NULL,(xmlChar*)"UF");
  //xmlNodePtr IE = xmlNewNode(NULL,"IE");
  xmlNodePtr CNPJ = xmlNewNode(NULL,(xmlChar*)"CNPJ");
  //xmlNodePtr CPF = xmlNewNode(NULL,"CPF");

  //xmlNodeSetContent(versao, (xmlChar*)"4.00");
  xmlNodeSetContent(xServ, (xmlChar*)"CONS-CAD");
  xmlNodeSetContent(CNPJ, (xmlChar*)cnpj);
  xmlNodeSetContent(UF, (xmlChar*)uf);

  xmlAddChild(infCons,xServ);
  xmlAddChild(infCons,UF);
  xmlAddChild(infCons,CNPJ);
  xmlAddChild(ConsCad,infCons);

  xmlDocSetRootElement(doc, ConsCad);
  /*
  if(!xmlValidateDtd(valid, doc, dtd)){
    xmlErrorPtr	erro = xmlGetLastError();
    popup(NULL,erro->message);
    return NULL;
  }
  */
  return doc;
}
