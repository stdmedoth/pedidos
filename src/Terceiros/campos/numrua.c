int numrua()
{
	address_num = malloc(MAX_CODE_LEN);
	address_num = (gchar*) gtk_entry_get_text(GTK_ENTRY(address_num_field));
	if(strlen(address_num)<=0)
	{
		popup(NULL,"Insira o número da rua");
		gtk_widget_grab_focus(address_num_field);
		return 1;
	}
	if(stoi(address_num)==-1)
	{
		popup(NULL,"Deve ser inserido caracteres numéricos");
		gtk_widget_grab_focus(address_num_field);
		return 1;	
	}
	tipo_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(type_ter_field));
	if((strlen(tipo_ter))<=0)
	{
		gtk_widget_grab_focus(type_ter_field);
	}
	else
	{
		gtk_widget_grab_focus(prazo_ter_field);
	}
	return 0;
}
