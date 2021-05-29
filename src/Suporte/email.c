int suporte_envia_email(){

  xmlNodePtr root = xmlNewNode (NULL, (const xmlChar *)"Envio");
  xmlDocPtr doc = xmlNewDoc((xmlChar *)"1.0");
  FILE *sup_file = fopen(SUP_XML,"w");
  if(!sup_file){
    popup(NULL,"Não foi possivel abrir arquivo de exportação");
    return 1;
  }

  for(int cont=0;cont<MAX_POST_QNT;cont++){

    if((sup_vet_posts_ativos[cont])){
      
      xmlNodePtr id = xmlNewNode (NULL, (const xmlChar *)"id");
      xmlNodePtr titulo = xmlNewNode (NULL, (const xmlChar *)"titulo");
      xmlNodePtr descricao = xmlNewNode (NULL, (const xmlChar *)"descricao");
      xmlNodePtr data = xmlNewNode (NULL, (const xmlChar *)"data");
      xmlNodePtr status = xmlNewNode (NULL, (const xmlChar *)"status");
      xmlNodePtr tipo = xmlNewNode (NULL, (const xmlChar *)"tipo");
      xmlNodePtr prioridade = xmlNewNode (NULL, (const xmlChar *)"prioridade");
      xmlNodePtr post = xmlNewNode (NULL, (const xmlChar *)"post");

      xmlNodeSetContent(id,(xmlChar *)suporte_list[cont].id);
      xmlNodeSetContent(titulo,(xmlChar *)suporte_list[cont].titulo);
      xmlNodeSetContent(descricao,(xmlChar *)suporte_list[cont].descricao);
      xmlNodeSetContent(data,(xmlChar *)suporte_list[cont].data);
      xmlNodeSetContent(tipo,(xmlChar *)suporte_list[cont].tipo);
      xmlNodeSetContent(status,(xmlChar *)suporte_list[cont].status);
      xmlNodeSetContent(prioridade,(xmlChar *)suporte_list[cont].prioridade);

      xmlAddChild(post,id);
      xmlAddChild(post,titulo);
      xmlAddChild(post,descricao);
      xmlAddChild(post,data);
      xmlAddChild(post,status);
      xmlAddChild(post,prioridade);
      xmlAddChild(post,tipo);
      xmlAddChild(root,post);
    }

  }

  xmlDocSetRootElement(doc,root);

  if(xmlDocDump(sup_file,doc)<=0){
    fclose(sup_file);
    popup(NULL,"O arquivo de comunicaçao teve erro na exportação XML");
    return 1;
  }
  fclose(sup_file);

  enviar_email_suporte( SUP_XML );


  return 0;
}
