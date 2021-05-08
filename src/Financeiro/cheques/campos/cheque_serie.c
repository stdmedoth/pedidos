int cheque_serie_fun(){
	cheque_serie_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_serie_entry));
	if(!strlen(cheque_serie_gchar)){
		popup(NULL,"A serie deve ser inserida");
		return 1;
	}
	gtk_widget_grab_focus(cheque_numero_entry);
	return 0;	
}