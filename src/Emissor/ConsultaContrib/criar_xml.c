xmlDocPtr consulta_contrib_cria_xml(gchar *cnpj, gchar *uf){

  xmlDocPtr doc = xmlNewDoc( (xmlChar*)"1.0");

  xmlValidCtxtPtr	valid = xmlNewValidCtxt();
  xmlDocPtr xsdDoc = xmlReadFile("/home/calistu/Downloads/PL_009/consCad_v2.00.xsd", NULL, XML_PARSE_DTDLOAD);
  xmlDtdPtr dtd = xmlNewDtd(xsdDoc,  (xmlChar*)"consCad", (xmlChar*)"consCad_v2.00",  (xmlChar*)"consCad_v2.00.xsd");

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
