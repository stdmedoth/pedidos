int est_ent_qnt_fun()
{
	est_ent_qnt_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_qnt_entry));

	if(strlen(est_ent_qnt_gchar)<=0)
	{
		popup(NULL,"Insira a quantidade");
		gtk_widget_grab_focus(est_ent_qnt_entry);
		return 1;
	}


	gtk_widget_grab_focus(est_ent_confirma_button);
	return 0;
}
