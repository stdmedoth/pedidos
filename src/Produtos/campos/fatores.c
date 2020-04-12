GtkWidget *codigo_ftr_entry,*nome_ftr_entry,*observacao_ftr_entry;
char *codigos_ftr,*nomes_ftr,*observacoes_ftr;
void codigo_ftr()
{
	char code[10];
	codigos_ftr = malloc(ENTRADA);
	codigos_ftr = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_ftr_entry));
	if(strlen(codigos_ftr)<=0)
	{
		sprintf(code,"%i",tasker("fatores"));
		g_print("Inserir um código para o fator");
		popup(NULL,"Por favor, Insira um código para o fator");
		sprintf(code,"%i",tasker("fatores"));
		gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
		vet_erro[COD_ERR] = 1;
		return;
	}	
	if(strlen(codigos_ftr)>=MAX_CODE_LEN)
	{
		g_print("Código do fator muito grande");
		popup(NULL,"Por favor,verifique com suporte\n\tsobre o tamanho do código");
		sprintf(code,"%i",tasker("fatores"));
		gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
		vet_erro[COD_ERR] = 1;
		return ;
	}
	vet_erro[COD_ERR] = 0;
	gtk_widget_grab_focus(GTK_WIDGET(nome_ftr_entry));
}

void nome_ftr()
{
	nomes_ftr = malloc(ENTRADA);
	nomes_ftr = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_ftr_entry));
	if(strlen(nomes_ftr)<=0)
	{
		g_print("Inserir um nome para o fator");
		popup(NULL,"Por favor, Insira um nome para o fator");
		vet_erro[NOM_ERR] = 1;
		return;
	}	
	if(strlen(nomes_ftr)>=MAX_NAME_LEN)
	{
		g_print("Nome do fator muito grande");
		popup(NULL,"Nome do fator muito grande");
		vet_erro[NOM_ERR] = 1;
		return;
	}
	vet_erro[NOM_ERR] = 0;
	gtk_widget_grab_focus(GTK_WIDGET(observacao_ftr_entry));
}

GtkTextBuffer *buffer_ftr;
void observacao_ftr()
{
	observacoes_ftr = malloc(MAX_OBS_LEN);
	buffer_ftr = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_ftr_entry));
	if(buffer_ftr == NULL)
	{
		popup(NULL,"Erro em observações");
		vet_erro[OBS_ERR] = 1;
		return;
	} 
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer_ftr),&inicio,&fim);
	observacoes_ftr = (gchar*)gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer_ftr),&inicio,&fim,FALSE);
	vet_erro[OBS_ERR] = 0;
	return;
}

void adicionar_fator()
{
	char *query;
	char code[10];
	int cont;
	for(cont=0;cont<=CAMPOS_QNT;cont++)
	{
		if(vet_erro[cont]!=0)
		{
			popup(NULL,"Você tem campos incorretos\n\t\tRepasse com tecla ENTER");
			g_print("Tentou concluir cadastro com campos incorretos: campo %i\n",cont);
			autologger("Tentou concluir cadastro com campos incorretos");
			return;
		}
	}
	query = malloc((int)(QUERY_LEN+INSERT_QUERY));
	if(alterando_prod==0)
	{
		sprintf(query,FTR_CAD_QUERY,ARGS_FTR_CAD_QUERY);
	}
	else
	{
		sprintf(query,FTR_UPD_QUERY,ARGS_FTR_UPD_QUERY);
	}
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro no envio, Chame suporte");
		return ;
	}
	popup(NULL,"Concluido");
	gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),"");
	gtk_entry_set_text(GTK_ENTRY(nome_ftr_entry),"");
	buffer_ftr = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_ftr_entry));
	gtk_text_buffer_get_start_iter (buffer_ftr,&inicio);
	gtk_text_buffer_get_end_iter (buffer_ftr,&fim);
	gtk_text_buffer_delete (buffer_ftr,&inicio,&fim);	
	sprintf(code,"%i",tasker("fatores"));
	gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
	
	gtk_widget_grab_focus(nome_ftr_entry);
	alterando_prod = 0;
}

