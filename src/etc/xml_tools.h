xmlNodePtr search_content_tag(xmlNode * a_node, char *TagName);

xmlNodePtr search_elem_tag(xmlNode * a_node, char *TagName);

xmlNodePtr getContentByTagName( xmlNodePtr nodes,char *TagName );

xmlNodePtr getElementByTagName( xmlNodePtr nodes,char *TagName );

xmlNodePtr get_tag_by_namepath(xmlDoc *doc, char *namepath);

int validar_coord_xml(xmlDocPtr doc, char **paths);

xmlNodeSet *get_tags_by_namepath(xmlDoc *doc, char *namepath);