#include "campos.h"

int remover_linha_orc(GtkWidget *widget,int id_ponteiro)
{
	ativos[id_ponteiro].id = 0;
	excluidos[id_ponteiro].id = 1;
	g_print("linha deletada %i\n",id_ponteiro);
	gtk_widget_destroy(linhas_prod_orc_frame[id_ponteiro]);
	return 0;
}

int adicionar_linha_orc()
{
	sprintf(item_frame_char,"Item %i",itens_qnt);
	linhas_prod_orc_frame[itens_qnt] =  gtk_frame_new(item_frame_char);
	gtk_widget_set_name(linhas_prod_orc_frame[itens_qnt],"frame2");
	linhas_prod_orc_box[itens_qnt] = gtk_box_new(0,0); 
	codigo_prod_orc_label[itens_qnt] = gtk_label_new("Código");
	codigo_prod_orc_entry[itens_qnt] = gtk_entry_new();
	descricao_prod_orc_label[itens_qnt] = gtk_label_new("Descrição");
	descricao_prod_orc_entry[itens_qnt] = gtk_entry_new();
	qnt_prod_orc_label[itens_qnt] = gtk_label_new("Quantidade:");
	qnt_prod_orc_entry[itens_qnt] = gtk_entry_new();
	preco_prod_orc_label[itens_qnt] = gtk_label_new("Preço:");
	preco_prod_orc_entry[itens_qnt] =  gtk_entry_new();
	orig_preco_prod_orc_label[itens_qnt] = gtk_label_new("Origem Preço");
	orig_preco_prod_orc_entry[itens_qnt] = gtk_entry_new();
	desconto_prod_orc_label[itens_qnt] = gtk_label_new("Desconto");
	desconto_prod_orc_entry[itens_qnt] = gtk_entry_new();
	total_prod_orc_label[itens_qnt] = gtk_label_new("Total");
	total_prod_orc_entry[itens_qnt] = gtk_entry_new();
	
	if(GTK_IS_WIDGET(botao_orc_mais))
	{
		gtk_widget_destroy(botao_orc_mais);	
	}	
	img_botao_orc_mais = gtk_image_new_from_file(IMG_MAIS);
	botao_orc_mais  = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(botao_orc_mais),img_botao_orc_mais);	
	
	botao_menos[itens_qnt] = gtk_button_new();
	img_botao_menos[itens_qnt] = gtk_image_new_from_file(IMG_MENOS);
	gtk_button_set_image(GTK_BUTTON(botao_menos[itens_qnt]),img_botao_menos[itens_qnt]);	
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),codigo_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),codigo_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_prod_orc_entry[itens_qnt]),8);
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),descricao_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),descricao_prod_orc_entry[itens_qnt],0,0,2);
	gtk_widget_set_sensitive(descricao_prod_orc_entry[itens_qnt],FALSE);
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),qnt_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),qnt_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(qnt_prod_orc_entry[itens_qnt]),8);
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),preco_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),preco_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(preco_prod_orc_entry[itens_qnt]),8);
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),orig_preco_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),orig_preco_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(orig_preco_prod_orc_entry[itens_qnt]),8);
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),desconto_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),desconto_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(desconto_prod_orc_entry[itens_qnt]),4);
	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),total_prod_orc_label[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),total_prod_orc_entry[itens_qnt],0,0,2);
	gtk_entry_set_width_chars(GTK_ENTRY(total_prod_orc_entry[itens_qnt]),8);

	
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),botao_menos[itens_qnt],0,0,2);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),botao_orc_mais,0,0,2);
	
	gtk_container_add(GTK_CONTAINER(linhas_prod_orc_frame[itens_qnt]),linhas_prod_orc_box[itens_qnt]);
	gtk_widget_set_size_request(linhas_prod_orc_frame[itens_qnt],1100,30);
	gtk_box_pack_start(GTK_BOX(prod_scroll_box),linhas_prod_orc_frame[itens_qnt],0,0,10);
	id_vetor[itens_qnt] = itens_qnt;
	ativos[itens_qnt].id = 1;
	excluidos[itens_qnt].id = 0;
	gtk_widget_set_sensitive(botao_menos[itens_qnt-1],TRUE);
	gtk_widget_set_sensitive(botao_menos[itens_qnt],FALSE);
	
	#pragma GCC diagnostic ignored "-Wint-conversion"
	g_signal_connect(botao_menos[itens_qnt],"clicked",G_CALLBACK(remover_linha_orc),id_vetor[itens_qnt]);
	g_signal_connect(codigo_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(codigo_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(qnt_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(qnt_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(preco_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(orig_preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(orig_preco_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(desconto_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(desconto_prod_orc),id_vetor[itens_qnt]);
	//g_signal_connect(total_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(total_prod_orc),id_vetor[cont]);
	#pragma GCC diagnostic warning "-Wint-conversion"
	g_signal_connect(botao_orc_mais,"clicked",G_CALLBACK(adicionar_linha_orc),NULL);
	gtk_widget_grab_focus(codigo_prod_orc_entry[id_vetor[itens_qnt]]);
	itens_qnt++;
	gtk_widget_show_all(janela_orcamento);	
	return 0;
}


int vnd_orc()
{
	char code[10];
	//campos gerais
	//GtkWidget *qnt_volumes_label,*valor_total_label;
	g_print("Entrando na opção de orcamentos\n");
	janela_orcamento = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(janela_orcamento),TRUE);
	gtk_widget_set_size_request(janela_orcamento,1200,600);
	gtk_window_set_title(GTK_WINDOW(janela_orcamento),"Orçamentos");
	gtk_window_set_position(GTK_WINDOW(janela_orcamento),3);
	itens_qnt = 1;
	cont=1;
	item_frame_char = malloc(strlen("Item ")+10);
	
	orc_infos_fixed = gtk_fixed_new();
	orc_itens_fixed = gtk_fixed_new();
	orc_geral_fixed = gtk_fixed_new();
	
	codigo_orc_label = gtk_label_new("Orçamento:");
	codigo_orc_entry = gtk_entry_new();
	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	codigo_orc_box = gtk_box_new(0,0);
	codigo_orc_frame = gtk_frame_new("Código do Orçamento");
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),codigo_orc_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(codigo_orc_box),codigo_orc_entry,0,0,5);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_orc_entry),8);
	gtk_container_add(GTK_CONTAINER(codigo_orc_frame),codigo_orc_box);
	
	operacao_orc_label = gtk_label_new("Operação:");
	operacao_orc_entry = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(operacao_orc_entry),0,"Escolher");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(operacao_orc_entry),"1","Venda");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(operacao_orc_entry),"2","Devolucao");
	gtk_combo_box_set_active(GTK_COMBO_BOX(operacao_orc_entry),0);
	operacao_orc_box = gtk_box_new(0,0);
	operacao_orc_frame = gtk_frame_new("Tipo de Operação");
	gtk_box_pack_start(GTK_BOX(operacao_orc_box),operacao_orc_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(operacao_orc_box),operacao_orc_entry,0,0,52);
	gtk_container_add(GTK_CONTAINER(operacao_orc_frame),operacao_orc_box);
	
	cliente_orc_label = gtk_label_new("Insira o Código: ");
	cliente_orc_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_entry),"Código");
	cliente_orc_name_entry = gtk_entry_new();
	gtk_widget_set_sensitive(cliente_orc_name_entry,FALSE);
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_name_entry),"Nome");
	cliente_orc_end_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_end_entry),"Endereco");
	gtk_widget_set_sensitive(cliente_orc_end_entry,FALSE);
	cliente_orc_tel_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cliente_orc_tel_entry),"Telefone");
	gtk_widget_set_sensitive(cliente_orc_tel_entry,FALSE);
	cliente_orc_box = gtk_box_new(0,0);
	cliente_orc_frame = gtk_frame_new("Informações do Cliente");
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_label,0,0,30);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_entry,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(cliente_orc_entry),8);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_name_entry,0,0,1);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_end_entry,0,0,1);
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),cliente_orc_tel_entry,0,0,1);
	gtk_container_add(GTK_CONTAINER(cliente_orc_frame),cliente_orc_box);
	
	observacoes_orc = gtk_text_view_new_with_buffer(NULL);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
	observacoes_orc_frame = gtk_frame_new("Observações");
	gtk_container_add(GTK_CONTAINER(observacoes_orc_frame),observacoes_orc);
	gtk_widget_set_size_request(observacoes_orc,250,150);
	
	
	gtk_widget_set_size_request(codigo_orc_box,200,40);
	gtk_widget_set_size_request(operacao_orc_box,200,40);
	gtk_widget_set_size_request(cliente_orc_box,200,40);
	
	caixa_orc_infos_c = gtk_box_new(0,0);
	//caixa_orc_infos_b = gtk_box_new(1,0);
	caixa_orc_infos_d = gtk_box_new(1,0);
	caixa_orc_infos_e = gtk_box_new(0,0);
	caixa_orc_infos = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_c),codigo_orc_frame,0,0,30);
	gtk_widget_set_name(codigo_orc_frame,"frame");
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_c),operacao_orc_frame,0,0,30);
	gtk_widget_set_name(operacao_orc_frame,"frame");
	
	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),caixa_orc_infos_c,MARGEM_D,10);
	//gtk_fixed_put(GTK_FIXED(orc_infos_fixed),operacao_orc_frame,MARGEM_D,90);
	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),cliente_orc_frame,MARGEM_D,100);
	
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_d),orc_infos_fixed,0,0,0);
	gtk_box_pack_end(GTK_BOX(caixa_orc_infos_e),observacoes_orc_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos),caixa_orc_infos_d,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos),caixa_orc_infos_e,0,0,0);

	//labels produtos
	linhas_prod_orc_box = malloc(sizeof(GtkBox*)*MAX_PROD_ORC);
	codigo_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	descricao_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	//qnt_prod_est_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	qnt_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	preco_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	orig_preco_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	desconto_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	total_prod_orc_label = malloc(sizeof(GtkLabel*)*MAX_PROD_ORC);
	
	//entrys
	codigo_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	descricao_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	qnt_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	preco_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	orig_preco_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	desconto_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	total_prod_orc_entry = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	itens_orc_box = gtk_box_new(1,0);	
	
	img_botao_menos = malloc(sizeof(GtkImage*)*MAX_PROD_ORC);
	botao_menos = malloc(sizeof(GtkButton*)*MAX_PROD_ORC);
	
	linhas_prod_orc_frame = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	prod_scroll_window = gtk_scrolled_window_new(NULL,NULL);
	prod_scroll_box = gtk_box_new(1,0);
	
	for(cont=1;cont<=PROD_LINHAS_ORC;cont++)
	{	
		sprintf(item_frame_char,"Item %i",cont);
		linhas_prod_orc_frame[cont] =  gtk_frame_new(item_frame_char);
		gtk_widget_set_name(linhas_prod_orc_frame[cont],"frame2");
		linhas_prod_orc_box[cont] = gtk_box_new(0,0); 
		codigo_prod_orc_label[cont] = gtk_label_new("Código");
		codigo_prod_orc_entry[cont] = gtk_entry_new();
		descricao_prod_orc_label[cont] = gtk_label_new("Descrição");
		descricao_prod_orc_entry[cont] = gtk_entry_new();
		qnt_prod_orc_label[cont] = gtk_label_new("Quantidade:");
		qnt_prod_orc_entry[cont] = gtk_entry_new();
		preco_prod_orc_label[cont] = gtk_label_new("Preço:");
		preco_prod_orc_entry[cont] =  gtk_entry_new();
		orig_preco_prod_orc_label[cont] = gtk_label_new("Origem Preço");
		orig_preco_prod_orc_entry[cont] = gtk_entry_new();
		desconto_prod_orc_label[cont] = gtk_label_new("Desconto");
		desconto_prod_orc_entry[cont] = gtk_entry_new();
		total_prod_orc_label[cont] = gtk_label_new("Total");
		total_prod_orc_entry[cont] = gtk_entry_new();
		img_botao_menos[cont] = gtk_image_new_from_file(IMG_MENOS);
		botao_menos[cont] = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(botao_menos[cont]),img_botao_menos[cont]);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),codigo_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),codigo_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(codigo_prod_orc_entry[cont]),8);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),descricao_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),descricao_prod_orc_entry[cont],0,0,2);
		gtk_widget_set_sensitive(descricao_prod_orc_entry[cont],FALSE);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),qnt_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),qnt_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(qnt_prod_orc_entry[cont]),8);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),preco_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),preco_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(preco_prod_orc_entry[cont]),8);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),orig_preco_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),orig_preco_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(orig_preco_prod_orc_entry[cont]),8);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),desconto_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),desconto_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(desconto_prod_orc_entry[cont]),4);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),total_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),total_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(total_prod_orc_entry[cont]),8);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),botao_menos[cont],0,0,2);
		id_vetor[cont] = cont; 
		#pragma GCC diagnostic ignored "-Wint-conversion"
		g_signal_connect(botao_menos[itens_qnt],"clicked",G_CALLBACK(remover_linha_orc),id_vetor[cont]);
		g_signal_connect(codigo_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(codigo_prod_orc),id_vetor[cont]);
		g_signal_connect(qnt_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(qnt_prod_orc),id_vetor[cont]);
		g_signal_connect(preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(preco_prod_orc),id_vetor[cont]);
		g_signal_connect(orig_preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(orig_preco_prod_orc),id_vetor[cont]);
		g_signal_connect(desconto_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(desconto_prod_orc),id_vetor[cont]);
		g_signal_connect(total_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(total_prod_orc),id_vetor[cont]);
		
		gtk_widget_set_sensitive(botao_menos[itens_qnt],FALSE);
		#pragma GCC diagnostic warning "-Wint-conversion"
		gtk_container_add(GTK_CONTAINER(linhas_prod_orc_frame[cont]),linhas_prod_orc_box[cont]);
		gtk_widget_set_size_request(linhas_prod_orc_frame[cont],1100,30);
		gtk_box_pack_start(GTK_BOX(prod_scroll_box),linhas_prod_orc_frame[cont],0,0,10);

		itens_qnt++;
	}
	img_botao_orc_mais = gtk_image_new_from_file(IMG_MAIS);
	botao_orc_mais = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(botao_orc_mais),img_botao_orc_mais);
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt-1]),botao_orc_mais,0,0,2);
	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,600);
	
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(prod_scroll_window),prod_scroll_box);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(prod_scroll_window),prod_scroll_box);
	#endif	
	gtk_box_pack_start(GTK_BOX(itens_orc_box),prod_scroll_window,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_orc_infos,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),itens_orc_box,0,0,10);
	gtk_container_add(GTK_CONTAINER(janela_orcamento),caixa_grande);
	g_signal_connect(cliente_orc_entry,"activate",G_CALLBACK(codigo_cli_orc),NULL);
	g_signal_connect(botao_orc_mais,"clicked",G_CALLBACK(adicionar_linha_orc),NULL);
	g_signal_connect(janela_orcamento,"destroy",G_CALLBACK(close_window_callback),janela_orcamento);
	gtk_widget_grab_focus(cliente_orc_entry);
	gtk_widget_show_all(janela_orcamento);
	return 0;
}

