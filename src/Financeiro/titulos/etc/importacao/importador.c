int import_tits(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(janela,"importador_tits");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Importador");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"avatar-default");
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  /*registrando a janela para o reg_win*/
  janelas_gerenciadas.vetor_janelas[IMPORT_TITS_WND].reg_id = IMPORT_TITS_WND;
  janelas_gerenciadas.vetor_janelas[IMPORT_TITS_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[IMPORT_TITS_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[IMPORT_TITS_WND].janela_pointer = janela;

  imprt_tits_choose = gtk_file_chooser_button_new("Escolher Arquivo",GTK_FILE_CHOOSER_ACTION_OPEN);
  imprt_tits_entry = gtk_entry_new();
  GtkWidget *imprt_tits_frame = gtk_frame_new("Importar do arquivo");
  GtkWidget *imprt_tits_fixed = gtk_fixed_new();
  GtkWidget *imprt_tits_box = gtk_box_new(0,0);
  GtkWidget *box = gtk_box_new(1,0);
  GtkWidget *caixa_opcoes = gtk_box_new(0,0);
  imprt_tits_tipo_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_insert_text( GTK_COMBO_BOX_TEXT(imprt_tits_tipo_combo), 0, "Todos");
  gtk_combo_box_text_insert_text( GTK_COMBO_BOX_TEXT(imprt_tits_tipo_combo), TP_TIT_REC, "Recebidos");
  gtk_combo_box_text_insert_text( GTK_COMBO_BOX_TEXT(imprt_tits_tipo_combo), TP_TIT_PAG, "Pagos");
  gtk_combo_box_set_active(GTK_COMBO_BOX(imprt_tits_tipo_combo), 0);

  gtk_box_pack_start(GTK_BOX(imprt_tits_box),imprt_tits_choose,0,0,5);
  gtk_box_pack_start(GTK_BOX(imprt_tits_box),imprt_tits_entry,0,0,5);
  gtk_container_add(GTK_CONTAINER(imprt_tits_frame),imprt_tits_box);
  gtk_fixed_put(GTK_FIXED(imprt_tits_fixed),imprt_tits_frame,10,10);

  imprt_tits_analisar_button = gtk_button_new_with_label("Analisar");
  gtk_button_set_image(GTK_BUTTON( imprt_tits_analisar_button ),gtk_image_new_from_file(IMG_OK));
  imprt_tits_cancelar_button = gtk_button_new_with_label("Limpar");
  gtk_button_set_image(GTK_BUTTON( imprt_tits_cancelar_button ),gtk_image_new_from_file(IMG_CANCEL));
  imprt_tits_importar_button = gtk_button_new_with_label("Importar");
  gtk_button_set_image(GTK_BUTTON( imprt_tits_importar_button ),gtk_image_new_from_file(IMG_GERA));
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),imprt_tits_analisar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),imprt_tits_cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),imprt_tits_importar_button,0,0,5);
  

  gtk_box_pack_start(GTK_BOX(box),imprt_tits_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),imprt_tits_tipo_combo,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),caixa_opcoes,0,0,5);

  gtk_container_add(GTK_CONTAINER(janela),box);

  g_signal_connect(imprt_tits_choose,"file-set",G_CALLBACK(get_filename_to_entry),imprt_tits_entry);
  g_signal_connect(imprt_tits_analisar_button,"clicked",G_CALLBACK(import_tits_iniciar),NULL);
  g_signal_connect(imprt_tits_importar_button,"clicked",G_CALLBACK(import_tits_importar),NULL);
  
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[IMPORT_TITS_WND]);

  gtk_widget_show_all(janela);
  return 0;
}
