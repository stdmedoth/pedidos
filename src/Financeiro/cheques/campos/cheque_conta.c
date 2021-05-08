int cheque_conta_fun(){
	cheque_conta_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_conta_entry));
	if(!strlen(cheque_conta_gchar)){	
		popup(NULL,"A conta deve ser inserida");
		return 1;
	}
	gtk_widget_grab_focus(cheque_serie_entry);
	return 0;	
}