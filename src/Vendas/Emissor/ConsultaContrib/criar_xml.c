xmlDocPtr consulta_contrib_cria_xml(gchar *cnpj, gchar *uf){

  xmlDocPtr doc = xmlNewDoc( (xmlChar*)"1.0");
  //xmlNs *soap = xmlNewNs( NULL, NULL, (xmlChar*)"soap" );
  //xmlNodePtr Envelope = xmlNewNode( soap, (xmlChar*)"Envelope");

  xmlNodePtr ConsCad = xmlNewNode(NULL,(xmlChar*)"ConsCad");
  xmlNodePtr versao = xmlNewNode(NULL,(xmlChar*)"versao");
  xmlNodePtr infCons = xmlNewNode(NULL,(xmlChar*)"infCons");
  xmlNodePtr xServ = xmlNewNode(NULL,(xmlChar*)"xServ");
  xmlNodePtr UF = xmlNewNode(NULL,(xmlChar*)"UF");
  //xmlNodePtr IE = xmlNewNode(NULL,"IE");
  xmlNodePtr CNPJ = xmlNewNode(NULL,(xmlChar*)"CNPJ");
  //xmlNodePtr CPF = xmlNewNode(NULL,"CPF");

  xmlNodeSetContent(versao, (xmlChar*)"4.00");
  xmlNodeSetContent(xServ, (xmlChar*)"CONS-CAD");
  xmlNodeSetContent(CNPJ, (xmlChar*)cnpj);
  xmlNodeSetContent(UF, (xmlChar*)uf);

  xmlAddChild(infCons,xServ);
  xmlAddChild(infCons,UF);
  xmlAddChild(infCons,CNPJ);

  xmlAddChild(ConsCad,versao);
  xmlAddChild(ConsCad,infCons);

  //xmlAddChild(Envelope,ConsCad);

  //xmlDocSetRootElement(doc, Envelope);
  xmlDocSetRootElement(doc, ConsCad);

  return doc;
}
