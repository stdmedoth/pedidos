xmlNode *add_emit_xml(struct _CFe *cfe_struct){

  if(!cfe_struct->xml)
    return NULL;

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  xmlNode *emit = xmlNewNode(NULL, (xmlChar*)"emit");
  xmlNode *CNPJ = xmlNewNode(NULL, (xmlChar*)"CNPJ");
  xmlNode *IE = xmlNewNode(NULL, (xmlChar*)"IE");
  xmlNode *IM = xmlNewNode(NULL, (xmlChar*)"IM");
  xmlNode *cRegTribISSQN = xmlNewNode(NULL, (xmlChar*)"cRegTribISSQN");
  xmlNode *indRatISSQN = xmlNewNode(NULL, (xmlChar*)"indRatISSQN");

  xmlNodeAddContent(CNPJ, (xmlChar*)cfe_struct->emit.CNPJ);
  xmlNodeAddContent(IE, (xmlChar*)cfe_struct->emit.IE);
  xmlNodeAddContent(IM, (xmlChar*)cfe_struct->emit.IM);
  xmlNodeAddContent(cRegTribISSQN, (xmlChar*)cfe_struct->emit.cRegTribISSQN);
  xmlNodeAddContent(indRatISSQN, (xmlChar*)cfe_struct->emit.indRatISSQN);

  xmlAddChild(emit,CNPJ);
  xmlAddChild(emit,IE);
  xmlAddChild(emit,IM);
  xmlAddChild(emit,cRegTribISSQN);
  xmlAddChild(emit,indRatISSQN);

  xmlAddChild(infCFe,emit);

  return emit;

}
