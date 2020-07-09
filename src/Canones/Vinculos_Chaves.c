GtkWidget *table_vinc_combo;
GtkWidget *code_vinc_entry;
GtkWidget **vinculos_label;
GtkWidget **vinculos_button;
GtkWidget **vinculos_box;

GtkWidget *vinculos_scroll,*vinculo_box;

void del_vinculos(GtkWidget *widget, gpointer ponteiro)
{
	int erro;
	gchar *codec;
	codec = malloc(MAX_CODE_LEN);
	codec = (gchar*)gtk_entry_get_text(GTK_ENTRY(code_vinc_entry));
	if(strlen(codec)<=0)
	{
		gtk_widget_grab_focus(code_vinc_entry);
		popup(NULL,"Insira o código para consulta");
		return;
	}
	int codei = stoi(codec);
	if(codei == -1)
	{
		gtk_widget_grab_focus(code_vinc_entry);
		popup(NULL,"O campo deve ser preechido com um código numérico");
		return;
	}
	int tabela;
	char *query;
	query = malloc(MAX_QUERY_LEN);
	tabela = gtk_combo_box_get_active(GTK_COMBO_BOX(table_vinc_combo));
	switch(tabela)
	{
		case 0:
			gtk_widget_grab_focus(table_vinc_combo);
			popup(NULL,"Selecione a tabela que deseja excluir vinculos");
			break;
		case 1:
			sprintf(query,"update precos set produto = 0 where produto = %i",codei);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			sprintf(query,"update Produto_Orcamento set produto = 0 where produto = %i",codei);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			popup(NULL,"Vinculos Deletados");
			break;
		case 2:
			sprintf(query,"update orcamentos set cliente = 0 where cliente = %i",codei);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			sprintf(query,"update precos set terceiro = 0 where terceiro = %i",codei);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			sprintf(query,"update produtos set fornecedor = 0 where fornecedor = %i",codei);
			erro = enviar_query(query);
			if(erro != 0)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}

			popup(NULL,"Vinculos Deletados");
			break;
	}

	return;
}

