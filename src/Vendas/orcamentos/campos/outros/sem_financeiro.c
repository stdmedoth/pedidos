int orc_pag_sem_finan(){

	gtk_widget_hide(orc_box_datas);

	gtk_widget_hide(orc_bnc_fixed);
	gtk_widget_hide(orc_cheque_fixed);

	gtk_entry_set_text(GTK_ENTRY(orc_bnc_code_entry), "");
	gtk_entry_set_text(GTK_ENTRY(orc_cheque_code_entry), "");

	return 0;
}
