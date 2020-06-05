int prazo_fun()
{
	prazo_ter = (gchar*) gtk_entry_get_text(GTK_ENTRY(prazo_ter_field));

	if(strlen(prazo_ter)<=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
		popup(NULL,"Insira uma data para o prazo do cliente");
		return 1;
	}

	gtk_widget_grab_focus(frete_pago_flag);
	return 0;
}
