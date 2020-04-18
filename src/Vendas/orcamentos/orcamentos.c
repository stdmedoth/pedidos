int alterando_orc=0;
#include "campos.h"
#include <time.h>

int gerar_total_geral()
{
	if(ativos_qnt>0)
	{
		gtk_widget_set_sensitive(cliente_orc_entry,FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(cliente_orc_entry,TRUE);
	}
	
	char *muda_label;
	total_geral_orc = 0;
	desconto_geral_orc =0 ;
	g_print("iniciando gerar_total_geral()\n");
	muda_label = malloc(sizeof(char*)*MAX_PRECO_LEN+3);
	for(cont=1;cont<itens_qnt;cont++)
	{
		if(ativos[cont].id == 1)
		{
			ativos[cont].total_f = ((ativos[cont].qnt_f)*(ativos[cont].preco_f))-(ativos[cont].desconto_f);
			g_print("Somando totais para %i\n",cont);
			g_print("TOTAL: %.2f\n",ativos[cont].total_f);
			g_print("PRECO: %.2f\n",ativos[cont].preco_f);
			g_print("DESCONTO: %.2f\n",ativos[cont].desconto_f);
			total_geral_orc = total_geral_orc + ativos[cont].total_f;
			desconto_geral_orc = desconto_geral_orc + ativos[cont].desconto_f;
			g_print("total: %.2f = %.2f + %.2f\n",total_geral_orc, total_geral_orc , ativos[cont].total_f);
			g_print("desconto: %.2f = %.2f + %.2f\n",desconto_geral_orc, desconto_geral_orc , ativos[cont].desconto_f);
			if(total_geral_orc<0)
			{
				popup(NULL,"Total Negativo! Verifique o desconto");
				return 1;
			}
			sprintf(muda_label,"%.2f",total_geral_orc);
			gtk_label_set_text(GTK_LABEL(total_geral_orc_label),muda_label);
			
			sprintf(muda_label,"%.2f",desconto_geral_orc);
			gtk_label_set_text(GTK_LABEL(desconto_geral_orc_label),muda_label);
		}
	}	
	g_print("finalizando gerar_total_geral()\n");
	return 0;
}

int remover_linha_orc(GtkWidget *widget,int id_ponteiro)
{
	int erro;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	sprintf(query,"select * from Produto_Orcamento where code = %s and item = %i",codigo_orc_gchar,id_ponteiro);
	vetor = consultar(query);
	if(vetor!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos!=NULL)
		{
			sprintf(query,"delete from Produto_Orcamento where code = %s and item = %i",codigo_orc_gchar,id_ponteiro);
			erro = enviar_query(query);
			if(erro!=0)
			{
				popup(NULL,"Erro ao tentar excluir o item\n\rReinicie o sistema!\n\tCaso persista, chame suporte");
				return 1;
			}
		}
	}
	ativos[id_ponteiro].id = 0;
	excluidos[id_ponteiro].id = 1;
	g_print("linha deletada %i\n",id_ponteiro);
	ativos_qnt--;
	gtk_widget_destroy(linhas_prod_orc_frame[id_ponteiro]);
	return 0;
}

