int cnpj_terc()
{
	int len,cont,cont2=0;
	char formatar[20];
	memset(formatar,0x0,20);	
	cnpj_ter = malloc(20);
	memset(cnpj_ter,0x0,20);	
	cnpj_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(cnpj_ter_field));
	len = strlen(cnpj_ter);
	g_print("CNPJ %s\ncom %i digitos\n",cnpj_ter,len);
	if(len<1)
	{
		g_print("CNPJ terceiro deve ser inserido\n");
		popup(NULL,"Por favor, insira um CNPJ para o terceiro!");
		gtk_entry_set_text(GTK_ENTRY(cnpj_ter_field),"00.000.000/0001-xx");
		gtk_widget_grab_focus(GTK_WIDGET(cnpj_ter_field));
		cnpj_ter_err=1;
		return 1;
	}
	if(len==CNPJ_N_LEN)
	{
			for(cont=0;cont<CNPJ_N_LEN;cont++)
			{
				if(cont==2)
				{
					formatar[cont2]='.';
					cont2++;
				}
				else
				if(cont==5)
				{
					formatar[cont2]='.';
					cont2++;
				}
				else
				if(cont==8)
				{
						formatar[cont2]='/';
						cont2++;
				}
				else
				if(cont==12)
				{
						formatar[cont2]='-';
						cont2++;
				}
				formatar[cont2] = cnpj_ter[cont];
				printf("%s\n",formatar);
				cont2++;	
			}
			formatar[cont2] = '\0';
			gtk_entry_set_text(GTK_ENTRY(cnpj_ter_field),formatar);
	}
	else
	if(len==CNPJ_S_LEN)
	{
		if(cnpj_ter[2]!='.'||cnpj_ter[6]!='.'||cnpj_ter[10]!='/'||cnpj_ter[15]!='-')
		{
			g_print("CNPJ incorreto\n");
			popup(NULL,"Formato incorreto para CNPJ!");
			gtk_entry_set_text(GTK_ENTRY(cnpj_ter_field),"00.000.000/0001-xx");
			gtk_widget_grab_focus(GTK_WIDGET(cnpj_ter_field));
			cnpj_ter_err=1;
			return 1;		
		}
		gtk_widget_grab_focus(name_ter_field);
	}
	else
	{
		g_print("CNPJ incorreto\n");
		popup(NULL,"Formato incorreto para CNPJ!");
		gtk_entry_set_text(GTK_ENTRY(cnpj_ter_field),"00.000.000/0001-xx");
		gtk_widget_grab_focus(GTK_WIDGET(cnpj_ter_field));
		cnpj_ter_err=1;
		return 1;		
	}
	
	return 0;
}
