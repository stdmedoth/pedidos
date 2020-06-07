int cad_relat_nome()
{
	cad_rel_nome_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_rel_nome_entry));
	if(strlen(cad_rel_nome_gchar)<=0)
	{
		popup(NULL,"Insira o nome do relatorio");
		gtk_widget_grab_focus(cad_rel_nome_entry);
		return 1;
	}
	if(strlen(cad_rel_nome_gchar)>=MAX_RELAT_NOME)
	{
		popup(NULL,"Nome do relatório excede limite");
		gtk_widget_grab_focus(cad_rel_nome_entry);
		return 1;	
	}
	strcpy(relat_struct.nome,cad_rel_nome_gchar);
	
	gtk_widget_grab_focus(cad_rel_psqrow_button);
	return 0;
}
