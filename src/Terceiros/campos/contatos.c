#define MAX_CEL_LEN 15
#define MAX_TEL_LEN 15
#define MAX_CONT_LEN 15
int mostrar_contatoc()
{
	g_print("mostrando contatoc\n");
	gtk_widget_show(contatoc_label);
	gtk_widget_show(contatoc_entry);
	return 0;
}

int mostrar_contatot()
{
	g_print("mostrando contatot\n");
	gtk_widget_show(contatot_label);
	gtk_widget_show(contatot_entry);
	return 0;
}
int cel()
{
	celular_ter = malloc(MAX_CEL_LEN);
	celular_ter = (char *) gtk_entry_get_text(GTK_ENTRY(celular_entry));
	if(strlen(celular_ter)>=MAX_CEL_LEN)
	{
		popup(NULL,"O numero está muito grande");
		g_print("O numero está muito grande");
		autologger("O numero está muito grande");
		return 1;
	}
	gtk_widget_grab_focus(contatoc_entry);
	return 0;
}
int contc()
{
	contatoc_ter = malloc(MAX_CONT_LEN);
	contatoc_ter =(char *) gtk_entry_get_text(GTK_ENTRY(contatoc_entry));
	if(strlen(contatoc_ter)>=MAX_CONT_LEN)
	{
		popup(NULL,"O nome do contato está muito grande");
		g_print("O nome do contato está muito grande");
		autologger("O nome do contato está muito grande");
		return 1;
	}
	gtk_widget_grab_focus(telefone_entry);
	return 0;
}

int tel()
{
	telefone_ter = malloc(MAX_TEL_LEN);
	telefone_ter =(char *) gtk_entry_get_text(GTK_ENTRY(telefone_entry));
	if(strlen(telefone_ter)>=MAX_TEL_LEN)
	{
		popup(NULL,"O numero de telefone está muito grande");
		g_print("O numero de telefone está muito grande");
		autologger("O numero de telefone está muito grande");
		return 1;
	}
	gtk_widget_grab_focus(contatot_entry);
	return 0;
}

int contt()
{
	contatot_ter = malloc(MAX_CONT_LEN);
	contatot_ter =(char *) gtk_entry_get_text(GTK_ENTRY(contatot_entry));
	if(strlen(contatot_ter)>=MAX_CEL_LEN)
	{
		popup(NULL,"O nome do contato está muito grande");
		g_print("O nome do contato está muito grande");
		autologger("O nome do contato está muito grande");
		return 1;
	}
	gtk_widget_grab_focus(concluir);
	return 0;
}
