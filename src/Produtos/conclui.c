int conclui_prod(GtkWidget* nome, gpointer *botao)
{
	int err;
	char code[MAX_CODE_LEN];
	char query[MAX_QUERY_LEN+INSERT_QUERY];
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
	if(prod_barra_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
		gtk_widget_grab_focus(prod_barra_entry);
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

	file_logger("iniciando conclui_prod()\n");
	if(alterando_prod==0){
		sprintf(query,PROD_CAD_QUERY,ARGS_PROD_CAD_QUERY);
	}else{
		sprintf(query,PROD_UPD_QUERY,ARGS_PROD_UPD_QUERY);
	}


	if(enviar_query(query)){
	
		file_logger("Erro Query para tabela produtos");
		file_logger(query);
		return 1;
	
	}else{
		file_logger(query);
		popup(NULL,"Concluido");
		cancelar_prod();
	}

	file_logger("finalizando conclui_prod()");
	gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
	return 0;
}
