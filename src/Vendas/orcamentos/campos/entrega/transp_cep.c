

int orc_transp_cepc()
{
	char *query;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	query = malloc(MAX_QUERY_LEN);
	orc_transp_cep = (gchar *) gtk_entry_get_text(GTK_ENTRY(orc_transp_cep_entry));

	if(strlen(orc_transp_cep)<=0)
	{
		if(orc_com_entrega == 0)
		{
			orc_transp_cep = malloc(MAX_CEP_LEN);
			strcpy(orc_transp_cep,"");
			gtk_widget_grab_focus(orc_transp_logradouro_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Por favor insira um cep");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_cep_entry));
		return 1;
	}

	if(strlen(orc_transp_cep)>=MAX_CEP_LEN)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"CEP muito grande\nPor favor verifique");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_cep_entry));
		return 1;
	}

	if(strlen(orc_transp_cep)!=CEP_LEN)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Insira o CEP com formato indicado");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_cep_entry));
		return 1;
	}
	autologger("CEP:");
	autologger(orc_transp_cep);
	sprintf(query,"select l.descricao, c.descricao, l.UF, l.descricao_bairro  from logradouro as l inner join cidade as c on l.id_cidade = c.code where CEP = '%s'",orc_transp_cep);

	if(!(vetor = consultar(query)))
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Erro na query para CEP\n\tConsulte suporte");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_cep_entry));
		return 1;
	}
	if(!(campos = mysql_fetch_row(vetor)))
	{
		if( orc_transp_msg_cep==0 && concluindo_orc == 0 && recebendo_prod_orc == 0){
			const gchar *logradouro = NULL;
			const gchar *bairro = NULL;
			const gchar *cidade = NULL;

			if(strlen(gtk_entry_get_text(GTK_ENTRY(orc_transp_logradouro_entry))))
				logradouro = gtk_entry_get_text(GTK_ENTRY(orc_transp_logradouro_entry));
			if(strlen(gtk_entry_get_text(GTK_ENTRY(orc_transp_bairro_entry))))
				bairro = gtk_entry_get_text(GTK_ENTRY(orc_transp_bairro_entry));
			if(strlen(gtk_entry_get_text(GTK_ENTRY(orc_transp_cidade_entry))))
				cidade = gtk_entry_get_text(GTK_ENTRY(orc_transp_cidade_entry));

			cep_nao_existente_fun(orc_transp_cep, logradouro, bairro, cidade);
		}

		autologger("CEP não encontrado,\n\tpor favor insira o endereço manualmente");
		autologger(orc_transp_cep);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		gtk_widget_grab_focus(orc_transp_logradouro_entry);
		return 0;
	}

	if(campos[0])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),campos[0]);
	if(campos[1])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),campos[1]);
	if(campos[2])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),campos[2]);
	if(campos[3])
		gtk_entry_set_text(GTK_ENTRY(orc_transp_bairro_entry),campos[3]);

	gtk_widget_grab_focus(orc_transp_logradouro_entry);
	return 0;
}
