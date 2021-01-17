int trsp_cad_alterar_fun(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	trsp_cad_alterando = 1;
	trsp_cad_rec_alteracao = 1;

	if(trsp_cad_code_fun())
		return 1;

	sprintf(query,"select * from servico_transporte where code = %s",trsp_cad_code_gchar);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível alterar");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"O serviço não existe para ser alterado");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(trsp_cad_trspcode_entry),row[TRSP_TRANSP_COL]);
	gtk_widget_activate(trsp_cad_trspcode_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_clicode_entry),row[TRSP_CLI_COL]);
	gtk_widget_activate(trsp_cad_clicode_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cepini_entry),row[TRSP_CEPINI_COL]);
	gtk_widget_activate(trsp_cad_cepini_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cepentr_entry),row[TRSP_CEPFIM_COL]);
	gtk_widget_activate(trsp_cad_cepentr_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_nument_entry),row[TRSP_NUM_COL]);
	gtk_widget_activate(trsp_cad_nument_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_orc_entry),row[TRSP_ORC_COL]);
	gtk_widget_activate(trsp_cad_orc_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_vlrfrt_entry),row[TRSP_VLR_COL]);
	gtk_widget_activate(trsp_cad_vlrfrt_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_descfrt_entry),row[TRSP_DESC_COL]);
	gtk_widget_activate(trsp_cad_descfrt_entry);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(trsp_cad_frtpag_check), atoi(row[TRSP_FRTPAG_COL]));

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(trsp_cad_obs_entry));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), row[TRSP_OBS_COL], strlen(row[TRSP_OBS_COL]));

	trsp_cad_rec_alteracao = 0;

	return 0;
}
