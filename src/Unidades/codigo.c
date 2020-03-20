int code_und()
{
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	char query[50];
	char code[10];
	codigos_und = malloc(51);
	codigos_und = (gchar*) gtk_entry_get_text(GTK_ENTRY(code_field));
	if(strlen(codigos_und)<1)
	{
		g_print("Inserir um código para o produto");
		popup(NULL,"Por favor, Insira um código para o produto");
		sprintf(code,"%i",tasker("unidades"));
		gtk_entry_set_text(GTK_ENTRY(code_field),code);
		return 1;
		
	}
	sprintf(query,"select code from unidades where code = '%s'",codigos_und);
	if(stoi(codigos_und)==-1)
	{
		if(strlen(codigos_und)>8)
		{
			g_print("O codigo deve ser menor");
			popup(NULL,"O codigo deve ser menor");
			return 1;
		}
		else
		{
			g_print("Codigo da unidade incorreto: %s\n",codigos_prod);
			popup(NULL,"O código da unidade deve ser numérico\n");
			code[0] = '\0';
			sprintf(code,"%i",tasker("unidades"));
			gtk_entry_set_text(GTK_ENTRY(code_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_field),"");
			gtk_entry_set_text(GTK_ENTRY(sigla_field),"");
			gtk_entry_set_text(GTK_ENTRY(mult_field),"");
		}
		return -1;
	}
	else
	if((vetor = consultar(query))!=NULL)
	{
		campos = mysql_fetch_row(vetor);
		if(campos!=NULL)
		{
			popup(NULL,"Este código ja foi incluído\nPor favor tente com o próximo");
			g_print("Código ja foi incluído\n");
			g_print("%s\n",campos[0]);
			codigos_und_err=1;
			return 1;
		}
	}
	codigos_und_err=0;
	g_print("codigo: %s\n",codigos_und);
	gtk_widget_grab_focus(GTK_WIDGET(name_field));
	return 0;
}

