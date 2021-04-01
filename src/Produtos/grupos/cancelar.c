int cancela_grupo()
{
	char code[MAX_CODE_LEN];
	sprintf(code,"%i",tasker("grupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_grp_entry),code);
	gtk_entry_set_text(GTK_ENTRY(nome_grp_entry),"");
	gtk_entry_set_text(GTK_ENTRY(pai_grp_entry), "" );
	gtk_entry_set_text(GTK_ENTRY(painome_grp_entry), "");
	gtk_widget_grab_focus(nome_grp_entry);
	gtk_widget_set_sensitive(cod_grp_entry,TRUE);
	gtk_widget_set_sensitive(psq_grp_button,TRUE);
	gtk_widget_set_sensitive(altera_grp_button,TRUE);
	alterando_grp = 0;
	concluindo_grp = 0;

	if( atoi(code) == 2){
		gtk_entry_set_text(GTK_ENTRY(pai_grp_entry), "1");
		gtk_widget_activate(pai_grp_entry);
	}

	GtkTreeStore *modelo = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(cad_grp_treeview)));
	g_object_ref(G_OBJECT(modelo));
  	gtk_tree_view_set_model(GTK_TREE_VIEW(cad_grp_treeview),NULL);
  	gtk_tree_store_clear(modelo);
  	gtk_tree_view_set_model(GTK_TREE_VIEW(cad_grp_treeview),GTK_TREE_MODEL(modelo));

	if(!grp_get_tree(modelo, 1, NULL))
		return 1;

	gtk_widget_grab_focus(nome_grp_entry);
	return 0;
}
