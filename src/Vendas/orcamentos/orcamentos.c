#define MAX_PROD_ORC 300
#define PROD_LINHAS_ORC 7
int inicializar_orc()
{
	
	return 0;
}
int itens_qnt=0;
int vnd_orc()
{
	char *item_frame_label;
	
	GtkWidget *janela_orcamento;
	//  FRAMES
	GtkWidget *codigo_orc_frame,*operacao_orc_frame,*cliente_orc_frame,*observacoes_orc_frame,*itens_orc_frame,**linhas_prod_orc_frame;
	
	// FIXEDs
	GtkWidget *orc_infos_fixed,*orc_itens_fixed,*orc_geral_fixed;

	// LABELS

	GtkWidget *codigo_orc_label,*operacao_orc_label,*cliente_orc_label;
	
	GtkWidget **codigo_prod_orc_label,
	**descricao_prod_orc_label,
	**qnt_prod_orc_label,
	**preco_prod_orc_label,
	**orig_preco_prod_orc_label,
	**desconto_prod_orc_label,
	**total_prod_orc_label;
	
	//  ENTRYs
	
	GtkWidget *codigo_orc_entry,*operacao_orc_entry,*cliente_orc_entry,*cliente_orc_name_entry,*cliente_orc_end_entry,*cliente_orc_tel_entry;
	
	GtkWidget **codigo_prod_orc_entry,
	**descricao_prod_orc_entry,
	**qnt_prod_orc_entry,
	**preco_prod_orc_entry,
	**orig_preco_prod_orc_entry,
	**desconto_prod_orc_entry,
	**total_prod_orc_entry;
	
	//  BOXES
	GtkWidget *caixa_infos_c,*caixa_infos_b;
	GtkWidget *codigo_orc_box,*operacao_orc_box,*cliente_orc_box,*itens_orc_box,**linhas_prod_orc_box;
	GtkWidget *caixa_grande,*caixa_infos_d,*caixa_infos_e,*caixa_infos;
	
	//Containers
	GtkWidget *prod_scroll_window,*prod_scroll_box;
	
	GtkWidget **codigo_prod_orc_box,
	**descricao_prod_orc_box,
	**qnt_prod_est_orc_box,
	**qnt_prod_orc_box,
	**preco_prod_orc_box,
	**orig_preco_prod_orc_box,
	**desconto_prod_orc_box,
	**botao_mais,**botao_menos;
	int **vetor_identificador,cont;
	
	GtkWidget *observacoes_orc,*buffer_orc;
	
	//campos gerais
	//GtkWidget *qnt_volumes_label,*valor_total_label;
	g_print("Entrando na opção de orcamentos\n");
	janela_orcamento = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(janela_orcamento),TRUE);
	gtk_widget_set_size_request(janela_orcamento,1200,600);
	gtk_window_set_title(GTK_WINDOW(janela_orcamento),"Orçamentos");
	gtk_window_set_position(GTK_WINDOW(janela_orcamento),3);
	
	item_frame_label = malloc(strlen("Item ")+10);
	
	orc_infos_fixed = gtk_fixed_new();
	orc_itens_fixed = gtk_fixed_new();
	orc_geral_fixed = gtk_fixed_new();
	
	codigo_orc_label = gtk_label_new("Orçamento:");
	codigo_orc_entry = gtk_entry_new();
	codigo_orc_box = gtk_box_new(0,0);
	codigo_orc_frame = gtk_frame_new("Código do Orçamento");
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),codigo_orc_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(codigo_orc_box),codigo_orc_entry,0,0,5);
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
	
	caixa_infos_c = gtk_box_new(0,0);
	//caixa_infos_b = gtk_box_new(1,0);
	caixa_infos_d = gtk_box_new(1,0);
	caixa_infos_e = gtk_box_new(0,0);
	caixa_infos = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_infos_c),codigo_orc_frame,0,0,30);
	gtk_widget_set_name(codigo_orc_frame,"frame");
	gtk_box_pack_start(GTK_BOX(caixa_infos_c),operacao_orc_frame,0,0,30);
	gtk_widget_set_name(operacao_orc_frame,"frame");
	
	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),caixa_infos_c,MARGEM_D,10);
	//gtk_fixed_put(GTK_FIXED(orc_infos_fixed),operacao_orc_frame,MARGEM_D,90);
	gtk_fixed_put(GTK_FIXED(orc_infos_fixed),cliente_orc_frame,MARGEM_D,100);
	
	gtk_box_pack_start(GTK_BOX(caixa_infos_d),orc_infos_fixed,0,0,0);
	gtk_box_pack_end(GTK_BOX(caixa_infos_e),observacoes_orc_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_infos),caixa_infos_d,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_infos),caixa_infos_e,0,0,0);

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
	
	botao_mais = malloc(sizeof(GtkImage*)*MAX_PROD_ORC);
	botao_menos = malloc(sizeof(GtkImage*)*MAX_PROD_ORC);
	
	linhas_prod_orc_frame = malloc(sizeof(GtkEntry*)*MAX_PROD_ORC);
	
	prod_scroll_window = gtk_scrolled_window_new(NULL,NULL);
	prod_scroll_box = gtk_box_new(1,0);

	for(cont=0;cont<=PROD_LINHAS_ORC;cont++)
	{
		sprintf(item_frame_label,"Item %i",itens_qnt+1);
		linhas_prod_orc_frame[cont] =  gtk_frame_new(item_frame_label);
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
		botao_menos[cont] = gtk_image_new_from_file(IMG_MENOS);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),codigo_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),codigo_prod_orc_entry[cont],0,0,2);
		gtk_entry_set_width_chars(GTK_ENTRY(codigo_prod_orc_entry[cont]),8);
		
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),descricao_prod_orc_label[cont],0,0,2);
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),descricao_prod_orc_entry[cont],0,0,2);
		
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
		
		//gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),botao_menos[cont],0,0,2);
		
		gtk_container_add(GTK_CONTAINER(linhas_prod_orc_frame[cont]),linhas_prod_orc_box[cont]);
		gtk_widget_set_size_request(linhas_prod_orc_frame[cont],1100,30);
		gtk_box_pack_start(GTK_BOX(prod_scroll_box),linhas_prod_orc_frame[cont],0,0,10);
		itens_qnt++;
	}
	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,600);
	
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(prod_scroll_window),prod_scroll_box);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(prod_scroll_window),prod_scroll_box);
	#endif	
	gtk_box_pack_start(GTK_BOX(itens_orc_box),prod_scroll_window,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_infos,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),itens_orc_box,0,0,10);
	gtk_container_add(GTK_CONTAINER(janela_orcamento),caixa_grande);
	
	g_signal_connect(janela_orcamento,"destroy",G_CALLBACK(close_window_callback),janela_orcamento);
	gtk_widget_show_all(janela_orcamento);
	return 0;
}

