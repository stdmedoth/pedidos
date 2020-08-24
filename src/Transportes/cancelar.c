int trsp_cad_cancelar_fun(){

	gtk_entry_set_text(GTK_ENTRY(trsp_cad_trspcode_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_clicode_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cepini_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cepentr_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_nument_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_vlrfrt_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_descfrt_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_endini_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_endentr_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_trsp_entry),"");
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cli_entry),"");

	trsp_cad_alterando = 0;
	trsp_cad_concluindo = 0;
	trsp_cad_rec_alteracao = 0;

	char task[MAX_CODE_LEN];
	sprintf(task,"%i",tasker("servico_transporte"));

	gtk_entry_set_text(GTK_ENTRY(trsp_cad_code_entry),task);
	gtk_widget_grab_focus(trsp_cad_trspcode_entry);

	return 0;
}
