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
