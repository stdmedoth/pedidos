int codigo_precos[MAX_PROD];
int enviar_preco(int codigo_preco)
{
	g_print("%i\n",codigo_preco);
	return 0;
}
int verificar_entrada(int* codigo_preco)
{
	g_print("%i\n",*codigo_preco);
	return 0;
}
int prod_vinc(int* codigo_preco)
{
	g_print("%i\n",*codigo_preco);
	return 0;
}
int rem_preco(int* codigo_preco)
{
	g_print("%i\n",*codigo_preco);
	return 0;
}
int rec_precos()
{
	int pos=0;
	char *query;
	MYSQL_ROW campos;
	query = malloc(QUERY_LEN);
	code_terc();
	sprintf(query,"select * from precos where terceiro = %s",codigos_ter);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Query de precos voltou com vetor nulo\n");
		autologger("Query de precos voltou com vetor nulo\n");
		return 1;
	}
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		codigo_precos[pos] = atoi(campos[0]);
		g_print("codigo do preco: %i\n",codigo_precos[pos]);
		precos_caixas[pos] = gtk_box_new(1,0);
		produto_label[pos] = gtk_label_new(campos[1]);
		preco_entry[pos] = gtk_entry_new();
		atualizar_preco[pos] = gtk_button_new_with_label("Enviar");
		remover_preco[pos] = gtk_button_new_with_label("Remover");
		gtk_box_pack_start(GTK_BOX(precos_caixas[pos]),produto_label[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(precos_caixas[pos]),preco_entry[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(precos_caixas[pos]),atualizar_preco[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(precos_caixas[pos]),remover_preco[pos],0,0,0);

		g_signal_connect(preco_entry[pos],"activate",G_CALLBACK(verificar_entrada),NULL);
		g_signal_connect(atualizar_preco[pos],"clicked",G_CALLBACK(enviar_preco),NULL);
		g_signal_connect(remover_preco[pos],"clicked",G_CALLBACK(rem_preco),NULL);

//		g_signal_connect(remover_preco[pos],"clicked",G_CALLBACK(gtk_widget_hide),precos_caixas[pos]);
		gtk_entry_set_text(GTK_ENTRY(preco_entry[pos]),campos[3]);
		gtk_box_pack_start(GTK_BOX(precos_scroll_caixa),precos_caixas[pos],0,0,0);
		pos++;
	}
	if(pos==0)
	{

		g_print("Terceiro sem nenhum preco vinculado\n");
		autologger("Terceiro sem nenhum preco vinculado");
	}
	gtk_widget_show_all(precos_scroll_caixa);
	return 0;
}
