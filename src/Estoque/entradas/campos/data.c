int est_ent_data_fun()
{
	est_ent_data_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_data_entry));

	if(strlen(est_ent_data_gchar)<=0)
	{
		popup(NULL,"Insira a data");
		gtk_widget_grab_focus(est_ent_data_entry);
		return 1;
	}

	gtk_widget_grab_focus(est_ent_client_entry);

	return 0;
}
