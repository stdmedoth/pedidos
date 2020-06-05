int est_said_qnt_fun()
{
	est_said_qnt_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_qnt_entry));
	
	if(strlen(est_said_qnt_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_said_qnt_entry);
		return 1;
	}
	
	gtk_widget_grab_focus(est_said_confirma_button);
	return 0;
}