void alterar_fator()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char *query;
	char code[10];
	query = malloc(MAX_QUERY_LEN);
	codigos_ftr = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_ftr_entry));
	sprintf(query,"select * from fatores where code = %s;",codigos_ftr);
	g_print("query: %s\n",query);
	autologger(query);
	vetor = consultar(query);
	if(vetor==NULL)
	{
			popup(NULL,"Erro no recebimento");
			return;
	}
	campos = mysql_fetch_row(vetor);
	if(campos==NULL)
	{
		g_print("fator não existe para ser alterado\n");
		popup(NULL,"Fator não existe");
		sprintf(code,"%i",tasker("fatores"));
		gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
		gtk_entry_set_text(GTK_ENTRY(nome_ftr_entry),"");
		buffer_ftr = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_ftr_entry));
		gtk_text_buffer_get_start_iter (buffer_ftr,&inicio);
		gtk_text_buffer_get_end_iter (buffer_ftr,&fim);
		gtk_text_buffer_delete (buffer_ftr,&inicio,&fim);	
		gtk_widget_grab_focus (GTK_WIDGET(nome_ftr_entry));
		return;
	}
	gtk_entry_set_text(GTK_ENTRY(nome_ftr_entry),campos[1]);
	buffer_ftr = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_ftr_entry));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer_ftr),campos[2],strlen(campos[2]));
	alterando_prod = 1;
}

void remover_fator()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	int erro;
	char *query;
	char code[10];
	query = malloc(MAX_QUERY_LEN);
	codigos_ftr = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_ftr_entry));
	sprintf(query,"select * from fatores where code = %s;",codigos_ftr);
	g_print("query: %s\n",query);
	autologger(query);
	vetor = consultar(query);
	if(vetor==NULL)
	{
			popup(NULL,"Erro no recebimento");
			return;
	}
	campos = mysql_fetch_row(vetor);
	if(campos==NULL)
	{
		g_print("fator não existe para ser excluido\n");
		popup(NULL,"Fator não existe");
		sprintf(code,"%i",tasker("fatores"));
		gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
		gtk_entry_set_text(GTK_ENTRY(nome_ftr_entry),"");
		buffer_ftr = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_ftr_entry));
		gtk_text_buffer_get_start_iter (buffer_ftr,&inicio);
		gtk_text_buffer_get_end_iter (buffer_ftr,&fim);
		gtk_text_buffer_delete (buffer_ftr,&inicio,&fim);	
		gtk_widget_grab_focus (GTK_WIDGET(nome_ftr_entry));
		return;
	}
	sprintf(query,"delete from fatores where code = %s;",codigos_ftr);
	erro = enviar_query(query);
	if(erro!=0)
	{
			popup(NULL,"Erro na exclusão");
			return;
	}
	popup(NULL,"concluido");
	sprintf(code,"%i",tasker("fatores"));
	gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
	alterando_prod = 0;
}
void listar_fatores()
{
	
}


