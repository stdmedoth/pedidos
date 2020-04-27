int verifica_frete()
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
		gtk_widget_set_sensitive(frete_pago_entry,TRUE);
	else
		gtk_widget_set_sensitive(frete_pago_entry,FALSE);
	return 0;
}
