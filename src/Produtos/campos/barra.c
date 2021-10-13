int prod_barra_fun()
{
	prod_barra_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(prod_barra_entry));
	if(!prod_barra_gchar || !strlen(prod_barra_gchar)){
    prod_barra_gchar = strdup("NULL");
	}

  gtk_widget_grab_focus(prod_origem_combo);
	return 0;
}
