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

  if( strlen(destinatario->xLgr) >= 60 )
    destinatario->xLgr[60] = '\0';
    
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
