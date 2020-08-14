int relat_fix_prod(){

  GtkWidget *relat_fix_prod_ordem_box,
  *relat_fix_prod_prod_box,
  *relat_fix_prod_grp_box,
  *relat_fix_prod_quebra_box,
  *relat_fix_prod_est_box;

  GtkWidget *relat_fix_prod_ordem_frame,
  *relat_fix_prod_prod_frame,
  *relat_fix_prod_grp_frame,
  *relat_fix_prod_quebra_frame,
  *relat_fix_prod_est_frame;

  GtkWidget *relat_fix_prod_ordem_fixed,
  *relat_fix_prod_prod_fixed,
  *relat_fix_prod_grp_fixed,
  *relat_fix_prod_quebra_fixed,
  *relat_fix_prod_est_fixed;

  GtkWidget *relat_fix_prod_prod_button,
  *relat_fix_prod_grp_button,
  *relat_fix_prod_est_button;

  GtkWidget *gerar_button;

  GtkWidget *caixa_grande, *caixa_opcoes,
  *linha1, *linha2, *linha3, *linha4,
  *colunas;

  caixa_grande = gtk_box_new(1,0);
  caixa_opcoes = gtk_box_new(0,0);
  linha1 = gtk_box_new(0,0);
  linha2 = gtk_box_new(0,0);
  linha3 = gtk_box_new(0,0);
  linha4 = gtk_box_new(0,0);
  colunas = gtk_box_new(1,0);

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].reg_id = REG_REL_FIX_PROD_WIN;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].janela_pointer = janela;

  gtk_widget_set_name(janela,"relat-produtos");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Relatório Fixo de Produtos");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");

  if(personalizacao.janela_keep_above==1)
    gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);

  relat_fix_prod_ordem_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Código");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Nome");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Peso");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Código Grupo");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Nome Grupo");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Preço Faturado");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_ordem_combo),"Preço A Vista");
  gtk_combo_box_set_active(GTK_COMBO_BOX(relat_fix_prod_ordem_combo),0);

  relat_fix_prod_prod_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_prod_prod_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_prod_grp_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_prod_grp_button),gtk_image_new_from_file(IMG_PESQ));
  relat_fix_prod_est_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(relat_fix_prod_est_button),gtk_image_new_from_file(IMG_PESQ));

  gerar_button = gtk_button_new_with_label("Gerar");
  gtk_button_set_image(GTK_BUTTON(gerar_button),gtk_image_new_from_icon_name("document-print",GTK_ICON_SIZE_DND));

  relat_fix_prod_prod_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_prod_prod_entry),10);
  relat_fix_prod_grp_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_prod_grp_entry),10);
  relat_fix_prod_quebra_check = gtk_check_button_new_with_label("Quebra de linha?");

  relat_fix_prod_quebra_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_quebra_combo),"Grupo");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(relat_fix_prod_quebra_combo),"Fornecedor");
  gtk_combo_box_set_active(GTK_COMBO_BOX(relat_fix_prod_quebra_combo),0);

  relat_fix_prod_est_entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(relat_fix_prod_est_entry),10);

  relat_fix_prod_ordem_frame = gtk_frame_new("Ordem: ");
  relat_fix_prod_prod_frame = gtk_frame_new("Produtos: ");
  relat_fix_prod_grp_frame = gtk_frame_new("Grupos: ");
  relat_fix_prod_quebra_frame = gtk_frame_new("Quebra: ");
  relat_fix_prod_est_frame = gtk_frame_new("Estoque: ");

  relat_fix_prod_ordem_box = gtk_box_new(0,0);
  relat_fix_prod_prod_box = gtk_box_new(0,0);
  relat_fix_prod_grp_box = gtk_box_new(0,0);
  relat_fix_prod_quebra_box = gtk_box_new(0,0);
  relat_fix_prod_est_box = gtk_box_new(0,0);

  relat_fix_prod_ordem_fixed = gtk_fixed_new();
  relat_fix_prod_prod_fixed = gtk_fixed_new();
  relat_fix_prod_grp_fixed = gtk_fixed_new();
  relat_fix_prod_quebra_fixed = gtk_fixed_new();
  relat_fix_prod_est_fixed = gtk_fixed_new();

  gtk_box_pack_start(GTK_BOX(relat_fix_prod_prod_box),relat_fix_prod_prod_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_prod_prod_box),relat_fix_prod_prod_button,0,0,5);

  gtk_box_pack_start(GTK_BOX(relat_fix_prod_grp_box),relat_fix_prod_grp_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_prod_grp_box),relat_fix_prod_grp_button,0,0,0);

  gtk_box_pack_start(GTK_BOX(relat_fix_prod_ordem_box),relat_fix_prod_ordem_combo,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_prod_quebra_box),relat_fix_prod_quebra_check,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_prod_quebra_box),relat_fix_prod_quebra_combo,0,0,10);

  gtk_box_pack_start(GTK_BOX(relat_fix_prod_est_box),relat_fix_prod_est_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(relat_fix_prod_est_box),relat_fix_prod_est_button,0,0,5);

  gtk_container_add(GTK_CONTAINER(relat_fix_prod_prod_frame),relat_fix_prod_prod_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_prod_grp_frame),relat_fix_prod_grp_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_prod_ordem_frame),relat_fix_prod_ordem_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_prod_quebra_frame),relat_fix_prod_quebra_box);
  gtk_container_add(GTK_CONTAINER(relat_fix_prod_est_frame),relat_fix_prod_est_box);

  gtk_fixed_put(GTK_FIXED(relat_fix_prod_prod_fixed),relat_fix_prod_prod_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_prod_grp_fixed),relat_fix_prod_grp_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_prod_ordem_fixed),relat_fix_prod_ordem_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_prod_quebra_fixed),relat_fix_prod_quebra_frame,20,20);
  gtk_fixed_put(GTK_FIXED(relat_fix_prod_est_fixed),relat_fix_prod_est_frame,20,20);

  gtk_box_pack_start(GTK_BOX(linha1),relat_fix_prod_prod_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha1),relat_fix_prod_grp_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2),relat_fix_prod_ordem_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha3),relat_fix_prod_quebra_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha4),relat_fix_prod_est_fixed,0,0,0);

  gtk_box_pack_start(GTK_BOX(caixa_opcoes),gerar_button,0,0,20);

  gtk_box_pack_start(GTK_BOX(colunas),linha1,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha2,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha3,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),linha4,0,0,0);
  gtk_box_pack_start(GTK_BOX(colunas),caixa_opcoes,0,0,20);

  gtk_container_add(GTK_CONTAINER(janela),colunas);

  gtk_widget_set_size_request(janela,300,300);
  gtk_widget_set_sensitive(relat_fix_prod_quebra_combo,FALSE);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN]);

  gtk_widget_show_all(janela);
  return 0;
}
