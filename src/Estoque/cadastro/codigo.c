int est_cad_code()
{
	est_cad_cod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_cod_entry));

	if(!strlen(est_cad_cod_gchar)){
		popup(NULL,"Insira o código");
		est_cad_cancelar();
		return 1;
	}


	gtk_widget_grab_focus(est_nome_entry);
	return 0;
}