int adicionar_linha_orc()
{		
	if(ativos[itens_qnt-1].id == 1)
	{
		int cont;
		if(codigo_orc()!=0)
			return 1;
		if(codigo_cli_orc()!=0)
			return 1;
		if(codigo_prod_orc(codigo_prod_orc_entry[itens_qnt-1],itens_qnt-1)!=0)
			return 1;
		if(qnt_prod_orc(qnt_prod_orc_entry[itens_qnt-1],itens_qnt-1)!=0)
			return 1;
		if(preco_prod_orc(preco_prod_orc_entry[itens_qnt-1],itens_qnt-1)!=0)
			return 1;
		for(cont=0;cont<=CAMPOS_QNT;cont++)
		{
			if(vet_erro[cont]!=0)
				return 1;
		}		
	}
	gerar_total_geral();
	sprintf(item_frame_char,"Item %i",itens_qnt);
	linhas_prod_orc_frame[itens_qnt] =  gtk_frame_new(item_frame_char);
	gtk_widget_set_name(linhas_prod_orc_frame[itens_qnt],"frame2");
	linhas_prod_orc_box[itens_qnt] = gtk_box_new(0,0); 
	codigo_prod_orc_label[itens_qnt] = gtk_label_new("Código");
	codigo_prod_orc_entry[itens_qnt] = gtk_entry_new();
	pesquisa_prod[itens_qnt] = gtk_button_new();
	img_pesquisa_prod[itens_qnt] = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(pesquisa_prod[itens_qnt]),img_pesquisa_prod[itens_qnt]);
		
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
	gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[itens_qnt]),pesquisa_prod[itens_qnt],0,0,2);
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
	ativos_qnt++;
	gtk_widget_set_sensitive(botao_menos[itens_qnt-1],TRUE);
	gtk_widget_set_sensitive(botao_menos[itens_qnt],FALSE);
	
	#pragma GCC diagnostic ignored "-Wint-conversion"
	g_signal_connect(botao_menos[itens_qnt],"clicked",G_CALLBACK(remover_linha_orc),id_vetor[itens_qnt]);
	g_signal_connect(codigo_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(codigo_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(pesquisa_prod[itens_qnt],"clicked",G_CALLBACK(lista_produtos),codigo_prod_orc_entry[id_vetor[itens_qnt]]);
	g_signal_connect(qnt_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(qnt_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(preco_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(preco_prod_orc_entry[itens_qnt],"focus-in-event",G_CALLBACK(prc_cli_alter),id_vetor[cont]);

	g_signal_connect(orig_preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(orig_preco_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(desconto_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(desconto_prod_orc),id_vetor[itens_qnt]);
	g_signal_connect(total_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(total_prod_orc),id_vetor[cont]);
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
	gtk_widget_set_size_request(janela_orcamento,1250,600);
	gtk_window_set_title(GTK_WINDOW(janela_orcamento),"Orçamentos");
	gtk_window_set_position(GTK_WINDOW(janela_orcamento),3);
	itens_qnt = 1;
	cont=1;
	ativos_qnt=1;
	item_frame_char = malloc(strlen("Item ")+10);
	
	orc_infos_fixed = gtk_fixed_new();
	orc_itens_fixed = gtk_fixed_new();
	orc_geral_fixed = gtk_fixed_new();
	
	codigo_orc_label = gtk_label_new("Orçamento:");
	codigo_orc_entry = gtk_entry_new();
	pesquisa_orc = gtk_button_new();
	img_pesquisa_orc = gtk_image_new_from_file(IMG_PROCR);
	gtk_button_set_image(GTK_BUTTON(pesquisa_orc),img_pesquisa_orc);
	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	codigo_orc_box = gtk_box_new(0,0);
	codigo_orc_frame = gtk_frame_new("Código do Orçamento");
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),codigo_orc_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),codigo_orc_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(codigo_orc_box),pesquisa_orc,0,0,5);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_orc_entry),8);
	gtk_container_add(GTK_CONTAINER(codigo_orc_frame),codigo_orc_box);
	
	operacao_orc_label = gtk_label_new("Operação:");
	operacao_orc_entry = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(operacao_orc_entry),0,"Escolher");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(operacao_orc_entry),"1","Venda");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(operacao_orc_entry),"2","Em desenvolvimento");
	gtk_combo_box_set_active(GTK_COMBO_BOX(operacao_orc_entry),0);
	operacao_orc_box = gtk_box_new(0,0);
	operacao_orc_frame = gtk_frame_new("Tipo de Operação");
	gtk_box_pack_start(GTK_BOX(operacao_orc_box),operacao_orc_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(operacao_orc_box),operacao_orc_entry,0,0,52);
	gtk_container_add(GTK_CONTAINER(operacao_orc_frame),operacao_orc_box);
	
	cliente_orc_label = gtk_label_new("Insira o Código: ");
	cliente_orc_entry = gtk_entry_new();
	pesquisa_ter = gtk_button_new();
	img_pesquisa_ter = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(pesquisa_ter),img_pesquisa_ter);
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
	gtk_box_pack_start(GTK_BOX(cliente_orc_box),pesquisa_ter,0,0,1);
	
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
	
	data_orc_frame = gtk_frame_new("Data");
	data_orc_entry = gtk_entry_new();
	data_orc_gchar = malloc(sizeof(gchar*)*15);
	sprintf(data_orc_gchar,"%s",data_sys);
	gtk_entry_set_placeholder_text(GTK_ENTRY(data_orc_entry),data_orc_gchar);
	gtk_entry_set_text(GTK_ENTRY(data_orc_entry),data_orc_gchar);
	gtk_container_add(GTK_CONTAINER(data_orc_frame),data_orc_entry);
	
	gtk_widget_set_size_request(codigo_orc_box,200,40);
	gtk_widget_set_size_request(operacao_orc_box,200,40);
	gtk_widget_set_size_request(cliente_orc_box,200,40);
	
	total_geral_orc_label = gtk_label_new("0.0");
	desconto_geral_orc_label = gtk_label_new("0.0");
	total_geral_orc_frame = gtk_frame_new("Total Geral");
	desconto_geral_orc_frame =  gtk_frame_new("Desconto Geral");
	gtk_container_add(GTK_CONTAINER(total_geral_orc_frame),total_geral_orc_label);
	gtk_container_add(GTK_CONTAINER(desconto_geral_orc_frame),desconto_geral_orc_label);
	
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
	gtk_box_pack_start(GTK_BOX(caixa_orc_infos_c),data_orc_frame,0,0,30);
	
	
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
	
	pesquisa_prod = malloc(sizeof(GtkButton*)*MAX_PROD_ORC);
	img_pesquisa_prod = malloc(sizeof(GtkImage*)*MAX_PROD_ORC);
	
	img_botao_menos = malloc(sizeof(GtkImage*)*MAX_PROD_ORC);
	botao_menos = malloc(sizeof(GtkButton*)*MAX_PROD_ORC);
	
	//Botoes opcoes
	concluir_orc_button = gtk_button_new_with_label("Concluir");
	gerar_orc_button = gtk_button_new_with_label("Gerar Orçamento");
	imprimir_orc_button = gtk_button_new_with_label("Imprimir");
	alterar_orc_button = gtk_button_new_with_label("Alterar");
	cancelar_orc_button = gtk_button_new_with_label("Cancelar");
	excluir_orc_button = gtk_button_new_with_label("Excluir");
	
	//imagens opçoes
	concluir_orc_img_button = gtk_image_new_from_file(IMG_OK);
	gtk_button_set_image(GTK_BUTTON(concluir_orc_button),concluir_orc_img_button);
	
	gerar_orc_img_button = gtk_image_new_from_file(IMG_GERA);
	gtk_button_set_image(GTK_BUTTON(gerar_orc_button),gerar_orc_img_button);
	
	imprimir_orc_img_button = gtk_image_new_from_file(IMG_IMP);
	gtk_button_set_image(GTK_BUTTON(imprimir_orc_button),imprimir_orc_img_button);
	
	alterar_orc_img_button = gtk_image_new_from_file(IMG_ALTER);
	gtk_button_set_image(GTK_BUTTON(alterar_orc_button),alterar_orc_img_button);
	
	cancelar_orc_img_button = gtk_image_new_from_file(IMG_CANCEL);
	gtk_button_set_image(GTK_BUTTON(cancelar_orc_button),cancelar_orc_img_button);
	
	excluir_orc_img_button = gtk_image_new_from_file(IMG_EXCLUI);
	gtk_button_set_image(GTK_BUTTON(excluir_orc_button),excluir_orc_img_button);
	
	opcoes_orc_fixed = gtk_fixed_new();
	
	caixa_opcoes_orc = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),concluir_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),gerar_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),imprimir_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),alterar_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),cancelar_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),excluir_orc_button,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),total_geral_orc_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes_orc),desconto_geral_orc_frame,0,0,10);
	
	gtk_fixed_put(GTK_FIXED(opcoes_orc_fixed),caixa_opcoes_orc,100,0);
	
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
		pesquisa_prod[cont] = gtk_button_new();
		img_pesquisa_prod[cont] = gtk_image_new_from_file(IMG_PESQ);
		gtk_button_set_image(GTK_BUTTON(pesquisa_prod[cont]),img_pesquisa_prod[cont]);
		
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
		gtk_box_pack_start(GTK_BOX(linhas_prod_orc_box[cont]),pesquisa_prod[cont],0,0,2);
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
		ativos[itens_qnt].id = 1;
		excluidos[itens_qnt].id = 0;
		#pragma GCC diagnostic ignored "-Wint-conversion"
		g_signal_connect(botao_menos[itens_qnt],"clicked",G_CALLBACK(remover_linha_orc),id_vetor[cont]);
		g_signal_connect(codigo_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(codigo_prod_orc),id_vetor[cont]);
		g_signal_connect(pesquisa_prod[itens_qnt],"clicked",G_CALLBACK(lista_produtos),codigo_prod_orc_entry[itens_qnt]);
		g_signal_connect(qnt_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(qnt_prod_orc),id_vetor[cont]);
		
		g_signal_connect(preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(preco_prod_orc),id_vetor[cont]);
		g_signal_connect(preco_prod_orc_entry[itens_qnt],"focus-in-event",G_CALLBACK(prc_cli_alter),id_vetor[cont]);
		
		g_signal_connect(orig_preco_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(orig_preco_prod_orc),id_vetor[cont]);
		g_signal_connect(desconto_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(desconto_prod_orc),id_vetor[cont]);
		g_signal_connect(total_prod_orc_entry[itens_qnt],"activate",G_CALLBACK(total_prod_orc),id_vetor[cont]);
		g_signal_connect(pesquisa_ter,"clicked",G_CALLBACK(listar_terceiros),cliente_orc_entry);
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
	gtk_box_pack_end(GTK_BOX(caixa_grande),opcoes_orc_fixed,0,0,10);
	gtk_container_add(GTK_CONTAINER(janela_orcamento),caixa_grande);
	
	g_signal_connect(concluir_orc_button,"clicked",G_CALLBACK(concluir_orc),NULL);
	g_signal_connect(gerar_orc_button,"clicked",G_CALLBACK(gerar_orc),NULL);
	g_signal_connect(alterar_orc_button,"clicked",G_CALLBACK(altera_orc),NULL);
	g_signal_connect(pesquisa_orc,"clicked",G_CALLBACK(lista_orcamentos),codigo_orc_entry);
	
	
	g_signal_connect(codigo_orc_entry,"activate",G_CALLBACK(codigo_orc),NULL);
	g_signal_connect(cliente_orc_entry,"activate",G_CALLBACK(codigo_cli_orc),NULL);
	g_signal_connect(botao_orc_mais,"clicked",G_CALLBACK(adicionar_linha_orc),NULL);
	g_signal_connect(janela_orcamento,"destroy",G_CALLBACK(close_window_callback),janela_orcamento);
	gtk_widget_grab_focus(cliente_orc_entry);
	gtk_widget_show_all(janela_orcamento);
	return 0;
}

