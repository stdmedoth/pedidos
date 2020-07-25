void est_cad_cancelar()
{
	char code[MAX_CODE_LEN];
	gtk_entry_set_text(GTK_ENTRY(est_nome_entry),"");

	est_cad_alterando = 0;
	gtk_widget_set_sensitive(est_cod_entry,TRUE);
	gtk_widget_set_sensitive(est_alterar_button,TRUE);

	sprintf(code,"%i",tasker("estoques"));
	gtk_entry_set_text(GTK_ENTRY(est_cod_entry),code);
	return ;
}
