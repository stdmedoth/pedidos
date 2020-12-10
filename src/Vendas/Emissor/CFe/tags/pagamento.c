xmlNode *add_pgto_xml(struct _CFe *cfe_struct){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(!cfe_struct->xml){
    popup(NULL,"Estrutura de dados do cupom não foi criada");
    autologger("Estrutura de dados do cupom não foi criada");
    return NULL;
  }

  xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

  if(!cfe_struct->pgto){
    popup(NULL,"Estrutura de dados do pagamento não foi criada");
    autologger("Estrutura de dados do pagamento não foi criada");
    return NULL;
  }

  xmlNode *pgto = xmlNewNode(NULL, (xmlChar*)"pgto"); //tag com MP
  for(int cont=0; cont < cfe_struct->MPqnt ;cont++){

    xmlNode *MP = xmlNewNode(NULL, (xmlChar*)"MP"); //tag com os filhos
    xmlNode *cMP = xmlNewNode(NULL, (xmlChar*)"cMP"); //código utilizado no meio de pagamento
    xmlNode *vMP = xmlNewNode(NULL, (xmlChar*)"vMP"); //valor no meio de pagamento
    xmlNode *cAdmC = xmlNewNode(NULL, (xmlChar*)"cAdmC"); // 001 a 034 ou 999.

    xmlNodeAddContent(cMP, (xmlChar*)cfe_struct->pgto[cont].ccMP);
    xmlNodeAddContent(vMP, (xmlChar*)cfe_struct->pgto[cont].cvMP);
    if(cfe_struct->pgto[cont].icMP == MEIO_PAG_CTCREDITO || cfe_struct->pgto[cont].icMP == MEIO_PAG_CTDEBITO)
      xmlNodeAddContent(cAdmC, (xmlChar*)cfe_struct->pgto[cont].cAdmC);

    xmlAddChild(MP,cMP);
    xmlAddChild(MP,vMP);
    if(cfe_struct->pgto[cont].icMP == MEIO_PAG_CTCREDITO || cfe_struct->pgto[cont].icMP == MEIO_PAG_CTDEBITO)
      xmlAddChild(MP,cAdmC);
    xmlAddChild(pgto,MP);

  }

  xmlAddChild(infCFe,pgto);

  return pgto;
}
