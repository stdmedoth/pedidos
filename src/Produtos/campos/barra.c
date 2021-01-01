int prod_barra_fun()
{
	prod_barra_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(prod_barra_entry));
	if(strlen(prod_barra_gchar)<=0){
		/*popup(NULL,"Insira um código de barras");
		gtk_widget_grab_focus(GTK_WIDGET(prod_barra_entry));
		return 1;*/
    prod_barra_gchar = strdup("");
	}

  gtk_widget_grab_focus(prod_origem_combo);
	g_print("Código de barras: %s\n",prod_barra_gchar);
	return 0;
}
