int cad_relat_alterar()
{
	MYSQL_ROW row;
	MYSQL_RES *res;
	GtkTreeStore *modelo_campos;
	GtkTreeIter iter_campos;
	char query[MAX_QUERY_LEN];

	enum{N_COLUNAS=3, COLUNA0=0, COLUNA1=1, COLUNA2=2};	
	
	alterando_cad_rel = 1;

	if(cad_relat_code()!=0)
		return 1;
	
	sprintf(query,"select * from criador_relat where code = %s",cad_rel_code_gchar);
	if((row = mysql_fetch_row(consultar(query)))==NULL)
	{
		alterando_cad_rel = 0;
		popup(NULL,"Relatório não existe para ser alterado");
		return 1;
	}
	
	alterando_cad_rel = 1;
	relat_struct.qnt_campos = 0;
	relat_campo_atual=1;
	while(cont<=MAX_RELAT_CAMPOS)
	{	
		relat_struct.status[cont] = FALSE;
		cont++;
	}

	modelo_campos = (GtkTreeStore*) gtk_tree_view_get_model(GTK_TREE_VIEW(cad_relat_treeview));
	gtk_tree_store_clear(modelo_campos);


	sprintf(query,"select r.nome, r.tabela, c.code,c.nome,c.sobre from relat_tab_campos as c inner join criador_relat as r on r.campos = c.code where r.code = %s",cad_rel_code_gchar);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Não foi possivel receber dados do relatorio");
		return 1;
	}
	
	modelo_campos = (GtkTreeStore*) gtk_tree_view_get_model(GTK_TREE_VIEW(cad_relat_treeview));
	gtk_tree_store_clear(modelo_campos);
	
	while((row = mysql_fetch_row(res))!=NULL)
	{
		if(relat_struct.qnt_campos==0)
		{
			gtk_entry_set_text(GTK_ENTRY(cad_rel_nome_entry),row[0]);
			gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rel_tabel_combo),atoi(row[1]));
		}
		
		gtk_tree_store_append(modelo_campos,&iter_campos,NULL);
		gtk_tree_store_set(modelo_campos,&iter_campos, 
		COLUNA0,atoi(row[2]), 
		COLUNA1,row[3], 
		COLUNA2,row[4],
		-1);
		relat_struct.campos_code_bkp[relat_campo_atual] = atoi(row[2]);	
		relat_struct.campos_code[relat_campo_atual] = atoi(row[2]);	
		relat_struct.status[relat_campo_atual] = TRUE;

		relat_struct.qnt_campos++;
		relat_campo_atual++;

		if(relat_struct.qnt_campos>0)
		{
			gtk_widget_set_sensitive(campos_rel_remover_button,TRUE);
		}
	}

	gtk_widget_set_sensitive(cad_rel_alterar_button,FALSE);
	gtk_widget_set_sensitive(cad_rel_code_entry,FALSE);
	gtk_widget_set_sensitive(psq_cad_rel_button,FALSE);
	
	return 0;
}
