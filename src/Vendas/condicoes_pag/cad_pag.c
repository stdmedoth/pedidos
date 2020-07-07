static GtkWidget *pag_cod_entry,*pag_nome_entry,*pag_parc_spin,*pag_parc_qnt_spin,*pag_tipo_combo,*pag_init_spin;
static GtkWidget *pag_cod_frame,*pag_nome_frame,*pag_parc_frame,*pag_parc_qnt_frame,*pag_tipo_frame,*pag_init_frame;
static GtkWidget *pag_cod_fixed,*pag_nome_fixed,*pag_parc_fixed,*pag_parc_qnt_fixed,*pag_tipo_fixed,*pag_init_fixed;
static GtkWidget *pag_dia_fixo_fixed,*pag_dia_fixo_check,*pag_dia_fixo_box;
gint pag_dia_fixo_int=0;

static int pag_concluindo = 0;
static int pag_alterando = 0;

static gchar *pag_cod_gchar, *pag_nome_gchar;
static gint pag_parc_int,pag_parc_qnt_int,pag_tipo_int,pag_init_int;

static GtkWidget *pag_datas_tree,
*pag_datas_fixed,
*pag_datas_frame,
*pag_datas_box,
*pag_datas_entry,
*pag_psq_datas_button,
*pag_psq_datas_box;

GtkTreeStore *pag_datas_model;
static GtkWidget *pag_grid;

static GtkWidget *pag_confirmar_button,
*pag_alterar_button,
*pag_cancelar_button,
*pag_excluir_button;

