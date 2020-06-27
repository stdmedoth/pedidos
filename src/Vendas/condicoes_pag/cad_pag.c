static GtkWidget *pag_cod_entry,*pag_nome_entry,*pag_parc_entry,*pag_parc_qnt_entry,*pag_tipo_combo,*pag_init_entry;
static GtkWidget *pag_cod_frame,*pag_nome_frame,*pag_parc_frame,*pag_parc_qnt_frame,*pag_tipo_frame,*pag_init_frame;
static GtkWidget *pag_cod_fixed,*pag_nome_fixed,*pag_parc_fixed,*pag_parc_qnt_fixed,*pag_tipo_fixed,*pag_init_fixed;
static GtkWidget *pag_grid;

static GtkWidget *pag_confirmar_button,
*pag_alterar_button,
*pag_cancelar_button,
*pag_excluir_button;

int cad_pag(){

  GtkWidget *caixa_grande, *caixa_opcoes;
  GtkWidget *pag_psq_cod_box,*pag_psq_cod_button;
  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  char code[MAX_CODE_LEN];

  if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_title(GTK_WINDOW(janela),"Condições de pagamento");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"x-office-calendar");
  gtk_widget_set_size_request(GTK_WIDGET(janela),500,300);

  pag_confirmar_button = gtk_button_new_with_label("Confirmar");
  pag_alterar_button = gtk_button_new_with_label("Alterar");
  pag_cancelar_button = gtk_button_new_with_label("Cancelar");
  pag_excluir_button = gtk_button_new_with_label("Excluir");

  caixa_opcoes = gtk_box_new(0,0);
  caixa_grande = gtk_box_new(1,0);
  pag_psq_cod_box = gtk_box_new(0,0);
  pag_grid = gtk_grid_new();

  pag_psq_cod_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(pag_psq_cod_button),gtk_image_new_from_file(IMG_PESQ));

  pag_cod_fixed = gtk_fixed_new();
  pag_nome_fixed = gtk_fixed_new();
  pag_tipo_fixed = gtk_fixed_new();
  pag_parc_fixed = gtk_fixed_new();
  pag_init_fixed = gtk_fixed_new();
  pag_parc_qnt_fixed = gtk_fixed_new();

  pag_cod_frame = gtk_frame_new("Código");
  pag_nome_frame = gtk_frame_new("Nome");
  pag_tipo_frame = gtk_frame_new("Tipo");
  pag_parc_frame = gtk_frame_new("Intervalos");
  pag_init_frame = gtk_frame_new("Dia inicial");
  pag_parc_qnt_frame = gtk_frame_new("Qnt. Parcelas");

  pag_cod_entry = gtk_entry_new();
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_cod_entry),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_cod_entry),10);

  pag_nome_entry = gtk_entry_new();
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_nome_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-direction-ltr");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_nome_entry),30);

  pag_tipo_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(pag_tipo_combo),"Escolha o tipo de data");
  gtk_combo_box_set_active(GTK_COMBO_BOX(pag_tipo_combo),0);

  pag_init_entry = gtk_spin_button_new_with_range(1,30,1);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_init_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-direction-ltr");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_init_entry),10);

  pag_parc_entry = gtk_entry_new();
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_parc_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-direction-ltr");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_parc_entry),20);

  pag_parc_qnt_entry = gtk_spin_button_new_with_range(1,20,1);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_parc_qnt_entry),GTK_ENTRY_ICON_PRIMARY,"view-list");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_parc_qnt_entry),10);

  gtk_box_pack_start(GTK_BOX(pag_psq_cod_box),pag_cod_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(pag_psq_cod_box),pag_psq_cod_button,0,0,0);
  gtk_container_add(GTK_CONTAINER(pag_cod_frame),pag_psq_cod_box);
  gtk_fixed_put(GTK_FIXED(pag_cod_fixed),pag_cod_frame,20,20);

  gtk_container_add(GTK_CONTAINER(pag_nome_frame),pag_nome_entry);
  gtk_fixed_put(GTK_FIXED(pag_nome_fixed),pag_nome_frame,20,20);

  gtk_fixed_put(GTK_FIXED(pag_tipo_fixed),pag_tipo_combo,20,20);

  gtk_container_add(GTK_CONTAINER(pag_init_frame),pag_init_entry);
  gtk_fixed_put(GTK_FIXED(pag_init_fixed),pag_init_frame,20,20);

  gtk_container_add(GTK_CONTAINER(pag_parc_frame),pag_parc_entry);
  gtk_fixed_put(GTK_FIXED(pag_parc_fixed),pag_parc_frame,20,20);

  gtk_container_add(GTK_CONTAINER(pag_parc_qnt_frame),pag_parc_qnt_entry);
  gtk_fixed_put(GTK_FIXED(pag_parc_qnt_fixed),pag_parc_qnt_frame,20,20);

  gtk_grid_attach(GTK_GRID(pag_grid),pag_cod_fixed,0,1,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_nome_fixed,1,2,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_tipo_fixed,0,2,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_init_fixed,0,3,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_parc_fixed,0,4,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_parc_qnt_fixed,0,5,1,1);

  gtk_box_pack_start(GTK_BOX(caixa_opcoes),pag_confirmar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),pag_alterar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),pag_cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),pag_excluir_button,0,0,5);

  sprintf(code,"%i",tasker("pag_cond"));
  gtk_entry_set_text(GTK_ENTRY(pag_cod_entry),code);
  gtk_widget_grab_focus(pag_nome_entry);

  gtk_box_pack_start(GTK_BOX(caixa_grande),pag_grid,0,0,0);
  gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_opcoes,0,0,40);

  gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
  gtk_widget_show_all(janela);

  return 0;
}
