int cod_grp(){
	grpcode = malloc(MAX_CODE_LEN);
	grpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_grp_entry));
	if(stoi(grpcode)==-1)
	{
		popup(NULL,"O campo deve ser preenchido com um código");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}
	if(strlen(grpcode)>MAX_CODE_LEN)
	{
		popup(NULL,"O código está muito extenso");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}

	if(alterando_grp==0&&concluindo_grp==0)
	{
		altera_grupo();
	}
	return 0;
}
