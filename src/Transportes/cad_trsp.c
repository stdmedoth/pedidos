int trsp_cad_fun(){

	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"transportes");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Transportes");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"x-package-repository");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	//gtk_widget_set_size_request(janela,800,600);

	janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND].reg_id = CAD_TRSP_WND;
	janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND].janela_pointer = janela;

	GtkWidget *caixa_grande = gtk_box_new(1,0);
	GtkWidget *caixa_opcoes = gtk_box_new(0,0);
	GtkWidget *linha1 = gtk_box_new(0,0);
	GtkWidget *linha2 = gtk_box_new(0,0);
	GtkWidget *linha3 = gtk_box_new(0,0);
	GtkWidget *linha4 = gtk_box_new(0,0);
	GtkWidget *linha5 = gtk_box_new(0,0);
	GtkWidget *linha6 = gtk_box_new(0,0);
	GtkWidget *linha7 = gtk_box_new(0,0);
	GtkWidget *linha8 = gtk_box_new(0,0);
	GtkWidget *coluna1 = gtk_box_new(1,0);
	GtkWidget *coluna2 = gtk_box_new(1,0);
	GtkWidget *colunas = gtk_box_new(0,0);
	GtkWidget *lateral1 = gtk_box_new(1,0);

	GtkWidget *inicio_box = gtk_box_new(1,0);
	GtkWidget *inicio_frame = gtk_frame_new("Início");
	GtkWidget *entrega_box = gtk_box_new(1,0);
	GtkWidget *entrega_frame = gtk_frame_new("Entrega");

	char task[MAX_CODE_LEN];
	sprintf(task,"%i",tasker("servico_transporte"));

	GtkWidget *trsp_cad_code_frame = gtk_frame_new("Código");
	GtkWidget *trsp_cad_trsp_frame = gtk_frame_new("Transportador");
	GtkWidget *trsp_cad_cli_frame = gtk_frame_new("Cliente");
	GtkWidget *trsp_cad_cepini_frame = gtk_frame_new("CEP Inicio");
	GtkWidget *trsp_cad_cepentr_frame = gtk_frame_new("CEP Entrega");
	GtkWidget *trsp_cad_nument_frame = gtk_frame_new("Número");
	GtkWidget *trsp_cad_orc_frame = gtk_frame_new("Orçamento");
	GtkWidget *trsp_cad_vlrfrt_frame = gtk_frame_new("Valor Frete");
	GtkWidget *trsp_cad_descfrt_frame = gtk_frame_new("Valor Desconto");
	GtkWidget *trsp_cad_obs_frame = gtk_frame_new("Observacão");
	GtkWidget *trsp_cad_endini_frame = gtk_frame_new("End. Inicio Resumido");
	GtkWidget *trsp_cad_endentr_frame = gtk_frame_new("End. Entrega Resumido");

	GtkWidget *trsp_cad_code_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_trsp_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_cli_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_cepini_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_cepentr_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_nument_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_orc_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_vlrfrt_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_descfrt_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_obs_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_endini_box = gtk_box_new(0,0);
	GtkWidget *trsp_cad_endentr_box = gtk_box_new(0,0);

	GtkWidget *trsp_cad_code_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_trsp_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_cli_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_cepini_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_cepentr_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_nument_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_orc_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_vlrfrt_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_descfrt_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_obs_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_endini_fixed = gtk_fixed_new();
	GtkWidget *trsp_cad_endentr_fixed = gtk_fixed_new();

	trsp_cad_code_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_code_entry),5);

	trsp_cad_trspcode_entry = gtk_entry_new();
	trsp_cad_trsp_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_trsp_entry),40);
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_trspcode_entry),5);
	gtk_widget_set_sensitive(trsp_cad_trsp_entry,FALSE);
	gtk_widget_set_name(trsp_cad_trsp_entry,"entry_unsensetivate");

	trsp_cad_clicode_entry = gtk_entry_new();
	trsp_cad_cli_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_cli_entry),40);
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_clicode_entry),5);
	gtk_widget_set_sensitive(trsp_cad_cli_entry,FALSE);
	gtk_widget_set_name(trsp_cad_cli_entry,"entry_unsensetivate");

	trsp_cad_cepini_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_cepini_entry),10);

	trsp_cad_cepentr_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_cepentr_entry),10);

	trsp_cad_endini_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_endini_entry),30);
	gtk_widget_set_sensitive(trsp_cad_endini_entry,FALSE);
	gtk_widget_set_name(trsp_cad_endini_entry,"entry_unsensetivate");

	trsp_cad_endentr_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_endentr_entry),30);
	gtk_widget_set_sensitive(trsp_cad_endentr_entry,FALSE);
	gtk_widget_set_name(trsp_cad_endentr_entry,"entry_unsensetivate");

	trsp_cad_nument_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_nument_entry),5);

	trsp_cad_orc_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_orc_entry),5);

	trsp_cad_vlrfrt_entry = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(trsp_cad_vlrfrt_entry),GTK_ENTRY_ICON_PRIMARY,"money");
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_vlrfrt_entry),15);

	trsp_cad_descfrt_entry = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(trsp_cad_descfrt_entry),GTK_ENTRY_ICON_PRIMARY,"money");
	gtk_entry_set_width_chars(GTK_ENTRY(trsp_cad_descfrt_entry),15);

	trsp_cad_obs_entry = gtk_text_view_new();
	gtk_widget_set_size_request(trsp_cad_obs_entry,300,50);

	trsp_cad_concluir_button = gtk_button_new_with_label("Concluir");
	trsp_cad_alterar_button = gtk_button_new_with_label("Alterar");
	trsp_cad_excluir_button = gtk_button_new_with_label("Excluir");
	trsp_cad_cancelar_button = gtk_button_new_with_label("Cancelar");

	gtk_box_pack_start(GTK_BOX(caixa_opcoes),trsp_cad_concluir_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),trsp_cad_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),trsp_cad_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),trsp_cad_excluir_button,0,0,5);

	trsp_cad_code_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(trsp_cad_code_button),gtk_image_new_from_file(IMG_PESQ));
	trsp_cad_trsp_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(trsp_cad_trsp_button),gtk_image_new_from_file(IMG_PESQ));
	trsp_cad_cli_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(trsp_cad_cli_button),gtk_image_new_from_file(IMG_PESQ));
	trsp_cad_cepini_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(trsp_cad_cepini_button),gtk_image_new_from_file(IMG_PESQ));
	trsp_cad_cepentr_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(trsp_cad_cepentr_button),gtk_image_new_from_file(IMG_PESQ));
	trsp_cad_orc_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(trsp_cad_orc_button),gtk_image_new_from_file(IMG_PESQ));

	gtk_box_pack_start(GTK_BOX(trsp_cad_code_box),trsp_cad_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_code_box),trsp_cad_code_button,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_trsp_box),trsp_cad_trspcode_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_trsp_box),trsp_cad_trsp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(trsp_cad_trsp_box),trsp_cad_trsp_entry,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_cli_box),trsp_cad_clicode_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_cli_box),trsp_cad_cli_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(trsp_cad_cli_box),trsp_cad_cli_entry,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_cepini_box),trsp_cad_cepini_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_cepini_box),trsp_cad_cepini_button,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_cepentr_box),trsp_cad_cepentr_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_cepentr_box),trsp_cad_cepentr_button,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_endini_box),trsp_cad_endini_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_endentr_box),trsp_cad_endentr_entry,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_nument_box),trsp_cad_nument_entry,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_orc_box),trsp_cad_orc_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_orc_box),trsp_cad_orc_button,0,0,0);

	gtk_box_pack_start(GTK_BOX(trsp_cad_vlrfrt_box),trsp_cad_vlrfrt_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_descfrt_box),trsp_cad_descfrt_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(trsp_cad_obs_box),trsp_cad_obs_entry,0,0,0);

	gtk_container_add(GTK_CONTAINER(trsp_cad_code_frame),trsp_cad_code_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_trsp_frame),trsp_cad_trsp_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_cli_frame),trsp_cad_cli_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_cepini_frame),trsp_cad_cepini_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_cepentr_frame),trsp_cad_cepentr_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_endini_frame),trsp_cad_endini_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_endentr_frame),trsp_cad_endentr_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_nument_frame),trsp_cad_nument_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_orc_frame),trsp_cad_orc_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_vlrfrt_frame),trsp_cad_vlrfrt_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_descfrt_frame),trsp_cad_descfrt_box);
	gtk_container_add(GTK_CONTAINER(trsp_cad_obs_frame),trsp_cad_obs_box);

	gtk_fixed_put(GTK_FIXED(trsp_cad_code_fixed),trsp_cad_code_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_trsp_fixed),trsp_cad_trsp_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_cli_fixed),trsp_cad_cli_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_cepini_fixed),trsp_cad_cepini_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_cepentr_fixed),trsp_cad_cepentr_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_endini_fixed),trsp_cad_endini_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_endentr_fixed),trsp_cad_endentr_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_nument_fixed),trsp_cad_nument_frame,10,200);
	gtk_fixed_put(GTK_FIXED(trsp_cad_orc_fixed),trsp_cad_orc_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_vlrfrt_fixed),trsp_cad_vlrfrt_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_descfrt_fixed),trsp_cad_descfrt_frame,10,10);
	gtk_fixed_put(GTK_FIXED(trsp_cad_obs_fixed),trsp_cad_obs_frame,10,10);

	gtk_box_pack_start(GTK_BOX(inicio_box),trsp_cad_cepini_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(inicio_box),trsp_cad_endini_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(entrega_box),trsp_cad_cepentr_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(entrega_box),trsp_cad_endentr_fixed,0,0,0);

	gtk_container_add(GTK_CONTAINER(inicio_frame),inicio_box);
	gtk_container_add(GTK_CONTAINER(entrega_frame),entrega_box);


	gtk_box_pack_start(GTK_BOX(linha1),trsp_cad_code_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha2),trsp_cad_trsp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha3),trsp_cad_cli_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha4),inicio_frame,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha4),entrega_frame,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha5),trsp_cad_vlrfrt_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha5),trsp_cad_descfrt_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha6),trsp_cad_obs_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(coluna1),linha1,0,0,2);
	gtk_box_pack_start(GTK_BOX(coluna1),linha2,0,0,2);
	gtk_box_pack_start(GTK_BOX(coluna1),linha3,0,0,2);
	gtk_box_pack_start(GTK_BOX(coluna1),linha4,0,0,2);
	gtk_box_pack_start(GTK_BOX(coluna1),linha5,0,0,2);
	gtk_box_pack_start(GTK_BOX(coluna1),linha6,0,0,2);

	gtk_box_pack_start(GTK_BOX(lateral1),trsp_cad_nument_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(lateral1),trsp_cad_orc_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(coluna2),lateral1,0,0,0);

	gtk_box_pack_start(GTK_BOX(colunas),coluna1,0,0,2);
	gtk_box_pack_start(GTK_BOX(colunas),coluna2,0,0,2);

	gtk_box_pack_start(GTK_BOX(caixa_grande),colunas,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_opcoes,0,0,5);

	trsp_cad_alterando = 0;
	trsp_cad_concluindo = 0;
	trsp_cad_rec_alteracao = 0;

	gtk_entry_set_text(GTK_ENTRY(trsp_cad_code_entry),task);
	gtk_widget_grab_focus(trsp_cad_trspcode_entry);

	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);

	g_signal_connect(trsp_cad_code_entry,"activate",G_CALLBACK(trsp_cad_code_fun),NULL);
	g_signal_connect(trsp_cad_trspcode_entry,"activate",G_CALLBACK(trsp_cad_trspcode_fun),NULL);
	g_signal_connect(trsp_cad_clicode_entry,"activate",G_CALLBACK(trsp_cad_cli_fun),NULL);
	g_signal_connect(trsp_cad_cepini_entry,"activate",G_CALLBACK(trsp_cad_cepini_fun),NULL);
	g_signal_connect(trsp_cad_cepentr_entry,"activate",G_CALLBACK(trsp_cad_cepentr_fun),NULL);
	g_signal_connect(trsp_cad_nument_entry,"activate",G_CALLBACK(trsp_cad_nument_fun),NULL);
	g_signal_connect(trsp_cad_orc_entry,"activate",G_CALLBACK(trsp_cad_orc_fun),NULL);
	g_signal_connect(trsp_cad_vlrfrt_entry,"activate",G_CALLBACK(trsp_cad_vlrfrt_fun),NULL);
	g_signal_connect(trsp_cad_descfrt_entry,"activate",G_CALLBACK(trsp_cad_descfrt_fun),NULL);

	g_signal_connect(trsp_cad_code_button,"clicked",G_CALLBACK(psq_srv_trsp),trsp_cad_code_entry);
	g_signal_connect(trsp_cad_orc_button,"clicked",G_CALLBACK(psq_orc),trsp_cad_orc_entry);
	g_signal_connect(trsp_cad_trsp_button,"clicked",G_CALLBACK(psq_ter),trsp_cad_trspcode_entry);
	g_signal_connect(trsp_cad_cli_button,"clicked",G_CALLBACK(psq_ter),trsp_cad_clicode_entry);

	g_signal_connect(trsp_cad_cepini_button,"clicked",G_CALLBACK(psq_cep),trsp_cad_cepini_entry);
	g_signal_connect(trsp_cad_cepentr_button,"clicked",G_CALLBACK(psq_cep),trsp_cad_cepentr_entry);

	g_signal_connect(trsp_cad_concluir_button,"clicked",G_CALLBACK(trsp_cad_concluir_fun),NULL);
	g_signal_connect(trsp_cad_alterar_button,"clicked",G_CALLBACK(trsp_cad_alterar_fun),NULL);
	g_signal_connect(trsp_cad_cancelar_button,"clicked",G_CALLBACK(trsp_cad_cancelar_fun),NULL);
	g_signal_connect(trsp_cad_excluir_button,"clicked",G_CALLBACK(trsp_cad_excluir_fun),NULL);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND]);


	gtk_widget_show_all(janela);
  return 0;
}
