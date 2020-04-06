int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	qnt_prod_orc_gchar = malloc(MAX_CODE_LEN);
	qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));
	if(strlen(qnt_prod_orc_gchar)<=0)
	{
		popup(NULL,"A quantidade deve ser inserida");
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		vet_erro[COD_ERR] = 1;
		return 1;
	}
	codigo_cli_orc();
	sprintf(query,"select valor from precos where terceiro = %s",cliente_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de produtos no orcamento\n");
		autologger("Erro na query de produtos no orcamento\n");
		autologger(query);
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		vet_erro[COD_ERR] = 1;
		return 1;
	}
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		codigo_prod_orc(widget,posicao);
		sprintf(query,"select preco from produtos where code = %s",codigo_prod_orc_gchar);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
			g_print("Erro na query de produtos no orcamento\n");
			autologger("Erro na query de produtos no orcamento\n");
			autologger(query);
			gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
			vet_erro[COD_ERR] = 1;
			return 1;
		}
		campos = mysql_fetch_row(vetor);
		if(campos == NULL)
		{
			popup(NULL,"Produto sem preço");
			gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
			vet_erro[COD_ERR] = 1;
			return 1;
		}
		gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),campos[0]);
		gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[posicao]),"tabela");
	}
	else
	{
		gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),campos[0]);
		gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[posicao]),"cliente");
		//gtk_entry_set_text(GTK_ENTRY(descricao_prod_orc_entry[posicao]),campos[0]);
		
	}
	total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	sprintf(total_prod_orc_gchar,"%.2f",atof(gtk_entry_get_text(GTK_ENTRY(preco_prod_orc_entry[posicao])))*atof(gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]))));
	gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[posicao]),total_prod_orc_gchar);
	gtk_widget_grab_focus(botao_orc_mais);
	return 0;
}
