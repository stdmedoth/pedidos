static GtkWidget *prod_concluir_button, *prod_alterar_button, *prod_cancelar_button, *prod_excluir_button;
static GtkWidget *psq_prod_codigo_button;
static int alterando_prod=0, concluindo_prod=0, cancelando_prod=0;
#include "campos.c"
#include "cancela.c"
#include "conclui.c"
#include "altera.c"
#include "exclui.c"

int inicializar_prod()
{
	int i,cont;

	codigos_prod = malloc(MAX_CODE_LEN);
	nomes_prod = malloc(MAX_NAME_LEN);
	precos_prod = malloc(MAX_PRECO_LEN);
	pesos_prod = malloc(MAX_PRECO_LEN);
	unidades_prod = malloc(MAX_CODE_LEN);
	unidades_atac_prod = malloc(MAX_CODE_LEN);
	grupos_prod = malloc(MAX_GRP_LEN);
	precos_faturado_prod = malloc(MAX_MRC_LEN);
	fornecedores_prod = malloc(MAX_FOR_LEN);
	observacoes_prod = malloc(MAX_OBS_LEN);

	return 0;
}

int  cad_prod()
{
	char task[20];
	sprintf(task,"%i",tasker("produtos"));
	g_print("task %s\n",task);
	//linhas
	GtkWidget *horizontal_box_one,
	*horizontal_box_two,
	*horizontal_box_three,
	*horizontal_box_four,
	*horizontal_box_five,
	*horizontal_box_six,
	*horizontal_box_seven,
	*horizontal_box_eight;

 	//container/visual
	GtkWidget *janela;
	GtkWidget *fixed, *fixed2, *fixed3,*box, *box2, *vertical_box1, *vertical_box2, *separator;
	GtkWidget *code, *name, *preco, *peso, *unidade, *qnt_atacado, *fornecedor, *grupo, *preco_faturado, *observacoes;
	GtkWidget *caixa_grande, *psq_prod_codigo_box;
	GtkWidget *observacoes_scroll;
	GtkWidget *acao;
	GtkWidget *precos_box;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"produtos");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Produtos");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].reg_id = REG_CAD_PROD;
	janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_CAD_PROD]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].janela_pointer = janela;

	grupos_prod=NULL;
	concluindo_prod=0;
	alterando_prod=0;
	cancelando_prod=0;

	psq_forn_button = gtk_button_new();
	psq_forn_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_forn_button),psq_forn_img);

	psq_grp_button = gtk_button_new();
	psq_subgrp_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_grp_button),psq_subgrp_img);

	psq_und_button = gtk_button_new();
	psq_und_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_und_button),psq_und_img);

	psq_qnt_atacado_button = gtk_button_new();
	psq_qnt_atacado_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_qnt_atacado_button),psq_qnt_atacado_img);

	psq_forn = gtk_box_new(0,0);
	psq_subgrp = gtk_box_new(0,0);
	psq_und = gtk_box_new(0,0);
	psq_qnt_atacado =  gtk_box_new(0,0);

	precos_box = gtk_box_new(1,0);

	psq_prod_codigo_box = gtk_box_new(0,0);
	psq_prod_codigo_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_prod_codigo_button),gtk_image_new_from_file(IMG_PESQ));

	caixa_grande = gtk_box_new(1,0);
	acao = gtk_box_new(0,0);
	acao_atual = gtk_label_new("Ação atual: ");
	acao_atual2 = gtk_label_new("Cadastrando");
	gtk_widget_set_name(acao_atual2,"acao_atual");
	gtk_box_pack_start(GTK_BOX(acao),acao_atual,0,0,0);
	gtk_box_pack_start(GTK_BOX(acao),acao_atual2,0,0,5);

	imagem_mais = gtk_image_new_from_file(IMG_MAIS);
	botao_mais = gtk_button_new_with_label("");
	gtk_button_set_image(GTK_BUTTON(botao_mais),imagem_mais);

	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	fixed3 = gtk_fixed_new();

	horizontal_box_one = gtk_box_new(0,0);
	horizontal_box_two = gtk_box_new(0,0);
	horizontal_box_three = gtk_box_new(0,0);
	horizontal_box_four = gtk_box_new(0,0);
	horizontal_box_five = gtk_box_new(0,0);
	horizontal_box_six = gtk_box_new(0,0);
	horizontal_box_seven = gtk_box_new(0,0);
	horizontal_box_eight = gtk_box_new(0,0);

	box = gtk_box_new(0,0);
	box2 = gtk_box_new(0,0);
	vertical_box1 = gtk_box_new(1,0);
	vertical_box2 = gtk_box_new(1,0);
	separator = gtk_separator_new(1);

	code_prod_label = gtk_label_new("Codigo: ");
	nome_prod_label = gtk_label_new("Nome: ");
	preco_prod_label = gtk_label_new("Preco à Vista: ");
	peso_prod_label = gtk_label_new("Peso: ");
	unidade_prod_label =  gtk_label_new("Quantidade Unitária: ");
	fornecedor_prod_label =  gtk_label_new("Fornecedor: ");
	grupo_prod_label =  gtk_label_new("Grupo: ");
	preco_faturado_prod_label =  gtk_label_new("Preço Faturado: ");
	observacao_prod_label =  gtk_label_new("Observacoes: ");
	qnt_atacado_label = gtk_label_new("Quantidade Varejo");

	campo_nome_fornecedor = gtk_entry_new();
	campo_nome_grupo = gtk_entry_new();
	campo_nome_unidade = gtk_entry_new();
	campo_nome_qnt_atacado = gtk_entry_new();

	codigo_prod_field = gtk_entry_new();
	nome_prod_field = gtk_entry_new();
	preco_prod_field = gtk_entry_new();
	peso_prod_field = gtk_entry_new();
	unidade_prod_field = gtk_entry_new();
	fornecedor_prod_field = gtk_entry_new();
	grupo_prod_field = gtk_entry_new();
	preco_faturado_prod_field = gtk_entry_new();
	observacao_prod_field = gtk_text_view_new();
	gtk_widget_set_name(observacao_prod_field,"textview");
	//gtk_container_set_border_width()

	qnt_atacado_field = gtk_entry_new();

	code = gtk_box_new(1,0);
	gtk_widget_set_name(code,"caixa");
	gtk_box_pack_start(GTK_BOX(code),code_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_prod_codigo_box),codigo_prod_field,0,0,0);
	gtk_box_pack_end(GTK_BOX(psq_prod_codigo_box),psq_prod_codigo_button,0,0,0);
	gtk_box_pack_end(GTK_BOX(code),psq_prod_codigo_box,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(codigo_prod_field),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
	gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),task);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_prod_field),10);


	name = gtk_box_new(1,0);
	gtk_widget_set_name(name,"caixa");
	gtk_box_pack_start(GTK_BOX(name),nome_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(name),nome_prod_field,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(nome_prod_field),GTK_ENTRY_ICON_PRIMARY,"tools-check-spelling");
	gtk_widget_set_size_request(nome_prod_field,500,30);

	peso = gtk_box_new(1,0);
	gtk_widget_set_name(peso,"caixa");
	gtk_box_pack_start(GTK_BOX(peso),peso_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(peso),peso_prod_field,0,0,0);
	gtk_entry_set_placeholder_text(GTK_ENTRY(peso_prod_field),"00,00 KG");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(peso_prod_field),GTK_ENTRY_ICON_PRIMARY,"insert-object");
	gtk_widget_set_size_request(peso_prod_field,100,30);

	unidade = gtk_box_new(1,0);
	gtk_widget_set_name(unidade,"caixa");
	gtk_box_pack_start(GTK_BOX(unidade),unidade_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(unidade),campo_nome_unidade,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_und),unidade_prod_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_und),psq_und_button,0,0,0);
	gtk_box_pack_end(GTK_BOX(unidade),psq_und,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(unidade_prod_field),GTK_ENTRY_ICON_PRIMARY,"system-software-install");
	gtk_entry_set_width_chars(GTK_ENTRY(campo_nome_unidade),20);
	gtk_entry_set_width_chars(GTK_ENTRY(unidade_prod_field),20);

	qnt_atacado = gtk_box_new(1,0);
	gtk_widget_set_name(qnt_atacado,"caixa");
	gtk_box_pack_start(GTK_BOX(qnt_atacado),qnt_atacado_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(qnt_atacado),campo_nome_qnt_atacado,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_qnt_atacado),qnt_atacado_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_qnt_atacado),psq_qnt_atacado_button,0,0,0);
	gtk_box_pack_end(GTK_BOX(qnt_atacado),psq_qnt_atacado,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(qnt_atacado_field),GTK_ENTRY_ICON_PRIMARY,"system-software-install");
	gtk_entry_set_width_chars(GTK_ENTRY(campo_nome_qnt_atacado),20);
	gtk_entry_set_width_chars(GTK_ENTRY(qnt_atacado_field),20);

	fornecedor = gtk_box_new(1,0);
	gtk_widget_set_name(fornecedor,"caixa");
	gtk_box_pack_start(GTK_BOX(fornecedor),fornecedor_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(fornecedor),campo_nome_fornecedor,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_forn),fornecedor_prod_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_forn),psq_forn_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(fornecedor),psq_forn,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(fornecedor_prod_field),GTK_ENTRY_ICON_PRIMARY,"x-package-repository");
	gtk_widget_set_size_request(fornecedor_prod_field,100,30);
	gtk_widget_set_size_request(campo_nome_fornecedor,100,30);

	grupo = gtk_box_new(1,0);
	gtk_widget_set_name(grupo,"caixa");
	gtk_box_pack_start(GTK_BOX(grupo),grupo_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(grupo),campo_nome_grupo,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_subgrp),grupo_prod_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_subgrp),psq_grp_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(grupo),psq_subgrp,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(grupo_prod_field),GTK_ENTRY_ICON_PRIMARY,"emblem-package");
	gtk_widget_set_size_request(grupo_prod_field,100,30);

	observacoes_scroll = gtk_scrolled_window_new(NULL,NULL);
	observacoes = gtk_box_new(1,0);
	gtk_widget_set_name(observacoes,"caixa_frame");
	gtk_box_pack_start(GTK_BOX(observacoes),observacao_prod_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(observacoes),observacao_prod_field,0,0,10);

	gtk_container_add(GTK_CONTAINER(observacoes_scroll),observacoes);

	gtk_widget_set_size_request(observacao_prod_field,400,150);
	gtk_widget_set_size_request(observacoes_scroll,400,150);
	gtk_widget_set_size_request(observacoes,400,150);

	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),name,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),peso,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),fornecedor,0,0,50);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),observacoes_scroll,0,0,10);

	gtk_box_pack_start(GTK_BOX(horizontal_box_five),unidade,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_five),qnt_atacado,0,0,10);

	gtk_box_pack_start(GTK_BOX(horizontal_box_six),grupo,0,0,10);

	prod_concluir_button = gtk_button_new_with_label("Concluir");
	prod_alterar_button = gtk_button_new_with_label("Alterar");
	prod_cancelar_button = gtk_button_new_with_label("Cancelar");
	prod_excluir_button = gtk_button_new_with_label("Excluir");

	gtk_box_pack_start(GTK_BOX(horizontal_box_eight),prod_concluir_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_eight),prod_alterar_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_eight),prod_cancelar_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_eight),prod_excluir_button,0,0,10);

	gtk_widget_set_size_request(GTK_WIDGET(prod_concluir_button),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(prod_alterar_button),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(prod_cancelar_button),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(prod_excluir_button),100,50);

	g_signal_connect(GTK_ENTRY(codigo_prod_field),"activate",G_CALLBACK(code_prod),NULL);
	g_signal_connect(GTK_ENTRY(nome_prod_field),"activate",G_CALLBACK(nome_prod),NULL);
	g_signal_connect(GTK_ENTRY(peso_prod_field),"activate",G_CALLBACK(peso_prod),NULL);
	g_signal_connect(GTK_ENTRY(unidade_prod_field),"activate",G_CALLBACK(und_unt_prod),NULL);
	g_signal_connect(GTK_ENTRY(qnt_atacado_field),"activate",G_CALLBACK(und_atac_prod),NULL);
	g_signal_connect(GTK_ENTRY(grupo_prod_field),"activate",G_CALLBACK(grupo_prod),NULL);
	g_signal_connect(GTK_ENTRY(fornecedor_prod_field),"activate",G_CALLBACK(fornecedor_prod),NULL);

	g_signal_connect(GTK_BUTTON(prod_concluir_button),"clicked",G_CALLBACK(conclui_prod),NULL);
	g_signal_connect(GTK_BUTTON(prod_alterar_button),"clicked",G_CALLBACK(altera_prod),NULL);
	g_signal_connect(GTK_BUTTON(psq_prod_codigo_button),"clicked",G_CALLBACK(psq_prod),codigo_prod_field);
	g_signal_connect(GTK_BUTTON(prod_cancelar_button),"clicked",G_CALLBACK(cancelar_prod),NULL);
	g_signal_connect(GTK_BUTTON(prod_excluir_button),"clicked",G_CALLBACK(exclui_prod),NULL);

	g_signal_connect(GTK_BUTTON(psq_grp_button),"clicked",G_CALLBACK(pesquisa_subgrp_todos),grupo_prod_field);
	g_signal_connect(GTK_BUTTON(psq_forn_button),"clicked",G_CALLBACK(psq_ter),GTK_ENTRY(fornecedor_prod_field));
	g_signal_connect(GTK_BUTTON(psq_und_button),"clicked",G_CALLBACK(pesquisa_und),GTK_ENTRY(unidade_prod_field));
	g_signal_connect(GTK_BUTTON(psq_qnt_atacado_button),"clicked",G_CALLBACK(pesquisa_und),qnt_atacado_field);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_PROD]);

	gtk_widget_set_name(vertical_box1,"vertical_box1");

	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,MARGEM_D,20);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_two,MARGEM_D,80);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_three,MARGEM_D,160);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_four,MARGEM_D+20,300);

	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_five,MARGEM_D,20);
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,120);
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_seven,MARGEM_D,220);

	gtk_box_pack_start(GTK_BOX(vertical_box1),acao,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box1),fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(vertical_box2),fixed2,0,0,10);

	gtk_box_pack_start(GTK_BOX(box),vertical_box1,0,0,10);
	gtk_box_pack_start(GTK_BOX(box2),vertical_box2,0,0,10);

	notebook_cad_prod = gtk_notebook_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_cad_prod),box,gtk_label_new("Informações do Produto"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_cad_prod),box2,gtk_label_new("Faturamento"));

	gtk_box_pack_start(GTK_BOX(caixa_grande),notebook_cad_prod,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),horizontal_box_eight,0,0,0);

	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);

	inicializar_prod();

	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_fornecedor),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_grupo),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_unidade),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_qnt_atacado),FALSE);

	gtk_widget_grab_focus(psq_prod_codigo_button);
	gtk_widget_show_all(janela);

	return 0;
}
