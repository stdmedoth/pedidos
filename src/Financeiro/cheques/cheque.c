#include "acoes/concluir.c"
#include "acoes/cancelar.c"
#include "acoes/excluir.c"
#include "acoes/alterar.c"

#include "campos/cheque_code.c"
#include "campos/cheque_bnc.c"
#include "campos/cheque_conta.c"
#include "campos/cheque_serie.c"
#include "campos/cheque_numero.c"
#include "campos/cheque_pgnt.c"
#include "campos/cheque_dtemissao.c"
#include "campos/cheque_tipo.c"
#include "campos/cheque_status.c"
#include "campos/cheque_valor.c"

struct _cheque *cheque_get_simple_cheque(int cheque_code){

	MYSQL_ROW row;
	MYSQL_RES *res;
	char query[MAX_QUERY_LEN];

	sprintf(query, "select *, DATE_FORMAT(data_emissao, '%%d/%%m/%%Y') from cheque where code = %i", cheque_code);
	if(!(res = consultar(query))){
		return NULL;
	}

	if(!(row = mysql_fetch_row(res))){
		return NULL;
	}

	struct _cheque *cheque = malloc(sizeof(struct _cheque));

	cheque->code = atoi(row[CHEQUE_CODE_COL]);
	
	struct _banco *banco = malloc(sizeof(struct _banco ));
	banco->code = atoi(row[CHEQUE_BNC_COL]);
	cheque->banco = banco;
	
	cheque->conta = strdup(row[CHEQUE_CONTA_COL]);
	cheque->serie = strdup(row[CHEQUE_SERIE_COL]);
	cheque->numero = strdup(row[CHEQUE_NUM_COL]);

	cheque->tipo = atoi(row[CHEQUE_TIPO_COL]);
	cheque->status = atoi(row[CHEQUE_STAT_COL]);
	
	struct _terc_infos *pagante = malloc(sizeof(struct _terc_infos));
	pagante->code = atoi(row[CHEQUE_PAGNT_COL]);
	cheque->pagante = pagante;
	
	cheque->data_emissao = strdup(row[CHEQUE_NUM_ROWS]);
	cheque->valor = atof(row[CHEQUE_VLR_COL]);
	
	return cheque;

}

struct _cheque *cheque_get_cheque(int cheque_code){

	MYSQL_ROW row;
	MYSQL_RES *res;
	char query[MAX_QUERY_LEN];

	sprintf(query, "select * from cheque where code = %i", cheque_code);
	if(!(res = consultar(query))){
		return NULL;
	}

	if(!(row = mysql_fetch_row(res))){
		return NULL;
	}

	struct _cheque *cheque = malloc(sizeof(struct _cheque));
	cheque->code = atoi(row[CHEQUE_CODE_COL]);
	
	cheque->banco = get_banco(atoi(row[CHEQUE_BNC_COL]));
	if(!cheque->banco)
		return NULL;

	cheque->conta = strdup(row[CHEQUE_CONTA_COL]);
	cheque->serie = strdup(row[CHEQUE_SERIE_COL]);
	cheque->numero = strdup(row[CHEQUE_NUM_COL]);
	cheque->pagante = terceiros_get_simp_terceiro(atoi(row[CHEQUE_PAGNT_COL]));
	cheque->data_emissao = strdup(row[CHEQUE_DT_EMSSAO_COL]);
	cheque->valor = atof(row[CHEQUE_VLR_COL]);
	return cheque;
}

