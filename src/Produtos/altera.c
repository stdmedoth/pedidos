int altera_prod()
{
	char task[10];
	char query[100];
	char *row;
	row = malloc(ENTRADA);
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	codigos_prod = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_prod_field));
	sprintf(query,"select * from produtos where code = '%s';",codigos_prod);
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);
	if(campo==NULL)
	{
		g_print("produto não existe para ser alterado\n");
		popup(NULL,"Produto não existe");
		sprintf(task,"%i",tasker("Produto"));
		gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),task);
		gtk_entry_set_text(GTK_ENTRY(nome_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(preco_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(peso_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(marca_prod_field),"");
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
		gtk_text_buffer_get_start_iter (buffer,&inicio);
		gtk_text_buffer_get_end_iter (buffer,&fim);
		gtk_text_buffer_delete (buffer,&inicio,&fim);	
		
		gtk_widget_grab_focus (GTK_WIDGET(nome_prod_field));
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(nome_prod_field),campo[1]);
	sprintf(row,"%.2f",atof(campo[2]));
	gtk_entry_set_text(GTK_ENTRY(preco_prod_field),row);
	sprintf(row,"%.2f",atof(campo[3]));
	gtk_entry_set_text(GTK_ENTRY(peso_prod_field),row);
	strcpy(row,campo[4]);
	gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),row);
	strcpy(row,campo[5]);
	gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),row);
	strcpy(row,campo[6]);
	gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),row);
	strcpy(row,campo[7]);
	gtk_entry_set_text(GTK_ENTRY(marca_prod_field),row);
	strcpy(observacoes_prod,campo[8]);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),observacoes_prod,strlen(observacoes_prod));
	memset(query,0x0,strlen(query));
	alterando=1;
	gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),TRUE);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;
}