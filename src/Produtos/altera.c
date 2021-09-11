int altera_prod()
{
	char task[10];
	char query[MAX_QUERY_LEN];
	char *row;
	MYSQL_RES *vetor, *res;
	MYSQL_ROW campo, mrow;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	row = malloc(ENTRADA);
	codigos_prod = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_prod_field));
	sprintf(query,"select p.code,  p.nome, p.peso, p.preco, p.unidades, p.unidades_atacado,  p.fornecedor,  p.grupo, p.grupo_nivel, p.ncm, p.code_barra, p.icmscst, p.piscst, p.pisaliq, p.cofinscst, p.cofinsaliq, p.origem,  p.observacoes, DATE_FORMAT(dt_criacao, '%%d/%%m/%%Y'), DATE_FORMAT(dt_modificacao, '%%d/%%m/%%Y') from produtos as p join unidades as u on p.unidades = u.code where p.code = '%s';",codigos_prod);
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
		cancelar_prod();
		gtk_widget_grab_focus (GTK_WIDGET(nome_prod_field));
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(nome_prod_field),campo[PROD_NOM_COL]);

	if(campo[PROD_PES_COL]){
		sprintf(row,"%.2f",atof(campo[PROD_PES_COL]));
		gtk_entry_set_text(GTK_ENTRY(peso_prod_field),row);
	}

	if(campo[PROD_PRC_COL]){
		sprintf(row,"%.2f",atof(campo[PROD_PRC_COL]));
		gtk_entry_set_text(GTK_ENTRY(preco_prod_field),row);
	}

	if(campo[PROD_GRP_COL]){
		row = strdup(campo[PROD_GRP_COL]);
		gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),row);
	}

	if(campo[PROD_FORN_COL]){
		row = strdup(campo[PROD_FORN_COL]);
		gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),row);
	}

	if(campo[PROD_UND_COL]){
		row = strdup(campo[PROD_UND_COL]);
		gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),row);
	}

	if(campo[PROD_UND_ATAC_COL]){
		row = strdup(campo[PROD_UND_ATAC_COL]);
		gtk_entry_set_text(GTK_ENTRY(qnt_atacado_field),row);
	}

	if(campo[PROD_NCM_COL]){
		row = strdup(campo[PROD_NCM_COL]);
		sprintf(query, "select cod_ncm from ncm where code = '%s'", row);
		if(!(res = consultar(query))){
			popup(NULL,"Não foi possível consultar NCM base");
			return 1;
		}
		if(!(mrow = mysql_fetch_row(res))){
			popup(NULL,"NCM base não existente");
			return 1;
		}else{
			row = strdup(mrow[0]);
			gtk_entry_set_text(GTK_ENTRY(prod_ncm_entry),row);
			gtk_widget_activate(prod_ncm_entry);
		}
	}

	if(campo[PROD_BAR_COL]){
		gchar *code_barra = strdup(campo[PROD_BAR_COL]);
		gtk_entry_set_text(GTK_ENTRY(prod_barra_entry), code_barra);
	}

	if(campo[PROD_ICMSCST_COL]){
		gchar *icmscst = strdup(campo[PROD_ICMSCST_COL]);
		gtk_combo_box_set_active_id(GTK_COMBO_BOX(prod_icmscst_combo), icmscst);
	}

	if(campo[PROD_PISCST_COL]){
		gchar *piscst = strdup(campo[PROD_PISCST_COL]);
		gtk_combo_box_set_active_id(GTK_COMBO_BOX(prod_piscst_combo), piscst);
	}

	if(campo[PROD_PISALIQ_COL]){
		gchar *pisaliq = strdup(campo[PROD_PISALIQ_COL]);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(prod_pisaliq_entry), atof(pisaliq));
	}

	if(campo[PROD_COFINSCST_COL]){
		gchar *cofinscst = strdup(campo[PROD_COFINSCST_COL]);
		gtk_combo_box_set_active_id(GTK_COMBO_BOX(prod_cofinscst_combo), cofinscst);
	}

	if(campo[PROD_COFINSALIQ_COL]){
		gchar *cofinsaliq = strdup(campo[PROD_COFINSALIQ_COL]);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(prod_cofinsaliq_entry), atof(cofinsaliq));
	}

	if(campo[PROD_ORIGEM_COL]){
		gchar *origem = strdup(campo[PROD_ORIGEM_COL]);
		gtk_combo_box_set_active_id(GTK_COMBO_BOX(prod_origem_combo), origem);
	}


	if(campo[PROD_OBS_COL]){
		observacoes_prod = malloc(strlen(campo[PROD_OBS_COL]));
		strcpy(observacoes_prod, campo[PROD_OBS_COL]);
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),observacoes_prod,strlen(observacoes_prod));
	}
	if(campo[PROD_DTMODIF_COL]){
		gtk_entry_set_text(GTK_ENTRY(prod_dt_alteracao_entry), campo[PROD_DTMODIF_COL]);
	}

	alterando_prod=1;
	concluindo_prod=0;

	nome_prod();
	peso_prod();
	grupo_prod();
	fornecedor_prod();
	und_unt_prod();
	und_atac_prod();

	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),0);
	gtk_widget_set_sensitive(prod_prcwnd_button,TRUE);
	memset(query,0x0,strlen(query));

	gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(codigo_prod_field),FALSE);

	gtk_widget_set_sensitive(GTK_WIDGET(psq_prod_codigo_button),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(prod_alterar_button),FALSE);

	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;
}
