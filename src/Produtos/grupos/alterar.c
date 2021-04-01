int altera_grupo()
{
	grpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_grp_entry));

	struct _grupo *grupo = grp_get_grupo(atoi(grpcode));
	if(!grupo){
		popup(NULL,"Grupo pai não existente");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(nome_grp_entry), grupo->nome);
	gtk_entry_set_text(GTK_ENTRY(pai_grp_entry), inttochar(grupo->pai) );
	gtk_entry_set_text(GTK_ENTRY(painome_grp_entry), grupo->pai_nome);
	gtk_widget_grab_focus(confirma_grp_button);
	gtk_widget_set_sensitive(cod_grp_entry,FALSE);
	gtk_widget_set_sensitive(psq_grp_button,FALSE);
	gtk_widget_set_sensitive(altera_grp_button,FALSE);
	alterando_grp = 1;
	return 0;
}
