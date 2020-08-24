int cad_titulos_pagar(){

    GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(janela),3);
    gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
    gtk_window_set_title(GTK_WINDOW(janela),"Títulos à Pagar");
    gtk_window_set_icon_name(GTK_WINDOW(janela),"document-edit");
    gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
    gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

    janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND].reg_id = CAD_TIT_PAG_WND;
    janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND].aberta = 1;
    if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND]))
      return 1;
    janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND].janela_pointer = janela;

    GtkWidget *cad_pag_code_frame, *cad_pag_code_box, *cad_pag_code_fixed;
    GtkWidget *cad_pag_cli_frame, *cad_pag_cli_box, *cad_pag_cli_fixed;
    GtkWidget *cad_pag_ped_frame, *cad_pag_ped_box, *cad_pag_ped_fixed;
    GtkWidget *cad_pag_status_frame, *cad_pag_status_box, *cad_pag_status_fixed;
    GtkWidget *cad_pag_parcela_frame, *cad_pag_parcela_box, *cad_pag_parcela_fixed;
    GtkWidget *cad_pag_datacriacao_frame, *cad_pag_datacriacao_box, *cad_pag_datacriacao_fixed;
    GtkWidget *cad_pag_datavencimento_frame, *cad_pag_datavencimento_box, *cad_pag_datavencimento_fixed;
    GtkWidget *cad_pag_valor_frame, *cad_pag_valor_box, *cad_pag_valor_fixed;
    GtkWidget *caixa_grande, *linha1, *linha2, *linha3, *linha4, *colunas;
    GtkWidget *caixa_opcoes;
    char task_code[MAX_CODE_LEN];

    cad_pag_concluir_button = gtk_button_new_with_label("Concluir");
    cad_pag_alterar_button = gtk_button_new_with_label("Alterar");
    cad_pag_cancelar_button = gtk_button_new_with_label("Cancelar");
    cad_pag_excluir_button = gtk_button_new_with_label("Excluir");

    caixa_opcoes = gtk_box_new(0,0);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_pag_concluir_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_pag_alterar_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_pag_cancelar_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(caixa_opcoes),cad_pag_excluir_button,0,0,5);

    caixa_grande = gtk_box_new(1,0);
    linha1 = gtk_box_new(0,0);
    linha2 = gtk_box_new(0,0);
    linha3 = gtk_box_new(0,0);
    linha4 = gtk_box_new(0,0);

    cad_pag_code_fixed = gtk_fixed_new();
    cad_pag_cli_fixed = gtk_fixed_new();
    cad_pag_ped_fixed = gtk_fixed_new();
    cad_pag_status_fixed = gtk_fixed_new();
    cad_pag_parcela_fixed = gtk_fixed_new();
    cad_pag_datacriacao_fixed = gtk_fixed_new();
    cad_pag_datavencimento_fixed = gtk_fixed_new();
    cad_pag_valor_fixed = gtk_fixed_new();

    cad_pag_code_frame = gtk_frame_new("Código:");
    cad_pag_cli_frame = gtk_frame_new("Cliente:");
    cad_pag_ped_frame = gtk_frame_new("Pedido:");
    cad_pag_status_frame = gtk_frame_new("Status");
    cad_pag_parcela_frame = gtk_frame_new("Parcela:");
    cad_pag_datacriacao_frame = gtk_frame_new("Criação:");
    cad_pag_datavencimento_frame = gtk_frame_new("Vencimento:");
    cad_pag_valor_frame = gtk_frame_new("Valor:");

    cad_pag_code_box = gtk_box_new(0,0);
    cad_pag_cli_box = gtk_box_new(0,0);
    cad_pag_ped_box = gtk_box_new(0,0);
    cad_pag_status_box = gtk_box_new(0,0);
    cad_pag_parcela_box = gtk_box_new(0,0);
    cad_pag_datacriacao_box = gtk_box_new(0,0);
    cad_pag_datavencimento_box = gtk_box_new(0,0);
    cad_pag_valor_box = gtk_box_new(0,0);

    cad_pag_cli_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_pag_cli_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_pag_tit_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_pag_tit_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_pag_ped_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_pag_ped_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_pag_datacri_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_pag_datacri_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_pag_datavenc_psq_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(cad_pag_datavenc_psq_button),gtk_image_new_from_file(IMG_PESQ));

    cad_pag_code_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_code_entry),5);
    cad_pag_cli_entry = gtk_entry_new();
    cad_pag_cli_nome_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_cli_entry),5);
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_cli_nome_entry),20);
    gtk_widget_set_sensitive(cad_pag_cli_nome_entry,FALSE);
  	gtk_widget_set_name(cad_pag_cli_nome_entry,"entry_unsensetivate");
    cad_pag_ped_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_ped_entry),5);
    cad_pag_status_combo = gtk_combo_box_text_new();

    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_pag_status_combo),0,"Baixado");
    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_pag_status_combo),1,"Parcialmente Baixado");
    gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cad_pag_status_combo),2,"Pendente");
    gtk_combo_box_set_active(GTK_COMBO_BOX(cad_pag_status_combo),0);
    cad_pag_parcela_spin = gtk_spin_button_new_with_range(0,MAX_PARCELAS_QNT,1);
    cad_pag_datacriacao_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_datacriacao_entry),15);
    cad_pag_datavencimento_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_datavencimento_entry),15);
    cad_pag_valor_entry = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(cad_pag_valor_entry),GTK_ENTRY_ICON_PRIMARY,"money");
    gtk_entry_set_width_chars(GTK_ENTRY(cad_pag_valor_entry),15);

    gtk_box_pack_start(GTK_BOX(cad_pag_code_box),cad_pag_code_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_code_box),cad_pag_tit_psq_button,0,0,5);

    gtk_box_pack_start(GTK_BOX(cad_pag_cli_box),cad_pag_cli_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_cli_box),cad_pag_cli_psq_button,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_cli_box),cad_pag_cli_nome_entry,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_pag_ped_box),cad_pag_ped_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_ped_box),cad_pag_ped_psq_button,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_pag_status_box),cad_pag_status_combo,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_parcela_box),cad_pag_parcela_spin,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_pag_datacriacao_box),cad_pag_datacriacao_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_datacriacao_box),cad_pag_datacri_psq_button,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_pag_datavencimento_box),cad_pag_datavencimento_entry,0,0,0);
    gtk_box_pack_start(GTK_BOX(cad_pag_datavencimento_box),cad_pag_datavenc_psq_button,0,0,0);

    gtk_box_pack_start(GTK_BOX(cad_pag_valor_box),cad_pag_valor_entry,0,0,0);

    gtk_container_add(GTK_CONTAINER(cad_pag_code_frame),cad_pag_code_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_cli_frame),cad_pag_cli_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_ped_frame),cad_pag_ped_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_status_frame),cad_pag_status_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_parcela_frame),cad_pag_parcela_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_datacriacao_frame),cad_pag_datacriacao_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_datavencimento_frame),cad_pag_datavencimento_box);
    gtk_container_add(GTK_CONTAINER(cad_pag_valor_frame),cad_pag_valor_box);

    gtk_fixed_put(GTK_FIXED(cad_pag_code_fixed),cad_pag_code_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_cli_fixed),cad_pag_cli_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_ped_fixed),cad_pag_ped_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_status_fixed),cad_pag_status_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_parcela_fixed),cad_pag_parcela_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_datacriacao_fixed),cad_pag_datacriacao_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_datavencimento_fixed),cad_pag_datavencimento_frame,20,20);
    gtk_fixed_put(GTK_FIXED(cad_pag_valor_fixed),cad_pag_valor_frame,20,20);

    gtk_box_pack_start(GTK_BOX(linha1),cad_pag_code_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha1),cad_pag_parcela_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha2),cad_pag_cli_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha2),cad_pag_ped_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha3),cad_pag_datacriacao_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha3),cad_pag_datavencimento_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha4),cad_pag_valor_fixed,0,0,0);
    gtk_box_pack_start(GTK_BOX(linha4),cad_pag_status_fixed,0,0,0);

    gtk_box_pack_start(GTK_BOX(caixa_grande),linha1,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha2,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha3,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),linha4,0,0,0);
    gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_opcoes,0,0,20);

    cad_pag_alterando=0;
    cad_pag_concluindo=0;
    sprintf(task_code,"%i",tasker("titulos"));
    gtk_entry_set_text(GTK_ENTRY(cad_pag_code_entry),task_code);
    gtk_widget_grab_focus(cad_pag_cli_entry);

    g_signal_connect(cad_pag_tit_psq_button,"clicked",G_CALLBACK(psq_fin_pag),cad_pag_code_entry);
    g_signal_connect(cad_pag_cli_psq_button,"clicked",G_CALLBACK(psq_ter),cad_pag_cli_entry);
    g_signal_connect(cad_pag_ped_psq_button,"clicked",G_CALLBACK(psq_ped),cad_pag_ped_entry);
    g_signal_connect(cad_pag_datacri_psq_button,"clicked",G_CALLBACK(psq_data),cad_pag_datacriacao_entry);
    g_signal_connect(cad_pag_datavenc_psq_button,"clicked",G_CALLBACK(psq_data),cad_pag_datavencimento_entry);

    g_signal_connect(cad_pag_code_entry,"activate",G_CALLBACK(cad_pag_code_fun),NULL);
    g_signal_connect(cad_pag_parcela_spin,"activate",G_CALLBACK(cad_pag_parcela_fun),NULL);
    g_signal_connect(cad_pag_parcela_spin,"value-changed",G_CALLBACK(cad_pag_parcela_fun),NULL);
    g_signal_connect(cad_pag_cli_entry,"activate",G_CALLBACK(cad_pag_cli_fun),NULL);
    g_signal_connect(cad_pag_ped_entry,"activate",G_CALLBACK(cad_pag_ped_fun),NULL);
    g_signal_connect(cad_pag_datacriacao_entry,"activate",G_CALLBACK(cad_pag_datacriacao_fun),NULL);
    g_signal_connect(cad_pag_datavencimento_entry,"activate",G_CALLBACK(cad_pag_datavencimento_fun),NULL);
    g_signal_connect(cad_pag_valor_entry,"activate",G_CALLBACK(cad_pag_valor_fun),NULL);

    g_signal_connect(cad_pag_concluir_button,"clicked",G_CALLBACK(cad_pag_concluir_fun),NULL);
    g_signal_connect(cad_pag_alterar_button,"clicked",G_CALLBACK(cad_pag_alterar_fun),NULL);
    g_signal_connect(cad_pag_cancelar_button,"clicked",G_CALLBACK(cad_pag_cancelar_fun),NULL);

    g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND]);
    gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
    gtk_widget_show_all(janela);
    return 0;
}
