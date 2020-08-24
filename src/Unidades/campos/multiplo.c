int multiplo_und()
{
	mult_und = (gchar *) gtk_entry_get_text(GTK_ENTRY(mult_und_field));

	if(strlen(mult_und)<=0)
	{
		popup(NULL,"Por favor, insira um Multiplo");
		gtk_widget_grab_focus(mult_und_field);
		return 1;
	}

	gtk_widget_grab_focus(medida_und_combo_box);
	return 0;
}
