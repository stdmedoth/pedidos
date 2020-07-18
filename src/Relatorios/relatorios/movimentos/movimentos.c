void relat_mov_fun()
{
	GtkWidget *janela;
	GtkWidget *grid, *caixa, *frame;
	GtkWidget *linha1, *linha2, *linha3, *linha4;
	GtkWidget *relat_mov_code_frame, *relat_mov_code_fixed;
	GtkWidget *relat_mov_nome_frame, *relat_mov_nome_fixed;
	GtkWidget *relat_mov_query_frame, *relat_mov_query_fixed;
	GtkWidget *relat_mov_int_mov_fixed;
	GtkWidget *relat_mov_int_ter_fixed;
	GtkWidget *relat_mov_int_prod_fixed;
	GtkWidget *relat_mov_int_grp_fixed;
	GtkWidget *relat_mov_int_ped_fixed;
	GtkWidget *relat_mov_tipo_fixed;
	GtkWidget *relat_mov_ordem_fixed, *relat_mov_cresc_fixed;
	GtkWidget *relat_mov_code_box;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);

	linha1 = gtk_box_new(0,0);
	linha2 = gtk_box_new(0,0);
	linha3 = gtk_box_new(0,0);
	linha4 = gtk_box_new(0,0);

	relat_mov_code_box = gtk_box_new(0,0);
	psq_relat_mov_code = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_relat_mov_code),gtk_image_new_from_file(IMG_PESQ));

	relat_mov_code_entry = gtk_entry_new();
	relat_mov_code_frame = gtk_frame_new("Código");
	gtk_entry_set_placeholder_text(GTK_ENTRY(relat_mov_code_entry),"Buscar ->");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(relat_mov_code_entry),GTK_ENTRY_ICON_PRIMARY,"emblem-system");

	relat_mov_psq_mov_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_mov_psq_mov_button),gtk_image_new_from_file(IMG_PESQ));
	relat_mov_psq_ter_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_mov_psq_ter_button),gtk_image_new_from_file(IMG_PESQ));
	relat_mov_psq_prod_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_mov_psq_prod_button),gtk_image_new_from_file(IMG_PESQ));
	relat_mov_psq_grp_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_mov_psq_grp_button),gtk_image_new_from_file(IMG_PESQ));
	relat_mov_psq_ped_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(relat_mov_psq_ped_button),gtk_image_new_from_file(IMG_PESQ));

	relat_mov_code_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(relat_mov_code_box),relat_mov_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_mov_code_box),psq_relat_mov_code,0,0,0);
	gtk_container_add(GTK_CONTAINER(relat_mov_code_frame),relat_mov_code_box);
	gtk_fixed_put(GTK_FIXED(relat_mov_code_fixed),relat_mov_code_frame,20,10);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_mov_code_entry),12);

	relat_mov_gerar_button = gtk_button_new_with_label("Gerar");
	gtk_button_set_image(GTK_BUTTON(relat_mov_gerar_button),gtk_image_new_from_icon_name("document-print",GTK_ICON_SIZE_DND));
	relat_mov_gerar_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(relat_mov_gerar_fixed),relat_mov_gerar_button,20,20);

	relat_mov_nome_entry = gtk_entry_new();
	relat_mov_nome_frame = gtk_frame_new("Nome");
	gtk_entry_set_placeholder_text(GTK_ENTRY(relat_mov_nome_entry),"Nome relatório");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(relat_mov_nome_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-underline");
	relat_mov_nome_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(relat_mov_nome_frame),relat_mov_nome_entry);
	gtk_fixed_put(GTK_FIXED(relat_mov_nome_fixed),relat_mov_nome_frame,20,10);

	relat_mov_int_mov_fixed = gtk_fixed_new();
	relat_mov_int_ter_fixed = gtk_fixed_new();
	relat_mov_int_prod_fixed = gtk_fixed_new();
	relat_mov_int_grp_fixed = gtk_fixed_new();
	relat_mov_int_ped_fixed = gtk_fixed_new();
	relat_mov_tipo_fixed = gtk_fixed_new();

	relat_mov_int1_mov_entry = gtk_spin_button_new_with_range(1,99999,1);
	relat_mov_int2_mov_entry = gtk_spin_button_new_with_range(1,99999,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_mov_int2_mov_entry),99999);

	relat_mov_int1_ter_entry = gtk_spin_button_new_with_range(1,99999,1);
	relat_mov_int2_ter_entry = gtk_spin_button_new_with_range(1,99999,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_mov_int2_ter_entry),99999);

	relat_mov_int1_prod_entry = gtk_spin_button_new_with_range(1,99999,1);
	relat_mov_int2_prod_entry = gtk_spin_button_new_with_range(1,99999,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_mov_int2_prod_entry),99999);

	relat_mov_int1_grp_entry = gtk_spin_button_new_with_range(1,99999,1);
	relat_mov_int2_grp_entry = gtk_spin_button_new_with_range(1,99999,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_mov_int2_grp_entry),99999);

	relat_mov_int1_ped_entry = gtk_spin_button_new_with_range(1,99999,1);
	relat_mov_int2_ped_entry = gtk_spin_button_new_with_range(1,99999,1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_mov_int2_ped_entry),99999);

	relat_mov_tipo_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_tipo_combo),"Todos");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_tipo_combo),"Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_tipo_combo),"Devolução Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_tipo_combo),"Compra");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_tipo_combo),"Devolução Compra");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_tipo_combo),"Outros");
	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_mov_tipo_combo),0);

	relat_mov_ordem_combo = gtk_combo_box_text_new();
	relat_mov_ordem_frame = gtk_frame_new("Ordem");
	relat_mov_ordem_box = gtk_box_new(0,0);
	relat_mov_ordem_fixed = gtk_fixed_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_ordem_combo),"Selecionar Ordem");

	gtk_container_add(GTK_CONTAINER(relat_mov_ordem_frame),relat_mov_ordem_combo);
	gtk_box_pack_start(GTK_BOX(relat_mov_ordem_box), relat_mov_ordem_frame,0,0,0);
	gtk_fixed_put(GTK_FIXED(relat_mov_ordem_fixed),relat_mov_ordem_box,20,10);

	relat_mov_cresc_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_cresc_combo),"Crescente");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_mov_cresc_combo),"Decrescente");
	relat_mov_cresc_frame = gtk_frame_new("Direção");

	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_mov_ordem_combo),0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(relat_mov_cresc_combo),0);

	relat_mov_cresc_box = gtk_box_new(0,0);
	relat_mov_cresc_fixed = gtk_fixed_new();

	gtk_container_add(GTK_CONTAINER(relat_mov_cresc_frame),relat_mov_cresc_combo);
	gtk_box_pack_start(GTK_BOX(relat_mov_cresc_box), relat_mov_cresc_frame,0,0,0);
	gtk_fixed_put(GTK_FIXED(relat_mov_cresc_fixed),relat_mov_cresc_box,20,10);

	gtk_box_pack_start(GTK_BOX(linha4),relat_mov_ordem_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha4),relat_mov_cresc_fixed,0,0,0);

	relat_mov_int_mov_frame = gtk_frame_new("Cód. Movimentação:");
	relat_mov_int_ter_frame = gtk_frame_new("Cliente/Fornecedor:");
	relat_mov_int_prod_frame = gtk_frame_new("Produtos:");
	relat_mov_int_grp_frame = gtk_frame_new("Grupos:");
	relat_mov_int_ped_frame = gtk_frame_new("Pedidos:");
	relat_mov_tipo_frame = gtk_frame_new("Tipo Movimento");

	relat_mov_int_mov_box = gtk_box_new(0,0);
	relat_mov_int_ter_box = gtk_box_new(0,0);
	relat_mov_int_prod_box = gtk_box_new(0,0);
	relat_mov_int_grp_box = gtk_box_new(0,0);
	relat_mov_int_ped_box = gtk_box_new(0,0);
	relat_mov_tipo_box = gtk_box_new(0,0);

	gtk_box_pack_start(GTK_BOX(relat_mov_int_mov_box),relat_mov_int1_mov_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_mov_box),relat_mov_int2_mov_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_mov_box),relat_mov_psq_mov_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(relat_mov_int_ter_box),relat_mov_int1_ter_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_ter_box),relat_mov_int2_ter_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_ter_box),relat_mov_psq_ter_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(relat_mov_int_prod_box),relat_mov_int1_prod_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_prod_box),relat_mov_int2_prod_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_prod_box),relat_mov_psq_prod_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(relat_mov_int_grp_box),relat_mov_int1_grp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_grp_box),relat_mov_int2_grp_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_grp_box),relat_mov_psq_grp_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(relat_mov_int_ped_box),relat_mov_int1_ped_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_ped_box),relat_mov_int2_ped_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(relat_mov_int_ped_box),relat_mov_psq_ped_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(relat_mov_tipo_box),relat_mov_tipo_combo,0,0,0);

	gtk_container_add(GTK_CONTAINER(relat_mov_int_mov_frame),relat_mov_int_mov_box);
	gtk_container_add(GTK_CONTAINER(relat_mov_int_ter_frame),relat_mov_int_ter_box);
	gtk_container_add(GTK_CONTAINER(relat_mov_int_prod_frame),relat_mov_int_prod_box);
	gtk_container_add(GTK_CONTAINER(relat_mov_int_grp_frame),relat_mov_int_grp_box);
	gtk_container_add(GTK_CONTAINER(relat_mov_int_ped_frame),relat_mov_int_ped_box);
	gtk_container_add(GTK_CONTAINER(relat_mov_tipo_frame),relat_mov_tipo_box);

	gtk_fixed_put(GTK_FIXED(relat_mov_int_mov_fixed),relat_mov_int_mov_frame,20,10);
	gtk_fixed_put(GTK_FIXED(relat_mov_int_ter_fixed),relat_mov_int_ter_frame,20,10);
	gtk_fixed_put(GTK_FIXED(relat_mov_int_prod_fixed),relat_mov_int_prod_frame,20,10);
	gtk_fixed_put(GTK_FIXED(relat_mov_int_grp_fixed),relat_mov_int_grp_frame,20,10);
	gtk_fixed_put(GTK_FIXED(relat_mov_int_ped_fixed),relat_mov_int_ped_frame,20,10);
	gtk_fixed_put(GTK_FIXED(relat_mov_tipo_fixed),relat_mov_tipo_frame,20,10);

	gtk_box_pack_start(GTK_BOX(linha1),relat_mov_int_mov_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha1),relat_mov_int_ter_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(linha2),relat_mov_int_prod_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha2),relat_mov_int_grp_fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(linha3),relat_mov_int_ped_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(linha3),relat_mov_tipo_fixed,0,0,0);

	relat_mov_query_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(relat_mov_query_entry),"Query para análise");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(relat_mov_nome_entry),GTK_ENTRY_ICON_PRIMARY,"utilities-system-monitor");
	relat_mov_query_frame = gtk_frame_new("Query");
	relat_mov_query_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(relat_mov_query_frame),relat_mov_query_entry);
	gtk_fixed_put(GTK_FIXED(relat_mov_query_fixed),relat_mov_query_frame,20,20);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_mov_query_entry),55);

	grid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),relat_mov_code_fixed,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),relat_mov_nome_fixed,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),linha1,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),linha2,0,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),linha3,0,5,1,1);
	gtk_grid_attach(GTK_GRID(grid),linha4,0,6,1,1);
	gtk_grid_attach(GTK_GRID(grid),relat_mov_gerar_fixed,0,7,1,1);
	gtk_grid_attach(GTK_GRID(grid),relat_mov_query_fixed,0,8,1,1);

	frame = gtk_frame_new("Filtros");

	gtk_container_add(GTK_CONTAINER(frame),grid);

	caixa = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(caixa),frame,0,0,0);

	tabelas_bd_id=5;

	g_signal_connect(psq_relat_mov_code,"clicked",G_CALLBACK(psq_tables_relat),relat_mov_code_entry);

	g_signal_connect(relat_mov_code_entry,"activate",G_CALLBACK(relat_mov_codigo_fun),NULL);

	g_signal_connect(relat_mov_gerar_button,"clicked",G_CALLBACK(relat_mov_query_fun),NULL);

	gtk_widget_set_sensitive(relat_mov_nome_entry,FALSE);
	gtk_widget_set_sensitive(relat_mov_code_entry,FALSE);

	gtk_widget_grab_focus(psq_relat_mov_code);

	gtk_container_add(GTK_CONTAINER(janela),caixa);
	gtk_widget_set_size_request(janela,500,300);
	gtk_widget_show_all(janela);
}
