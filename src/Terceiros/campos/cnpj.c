int cnpj_terc()
{
	int len,cont,cont2=0;
	char formatar[20];
	memset(formatar,0x0,20);
	doc_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(doc_ter_field));
	len = strlen(doc_ter);
	g_print("CNPJ %s\ncom %i digitos\n",doc_ter,len);
	if(len<=0){
		if(terceiros.criticar.doc==0){
			doc_ter = malloc(sizeof(gchar *));
			strcpy(doc_ter,"");
			gtk_widget_grab_focus(GTK_WIDGET(inscr_ter_field));
			return 0;
		}
		g_print("CNPJ terceiro deve ser inserido\n");
		popup(NULL,"Por favor, insira um CNPJ para o terceiro!");
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
		gtk_entry_set_placeholder_text (GTK_ENTRY(doc_ter_field),"00.000.000/0001-XX");
		gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));
		return 1;
	}
	g_print("CNPJ %s\ncom %i digitos\n",doc_ter,len);
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
				formatar[cont2] = doc_ter[cont];
				printf("%s\n",formatar);
				cont2++;
			}
			formatar[cont2] = '\0';
			gtk_entry_set_text(GTK_ENTRY(doc_ter_field),formatar);
	}
	else
	if(len==CNPJ_S_LEN)
	{
		if(doc_ter[2]!='.'||doc_ter[6]!='.'||doc_ter[10]!='/'||doc_ter[15]!='-')
		{
			g_print("CNPJ incorreto\n");
			popup(NULL,"Formato incorreto para CNPJ!");
			gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
			gtk_entry_set_placeholder_text (GTK_ENTRY(doc_ter_field),"00.000.000/0001-XX");
			gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));
			return 1;
		}
		gtk_widget_grab_focus(inscr_ter_field);
	}
	else
	{
		g_print("CNPJ incorreto\n");
		popup(NULL,"Formato incorreto para CNPJ!");
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
		gtk_entry_set_placeholder_text (GTK_ENTRY(doc_ter_field),"00.000.000/0001-XX");
		gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));
		return 1;
	}

	return 0;
}
