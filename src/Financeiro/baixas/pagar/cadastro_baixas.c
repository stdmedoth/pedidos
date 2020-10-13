int cad_baixas_pagar(){

  GtkWidget *cad_bxs_pag_code_box;
  GtkWidget *cad_bxs_pag_code_id_box;
  GtkWidget *cad_bxs_pag_cli_box, *cad_bxs_pag_cli_nome_box;
  GtkWidget *cad_bxs_pag_status_box;
  GtkWidget *cad_bxs_pag_parcela_box;
  GtkWidget *cad_bxs_pag_datacriacao_box;
  GtkWidget *cad_bxs_pag_datavencimento_box;
  GtkWidget *cad_bxs_pag_parcvalor_box;
  GtkWidget *cad_bxs_pag_bxrvalor_box;
  GtkWidget *cad_bxs_pag_valor_box;

  GtkWidget *cad_bxs_pag_code_fixed;
  GtkWidget *cad_bxs_pag_code_id_fixed;
  GtkWidget *cad_bxs_pag_cli_fixed, *cad_bxs_pag_cli_nome_fixed;
  GtkWidget *cad_bxs_pag_status_fixed;
  GtkWidget *cad_bxs_pag_parcela_fixed;
  GtkWidget *cad_bxs_pag_datacriacao_fixed;
  GtkWidget *cad_bxs_pag_datavencimento_fixed;
  GtkWidget *cad_bxs_pag_parcvalor_fixed;
  GtkWidget *cad_bxs_pag_bxrvalor_fixed;
  GtkWidget *cad_bxs_pag_valor_fixed;

  GtkWidget *cad_bxs_pag_code_frame;
  GtkWidget *cad_bxs_pag_code_id_frame;
  GtkWidget *cad_bxs_pag_cli_frame, *cad_bxs_pag_cli_nome_frame;
  GtkWidget *cad_bxs_pag_status_frame;
  GtkWidget *cad_bxs_pag_parcela_frame;
  GtkWidget *cad_bxs_pag_datacriacao_frame;
  GtkWidget *cad_bxs_pag_datavencimento_frame;
  GtkWidget *cad_bxs_pag_parcvalor_frame;
  GtkWidget *cad_bxs_pag_bxrvalor_frame;
  GtkWidget *cad_bxs_pag_valor_frame;

  GtkWidget *campo_opcoes, *caixa_grande, *linha1,
  *linha2,
  *linha3,
  *linha4,
  *linha5, *colunas;

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Baixas à pagar");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"document-edit");
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

  janelas_gerenciadas.vetor_janelas[CAD_BX_PAG_WND].reg_id = CAD_BX_PAG_WND;
  janelas_gerenciadas.vetor_janelas[CAD_BX_PAG_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_BX_PAG_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[CAD_BX_PAG_WND].janela_pointer = janela;

  cad_bxs_pag_concluir_button = gtk_button_new_with_label("Concluir");
  gtk_button_set_image(GTK_BUTTON(cad_bxs_pag_concluir_button),gtk_image_new_from_file(IMG_OK));
  cad_bxs_pag_cancelar_button = gtk_button_new_with_label("Cancelar");
  gtk_button_set_image(GTK_BUTTON(cad_bxs_pag_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));
  cad_bxs_pag_excluir_button = gtk_button_new_with_label("Excluir");
  gtk_button_set_image(GTK_BUTTON(cad_bxs_pag_excluir_button),gtk_image_new_from_file(IMG_EXCLUI));
  cad_bxs_pag_alterar_button = gtk_button_new_with_label("Alterar");
  gtk_button_set_image(GTK_BUTTON(cad_bxs_pag_alterar_button),gtk_image_new_from_file(IMG_ALTER));

  cad_bxs_pag_code_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(cad_bxs_pag_code_button),gtk_image_new_from_file(IMG_PESQ));
  cad_bxs_pag_datacriacao_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(cad_bxs_pag_datacriacao_button),gtk_image_new_from_file(IMG_PESQ));

  caixa_grande = gtk_box_new(1,0);
  campo_opcoes = gtk_box_new(0,0);

  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  linha4 = gtk_box_new(0,0);
  linha5 = gtk_box_new(0,0);
  colunas = gtk_box_new(1,0);

  cad_bxs_pag_code_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_code_entry),5);
  cad_bxs_pag_code_id_spin = gtk_spin_button_new_with_range(0,MAX_PARCELAS_QNT,1);
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_code_id_spin),5);
  cad_bxs_pag_cli_nome_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_cli_nome_entry),30);
  cad_bxs_pag_parcela_spin = gtk_spin_button_new_with_range(0,MAX_PARCELAS_QNT,1);
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_parcela_spin),5);
  cad_bxs_pag_datacriacao_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),15);
  gtk_entry_set_placeholder_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),data_sys);
  cad_bxs_pag_datavencimento_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_datavencimento_entry),15);
  cad_bxs_pag_parcvalor_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_parcvalor_entry),10);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(cad_bxs_pag_parcvalor_entry),GTK_ENTRY_ICON_PRIMARY,"money");
  cad_bxs_pag_bxrvalor_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_bxrvalor_entry),10);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(cad_bxs_pag_bxrvalor_entry),GTK_ENTRY_ICON_PRIMARY,"money");
  cad_bxs_pag_valor_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(cad_bxs_pag_valor_entry),10);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(cad_bxs_pag_valor_entry),GTK_ENTRY_ICON_PRIMARY,"money");

  gtk_widget_set_sensitive(cad_bxs_pag_cli_nome_entry,FALSE);
  gtk_widget_set_name(cad_bxs_pag_cli_nome_entry,"entry_unsensetivate");

  gtk_widget_set_sensitive(cad_bxs_pag_datavencimento_entry,FALSE);
  gtk_widget_set_name(cad_bxs_pag_datavencimento_entry,"entry_unsensetivate");

  gtk_widget_set_sensitive(cad_bxs_pag_parcvalor_entry,FALSE);
  gtk_widget_set_name(cad_bxs_pag_parcvalor_entry,"entry_unsensetivate");

  gtk_widget_set_sensitive(cad_bxs_pag_bxrvalor_entry,FALSE);
  gtk_widget_set_name(cad_bxs_pag_bxrvalor_entry,"entry_unsensetivate");

  cad_bxs_pag_code_fixed = gtk_fixed_new();
  cad_bxs_pag_code_id_fixed = gtk_fixed_new();
  cad_bxs_pag_cli_nome_fixed = gtk_fixed_new();
  cad_bxs_pag_parcela_fixed = gtk_fixed_new();
  cad_bxs_pag_datacriacao_fixed = gtk_fixed_new();
  cad_bxs_pag_datavencimento_fixed = gtk_fixed_new();
  cad_bxs_pag_parcvalor_fixed = gtk_fixed_new();
  cad_bxs_pag_bxrvalor_fixed = gtk_fixed_new();
  cad_bxs_pag_valor_fixed = gtk_fixed_new();

  cad_bxs_pag_code_frame = gtk_frame_new("Título à Baixar");
  cad_bxs_pag_code_id_frame = gtk_frame_new("Nº:");
  cad_bxs_pag_cli_nome_frame = gtk_frame_new("Cliente");
  cad_bxs_pag_parcela_frame = gtk_frame_new("Parcela");
  cad_bxs_pag_datacriacao_frame = gtk_frame_new("Baixado em:");
  cad_bxs_pag_datavencimento_frame = gtk_frame_new("Vencimento em:");
  cad_bxs_pag_parcvalor_frame = gtk_frame_new("Valor da Parcela");
  cad_bxs_pag_bxrvalor_frame = gtk_frame_new("Valor à Baixar");
  cad_bxs_pag_valor_frame = gtk_frame_new("Valor Baixado");

  cad_bxs_pag_code_box = gtk_box_new(0,0);
  cad_bxs_pag_code_id_box = gtk_box_new(0,0);
  cad_bxs_pag_cli_nome_box = gtk_box_new(0,0);
  cad_bxs_pag_parcela_box = gtk_box_new(0,0);
  cad_bxs_pag_datacriacao_box = gtk_box_new(0,0);
  cad_bxs_pag_datavencimento_box = gtk_box_new(0,0);
  cad_bxs_pag_parcvalor_box = gtk_box_new(0,0);
  cad_bxs_pag_bxrvalor_box = gtk_box_new(0,0);
  cad_bxs_pag_valor_box = gtk_box_new(0,0);

  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_code_box),cad_bxs_pag_code_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_code_box),cad_bxs_pag_code_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_code_id_box),cad_bxs_pag_code_id_spin,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_cli_nome_box),cad_bxs_pag_cli_nome_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_parcela_box),cad_bxs_pag_parcela_spin,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_datacriacao_box),cad_bxs_pag_datacriacao_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_datacriacao_box),cad_bxs_pag_datacriacao_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_datavencimento_box),cad_bxs_pag_datavencimento_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_parcvalor_box),cad_bxs_pag_parcvalor_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_bxrvalor_box),cad_bxs_pag_bxrvalor_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(cad_bxs_pag_valor_box),cad_bxs_pag_valor_entry,0,0,0);

  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_code_frame),cad_bxs_pag_code_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_code_id_frame),cad_bxs_pag_code_id_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_cli_nome_frame),cad_bxs_pag_cli_nome_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_parcela_frame),cad_bxs_pag_parcela_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_datacriacao_frame),cad_bxs_pag_datacriacao_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_datavencimento_frame),cad_bxs_pag_datavencimento_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_parcvalor_frame),cad_bxs_pag_parcvalor_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_bxrvalor_frame),cad_bxs_pag_bxrvalor_box);
  gtk_container_add(GTK_CONTAINER(cad_bxs_pag_valor_frame),cad_bxs_pag_valor_box);

  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_code_fixed),cad_bxs_pag_code_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_code_id_fixed),cad_bxs_pag_code_id_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_cli_nome_fixed),cad_bxs_pag_cli_nome_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_parcela_fixed),cad_bxs_pag_parcela_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_datacriacao_fixed),cad_bxs_pag_datacriacao_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_datavencimento_fixed),cad_bxs_pag_datavencimento_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_parcvalor_fixed),cad_bxs_pag_parcvalor_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_bxrvalor_fixed),cad_bxs_pag_bxrvalor_frame,20,20);
  gtk_fixed_put(GTK_FIXED(cad_bxs_pag_valor_fixed),cad_bxs_pag_valor_frame,20,20);

  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bxs_pag_concluir_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bxs_pag_alterar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bxs_pag_cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(campo_opcoes),cad_bxs_pag_excluir_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(linha1),cad_bxs_pag_code_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha1),cad_bxs_pag_parcela_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),cad_bxs_pag_code_id_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3),cad_bxs_pag_cli_nome_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),cad_bxs_pag_datacriacao_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),cad_bxs_pag_datavencimento_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha5),cad_bxs_pag_parcvalor_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha5),cad_bxs_pag_bxrvalor_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha5),cad_bxs_pag_valor_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(caixa_grande),linha1,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_grande),linha2,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_grande),linha3,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_grande),linha4,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_grande),linha5,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_grande),campo_opcoes,0,0,15);

  gtk_container_add(GTK_CONTAINER(janela),caixa_grande);

  g_signal_connect(cad_bxs_pag_code_entry,"activate",G_CALLBACK(cad_bxs_pag_tit_fun),NULL);
  g_signal_connect(cad_bxs_pag_code_id_spin,"activate",G_CALLBACK(cad_bxs_pag_id_fun),NULL);
  g_signal_connect(cad_bxs_pag_code_id_spin,"value-changed",G_CALLBACK(cad_bxs_pag_id_fun),NULL);
  g_signal_connect(cad_bxs_pag_parcela_spin,"value-changed",G_CALLBACK(cad_bxs_pag_parc_fun),NULL);
  g_signal_connect(cad_bxs_pag_parcela_spin,"activate",G_CALLBACK(cad_bxs_pag_parc_fun),NULL);
  g_signal_connect(cad_bxs_pag_datacriacao_entry,"activate",G_CALLBACK(cad_bxs_pag_dtc_fun),NULL);
  g_signal_connect(cad_bxs_pag_valor_entry,"activate",G_CALLBACK(cad_bxs_pag_vlr_fun),NULL);

  g_signal_connect(cad_bxs_pag_code_button,"clicked",G_CALLBACK(psq_fin_pag),cad_bxs_pag_code_entry);
  g_signal_connect(cad_bxs_pag_datacriacao_button,"clicked",G_CALLBACK(psq_data),cad_bxs_pag_datacriacao_entry);

  g_signal_connect(cad_bxs_pag_concluir_button,"clicked",G_CALLBACK(cad_bxs_pag_concluir_fun),NULL);
  g_signal_connect(cad_bxs_pag_alterar_button,"clicked",G_CALLBACK(cad_bxs_pag_alterar_fun),NULL);
  g_signal_connect(cad_bxs_pag_cancelar_button,"clicked",G_CALLBACK(cad_bxs_pag_cancelar_fun),NULL);

  cad_bxs_pag_alterando=0;
  cad_bxs_pag_concluindo=0;

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_BX_PAG_WND]);
  //gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
  gtk_widget_show_all(janela);
  return 0;
}