void rec_vinculos(GtkWidget *widget, gpointer ponteiro)
{
	int tabela,cont=0;
	char *query,*formatar;
	GList *children,*iter;
	if(GTK_IS_WIDGET(vinculo_box))
	{
		children = gtk_container_get_children(GTK_CONTAINER(vinculo_box));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
	}

	MYSQL_ROW campos;
	MYSQL_RES *vetor;
	vinculos_label = malloc(sizeof(GtkLabel*)*MAX_FETCH_ROW);
	vinculos_button = malloc(sizeof(GtkButton*)*MAX_FETCH_ROW);
	vinculos_box = malloc(sizeof(GtkBox*)*MAX_FETCH_ROW);
	query = malloc(MAX_QUERY_LEN);
	formatar = malloc((MAX_PROD+MAX_CODE_LEN*2+MAX_PRECO_LEN)*MAX_FETCH_ROW);
	gchar *codec;
	codec = malloc(MAX_CODE_LEN);
	codec = (gchar*)gtk_entry_get_text(GTK_ENTRY(code_vinc_entry));
	if(strlen(codec)<=0)
	{
		gtk_widget_grab_focus(code_vinc_entry);
		popup(NULL,"Insira o código para consulta");
		return;
	}
	int codei = stoi(codec);
	if(codei == -1)
	{
		gtk_widget_grab_focus(code_vinc_entry);
		popup(NULL,"O campo deve ser preechido com um código numérico");
		return;
	}
	tabela = gtk_combo_box_get_active(GTK_COMBO_BOX(table_vinc_combo));
	switch(tabela)
	{
		case 0:
			popup(NULL,"Selecione a tabela que deseja consultar vinculos");
			break;
		case 1:
			sprintf(query,"select o.code,p.nome,o.item from Produto_Orcamento as o inner join produtos as p on o.produto = p.code where produto = %i",codei);
			vetor = consultar(query);
			if(vetor == NULL)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			while((campos = mysql_fetch_row(vetor))!=NULL)
			{
				sprintf(formatar,"Vínculo do Orcamento '%s' com Produto '%s' como item %s",campos[0],campos[1],campos[2]);

				vinculos_label[cont] = gtk_label_new(formatar);
				vinculos_box[cont] = gtk_box_new(0,0);
				gtk_box_pack_start(GTK_BOX(vinculos_box[cont]),vinculos_label[cont],0,0,0);
				gtk_box_pack_start(GTK_BOX(vinculo_box),vinculos_box[cont],0,0,0);
				cont++;
				if(cont>=MAX_FETCH_ROW)
					break;
			}
			sprintf(query,"select a.nome,b.razao,c.valor from precos as c inner join terceiros as b inner join produtos as a on c.terceiro = b.code and c.produto = a.code where c.produto = %i",codei);
			if(vetor == NULL)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			while((campos = mysql_fetch_row(vetor))!=NULL)
			{
				sprintf(formatar,"Vínculo do Produto '%s' de Preço '%s' com Cliente '%s'",campos[0],campos[1],campos[2]);
				vinculos_label[cont] = gtk_label_new(formatar);
				vinculos_box[cont] = gtk_box_new(0,0);
				gtk_box_pack_start(GTK_BOX(vinculos_box[cont]),vinculos_label[cont],0,0,0);
				gtk_box_pack_start(GTK_BOX(vinculo_box),vinculos_box[cont],0,0,0);
				cont++;
				if(cont>=MAX_FETCH_ROW)
					break;
			}
			break;
		case 2:
			sprintf(query,"select o.code,t.razao from orcamentos as o inner join terceiros as t on o.cliente = t.code where cliente = %i",codei);
			vetor = consultar(query);
			if(vetor == NULL)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			while((campos = mysql_fetch_row(vetor))!=NULL)
			{
				sprintf(formatar,"Vínculo do Orcamento '%s' com Cliente '%s'",campos[0],campos[1]);
				vinculos_label[cont] = gtk_label_new(formatar);
				vinculos_box[cont] = gtk_box_new(0,0);
				gtk_box_pack_start(GTK_BOX(vinculos_box[cont]),vinculos_label[cont],0,0,0);
				gtk_box_pack_start(GTK_BOX(vinculo_box),vinculos_box[cont],0,0,0);
				cont++;
				if(cont>=MAX_FETCH_ROW)
					break;
			}
			sprintf(query,"select p.nome,t.razao from produtos as p inner join terceiros as t on p.fornecedor = t.code where fornecedor = %i",codei);
			vetor = consultar(query);
			if(vetor == NULL)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			while((campos = mysql_fetch_row(vetor))!=NULL)
			{
				sprintf(formatar,"Vínculo do Produto '%s' com Fornecedor '%s'",campos[0],campos[1]);
				vinculos_label[cont] = gtk_label_new(formatar);
				vinculos_box[cont] = gtk_box_new(0,0);
				gtk_box_pack_start(GTK_BOX(vinculos_box[cont]),vinculos_label[cont],0,0,0);
				gtk_box_pack_start(GTK_BOX(vinculo_box),vinculos_box[cont],0,0,0);
				cont++;
				if(cont>=MAX_FETCH_ROW)
					break;
			}
			sprintf(query,"select a.nome,b.razao,c.valor from precos as c inner join terceiros as b inner join produtos as a on c.terceiro = b.code and c.produto = a.code where terceiro = %i",codei);
			vetor = consultar(query);
			if(vetor == NULL)
			{
				popup(NULL,"Consulte Suporte");
				return;
			}
			while((campos = mysql_fetch_row(vetor))!=NULL)
			{
				sprintf(formatar,"Vínculo do Cliente '%s' com Preço '%s' para Produto '%s'",campos[1],campos[2],campos[0]);
				vinculos_label[cont] = gtk_label_new(formatar);
				vinculos_box[cont] = gtk_box_new(0,0);
				gtk_box_pack_start(GTK_BOX(vinculos_box[cont]),vinculos_label[cont],0,0,0);
				gtk_box_pack_start(GTK_BOX(vinculo_box),vinculos_box[cont],0,0,0);
				cont++;
				if(cont>=MAX_FETCH_ROW)
					break;
			}

			break;
	}

	gtk_widget_show_all(vinculo_box);
	return;
}
void mensagem_aviso_vinculos()
{
	GtkWidget *popup,*label_aviso,*button_confirma,*button_cancela,*caixa_grande,*caixa_escolha;
	char mensagem[] = "\tEsta operação irá modificar\n\ttodos cadastros relacionados à essa tabela\n\n\tTem certeza que é isso que deseja?\n\n\tMAIS SEGURO: altere os cadastros e retire os vínculos manualmente";
	popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(popup),3);
	gtk_window_set_decorated(GTK_WINDOW(popup),TRUE);
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	label_aviso = gtk_label_new(mensagem);
	button_confirma = gtk_button_new_with_label("Confirmar");
	button_cancela = gtk_button_new_with_label("Cancelar");
	caixa_grande = gtk_box_new(1,0);
	caixa_escolha = gtk_box_new(0,0);

	gtk_box_pack_start(GTK_BOX(caixa_escolha),button_confirma,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_escolha),button_cancela,0,0,10);

	gtk_box_pack_start(GTK_BOX(caixa_grande),label_aviso,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_escolha,0,0,10);

	g_signal_connect(button_confirma,"clicked",G_CALLBACK(del_vinculos),NULL);
	g_signal_connect(button_confirma,"clicked",G_CALLBACK(close_window_callback),popup);
	g_signal_connect(button_cancela,"clicked",G_CALLBACK(close_window_callback),popup);

	gtk_container_add(GTK_CONTAINER(popup),caixa_grande);
	gtk_widget_show_all(popup);
	return;

}

