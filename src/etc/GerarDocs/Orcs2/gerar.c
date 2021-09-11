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
    "orc/img_logo",
    "orc/itens/codigo",
    "orc/itens/descricao",
    "orc/itens/unidade",
    "orc/itens/quantidade",
    "orc/itens/valor_unit",
    "orc/itens/subtotal",
    "orc/subtotal",
    "orc/desconto",
    "orc/total",
    "orc/transporte/valor",
    "orc/transporte/desconto",

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

  cairo_rectangle(cairo, MM_TO_POINTS(10), MM_TO_POINTS(0), MM_TO_POINTS(1582), MM_TO_POINTS(1362));
  if(fopen(ORC_MODEL, "r")){
    cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(ORC_MODEL);
    cairo_set_source_surface(cairo, logo_surface ,0,0);
  }else{
    file_logger("Não foi possível ler imagem de fundo gera_doc_orc() -> cairo_image_surface_create_from_png()");
  }
  cairo_fill(cairo);

  int img_logo_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/img_logo/x")));
  int img_logo_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/img_logo/y")));
  cairo_rectangle(cairo, MM_TO_POINTS(10), MM_TO_POINTS(10), MM_TO_POINTS(300), MM_TO_POINTS(80));
  if(fopen(LOGO_PDF, "r")){
    cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(LOGO_PDF);
    cairo_set_source_surface(cairo, logo_surface ,img_logo_x, img_logo_y);
  }else{
    file_logger("Não foi possível ler imagem de logo gera_doc_orc() -> cairo_image_surface_create_from_png()");
  }
  cairo_fill(cairo);

  cairo_move_to(cairo, 0,0 );
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  /*

  cairo_set_font_size(cairo, ORC_TITLE_TEXT_FONT_SIZE);

  gchar *nome_empresa = malloc( strlen(cad_emp_strc.xNome) );
  sprintf(nome_empresa, "%s", cad_emp_strc.xNome);
  cairo_show_text(cairo, nome_empresa);
  cairo_fill(cairo);
  */

  cairo_set_font_size(cairo, ORC_NORMAL_TEXT_FONT_SIZE);
  int orc_code_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/orc_code/x")));
  int orc_code_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/orc_code/y")));
  cairo_move_to(cairo, orc_code_x, orc_code_y);
  gchar num_orc[30];

  sprintf(num_orc, "%i",orc->infos->code );
  cairo_show_text(cairo, num_orc);
  cairo_fill(cairo);

  /*
  int email_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/empresa_email/x")));
  int email_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/empresa_email/y")));
  cairo_move_to(cairo, email_x, email_y);
  gchar *email = malloc( strlen(cad_emp_strc.email) + 20);
  sprintf(email, "%s", cad_emp_strc.email);
  cairo_show_text(cairo, email);
  cairo_fill(cairo);
  */

  int data_emissao_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/data_emissao/x")));
  int data_emissao_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/data_emissao/y")));
  cairo_move_to(cairo, data_emissao_x, data_emissao_y);
  gchar *data_emissao = malloc( strlen(orc->infos->data) + 20);
  sprintf(data_emissao, "%s", orc->infos->data);
  cairo_show_text(cairo, data_emissao);
  cairo_fill(cairo);

  cairo_set_font_size(cairo, ORC_NORMAL_TEXT_FONT_SIZE);
  int nome_cliente_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/nome_cliente/x")));
  int nome_cliente_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/nome_cliente/y")));
  cairo_move_to(cairo, nome_cliente_x, nome_cliente_y);
  gchar *nome_cliente = malloc( strlen(orc->infos->cliente->razao) + 20);
  sprintf(nome_cliente, "%s", orc->infos->cliente->razao);
  cairo_show_text(cairo, nome_cliente);
  cairo_fill(cairo);

  int ender_cliente_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/ender_cliente/x")));
  int ender_cliente_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/ender_cliente/y")));
  cairo_move_to(cairo, ender_cliente_x, ender_cliente_y);


  const int MAX_ENDER_LEN = 70;
  gchar *ender_cliente = malloc(20 + strlen(orc->infos->cliente->xLgr) + strlen(orc->infos->cliente->xBairro) + strlen(orc->infos->cliente->cep) + strlen(orc->infos->cliente->xCpl)+2);
  gchar *cmplt_cliente;
  if(strlen(orc->infos->cliente->xCpl)){
    cmplt_cliente = malloc(strlen(orc->infos->cliente->xCpl)+2);
    sprintf(cmplt_cliente, "(%s)", orc->infos->cliente->xCpl);
  }else{
    cmplt_cliente = strdup("");
  }

  sprintf(ender_cliente, "%s, %s - %s %s, %s", orc->infos->cliente->xLgr, orc->infos->cliente->c_nro ,orc->infos->cliente->xBairro, orc->infos->cliente->cep, cmplt_cliente);
  if(strlen(ender_cliente) >= MAX_ENDER_LEN ){
    ender_cliente[MAX_ENDER_LEN] = '\0';
  }
  cairo_show_text(cairo, ender_cliente);
  cairo_fill(cairo);


  int  cidade_cliente_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/cidade_cliente/x")));
  int  cidade_cliente_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/cidade_cliente/y")));
  cairo_move_to(cairo, cidade_cliente_x, cidade_cliente_y);
  gchar *cidade_cliente = malloc(20+strlen(orc->infos->cliente->xMun)+strlen(orc->infos->cliente->UF));
  sprintf(cidade_cliente, "%s/%s", orc->infos->cliente->xMun, orc->infos->cliente->UF);
  cairo_show_text(cairo, cidade_cliente);
  cairo_fill(cairo);


  int  telefone_cliente_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/telefone_cliente/x")));
  int  telefone_cliente_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/telefone_cliente/y")));
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

  int  contato_cliente_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/contato_cliente/x")));
  int  contato_cliente_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/contato_cliente/y")));
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

  cairo_set_font_size(cairo, ORC_ITENS_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  int interval_pos = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/distancia")));

  int code_pos_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/codigo/x")));
  int code_pos_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/codigo/y")));

  int descricao_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/descricao/x")));
  int descricao_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/descricao/y")));

  int und_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/unidade/x")));
  int und_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/unidade/y")));

  int qtde_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/quantidade/x")));
  int qtde_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/quantidade/y")));

  int vlr_unit_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/valor_unit/x")));
  int vlr_unit_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/valor_unit/y")));

  int itens_subtotal_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/subtotal/x")));
  int itens_subtotal_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/itens/subtotal/y")));

  for(int cont=0;cont<orc->itens_qnt;cont++){

    char *format = malloc(strlen(orc->itens[cont]->_produto->xNome));
    sprintf(format, "%i", orc->itens[cont]->_produto->code);
    cairo_move_to(cairo, code_pos_x, code_pos_y);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);
    free(format);

    cairo_move_to(cairo, descricao_x, descricao_y);
    int prod_name_len = strlen(orc->itens[cont]->_produto->xNome);
    gchar prod_name[prod_name_len];
    const int PDF_MAX_PROD_LEN = 30;
    strcpy(prod_name, orc->itens[cont]->_produto->xNome);
    if(prod_name_len > PDF_MAX_PROD_LEN){
      prod_name[PDF_MAX_PROD_LEN] = '\0';
    }
    cairo_show_text(cairo, prod_name);
    cairo_fill(cairo);

    cairo_move_to(cairo, und_x, und_y);
    format = malloc(strlen(orc->itens[cont]->_produto->und->nome));
    sprintf(format, "%s", orc->itens[cont]->_produto->und->nome);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);
    free(format);

    cairo_move_to(cairo, qtde_x, qtde_y);
    format = malloc(20);
    sprintf(format, "%.2f", orc->itens[cont]->qnt_f);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);

    cairo_move_to(cairo, vlr_unit_x, vlr_unit_y);
    format = malloc(20);
    sprintf(format, "R$ %.2f", orc->itens[cont]->preco_f);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);
    free(format);

    float subtotal = 0.00;
    subtotal = orc->itens[cont]->preco_f * orc->itens[cont]->qnt_f;
    cairo_move_to(cairo, itens_subtotal_x, itens_subtotal_y);
    format = malloc(20);
    sprintf(format, "R$ %.2f", subtotal);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);
    free(format);

    code_pos_y += interval_pos;
    und_y += interval_pos;
    descricao_y += interval_pos;
    vlr_unit_y += interval_pos;
    qtde_y += interval_pos;
    itens_subtotal_y += interval_pos;

  }

  gchar *format = malloc(20);
  int subtotal_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/subtotal/x")));
  int subtotal_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/subtotal/y")));
  cairo_move_to(cairo, subtotal_x, subtotal_y);
  sprintf(format, "R$ %.2f", orc->valores->valor_prds);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);

  int desconto_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/desconto/x")));
  int desconto_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/desconto/y")));
  cairo_move_to(cairo, desconto_x, desconto_y);
  sprintf(format, "R$ %.2f", orc->valores->valor_prds_desc);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);

  int transp_vlr_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/transporte/valor/x")));
  int transp_vlr_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/transporte/valor/y")));
  cairo_move_to(cairo, transp_vlr_x, transp_vlr_y);
  sprintf(format, "R$ %.2f", orc->valores->valor_frete);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);

  int transp_descvlr_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/transporte/desconto/x")));
  int transp_descvlr_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/transporte/desconto/y")));
  cairo_move_to(cairo, transp_descvlr_x, transp_descvlr_y);
  sprintf(format, "R$ %.2f", orc->valores->desconto_frete);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);

  int total_x = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/total/x")));
  int total_y = atoi((const char *)xmlNodeGetContent(get_tag_by_namepath(doc,"/orc/total/y")));
  cairo_move_to(cairo, total_x, total_y);
  sprintf(format, "R$ %.2f", orc->valores->valor_total_liquido);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);
  free(format);

  cairo_move_to(cairo, 0, 0);
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  format = malloc(strlen(orc->parcelas->condpag->nome) + 30);
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
