int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	preco_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
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
		strcpy(preco_prod_orc_gchar,campos[0]);
		critica_real(preco_prod_orc_gchar,preco_prod_orc_entry[posicao]);
		g_print("Inserindo preco no produto pela tabela\n");
		gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[posicao]),"tabela");
	}
	else
	{
		strcpy(preco_prod_orc_gchar,campos[0]);
		critica_real(preco_prod_orc_gchar,preco_prod_orc_entry[posicao]);
		g_print("Inserindo preco no produto pelo vinculo de cliente\n");
		gtk_entry_set_text(GTK_ENTRY(orig_preco_prod_orc_entry[posicao]),"cliente");
		//gtk_entry_set_text(GTK_ENTRY(descricao_prod_orc_entry[posicao]),campos[0]);
	}
	g_print("Iniciando verificação de total\n");
	for(int pos=0;pos<=strlen(preco_prod_orc_gchar);pos++)
	{
		if(preco_prod_orc_gchar[pos]==46||preco_prod_orc_gchar[pos]==44)
		{	
			#ifdef __linux__
			preco_prod_orc_gchar[pos] = 46;
			#endif
			#ifdef WIN32
			preco_prod_orc_gchar[pos] = 44;
			#endif
		}
	}
	for(int pos=0;pos<=strlen(qnt_prod_orc_gchar);pos++)
	{
		if(qnt_prod_orc_gchar[pos]==46||qnt_prod_orc_gchar[pos]==44)
		{	
			#ifdef __linux__
			qnt_prod_orc_gchar[pos] = 46;
			#endif
			#ifdef WIN32
			qnt_prod_orc_gchar[pos] = 44;
			#endif
		}
	}
	sprintf(total_prod_orc_gchar,"%.2f",atof(preco_prod_orc_gchar)*atof(qnt_prod_orc_gchar));
	g_print("%.2f * %i = float - %.2f, string -%s \n",atof(preco_prod_orc_gchar),atoi(qnt_prod_orc_gchar),atof(preco_prod_orc_gchar)*atoi(qnt_prod_orc_gchar),total_prod_orc_gchar);
	critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
	
	gtk_widget_grab_focus(botao_orc_mais);
	return 0;
}
