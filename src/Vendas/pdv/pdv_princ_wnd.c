int pdv_princ_wnd(){

  if(!caixas_qnt()){
    if(janela_criar_caixa())
      return 1;
  }

  struct _maquina *maquina_atual = maquinas_get_atual();
  if(!maquina_atual){
    return 1;
  }

  struct _caixa *caixa = caixa_get_aberto(maquina_atual);
  if(!caixa){
    return 1;
  }

  if(caixa->status == CAIXA_FECHADO){
    if(janela_abrir_caixa(maquina_atual, caixa))
      return 1;

    struct _caixa *caixa = caixa_get_aberto(maquina_atual);
  }


  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(janela,"janela_pdv");
  gtk_widget_hide_on_delete(janela);
  gtk_window_maximize(GTK_WINDOW(janela));
  gtk_window_set_decorated(GTK_WINDOW(janela),FALSE);
  gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].reg_id = REG_PDV_WND;
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_PDV_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_PDV_WND].janela_pointer = janela;

  GtkWidget *caixa_principal = gtk_box_new(1,0);
  GtkWidget *container_pdv_principal = gtk_box_new(0,0);
  GtkWidget *container_pdv_logo = gtk_box_new(0,0);
  GtkWidget *pdv_logo_img = gtk_image_new_from_file(PDV_LOGO);
  gtk_box_pack_start(GTK_BOX(container_pdv_logo),pdv_logo_img,0,0,0);
  gtk_box_pack_start(GTK_BOX(container_pdv_principal),container_pdv_logo,0,0,5);

  GtkWidget *logoheader_pdv = gtk_image_new_from_file(LOGO_HEADER);
  gtk_widget_set_name(logoheader_pdv,"logoheader");
  GtkWidget *header_layout = gtk_layout_new(NULL,NULL);
  GtkWidget *fechar_button = gtk_button_new();
  GtkWidget *encerrar_caixa = gtk_button_new_with_label("Encerrar Caixa");
  gtk_button_set_image(GTK_BUTTON(fechar_button),gtk_image_new_from_file(IMG_CANCEL));

  GtkWidget *container_pdv = gtk_box_new(1,0);
  gtk_box_pack_start(GTK_BOX(container_pdv_principal),container_pdv,0,0,5);

  GtkWidget *footer_pdv = gtk_box_new(0,0);
  GtkWidget *opcoes_header = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(opcoes_header),encerrar_caixa,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_header),fechar_button,0,0,5);

  gtk_layout_put(GTK_LAYOUT(header_layout),logoheader_pdv,0,0);
  gtk_layout_put(GTK_LAYOUT(header_layout),opcoes_header,1100,15);

  gtk_widget_set_size_request(header_layout,1366,90);



  gtk_box_pack_start(GTK_BOX(caixa_principal),header_layout,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_principal),container_pdv_principal,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_principal),footer_pdv,0,0,0);

  gtk_container_add(GTK_CONTAINER(janela),caixa_principal);
  gtk_widget_show_all(janela);

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_PDV_WND]);
  g_signal_connect(encerrar_caixa,"clicked",G_CALLBACK(signal_caixa_encerramento),caixa);
  g_signal_connect(fechar_button,"clicked",G_CALLBACK(close_window_callback),janela);
  return 0;
}
