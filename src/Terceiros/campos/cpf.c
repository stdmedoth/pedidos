int cpf_terc()
{
	int len,cont,cont2=0;
	char formatar[20];
	memset(formatar,0x0,20);	
	doc_ter = malloc(20);
	memset(doc_ter,0x0,20);	
	doc_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(doc_ter_field));
	len = strlen(doc_ter);
	g_print("CPF %s\ncom %i digitos\n",doc_ter,len);
	if(len<=0)
	{
		if(criticar.doc==0)
		{
			gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));
			return 0;
		}
		g_print("CPF terceiro deve ser inserido\n");
		popup(NULL,"Por favor, insira um CPF para o terceiro!");
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
		gtk_entry_set_placeholder_text(GTK_ENTRY(doc_ter_field),"123.456.789-09");
		gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));
		vet_erro[DOC_ERR]=1;
		return 1;
	}
	if(len==CPF_N_LEN)
	{
			for(cont=0;cont<CPF_N_LEN;cont++)
			{
				if(cont==3)
				{
					formatar[cont2]='.';
					cont2++;
				}
				else
				if(cont==6)
				{
					formatar[cont2]='.';
					cont2++;
				}
				else
				if(cont==9)
				{
						formatar[cont2]='-';
						cont2++;
				}
				formatar[cont2] = doc_ter[cont];
				printf("%s\n",formatar);
				cont2++;	
			}
			formatar[cont2] = '\0';
			vet_erro[DOC_ERR] = 0;
			gtk_entry_set_text(GTK_ENTRY(doc_ter_field),formatar);
	}
	else
	if(len==CPF_S_LEN)
	{
		if(doc_ter[3]!='.'||doc_ter[7]!='.'||doc_ter[11]!='-')
		{
			g_print("CPF incorreto\n");
			popup(NULL,"Formato incorreto para CPF!");
			gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
			gtk_entry_set_placeholder_text(GTK_ENTRY(doc_ter_field),"123.456.789-09");
			gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));
			vet_erro[DOC_ERR]=1;
			return 1;		
		}
		vet_erro[DOC_ERR] = 0;
		gtk_widget_grab_focus(name_ter_field);
	}
	else
	{
		g_print("CPF incorreto\n");
		popup(NULL,"Formato incorreto para CPF!");
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
		gtk_entry_set_placeholder_text(GTK_ENTRY(doc_ter_field),"123.456.789-09");
		gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));
		vet_erro[DOC_ERR]=1;
		return 1;		
	}
	
	return 0;
}

