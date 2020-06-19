int concluido_und()
{
	MYSQL_RES *res;
	MYSQL_ROW campo;
	g_print("Iniciando concluido_und()\n");
	char query[MAX_QUERY_LEN], code[MAX_CODE_LEN];
	char task[MAX_CODE_LEN];
	concluindo_und=1;
	sprintf(task,"%i",tasker("unidades"));
	if(code_und()!=0)
	{
		gtk_widget_grab_focus(code_und_field);
		return 1;
	}
	if(name_und()!=0)
	{
		gtk_widget_grab_focus(name_und_field);
		return 1;
	}
	if(sig_und()!=0)
	{
		gtk_widget_grab_focus(sigla_und_field);
		return 1;
	}
	if(multiplo_und()!=0)
	{
		gtk_widget_grab_focus(mult_und_field);
		return 1;
	}
	if(medida_und()!=0)
	{
		gtk_widget_grab_focus(medida_und_combo_box);
		return 1;
	}
	if(alterando_und==0)
	{
		sprintf(query,"select code from unidades where code = '%s'",codigos_und);
		autologger(query);
		res = consultar(query);
		campo = mysql_fetch_row(res);
		if(campo!=NULL)
		{
			popup(NULL,"Unidade já existente");
			gtk_entry_set_text(GTK_ENTRY(code_und_field),task);
			gtk_entry_set_text(GTK_ENTRY(name_und_field),"");
			gtk_entry_set_text(GTK_ENTRY(sigla_und_field),"");
			gtk_entry_set_text(GTK_ENTRY(mult_und_field),"");
			return 1;
		}
		sprintf(query,"insert into unidades(code,nome,sigla,multiplo,medida) values('%s','%s','%s',%s,%i);",
				codigos_und,
				nomes_und,
				sigla_und,
				mult_und,
				medidas_und);
	}
	else
	{
		sprintf(query,"update unidades set nome = '%s', sigla = '%s', multiplo = %s, medida = %i where code = %s",
				nomes_und,
				sigla_und,
				mult_und,
				medidas_und,
				codigos_und);
	}

	if(enviar_query(query)==0)
	{
		autologger(query);
		printf("Query envida com sucesso\n");
		popup(NULL,"Concluido");
		code[0] = '\0';
		sprintf(code,"%i",tasker("unidades"));
		gtk_entry_set_text(GTK_ENTRY(code_und_field),code);
		gtk_entry_set_text(GTK_ENTRY(name_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(sigla_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(mult_und_field),"");
	//	gtk_widget_grab_focus (GTK_WIDGET(name_und_field));
	//	gtk_widget_destroy(janela);
	}
	else
	{
		popup(NULL,"O cadastro nao foi feito\nverifique os campos");
		autologger(query);
		printf("Query com erro\n");
		code[0] = '\0';
		sprintf(code,"%i",tasker("unidades"));
		gtk_entry_set_text(GTK_ENTRY(code_und_field),code);
		gtk_entry_set_text(GTK_ENTRY(name_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(sigla_und_field),"");
		gtk_entry_set_text(GTK_ENTRY(mult_und_field),"");
	//	gtk_widget_grab_focus (GTK_WIDGET(name_und_field));
	//	gtk_widget_destroy(janela);
		return 1;
	}
	alterando_und=0;
	concluindo_und=0;
	return 0;
}