int cheque_wnd_fun(){

	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Cadastro de Cheques");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"document-edit");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	GtkWidget 
	*box = gtk_box_new(1,0), 
	*fixed = gtk_fixed_new(), 
	*frame = gtk_frame_new("Cheques");
	GtkWidget 
	*linha1 = gtk_box_new(0,0), 
	*linha2 = gtk_box_new(0,0), 
	*linha3 = gtk_box_new(0,0),
	*linha4 = gtk_box_new(0,0),
	*linha5 = gtk_box_new(0,0),
	*linha6 = gtk_box_new(0,0);
	
	GtkWidget *box_opcoes = gtk_box_new(0,0);
	cheque_concluir_button = gtk_button_new_with_label("Concluir");
  	gtk_button_set_image(GTK_BUTTON(cheque_concluir_button),gtk_image_new_from_file(IMG_OK));
  	cheque_cancelar_button = gtk_button_new_with_label("Cancelar");
  	gtk_button_set_image(GTK_BUTTON(cheque_cancelar_button),gtk_image_new_from_file(IMG_CANCEL));
  	cheque_excluir_button = gtk_button_new_with_label("Excluir");
  	gtk_button_set_image(GTK_BUTTON(cheque_excluir_button),gtk_image_new_from_file(IMG_EXCLUI));
  	cheque_alterar_button = gtk_button_new_with_label("Alterar");
  	gtk_button_set_image(GTK_BUTTON(cheque_alterar_button),gtk_image_new_from_file(IMG_ALTER));
  	gtk_box_pack_start(GTK_BOX(box_opcoes), cheque_concluir_button , 0,0,5);
  	gtk_box_pack_start(GTK_BOX(box_opcoes), cheque_alterar_button , 0,0,5);
  	gtk_box_pack_start(GTK_BOX(box_opcoes), cheque_cancelar_button , 0,0,5);
  	gtk_box_pack_start(GTK_BOX(box_opcoes), cheque_excluir_button , 0,0,5);


	cheque_code_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(cheque_code_entry), 5);
	cheque_psqcode_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(cheque_psqcode_button), gtk_image_new_from_file(IMG_PESQ));
	GtkWidget *cheque_code_frame = gtk_frame_new("Código");
	GtkWidget *cheque_code_box = gtk_box_new(0,0);
	GtkWidget *cheque_code_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_code_box), cheque_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cheque_code_box), cheque_psqcode_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_code_frame), cheque_code_box);
	gtk_fixed_put(GTK_FIXED(cheque_code_fixed), cheque_code_frame, 5, 5);

	cheque_bnccode_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(cheque_bnccode_entry), 5);
	cheque_bncpsqcode_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(cheque_bncpsqcode_button), gtk_image_new_from_file(IMG_PESQ));
	cheque_bncnome_entry = gtk_entry_new();
	GtkWidget *cheque_bnccode_frame = gtk_frame_new("Banco");
	GtkWidget *cheque_bnccode_box = gtk_box_new(0,0);
	GtkWidget *cheque_bnccode_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_bnccode_box), cheque_bnccode_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cheque_bnccode_box), cheque_bncpsqcode_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(cheque_bnccode_box), cheque_bncnome_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(cheque_bnccode_frame), cheque_bnccode_box);
	gtk_fixed_put(GTK_FIXED(cheque_bnccode_fixed), cheque_bnccode_frame, 10, 10);

	cheque_conta_entry = gtk_entry_new();
	GtkWidget *cheque_conta_frame = gtk_frame_new("Conta");
	GtkWidget *cheque_conta_box = gtk_box_new(0,0);
	GtkWidget *cheque_conta_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_conta_box), cheque_conta_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_conta_frame), cheque_conta_box);
	gtk_fixed_put(GTK_FIXED(cheque_conta_fixed), cheque_conta_frame, 10, 10);

	cheque_serie_entry = gtk_entry_new();
	GtkWidget *cheque_serie_frame = gtk_frame_new("Série");
	GtkWidget *cheque_serie_box = gtk_box_new(0,0);
	GtkWidget *cheque_serie_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_serie_box), cheque_serie_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_serie_frame), cheque_serie_box);
	gtk_fixed_put(GTK_FIXED(cheque_serie_fixed), cheque_serie_frame, 10, 10);

	cheque_numero_entry = gtk_entry_new();
	GtkWidget *cheque_numero_frame = gtk_frame_new("Número");
	GtkWidget *cheque_numero_box = gtk_box_new(0,0);
	GtkWidget *cheque_numero_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_numero_box), cheque_numero_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_numero_frame), cheque_numero_box);
	gtk_fixed_put(GTK_FIXED(cheque_numero_fixed), cheque_numero_frame, 10, 10);

	cheque_status_combo = gtk_combo_box_text_new();
	GtkWidget *cheque_status_frame = gtk_frame_new("Status");
	GtkWidget *cheque_status_box = gtk_box_new(0,0);
	GtkWidget *cheque_status_fixed = gtk_fixed_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cheque_status_combo), inttochar(CHEQUE_STAT_APRESENTADO), "Apresentado");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cheque_status_combo), inttochar(CHEQUE_STAT_CANCELADO), "Cancelado");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cheque_status_combo), inttochar(CHEQUE_STAT_ENDOSSADO), "Endossado");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cheque_status_combo), inttochar(CHEQUE_STAT_COMPENSADO), "Compenssado");
	gtk_box_pack_start(GTK_BOX(cheque_status_box), cheque_status_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_status_frame), cheque_status_box);
	gtk_fixed_put(GTK_FIXED(cheque_status_fixed), cheque_status_frame, 10, 10);

	cheque_tipo_combo = gtk_combo_box_text_new();
	GtkWidget *cheque_tipo_frame = gtk_frame_new("Tipo");
	GtkWidget *cheque_tipo_box = gtk_box_new(0,0);
	GtkWidget *cheque_tipo_fixed = gtk_fixed_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cheque_tipo_combo), inttochar(CHEQUE_TIPO_PAGAR), "Pagar");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cheque_tipo_combo), inttochar(CHEQUE_TIPO_RECEBER), "Receber");
	gtk_box_pack_start(GTK_BOX(cheque_tipo_box), cheque_tipo_combo,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_tipo_frame), cheque_tipo_box);
	gtk_fixed_put(GTK_FIXED(cheque_tipo_fixed), cheque_tipo_frame, 10, 10);

	cheque_pgntcode_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(cheque_pgntcode_entry), 5);
	cheque_pgntpsqcode_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(cheque_pgntpsqcode_button), gtk_image_new_from_file(IMG_PESQ));
	cheque_pgntnome_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(cheque_pgntnome_entry), 30);
	GtkWidget *cheque_pgntcode_frame = gtk_frame_new("Pagante");
	GtkWidget *cheque_pgntcode_box = gtk_box_new(0,0);
	GtkWidget *cheque_pgntcode_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_pgntcode_box), cheque_pgntcode_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cheque_pgntcode_box), cheque_pgntpsqcode_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(cheque_pgntcode_box), cheque_pgntnome_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(cheque_pgntcode_frame), cheque_pgntcode_box);
	gtk_fixed_put(GTK_FIXED(cheque_pgntcode_fixed), cheque_pgntcode_frame, 10, 10);

	cheque_dtemissao_entry = gtk_entry_new();
	GtkWidget *cheque_dtemissao_frame = gtk_frame_new("Emissão");
	GtkWidget *cheque_dtemissao_box = gtk_box_new(0,0);
	GtkWidget *cheque_dtemissao_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_dtemissao_box), cheque_dtemissao_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_dtemissao_frame), cheque_dtemissao_box);
	gtk_fixed_put(GTK_FIXED(cheque_dtemissao_fixed), cheque_dtemissao_frame, 10, 10);

	cheque_valor_entry = gtk_entry_new();
	GtkWidget *cheque_valor_frame = gtk_frame_new("Valor");
	GtkWidget *cheque_valor_box = gtk_box_new(0,0);
	GtkWidget *cheque_valor_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(cheque_valor_box), cheque_valor_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(cheque_valor_frame), cheque_valor_box);
	gtk_fixed_put(GTK_FIXED(cheque_valor_fixed), cheque_valor_frame, 10, 10);

	gtk_box_pack_start(GTK_BOX(linha1), cheque_code_fixed, 0,0, 5);
	
	gtk_box_pack_start(GTK_BOX(linha2), cheque_bnccode_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha2), cheque_conta_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha3), cheque_serie_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha3), cheque_numero_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha4), cheque_pgntcode_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha5), cheque_status_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha5), cheque_tipo_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha6), cheque_dtemissao_fixed, 0,0, 5);
	gtk_box_pack_start(GTK_BOX(linha6), cheque_valor_fixed, 0,0, 5);

	gtk_box_pack_start(GTK_BOX(box), linha1, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(box), linha2, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(box), linha3, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(box), linha4, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(box), linha5, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(box), box_opcoes, 0, 0, 5);
	

	gtk_fixed_put(GTK_FIXED(fixed), box, 10, 10);
	gtk_container_add(GTK_CONTAINER(frame), fixed);

	gtk_container_add(GTK_CONTAINER(janela), frame);

	janelas_gerenciadas.vetor_janelas[CAD_CHEQUES_WND].reg_id = CAD_CHEQUES_WND;
	janelas_gerenciadas.vetor_janelas[CAD_CHEQUES_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[CAD_CHEQUES_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[CAD_CHEQUES_WND].janela_pointer = janela;

	gtk_widget_show_all(janela);
 	
	g_signal_connect(cheque_concluir_button, "clicked", G_CALLBACK(cheque_concluir_fun), NULL);
	g_signal_connect(cheque_alterar_button, "clicked", G_CALLBACK(cheque_alterar_fun), NULL);
	g_signal_connect(cheque_cancelar_button, "clicked", G_CALLBACK(cheque_cancelar_fun), NULL);
	g_signal_connect(cheque_excluir_button, "clicked", G_CALLBACK(cheque_excluir_fun), NULL);

 	g_signal_connect(cheque_psqcode_button ,"clicked", G_CALLBACK(psq_cheq), cheque_code_entry);
 	g_signal_connect(cheque_pgntpsqcode_button, "clicked", G_CALLBACK(psq_ter), cheque_pgntcode_entry);
 	g_signal_connect(cheque_bncpsqcode_button, "clicked", G_CALLBACK(psq_bnc), cheque_bnccode_entry);

 	g_signal_connect(cheque_code_entry, "activate", G_CALLBACK(cheque_code_fun), NULL);
 	g_signal_connect(cheque_bnccode_entry, "activate", G_CALLBACK(cheque_bnc_fun), NULL);
 	
 	g_signal_connect(cheque_conta_entry, "activate", G_CALLBACK(cheque_conta_fun), NULL);
 	g_signal_connect(cheque_serie_entry, "activate", G_CALLBACK(cheque_serie_fun), NULL);
 	g_signal_connect(cheque_numero_entry, "activate", G_CALLBACK(cheque_numero_fun), NULL);

 	g_signal_connect(cheque_pgntcode_entry, "activate", G_CALLBACK(cheque_pgnt_fun), NULL);
 	g_signal_connect(cheque_dtemissao_entry, "activate", G_CALLBACK(cheque_dtemissao_fun), NULL);
 	g_signal_connect(cheque_valor_entry, "activate", G_CALLBACK(cheque_valor_fun), NULL);
 	
  	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[CAD_CHEQUES_WND]);
 

  	cheque_cancelar_fun();
  	return 0;
}