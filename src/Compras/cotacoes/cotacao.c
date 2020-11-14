#include "campos/codigo.c"
#include "campos/participantes.c"
#include "campos/descricao.c"
#include "campos/tipo.c"
#include "campos/status.c"
#include "campos/data.c"
#include "campos/validade.c"

#include "interface/itens_container.c"

#include "campos/itens/produto.c"
#include "campos/itens/participante.c"
#include "campos/itens/preco.c"
#include "campos/itens/quantidade.c"

#include "concluir.c"
#include "alterar.c"
#include "excluir.c"
#include "cancelar.c"

int cotacao_fun(){
	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"req_prods");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Cotação de Materiais");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"edit-find");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_COTAC_WND].reg_id = REG_COTAC_WND;
	janelas_gerenciadas.vetor_janelas[REG_COTAC_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_COTAC_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_COTAC_WND].janela_pointer = janela;

	GtkWidget *cotac_linha1 = gtk_box_new(0,0);
	GtkWidget *cotac_linha2 = gtk_box_new(0,0);
	cotac_partc_itens = gtk_box_new(0,0);
	GtkWidget *cotac_linha4 = gtk_box_new(0,0);
	GtkWidget *cotac_linhas = gtk_box_new(1,0);

	GtkWidget *cotac_code_box = gtk_box_new(0,0);
	GtkWidget *cotac_code_frame = gtk_frame_new("Código");
	GtkWidget *cotac_psq_code = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(cotac_psq_code),gtk_image_new_from_file(IMG_PESQ));
	cotac_code_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(cotac_code_entry),10);
	gtk_box_pack_start(GTK_BOX(cotac_code_box),cotac_code_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_code_box),cotac_psq_code,0,0,0);
	gtk_container_add(GTK_CONTAINER(cotac_code_frame),cotac_code_box);

	GtkWidget *cotac_partc_frame = gtk_frame_new("Participantes");
	cotac_partc_entry = gtk_entry_new();
	GtkWidget *cotac_add_partc_button = gtk_button_new_with_label("Adicionar");
	GtkWidget *cotac_rem_partc_button = gtk_button_new_with_label("Remover");
	GtkWidget *cotac_partc_box = gtk_box_new(0,0);

	cotac_partc_combo = gtk_combo_box_text_new();
	gtk_box_pack_start(GTK_BOX(cotac_partc_box),cotac_partc_combo,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_partc_box),cotac_add_partc_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_partc_box),cotac_rem_partc_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(cotac_partc_frame),cotac_partc_box);

	GtkWidget *cotac_descricao_frame = gtk_frame_new("Descrição");
	cotac_descricao_view = gtk_text_view_new();
	GtkWidget *cotac_descricao_box = gtk_box_new(0,0);
	GtkWidget *cotac_descricao_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(cotac_descricao_view,200,30);
	gtk_widget_set_size_request(cotac_descricao_scroll,200,30);
	gtk_widget_set_size_request(cotac_descricao_box,200,30);
	gtk_widget_set_size_request(cotac_descricao_frame,200,30);
	gtk_container_add(GTK_CONTAINER(cotac_descricao_scroll),cotac_descricao_view);
	gtk_box_pack_start(GTK_BOX(cotac_descricao_box),cotac_descricao_scroll,0,0,0);
	gtk_container_add(GTK_CONTAINER(cotac_descricao_frame),cotac_descricao_box);

	GtkWidget *cotac_status_frame = gtk_frame_new("Status");
	GtkWidget *cotac_status_box = gtk_box_new(0,0);
	cotac_status_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cotac_status_combo),0,"Aberta");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cotac_status_combo),1,"Encerrada");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cotac_status_combo),2,"Pendente Encerramento");
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(cotac_status_combo),3,"Pendente Aprovação");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_status_combo),0);
	gtk_box_pack_start(GTK_BOX(cotac_status_box),cotac_status_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(cotac_status_frame),cotac_status_box);

	GtkWidget *cotac_publica_box = gtk_box_new(0,0);
	GtkWidget *cotac_publica_frame = gtk_frame_new("Tipo");
	cotac_publica_check = gtk_check_button_new_with_label("Cotação Publica?");
	gtk_box_pack_start(GTK_BOX(cotac_publica_box),cotac_publica_check,0,0,0);
	gtk_container_add(GTK_CONTAINER(cotac_publica_frame),cotac_publica_box);

	gtk_box_pack_start(GTK_BOX(cotac_linha1),cotac_code_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha1),cotac_status_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha1),cotac_publica_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha1),cotac_descricao_frame,0,0,0);
	gtk_box_pack_start(GTK_BOX(cotac_linha1),cotac_partc_entry,0,0,5);

	GtkWidget *cotac_data_box = gtk_box_new(0,0);
	GtkWidget *cotac_data_frame = gtk_frame_new("Data");
	cotac_data_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cotac_data_entry),"00/00/00");
	gtk_box_pack_start(GTK_BOX(cotac_data_box),cotac_data_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cotac_data_frame),cotac_data_box);

	GtkWidget *cotac_validade_frame = gtk_frame_new("Validade");
	GtkWidget *cotac_validade_box = gtk_box_new(0,0);
	cotac_validade_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(cotac_validade_box),cotac_validade_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cotac_validade_frame),cotac_validade_box);
	gtk_entry_set_placeholder_text(GTK_ENTRY(cotac_validade_entry),"00/00/00");

	gtk_box_pack_start(GTK_BOX(cotac_linha2),cotac_data_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha2),cotac_validade_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha2),cotac_partc_frame,0,0,5);

	GtkWidget *cotac_confirmar_button = gtk_button_new_with_label("Concluir");
	GtkWidget *cotac_alterar_button = gtk_button_new_with_label("Alterar");
	GtkWidget *cotac_cancelar_button = gtk_button_new_with_label("Cancelar");
	GtkWidget *cotac_excluir_button = gtk_button_new_with_label("Excluir");

	gtk_box_pack_start(GTK_BOX(cotac_linha4),cotac_confirmar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha4),cotac_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha4),cotac_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linha4),cotac_excluir_button,0,0,5);

	gtk_box_pack_start(GTK_BOX(cotac_linhas),cotac_linha1,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linhas),cotac_linha2,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linhas),cotac_partc_itens,0,0,5);
	gtk_box_pack_start(GTK_BOX(cotac_linhas),cotac_linha4,0,0,5);

	cotac_alterando=0;
	cotac_concluindo=0;

	cotac_container_exists = malloc(sizeof(int) *MAX_PARTC_QNT);
	cotac_rec_itens_alter_vetor = malloc(sizeof(int) *MAX_COTAC_ITENS);

	cotac_pPos = malloc(sizeof(int*) *MAX_PARTC_QNT);
  cotac_ativo = malloc(sizeof(int*) *MAX_PARTC_QNT);
	cotac_produto_inserido = malloc(sizeof(int*) *MAX_PARTC_QNT );

	cotac_scroll = malloc(sizeof(GtkWidget**) *MAX_PARTC_QNT);
	cotac_itens_grid = malloc(sizeof(GtkWidget**) *MAX_PARTC_QNT);
	cotac_add_button = malloc( sizeof( GtkWidget** )  *MAX_PARTC_QNT);
	cotac_itens_container = malloc(sizeof(GtkWidget**) *MAX_PARTC_QNT);

	cotac_prod_cod_entry = malloc( sizeof( GtkWidget** ) * MAX_PARTC_QNT);
  cotac_psq_prod_button = malloc (sizeof( GtkWidget** ) * MAX_PARTC_QNT);
  cotac_prod_nome_entry = malloc (sizeof( GtkWidget** ) * MAX_PARTC_QNT);
  cotac_prod_qnt_entry = malloc( sizeof( GtkWidget** ) * MAX_PARTC_QNT);
  cotac_prod_prc_entry = malloc( sizeof( GtkWidget** ) * MAX_PARTC_QNT);
	cotac_rem_button = malloc( sizeof( GtkWidget** ) * MAX_PARTC_QNT);
  cotac_prod_frames = malloc( sizeof( GtkWidget** ) * MAX_PARTC_QNT);

	cotacao_new = malloc(sizeof( struct _cotacao) );
	cotacao_new->cotacao_itens = malloc( sizeof(struct _contacao_itens* ) *MAX_PARTC_QNT );

	for(int cont=0;cont<MAX_PARTC_QNT;cont++){
		cotac_container_exists[cont] = 0;
	}

	gtk_container_add (GTK_CONTAINER(janela),cotac_linhas);
	gtk_widget_show_all(janela);
	gtk_widget_hide(cotac_partc_entry);

	cotacao_cancelar_fun();

	g_signal_connect(cotac_add_partc_button,"clicked",G_CALLBACK(psq_ter),cotac_partc_entry);
	g_signal_connect(cotac_partc_entry,"activate", G_CALLBACK(cotac_partc_fun),NULL);
	g_signal_connect(cotac_code_entry,"activate",G_CALLBACK(cotac_code_fun),NULL);
	g_signal_connect(cotac_data_entry,"activate",G_CALLBACK(cotac_data_fun),NULL);
	g_signal_connect(cotac_validade_entry,"activate",G_CALLBACK(cotac_validade_fun),NULL);

	g_signal_connect(cotac_partc_combo,"changed",G_CALLBACK(cotac_partc_combo_fun),NULL);

	g_signal_connect(cotac_confirmar_button,"clicked",G_CALLBACK(cotacao_concluir_fun),NULL);
	g_signal_connect(cotac_alterar_button,"clicked",G_CALLBACK(cotacao_alterar_fun),NULL);
	g_signal_connect(cotac_cancelar_button,"clicked",G_CALLBACK(cotacao_cancelar_fun),NULL);
	g_signal_connect(cotac_excluir_button,"clicked",G_CALLBACK(cotacao_excluir_fun),NULL);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_COTAC_WND]);
	return 0;
}
