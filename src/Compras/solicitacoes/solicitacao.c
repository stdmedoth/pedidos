#include "campos/codigo.c"
#include "campos/produto.c"
#include "campos/quantidade.c"
#include "campos/descricao.c"
#include "campos/data.c"
#include "campos/prioridade.c"
#include "campos/status.c"
#include "concluir.c"
#include "alterar.c"
#include "excluir.c"
#include "cancelar.c"

int solicitacao(){

	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"req_prods");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Requisição de Materiais");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-update");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_SOLIT_WND].reg_id = REG_SOLIT_WND;
	janelas_gerenciadas.vetor_janelas[REG_SOLIT_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_SOLIT_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_SOLIT_WND].janela_pointer = janela;

	GtkWidget *req_prod_linha1, *req_prod_linha2, *req_prod_linha3, *req_prod_linha4, *req_prod_opcoes, *req_prod_box;

	GtkWidget *req_prod_psq_req, *req_prod_psq_prod;

	GtkWidget *req_prod_code_box,
	*req_prod_descr_box,
	*req_prod_prod_box,
	*req_prod_qnt_box,
	*req_prod_prori_box,
	*req_prod_data_box,
	*req_prod_dtevent_box,
	*req_prod_status_box;


	GtkWidget *req_prod_code_frame,
	*req_prod_descr_frame, *req_prod_descr_scroll,
	*req_prod_prod_frame,
	*req_prod_qnt_frame,
	*req_prod_prori_frame,
	*req_prod_data_frame,
	*req_prod_dtevent_frame,
	*req_prod_status_frame;

	req_prod_psq_req = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(req_prod_psq_req),gtk_image_new_from_file(IMG_PESQ));
	req_prod_psq_prod = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(req_prod_psq_prod),gtk_image_new_from_file(IMG_PESQ));

	req_prod_linha1 = gtk_box_new(0,0);
	req_prod_linha2 = gtk_box_new(0,0);
	req_prod_linha3 = gtk_box_new(0,0);
	req_prod_linha4 = gtk_box_new(0,0);
	req_prod_opcoes = gtk_box_new(0,0);
	req_prod_box = gtk_box_new(1,0);

	req_prod_code_entry = gtk_entry_new();
	req_prod_code_box = gtk_box_new(0,0);
	req_prod_code_frame = gtk_frame_new("Código");
	gtk_entry_set_width_chars(GTK_ENTRY(req_prod_code_entry),8);
	gtk_box_pack_start(GTK_BOX(req_prod_code_box),req_prod_code_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_code_box),req_prod_psq_req,0,0,5);
	gtk_container_add(GTK_CONTAINER(req_prod_code_frame), req_prod_code_box);
	gtk_box_pack_start(GTK_BOX(req_prod_linha1),req_prod_code_frame,0,0,5);

	req_prod_prod_entry = gtk_entry_new();
	req_prod_prod_box = gtk_box_new(0,0);
	req_prod_prod_frame = gtk_frame_new("Produto");
	req_prod_prodnome_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(req_prod_prod_entry),8);
	gtk_box_pack_start(GTK_BOX(req_prod_prod_box),req_prod_prod_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_prod_box),req_prod_psq_prod,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_prod_box),req_prod_prodnome_entry,0,0,5);
	gtk_entry_set_width_chars(GTK_ENTRY(req_prod_prodnome_entry),20);
	gtk_editable_set_editable(GTK_EDITABLE(req_prod_prodnome_entry),FALSE);
	gtk_container_add(GTK_CONTAINER(req_prod_prod_frame), req_prod_prod_box);
	gtk_box_pack_start(GTK_BOX(req_prod_linha2),req_prod_prod_frame,0,0,5);

	req_prod_qnt_spin = gtk_spin_button_new_with_range(1,1000,1);
	req_prod_qnt_box = gtk_box_new(0,0);
	req_prod_qnt_frame = gtk_frame_new("Quantidade");
	gtk_entry_set_width_chars(GTK_ENTRY(req_prod_qnt_spin),8);
	gtk_box_pack_start(GTK_BOX(req_prod_qnt_box),req_prod_qnt_spin,0,0,5);
	gtk_container_add(GTK_CONTAINER(req_prod_qnt_frame), req_prod_qnt_box);
	gtk_box_pack_start(GTK_BOX(req_prod_linha2),req_prod_qnt_frame,0,0,5);

	req_prod_descr_text = gtk_text_view_new();
	req_prod_descr_frame = gtk_frame_new("Descrição");
	req_prod_descr_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_container_add(GTK_CONTAINER(req_prod_descr_scroll), req_prod_descr_text);
	gtk_container_add(GTK_CONTAINER(req_prod_descr_frame), req_prod_descr_scroll);
	gtk_widget_set_size_request(req_prod_descr_scroll,200,50);
	gtk_widget_set_size_request(req_prod_descr_text,200,50);

	gtk_box_pack_start(GTK_BOX(req_prod_linha3),req_prod_descr_frame,0,0,0);

	req_prod_prori_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_prori_combo), 0, "Baixa prioridade");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_prori_combo), 1, "Média prioridade");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_prori_combo), 2, "Alta prioridade");
	gtk_combo_box_set_active(GTK_COMBO_BOX(req_prod_prori_combo),0);
	req_prod_prori_frame = gtk_frame_new("Prioridade");
	gtk_container_add(GTK_CONTAINER(req_prod_prori_frame), req_prod_prori_combo);
	gtk_box_pack_start(GTK_BOX(req_prod_linha3),req_prod_prori_frame,0,0,5);

	req_prod_data_entry = gtk_entry_new();
	req_prod_data_frame = gtk_frame_new("Data Solicitação");
	gtk_container_add(GTK_CONTAINER(req_prod_data_frame), req_prod_data_entry);
	gtk_box_pack_start(GTK_BOX(req_prod_linha4),req_prod_data_frame,0,0,5);

	req_prod_dtevent_entry = gtk_entry_new();
	req_prod_dtevent_frame = gtk_frame_new("Ultimo evento");
	gtk_editable_set_editable(GTK_EDITABLE(req_prod_dtevent_entry),FALSE);
	gtk_container_add(GTK_CONTAINER(req_prod_dtevent_frame), req_prod_dtevent_entry);
	gtk_box_pack_start(GTK_BOX(req_prod_linha4),req_prod_dtevent_frame,0,0,5);

	req_prod_status_combo = gtk_combo_box_text_new();
	req_prod_status_frame = gtk_frame_new("Status");
	gtk_container_add(GTK_CONTAINER(req_prod_status_frame), req_prod_status_combo);
	gtk_box_pack_start(GTK_BOX(req_prod_linha4),req_prod_status_frame,0,0,5);

	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_status_combo), REQ_PROD_PENDENTE , "Pendente");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_status_combo), REQ_PROD_REPREVADO , "Reprovado");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_status_combo), REQ_PROD_APROVADO , "Aprovado");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(req_prod_status_combo), REQ_PROD_CONCLUIDO , "Concluido");
	gtk_combo_box_set_active(GTK_COMBO_BOX(req_prod_status_combo),0);

	req_prod_concluir_button = gtk_button_new_with_label("Concluir");
	req_prod_alterar_button = gtk_button_new_with_label("Alterar");
	req_prod_cancelar_button =  gtk_button_new_with_label("Cancelar");
	req_prod_excluir_button = gtk_button_new_with_label("Excluir");
	gtk_box_pack_start(GTK_BOX(req_prod_opcoes),req_prod_concluir_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_opcoes),req_prod_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_opcoes),req_prod_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_opcoes),req_prod_excluir_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(req_prod_box),req_prod_linha1,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_box),req_prod_linha2,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_box),req_prod_linha3,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_box),req_prod_linha4,0,0,5);
	gtk_box_pack_start(GTK_BOX(req_prod_box),req_prod_opcoes,0,0,5);

	gtk_container_add(GTK_CONTAINER(janela), req_prod_box);
	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_SOLIT_WND]);
	g_signal_connect(req_prod_psq_req,"clicked",G_CALLBACK(psq_prod),req_prod_code_entry);
	g_signal_connect(req_prod_psq_prod,"clicked",G_CALLBACK(psq_prod),req_prod_prod_entry);

	g_signal_connect(req_prod_code_entry,"activate",G_CALLBACK(req_prod_code_fun),NULL);
	g_signal_connect(req_prod_prod_entry,"activate",G_CALLBACK(req_prod_prod_fun),NULL);
	g_signal_connect(req_prod_qnt_spin,"activate",G_CALLBACK(req_prod_qnt_fun),NULL);
	g_signal_connect(req_prod_data_entry,"activate",G_CALLBACK(req_prod_data_fun),NULL);

	g_signal_connect(req_prod_concluir_button,"clicked",G_CALLBACK(req_prod_concluir_fun),NULL);
	g_signal_connect(req_prod_alterar_button,"clicked",G_CALLBACK(req_prod_alterar_fun),NULL);
	g_signal_connect(req_prod_excluir_button,"clicked",G_CALLBACK(req_prod_excluir_fun),NULL);
	g_signal_connect(req_prod_cancelar_button,"clicked",G_CALLBACK(req_prod_cancelar_fun),NULL);
	req_prod_cancelar_fun();
	gtk_widget_show_all(janela);
	return 0;
}
