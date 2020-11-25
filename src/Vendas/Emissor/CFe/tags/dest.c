xmlNode *add_dest_xml(struct _CFe *cfe_struct, struct _terc_infos *destinatario){

    if(!cfe_struct->xml)
      return NULL;

    xmlNode *infCFe = criar_InfCFeNode(cfe_struct->xml);

    xmlNode *dest = xmlNewNode(NULL, (xmlChar*)"dest");
    xmlNode *CPF = xmlNewNode(NULL, (xmlChar*)"CPF");
    xmlNode *xNome = xmlNewNode(NULL, (xmlChar*)"xNome");

    xmlNodeAddContent(xNome,(xmlChar*)destinatario->razao);
    xmlNodeAddContent(CPF,(xmlChar*)destinatario->doc);

    xmlAddChild(dest,CPF);
    xmlAddChild(dest,xNome);

    xmlAddChild(infCFe,dest);

    return dest;
}
