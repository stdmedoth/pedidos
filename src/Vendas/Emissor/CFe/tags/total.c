xmlNode *add_total_xml(struct _CFe *cfe_struct){

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *total = xmlNewNode(NULL, (xmlChar*)"total");
  xmlNode *DescAcrEntr = xmlNewNode(NULL, (xmlChar*)"DescAcrEntr");
  xmlNode *vAcresSubtot = xmlNewNode(NULL, (xmlChar*)"vAcresSubtot");

  xmlAddChild(DescAcrEntr,vAcresSubtot);
  xmlAddChild(total,DescAcrEntr);
  xmlAddChild(infCFe,total);

  return total;
}
