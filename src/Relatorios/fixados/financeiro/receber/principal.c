int rel_fix_fin_rec(){

  GtkWidget *janela,*caixa_grande,
  *linha1, *linha2, *linha3, *linha4, *linha5, *linha6,
  *coluna1, *coluna2, *colunas;

  GtkWidget *rel_fix_fin_rec_ped_frame,
  *rel_fix_fin_rec_tit_frame,
  *rel_fix_fin_rec_bx_frame,
  *rel_fix_fin_rec_cli_frame,
  *rel_fix_fin_rec_status_frame,
  *rel_fix_fin_rec_datacriacao_frame,
  *rel_fix_fin_rec_databaixa_frame,
  *rel_fix_fin_rec_datavencimento_frame,
  *rel_fix_fin_rec_valor_frame;

  GtkWidget *rel_fix_fin_rec_ped_box,
  *rel_fix_fin_rec_cli_box,
  *rel_fix_fin_rec_tit_box,
  *rel_fix_fin_rec_bx_box,
  *rel_fix_fin_rec_status_box,
  *rel_fix_fin_rec_datacriacao_box,
  *rel_fix_fin_rec_databaixa_box,
  *rel_fix_fin_rec_datavencimento_box,
  *rel_fix_fin_rec_valor_box;

  GtkWidget *rel_fix_fin_rec_ped_fixed,
  *rel_fix_fin_rec_cli_fixed,
  *rel_fix_fin_rec_tit_fixed,
  *rel_fix_fin_rec_bx_fixed,
  *rel_fix_fin_rec_status_fixed,
  *rel_fix_fin_rec_datacriacao_fixed,
  *rel_fix_fin_rec_databaixa_fixed,
  *rel_fix_fin_rec_datavencimento_fixed,
  *rel_fix_fin_rec_valor_fixed;

  GtkWidget *gerar_button, *gerar_fixed;
  GtkWidget *frame_datas,*box_datas,*fixed_datas;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"relatorio");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Relatório de Títulos à Receber");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"money");

	gtk_window_set_transient_for(GTK_WINDOW(janela),
  GTK_WINDOW(janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].janela_pointer));

  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	gtk_widget_set_size_request(janela,500,500);

	janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].reg_id = REG_REL_FIX_FINREC_WIN;
	janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].janela_pointer = janela;

  rel_fix_fin_rec_tit_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_tit_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_tit_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_tit_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_bx_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_bx_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_bx_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_bx_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_ped_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_ped_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_ped_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_ped_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_cli_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_cli_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_cli_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_cli_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_datacriacao_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_datacriacao_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_datacriacao_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_datacriacao_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_databaixa_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_databaixa_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_databaixa_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_databaixa_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_datavencimento_button1 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_datavencimento_button1),gtk_image_new_from_file(IMG_PESQ));
  rel_fix_fin_rec_datavencimento_button2 = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(rel_fix_fin_rec_datavencimento_button2),gtk_image_new_from_file(IMG_PESQ));

  rel_fix_fin_rec_ped_entry1 = gtk_spin_button_new_with_range(0,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_ped_entry1),5);
  rel_fix_fin_rec_ped_entry2 = gtk_spin_button_new_with_range(0,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_ped_entry2),5);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(rel_fix_fin_rec_ped_entry2),tasker("pedidos"));

  rel_fix_fin_rec_cli_entry1 = gtk_spin_button_new_with_range(1,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_cli_entry1),5);
  rel_fix_fin_rec_cli_entry2 = gtk_spin_button_new_with_range(1,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_cli_entry2),5);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(rel_fix_fin_rec_cli_entry2),tasker("terceiros"));

  rel_fix_fin_rec_tit_entry1 = gtk_spin_button_new_with_range(1,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_tit_entry1),5);
  rel_fix_fin_rec_tit_entry2 = gtk_spin_button_new_with_range(1,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_tit_entry2),5);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(rel_fix_fin_rec_tit_entry2),tasker("titulos"));

  rel_fix_fin_rec_bx_entry1 = gtk_spin_button_new_with_range(0,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_bx_entry1),5);
  rel_fix_fin_rec_bx_entry2 = gtk_spin_button_new_with_range(0,99999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_bx_entry2),5);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(rel_fix_fin_rec_bx_entry2),tasker("baixas_titulos"));

  rel_fix_fin_rec_status_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_status_combo),"Indiferente");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_status_combo),"Baixado");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_status_combo),"Parcialmente Baixado");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_status_combo),"Pendente");
  gtk_combo_box_set_active(GTK_COMBO_BOX(rel_fix_fin_rec_status_combo),0);

  rel_fix_fin_rec_datacriacao_entry1 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_datacriacao_entry1),10);
  rel_fix_fin_rec_datacriacao_entry2 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_datacriacao_entry2),10);

  rel_fix_fin_rec_databaixa_entry1 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_databaixa_entry1),10);
  rel_fix_fin_rec_databaixa_entry2 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_databaixa_entry2),10);

  rel_fix_fin_rec_datavencimento_entry1 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_datavencimento_entry1),10);
  rel_fix_fin_rec_datavencimento_entry2 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_datavencimento_entry2),10);

  rel_fix_fin_rec_valor_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_valor_combo),"Indiferente");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_valor_combo),"Valor Título Mínimo");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(rel_fix_fin_rec_valor_combo),"Valor Título Máximo");
  gtk_combo_box_set_active(GTK_COMBO_BOX(rel_fix_fin_rec_valor_combo),0);
  rel_fix_fin_rec_valor_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(rel_fix_fin_rec_valor_entry),10);

  rel_fix_fin_rec_ped_frame = gtk_frame_new("Pedido");
  rel_fix_fin_rec_cli_frame = gtk_frame_new("Cliente");
  rel_fix_fin_rec_tit_frame = gtk_frame_new("Título");
  rel_fix_fin_rec_bx_frame = gtk_frame_new("Baixa");
  rel_fix_fin_rec_status_frame = gtk_frame_new("Status");
  rel_fix_fin_rec_datacriacao_frame = gtk_frame_new("Criação Título");
  rel_fix_fin_rec_databaixa_frame = gtk_frame_new("Criação Baixa");
  rel_fix_fin_rec_datavencimento_frame = gtk_frame_new("Data Vencimento");
  rel_fix_fin_rec_valor_frame = gtk_frame_new("Valor");

  rel_fix_fin_rec_ped_box = gtk_box_new(0,0);
  rel_fix_fin_rec_cli_box = gtk_box_new(0,0);
  rel_fix_fin_rec_tit_box = gtk_box_new(0,0);
  rel_fix_fin_rec_bx_box = gtk_box_new(0,0);
  rel_fix_fin_rec_status_box = gtk_box_new(0,0);
  rel_fix_fin_rec_datacriacao_box = gtk_box_new(0,0);
  rel_fix_fin_rec_databaixa_box = gtk_box_new(0,0);
  rel_fix_fin_rec_datavencimento_box = gtk_box_new(0,0);
  rel_fix_fin_rec_valor_box = gtk_box_new(0,0);

  rel_fix_fin_rec_ped_fixed = gtk_fixed_new();
  rel_fix_fin_rec_cli_fixed = gtk_fixed_new();
  rel_fix_fin_rec_tit_fixed = gtk_fixed_new();
  rel_fix_fin_rec_bx_fixed = gtk_fixed_new();
  rel_fix_fin_rec_status_fixed = gtk_fixed_new();
  rel_fix_fin_rec_datacriacao_fixed = gtk_fixed_new();
  rel_fix_fin_rec_databaixa_fixed = gtk_fixed_new();
  rel_fix_fin_rec_datavencimento_fixed = gtk_fixed_new();
  rel_fix_fin_rec_valor_fixed = gtk_fixed_new();

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_ped_box),rel_fix_fin_rec_ped_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_ped_box),rel_fix_fin_rec_ped_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_ped_box),gtk_label_new("à"),0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_ped_box),rel_fix_fin_rec_ped_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_ped_box),rel_fix_fin_rec_ped_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_cli_box),rel_fix_fin_rec_cli_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_cli_box),rel_fix_fin_rec_cli_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_cli_box),gtk_label_new("à"),0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_cli_box),rel_fix_fin_rec_cli_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_cli_box),rel_fix_fin_rec_cli_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_tit_box),rel_fix_fin_rec_tit_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_tit_box),rel_fix_fin_rec_tit_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_tit_box),gtk_label_new("à"),0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_tit_box),rel_fix_fin_rec_tit_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_tit_box),rel_fix_fin_rec_tit_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_bx_box),rel_fix_fin_rec_bx_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_bx_box),rel_fix_fin_rec_bx_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_bx_box),gtk_label_new("à"),0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_bx_box),rel_fix_fin_rec_bx_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_bx_box),rel_fix_fin_rec_bx_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_status_box),rel_fix_fin_rec_status_combo,0,0,0);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datacriacao_box),rel_fix_fin_rec_datacriacao_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datacriacao_box),rel_fix_fin_rec_datacriacao_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datacriacao_box),gtk_label_new("à"),0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datacriacao_box),rel_fix_fin_rec_datacriacao_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datacriacao_box),rel_fix_fin_rec_datacriacao_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_databaixa_box),rel_fix_fin_rec_databaixa_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_databaixa_box),rel_fix_fin_rec_databaixa_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_databaixa_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_databaixa_box),rel_fix_fin_rec_databaixa_entry2,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_databaixa_box),rel_fix_fin_rec_databaixa_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datavencimento_box),rel_fix_fin_rec_datavencimento_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datavencimento_box),rel_fix_fin_rec_datavencimento_button1,0,0,5);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datavencimento_box),gtk_label_new("à"),0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datavencimento_box),rel_fix_fin_rec_datavencimento_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_datavencimento_box),rel_fix_fin_rec_datavencimento_button2,0,0,5);

  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_valor_box),rel_fix_fin_rec_valor_combo,0,0,0);
  gtk_box_pack_start(GTK_BOX(rel_fix_fin_rec_valor_box),rel_fix_fin_rec_valor_entry,0,0,5);

  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_ped_frame),rel_fix_fin_rec_ped_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_cli_frame),rel_fix_fin_rec_cli_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_tit_frame),rel_fix_fin_rec_tit_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_bx_frame),rel_fix_fin_rec_bx_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_status_frame),rel_fix_fin_rec_status_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_datacriacao_frame),rel_fix_fin_rec_datacriacao_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_databaixa_frame),rel_fix_fin_rec_databaixa_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_datavencimento_frame),rel_fix_fin_rec_datavencimento_box);
  gtk_container_add(GTK_CONTAINER(rel_fix_fin_rec_valor_frame),rel_fix_fin_rec_valor_box);

  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_ped_fixed),rel_fix_fin_rec_ped_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_cli_fixed),rel_fix_fin_rec_cli_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_tit_fixed),rel_fix_fin_rec_tit_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_bx_fixed),rel_fix_fin_rec_bx_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_status_fixed),rel_fix_fin_rec_status_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_datacriacao_fixed),rel_fix_fin_rec_datacriacao_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_databaixa_fixed),rel_fix_fin_rec_databaixa_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_datavencimento_fixed),rel_fix_fin_rec_datavencimento_frame,20,20);
  gtk_fixed_put(GTK_FIXED(rel_fix_fin_rec_valor_fixed),rel_fix_fin_rec_valor_frame,20,20);

  linha1 = gtk_box_new(0,0);
  linha2  = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  linha4 = gtk_box_new(0,0);
  linha5 = gtk_box_new(0,0);
  linha6 = gtk_box_new(0,0);

  coluna1 = gtk_box_new(1,0);
  coluna2  = gtk_box_new(1,0);

  colunas = gtk_box_new(0,0);

  frame_datas = gtk_frame_new("Datas");
  box_datas = gtk_box_new(1,0);
  caixa_grande = gtk_box_new(1,0);
  gerar_fixed = gtk_fixed_new();
  fixed_datas = gtk_fixed_new();
  gerar_button = gtk_button_new_with_label("Gerar");

  gtk_fixed_put(GTK_FIXED(gerar_fixed),gerar_button,20,20);

  gtk_box_pack_start(GTK_BOX(box_datas),rel_fix_fin_rec_datacriacao_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(box_datas),rel_fix_fin_rec_databaixa_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(box_datas),rel_fix_fin_rec_datavencimento_fixed,0,0,5);
  gtk_container_add(GTK_CONTAINER(frame_datas),box_datas);
  gtk_fixed_put(GTK_FIXED(fixed_datas),frame_datas,20,50);

  gtk_box_pack_start(GTK_BOX(linha1),rel_fix_fin_rec_ped_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha2),rel_fix_fin_rec_tit_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha3),rel_fix_fin_rec_bx_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha4),rel_fix_fin_rec_cli_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha5),rel_fix_fin_rec_status_fixed,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha6),rel_fix_fin_rec_valor_fixed,0,0,5);

  gtk_box_pack_start(GTK_BOX(coluna1),linha1,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha2,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha3,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha4,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha5,0,0,5);
  gtk_box_pack_start(GTK_BOX(coluna1),linha6,0,0,5);

  gtk_box_pack_start(GTK_BOX(coluna2),fixed_datas,0,0,5);

  gtk_box_pack_start(GTK_BOX(colunas),coluna1,0,0,5);
  gtk_box_pack_start(GTK_BOX(colunas),coluna2,0,0,5);

  gtk_box_pack_start(GTK_BOX(caixa_grande),colunas,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_grande),gerar_fixed,0,0,5);

  gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
  gtk_widget_show_all(janela);

  g_signal_connect(rel_fix_fin_rec_ped_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_ped1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_ped_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_ped2_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_cli_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_cli1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_cli_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_cli2_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_tit_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_tit1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_tit_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_tit2_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_bx_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_bx1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_bx_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_bx2_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_datacriacao_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_datacriacao1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_datacriacao_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_datacriacao2_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_databaixa_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_databaixa1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_databaixa_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_databaixa2_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_datavencimento_entry1,"activate",G_CALLBACK(rel_fix_fin_rec_datavencimento1_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_datavencimento_entry2,"activate",G_CALLBACK(rel_fix_fin_rec_datavencimento1_fun),NULL);

  g_signal_connect(rel_fix_fin_rec_valor_entry,"activate",G_CALLBACK(rel_fix_fin_rec_entryvalor_fun),NULL);

  g_signal_connect(gerar_button,"clicked",G_CALLBACK(rel_fix_fin_rec_gerar),NULL);

  g_signal_connect(rel_fix_fin_rec_ped_button1,"clicked",G_CALLBACK(psq_ter),rel_fix_fin_rec_ped_entry1);
  g_signal_connect(rel_fix_fin_rec_ped_button2,"clicked",G_CALLBACK(psq_ter),rel_fix_fin_rec_ped_entry2);

  g_signal_connect(rel_fix_fin_rec_cli_button1,"clicked",G_CALLBACK(psq_ter),rel_fix_fin_rec_cli_entry1);
  g_signal_connect(rel_fix_fin_rec_cli_button2,"clicked",G_CALLBACK(psq_ter),rel_fix_fin_rec_cli_entry2);

  g_signal_connect(rel_fix_fin_rec_tit_button1,"clicked",G_CALLBACK(psq_fin_rec),rel_fix_fin_rec_tit_entry1);
  g_signal_connect(rel_fix_fin_rec_tit_button2,"clicked",G_CALLBACK(psq_fin_rec),rel_fix_fin_rec_tit_entry2);

  g_signal_connect(rel_fix_fin_rec_bx_button1,"clicked",G_CALLBACK(psq_fin_rec),rel_fix_fin_rec_bx_entry1);
  g_signal_connect(rel_fix_fin_rec_bx_button2,"clicked",G_CALLBACK(psq_fin_rec),rel_fix_fin_rec_bx_entry2);

  g_signal_connect(rel_fix_fin_rec_status_combo,"changed",G_CALLBACK(rel_fix_fin_rec_status_fun),NULL);
  g_signal_connect(rel_fix_fin_rec_valor_combo,"changed",G_CALLBACK(rel_fix_fin_rec_combovalor_fun),NULL);


  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN]);
  return 0;
}
