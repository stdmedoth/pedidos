xmlNodePtr search_content_tag(xmlNode * a_node, char *TagName){
  xmlNode *cur_node = NULL;
  if(a_node==NULL)
  {
      return NULL;
  }

  for (cur_node = a_node; cur_node; cur_node = cur_node->next)
  {
    if (cur_node->type == XML_ELEMENT_NODE)
    {
      if(cur_node->children->type == XML_TEXT_NODE){
        if(cur_node->name && cur_node->children && cur_node->children->content){
          if(!strcmp((char *)cur_node->name,TagName)){
            return cur_node->children;
          }
        }
      }
    }
    a_node = search_content_tag(cur_node->children,TagName);
    if(a_node)
      return a_node;
  }
  return NULL;
}

xmlNodePtr search_elem_tag(xmlNode * a_node, char *TagName){
  xmlNode *cur_node = NULL;
  if(a_node==NULL)
  {
      return NULL;
  }

  for (cur_node = a_node; cur_node; cur_node = cur_node->next)
  {
    if (cur_node->type == XML_ELEMENT_NODE)
    {
      if(cur_node->children->type == XML_TEXT_NODE){
        if(cur_node->name && cur_node->children && cur_node->children->content){
          if(!strcmp((char *)cur_node->name,TagName)){
            return cur_node->children;
          }
        }
      }
    }
    a_node = search_elem_tag(cur_node->children,TagName);
    if(a_node)
      return a_node;
  }
  return NULL;
}


xmlNodePtr getContentByTagName( xmlNodePtr nodes,char *TagName ){
    return search_content_tag(nodes,TagName);
}

xmlNodePtr getElementByTagName( xmlNodePtr nodes,char *TagName ){
    return search_elem_tag(nodes,TagName);
}

xmlNodePtr get_tag_by_namepath(xmlDoc *doc, char *namepath){
  tracelogger_set_func_name("get_tag_by_namepath");
  xmlNodePtr root = xmlDocGetRootElement(doc);
  xmlXPathContextPtr contxt = xmlXPathNewContext(doc);
  xmlXPathObjectPtr node_contxt= xmlXPathEval((xmlChar*)namepath,contxt);

  xmlNodePtr node=NULL;
  if(node_contxt &&
    node_contxt->nodesetval &&
    node_contxt->nodesetval->nodeNr &&
    node_contxt->nodesetval->nodeTab){

    node = node_contxt->nodesetval->nodeTab[0];
  }

  return node;
}
