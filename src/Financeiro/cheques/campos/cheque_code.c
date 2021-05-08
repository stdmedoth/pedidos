int cheque_code_fun(){
	cheque_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_code_entry));
	if(!strlen(cheque_code_gchar)){
		popup(NULL,"O código deve ser inserido");
		return 1;
	}

	if(!cheque_alterando){
		struct _cheque *cheque = cheque_get_simple_cheque(atoi(cheque_code_gchar));
		if(cheque){
			cheque_alterar_fun();
		}
	}
	

	gtk_widget_grab_focus(cheque_bnccode_entry);	
	return 0;
}