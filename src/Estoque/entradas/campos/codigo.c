int est_ent_codigo_fun()
{
	est_ent_cod_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_cod_entry));
	
	if(strlen(est_ent_cod_gchar)<=0)
	{
		popup(NULL,"Insira o código");
		gtk_widget_grab_focus(est_ent_cod_entry);
		return 1;
	}
	
	
	gtk_widget_grab_focus(est_ent_data_entry);
	return 0;
}
