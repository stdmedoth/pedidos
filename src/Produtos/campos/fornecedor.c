int fornecedor_prod()
{
	int err=0;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[100];
	fornecedores_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(fornecedor_prod_field));

	if(strlen(fornecedores_prod)<=0)
	{
		fornecedores_prod = strdup("NULL");
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),1);
		gtk_widget_grab_focus(unidade_prod_field);
		gtk_entry_set_text(GTK_ENTRY(campo_nome_fornecedor), "Sem fornecedor");
		return 0;
	}
	sprintf(query,"select * from terceiros where code = '%s'",fornecedores_prod);
	if(!(vetor = consultar(query)))
		return 1;
	if(!(campos = mysql_fetch_row(vetor)))
	{
		popup(NULL,"Fornecedor não existente");
		gtk_widget_grab_focus(fornecedor_prod_field);
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(campo_nome_fornecedor),campos[RAZ_TER_COL]);
	fornecedores_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(fornecedor_prod_field));
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),1);
	gtk_widget_grab_focus(unidade_prod_field);
	return 0;
}
