int cad_titulos_receber(){

    GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(janela),3);
    gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
    gtk_window_set_title(GTK_WINDOW(janela),"Títulos à Receber");
    gtk_window_set_icon_name(GTK_WINDOW(janela),"document-edit");
    gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
    gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

    janelas_gerenciadas.vetor_janelas[CAD_TIT_REC_WND].reg_id = CAD_TIT_REC_WND;
    if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_TIT_REC_WND]))
      return 1;
    janelas_gerenciadas.vetor_janelas[CAD_TIT_REC_WND].janela_pointer = janela;

    GtkWidget *cad_rec_code_frame, *cad_rec_code_box, *cad_rec_code_fixed;
    GtkWidget *cad_rec_cli_frame, *cad_rec_cli_box, *cad_rec_cli_fixed;
    GtkWidget *cad_rec_ped_frame, *cad_rec_ped_box, *cad_rec_ped_fixed;
    GtkWidget *cad_rec_bnc_frame, *cad_rec_bnc_box, *cad_rec_bnc_fixed;
    GtkWidget *cad_rec_status_frame, *cad_rec_status_box, *cad_rec_status_fixed;
    GtkWidget *cad_rec_parcela_frame, *cad_rec_parcela_box, *cad_rec_parcela_fixed;
    GtkWidget *cad_rec_datacriacao_frame, *cad_rec_datacriacao_box, *cad_rec_datacriacao_fixed;
    GtkWidget *cad_rec_datavencimento_frame, *cad_rec_datavencimento_box, *cad_rec_datavencimento_fixed;
    GtkWidget *cad_rec_valor_frame, *cad_rec_valor_box, *cad_rec_valor_fixed;
    GtkWidget *caixa_grande, *linha1, *linha2, *linha3, *linha4, *linha5, *colunas;
    GtkWidget *caixa_opcoes;
    char task_code[MAX_CODE_LEN];

    cad_rec_concluir_button = gtk_button_new_with_label("Concluir");
    cad_rec_alterar_button = gtk_button_new_with_label("Alterar");
    cad_rec_cancelar_button = gtk_button_new_with_label("Cancelar");
    cad_rec_excluir_button = gtk_button_new_with_label("Excluir");

    caixa_opcoes = gtk_box_new(0,0);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_rec_concluir_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_rec_alterar_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_rec_cancelar_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_rec_excluir_button,0,0,5);

    caixa_grande = gtk_box_new(1,0);
    linha1 = gtk_box_new(0,0);
    linha2 = gtk_box_new(0,0);
    linha3 = gtk_box_new(0,0);
    linha4 = gtk_box_new(0,0);
    linha5 = gtk_box_new(0,0);

    cad_rec_code_fixed = gtk_fixed_new();
    cad_rec_cli_fixed = gtk_fixed_new();
    cad_rec_ped_fixed = gtk_fixed_new();
    cad_rec_bnc_fixed = gtk_fixed_new();
    cad_rec_status_fixed = gtk_fixed_new();
    cad_rec_parcela_fixed = gtk_fixed_new();
    cad_rec_datacriacao_fixed = gtk_fixed_new();
    cad_rec_datavencimento_fixed = gtk_fixed_new();
    cad_rec_valor_fixed = gtk_fixed_new();

    cad_rec_code_frame = gtk_frame_new("Código:");
    cad_rec_cli_frame = gtk_frame_new("Cliente:");
    cad_rec_ped_frame = gtk_frame_new("Pedido:");
    cad_rec_bnc_frame = gtk_frame_new("Banco:");
    cad_rec_status_frame = gtk_frame_new("Status");
    cad_rec_parcela_frame = gtk_frame_new("Parcela:");
    cad_rec_datacriacao_frame = gtk_frame_new("Criação:");
    cad_rec_datavencimento_frame = gtk_frame_new("Vencimento:");
    cad_rec_valor_frame = gtk_frame_new("Valor:");

    cad_rec_code_box = gtk_box_new(0,0);
    cad_rec_cli_box = gtk_box_new(0,0);
    cad_rec_ped_box = gtk_box_new(0,0);
    cad_rec_bnc_box = gtk_box_new(0,0);
    cad_rec_status_box = gtk_box_new(0,0);
    cad_rec_parcela_box = gtk_box_new(0,0);
    cad_rec_datacriacao_box = gtk_box_new(0,0);
    cad_rec_datavencimento_box = gtk_box_new(0,0);
    cad_rec_valor_box = gtk_box_new(0,0);

    cad_rec_bnc_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_rec_bnc_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_rec_cli_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_rec_cli_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_rec_tit_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_rec_tit_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_rec_ped_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_rec_ped_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_rec_datacri_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_rec_datacri_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_rec_datavenc_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_rec_datavenc_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_rec_code_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_code_entry),5);
    cad_rec_bnc_entry =  gtk_entry_new();
    cad_rec_bnc_nome_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_bnc_entry),5);
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_bnc_nome_entry),15);
    cad_rec_cli_entry = gtk_entry_new();
    cad_rec_cli_nome_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_cli_entry),5);
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_cli_nome_entry),20);
    gtk_widget_set_sensitive(cad_rec_cli_nome_entry,FALSE);
  	gtk_widget_set_name(cad_rec_cli_nome_entry,"entry_unsensetivate");
    gtk_widget_set_sensitive(cad_rec_bnc_nome_entry,FALSE);
  	gtk_widget_set_name(cad_rec_bnc_nome_entry,"entry_unsensetivate");
    cad_rec_ped_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_ped_entry),5);
    cad_rec_status_combo = gtk_combo_box_text_new();

    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_rec_status_combo),0,"Baixado");
    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_rec_status_combo),1,"Parcialmente Baixado");
    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_rec_status_combo),2,"Pendente");
    gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rec_status_combo),0);
    cad_rec_parcela_spin = gtk_spin_button_new_with_range(0,MAX_PARCELAS_QNT,1);
    cad_rec_datacriacao_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_datacriacao_entry),15);
    cad_rec_datavencimento_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_datavencimento_entry),15);
    cad_rec_valor_entry = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(cad_rec_valor_entry),GTK_ENTRY_ICON_PRIMARY,"money");
    gtk_entry_set_width_chars(GTK_ENTRY(cad_rec_valor_entry),15);

    gtk_box_pack_start(GTK_BOX(cad_rec_code_box),cad_rec_code_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_code_box),cad_rec_tit_psq_button,0,0,5);

    gtk_box_pack_start(GTK_BOX(cad_rec_cli_box),cad_rec_cli_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_cli_box),cad_rec_cli_psq_button,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_cli_box),cad_rec_cli_nome_entry,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_rec_ped_box),cad_rec_ped_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_ped_box),cad_rec_ped_psq_button,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_rec_bnc_box),cad_rec_bnc_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_bnc_box),cad_rec_bnc_psq_button,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_bnc_box),cad_rec_bnc_nome_entry,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_rec_status_box),cad_rec_status_combo,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_parcela_box),cad_rec_parcela_spin,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_rec_datacriacao_box),cad_rec_datacriacao_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_datacriacao_box),cad_rec_datacri_psq_button,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_rec_datavencimento_box),cad_rec_datavencimento_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_rec_datavencimento_box),cad_rec_datavenc_psq_button,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_rec_valor_box),cad_rec_valor_entry,0,0,0);

    gtk_container_add(GTK_CONTAINER(cad_rec_code_frame),cad_rec_code_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_cli_frame),cad_rec_cli_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_ped_frame),cad_rec_ped_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_bnc_frame),cad_rec_bnc_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_status_frame),cad_rec_status_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_parcela_frame),cad_rec_parcela_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_datacriacao_frame),cad_rec_datacriacao_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_datavencimento_frame),cad_rec_datavencimento_box);
    gtk_container_add(GTK_CONTAINER(cad_rec_valor_frame),cad_rec_valor_box);

    gtk_fixed_put(GTK_FIXED(cad_rec_code_fixed),cad_rec_code_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_cli_fixed),cad_rec_cli_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_ped_fixed),cad_rec_ped_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_bnc_fixed),cad_rec_bnc_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_status_fixed),cad_rec_status_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_parcela_fixed),cad_rec_parcela_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_datacriacao_fixed),cad_rec_datacriacao_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_datavencimento_fixed),cad_rec_datavencimento_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_rec_valor_fixed),cad_rec_valor_frame,20,20);

    gtk_box_pack_start(GTK_BOX(linha1),cad_rec_code_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha2),cad_rec_parcela_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha2),cad_rec_bnc_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha3),cad_rec_cli_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha3),cad_rec_ped_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha4),cad_rec_datacriacao_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha4),cad_rec_datavencimento_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha5),cad_rec_valor_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha5),cad_rec_status_fixed,0,0,0);

    gtk_box_pack_start(GTK_BOX(caixa_grande),linha1,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha2,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha3,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha4,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha5,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_opcoes,0,0,20);

    cad_rec_alterando=0;
    cad_rec_concluindo=0;
    sprintf(task_code,"%i",tasker("titulos"));
    gtk_entry_set_text(GTK_ENTRY(cad_rec_code_entry),task_code);
    gtk_widget_grab_focus(cad_rec_cli_entry);

    g_signal_connect(cad_rec_tit_psq_button,"clicked",G_CALLBACK(psq_fin_rec),cad_rec_code_entry);
    g_signal_connect(cad_rec_cli_psq_button,"clicked",G_CALLBACK(psq_ter),cad_rec_cli_entry);
    g_signal_connect(cad_rec_ped_psq_button,"clicked",G_CALLBACK(psq_ped),cad_rec_ped_entry);
    g_signal_connect(cad_rec_datacri_psq_button,"clicked",G_CALLBACK(psq_data),cad_rec_datacriacao_entry);
    g_signal_connect(cad_rec_datavenc_psq_button,"clicked",G_CALLBACK(psq_data),cad_rec_datavencimento_entry);
    g_signal_connect(cad_rec_bnc_psq_button,"clicked",G_CALLBACK(psq_bnc),cad_rec_bnc_entry);

    g_signal_connect(cad_rec_code_entry,"activate",G_CALLBACK(cad_rec_code_fun),NULL);
    g_signal_connect(cad_rec_parcela_spin,"activate",G_CALLBACK(cad_rec_parcela_fun),NULL);
    g_signal_connect(cad_rec_parcela_spin,"value-changed",G_CALLBACK(cad_rec_parcela_fun),NULL);
    g_signal_connect(cad_rec_bnc_entry,"activate",G_CALLBACK(cad_rec_bnc_fun),NULL);
    g_signal_connect(cad_rec_cli_entry,"activate",G_CALLBACK(cad_rec_cli_fun),NULL);
    g_signal_connect(cad_rec_ped_entry,"activate",G_CALLBACK(cad_rec_ped_fun),NULL);
    g_signal_connect(cad_rec_datacriacao_entry,"activate",G_CALLBACK(cad_rec_datacriacao_fun),NULL);
    g_signal_connect(cad_rec_datavencimento_entry,"activate",G_CALLBACK(cad_rec_datavencimento_fun),NULL);
    g_signal_connect(cad_rec_valor_entry,"activate",G_CALLBACK(cad_rec_valor_fun),NULL);

    g_signal_connect(cad_rec_concluir_button,"clicked",G_CALLBACK(cad_rec_concluir_fun),NULL);
    g_signal_connect(cad_rec_alterar_button,"clicked",G_CALLBACK(cad_rec_alterar_fun),NULL);
    g_signal_connect(cad_rec_excluir_button,"clicked",G_CALLBACK(cad_rec_excluir_fun),NULL);
    g_signal_connect(cad_rec_cancelar_button,"clicked",G_CALLBACK(cad_rec_cancelar_fun),NULL);

    g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_TIT_REC_WND]);
    gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
    gtk_widget_show_all(janela);

    return 0;
}
