int cheque_alterar_fun(){

	cheque_alterando = 1;
	if(cheque_code_fun())
		return 1;

	struct _cheque *cheque = cheque_get_simple_cheque(atoi(cheque_code_gchar));
	if(!cheque){
		popup(NULL,"Não foi possível receber dados do cheque");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(cheque_code_entry), inttochar(cheque->code));
	gtk_entry_set_text(GTK_ENTRY(cheque_bnccode_entry), inttochar(cheque->banco->code));
	gtk_widget_activate(cheque_bnccode_entry);

	gtk_entry_set_text(GTK_ENTRY(cheque_conta_entry), cheque->conta);
	gtk_entry_set_text(GTK_ENTRY(cheque_serie_entry), cheque->serie);
	gtk_entry_set_text(GTK_ENTRY(cheque_numero_entry), cheque->numero);
	gtk_entry_set_text(GTK_ENTRY(cheque_pgntcode_entry), inttochar(cheque->pagante->code));
	gtk_widget_activate(cheque_pgntcode_entry);

	gtk_combo_box_set_active_id(GTK_COMBO_BOX(cheque_tipo_combo), inttochar(cheque->tipo));
	gtk_combo_box_set_active_id(GTK_COMBO_BOX(cheque_status_combo), inttochar(cheque->status));

	gtk_entry_set_text(GTK_ENTRY(cheque_dtemissao_entry), cheque->data_emissao);
	gtk_entry_set_text(GTK_ENTRY(cheque_valor_entry), floattochar(cheque->valor));

	return 0;
}