void vin_chaves()
{
	GtkWidget *janela;
	GtkWidget *code_vinc_frame;
	GtkWidget *table_box,*code_box;
	GtkWidget *caixa_grande;
	GtkWidget *infos_fixed;
	GtkWidget *code_fixed;
	GtkWidget *botao_consulta,*botao_deleta;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela,600,400);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_title(GTK_WINDOW(janela),"Vínculos");
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);

	caixa_grande = gtk_box_new(1,0);
	infos_fixed = gtk_fixed_new();
	code_box = gtk_box_new(0,0);
	code_fixed = gtk_fixed_new();

	table_vinc_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(table_vinc_combo),"0","Escolher tabela");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(table_vinc_combo),"1","Produtos");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(table_vinc_combo),"2","Terceiros");
	gtk_combo_box_set_active(GTK_COMBO_BOX(table_vinc_combo),0);

	code_vinc_frame = gtk_frame_new("Consultar vínculos p/ Código:");
	code_vinc_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(code_vinc_entry),8);
	gtk_entry_set_placeholder_text(GTK_ENTRY(code_vinc_entry),"Código");
	botao_consulta = gtk_button_new_with_label("Consultar");
	botao_deleta = gtk_button_new_with_label("Deletar Colunas");

	gtk_box_pack_start(GTK_BOX(code_box),code_vinc_entry,0,0,5);
	gtk_box_pack_start(GTK_BOX(code_box),botao_consulta,0,0,5);
	gtk_box_pack_start(GTK_BOX(code_box),botao_deleta,0,0,5);

	gtk_fixed_put(GTK_FIXED(code_fixed),code_box,20,20);

	vinculos_scroll = gtk_scrolled_window_new(NULL,NULL);
	vinculo_box = gtk_box_new(1,0);
	gtk_widget_set_size_request(vinculos_scroll,200,200);
	//gtk_widget_set_size_request(vinculo_box,300,200);

	gtk_container_add(GTK_CONTAINER(code_vinc_frame),code_fixed);
	gtk_container_add(GTK_CONTAINER(vinculos_scroll),vinculo_box);

	table_box = gtk_box_new(1,0);

	gtk_box_pack_start(GTK_BOX(table_box),table_vinc_combo,0,0,10);
	gtk_box_pack_start(GTK_BOX(table_box),code_vinc_frame,0,0,10);

	gtk_fixed_put(GTK_FIXED(infos_fixed),table_box,145,20);

	gtk_box_pack_start(GTK_BOX(caixa_grande),infos_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),vinculos_scroll,0,0,10);

	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
	g_signal_connect(botao_consulta,"clicked",G_CALLBACK(rec_vinculos),NULL);
	g_signal_connect(botao_deleta,"clicked",G_CALLBACK(mensagem_aviso_vinculos),NULL);
	gtk_widget_show_all(janela);
	return;
}
