#include "campos/code.c"
#include "campos/fornecedor.c"
#include "campos/dtemissao.c"
#include "campos/dtentrega.c"
#include "campos/condpag.c"
#include "campos/status.c"

#include "campos/itens.c"

#include "concluir.c"
#include "alterar.c"
#include "excluir.c"
#include "cancelar.c"

int ordem_cmp(){
	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_widget_set_name(janela,"ordem_cmp");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Ordem de Compras");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"edit-find");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_ORDCMP_WND].reg_id = REG_ORDCMP_WND;
	janelas_gerenciadas.vetor_janelas[REG_ORDCMP_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_ORDCMP_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_ORDCMP_WND].janela_pointer = janela;

	GtkWidget *ordem_cmp_code_frame,
		*ordem_cmp_dtemissao_frame,
		*ordem_cmp_dtentrega_frame,
		*ordem_cmp_status_frame,
		*ordem_cmp_condpag_frame,
		*ordem_cmp_forncode_frame,
		*ordem_cmp_obs_frame;

	GtkWidget *ordem_cmp_code_box,
		*ordem_cmp_dtemissao_box,
		*ordem_cmp_dtentrega_box,
		*ordem_cmp_status_box,
		*ordem_cmp_condpag_box,
		*ordem_cmp_forncode_box,
		*ordem_cmp_obs_box;

	GtkWidget *ordem_cmp_code_fixed,
		*ordem_cmp_dtemissao_fixed,
		*ordem_cmp_dtentrega_fixed,
		*ordem_cmp_status_fixed,
		*ordem_cmp_condpag_fixed,
		*ordem_cmp_forncode_fixed,
		*ordem_cmp_obs_fixed;

	GtkWidget *ordem_cmp_req_frame,
		*ordem_cmp_ordreq_frame;

	GtkWidget *ordem_cmp_req_scroll,
		*ordem_cmp_ordreq_scroll;

	GtkWidget *box,
		*linha1,
		*linha2,
		*linha3,
		*linha4,
		*opcoes_box;

	enum {
		ID_COLUMN,
		PROD_NOME_COLUMN,
		PROD_QNT_COLUMN,
		PROD_VLR_COLUMN,
		N_COLUMNS
	};

	box = gtk_box_new(1,0);
	linha1 = gtk_box_new(0,0);
	linha2 = gtk_box_new(0,0);
	linha3 = gtk_box_new(0,0);
	linha4 = gtk_box_new(0,0);
	opcoes_box = gtk_box_new(0,0);

	ordem_cmp_concluir_button = gtk_button_new_with_label("Concluir");
  ordem_cmp_alterar_button = gtk_button_new_with_label("Alterar");
  ordem_cmp_excluir_button = gtk_button_new_with_label("Excluir");
  ordem_cmp_cancelar_button = gtk_button_new_with_label("Cancelar");

	ordem_cmp_code_frame = gtk_frame_new("Código");
	ordem_cmp_dtemissao_frame = gtk_frame_new("Data Emissão");
	ordem_cmp_dtentrega_frame = gtk_frame_new("Data Entrega");
	ordem_cmp_status_frame = gtk_frame_new("Status");
	ordem_cmp_condpag_frame = gtk_frame_new("Condição Pagamento");
	ordem_cmp_forncode_frame = gtk_frame_new("Fornecedor");
	ordem_cmp_obs_frame = gtk_frame_new("Observações");

	ordem_cmp_code_box = gtk_box_new(0,0);
	ordem_cmp_dtemissao_box = gtk_box_new(0,0);
	ordem_cmp_dtentrega_box = gtk_box_new(0,0);
	ordem_cmp_status_box = gtk_box_new(0,0);
	ordem_cmp_condpag_box = gtk_box_new(0,0);
	ordem_cmp_forncode_box = gtk_box_new(0,0);
	ordem_cmp_obs_box = gtk_box_new(0,0);

	ordem_cmp_code_fixed = gtk_fixed_new();
	ordem_cmp_dtemissao_fixed = gtk_fixed_new();
	ordem_cmp_dtentrega_fixed = gtk_fixed_new();
	ordem_cmp_status_fixed = gtk_fixed_new();
	ordem_cmp_condpag_fixed = gtk_fixed_new();
	ordem_cmp_forncode_fixed = gtk_fixed_new();
	ordem_cmp_obs_view = gtk_fixed_new();

	ordem_cmp_code_entry = gtk_entry_new();
	ordem_cmp_dtemissao_entry = gtk_entry_new();
	ordem_cmp_dtentrega_entry = gtk_entry_new();
	ordem_cmp_condpag_entry = gtk_entry_new();
	ordem_cmp_status_combo = gtk_combo_box_text_new();
	ordem_cmp_forncode_entry = gtk_entry_new();
	ordem_cmp_obs_view = gtk_entry_new();
	ordem_cmp_condpagnome_entry = gtk_entry_new();
	ordem_cmp_fornnome_entry = gtk_entry_new();

	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(ordem_cmp_status_combo), ORDCMP_N_ENVIADO, "Não enviada");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(ordem_cmp_status_combo), ORD_CMP_ENVIADO, "Enviada");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(ordem_cmp_status_combo), ORD_CMP_CONCLUIDA, "Concluída");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(ordem_cmp_status_combo), ORD_CMP_CANCELADA, "Cancelada");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ordem_cmp_status_combo),0);

	ordem_cmp_req_scroll = gtk_scrolled_window_new(NULL, NULL);
	ordem_cmp_ordreq_scroll = gtk_scrolled_window_new(NULL, NULL);
	ordem_cmp_req_frame = gtk_frame_new("Requisições");
	ordem_cmp_req_treeview = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(ordem_cmp_req_frame), ordem_cmp_req_treeview);
	ordem_cmp_ordreq_frame = gtk_frame_new("Selecionadas");
	ordem_cmp_ordreq_treeview = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(ordem_cmp_ordreq_frame), ordem_cmp_ordreq_treeview);
	gtk_widget_set_size_request(ordem_cmp_req_treeview, 500, 300);
	gtk_widget_set_size_request(ordem_cmp_req_frame, 500, 300);
	gtk_widget_set_size_request(ordem_cmp_ordreq_treeview, 500, 300);
	gtk_widget_set_size_request(ordem_cmp_ordreq_frame, 500, 300);

	GtkTreeViewColumn *reqidColumn = gtk_tree_view_column_new_with_attributes("Id", gtk_cell_renderer_text_new(), "text", ID_COLUMN, NULL);
	GtkTreeViewColumn *reqnomeColumn = gtk_tree_view_column_new_with_attributes("Nome Produto", gtk_cell_renderer_text_new(), "text", PROD_NOME_COLUMN, NULL);
	GtkTreeViewColumn *reqqntColumn = gtk_tree_view_column_new_with_attributes("Quantidade", gtk_cell_renderer_text_new(), "text", PROD_QNT_COLUMN, NULL);
	GtkTreeViewColumn *reqvlrColumn = gtk_tree_view_column_new_with_attributes("Valor", gtk_cell_renderer_text_new(), "text", PROD_VLR_COLUMN, NULL);

	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_req_treeview),reqidColumn);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_req_treeview),reqnomeColumn);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_req_treeview),reqqntColumn);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_req_treeview),reqvlrColumn);
	gtk_tree_view_column_set_visible(reqidColumn, FALSE);

	GtkTreeViewColumn *ordreqidColumn = gtk_tree_view_column_new_with_attributes("Id", gtk_cell_renderer_text_new(), "text", ID_COLUMN, NULL);
	GtkTreeViewColumn *ordreqnomeColumn = gtk_tree_view_column_new_with_attributes("Nome Produto", gtk_cell_renderer_text_new(), "text", PROD_NOME_COLUMN, NULL);
	GtkTreeViewColumn *ordreqqntColumn = gtk_tree_view_column_new_with_attributes("Quantidade", gtk_cell_renderer_text_new(), "text", PROD_QNT_COLUMN, NULL);
	GtkTreeViewColumn *ordreqvlrColumn = gtk_tree_view_column_new_with_attributes("Valor", gtk_cell_renderer_text_new(), "text", PROD_VLR_COLUMN, NULL);

	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),ordreqidColumn);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),ordreqnomeColumn);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),ordreqqntColumn);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),ordreqvlrColumn);
	gtk_tree_view_column_set_visible(ordreqidColumn, FALSE);

	GtkTreeStore *modelo_req = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	GtkTreeStore *modelo_ordreq = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_req_treeview), GTK_TREE_MODEL(modelo_req));
	gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview), GTK_TREE_MODEL(modelo_ordreq));

	ordem_cmp_codepsq_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(ordem_cmp_codepsq_button), gtk_image_new_from_file(IMG_PESQ));
	ordem_cmp_condpagpsq_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(ordem_cmp_condpagpsq_button), gtk_image_new_from_file(IMG_PESQ));
  ordem_cmp_fornpsq_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(ordem_cmp_fornpsq_button), gtk_image_new_from_file(IMG_PESQ));

	gtk_box_pack_start(GTK_BOX(ordem_cmp_code_box), ordem_cmp_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(ordem_cmp_code_box), ordem_cmp_codepsq_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(ordem_cmp_code_frame), ordem_cmp_code_box);
	gtk_fixed_put(GTK_FIXED(ordem_cmp_code_fixed), ordem_cmp_code_frame,5,5);
	gtk_entry_set_width_chars(GTK_ENTRY(ordem_cmp_code_entry), 8);

	gtk_box_pack_start(GTK_BOX(ordem_cmp_forncode_box), ordem_cmp_forncode_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(ordem_cmp_forncode_box), ordem_cmp_fornpsq_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(ordem_cmp_forncode_box), ordem_cmp_fornnome_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(ordem_cmp_forncode_frame), ordem_cmp_forncode_box);
	gtk_fixed_put(GTK_FIXED(ordem_cmp_forncode_fixed), ordem_cmp_forncode_frame,5,5);
	gtk_entry_set_width_chars(GTK_ENTRY(ordem_cmp_forncode_entry), 8);
	gtk_entry_set_width_chars(GTK_ENTRY(ordem_cmp_fornnome_entry), 30);

	gtk_box_pack_start(GTK_BOX(ordem_cmp_condpag_box), ordem_cmp_condpag_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(ordem_cmp_condpag_box), ordem_cmp_condpagpsq_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(ordem_cmp_condpag_box), ordem_cmp_condpagnome_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(ordem_cmp_condpag_frame), ordem_cmp_condpag_box);
	gtk_fixed_put(GTK_FIXED(ordem_cmp_condpag_fixed), ordem_cmp_condpag_frame,5,5);
	gtk_entry_set_width_chars(GTK_ENTRY(ordem_cmp_condpag_entry), 8);

	gtk_box_pack_start(GTK_BOX(ordem_cmp_status_box), ordem_cmp_status_combo,0,0,5);
	gtk_container_add(GTK_CONTAINER(ordem_cmp_status_frame), ordem_cmp_status_box);
	gtk_fixed_put(GTK_FIXED(ordem_cmp_status_fixed), ordem_cmp_status_frame,5,5);

	gtk_box_pack_start(GTK_BOX(ordem_cmp_dtemissao_box), ordem_cmp_dtemissao_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(ordem_cmp_dtemissao_frame), ordem_cmp_dtemissao_box);
	gtk_fixed_put(GTK_FIXED(ordem_cmp_dtemissao_fixed), ordem_cmp_dtemissao_frame,5,5);

	gtk_box_pack_start(GTK_BOX(ordem_cmp_dtentrega_box), ordem_cmp_dtentrega_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(ordem_cmp_dtentrega_frame), ordem_cmp_dtentrega_box);
	gtk_fixed_put(GTK_FIXED(ordem_cmp_dtentrega_fixed), ordem_cmp_dtentrega_frame,5,5);

	gtk_box_pack_start(GTK_BOX(linha1), ordem_cmp_code_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha1), ordem_cmp_status_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha2), ordem_cmp_forncode_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3), ordem_cmp_dtemissao_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3), ordem_cmp_dtentrega_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha3), ordem_cmp_condpag_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha4), ordem_cmp_req_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(linha4), ordem_cmp_ordreq_frame,0,0,5);

	gtk_box_pack_start(GTK_BOX(opcoes_box), ordem_cmp_concluir_button ,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box), ordem_cmp_alterar_button ,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box), ordem_cmp_excluir_button ,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box), ordem_cmp_cancelar_button ,0,0,5);

	gtk_box_pack_start(GTK_BOX(box), linha1,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), linha2,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), linha3,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), linha4,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), opcoes_box,0,0,5);

	ordem_cmp_cancelar_fun();

	gtk_container_add(GTK_CONTAINER(janela), box);
	gtk_widget_show_all(janela);

	g_signal_connect(ordem_cmp_code_entry, "activate", G_CALLBACK(ordem_cmp_code_fun), NULL);

	g_signal_connect(ordem_cmp_concluir_button, "clicked", G_CALLBACK(ordem_cmp_concluir_fun), NULL);
	g_signal_connect(ordem_cmp_alterar_button, "clicked", G_CALLBACK(ordem_cmp_alterar_fun), NULL);
	g_signal_connect(ordem_cmp_cancelar_button, "clicked", G_CALLBACK(ordem_cmp_cancelar_fun), NULL);
	g_signal_connect(ordem_cmp_excluir_button, "clicked", G_CALLBACK(ordem_cmp_excluir_fun), NULL);

	g_signal_connect(ordem_cmp_forncode_entry, "activate", G_CALLBACK(ordem_cmp_fornecedor_fun), NULL);
	g_signal_connect(ordem_cmp_dtemissao_entry, "activate", G_CALLBACK(ordem_cmp_dtemissao_fun), NULL);
	g_signal_connect(ordem_cmp_dtentrega_entry, "activate", G_CALLBACK(ordem_cmp_dtentrega_fun), NULL);
	g_signal_connect(ordem_cmp_condpag_entry, "activate", G_CALLBACK(ordem_cmp_condpag_fun), NULL);

	g_signal_connect(ordem_cmp_condpagpsq_button, "clicked", G_CALLBACK(psq_pag_cond), ordem_cmp_condpag_entry);
	g_signal_connect(ordem_cmp_fornpsq_button, "clicked", G_CALLBACK(psq_ter), ordem_cmp_forncode_entry);

	g_signal_connect(ordem_cmp_req_treeview,"row-activated",G_CALLBACK(ordem_cmp_selecionar_req),NULL);
	g_signal_connect(ordem_cmp_ordreq_treeview,"row-activated",G_CALLBACK(ordem_cmp_deselecionar_req),NULL);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_ORDCMP_WND]);

	return 0;
}
