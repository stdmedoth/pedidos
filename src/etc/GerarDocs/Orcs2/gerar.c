int gera_doc_orc(struct _orc *orc, GtkPrintContext *context){

  PangoLayout *pango_layout;
  PangoFontDescription *pango_desc;
  if(!orc){
    file_logger("Não foi possível receber estrutura do orcamento na impressao");
    return 1;
  }

  xmlDocPtr doc = xmlParseFile(ORC_TXTPOS);
  if(!doc){
    popup(NULL,"Não foi possível ler posicões do orçamento");
    return 1;
  }

  gchar *paths[] = {
    "orc/orc_code", 
    "orc/email", 
    "orc/nome_cliente", 
    "orc/cidade_cliente", 
    "orc/ender_cliente", 
    "orc/telefone_cliente", 
    "orc/contato_cliente",
    NULL
  };

  if(validar_coord_xml(doc, paths)){
    popup(NULL, "Faltam posições de campos para o PDF");
    return 1;
  }

  //xmlNodePtr root = xmlDocGetRootElement(doc);

  //cairo_surface_t *surface = cairo_pdf_surface_create(ORC_PDF_FILE, MM_TO_POINTS(594), MM_TO_POINTS(841));
  //cairo_t *cairo = cairo_create(surface);
  cairo_t *cairo = gtk_print_context_get_cairo_context(context);


  cairo_rectangle(cairo, MM_TO_POINTS(10), MM_TO_POINTS(10), MM_TO_POINTS(1582), MM_TO_POINTS(1362));
  if(fopen(ORC_MODEL, "r")){
    cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(ORC_MODEL);
    cairo_set_source_surface(cairo, logo_surface ,0,0);
  }else{
    file_logger("Não foi possível ler imagem de fundo gera_doc_orc() -> cairo_image_surface_create_from_png()");
  }
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(40), MM_TO_POINTS(10), MM_TO_POINTS(300), MM_TO_POINTS(50));
  if(fopen(LOGO_MEDIA, "r")){
    cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(LOGO_PDF);
    cairo_set_source_surface(cairo, logo_surface ,0,0);
  }else{
    file_logger("Não foi possível ler imagem de logo gera_doc_orc() -> cairo_image_surface_create_from_png()");
  }
  cairo_fill(cairo);

  cairo_move_to(cairo, 0,0 );
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  gchar *nome_empresa = malloc( strlen(cad_emp_strc.xNome) );
  sprintf(nome_empresa, "%s", cad_emp_strc.xNome);
  cairo_show_text(cairo, nome_empresa);
  cairo_fill(cairo);

  int orc_code_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/orc_code/x")));
  int orc_code_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/orc_code/y")));
  cairo_move_to(cairo, orc_code_x, orc_code_y);
  gchar num_orc[30];

  sprintf(num_orc, "%i",orc->infos->code );
  cairo_show_text(cairo, num_orc);
  cairo_fill(cairo);

  int email_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/email/x")));
  int email_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/email/y")));
  cairo_move_to(cairo, email_x, email_y);
  gchar *email = malloc( strlen(cad_emp_strc.email) + 20);
  sprintf(email, "%s", cad_emp_strc.email);
  cairo_show_text(cairo, email);
  cairo_fill(cairo);

  int data_emissao_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/data_emissao/x")));
  int data_emissao_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/data_emissao/y")));
  cairo_move_to(cairo, data_emissao_x, data_emissao_y);
  gchar *data_emissao = malloc( strlen(orc->infos->data) + 20);
  sprintf(data_emissao, "%s", orc->infos->data);
  cairo_show_text(cairo, data_emissao);
  cairo_fill(cairo);


  int nome_cliente_x = atoi((const char *)get_tag_by_namepath(doc,"/orc/nome_cliente/x"));
  int nome_cliente_y = atoi((const char *)get_tag_by_namepath(doc,"/orc/nome_cliente/y"));
  cairo_move_to(cairo, nome_cliente_x, nome_cliente_y);
  gchar *nome_cliente = malloc( strlen(orc->infos->cliente->razao) + 20);
  sprintf(nome_cliente, "%s", orc->infos->cliente->razao);
  cairo_show_text(cairo, nome_cliente);
  cairo_fill(cairo);

  int ender_cliente_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/ender_cliente/x")));
  int ender_cliente_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/ender_cliente/y")));
  cairo_move_to(cairo, ender_cliente_x, ender_cliente_y);
  gchar *ender_cliente = malloc(20+strlen(orc->infos->cliente->xLgr)+strlen(orc->infos->cliente->xBairro)+strlen(orc->infos->cliente->xCpl)+2);
  gchar *cmplt_cliente;
  if(strlen(orc->infos->cliente->xCpl)){
    cmplt_cliente = malloc(strlen(orc->infos->cliente->xCpl)+2);
    sprintf(cmplt_cliente, "(%s)", orc->infos->cliente->xCpl);
  }else{
    cmplt_cliente = strdup("");
  }
  sprintf(ender_cliente, "%s, %s - %s %s", orc->infos->cliente->xLgr, orc->infos->cliente->c_nro ,orc->infos->cliente->xBairro, cmplt_cliente);
  cairo_show_text(cairo, ender_cliente);
  cairo_fill(cairo);


  int  cidade_cliente_x = atoi((const char *)get_tag_by_namepath(doc,"/orc/cidade_cliente/x"));
  int  cidade_cliente_y = atoi((const char *)get_tag_by_namepath(doc,"/orc/cidade_cliente/y"));
  cairo_move_to(cairo, cidade_cliente_x, cidade_cliente_y);
  gchar *cidade_cliente = malloc(20+strlen(orc->infos->cliente->xMun)+strlen(orc->infos->cliente->UF));
  sprintf(cidade_cliente, "Cidade: %s/%s", orc->infos->cliente->xMun, orc->infos->cliente->UF);
  cairo_show_text(cairo, cidade_cliente);
  cairo_fill(cairo);


  int  telefone_cliente_x = atoi((const char *)get_tag_by_namepath(doc,"/orc/telefone_cliente/x"));
  int  telefone_cliente_y = atoi((const char *)get_tag_by_namepath(doc,"/orc/telefone_cliente/y"));
  cairo_move_to(cairo, telefone_cliente_x, telefone_cliente_y);
  gchar *telefone_cliente;
  if(orc->infos->cliente->contatos_qnt){
    telefone_cliente = malloc(20+strlen(orc->infos->cliente->contatos[0].telefone));
    sprintf(telefone_cliente, "Fone: %s", orc->infos->cliente->contatos[0].telefone);
  }else{
    telefone_cliente = strdup("Fone: Não possui");
  }
  cairo_show_text(cairo, telefone_cliente);
  cairo_fill(cairo);

  int  contato_cliente_x = atoi((const char *)get_tag_by_namepath(doc,"/orc/contato_cliente/x"));
  int  contato_cliente_y = atoi((const char *)get_tag_by_namepath(doc,"/orc/contato_cliente/y"));
  cairo_move_to(cairo, contato_cliente_x, contato_cliente_y);
  gchar *contato_cliente;
  if(orc->infos->cliente->contatos_qnt){
    contato_cliente = malloc(20+strlen(orc->infos->cliente->contatos[0].nome));
    sprintf(contato_cliente, "Contato: %s", orc->infos->cliente->contatos[0].nome);
  }else{
    contato_cliente = strdup("Contato: Não possui");
  }
  cairo_show_text(cairo, contato_cliente);
  cairo_fill(cairo);

  cairo_set_font_size(cairo, ITENS_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  for(int cont=0;cont<orc->itens_qnt;cont++){

    char *format = malloc(strlen(orc->itens[cont]->_produto->xNome));
    cairo_move_to(cairo, 0, 0);
    cairo_show_text(cairo, orc->itens[cont]->_produto->xNome);
    cairo_fill(cairo);

    cairo_move_to(cairo, 0, 0);
    sprintf(format, "%.2f %s", orc->itens[cont]->qnt_f, orc->itens[cont]->_produto->und->nome);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);

    cairo_move_to(cairo, 0, 0);
    sprintf(format, "R$ %.2f", orc->itens[cont]->preco_f);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);

  }

  cairo_move_to(cairo, 0, 0);
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  char *format = malloc(strlen(orc->parcelas->condpag->nome) + 30);
  sprintf(format, " %s | %i x R$ %.2f", orc->parcelas->condpag->nome, orc->parcelas->condpag->parcelas_qnt, orc->valores->valor_total);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);
    
  const int pdf_parcelas_limit = 12;
  for(int cont=0;cont< orc->parcelas->condpag->parcelas_qnt; cont++){

    if(cont >= pdf_parcelas_limit)
      break;

    //parcelas alocadas em vertical e horizontal
    cairo_move_to(cairo, 0, 0);
    gchar *parc = malloc( strlen(orc->parcelas->datas[cont]) + 30 );
    sprintf(parc, "| %iº %s R$ %.2f |", cont+1, orc->parcelas->datas[cont], orc->parcelas->vlrs[cont]);
    cairo_show_text(cairo, parc);
    cairo_fill(cairo);

  }

  //cairo_show_page(cairo);
  //cairo_destroy(cairo);

  //cairo_surface_flush(surface);
  //cairo_surface_destroy(surface);

  return 0;
}
