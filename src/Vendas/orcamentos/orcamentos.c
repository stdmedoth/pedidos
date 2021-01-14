#include "campos.c"
#include "get.c"
//#include "campos/rec_orc_infos.c"

int vnd_orc(){

	char code[10];
	tracelogger_set_func_name("vnd_orc");
	//campos gerais
	//GtkWidget *qnt_volumes_label,*valor_total_label;
	GtkWidget *orc_bnc_box, *orc_bnc_fixed, *orc_bnc_frame;
	GtkWidget *financeiro_box, *orc_box_datas;
	if(janelas_gerenciadas.vetor_janelas[REG_CAD_ORC].aberta == 0)
		janela_orcamento = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_transient_for(GTK_WINDOW(janela_orcamento),GTK_WINDOW(janela_principal));
	gtk_widget_set_size_request(janela_orcamento,1340,500);
	gtk_window_set_title(GTK_WINDOW(janela_orcamento),"Orçamentos");
	gtk_window_set_position(GTK_WINDOW(janela_orcamento),3);
	gtk_window_set_icon_name(GTK_WINDOW(janela_orcamento),"document-revert");

	janelas_gerenciadas.vetor_janelas[REG_CAD_ORC].reg_id = REG_CAD_ORC;
	janelas_gerenciadas.vetor_janelas[REG_CAD_ORC].aberta = 1;
	if(ger_janela_aberta(janela_orcamento, &janelas_gerenciadas.vetor_janelas[REG_CAD_ORC]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_ORC].janela_pointer = janela_orcamento;

	orc_notebook = gtk_notebook_new();

	if(orc_estoque.produtos)
		orc_estoque.produtos = realloc(orc_estoque.produtos, sizeof(struct _orc_estoque_prods* ) * MAX_PROD_ORC);
	else
		orc_estoque.produtos = malloc( sizeof(struct _orc_estoque_prods* ) * MAX_PROD_ORC);

	item_frame_char = malloc(strlen("Item ")+10);

	orc_infos_fixed = gtk_fixed_new();
	orc_itens_fixed = gtk_fixed_new();
	orc_geral_fixed = gtk_fixed_new();

	codigo_orc_gchar = malloc(MAX_CODE_LEN);
	cliente_orc_gchar = malloc(MAX_CODE_LEN);
	orc_ter_obs_char = malloc(MAX_OBS_LEN);
	preco_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	qnt_prod_orc_gchar = malloc(MAX_CODE_LEN);
	desconto_prod_orc_gchar = malloc(MAX_PRECO_LEN);

	codigo_orc_label = gtk_label_new("Orçamento:");
	codigo_orc_entry = gtk_entry_new();
	copia_orc_button = gtk_button_new();
	pesquisa_orc = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(pesquisa_orc),gtk_image_new_from_file(IMG_PROCR));
	gtk_button_set_image(GTK_BUTTON(copia_orc_button),gtk_image_new_from_icon_name("edit-copy",GTK_ICON_SIZE_SMALL_TOOLBAR));
	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	codigo_orc_box = gtk_box_new(0,0);
	codigo_orc_frame = gtk_frame_new("Código do Orçamento");
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),codigo_orc_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),codigo_orc_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),pesquisa_orc,0,0,5);
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),copia_orc_button,0,0,5);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_orc_entry),8);
	gtk_container_add(GTK_CONTAINER(codigo_orc_frame),codigo_orc_box);

	operacao_orc_label = gtk_label_new("Operação:");
	operacao_orc_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(operacao_orc_combo),0,"Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operacao_orc_combo),"Devolução Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operacao_orc_combo),"Compra");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operacao_orc_combo),"Devolução Compra");
	gtk_combo_box_set_active(GTK_COMBO_BOX(operacao_orc_combo),0);

	operacao_orc_box = gtk_box_new(0,0);
	operacao_orc_frame = gtk_frame_new("Tipo de Operação");
	gtk_box_pack_start(GTK_BOX(operacao_orc_box),operacao_orc_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(operacao_orc_box),operacao_orc_combo,0,0,52);
	gtk_container_add(GTK_CONTAINER(operacao_orc_frame),operacao_orc_box);

	cliente_orc_label = gtk_label_new("Cliente: ");
	cliente_orc_entry = gtk_entry_new();
	pesquisa_ter = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(pesquisa_ter),gtk_image_new_from_file(IMG_PESQ));
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_entry),"Código");
	cliente_orc_name_entry = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(cliente_orc_name_entry),FALSE);
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_name_entry),"Nome");
	cliente_orc_end_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_end_entry),"Endereco");
	gtk_editable_set_editable(GTK_EDITABLE(cliente_orc_end_entry),FALSE);
	cliente_orc_tel_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_tel_entry),"Telefone");
	gtk_editable_set_editable(GTK_EDITABLE(cliente_orc_tel_entry),FALSE);
	cliente_orc_box = gtk_box_new(0,0);

	orc_bnc_box = gtk_box_new(0,0);
	orc_bnc_fixed = gtk_fixed_new();
	orc_bnc_frame = gtk_frame_new("Banco");
	orc_bnc_psq_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(orc_bnc_psq_button),gtk_image_new_from_file(IMG_PESQ));
	orc_bnc_code_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(orc_bnc_code_entry),10);
	orc_bnc_nome_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(orc_bnc_nome_entry),20);

	gtk_editable_set_editable(GTK_EDITABLE(orc_bnc_nome_entry),FALSE);
	gtk_box_pack_start(GTK_BOX(orc_bnc_box),orc_bnc_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_bnc_box),orc_bnc_psq_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_bnc_box),orc_bnc_nome_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_bnc_frame),orc_bnc_box);
	gtk_fixed_put(GTK_FIXED(orc_bnc_fixed),orc_bnc_frame,20,20);

	orc_pag_cond_psq_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(orc_pag_cond_psq_button),gtk_image_new_from_file(IMG_PESQ));

	orc_pag_cond_entry = gtk_entry_new();
	orc_pag_cond_nome = gtk_entry_new();
	orc_pag_cond_fixed = gtk_fixed_new();
	orc_pag_cond_box = gtk_box_new(0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_cond_entry),8);
	orc_pag_cond_frame = gtk_frame_new("Cond.Pag.");
	gtk_entry_set_placeholder_text(GTK_ENTRY(orc_pag_cond_nome),"Modelo Datas");

	gtk_box_pack_start(GTK_BOX(orc_pag_cond_box),orc_pag_cond_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_pag_cond_box),orc_pag_cond_psq_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(orc_pag_cond_box),orc_pag_cond_nome,0,0,0);
	gtk_container_add(GTK_CONTAINER(orc_pag_cond_frame),orc_pag_cond_box);
	gtk_fixed_put(GTK_FIXED(orc_pag_cond_fixed),orc_pag_cond_frame,10,10);
	gtk_widget_set_size_request(orc_pag_cond_box,100,40);
	gtk_editable_set_editable(GTK_EDITABLE(orc_pag_cond_nome),FALSE);

	cliente_orc_frame = gtk_frame_new("Informações do Cliente");
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_entry,0,0,10);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),pesquisa_ter,0,0,10);

	gtk_entry_set_width_chars(GTK_ENTRY(cliente_orc_entry),8);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_name_entry,0,0,1);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_end_entry,0,0,1);

	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_tel_entry,0,0,1);
	gtk_container_add(GTK_CONTAINER(cliente_orc_frame),cliente_orc_box);

	observacoes_orc = gtk_text_view_new();
	observacoes_orc_frame = gtk_frame_new("Observações");
	gtk_container_add(GTK_CONTAINER(observacoes_orc_frame),observacoes_orc);
	gtk_widget_set_size_request(observacoes_orc,250,150);

	data_orc_frame = gtk_frame_new("Data");
	data_orc_entry = gtk_entry_new();
	data_orc_gchar = malloc( sizeof(gchar*)*15);
	sprintf(data_orc_gchar,"%s",data_sys);
	gtk_entry_set_placeholder_text(GTK_ENTRY(data_orc_entry),data_orc_gchar);
	gtk_entry_set_text(GTK_ENTRY(data_orc_entry),data_orc_gchar);
	gtk_container_add(GTK_CONTAINER(data_orc_frame),data_orc_entry);

	gtk_widget_set_size_request(codigo_orc_box,200,40);
	gtk_widget_set_size_request(operacao_orc_box,200,40);
	gtk_widget_set_size_request(cliente_orc_box,200,40);

	total_geral_orc_label = gtk_label_new("0.0");
	desconto_geral_orc_label = gtk_label_new("0.0");
	frete_orc_label = gtk_label_new("0.0");
	total_geral_orc_frame = gtk_frame_new("Total Geral");
	desconto_geral_orc_frame =  gtk_frame_new("Desconto Geral");
	frete_orc_frame = gtk_frame_new("Frete");
	gtk_container_add(GTK_CONTAINER(total_geral_orc_frame),total_geral_orc_label);
	gtk_container_add(GTK_CONTAINER(desconto_geral_orc_frame),desconto_geral_orc_label);
	gtk_container_add(GTK_CONTAINER(frete_orc_frame),frete_orc_label);

	caixa_orc_infos_c = gtk_box_new(0,0);
	//caixa_orc_infos_b = gtk_box_new(1,0);
	caixa_orc_infos_d = gtk_box_new(1,0);
	caixa_orc_infos_e = gtk_box_new(0,0);
	caixa_orc_infos = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);

	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_c),codigo_orc_frame,0,0,10);
	gtk_widget_set_name(codigo_orc_frame,"frame");
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_c),operacao_orc_frame,0,0,10);
	gtk_widget_set_name(operacao_orc_frame,"frame");
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_c),data_orc_frame,0,0,10);

	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),caixa_orc_infos_c,MARGEM_D,10);
	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),cliente_orc_frame,MARGEM_D,100);
	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),orc_pag_cond_fixed,750,90);//-MARGEM_D,90);

	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_d),orc_infos_fixed,0,0,0);
	gtk_box_pack_end(GTK_BOX(caixa_orc_infos_e),observacoes_orc_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos),caixa_orc_infos_d,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos),caixa_orc_infos_e,0,0,0);

	find_subgrupos_restrict = malloc( sizeof(struct duo_widget));

	codigo_orc_prod_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);

	codigo_prod_orc_frame = malloc( sizeof(GtkFrame* )*MAX_PROD_ORC);
	desconto_prod_orc_frame = malloc( sizeof(GtkFrame* )*MAX_PROD_ORC);
	desconto_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);

	preco_prod_orc_frame = malloc( sizeof(GtkFrame* )*MAX_PROD_ORC);
	preco_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);

	qnt_prod_orc_frame = malloc( sizeof(GtkFrame* )*MAX_PROD_ORC);
	qnt_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);

	saldo_prod_orc_frame = malloc( sizeof(GtkFrame* )*MAX_PROD_ORC);
	saldo_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);

	total_prod_orc_frame = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);
	total_prod_orc_box = malloc( sizeof(GtkFrame* )*MAX_PROD_ORC);
	total_prod_orc_fixed = malloc( sizeof(GtkFixed* )*MAX_PROD_ORC);

	juncao_linha_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);
	linhas_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);
	linhas2_prod_orc_box = malloc( sizeof(GtkBox* )*MAX_PROD_ORC);

	obs_prod_orc_gchar = malloc(MAX_OBS_LEN*MAX_PROD_ORC);
	obs_prod_orc_buffer = malloc( sizeof(GtkTextBuffer** )*MAX_PROD_ORC);

	//labels produtos
	codigo_prod_orc_label = malloc( sizeof(GtkLabel* )*MAX_PROD_ORC);
	descricao_prod_orc_label = malloc( sizeof(GtkLabel* )*MAX_PROD_ORC);
	//qnt_prod_est_orc_label = malloc( sizeof(GtkLabel** )*MAX_PROD_ORC);
	qnt_prod_orc_label = malloc( sizeof(GtkLabel* )*MAX_PROD_ORC);
	preco_prod_orc_label = malloc( sizeof(GtkLabel* )*MAX_PROD_ORC);
	orig_preco_prod_orc_combo = malloc( sizeof(GtkLabel* )*MAX_PROD_ORC);
	desconto_prod_orc_label = malloc( sizeof(GtkLabel* )*MAX_PROD_ORC);

	obs_prod_orc_view = malloc( sizeof(GtkTextView** )*MAX_PROD_ORC);
	obs_prod_orc_scroll = malloc( sizeof(GtkScrolledWindow** )*MAX_PROD_ORC);
	obs_prod_orc_fixed = malloc( sizeof(GtkFixed** )*MAX_PROD_ORC);
	obs_prod_orc_frame = malloc( sizeof(GtkFrame** )*MAX_PROD_ORC);

	//entrys
	codigo_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	descricao_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	qnt_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	preco_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	saldo_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	desconto_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	tipodesconto_prod_orc_combo = malloc( sizeof(GtkComboBoxText* )*MAX_PROD_ORC);
	total_prod_orc_entry = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);

	itens_orc_box = gtk_box_new(1,0);
	outros_orc_box = gtk_box_new(1,0);
	transp_orc_box = gtk_box_new(1,0);

	pesquisa_prod = malloc( sizeof(GtkButton** )*MAX_PROD_ORC);

	img_botao_menos = malloc( sizeof(GtkImage** )*MAX_PROD_ORC);
	botao_menos = malloc( sizeof(GtkButton** )*MAX_PROD_ORC);

	//Botoes opcoes
	concluir_orc_button = gtk_button_new_with_label("Concluir");
	gerar_orc_button = gtk_button_new_with_label("Gerar Orçamento");
	pedido_orc_button = gtk_button_new_with_label("Pedido");
	alterar_orc_button = gtk_button_new_with_label("Alterar");
	cancelar_orc_button = gtk_button_new_with_label("Cancelar");
	excluir_orc_button = gtk_button_new_with_label("Excluir");

	//imagens opçoes
	concluir_orc_img_button = gtk_image_new_from_file(IMG_OK);
	gtk_button_set_image(GTK_BUTTON(concluir_orc_button),concluir_orc_img_button);

	gerar_orc_img_button = gtk_image_new_from_file(IMG_GERA);
	gtk_button_set_image(GTK_BUTTON(gerar_orc_button),gerar_orc_img_button);

	pedido_orc_img_button = gtk_image_new_from_file(IMG_ENVIA);
	gtk_button_set_image(GTK_BUTTON(pedido_orc_button),pedido_orc_img_button);

	alterar_orc_img_button = gtk_image_new_from_file(IMG_ALTER);
	gtk_button_set_image(GTK_BUTTON(alterar_orc_button),alterar_orc_img_button);

	cancelar_orc_img_button = gtk_image_new_from_file(IMG_CANCEL);
	gtk_button_set_image(GTK_BUTTON(cancelar_orc_button),cancelar_orc_img_button);

	excluir_orc_img_button = gtk_image_new_from_file(IMG_EXCLUI);
	gtk_button_set_image(GTK_BUTTON(excluir_orc_button),excluir_orc_img_button);

	orc_box_datas = orc_campos_datas();
	financeiro_box = gtk_box_new(1,0);
	opcoes_orc_fixed = gtk_fixed_new();

	caixa_opcoes_orc = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),concluir_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),gerar_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),pedido_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),alterar_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),cancelar_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),excluir_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),total_geral_orc_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),desconto_geral_orc_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),frete_orc_frame,0,0,10);

	gtk_fixed_put(GTK_FIXED(opcoes_orc_fixed),caixa_opcoes_orc,100,0);

	linhas_prod_orc_frame = malloc( sizeof(GtkEntry* )*MAX_PROD_ORC);
	prod_scroll_box = gtk_box_new(1,0);
	orc_prods_grid = gtk_grid_new();

	prod_scroll_window = gtk_scrolled_window_new(NULL,NULL);

	gtk_box_pack_start(GTK_BOX(financeiro_box),orc_box_datas,0,0,0);
	gtk_box_pack_start(GTK_BOX(financeiro_box),orc_bnc_fixed,0,0,0);

	g_signal_connect(pesquisa_ter,"clicked",G_CALLBACK(psq_ter),cliente_orc_entry);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);

	gtk_container_add(GTK_CONTAINER(prod_scroll_window),prod_scroll_box);
	gtk_box_pack_start(GTK_BOX(prod_scroll_box),orc_prods_grid,0,0,0);

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (prod_scroll_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_box_pack_start(GTK_BOX(itens_orc_box),prod_scroll_window,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_orc_infos,0,0,0);

	gtk_notebook_append_page(GTK_NOTEBOOK(orc_notebook),itens_orc_box,gtk_label_new("Itens"));
	gtk_notebook_append_page(GTK_NOTEBOOK(orc_notebook),orc_entrega_campos(),gtk_label_new("Transporte"));
	gtk_notebook_append_page(GTK_NOTEBOOK(orc_notebook),financeiro_box,gtk_label_new("Outros"));

	gtk_box_pack_start(GTK_BOX(caixa_grande),orc_notebook,0,0,10);
	gtk_box_pack_end(GTK_BOX(caixa_grande),opcoes_orc_fixed,0,0,10);

	gtk_container_add(GTK_CONTAINER(janela_orcamento),caixa_grande);

	g_signal_connect(concluir_orc_button,"clicked",G_CALLBACK(concluir_orc),NULL);
	g_signal_connect(gerar_orc_button,"clicked",G_CALLBACK(gerar_orc),NULL);
	g_signal_connect(cancelar_orc_button,"clicked",G_CALLBACK(cancela_orc),NULL);
	g_signal_connect(alterar_orc_button,"clicked",G_CALLBACK(altera_orc),NULL);
	g_signal_connect(excluir_orc_button,"clicked",G_CALLBACK(excluir_orc),NULL);
	g_signal_connect(pedido_orc_button,"clicked",G_CALLBACK(gera_orc_ped),NULL);
	g_signal_connect(copia_orc_button,"clicked",G_CALLBACK(copia_orc_fun),NULL);
	g_signal_connect(pesquisa_orc,"clicked",G_CALLBACK(psq_orc),codigo_orc_entry);

	g_signal_connect(codigo_orc_entry,"activate",G_CALLBACK(codigo_orc),NULL);
	g_signal_connect(orc_bnc_code_entry,"activate",G_CALLBACK(orc_bnc_code_fun),NULL);
	g_signal_connect(cliente_orc_entry,"activate",G_CALLBACK(codigo_cli_orc),NULL);

	g_signal_connect(orc_pag_cond_entry,"activate",G_CALLBACK(rec_fat_vist),NULL);

	g_signal_connect(orc_pag_cond_psq_button,"clicked",G_CALLBACK(psq_pag_cond),orc_pag_cond_entry);
	g_signal_connect(orc_bnc_psq_button,"clicked",G_CALLBACK(psq_bnc),orc_bnc_code_entry);

	g_signal_connect(janela_orcamento,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_ORC]);
	g_signal_connect(orc_prods_grid,"size-allocate",G_CALLBACK(auto_vmover_scroll),prod_scroll_window);

	for(int cont=1;cont<=MAX_PROD_ORC;cont++)
		ativos[cont].id = 0;

	cancela_orc();

	gtk_widget_grab_focus(cliente_orc_entry);
	gtk_widget_show_all(janela_orcamento);
	return 0;
}
