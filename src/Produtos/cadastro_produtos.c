GtkWidget *concluir, *alterar, *listar, *excluir;
int alterando_prod=0;
#include "campos.c"
#include "conclui.c"
#include "altera.c"
#include "exclui.c"
#include "lista.c"

int inicializar_prod()
{
	int i,cont;
	
	for(cont=0;cont<=CAMPOS_QNT;cont++)
	{
		vet_erro[cont] = 0;
	}
	
	for(i=0;i<=CAMPOS_QNT;i++)
		vet_erro[i] = 0;
	
	codigos_prod = malloc(MAX_CODE_LEN);
	nomes_prod = malloc(MAX_NAME_LEN);	
	precos_prod = malloc(MAX_PRECO_LEN);	
	pesos_prod = malloc(MAX_PRECO_LEN);	
	unidades_prod = malloc(MAX_UND_LEN);
	grupos_prod = malloc(MAX_GRP_LEN);
	precos_faturado_prod = malloc(MAX_MRC_LEN);
	fornecedores_prod = malloc(MAX_FOR_LEN);
	observacoes_prod = malloc(MAX_OBS_LEN);
	buffer = malloc(sizeof(GtkTextBuffer*));
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	imagem_ok = malloc(sizeof(GtkImage*)*MAX_PROD);
	imagem_cancel = malloc(sizeof(GtkImage*)*MAX_PROD);
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	
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
	*horizontal_box_six;
	
 	//container/visual
	GtkWidget *janela;
	GtkWidget *fixed, *fixed2, *box,*vertical_box1, *vertical_box2, *separator;
	GtkWidget *code, *name, *preco, *peso, *unidade, *fornecedor, *grupo, *preco_faturado_ , *observacoes;
	GtkWidget *acao;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"produtos");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO PRODUTOS");
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),janela);
	gtk_widget_set_size_request(janela,900,600);
	
	psq_forn_button = gtk_button_new();
	psq_forn_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_forn_button),psq_forn_img);
	
	psq_subgrp_button = gtk_button_new();
	psq_subgrp_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_subgrp_button),psq_subgrp_img);
	
	psq_und_button = gtk_button_new();
	psq_und_img = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(psq_und_button),psq_und_img);
	
	psq_forn = gtk_box_new(0,0);
	psq_subgrp = gtk_box_new(0,0);
	psq_und = gtk_box_new(0,0);
	
	acao = gtk_box_new(0,0);
	acao_atual = gtk_label_new("Ação atual: ");
	acao_atual2 = gtk_label_new("Cadastrando");
	gtk_widget_set_name(acao_atual2,"acao_atual");
	gtk_box_pack_start(GTK_BOX(acao),acao_atual,0,0,0);
	gtk_box_pack_start(GTK_BOX(acao),acao_atual2,0,0,5);
	
	imagem_mais = gtk_image_new_from_file(IMG_MAIS);												
	botao_mais = gtk_button_new_with_label("");
	gtk_button_set_image(GTK_BUTTON(botao_mais),imagem_mais);
	
 	tipos_scroll_caixa	 = gtk_box_new(1,0);
	tipos_scroll_window = gtk_scrolled_window_new(NULL,NULL);
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(tipos_scroll_window),tipos_scroll_caixa);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(tipos_scroll_window),tipos_scroll_caixa);
	#endif
	//gtk_box_pack_start(GTK_BOX(tipos_scroll_caixa),lista_prod_label,0,0,20);
	/*																	*/
	gtk_widget_set_size_request(tipos_scroll_window,200,500);
	
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,0);
	horizontal_box_two = gtk_box_new(0,0);
	horizontal_box_three = gtk_box_new(0,0);
	horizontal_box_four = gtk_box_new(0,0);
	horizontal_box_five = gtk_box_new(0,0);
	horizontal_box_six = gtk_box_new(0,0);
	
	box = gtk_box_new(0,0);
	vertical_box1 = gtk_box_new(1,0);
	vertical_box2 = gtk_box_new(1,0);
	separator = gtk_separator_new(1);

	code_prod_label = gtk_label_new("Codigo: ");
	nome_prod_label = gtk_label_new("Nome: ");
	preco_prod_label = gtk_label_new("Preco: ");
	peso_prod_label = gtk_label_new("Peso: ");
	unidade_prod_label =  gtk_label_new("Unidade: ");
	fornecedor_prod_label =  gtk_label_new("Fornecedor: ");
	grupo_prod_label =  gtk_label_new("Grupo: ");
	preco_faturado_prod_label =  gtk_label_new("Preço Faturado: ");
	observacao_prod_label =  gtk_label_new("Observacoes: ");
	
	campo_nome_fornecedor = gtk_entry_new();
	campo_nome_grupo = gtk_entry_new();
	campo_nome_unidade = gtk_entry_new();
	
	codigo_prod_field = gtk_entry_new();
	nome_prod_field = gtk_entry_new();
	preco_prod_field = gtk_entry_new();
	peso_prod_field = gtk_entry_new();
	unidade_prod_field = gtk_entry_new();
	fornecedor_prod_field = gtk_entry_new();
	grupo_prod_field = gtk_entry_new();
	preco_faturado_prod_field = gtk_entry_new();
	observacao_prod_field = gtk_text_view_new();
	
	code = gtk_box_new(1,0);
	gtk_widget_set_name(code,"caixa");
	gtk_box_pack_start(GTK_BOX(code),code_prod_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(code),codigo_prod_field,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(codigo_prod_field),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
	gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),task);
	gtk_widget_set_size_request(codigo_prod_field,50,30);
		
	name = gtk_box_new(1,0);
	gtk_widget_set_name(name,"caixa");
	gtk_box_pack_start(GTK_BOX(name),nome_prod_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(name),nome_prod_field,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(nome_prod_field),GTK_ENTRY_ICON_PRIMARY,"tools-check-spelling");
	gtk_widget_set_size_request(nome_prod_field,500,30);
		
	preco = gtk_box_new(1,0);
	gtk_widget_set_name(preco,"caixa");
	gtk_box_pack_start(GTK_BOX(preco),preco_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(preco),preco_prod_field,0,0,0);
	gtk_entry_set_input_hints(GTK_ENTRY(preco_prod_field),GTK_INPUT_HINT_NONE);
	gtk_entry_set_placeholder_text(GTK_ENTRY(preco_prod_field),"R$ 00,00");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(preco_prod_field),GTK_ENTRY_ICON_PRIMARY,"emblem-generic");
	gtk_widget_set_size_request(preco_prod_field,100,30);

	preco_faturado_ = gtk_box_new(1,0);
	gtk_widget_set_name(preco_faturado_,"caixa");
	gtk_box_pack_start(GTK_BOX(preco_faturado_),preco_faturado_prod_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(preco_faturado_),preco_faturado_prod_field,0,0,0);
	gtk_entry_set_placeholder_text(GTK_ENTRY(preco_faturado_prod_field),"R$ 00,00");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(preco_faturado_prod_field),GTK_ENTRY_ICON_PRIMARY,"emblem-generic");
	gtk_widget_set_size_request(preco_faturado_prod_field,100,30);

	peso = gtk_box_new(1,0);
	gtk_widget_set_name(peso,"caixa");
	gtk_box_pack_start(GTK_BOX(peso),peso_prod_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(peso),peso_prod_field,0,0,0);
	gtk_entry_set_input_hints(GTK_ENTRY(peso_prod_field),GTK_INPUT_HINT_NONE);
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
	gtk_widget_set_size_request(unidade_prod_field,100,30);

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
	gtk_box_pack_start(GTK_BOX(psq_subgrp),psq_subgrp_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(grupo),psq_subgrp,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(grupo_prod_field),GTK_ENTRY_ICON_PRIMARY,"emblem-package");
	gtk_widget_set_size_request(grupo_prod_field,100,30);

	
	observacoes = gtk_box_new(1,0);
	gtk_widget_set_name(observacoes,"caixa");
	gtk_box_pack_start(GTK_BOX(observacoes),observacao_prod_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(observacoes),observacao_prod_field,0,0,10);
	gtk_widget_set_size_request(observacao_prod_field,500,100);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),name,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),preco,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),preco_faturado_,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),peso,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),unidade,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),grupo,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),fornecedor,0,0,10);
	
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_five),observacoes,0,0,10);

	concluir = gtk_button_new_with_label("Concluir");
	alterar = gtk_button_new_with_label("Alterar");
	listar = gtk_button_new_with_label("Pesquisar");
	excluir = gtk_button_new_with_label("Excluir");
		
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),concluir,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),alterar,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),listar,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),excluir,0,0,10);

	gtk_widget_set_size_request(GTK_WIDGET(concluir),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir),100,50);	
	
	g_signal_connect(GTK_ENTRY(codigo_prod_field),"activate",G_CALLBACK(code_prod),NULL);	
	g_signal_connect(GTK_ENTRY(nome_prod_field),"activate",G_CALLBACK(nome_prod),NULL);
	g_signal_connect(GTK_ENTRY(preco_prod_field),"activate",G_CALLBACK(preco_prod),NULL);
	g_signal_connect(GTK_ENTRY(peso_prod_field),"activate",G_CALLBACK(peso_prod),NULL);
	g_signal_connect(GTK_ENTRY(unidade_prod_field),"activate",G_CALLBACK(und_prod),NULL);
	g_signal_connect(GTK_ENTRY(grupo_prod_field),"activate",G_CALLBACK(grupo_prod),NULL);
	g_signal_connect(GTK_ENTRY(preco_faturado_prod_field),"activate",G_CALLBACK(preco_faturado_prod),NULL);
	g_signal_connect(GTK_ENTRY(fornecedor_prod_field),"activate",G_CALLBACK(fornecedor_prod),NULL);
	
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(code_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(nome_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(preco_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(peso_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(und_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(fornecedor_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(grupo_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(preco_faturado_prod),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(obs_prod),NULL);

	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(conclui_prod),concluir);
	g_signal_connect(GTK_BUTTON(alterar),"clicked",G_CALLBACK(altera_prod),alterar);
	g_signal_connect(GTK_BUTTON(listar),"clicked",G_CALLBACK(psq_prod),codigo_prod_field);
	g_signal_connect(GTK_BUTTON(excluir),"clicked",G_CALLBACK(exclui_prod),excluir);
		
	g_signal_connect(janela,"destroy",G_CALLBACK(close_window_callback),janela);

	g_signal_connect(GTK_BUTTON(psq_subgrp_button),"clicked",G_CALLBACK(pesquisa_subgrp),GTK_ENTRY(grupo_prod_field));
	g_signal_connect(GTK_BUTTON(psq_und_button),"clicked",G_CALLBACK(pesquisa_und),GTK_ENTRY(unidade_prod_field));
	g_signal_connect(GTK_BUTTON(psq_forn_button),"clicked",G_CALLBACK(psq_ter),GTK_ENTRY(fornecedor_prod_field));

	gtk_widget_set_name(vertical_box1,"vertical_box1");
	
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,MARGEM_D,20);    //codigo cnpj
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_two,MARGEM_D,80);    //nome
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_three,MARGEM_D,140); //preco peso unidade
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_four,MARGEM_D,240);  //grupo preco_faturado_ fornecedor
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_five,MARGEM_D,350);  //observacoes 
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,30);   //opcoes
	
	gtk_box_pack_start(GTK_BOX(vertical_box2),botao_mais,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box2),tipos_scroll_window,0,0,0);
	
	gtk_widget_set_size_request(vertical_box1,300,590);
		
	gtk_box_pack_start(GTK_BOX(vertical_box1),acao,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box1),fixed,0,0,0);
	gtk_box_pack_end(GTK_BOX(vertical_box1),fixed2,0,0,10);
	
	
	
	gtk_box_pack_start(GTK_BOX(box),vertical_box1,0,0,50);
	gtk_box_pack_start(GTK_BOX(box),separator,0,0,10);
	gtk_box_pack_start(GTK_BOX(box),vertical_box2,0,0,0);
	
	gtk_container_add(GTK_CONTAINER(janela),box);
	gtk_widget_grab_focus(nome_prod_field);
	abrir_css(DESKTOP_STYLE);
	inicializar_prod();
	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_fornecedor),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_grupo),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(campo_nome_unidade),FALSE);
	gtk_widget_show_all(janela);
	
	return 0;
}