int cad_fatores()
{
	int cont;
	char code[10];
	//Labels
	GtkWidget *codigo_label,*nome_label,*observacao_label;
	
	//Boxs
	GtkWidget *codigo_box,*nome_box,*observacao_box;

	//Fixeds
	GtkWidget *codigo_fixed,*nome_fixed,*observacao_fixed;
	
	//Buttons
	GtkWidget *confirma,*exclui,*pesquisa,*altera;
	
	//Container
	GtkWidget *caixona,*opcoes;
	
	//Images
	GtkWidget *imagem_confirma,*imagem_altera,*imagem_exclui,*imagem_pesquisa;
	
	GtkWidget *janela;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Cadastro de Fatores");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_widget_set_size_request(GTK_WIDGET(janela),300,300);
	
	imagem_confirma = gtk_image_new_from_file(IMG_OK);
	imagem_altera = gtk_image_new_from_file(IMG_ALTER);
	imagem_exclui = gtk_image_new_from_file(IMG_EXCLUI);
	imagem_pesquisa = gtk_image_new_from_file(IMG_PESQ);
	
	alterando_prod = 0;
	for(cont=0;cont<=CAMPOS_QNT;cont++)
	{
		vet_erro[cont] = 0;
	}
	
	codigo_label = gtk_label_new("Código:");
	nome_label   = gtk_label_new("Nome:");
	observacao_label = gtk_label_new("Observações");
	
	codigo_ftr_entry = gtk_entry_new();
	nome_ftr_entry = gtk_entry_new();
	observacao_ftr_entry = gtk_text_view_new();
	gtk_widget_set_size_request(observacao_ftr_entry,160,100);
	
	codigo_box = gtk_box_new(1,0);
	nome_box = gtk_box_new(1,0);
	observacao_box = gtk_box_new(1,0);
	
	codigo_fixed = gtk_fixed_new();
	nome_fixed = gtk_fixed_new();
	observacao_fixed = gtk_fixed_new();
	
	opcoes = gtk_box_new(0,0);
	confirma = gtk_button_new_with_label("Confirmar");
	exclui = gtk_button_new_with_label("Excluir");
	pesquisa = gtk_button_new_with_label("Pesquisar");
	altera = gtk_button_new_with_label("Alterar");

	caixona = gtk_box_new(1,0);
	
	gtk_box_pack_start(GTK_BOX(codigo_box),codigo_label,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_ftr_entry),10);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(codigo_ftr_entry),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
	gtk_entry_set_placeholder_text(GTK_ENTRY(codigo_ftr_entry),"Código");
	gtk_box_pack_start(GTK_BOX(codigo_box),codigo_ftr_entry,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(nome_box),nome_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_box),nome_ftr_entry,0,0,0);
	
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(nome_ftr_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-bold");
	gtk_entry_set_placeholder_text(GTK_ENTRY(nome_ftr_entry),"Fator");
	
	gtk_box_pack_start(GTK_BOX(observacao_box),observacao_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(observacao_box),observacao_ftr_entry,0,0,0);
	
	gtk_fixed_put(GTK_FIXED(codigo_fixed),codigo_box,145,15);
	gtk_fixed_put(GTK_FIXED(nome_fixed),nome_box,120,15);
	gtk_fixed_put(GTK_FIXED(observacao_fixed),observacao_box,120,15);
	
	gtk_box_pack_start(GTK_BOX(opcoes),confirma,0,0,5);
	gtk_button_set_image(GTK_BUTTON(confirma),imagem_confirma);
	gtk_box_pack_start(GTK_BOX(opcoes),altera,0,0,5);
	gtk_button_set_image(GTK_BUTTON(altera),imagem_altera);
	gtk_box_pack_start(GTK_BOX(opcoes),exclui,0,0,5);
	gtk_button_set_image(GTK_BUTTON(exclui),imagem_exclui);
	gtk_box_pack_start(GTK_BOX(opcoes),pesquisa,0,0,5);
	gtk_button_set_image(GTK_BUTTON(pesquisa),imagem_pesquisa);
	

	gtk_box_pack_start(GTK_BOX(caixona),codigo_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),nome_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),observacao_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),opcoes,0,0,30);
	
	sprintf(code,"%i",tasker("fatores"));
	gtk_entry_set_text(GTK_ENTRY(codigo_ftr_entry),code);
	gtk_widget_grab_focus(nome_ftr_entry);

	g_signal_connect(codigo_ftr_entry,"activate",G_CALLBACK(codigo_ftr),nome_ftr_entry);
	g_signal_connect(nome_ftr_entry,"activate",G_CALLBACK(nome_ftr),observacao_ftr_entry);

	g_signal_connect(altera,"clicked",G_CALLBACK(alterar_fator),NULL);
	g_signal_connect(exclui,"clicked",G_CALLBACK(remover_fator),NULL);
	g_signal_connect(confirma,"clicked",G_CALLBACK(codigo_ftr),NULL);
	g_signal_connect(confirma,"clicked",G_CALLBACK(nome_ftr),NULL);
	g_signal_connect(confirma,"clicked",G_CALLBACK(observacao_ftr),NULL);
	g_signal_connect(confirma,"clicked",G_CALLBACK(adicionar_fator),NULL);
	
	gtk_container_add(GTK_CONTAINER(janela),caixona);
	
	gtk_widget_show_all(janela);
	return 0;
}

