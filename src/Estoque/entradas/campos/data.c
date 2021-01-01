int est_ent_data_fun(){
	est_ent_data_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_ent_data_entry));

	if(strlen(est_ent_data_gchar)<=0){
		est_ent_data_gchar = strdup(data_sys);
	}

	gchar *est_ent_data_gchar2 = formatar_data(est_ent_data_gchar);
	gtk_entry_set_text(GTK_ENTRY(est_ent_data_entry), est_ent_data_gchar2);
	est_ent_data_gchar = strdup(est_ent_data_gchar2);


	gtk_widget_grab_focus(est_ent_client_entry);

	return 0;
}
