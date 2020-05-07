int qnt_prod_orc(GtkWidget *widget,int posicao)
{
	int desconto_prod_orc(GtkWidget*,int);
	char query[MAX_QUERY_LEN];
	int tipodesc;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	
	preco_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	total_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	qnt_prod_orc_gchar = malloc(MAX_CODE_LEN);
	desconto_prod_orc_gchar = malloc(MAX_PRECO_LEN);
	
	qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));
	
	if(strlen(qnt_prod_orc_gchar)<=0)
	{
		popup(NULL,"A quantidade deve ser inserida");
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}
	if(critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao])!=0)
	{
		gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
		return 1;
	}
	codigo_cli_orc();
	if(preco_alterado[posicao]==0)
	{
		if(strlen(cliente_orc_gchar)<=0)
		{
			popup(NULL,"Cliente não inserido");
			gtk_widget_grab_focus(cliente_orc_entry);
			return 0;
		}
		if(strlen(codigo_prod_orc_gchar)<=0)
		{
			codigo_prod_orc(codigo_prod_orc_entry[posicao],posicao);
		}
		sprintf(query,"select valor from precos where terceiro = %s and produto = %s",cliente_orc_gchar,codigo_prod_orc_gchar);
		vetor = consultar(query);
		if(vetor==NULL)
		{
			popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
			g_print("Erro na query de produtos no orcamento\n");
			autologger("Erro na query de produtos no orcamento\n");
			autologger(query);
			gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
			return 1;
		}
		campos = mysql_fetch_row(vetor);
		if(campos == NULL)
		{
			codigo_prod_orc(widget,posicao);
			sprintf(query,"select preco_faturado from produtos where code = %s",codigo_prod_orc_gchar);
			vetor = consultar(query);
			if(vetor==NULL)
			{
				popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
				g_print("Erro na query de produtos no orcamento\n");
				autologger("Erro na query de produtos no orcamento\n");
				autologger(query);
				gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
				return 1;
			}
			campos = mysql_fetch_row(vetor);
			if(campos == NULL)
			{
				popup(NULL,"Produto sem preço");
				gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
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
	}
	else
	{
		preco_prod_orc(NULL,posicao);
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
	
	desconto_prod_orc(desconto_prod_orc_entry[posicao],posicao);

	ativos[posicao].qnt_f = atof(qnt_prod_orc_gchar);
	strcpy(ativos[posicao].qnt_c,qnt_prod_orc_gchar);
	critica_real(ativos[posicao].qnt_c,qnt_prod_orc_entry[posicao]);
	g_print("float qnt %.2f\n",ativos[posicao].qnt_f);


	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
	critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);
	g_print("float preco %.2f\n",ativos[posicao].preco_f);

	
	tipodesc = gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[posicao]));
	if(tipodesc==0)
	{
		ativos[posicao].desconto_f = atof(desconto_prod_orc_gchar);
		strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
		critica_real(&(ativos[posicao].desconto_c[0]),desconto_prod_orc_entry[posicao]);
	}
	else
	if(tipodesc==1)
	{
		ativos[posicao].desconto_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))*(atof(desconto_prod_orc_gchar)/100);
		strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
		critica_real(&(ativos[posicao].desconto_c[0]),desconto_prod_orc_entry[posicao]);
	}
	
	g_print("Total: ");
	ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;
	g_print("float: %.2f ",ativos[posicao].total_f);
	
	sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
	g_print("string: %s \n",total_prod_orc_gchar);
	critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
	strcpy(ativos[posicao].total_c,total_prod_orc_gchar);
	critica_real(ativos[posicao].total_c,total_prod_orc_entry[posicao]);
	gerar_total_geral();
	vet_erro[QNT_ERR] = 0;
	
	if(ativos[posicao+1].id == 1)
	{
		if(GTK_IS_WIDGET(codigo_prod_orc_entry[posicao+1]))
			gtk_widget_grab_focus(codigo_prod_orc_entry[posicao+1]);
		else
			gtk_widget_grab_focus(botao_orc_mais);
	}
	else
		gtk_widget_grab_focus(botao_orc_mais);
	
	return 0;
}
