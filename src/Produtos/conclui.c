int conclui_prod(GtkWidget* nome, gpointer *botao)
{
	int err;
	char *code;
	code = malloc(10);
	char *query;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;

	concluindo_prod=1;
	if(code_prod()){
		gtk_widget_grab_focus(codigo_prod_field);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),0);
		return 1;
	}
	if(nome_prod()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),0);
		gtk_widget_grab_focus(nome_prod_field);
		return 1;
	}
	if(peso_prod()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),0);
		gtk_widget_grab_focus(peso_prod_field);
		return 1;
	}
	if(fornecedor_prod()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),0);
		gtk_widget_grab_focus(fornecedor_prod_field);
		return 1;
	}

	if(grupo_prod()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),1);
		gtk_widget_grab_focus(grupo_prod_field);
		return 1;
	}
	if(precos_prod_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),1);
		gtk_widget_grab_focus(preco_prod_field);
		return 1;
	}
	if(und_unt_prod()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),1);
		gtk_widget_grab_focus(unidade_prod_field);
		return 1;
	}
	if(und_atac_prod()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),1);
		gtk_widget_grab_focus(unidade_prod_field);
		return 1;
	}
	if(prod_ncm_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
		gtk_widget_grab_focus(prod_ncm_entry);
		return 1;
	}
	if(prod_origem_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
		gtk_widget_grab_focus(prod_origem_combo);
		return 1;
	}
	if(prod_icmscst_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
		gtk_widget_grab_focus(prod_icmscst_combo);
		return 1;
	}
	if(prod_piscst_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
		gtk_widget_grab_focus(prod_piscst_combo);
		return 1;
	}
	if(prod_cofinscst_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
		gtk_widget_grab_focus(prod_cofinscst_combo);
		return 1;
	}

	if(obs_prod()!=0){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),3);
		return 1;
	}

	g_print("alocando memoria para query %i\n",(int)(MAX_QUERY_LEN+INSERT_QUERY));
	query = malloc((int)(MAX_QUERY_LEN+INSERT_QUERY));
	if(query==NULL)
	{
			popup(NULL,"Erro de memoria");
			autologger("Erro de memoria");
			return 1;
	}
	g_print("iniciando concluir_ter()\n");

	if(alterando_prod==0)
	{
		sprintf(query,PROD_CAD_QUERY,ARGS_PROD_CAD_QUERY);
	}
	else
	{
		sprintf(query,PROD_UPD_QUERY,ARGS_PROD_UPD_QUERY);
	}

	if(stoi(codigos_prod)==-1)
	{
		if(strlen(codigos_prod)>8)
		{
			autologger("Codigo produto chegou ao limite\n");
			popup(NULL,"O código do produto deve ser menor\n");
			return -1;
		}
	}
	g_print("%s\n",query);
	autologger(query);
	err = enviar_query(query);
	if(err!=0)
	{
		g_print("Query para tabela produtos\n");
		autologger("Query para tabela produtos");
		g_print("codigo do erro %i\n",err);
		g_print("%s\n\n",query);
		autologger(query);
		return 1;
	}
	else
	{
		autologger(query);
		g_print("Query para tabela produtos\n");
		g_print("Query envida com sucesso\n");
		popup(NULL,"Concluido");
		gtk_label_set_text(GTK_LABEL(acao_atual2),"Cadastrando");
		cancelar_prod();
	}

	printf("finalizando conclui_ter()\n");
	gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
	return 0;
}
