xmlNode *add_infAdic_xml(struct _CFe *cfe_struct){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *infAdic = xmlNewNode(NULL, (xmlChar*)"infAdic");
  xmlNode *infCpl = xmlNewNode(NULL, (xmlChar*)"infCpl");

//  xmlAddChild(infAdic,infCpl);
//  xmlAddChild(infCFe,infAdic);

  return infAdic;
}
