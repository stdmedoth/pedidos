int cad_relat_cancelar()
{
	int cont=1;
	char code[MAX_CODE_LEN];
	GtkTreeIter iter1;
	enum {COLUMN0=0, COLUMN1=1, COLUMN2=2};
	GtkTreeStore *modelo_campos;

	while(cont<=MAX_RELAT_CAMPOS)
	{	
		relat_struct.campos_code_bkp[cont] =  0;
		relat_struct.status[cont] = FALSE;
		cont++;
	}

	sprintf(code,"%i",tasker("criador_relat"));
	gtk_entry_set_text(GTK_ENTRY(cad_rel_code_entry),code);
	gtk_entry_set_text(GTK_ENTRY(cad_rel_nome_entry),"");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rel_tabel_combo),0);
	
	relat_struct.qnt_campos = 0;
	relat_campo_atual=1;
	
	modelo_campos = (GtkTreeStore*) gtk_tree_view_get_model(GTK_TREE_VIEW(cad_relat_treeview));
	gtk_tree_store_clear(modelo_campos);
	gtk_tree_store_append(modelo_campos,&iter1,NULL);
	gtk_tree_store_set(modelo_campos,&iter1,COLUMN0,0,COLUMN1,"",COLUMN2,"",-1);
	alterando_cad_rel=0;
	concluindo_cad_rel=0;
	gtk_widget_grab_focus(cad_rel_nome_entry);
	
	gtk_widget_set_sensitive(cad_rel_alterar_button,TRUE);
	gtk_widget_set_sensitive(cad_rel_code_entry,TRUE);
	gtk_widget_set_sensitive(psq_cad_rel_button,TRUE);
	gtk_widget_set_sensitive(cad_rel_tabel_combo,TRUE);
	
	return 0;
}
