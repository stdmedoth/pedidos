int orc_transp_num_fun()
{
	orc_transp_num = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_transp_num_entry));
	if(strlen(orc_transp_num)<=0)
	{
		if(orc_com_entrega == 0)
		{
			orc_transp_num = malloc(MAX_CODE_LEN);
			strcpy(orc_transp_num,"");
			gtk_widget_grab_focus(orc_transp_bairro_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Insira o número da rua");
		gtk_widget_grab_focus(orc_transp_num_entry);
		return 1;
	}
	if(stoi(orc_transp_num)==-1)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Deve ser inserido caracteres numéricos");
		gtk_widget_grab_focus(orc_transp_num_entry);
		return 1;
	}

	gtk_widget_grab_focus(orc_transp_bairro_entry);
	return 0;
}
