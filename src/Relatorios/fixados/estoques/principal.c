int relat_fix_est(){

  GtkWidget *relat_fix_est_ordem_box,
  *relat_fix_est_prod_box,
  *relat_fix_est_grp_box,
  *relat_fix_est_cli_box,
  *relat_fix_est_quebra_box,
  *relat_fix_est_sintetiza_box,
  *relat_fix_est_totaliza_box,
  *relat_fix_est_ped_box,
  *relat_fix_est_data_box,
  *relat_fix_est_est_box;

  GtkWidget *relat_fix_est_ordem_frame,
  *relat_fix_est_prod_frame,
  *relat_fix_est_grp_frame,
  *relat_fix_est_cli_frame,
  *relat_fix_est_quebra_frame,
  *relat_fix_est_sintetiza_frame,
  *relat_fix_est_totaliza_frame,
  *relat_fix_est_ped_frame,
  *relat_fix_est_data_frame,
  *relat_fix_est_est_frame;

  GtkWidget *relat_fix_est_ordem_fixed,
  *relat_fix_est_prod_fixed,
  *relat_fix_est_grp_fixed,
  *relat_fix_est_cli_fixed,
  *relat_fix_est_quebra_fixed,
  *relat_fix_est_sintetiza_fixed,
  *relat_fix_est_ped_fixed ,
  *relat_fix_est_data_fixed,
  *relat_fix_est_totaliza_fixed,
  *relat_fix_est_est_fixed;

  GtkWidget *relat_fix_est_prod_button,
  *relat_fix_est_grp_button,
  *relat_fix_est_cli_button,
  *relat_fix_est_est_button,
  *relat_fix_est_ped_button,
  *relat_fix_est_data_button;

  GtkWidget *caixa_grande, *caixa_opcoes,
  *linha1,
  *linha2,
  *linha3,
  *linha4,
  *linha5,
  *linha6,
  *linha7,
  *colunas;

  caixa_grande = gtk_box_new(1,0);
  caixa_opcoes = gtk_box_new(0,0);
  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  linha4 = gtk_box_new(0,0);
  linha5 = gtk_box_new(0,0);
  linha6 = gtk_box_new(0,0);
  linha7 = gtk_box_new(0,0);
  colunas = gtk_box_new(1,0);

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].reg_id = REG_REL_FIX_EST_WIN;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].janela_pointer = janela;

  gtk_widget_set_name(janela,"relat-produtos");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Relatório Fixo de Estoque");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");

  gtk_window_set_transient_for(GTK_WINDOW(janela),
  GTK_WINDOW(janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].janela_pointer));

  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);

  relat_fix_est_ordem_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_ordem_combo),"Código");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_ordem_combo),"Razão/Nome Cliente");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_ordem_combo),"Nome Produto");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_ordem_combo),"Quantidade");
  gtk_combo_box_set_active(GTK_COMBO_BOX(relat_fix_est_ordem_combo),0);

  relat_fix_est_prod_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_prod_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_est_grp_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_grp_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_est_cli_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_cli_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_est_est_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_est_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_est_ped_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_ped_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_est_data_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_data_button),gtk_image_new_from_file(IMG_PESQ));

  relat_fix_est_gerar_button = gtk_button_new_with_label("Gerar");
  gtk_button_set_image(GTK_BUTTON(relat_fix_est_gerar_button),gtk_image_new_from_icon_name("document-print",GTK_ICON_SIZE_DND));

  relat_fix_est_prod_entry1 = gtk_spin_button_new_with_range(1,999999,1);
  relat_fix_est_prod_entry2 = gtk_spin_button_new_with_range(1,999999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_prod_entry1),5);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_prod_entry2),5);

  relat_fix_est_grp_entry1 = gtk_spin_button_new_with_range(1,999999,1);
  relat_fix_est_grp_entry2 = gtk_spin_button_new_with_range(1,999999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_grp_entry1),5);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_grp_entry2),5);

  relat_fix_est_cli_entry1 = gtk_spin_button_new_with_range(1,999999,1);
  relat_fix_est_cli_entry2 = gtk_spin_button_new_with_range(1,999999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_cli_entry1),5);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_cli_entry2),5);

  relat_fix_est_ped_entry1 = gtk_spin_button_new_with_range(1,999999,1);
  relat_fix_est_ped_entry2 = gtk_spin_button_new_with_range(1,999999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_ped_entry1),5);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_ped_entry2),5);

  relat_fix_est_quebra_check = gtk_check_button_new_with_label("Quebra?");

  relat_fix_est_data_entry1 = gtk_entry_new();
  relat_fix_est_data_entry2 = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_data_entry1),10);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_data_entry2),10);

  relat_fix_est_est_entry1 = gtk_spin_button_new_with_range(1,999999,1);
  relat_fix_est_est_entry2 = gtk_spin_button_new_with_range(1,999999,1);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_est_entry1),10);
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_est_est_entry2),10);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_est_entry1),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_est_entry2),tasker("estoques"));

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_prod_entry1),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_prod_entry2),tasker("produtos"));
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_grp_entry1),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_grp_entry2),tasker("grupos"));
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_ped_entry1),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_ped_entry2),tasker("pedidos"));
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_cli_entry1),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(relat_fix_est_cli_entry2),tasker("terceiros"));

  relat_fix_est_quebra_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Não");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Produtos");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Grupos");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Clientes");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Código Pedido");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Status Pedido");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_quebra_combo),"Data de Emissão");
  gtk_combo_box_set_active(GTK_COMBO_BOX(relat_fix_est_quebra_combo),0);

  relat_fix_est_sintetiza_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_sintetiza_combo),"Não");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_sintetiza_combo),"Quantidade");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_sintetiza_combo),"Valor Produtos");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_sintetiza_combo),"Valor Frete");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_sintetiza_combo),"Valor Total");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_sintetiza_combo),"Valor Descontos");
  gtk_combo_box_set_active(GTK_COMBO_BOX(relat_fix_est_sintetiza_combo),0);

  relat_fix_est_totaliza_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_totaliza_combo),"Não");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_est_totaliza_combo),"Quantidades");
  gtk_combo_box_set_active(GTK_COMBO_BOX(relat_fix_est_totaliza_combo),0);

  relat_fix_est_ordem_frame = gtk_frame_new("Ordem: ");
  relat_fix_est_prod_frame = gtk_frame_new("Produtos: ");
  relat_fix_est_grp_frame = gtk_frame_new("Grupos: ");
  relat_fix_est_cli_frame = gtk_frame_new("Clientes: ");
  relat_fix_est_quebra_frame = gtk_frame_new("Quebra: ");
  relat_fix_est_totaliza_frame = gtk_frame_new("Totaliza: ");
  relat_fix_est_sintetiza_frame = gtk_frame_new("Sintetiza: ");
  relat_fix_est_ped_frame = gtk_frame_new("Pedidos");
  relat_fix_est_data_frame  = gtk_frame_new("Data");
  relat_fix_est_est_frame = gtk_frame_new("Estoque: ");

  relat_fix_est_ordem_box = gtk_box_new(0,0);
  relat_fix_est_prod_box = gtk_box_new(0,0);
  relat_fix_est_grp_box = gtk_box_new(0,0);
  relat_fix_est_cli_box = gtk_box_new(0,0);
  relat_fix_est_quebra_box = gtk_box_new(0,0);
  relat_fix_est_totaliza_box = gtk_box_new(0,0);
  relat_fix_est_sintetiza_box = gtk_box_new(0,0);
  relat_fix_est_ped_box = gtk_box_new(0,0);
  relat_fix_est_data_box  = gtk_box_new(0,0);
  relat_fix_est_est_box = gtk_box_new(0,0);

  relat_fix_est_ordem_fixed = gtk_fixed_new();
  relat_fix_est_prod_fixed = gtk_fixed_new();
  relat_fix_est_grp_fixed = gtk_fixed_new();
  relat_fix_est_cli_fixed = gtk_fixed_new();
  relat_fix_est_quebra_fixed = gtk_fixed_new();
  relat_fix_est_totaliza_fixed = gtk_fixed_new();
  relat_fix_est_sintetiza_fixed = gtk_fixed_new();
  relat_fix_est_ped_fixed = gtk_fixed_new();
  relat_fix_est_data_fixed  = gtk_fixed_new();
  relat_fix_est_est_fixed = gtk_fixed_new();

  gtk_box_pack_start(GTK_BOX(relat_fix_est_prod_box),relat_fix_est_prod_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_prod_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_prod_box),relat_fix_est_prod_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_prod_box),relat_fix_est_prod_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_grp_box),relat_fix_est_grp_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_grp_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_grp_box),relat_fix_est_grp_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_grp_box),relat_fix_est_grp_button,0,0,0);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_cli_box),relat_fix_est_cli_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_cli_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_cli_box),relat_fix_est_cli_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_cli_box),relat_fix_est_cli_button,0,0,0);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_ordem_box),relat_fix_est_ordem_combo,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_quebra_box),relat_fix_est_quebra_check,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_quebra_box),relat_fix_est_quebra_combo,0,0,10);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_est_box),relat_fix_est_est_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_est_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_est_box),relat_fix_est_est_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_est_box),relat_fix_est_est_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_ped_box),relat_fix_est_ped_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_ped_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_ped_box),relat_fix_est_ped_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_ped_box),relat_fix_est_ped_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_data_box),relat_fix_est_data_entry1,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_data_box),gtk_label_new("à"),0,0,5);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_data_box),relat_fix_est_data_entry2,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_data_box),relat_fix_est_data_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(relat_fix_est_totaliza_box),relat_fix_est_totaliza_combo,0,0,10);
  gtk_box_pack_start(GTK_BOX(relat_fix_est_sintetiza_box),relat_fix_est_sintetiza_combo,0,0,10);

  gtk_container_add(GTK_CONTAINER(relat_fix_est_ped_frame),relat_fix_est_ped_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_prod_frame),relat_fix_est_prod_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_cli_frame),relat_fix_est_cli_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_data_frame),relat_fix_est_data_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_grp_frame),relat_fix_est_grp_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_ordem_frame),relat_fix_est_ordem_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_quebra_frame),relat_fix_est_quebra_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_sintetiza_frame),relat_fix_est_sintetiza_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_totaliza_frame),relat_fix_est_totaliza_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_est_est_frame),relat_fix_est_est_box);

  gtk_fixed_put(GTK_FIXED(relat_fix_est_ped_fixed),relat_fix_est_ped_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_data_fixed),relat_fix_est_data_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_prod_fixed),relat_fix_est_prod_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_grp_fixed),relat_fix_est_grp_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_cli_fixed),relat_fix_est_cli_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_ordem_fixed),relat_fix_est_ordem_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_quebra_fixed),relat_fix_est_quebra_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_totaliza_fixed),relat_fix_est_totaliza_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_sintetiza_fixed),relat_fix_est_sintetiza_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_est_est_fixed),relat_fix_est_est_frame,20,20);

  gtk_box_pack_start(GTK_BOX(linha1),relat_fix_est_ped_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),relat_fix_est_prod_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),relat_fix_est_grp_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3),relat_fix_est_cli_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),relat_fix_est_ordem_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),relat_fix_est_quebra_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha5),relat_fix_est_totaliza_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha5),relat_fix_est_sintetiza_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha6),relat_fix_est_data_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha6),relat_fix_est_est_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(caixa_opcoes),relat_fix_est_gerar_button,0,0,20);

  gtk_box_pack_start(GTK_BOX(colunas),linha1,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha2,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha3,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha4,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha5,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha6,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),caixa_opcoes,0,0,20);

  gtk_container_add(GTK_CONTAINER(janela),colunas);

  find_subgrupos_restrict = malloc(sizeof(struct duo_widget));
  find_subgrupos_restrict->grupo = 1;
  find_subgrupos_restrict->posicao = 0;
  find_subgrupos_restrict->entry = relat_fix_est_grp_entry1;

  gtk_widget_set_size_request(janela,300,300);
  gtk_widget_set_sensitive(relat_fix_est_quebra_combo,FALSE);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN]);

  g_signal_connect(relat_fix_est_ped_button,"clicked",G_CALLBACK(psq_ped),relat_fix_est_ped_entry1);
  g_signal_connect(relat_fix_est_prod_button,"clicked",G_CALLBACK(psq_prod),relat_fix_est_prod_entry1);
  g_signal_connect(relat_fix_est_grp_button,"clicked",G_CALLBACK(pesquisa_subgrp),relat_fix_est_grp_entry1);
  g_signal_connect(relat_fix_est_data_button,"clicked",G_CALLBACK(psq_data),relat_fix_est_data_entry1);
  //g_signal_connect(relat_fix_est_est_button,"clicked",G_CALLBACK(pesquisa_est),relat_fix_est_est_entry1);

  g_signal_connect(relat_fix_est_gerar_button,"clicked",G_CALLBACK(relat_fix_est_gerar_fun),NULL);

  g_signal_connect(relat_fix_est_prod_entry1,"activate",G_CALLBACK(relat_fix_est_prod_fun),NULL);
  g_signal_connect(relat_fix_est_grp_entry1,"activate",G_CALLBACK(relat_fix_est_grp_fun),NULL);
  g_signal_connect(relat_fix_est_est_entry1,"activate",G_CALLBACK(relat_fix_est_est_fun),NULL);


  gtk_widget_show_all(janela);
  return 0;
}
