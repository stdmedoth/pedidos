int cheque_cancelar_fun(){

	char task[MAX_CODE_LEN];
	sprintf(task,"%i",tasker("cheque"));
	cheque_alterando = 0;
	gtk_widget_grab_focus(cheque_bnccode_entry);
	gtk_entry_set_text(GTK_ENTRY(cheque_code_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_bnccode_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_bncnome_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_conta_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_serie_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_numero_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_pgntcode_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_pgntnome_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_dtemissao_entry), "");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cheque_status_combo), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(cheque_tipo_combo), 0);
	gtk_entry_set_text(GTK_ENTRY(cheque_valor_entry), "");
	gtk_entry_set_text(GTK_ENTRY(cheque_code_entry), task);	

	return 0;
}