int cad_pag(){
  GtkTreeIter iter1;
  GtkWidget *scrolled,*scrolled_box;
  GtkTreeViewColumn *coluna1,*coluna2;
  GtkCellRenderer *celula1,*celula2;
  GtkWidget *caixa_grande, *caixa_opcoes, *layout;
  GtkWidget *pag_psq_cod_box,*pag_psq_cod_button;
  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  char code[MAX_CODE_LEN];

  if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);

  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_title(GTK_WINDOW(janela),"Condições de pagamento");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"x-office-calendar");
  gtk_widget_set_size_request(GTK_WIDGET(janela),500,470);

  janelas_gerenciadas.vetor_janelas[REG_CAD_COND].reg_id = REG_CAD_COND;
	janelas_gerenciadas.vetor_janelas[REG_CAD_COND].aberta = 1;
	if(ger_janela_aberta(janela_grupo, &janelas_gerenciadas.vetor_janelas[REG_CAD_COND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_COND].janela_pointer = janela_grupo;


  pag_confirmar_button = gtk_button_new_with_label("Confirmar");
  pag_cancelar_button = gtk_button_new_with_label("Cancelar");
  pag_excluir_button = gtk_button_new_with_label("Excluir");
  pag_alterar_button = gtk_button_new_with_label("Alterar");

  pag_concluindo = 0;
  pag_alterando = 0;

  scrolled_box = gtk_box_new(1,0);
  scrolled = gtk_scrolled_window_new(NULL,NULL);
  caixa_opcoes = gtk_box_new(0,0);
  caixa_grande = gtk_box_new(1,0);
  layout = gtk_layout_new(NULL,NULL);
  pag_psq_cod_box = gtk_box_new(0,0);
  pag_grid = gtk_grid_new();

  pag_dia_fixo_box = gtk_box_new(1,0);
  pag_dia_fixo_fixed = gtk_fixed_new();
  pag_dia_fixo_check = gtk_check_button_new_with_label("Dia Inicial Fixo?");

  pag_datas_model = gtk_tree_store_new(2,G_TYPE_INT,G_TYPE_STRING);
  pag_datas_tree = gtk_tree_view_new_with_model((GtkTreeModel*)pag_datas_model);
  pag_datas_fixed = gtk_fixed_new();
  pag_datas_box = gtk_box_new(1,0);
  pag_datas_frame = gtk_frame_new("Área de Teste");;

  coluna1 = gtk_tree_view_column_new();
  celula1 = gtk_cell_renderer_text_new();
  coluna2 = gtk_tree_view_column_new();
  celula2 = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
  gtk_tree_view_column_set_title(coluna1,"Parcela");
  gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

  gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
  gtk_tree_view_column_set_title(coluna2,"Data");
  gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

  gtk_tree_view_append_column(GTK_TREE_VIEW(pag_datas_tree),coluna1);
  gtk_tree_view_append_column(GTK_TREE_VIEW(pag_datas_tree),coluna2);

  gtk_tree_store_append(pag_datas_model,&iter1,NULL);
  gtk_tree_store_set(pag_datas_model,&iter1,0,0,1,"Listar datas",-1);

  pag_datas_entry = gtk_entry_new ();
  gtk_entry_set_placeholder_text(GTK_ENTRY(pag_datas_entry),"Insira Data Teste");
  pag_psq_datas_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(pag_psq_datas_button),gtk_image_new_from_file(IMG_PESQ));

  pag_psq_datas_box = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(pag_psq_datas_box),pag_datas_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(pag_psq_datas_box),pag_psq_datas_button,0,0,0);

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
  pag_init_frame = gtk_frame_new("Dia Inicial");
  pag_parc_qnt_frame = gtk_frame_new("Qnt. Parcelas");

  pag_cod_entry = gtk_entry_new();
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_cod_entry),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_cod_entry),10);

  pag_nome_entry = gtk_entry_new();
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_nome_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-direction-ltr");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_nome_entry),30);

  pag_tipo_combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(pag_tipo_combo),"Escolher Modelo");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(pag_tipo_combo),"Intervalo/dias");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(pag_tipo_combo),"Intervalo/Meses");
  gtk_combo_box_set_active(GTK_COMBO_BOX(pag_tipo_combo),1);

  pag_init_spin = gtk_spin_button_new_with_range(1,31,1);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_init_spin),GTK_ENTRY_ICON_PRIMARY,"format-text-direction-ltr");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_init_spin),10);

  pag_parc_spin = gtk_spin_button_new_with_range(1,365,1);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_parc_spin),GTK_ENTRY_ICON_PRIMARY,"format-text-direction-ltr");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_parc_spin),10);

  pag_parc_qnt_spin = gtk_spin_button_new_with_range(1,20,1);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pag_parc_qnt_spin),GTK_ENTRY_ICON_PRIMARY,"view-list");
  gtk_entry_set_width_chars(GTK_ENTRY(pag_parc_qnt_spin),10);

  pag_psq_cod_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(pag_psq_cod_button),gtk_image_new_from_file(IMG_PESQ));

  gtk_box_pack_start(GTK_BOX(pag_psq_cod_box),pag_cod_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(pag_psq_cod_box),pag_psq_cod_button,0,0,0);

  gtk_container_add(GTK_CONTAINER(pag_cod_frame),pag_psq_cod_box);
  gtk_fixed_put(GTK_FIXED(pag_cod_fixed),pag_cod_frame,20,20);

  gtk_container_add(GTK_CONTAINER(pag_nome_frame),pag_nome_entry);
  gtk_fixed_put(GTK_FIXED(pag_nome_fixed),pag_nome_frame,20,20);

  gtk_fixed_put(GTK_FIXED(pag_tipo_fixed),pag_tipo_combo,20,20);

  gtk_box_pack_start(GTK_BOX(pag_dia_fixo_box),pag_dia_fixo_check,0,0,0);
  gtk_box_pack_start(GTK_BOX(pag_dia_fixo_box),pag_init_spin,0,0,0);
  gtk_container_add(GTK_CONTAINER(pag_init_frame),pag_dia_fixo_box);
  gtk_fixed_put(GTK_FIXED(pag_init_fixed),pag_init_frame,20,20);

  gtk_container_add(GTK_CONTAINER(pag_parc_frame),pag_parc_spin);
  gtk_fixed_put(GTK_FIXED(pag_parc_fixed),pag_parc_frame,20,20);

  gtk_container_add(GTK_CONTAINER(pag_parc_qnt_frame),pag_parc_qnt_spin);
  gtk_fixed_put(GTK_FIXED(pag_parc_qnt_fixed),pag_parc_qnt_frame,20,20);

  gtk_box_pack_start(GTK_BOX(pag_datas_box),pag_psq_datas_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(pag_datas_box),pag_datas_tree,0,0,5);

  gtk_container_add(GTK_CONTAINER(pag_datas_frame),pag_datas_box);
  gtk_box_pack_start(GTK_BOX(scrolled_box),pag_datas_frame,0,0,5);
  gtk_container_add(GTK_CONTAINER(scrolled),scrolled_box);
  gtk_fixed_put(GTK_FIXED(pag_datas_fixed),scrolled,220,160);

  gtk_widget_set_size_request(scrolled,220,200);
  gtk_widget_set_size_request(scrolled_box,220,200);

  gtk_container_set_border_width(GTK_CONTAINER(pag_datas_frame),5);
  gtk_frame_set_shadow_type(GTK_FRAME(pag_datas_frame),GTK_SHADOW_OUT);

  gtk_grid_attach(GTK_GRID(pag_grid),pag_cod_fixed,0,1,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_tipo_fixed,0,2,1,1);
  gtk_grid_attach(GTK_GRID(pag_grid),pag_nome_fixed,1,2,1,1);
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

  gtk_layout_put(GTK_LAYOUT(layout),caixa_grande,0,0);
  gtk_layout_put(GTK_LAYOUT(layout),pag_datas_fixed,0,0);

  g_signal_connect(pag_cod_entry,"activate",G_CALLBACK(pag_cod_fun),NULL);
  g_signal_connect(pag_nome_entry,"activate",G_CALLBACK(pag_nome_fun),NULL);
  g_signal_connect(pag_init_spin,"activate",G_CALLBACK(pag_init_fun),NULL);
  g_signal_connect(pag_parc_spin,"activate",G_CALLBACK(pag_parc_fun),NULL);
  g_signal_connect(pag_parc_qnt_spin,"activate",G_CALLBACK(pag_parc_qnt_fun),NULL);
  g_signal_connect(pag_datas_entry,"activate",G_CALLBACK(pag_datas_fun),NULL);

  g_signal_connect(pag_psq_datas_button,"clicked",G_CALLBACK(psq_data),pag_datas_entry);
  g_signal_connect(pag_psq_cod_button,"clicked",G_CALLBACK(psq_pag_cond),pag_cod_entry);


  g_signal_connect(pag_confirmar_button,"clicked",G_CALLBACK(pag_concluir_fun),NULL);
  g_signal_connect(pag_alterar_button,"clicked",G_CALLBACK(pag_alterar_fun),NULL);
  g_signal_connect(pag_cancelar_button,"clicked",G_CALLBACK(pag_cancelar_fun),NULL);
  g_signal_connect(pag_excluir_button,"clicked",G_CALLBACK(pag_excluir_fun),NULL);

  g_signal_connect(pag_dia_fixo_check,"toggled",G_CALLBACK(pag_dia_fixo_fun),NULL);

  g_signal_connect(janela_grupo,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_COND]);

  gtk_widget_set_sensitive(pag_init_spin,FALSE);
  gtk_widget_set_sensitive(pag_datas_entry,FALSE);
  gtk_container_add(GTK_CONTAINER(janela),layout);
  gtk_widget_show_all(janela);

  return 0;
}
