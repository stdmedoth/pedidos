int transp_num_fun()
{
	transp_num = malloc(MAX_CODE_LEN);
	transp_num = (gchar*) gtk_entry_get_text(GTK_ENTRY(transp_num_entry));
	if(strlen(transp_num)<=0)
	{
		popup(NULL,"Insira o número da rua");
		gtk_widget_grab_focus(transp_num_entry);
		return 1;
	}
	if(stoi(transp_num)==-1)
	{
		popup(NULL,"Deve ser inserido caracteres numéricos");
		gtk_widget_grab_focus(transp_num_entry);
		return 1;	
	}
	
	gtk_widget_grab_focus(transp_cidade_entry);
	return 0;
}

