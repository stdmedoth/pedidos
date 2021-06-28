int transp_msg_cep=0;
int transp_cepc()
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	transp_cep = (gchar *) gtk_entry_get_text(GTK_ENTRY(transp_cep_entry));

	if(strlen(transp_cep)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			transp_cep = malloc(MAX_CEP_LEN);
			strcpy(transp_cep,"");
			gtk_widget_grab_focus(transp_logradouro_entry);
			return 0;
		}
		popup(NULL,"Por favor insira um cep");
		gtk_widget_grab_focus(GTK_WIDGET(transp_cep_entry));
		return 1;
	}

	if(strlen(transp_cep)!=CEP_LEN)
	{
		popup(NULL,"Insira o CEP com formato indicado");
		gtk_widget_grab_focus(GTK_WIDGET(transp_cep_entry));
		return 1;
	}
	autologger("CEP:");
	autologger(transp_cep);
	sprintf(query,"select l.descricao, c.descricao, l.UF, l.descricao_bairro  from logradouro as l inner join cidade as c on l.id_cidade = c.code where CEP = '%s'",transp_cep);
	if(!(vetor = consultar(query)))
	{
		popup(NULL,"Erro na query para CEP\n\tConsulte suporte");
		gtk_widget_grab_focus(GTK_WIDGET(transp_cep_entry));
		return 1;
	}
	if(!(campos = mysql_fetch_row(vetor)))
	{
		if(transp_msg_cep==0 && alterando_ter==0){
			popup(NULL,"CEP não encontrado,\npor favor insira o endereço manualmente");
			transp_msg_cep = 1;
		}

		autologger("CEP não encontrado,\n\tpor favor insira o endereço manualmente");
		autologger(transp_cep);
		gtk_widget_grab_focus(transp_logradouro_entry);
		return 0;
	}
	g_print("cep_len: %li\n",strlen(transp_cep));
	if( campos[0] && !strlen(gtk_entry_get_text(GTK_ENTRY(transp_logradouro_entry) ) ) )
		gtk_entry_set_text(GTK_ENTRY(transp_logradouro_entry),campos[0]);

	if(campos[1] && !strlen(gtk_entry_get_text(GTK_ENTRY(transp_cidade_entry) ) ))
		gtk_entry_set_text(GTK_ENTRY(transp_cidade_entry),campos[1]);

	if(campos[2] && !strlen(gtk_entry_get_text(GTK_ENTRY(transp_estado_entry) ) ))
		gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),campos[2]);

	if(campos[3] && !strlen(gtk_entry_get_text(GTK_ENTRY(transp_bairro_entry) ) ))
		gtk_entry_set_text(GTK_ENTRY(transp_bairro_entry),campos[3]);

	gtk_widget_grab_focus(transp_logradouro_entry);
	g_print("cep: %s\n",transp_cep);
	return 0;
}
