int prazo_fun()
{
	prazo_ter = gtk_entry_get_text(GTK_ENTRY(prazo_ter_field));
	if(strlen(prazo_ter)<=0)
	{
		popup(NULL,"Insira uma data para o prazo do cliente");
		vet_erro[PRAZ_ERR] = 1;
		return 1;
	}
	
	vet_erro[PRAZ_ERR] = 0;
	gtk_widget_grab_focus(celular_ter_field);
	return 0;
}
