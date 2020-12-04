int mkt_mail_montar_fun(){

  gchar *body1=NULL, *body2=NULL, *body3=NULL;
  FILE *arquivo = fopen(TMPFILE_PATH, "wb");
  if(!arquivo){
    popup(NULL,"Não foi possível abrir arquivo temporário");
    return 1;
  }
  gchar *css_filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(mkt_mail_css_path_choose));
  gchar *title = (gchar *)gtk_entry_get_text(GTK_ENTRY(mkt_mail_title_entry));
  GtkTextIter inicio, fim;

  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_editorbody1_view));
  if(buffer){
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &inicio, &fim);
    body1 = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &inicio, &fim, TRUE);
  }


  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_editorbody2_view));
  if(buffer){
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &inicio, &fim);
    body2 = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &inicio, &fim, TRUE);
  }

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_editorbody3_view));
  if(buffer){
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &inicio, &fim);
    body3 = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &inicio, &fim, TRUE);
  }

  /*buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_editorfooter_view));
  if(buffer){
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &inicio, &fim);
    gchar *footer = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &inicio, &fim, TRUE);
  }*/

  gchar *headerimg = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(mkt_mail_css_path_choose));

  //gchar *backimg = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(mkt_mail_backimg_path_choose));

  xmlDocPtr document = xmlNewDoc((xmlChar*)"");
  xmlNodePtr htmlTag = xmlNewNode(NULL,(xmlChar*)"html");
  xmlNodePtr headTag = xmlNewNode(NULL,(xmlChar*)"head");
  xmlNodePtr bodyTag = xmlNewNode(NULL,(xmlChar*)"body");
  xmlNodePtr footerTag = xmlNewNode(NULL,(xmlChar*)"footer");

  xmlAddChild(htmlTag, headTag);
  xmlAddChild(htmlTag, bodyTag);
  xmlAddChild(htmlTag, footerTag);

  xmlNodePtr meta = xmlNewNode(NULL,(xmlChar*)"meta");
  xmlSetProp(meta, (xmlChar*) "http-equiv", (xmlChar*)"Content-Type");
  xmlSetProp(meta, (xmlChar*) "content", (xmlChar*)"text/html");
  xmlSetProp(meta, (xmlChar*) "charset", (xmlChar*)"UTF-8");
  xmlAddChild(headTag, meta);

  xmlNodePtr style = xmlNewNode(NULL,(xmlChar*)"style");
  if(css_filename && strlen(css_filename)){
    char *contents = malloc(1024*1024*4);

    FILE *cssfile = fopen(css_filename, "r");
    if(!cssfile){
      popup(NULL,"Stylesheets não encontrado");
      return 1;
    }
    fread(contents, 1024*1024*4, 1, cssfile);
    xmlNodeAddContent(style, (xmlChar*)contents);
    xmlAddChild(headTag, style);
  }

  if(title && strlen(title)){
    xmlNodePtr titleTag = xmlNewNode(NULL,(xmlChar*)"h1");
    xmlNodeAddContent(titleTag, (xmlChar*)title);
    xmlNodePtr div = xmlNewNode(NULL,(xmlChar*)"div");
    xmlSetProp(div, (xmlChar*) "class", (xmlChar*)"titulo");
    xmlAddChild(div, titleTag);
    xmlAddChild(bodyTag, div);
  }
  xmlNodePtr tableTag = xmlNewNode(NULL,(xmlChar*)"table");
  xmlSetProp(tableTag, (xmlChar*) "cellpadding", (xmlChar*) "0");
  xmlSetProp(tableTag, (xmlChar*) "cellspacing", (xmlChar*) "0");

  if(body1 && strlen(body1)){
    xmlNodePtr tr = xmlNewNode(NULL,(xmlChar*)"tr");
    xmlSetProp(tr, (xmlChar*) "class", (xmlChar*)"corpo1");
    xmlNodePtr td = xmlNewNode(NULL,(xmlChar*)"td");

    xmlNodePtr p = xmlNewNode(NULL,(xmlChar*)"p");
    xmlNodeAddContent(p, (xmlChar*)body1);

    xmlAddChild(td, p);
    xmlAddChild(tr, td);
    xmlAddChild(tableTag, tr);
  }
  if(body2 && strlen(body2)){
    xmlNodePtr tr = xmlNewNode(NULL,(xmlChar*)"tr");
    xmlSetProp(tr, (xmlChar*) "class", (xmlChar*)"corpo2");
    xmlNodePtr td = xmlNewNode(NULL,(xmlChar*)"td");

    xmlNodePtr p = xmlNewNode(NULL,(xmlChar*)"p");
    xmlNodeAddContent(p, (xmlChar*)body2);

    xmlAddChild(td, p);
    xmlAddChild(tr, td);
    xmlAddChild(tableTag, tr);
  }
  if(body3 && strlen(body3)){
    xmlNodePtr tr = xmlNewNode(NULL,(xmlChar*)"tr");
    xmlSetProp(tr, (xmlChar*) "class", (xmlChar*)"corpo3");
    xmlNodePtr td = xmlNewNode(NULL,(xmlChar*)"td");

    xmlNodePtr p = xmlNewNode(NULL,(xmlChar*)"p");
    xmlNodeAddContent(p, (xmlChar*)body3);

    xmlAddChild(td, p);
    xmlAddChild(tr, td);
    xmlAddChild(tableTag, tr);
  }
  xmlAddChild(bodyTag, tableTag);

  xmlDocSetRootElement(document, htmlTag);
  int mem;
  xmlBufferPtr xmlbuf = xmlBufferCreate();
  if(xmlNodeDump(xmlbuf, document, headTag, 1,1)){
    gchar *content = (gchar*) xmlBufferContent(xmlbuf);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_header_view));
    gtk_text_buffer_set_text(buffer, (gchar*)content, strlen((gchar*)content));
  }
  xmlBufferEmpty(xmlbuf);
  if(xmlNodeDump(xmlbuf, document, bodyTag, 1,1)){
    gchar *content = (gchar*) xmlBufferContent(xmlbuf);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_corpo_view));
    gtk_text_buffer_set_text(buffer, (gchar*)content, strlen((gchar*)content));
  }
  xmlBufferEmpty(xmlbuf);
  if(xmlNodeDump(xmlbuf, document, footerTag, 1,1)){
    gchar *content = (gchar*) xmlBufferContent(xmlbuf);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_footer_view));
    gtk_text_buffer_set_text(buffer, (gchar*)content, strlen((gchar*)content));
  }


  return 0;
}
