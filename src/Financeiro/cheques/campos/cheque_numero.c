int cheque_numero_fun(){
	cheque_numero_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_numero_entry));
	if(!strlen(cheque_numero_gchar)){
		popup(NULL,"O número do cheque deve ser inserido");
		return 1;		
	}
	gtk_widget_grab_focus(cheque_pgntcode_entry);
	return 0;
}