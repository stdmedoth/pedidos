int cheque_valor_fun(){
	cheque_valor_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_valor_entry));
	if(!strlen(cheque_valor_gchar)){
		popup(NULL,"O valor do cheque deve ser inserido");
		return 1;
	}
	gtk_widget_grab_focus(cheque_concluir_button);
	return 0;
}