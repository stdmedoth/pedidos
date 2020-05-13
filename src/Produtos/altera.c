int altera_prod()
{
	char task[10];
	char query[MAX_QUERY_LEN];
	char *row;
	MYSQL_RES *vetor;
	MYSQL_ROW campo;
	row = malloc(ENTRADA);
	codigos_prod = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_prod_field));
	sprintf(query,"select p.code,  p.nome,  p.peso,  p.unidade,  p.fornecedor,  p.grupo,  p.preco_vista,  p.preco_faturado, p.observacoes from produtos as p join unidades as u on p.unidade = u.code where p.code = '%s';",codigos_prod);
	g_print("query: %s\n",query);
	autologger(query);
	vetor = consultar(query);
	if(vetor == NULL)
	{
		popup(NULL,"Erro na query, algo está errado\n\tConsulte com suporte");
		autologger(query);
		return 1;
	}
	campo = mysql_fetch_row(vetor);
	if(campo==NULL)
	{
		g_print("produto não existe para ser alterado\n");
		popup(NULL,"Produto não existe");
		sprintf(task,"%i",tasker("produtos"));
		gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),task);
		gtk_entry_set_text(GTK_ENTRY(nome_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(preco_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(peso_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),"");
		gtk_entry_set_text(GTK_ENTRY(preco_faturado_prod_field),"");
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
		gtk_text_buffer_get_start_iter (buffer,&inicio);
		gtk_text_buffer_get_end_iter (buffer,&fim);
		gtk_text_buffer_delete (buffer,&inicio,&fim);	
		
		gtk_widget_grab_focus (GTK_WIDGET(nome_prod_field));
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(nome_prod_field),campo[PROD_NOM_COL]);
	
	sprintf(row,"%.2f",atof(campo[PROD_PRC_VIS_COL]));
	gtk_entry_set_text(GTK_ENTRY(preco_prod_field),row);
	
	sprintf(row,"%.2f",atof(campo[PROD_PES_COL]));
	gtk_entry_set_text(GTK_ENTRY(peso_prod_field),row);
	
	strcpy(row,campo[PROD_UND_COL]);
	gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),row);
	
	strcpy(row,campo[PROD_FORN_COL]);
	gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),row);
	
	strcpy(row,campo[PROD_GRP_COL]);
	gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),row);
	
	strcpy(row,campo[PROD_PRC_FAT_COL]);
	gtk_entry_set_text(GTK_ENTRY(preco_faturado_prod_field),row);
	
	strcpy(observacoes_prod,campo[PROD_OBS_COL]);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),observacoes_prod,strlen(observacoes_prod));
	
	alterando_prod=1;

	code_prod();
	fornecedor_prod();
	grupo_prod();
	nome_prod();
	peso_prod();
	preco_prod();
	und_prod();
	preco_faturado_prod();
	
	memset(query,0x0,strlen(query));
	
	gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),TRUE);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;
}
