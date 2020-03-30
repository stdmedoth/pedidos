int contato_email()
{
	contatoe_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(contatoe_ter_field));
	if((strlen(contatoe_ter)<1)&&(strlen(email_ter)>0)&&(criticar.contatoe!=0))
	{
		popup(NULL,"O nome do contato deve ser inserido");
		g_print("O nome do contato deve ser inserido\n");
		autologger("O nome do contato deve ser inserido");
		vet_erro[CNE_ERR] = 1;
		return 1;
	}
	if(strlen(contatoe_ter)>=MAX_CONT_LEN)
	{
		popup(NULL,"O nome do contato está muito grande");
		g_print("O nome do contato está muito grande");
		autologger("O nome do contato está muito grande");
		vet_erro[CNE_ERR] = 1;
		return 1;
	}
	vet_erro[CNE_ERR] = 0;
	gtk_widget_grab_focus(observacoes_ter_field);
	return 0;	
}
int email_fun()
{
	int i=0,arroba=0,ponto=0;
	email_ter = (char *) gtk_entry_get_text(GTK_ENTRY(email_ter_field));
	if(strlen(email_ter)<=0&&criticar.email!=0)
	{
		popup(NULL,"O email deve ser inserido");
		g_print("O email deve ser inserido\n");
		autologger("O email deve ser inserido");
		vet_erro[EML_ERR] = 1;
		return 1;
	}
	if(strlen(email_ter)>=MAX_EMAIL_LEN)
	{
		popup(NULL,"O email está muito grande");
		g_print("O email está muito grande");
		autologger("O email está muito grande");
		vet_erro[EML_ERR] = 1;
		return 1;
	}
	for(i=0;i<=strlen(email_ter);i++)
	{
		if(email_ter[i]=='@')
		{
			arroba=1;
		}
		if(email_ter[i]=='.')
		{
			ponto=1;
		}
	}
	if((ponto!=1||arroba!=1)&&criticar.email!=0)
	{
		popup(NULL,"Email incorreto, por favor verifique");
		vet_erro[EML_ERR] = 1;
		return 1;
	}
	vet_erro[EML_ERR] = 0;
	gtk_widget_grab_focus(contatoe_ter_field);
	return 0;
}

