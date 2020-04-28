int verifica_frete()
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
	{
		gtk_widget_set_sensitive(frete_pago_entry,TRUE);
		gtk_widget_grab_focus(frete_pago_entry);
	}
	else
	{
		gtk_widget_set_sensitive(frete_pago_entry,FALSE);
		gtk_widget_grab_focus(concluir_ter_buttom);
	}
	return 0;
}
