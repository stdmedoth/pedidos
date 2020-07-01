int est_cad_nome()
{
	est_cad_nome_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(est_nome_entry));
	if(!strlen(est_cad_nome_gchar)){
		popup(NULL,"Insira o nome para o estoque");
		return 1;
	}

	return 0;
}
