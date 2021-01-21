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

  cairo_rectangle(cairo, MM_TO_POINTS(5), MM_TO_POINTS(5), MM_TO_POINTS(584), MM_TO_POINTS(831));
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(6), MM_TO_POINTS(582), MM_TO_POINTS(132));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(10), MM_TO_POINTS(10), MM_TO_POINTS(582), MM_TO_POINTS(362));
  if(fopen(LOGO_MEDIA, "r")){
    cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(LOGO_MEDIA);
    cairo_set_source_surface(cairo, logo_surface ,10,10);
  }
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_EMP_INFOS_HPOS, ORC_EMP_INFOS_VPOS );
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  gchar *nome_empresa = malloc( strlen(cad_emp_strc.xNome) );
  sprintf(nome_empresa, "%s", cad_emp_strc.xNome);
  cairo_show_text(cairo, nome_empresa);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_EMP_INFOS_HPOS+450, ORC_EMP_INFOS_VPOS);
  gchar *num_orc = malloc(20 + 12);
  sprintf(num_orc, "Orçamento Nº: %i", orc->infos->code);
  cairo_show_text(cairo, num_orc);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_EMP_INFOS_HPOS, ORC_EMP_INFOS_VPOS+30);
  gchar *email = malloc( strlen(cad_emp_strc.email) + 20);
  sprintf(email, "Email: %s", cad_emp_strc.email);
  cairo_show_text(cairo, email);
  cairo_fill(cairo);


  cairo_move_to(cairo, ORC_EMP_INFOS_HPOS+450, ORC_EMP_INFOS_VPOS+30);
  gchar *data_emissao = malloc( strlen(orc->infos->data) + 20);
  sprintf(data_emissao, "Data: %s", orc->infos->data);
  cairo_show_text(cairo, data_emissao);
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(139), MM_TO_POINTS(582), MM_TO_POINTS(22));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, 500.0, 310.0);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Orçamento");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(162), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_CLI_INFOS_HPOS, ORC_CLI_INFOS_VPOS + 30);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  gchar *nome_cliente = malloc( strlen(orc->infos->cliente->razao) + 20);
  sprintf(nome_cliente, "Cliente: %s", orc->infos->cliente->razao);
  cairo_show_text(cairo, nome_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_CLI_INFOS_HPOS, ORC_CLI_INFOS_VPOS + 60);
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

  cairo_move_to(cairo, ORC_CLI_INFOS_HPOS, ORC_CLI_INFOS_VPOS + 90);
  gchar *cidade_cliente = malloc(20+strlen(orc->infos->cliente->xMun)+strlen(orc->infos->cliente->UF));
  sprintf(cidade_cliente, "Cidade: %s/%s", orc->infos->cliente->xMun, orc->infos->cliente->UF);
  cairo_show_text(cairo, cidade_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_CLI_INFOS_HPOS, ORC_CLI_INFOS_VPOS + 120);
  gchar *telefone_cliente;
  if(orc->infos->cliente->contatos_qnt){
    telefone_cliente = malloc(20+strlen(orc->infos->cliente->contatos[0].telefone));
    sprintf(telefone_cliente, "Fone: %s", orc->infos->cliente->contatos[0].telefone);
  }else{
    telefone_cliente = strdup("Fone: Não possui");
  }
  cairo_show_text(cairo, telefone_cliente);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_CLI_INFOS_HPOS, ORC_CLI_INFOS_VPOS + 150);
  gchar *contato_cliente;
  if(orc->infos->cliente->contatos_qnt){
    contato_cliente = malloc(20+strlen(orc->infos->cliente->contatos[0].nome));
    sprintf(contato_cliente, "Contato: %s", orc->infos->cliente->contatos[0].nome);
  }else{
    contato_cliente = strdup("Contato: Não possui");
  }
  cairo_show_text(cairo, contato_cliente);
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(243), MM_TO_POINTS(582), MM_TO_POINTS(60));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS, ASS_ORC_VPOS);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Autorizado por: ____________________");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS+500, ASS_ORC_VPOS);
  cairo_show_text(cairo, "Conferido por:  ____________________");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(304), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS, ASS_ORC_VPOS+50);
  cairo_set_font_size(cairo, DESCR_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Preecher no recebimento dos materiais:");
  cairo_fill(cairo);

  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);

  cairo_move_to(cairo, ASS_ORC_HPOS, ASS_ORC_VPOS+100);
  cairo_show_text(cairo, "NF Nº: __________");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS+300, ASS_ORC_VPOS+100);
  cairo_show_text(cairo, "Data Entrada: __/__/____");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS+700, ASS_ORC_VPOS+100);
  cairo_show_text(cairo, "Data Vencimento: __/__/____");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS, ASS_ORC_VPOS+170);
  cairo_show_text(cairo, "NF Nº: __________");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS+300, ASS_ORC_VPOS+170);
  cairo_show_text(cairo, "Data Entrada: __/__/____");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORC_HPOS+700, ASS_ORC_VPOS+170);
  cairo_show_text(cairo, "Data Vencimento: __/__/____");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(385), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_ENTRGA_HPOS, ORC_ENTRGA_VPOS);
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Condições de Entrega:");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(466), MM_TO_POINTS(582), MM_TO_POINTS(200));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_ITENS_HPOS, ORC_ITENS_VPOS);
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Itens Solicitados:");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(20), MM_TO_POINTS(490), MM_TO_POINTS(550), MM_TO_POINTS(20));
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_fill(cairo);

  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_move_to(cairo,  MM_TO_POINTS(25), MM_TO_POINTS(505));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_show_text(cairo, "Nome Produto");
  cairo_fill(cairo);

  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_move_to(cairo,  MM_TO_POINTS(220), MM_TO_POINTS(505));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_show_text(cairo, "Quantidade");
  cairo_fill(cairo);

  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_move_to(cairo,  MM_TO_POINTS(400), MM_TO_POINTS(505));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_show_text(cairo, "Valor");
  cairo_fill(cairo);

  int pos=ORC_ITENS_VPOS+80;
  cairo_set_font_size(cairo, ITENS_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  for(int cont=0;cont<orc->itens_qnt;cont++){

    char *format = malloc(strlen(orc->itens[cont]->_produto->xNome));
    cairo_move_to(cairo, ORC_ITENS_HPOS, pos);
    cairo_show_text(cairo, orc->itens[cont]->_produto->xNome);
    cairo_fill(cairo);

    cairo_move_to(cairo, ORC_ITENS_HPOS+400, pos);
    sprintf(format, "%.2f %s", orc->itens[cont]->qnt_f, orc->itens[cont]->_produto->und->nome);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);

    cairo_move_to(cairo, ORC_ITENS_HPOS+740, pos);
    sprintf(format, "R$ %.2f", orc->itens[cont]->preco_f);
    cairo_show_text(cairo, format);
    cairo_fill(cairo);

    pos += 30;
  }

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(667), MM_TO_POINTS(582), MM_TO_POINTS(200));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_move_to(cairo, ORC_CONDPAG_HPOS, ORC_CONDPAG_VPOS);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Condições de Pagamento:");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(20), MM_TO_POINTS(700), MM_TO_POINTS(550), MM_TO_POINTS(20));
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORC_CONDPAG_HPOS + 20, ORC_CONDPAG_VPOS + 50);
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  char *format = malloc(strlen(orc->parcelas->condpag->nome) + 30);
  sprintf(format, " %s | %i x R$ %.2f", orc->parcelas->condpag->nome, orc->parcelas->condpag->parcelas_qnt, orc->valores->valor_total);
  cairo_show_text(cairo, format);
  cairo_fill(cairo);

  int h_pos=0, v_pos=50, i_pos=0;
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  for(int cont=0;cont< orc->parcelas->condpag->parcelas_qnt; cont++){

    cairo_move_to(cairo, ORC_CONDPAG_HPOS + 20  + h_pos, ORC_CONDPAG_VPOS + 50 + v_pos);

    gchar *parc = malloc( strlen(orc->parcelas->datas[cont]) + 30 );
    sprintf(parc, "| %iº %s R$ %.2f |", cont+1, orc->parcelas->datas[cont], orc->parcelas->vlrs[cont]);
    cairo_show_text(cairo, parc);
    cairo_fill(cairo);

    if(i_pos > 1){
      i_pos = 0;
      h_pos = 0;
      v_pos += 50;
    }else{
      h_pos+=350;
      i_pos++;
    }
  }

  //cairo_show_page(cairo);
  //cairo_destroy(cairo);

  //cairo_surface_flush(surface);
  //cairo_surface_destroy(surface);

  return 0;
}
