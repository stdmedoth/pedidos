void est_cad_cancelar()
{
	char code[MAX_CODE_LEN];
	gtk_entry_set_text(GTK_ENTRY(est_nome_entry),"");

	sprintf(code,"%i",tasker("estoques"));
	gtk_entry_set_text(GTK_ENTRY(est_cod_entry),code);
	return ;
}
