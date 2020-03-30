int concluido_und()
{
	g_print("Iniciando concluido_und()\n");
	char query[100], code[20];
	if(strlen(codigos_und)<=0||
			strlen(nomes_und)<=0||
			strlen(sigla_und)<=0||
			strlen(mult_und)<=0)
	{
		code[0] = '\0';
		sprintf(code,"%i",tasker("unidades"));
		//gtk_entry_set_text(GTK_ENTRY(code_field),code);
		//gtk_entry_set_text(GTK_ENTRY(name_field),"");
		//gtk_entry_set_text(GTK_ENTRY(price_field),"");
		//gtk_entry_set_text(GTK_ENTRY(supp_field),"");
		gtk_widget_grab_focus(code_field);
		popup(NULL,"Voce deve preencher todos os campos");	
		return 1;
	}
	else
	if(codigos_und_err!=1&&
			nomes_und_err!=1&&
			sigla_und_err!=1&&
			mult_und_err!=1)
	{
		if(stoi(codigos_und)==-1)
		{
			if(strlen(codigos_und)>8)
			{
				g_print("O codigo deve ser menor");
				popup(NULL,"O codigo deve ser menor");
				
			}
			else
			{
				g_print("Codigo do produto incorreto: %s\n",codigos_prod);
				popup(NULL,"O código do produto deve ser numérico\n");
				code[0] = '\0';
				sprintf(code,"%i",tasker("produtos"));
				gtk_entry_set_text(GTK_ENTRY(code_field),code);
				gtk_entry_set_text(GTK_ENTRY(name_field),"");
				gtk_entry_set_text(GTK_ENTRY(price_field),"");
				gtk_entry_set_text(GTK_ENTRY(supp_field),"");
				gtk_entry_set_text(GTK_ENTRY(und_field),"");
			}
			return -1;
		}
		sprintf(query,"insert into unidades(code,name,sigla,multiplo) values('%s','%s','%s',%s);",
				codigos_und,
				nomes_und,
				sigla_und,
				mult_und);
		consultar(query);
		if(mysql_error(&conectar)==0)
		{	
			autologger(query);
			printf("Query envida com sucesso\n");
			gtk_button_set_label(GTK_BUTTON(concluir),"concluido");
			popup(NULL,"Concluido");
			code[0] = '\0';
			sprintf(code,"%i",tasker("unidades"));
			gtk_entry_set_text(GTK_ENTRY(code_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_field),"");
			gtk_entry_set_text(GTK_ENTRY(sigla_field),"");
			gtk_entry_set_text(GTK_ENTRY(mult_field),"");
		//	gtk_widget_grab_focus (GTK_WIDGET(name_field));
		//	gtk_widget_destroy(janela);
		}
		else
		{
			popup(NULL,"O cadastro nao foi feito\nverifique os campos");
			autologger(query);
			printf("Query com erro\n");
			gtk_button_set_label(GTK_BUTTON(concluir),"Tentar novamente");
			code[0] = '\0';
			sprintf(code,"%i",tasker("unidades"));
			gtk_entry_set_text(GTK_ENTRY(code_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_field),"");
			gtk_entry_set_text(GTK_ENTRY(sigla_field),"");
			gtk_entry_set_text(GTK_ENTRY(mult_field),"");
		//	gtk_widget_grab_focus (GTK_WIDGET(name_field));
		//	gtk_widget_destroy(janela);
			return 1;
		}
	}
	return 0;
}

