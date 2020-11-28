xmlNode *add_pgto_xml(struct _CFe *cfe_struct){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *pgto = xmlNewNode(NULL, (xmlChar*)"pgto");
  xmlNode *MP = xmlNewNode(NULL, (xmlChar*)"MP");
  xmlNode *cMP = xmlNewNode(NULL, (xmlChar*)"cMP");
  xmlNode *vMP = xmlNewNode(NULL, (xmlChar*)"vMP");
  xmlNode *cAdmC = xmlNewNode(NULL, (xmlChar*)"cAdmC");

  xmlAddChild(MP,cMP);
  xmlAddChild(MP,vMP);
  xmlAddChild(MP,cAdmC);
  xmlAddChild(pgto,MP);

  xmlAddChild(infCFe,pgto);

  return pgto;
}
