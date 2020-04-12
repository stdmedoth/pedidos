#define MAX_CEL_LEN 20
#define MAX_TEL_LEN 20
#define MAX_CONT_LEN 20
int mostrar_contatoc()
{
	g_print("mostrando contatoc\n");
	gtk_widget_show(contatoc_label);
	gtk_widget_show(contatoc_ter_field);
	return 0;
}

int mostrar_telefone(GtkWidget *widget,GdkEvent *focar,gpointer telefone)
{
	g_print("mostrando telefone\n");
	gtk_widget_show_all(GTK_WIDGET(telefone));
	return 0;
}
int cel()
{
	celular_ter = (char *) gtk_entry_get_text(GTK_ENTRY(celular_ter_field));
	if(strlen(celular_ter)<=0)
	{
		if(terceiros.criticar.celular==0)
		{
			celular_ter = malloc(MAX_CEL_LEN);
			strcpy(celular_ter,"");
			gtk_widget_grab_focus(contatoc_ter_field);
			return 0;
		}
		popup(NULL,"O numero de celular deve ser inserido");
		g_print("O numero de celular deve ser inserido\n");
		autologger("O numero de celular deve ser inserido");
		vet_erro[CEL_ERR] = 1;
		return 1;
	}
	if(strlen(celular_ter)>=MAX_CEL_LEN)
	{
		popup(NULL,"O numero está muito grande");
		g_print("O numero está muito grande");
		autologger("O numero está muito grande");
		vet_erro[CEL_ERR] = 1;
		return 1;
	}
	vet_erro[CEL_ERR] = 0;
	gtk_widget_grab_focus(contatoc_ter_field);
	return 0;
}
int contc()
{
	contatoc_ter =(char *) gtk_entry_get_text(GTK_ENTRY(contatoc_ter_field));
	if(strlen(contatoc_ter)<=0)
	{
		if(terceiros.criticar.contatoc==0)
		{
			contatoc_ter = malloc(MAX_CONT_LEN);
			strcpy(contatoc_ter,"");
			gtk_widget_grab_focus(telefone_ter_field);
			return 0;
		}
		popup(NULL,"O nome do contato deve ser inserido");
		g_print("O nome do contato deve ser inserido\n");
		autologger("O nome do contato deve ser inserido");
		vet_erro[CNC_ERR] = 1;
		return 1;
	}
	if(strlen(contatoc_ter)>=MAX_CONT_LEN)
	{
		popup(NULL,"O nome do contato está muito grande");
		g_print("O nome do contato está muito grande");
		autologger("O nome do contato está muito grande");
		vet_erro[CNC_ERR] = 1;
		return 1;
	}
	vet_erro[CNC_ERR] = 0;
	gtk_widget_grab_focus(telefone_ter_field);
	return 0;
}

int tel()
{
	telefone_ter =(char *) gtk_entry_get_text(GTK_ENTRY(telefone_ter_field));
	if(strlen(telefone_ter)<=0)
	{
		if(terceiros.criticar.telefone==0)
		{
			telefone_ter = malloc(MAX_TEL_LEN);
			strcpy(telefone_ter,"");
			gtk_widget_grab_focus(contatot_ter_field);
			return 0;
		}
		popup(NULL,"O numero de telefone deve ser inserido");
		g_print("O numero de telefone deve ser inserido\n");
		autologger("O numero de telefone deve ser inserido");
		gtk_widget_grab_focus(telefone_ter_field);
		vet_erro[TEL_ERR] = 1;
		return 1;
	}
	if(strlen(telefone_ter)>=MAX_TEL_LEN)
	{
		popup(NULL,"O numero de telefone está muito grande");
		g_print("O numero de telefone está muito grande\n");
		autologger("O numero de telefone está muito grande");
		gtk_widget_grab_focus(telefone_ter_field);
		vet_erro[TEL_ERR] = 1;
		return 1;
	}
	vet_erro[TEL_ERR] = 0;
	gtk_widget_grab_focus(contatot_ter_field);
	return 0;
}

int contt()
{
	contatot_ter =(char *) gtk_entry_get_text(GTK_ENTRY(contatot_ter_field));
	if(strlen(contatot_ter)<=0)
	{
		if(terceiros.criticar.contatot==0)
		{
			contatot_ter = malloc(MAX_CONT_LEN);
			strcpy(contatot_ter,"");
			gtk_widget_grab_focus(email_ter_field);
			return 0;
		}
		popup(NULL,"O nome do contato deve ser inserido");
		g_print("O nome do contato não foi inserido\n");
		autologger("O nome do contato deve ser inserido");
		vet_erro[CNT_ERR] = 1;
		return 1;
	}
	if(strlen(contatot_ter)>=MAX_CEL_LEN)
	{
		popup(NULL,"O nome do contato está muito grande");
		g_print("O nome do contato está muito grande\n");
		autologger("O nome do contato está muito grande");
		vet_erro[CNT_ERR] = 1;
		return 1;
	}
	vet_erro[CNT_ERR] = 0;
	gtk_widget_grab_focus(email_ter_field);
	return 0;
}
