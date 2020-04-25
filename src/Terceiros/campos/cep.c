int msg_cep=0;
int cep_terc()
{
	char *query;
	int cont=0,cont2=0;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	query = malloc(QUERY_LEN);
	cep_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(cep_ter_field));
	if(strlen(cep_ter)>=MAX_CEP_LEN)
	{
		popup(NULL,"CEP muito grande\nPor favor verifique");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		vet_erro[CEP_ERR]=1;
		return 1;
	}
	if(strlen(cep_ter)<=0)
	{
		if(terceiros.criticar.cep==0)
		{
			cep_ter = malloc(MAX_CEP_LEN);
			strcpy(cep_ter,"");
			gtk_widget_grab_focus(address_ter_field);
			return 0;
		}
		popup(NULL,"Por favor insira um cep");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		vet_erro[CEP_ERR]=1;
		return 1;
	}
	if(strlen(cep_ter)!=CEP_LEN)
	{
		popup(NULL,"Insira o CEP com formato indicado");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		return 1;
	}
	g_print("CEP: %s\n",cep_ter);
	autologger("CEP:");
	autologger(cep_ter);
	sprintf(query,"select l.descricao,l.tipo, c.descricao from logradouro as l inner join cidade as c on l.id_cidade = c.id_cidade where CEP = '%s'",cep_ter);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query para CEP\n\tConsulte suporte");
		gtk_widget_grab_focus(GTK_WIDGET(cep_ter_field));
		return 1;
	}
	if((campos = mysql_fetch_row(vetor))==NULL)
	{
		if(msg_cep==0&&alterando_ter==0)
			popup(NULL,"CEP não encontrado,\npor favor insira o endereço manualmente");
		autologger("CEP não encontrado,\n\tpor favor insira o endereço manualmente");
		autologger(cep_ter);
		msg_cep = 1;
		vet_erro[CEP_ERR]=0;
		tipo_log = gtk_combo_box_get_active(GTK_COMBO_BOX(rua_combo));
		gtk_widget_grab_focus(address_ter_field);
		return 0;
	}
	g_print("cep_len: %li\n",strlen(cep_ter));
	gtk_entry_set_text(GTK_ENTRY(address_ter_field),campos[0]);
	for(cont=0;cont<=6;cont++)
	{
		if(strcmp(campos[1],tip_logds[cont])==0)
		{
			gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),cont+1);
			tipo_log = cont+1;
			cont2 = 1;
 		}
	}
	if(cont2==0)
	{
		gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),7);
	}
	gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),campos[2]);
	vet_erro[CEP_ERR]=0;
	gtk_widget_grab_focus(address_ter_field);
	g_print("cep: %s\n",cep_ter);
	return 0;
}

