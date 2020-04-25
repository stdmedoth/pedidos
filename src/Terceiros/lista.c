#define PSQ_TER_QUERY "select * from terceiros where razao like '%c%s%c' or cidade like '%c%s%c';"
GtkWidget *lista_ter,*caixona,*colunasc;
GtkWidget *pesquisa;

int chama_ter_codigo(GtkWidget *widget,GdkEvent *evento,char *pcodigo)
{
	if(pcodigo==NULL)
		return 1;
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),pcodigo);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",pcodigo);
	if(altera_ter()==0)
	{
		gtk_widget_destroy(lista_ter);	
	}
	return 0;
}

GtkWidget *lista_scroll_caixah,*lista_scroll_caixav;
GtkWidget *lista_scroll_windowh;

int rec_ter_list()
{
	int cont=0,pos=0;
	char **vet_codigosc;
	char *row;
	GtkWidget ***separadoresvc;
	MYSQL_RES *mysql_res;
	MYSQL_ROW mysql_row;
	GtkWidget **evento;
	GtkWidget **codigoc,**nomec,**doc,
	**cidade,**uf,
	**tipodoc,**type,**address,
	**cep,**telefone,**contatot,
	**celular,**contatoc,**email,
	**contatoe,**prazo,**_obs;	

	GtkWidget 
	*codigo_ter_list,  
	*nome_ter_list,    
	*address_ter_list, 
	*cidade_ter_list, 
	*uf_ter_list, 
	*type_ter_list,    
	*doc_ter_list,
	*tipodoc_ter_list,
	*cep_ter_list,
	*telefone_ter_list,
	*contatot_ter_list,
	*celular_ter_list,
	*contatoc_ter_list,
	*email_ter_list,
	*contatoe_ter_list,
	*prazo_ter_list,
	*obs_ter_list;

	GtkWidget          
	*codigo_list_label,
	*nome_list_label,  
	*address_list_label,
	*cidade_list_label,
	*uf_list_label,
	*type_list_label,   
	*doc_list_label,
	*tipodoc_list_label,
	*cep_list_label,
	*telefone_list_label,
	*contatot_list_label,
	*celular_list_label,
	*contatoc_list_label,
	*email_list_label,
	*contatoe_list_label,
	*prazo_list_label,
	*obs_list_label;
	
	GList *children,*iter;
	char *query;
	int ascii = 37;	
	
	printf("Retirando filhos da colunasc\n");
	if(GTK_IS_WIDGET(colunasc))
	{
		children = gtk_container_get_children(GTK_CONTAINER(colunasc));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
			gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
	}
	
	if(GTK_IS_WIDGET(lista_scroll_caixav))
	{
		children = gtk_container_get_children(GTK_CONTAINER(lista_scroll_caixav));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
	}
	if(GTK_IS_WIDGET(lista_scroll_caixah))
	{
		children = gtk_container_get_children(GTK_CONTAINER(lista_scroll_caixah));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
	}
	if(GTK_IS_WIDGET(lista_scroll_windowh))
	{
		children = gtk_container_get_children(GTK_CONTAINER(lista_scroll_windowh));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
			gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
		gtk_widget_destroy(GTK_WIDGET(lista_scroll_windowh));
	}

	colunasc = gtk_box_new(0,0);
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	lista_scroll_windowh = gtk_scrolled_window_new(NULL,NULL);	
	

	gtk_widget_set_size_request(lista_scroll_caixav,1000,3000);
	gtk_widget_set_size_request(lista_scroll_caixah,1000,3000);
	gtk_widget_set_size_request(lista_scroll_windowh,1000,500);
	
	row = malloc(ENTRADA);
	evento = malloc(sizeof(GtkEventBox*)*TERC_QNT);
	codigoc = malloc(sizeof(GtkLabel*)*TERC_QNT);
	nomec = malloc(sizeof(GtkLabel*)*TERC_QNT);
	doc = malloc(sizeof(GtkLabel*)*TERC_QNT);
	address = malloc(sizeof(GtkLabel*)*TERC_QNT);
	tipodoc = malloc(sizeof(GtkLabel*)*TERC_QNT);
	type = malloc(sizeof(GtkLabel*)*TERC_QNT);
	address = malloc(sizeof(GtkLabel*)*TERC_QNT);
	cidade = malloc(sizeof(GtkLabel*)*TERC_QNT);
	uf = malloc(sizeof(GtkLabel*)*TERC_QNT);
	cep = malloc(sizeof(GtkLabel*)*TERC_QNT);
	telefone = malloc(sizeof(GtkLabel*)*TERC_QNT);
	contatot = malloc(sizeof(GtkLabel*)*TERC_QNT);
	celular = malloc(sizeof(GtkLabel*)*TERC_QNT);
	contatoc = malloc(sizeof(GtkLabel*)*TERC_QNT);
	email = malloc(sizeof(GtkLabel*)*TERC_QNT);
	contatoe = malloc(sizeof(GtkLabel*)*TERC_QNT);
	prazo = malloc(sizeof(GtkLabel*)*TERC_QNT);
	_obs =  malloc(sizeof(GtkLabel*)*TERC_QNT);
	vet_codigosc = malloc(sizeof(char**)*MAX_CODE_LEN*TERC_QNT);	
	separadoresvc = malloc(sizeof(GtkSeparator*)*TERC_QNT*ROWS_QNT);
	
	query = malloc(QUERY_LEN);
	gchar *entrada;
	entrada = malloc(ENTRADA);
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(pesquisa));
	if(strlen(entrada)<2)
		return 0;
	sprintf(query,PSQ_TER_QUERY,ascii,entrada,ascii,ascii,entrada,ascii);
	mysql_res = consultar(query);
	if(mysql_res==NULL)
	{
		return 0;
	}
	

	while((mysql_row = mysql_fetch_row(mysql_res))!=NULL)
	{
		separadoresvc[cont] = malloc(sizeof(GtkSeparator*)*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigosc[cont] = malloc(MAX_CODE_LEN);	
		strcpy(vet_codigosc[cont],mysql_row[COD_TER_COL]);
		//codigo
		if(mysql_row[COD_TER_COL]!=NULL)
			strcpy(row,mysql_row[COD_TER_COL]);
		else
			strcpy(row,"vazio");
		codigoc[cont] = gtk_label_new(row);
		separadoresvc[cont][COD_TER_COL] = gtk_separator_new(0);
		
		//razao/nome
		if(mysql_row[1]!=NULL)
			strcpy(row,mysql_row[RAZ_TER_COL]);
		else
			strcpy(row,"vazio");
		nomec[cont] =  gtk_label_new(row);
		separadoresvc[cont][RAZ_TER_COL] = gtk_separator_new(0);
		
		//numero documento
		if(mysql_row[DOC_TER_COL]!=NULL)
			strcpy(row,mysql_row[DOC_TER_COL]);
		else
			strcpy(row,"vazio");
		doc[cont] = gtk_label_new(row);
		separadoresvc[cont][DOC_TER_COL] = gtk_separator_new(0);
		
		//tipo documento
		if(mysql_row[TDOC_TER_COL]!=NULL)
			strcpy(row,mysql_row[TDOC_TER_COL]);
		else
			strcpy(row,"vazio");
		
		if(atoi(row)==1)	
		{		
			tipodoc[cont] = gtk_label_new("CNPJ");
		}
		else
		if(atoi(row)==2)	
		{
			tipodoc[cont] = gtk_label_new("CPF");
		}
		else
		if(atoi(row)==3)	
		{
			tipodoc[cont] = gtk_label_new("SEM DOC");
		}
		separadoresvc[cont][TDOC_TER_COL] = gtk_separator_new(0);
	
	
		//tipo terceiro
		if(mysql_row[TIPI_TER_COL]!=NULL)
			strcpy(row,mysql_row[TIPI_TER_COL]);
		else
			strcpy(row,"0");
			
		if(atoi(row)==0)
		{	
			type[cont] = gtk_label_new("Não Inserido");
		}
		else
		if(atoi(row)==1)
		{	
			type[cont] = gtk_label_new("Cliente");
		}
		else
		if(atoi(row)==2)		
		{
			type[cont] = gtk_label_new("Fornecedor");
		}
		else
		if(atoi(row)==3)		
		{
			type[cont] = gtk_label_new("Cliente/Fornecedor");
		}
		separadoresvc[cont][TIPI_TER_COL] = gtk_separator_new(0);
		
		//cep
		if(mysql_row[CEP_TER_COL]!=NULL)
			strcpy(row,mysql_row[CEP_TER_COL]);
		else
			strcpy(row,"vazio");
		cep[cont] = gtk_label_new(row);
		separadoresvc[cont][CEP_TER_COL] = gtk_separator_new(0);
		
		
		//endereco
		if(mysql_row[END_TER_COL]!=NULL)
			strcpy(row,mysql_row[END_TER_COL]);
		else
			strcpy(row,"vazio");
		address[cont] = gtk_label_new(row);
		separadoresvc[cont][END_TER_COL] = gtk_separator_new(0);


		//cidade
		if(mysql_row[CID_TER_COL]!=NULL)
			strcpy(row,mysql_row[CID_TER_COL]);
		else
			strcpy(row,"vazio");
		
		cidade[cont] = gtk_label_new(row);
		separadoresvc[cont][CID_TER_COL] = gtk_separator_new(0);


		//UF
		if(mysql_row[UF_TER_COL]!=NULL)
			strcpy(row,mysql_row[UF_TER_COL]);
		else
			strcpy(row,"vazio");
		
		uf[cont] = gtk_label_new(row);
		separadoresvc[cont][UF_TER_COL] = gtk_separator_new(0);
				
		//telefone
		if(mysql_row[TEL_TER_COL]!=NULL)
			strcpy(row,mysql_row[TEL_TER_COL]);
		else
			strcpy(row,"vazio");
		telefone[cont] = gtk_label_new(row);
		separadoresvc[cont][TEL_TER_COL] = gtk_separator_new(0);
		
		
		//contato telefone
		if(mysql_row[CTEL_TER_COL]!=NULL)
			strcpy(row,mysql_row[CTEL_TER_COL]);
		else
			strcpy(row,"vazio");
		contatot[cont] = gtk_label_new(row);
		separadoresvc[cont][CTEL_TER_COL] = gtk_separator_new(0);
		
		//celular
		if(mysql_row[CEL_TER_COL]!=NULL)
			strcpy(row,mysql_row[CEL_TER_COL]);
		else
			strcpy(row,"vazio");
		celular[cont] = gtk_label_new(row);
		separadoresvc[cont][CEL_TER_COL] = gtk_separator_new(0);
	
		//contato celular
		if(mysql_row[CCEL_TER_COL]!=NULL)
			strcpy(row,mysql_row[CCEL_TER_COL]);
		else
			strcpy(row,"vazio");
		contatoc[cont] = gtk_label_new(row);
		separadoresvc[cont][CCEL_TER_COL] = gtk_separator_new(0);
		
		//email
		if(mysql_row[EMAIl_TER_COL]!=NULL)	
			strcpy(row,mysql_row[EMAIl_TER_COL]);
		else
			strcpy(row,"vazio");
		email[cont] = gtk_label_new(row);
		separadoresvc[cont][EMAIl_TER_COL] = gtk_separator_new(0);
		
		//contato email
		if(mysql_row[CEMAIL_TER_COL]!=NULL)	
			strcpy(row,mysql_row[CEMAIL_TER_COL]);
		else
			strcpy(row,"vazio");
		contatoe[cont] = gtk_label_new(row);
		separadoresvc[cont][CEMAIL_TER_COL] = gtk_separator_new(0);
		
		//prazo
		if(mysql_row[PRAZ_TER_COL]!=NULL)	
			strcpy(row,mysql_row[PRAZ_TER_COL]);
		else
			strcpy(row,"vazio");
		prazo[cont] = gtk_label_new(row);
		separadoresvc[cont][PRAZ_TER_COL] = gtk_separator_new(0);
		
		//observacoes
		if(mysql_row[OBS_TER_COL]!=NULL)
			strcpy(row,mysql_row[OBS_TER_COL]);
		else
			strcpy(row,"vazio");
		_obs[cont] = gtk_label_new(row);
		separadoresvc[cont][OBS_TER_COL] = gtk_separator_new(0);
		printf("cont :%i\n",cont);
		cont++;
	}

	
	codigo_ter_list = gtk_box_new(1,0);
	nome_ter_list = gtk_box_new(1,0);
	doc_ter_list = gtk_box_new(1,0);
	tipodoc_ter_list = gtk_box_new(1,0);
	type_ter_list = gtk_box_new(1,0);
	address_ter_list = gtk_box_new(1,0);
	cidade_ter_list = gtk_box_new(1,0);
	uf_ter_list = gtk_box_new(1,0);
	cep_ter_list = gtk_box_new(1,0);
	telefone_ter_list = gtk_box_new(1,0);
	contatot_ter_list = gtk_box_new(1,0);
	celular_ter_list = gtk_box_new(1,0);
	contatoc_ter_list = gtk_box_new(1,0);
	email_ter_list = gtk_box_new(1,0);
	contatoe_ter_list = gtk_box_new(1,0);
	prazo_ter_list = gtk_box_new(1,0);
	obs_ter_list = gtk_box_new(1,0);
	
	codigo_list_label = gtk_label_new("Código do Terceiro\n");	
	gtk_widget_set_name(GTK_WIDGET(codigo_list_label),"colunas");
	
	nome_list_label = gtk_label_new("Nome do Terceiro\n");
	gtk_widget_set_name(GTK_WIDGET(nome_list_label),"colunas");
	
	doc_list_label = gtk_label_new("Documento\n");
	gtk_widget_set_name(GTK_WIDGET(doc_list_label),"colunas");
	
	tipodoc_list_label = gtk_label_new("Tipo Documento\n");
	gtk_widget_set_name(GTK_WIDGET(tipodoc_list_label),"colunas");
	
	type_list_label = gtk_label_new("Tipo de Terceiro\n");	
	gtk_widget_set_name(GTK_WIDGET(type_list_label),"colunas");
	
	address_list_label = gtk_label_new("Endereço\n");
	gtk_widget_set_name(GTK_WIDGET(address_list_label),"colunas");
	
	cidade_list_label = gtk_label_new("Cidade\n");
	gtk_widget_set_name(GTK_WIDGET(cidade_list_label),"colunas");
	
	uf_list_label = gtk_label_new("UF\n");
	gtk_widget_set_name(GTK_WIDGET(uf_list_label),"colunas");
	
	cep_list_label = gtk_label_new("CEP\n");
	gtk_widget_set_name(GTK_WIDGET(cep_list_label),"colunas");
	
	telefone_list_label = gtk_label_new("Telefone\n");
	gtk_widget_set_name(GTK_WIDGET(telefone_list_label),"colunas");
	
	contatot_list_label = gtk_label_new("Contato TEL\n");	
	gtk_widget_set_name(GTK_WIDGET(contatot_list_label),"colunas");
	
	celular_list_label = gtk_label_new("Celular\n");	
	gtk_widget_set_name(GTK_WIDGET(celular_list_label),"colunas");
	
	contatoc_list_label = gtk_label_new("Contato CEL\n");	
	gtk_widget_set_name(GTK_WIDGET(contatoc_list_label),"colunas");
	
	email_list_label = gtk_label_new("Email\n");	
	gtk_widget_set_name(GTK_WIDGET(email_list_label),"colunas");
	
	contatoe_list_label = gtk_label_new("Contato Email\n");	
	gtk_widget_set_name(GTK_WIDGET(contatoe_list_label),"colunas");
	
	prazo_list_label = gtk_label_new("Prazo\n");
	gtk_widget_set_name(GTK_WIDGET(prazo_list_label),"colunas");
	
	obs_list_label = gtk_label_new("Observações\n");	
	gtk_widget_set_name(GTK_WIDGET(obs_list_label),"colunas");

	gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(doc_ter_list),doc_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(tipodoc_ter_list),tipodoc_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(type_ter_list),type_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address_ter_list),address_list_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(cidade_ter_list),cidade_list_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(uf_ter_list),uf_list_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(cep_ter_list),cep_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(contatot_ter_list),contatot_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular_ter_list),celular_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(contatoc_ter_list),contatoc_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(email_ter_list),email_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(contatoe_ter_list),contatoe_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(prazo_ter_list),prazo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(obs_ter_list),obs_list_label,0,0,0);
	
	while(pos<cont)
	{
		gtk_container_add(GTK_CONTAINER(evento[pos]),codigoc[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),separadoresvc[pos][COD_TER_COL],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_ter_list),nomec[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_ter_list),separadoresvc[pos][RAZ_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(doc_ter_list),doc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(doc_ter_list),separadoresvc[pos][DOC_TER_COL],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(tipodoc_ter_list),tipodoc[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(tipodoc_ter_list),separadoresvc[pos][TDOC_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(type_ter_list),type[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(type_ter_list),separadoresvc[pos][TIPI_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(cep_ter_list),cep[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(cep_ter_list),separadoresvc[pos][CEP_TER_COL],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(address_ter_list),address[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(address_ter_list),separadoresvc[pos][END_TER_COL],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(cidade_ter_list),cidade[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(cidade_ter_list),separadoresvc[pos][CID_TER_COL],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(uf_ter_list),uf[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(uf_ter_list),separadoresvc[pos][UF_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),separadoresvc[pos][TEL_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(contatot_ter_list),contatot[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(contatot_ter_list),separadoresvc[pos][CTEL_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(celular_ter_list),celular[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(celular_ter_list),separadoresvc[pos][CEL_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(contatoc_ter_list),contatoc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(contatoc_ter_list),separadoresvc[pos][CCEL_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(email_ter_list),email[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(email_ter_list),separadoresvc[pos][EMAIl_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(contatoe_ter_list),contatoe[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(contatoe_ter_list),separadoresvc[pos][CEMAIL_TER_COL],0,0,10);

		gtk_box_pack_start(GTK_BOX(prazo_ter_list),prazo[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(prazo_ter_list),separadoresvc[pos][PRAZ_TER_COL],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(obs_ter_list),_obs[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(obs_ter_list),separadoresvc[pos][OBS_TER_COL],0,0,10);
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(chama_ter_codigo),(void*)vet_codigosc[pos]);
		printf("pos %i\n",pos);
		pos++;
		
	}
	
	gtk_widget_set_size_request(codigo_ter_list,70,30);
	gtk_widget_set_size_request(nome_ter_list,70,30);
	gtk_widget_set_size_request(doc_ter_list,70,30);
	gtk_widget_set_size_request(tipodoc_ter_list,75,30);
	gtk_widget_set_size_request(address_ter_list,70,30);
	gtk_widget_set_size_request(type_ter_list,70,30);
	gtk_widget_set_size_request(address_ter_list,70,30);
	gtk_widget_set_size_request(cidade_ter_list,70,30);
	gtk_widget_set_size_request(uf_ter_list,70,30);
	gtk_widget_set_size_request(cep_ter_list,70,30);
	gtk_widget_set_size_request(telefone_ter_list,70,30);
	gtk_widget_set_size_request(contatot_ter_list,70,30);
	gtk_widget_set_size_request(celular_ter_list,70,30);
	gtk_widget_set_size_request(contatoc_ter_list,70,30);
	gtk_widget_set_size_request(email_ter_list,70,30);
	gtk_widget_set_size_request(contatoe_ter_list,70,30);
	gtk_widget_set_size_request(prazo_ter_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunasc),codigo_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),nome_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),doc_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),tipodoc_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),type_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),cep_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),address_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),cidade_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),uf_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),telefone_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),contatot_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),celular_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),contatoc_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),email_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),contatoe_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),prazo_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),obs_ter_list,0,0,10);
	
	gtk_box_pack_end(GTK_BOX(lista_scroll_caixah),colunasc,0,0,0);	
	
	g_print("Inserindo as colunas na scroll_box\n");
	
	gtk_box_pack_end(GTK_BOX(lista_scroll_caixav),lista_scroll_caixah,0,0,0);

	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(lista_scroll_windowh),lista_scroll_caixav);
	#endif

	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(lista_scroll_windowh),lista_scroll_caixav);
	#endif	

	gtk_box_pack_end(GTK_BOX(caixona),lista_scroll_windowh,0,0,20);

	gtk_widget_show_all(caixona);
	return 0;
}
int pesquisar_terceiros(GtkWidget *botao,gpointer *ponteiro)
{	
	lista_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_keep_above(GTK_WINDOW(lista_ter), TRUE);
	gtk_window_set_title(GTK_WINDOW(lista_ter),"Lista de Terceiros");
			
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_resizable(GTK_WINDOW(lista_ter),FALSE);
	gtk_window_set_title(GTK_WINDOW(lista_ter),"LISTAGEM TERCEIROS");
	
	gtk_widget_set_size_request(lista_ter,1000,600);
	
	pesquisa = gtk_search_entry_new();
	caixona = gtk_box_new(1,0);
	colunasc = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(caixona),pesquisa,0,0,20);		
	gtk_container_add(GTK_CONTAINER(lista_ter),caixona);
	
	g_signal_connect(pesquisa,"activate",G_CALLBACK(rec_ter_list),NULL);	
	g_signal_connect(lista_ter,"destroy",G_CALLBACK(close_window_callback),lista_ter);
	gtk_widget_show_all(lista_ter);
	return 0;
}


