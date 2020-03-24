gint *vet_cod;
int bloco_qnt=0;
int codigo_preco[MAX_PROD];

int enviar_preco(GtkWidget *widget,int *codigo_preco_pointer)
{
	int codigo;
	char *query;
	int analise,erro=0;
	int posicao_do_envio=0;
	gchar *valor;
	codigo = *codigo_preco_pointer;
	valor  = malloc(VLR_MAX_LEN);
	query  = malloc(QUERY_LEN);
	g_print("iniciando funcao enviar_preco\n");
	for(analise=0;analise<bloco_qnt;analise++)
	{
		if(codigo_preco[analise]==codigo)
		{
			posicao_do_envio = analise;
			break;
		}	
	}
	g_print("%i blocos\n",bloco_qnt);
	g_print("enviando preços da box %i\n",posicao_do_envio);
	if(preco_entry[posicao_do_envio]==NULL)
	{
		g_print("Erro de memoria\n");	
		return 1;
	}
	valor = (gchar*)gtk_entry_get_text(GTK_ENTRY(preco_entry[posicao_do_envio]));
	if(critica_preco(valor,preco_entry[posicao_do_envio])!=0)
		return 1;
	sprintf(query,"update precos set valor = %s where code = %i;",valor,*codigo_preco);
	g_print("%s\n",query);
	erro = enviar_query(query);
	if(erro!=0)
	{
			popup(NULL,"Erro ao tentar atualizar o preço");
			return 1;
	}
	popup(NULL,"Preço atualizado com sucesso");
	g_print("codigo :%i\n",codigo);
	return 0;
}
int verificar_entrada(GtkWidget *widget, int *codigo_preco)
{
	g_print("codigo :%i\n",*codigo_preco);	
	return 0;
}
int prod_vinc(GtkWidget *widget,int *codigo_preco)
{
	g_print("codigo :%i\n",*codigo_preco);
	return 0;
}
int rem_preco(GtkWidget *widget,int *codigo_preco)
{
	g_print("codigo :%i\n",*codigo_preco);	
	return 0;
}
int rec_precos()
{

	char *query;
	bloco_qnt=0;
	MYSQL_ROW campos;
	query = malloc(QUERY_LEN);
	code_terc();
	sprintf(query,"select b.code,a.nome,valor from precos as b join produtos as a on a.code = b.produto where terceiro = %s",codigos_ter);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Query de precos voltou com vetor nulo\n");
		autologger("Query de precos voltou com vetor nulo\n");
		return 1;
	}
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{	
		precos_caixas[bloco_qnt] = gtk_box_new(1,0);
		codigo_preco[bloco_qnt] = atoi(campos[0]);
		produto_label[bloco_qnt] = gtk_label_new(campos[1]);
		preco_entry[bloco_qnt] = gtk_entry_new();
		atualizar_preco[bloco_qnt] = gtk_button_new_with_label("Atualizar");
		remover_preco[bloco_qnt] = gtk_button_new_with_label("Remover");
		gtk_box_pack_start(GTK_BOX(precos_caixas[bloco_qnt]),produto_label[bloco_qnt],0,0,0);
		gtk_box_pack_start(GTK_BOX(precos_caixas[bloco_qnt]),preco_entry[bloco_qnt],0,0,0);
		gtk_box_pack_start(GTK_BOX(precos_caixas[bloco_qnt]),atualizar_preco[bloco_qnt],0,0,0);
		gtk_box_pack_start(GTK_BOX(precos_caixas[bloco_qnt]),remover_preco[bloco_qnt],0,0,0);
		vet_cod[bloco_qnt] = bloco_qnt;
		g_signal_connect(preco_entry[bloco_qnt],"activate",G_CALLBACK(verificar_entrada),&vet_cod[bloco_qnt]);
		g_signal_connect(atualizar_preco[bloco_qnt],"clicked",G_CALLBACK(enviar_preco),&vet_cod[bloco_qnt]);
		g_signal_connect(remover_preco[bloco_qnt],"clicked",G_CALLBACK(rem_preco),&vet_cod[bloco_qnt]);
		
		gtk_entry_set_text(GTK_ENTRY(preco_entry[bloco_qnt]),campos[2]);
		gtk_box_pack_start(GTK_BOX(precos_scroll_caixa),precos_caixas[bloco_qnt],0,0,10);
		bloco_qnt++;
	}
	if(bloco_qnt==0)
	{

		g_print("Terceiro sem nenhum preco vinculado\n");
		autologger("Terceiro sem nenhum preco vinculado");
	}
	gtk_widget_show_all(precos_scroll_caixa);
	return 0;
}

