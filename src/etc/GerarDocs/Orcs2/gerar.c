int gera_doc_orc(struct _orc *orc, GtkPrintContext *context){

  PangoLayout *pango_layout;
  PangoFontDescription *pango_desc;
  if(!orc){
    file_logger("Não foi possível receber estrutura do orcamento na impressao");
    return 1;
  }

  //cairo_surface_t *surface = cairo_pdf_surface_create(ORC_PDF_FILE, MM_TO_POINTS(594), MM_TO_POINTS(841));
  //cairo_t *cairo = cairo_create(surface);
  cairo_t *cairo = gtk_print_context_get_cairo_context(context);


  cairo_rectangle(cairo, MM_TO_POINTS(10), MM_TO_POINTS(10), MM_TO_POINTS(582), MM_TO_POINTS(362));
  if(fopen(LOGO_MEDIA, "r")){
    cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(LOGO_MEDIA);
    cairo_set_source_surface(cairo, logo_surface ,10,10);
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

  cairo_move_to(cairo, 0,0 );
  gchar num_orc[30];
  sprintf(num_orc, "Orçamento Nº: %i",orc->infos->code );
  cairo_show_text(cairo, num_orc);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  gchar *email = malloc( strlen(cad_emp_strc.email) + 20);
  sprintf(email, "Email: %s", cad_emp_strc.email);
  cairo_show_text(cairo, email);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0,0);
  gchar *data_emissao = malloc( strlen(orc->infos->data) + 20);
  sprintf(data_emissao, "Data: %s", orc->infos->data);
  cairo_show_text(cairo, data_emissao);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Orçamento");
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  gchar *nome_cliente = malloc( strlen(orc->infos->cliente->razao) + 20);
  sprintf(nome_cliente, "Cliente: %s", orc->infos->cliente->razao);
  cairo_show_text(cairo, nome_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  gchar *ender_cliente = malloc(20+strlen(orc->infos->cliente->xLgr)+strlen(orc->infos->cliente->xBairro)+strlen(orc->infos->cliente->xCpl)+2);
  gchar *cmplt_cliente;
  if(strlen(orc->infos->cliente->xCpl)){
    cmplt_cliente = malloc(strlen(orc->infos->cliente->xCpl)+2);
    sprintf(cmplt_cliente, "(%s)", orc->infos->cliente->xCpl);
  }else{
    cmplt_cliente = strdup("");
  }
  sprintf(ender_cliente, "Endereço: %s, %s - %s %s", orc->infos->cliente->xLgr, orc->infos->cliente->c_nro ,orc->infos->cliente->xBairro, cmplt_cliente);
  cairo_show_text(cairo, ender_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  gchar *cidade_cliente = malloc(20+strlen(orc->infos->cliente->xMun)+strlen(orc->infos->cliente->UF));
  sprintf(cidade_cliente, "Cidade: %s/%s", orc->infos->cliente->xMun, orc->infos->cliente->UF);
  cairo_show_text(cairo, cidade_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  gchar *telefone_cliente;
  if(orc->infos->cliente->contatos_qnt){
    telefone_cliente = malloc(20+strlen(orc->infos->cliente->contatos[0].telefone));
    sprintf(telefone_cliente, "Fone: %s", orc->infos->cliente->contatos[0].telefone);
  }else{
    telefone_cliente = strdup("Fone: Não possui");
  }
  cairo_show_text(cairo, telefone_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  gchar *contato_cliente;
  if(orc->infos->cliente->contatos_qnt){
    contato_cliente = malloc(20+strlen(orc->infos->cliente->contatos[0].nome));
    sprintf(contato_cliente, "Contato: %s", orc->infos->cliente->contatos[0].nome);
  }else{
    contato_cliente = strdup("Contato: Não possui");
  }
  cairo_show_text(cairo, contato_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, 0, 0);
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Condições de Entrega:");
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
