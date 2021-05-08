int cheque_bnc_fun(){
	
	cheque_bnccode_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_bnccode_entry));
	if(!strlen(cheque_bnccode_gchar)){	
		popup(NULL,"O banco deve ser inserido");
		return 1;
	}
	struct _banco *banco = get_banco(atoi(cheque_bnccode_gchar));
	if(!banco){
		popup(NULL,"Não foi possível carregar banco");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(cheque_bncnome_entry), banco->nome);
	gtk_widget_grab_focus(cheque_conta_entry);	
	return 0;
}