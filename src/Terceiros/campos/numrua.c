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
	char *num = malloc(strlen(address_num));
	sprintf(num,"%i",atoi(address_num));
	gtk_entry_set_text(GTK_ENTRY(address_num_field),num);

	gtk_widget_grab_focus(bairro_ter_field);
	return 0;
}
