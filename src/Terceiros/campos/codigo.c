int code_terc()
{
	char code[10];
	char task[8];
	char query[MAX_QUERY_LEN];
	codigos_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(code_ter_field));

	if(strlen(codigos_ter)<=0)
	{
		g_print("Codigo terceiro deve ser inserido\n");
		popup(NULL,"Por favor, insira um Código para o terceiro!");
                sprintf(code,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
		gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
		vet_erro[COD_ERR]=1;
		return 1;
	}

	if(stoi(codigos_ter)==-1)
	{
		if(strlen(codigos_ter)>8)
		{
			g_print("Codigo terceiro muito grande %s\n",codigos_ter);
			popup(NULL,"Por favor tente com um código menor\nO código do terceiro está enorme");
			return -1;
		}
		else
		{
			g_print("Codigo do terceiro incorreto %s\n",codigos_ter);
			popup(NULL,"Codigo terceiro deve ser numérico\nCaso não seja necessário, não mude o código padrão");
			code[0] = '\0';
			sprintf(code,"%i",tasker("terceiros"));
			gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
			gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);
			gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
			return 1;
		}
	}

	if(strlen(codigos_ter)<1)
	{
		g_print("Código nao inserido%s\n",codigos_ter);
		popup(NULL,"Por favor é necessário usar o código");
		sprintf(task,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
		return -1;
	}

	sprintf(query,"select code from terceiros where code = '%s'",codigos_ter);
	vetor = consultar(query);
	if(alterando_ter==0)
	{
		if(vetor!=NULL)
		{
			if((campos = mysql_fetch_row(vetor))!=NULL)
			{
				altera_ter();
			}
		}
	}
	gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));


	g_print("codigo: %s\n",codigos_ter);
	return 0;
}
