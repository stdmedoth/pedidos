#define PSQ_TER_QUERY "select * from terceiros where razao like '%c%s%c';"
GtkWidget *colunasc;


int chama_ter_codigo(GtkWidget *widget,GdkEvent *evento,char *pcodigo)
{
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),pcodigo);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",pcodigo);
	if(altera_ter()==0)
		gtk_widget_destroy(lista_ter);
	return 0;
}

int rec_ter_list(GtkWidget *widget,GdkEvent *event,gpointer lista_scroll_caixav)
{
	int cont=0,pos=0;
	char **vet_codigosc;
	char *row;
	GtkWidget **evento=NULL,**codigoc=NULL,**nomec=NULL,**doc=NULL,
	**tipodoc=NULL,**type=NULL,**address=NULL,
	**cep=NULL,**telefone=NULL,**contatot=NULL,
	**celular=NULL,**contatoc=NULL,**email=NULL,
	**contatoe=NULL,**_obs=NULL;
	GtkWidget ***separadoresvc;
	
	GtkWidget 
	*codigo_ter_list=NULL,  
	*nome_ter_list=NULL,    
	*address_ter_list=NULL, 
	*type_ter_list=NULL,    
	*doc_ter_list=NULL,
	*tipodoc_ter_list=NULL,
	*cep_ter_list=NULL,
	*telefone_ter_list=NULL,
	*contatot_ter_list=NULL,
	*celular_ter_list=NULL,
	*contatoc_ter_list=NULL,
	*email_ter_list=NULL,
	*contatoe_ter_list=NULL,
	*obs_ter_list=NULL;

	GtkWidget          
	*codigo_list_label=NULL,
	*nome_list_label=NULL,  
	*address_list_label=NULL,
	*type_list_label=NULL,   
	*doc_list_label=NULL,
	*tipodoc_list_label=NULL,
	*cep_list_label=NULL,
	*telefone_list_label=NULL,
	*contatot_list_label=NULL,
	*celular_list_label=NULL,
	*contatoc_list_label=NULL,
	*email_list_label=NULL,
	*contatoe_list_label=NULL,
	*obs_list_label=NULL;

	row = malloc(ENTRADA);
	separadoresvc = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*CAMPOS_QNT);
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigoc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nomec = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	doc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	address = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	tipodoc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	type = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	address = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	cep = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	telefone = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	contatot = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	celular = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	contatoc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	email = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	contatoe = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	_obs =  malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	vet_codigosc = malloc(sizeof(char**)*MAX_CODE_LEN*TERC_QNT);

	
	char query[QUERY_LEN];
	gchar *entrada;
	int ascii = 37;
	entrada = malloc(ENTRADA);
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));
	
	if(GTK_IS_WIDGET(colunasc))
		gtk_widget_destroy(colunasc);

	sprintf(query,"select * from terceiros where razao like '%c%s%c';",ascii,entrada,ascii);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		return 0;
	}

	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadoresvc[cont] = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigosc[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigosc[cont],campos[0]);

		strcpy(row,campos[0]);
		codigoc[cont] = gtk_label_new(row);
		separadoresvc[cont][0] = gtk_separator_new(0);
		
		strcpy(row,campos[1]);
		nomec[cont] =  gtk_label_new(row);
		separadoresvc[cont][1] = gtk_separator_new(0);
	
		strcpy(row,campos[2]);
		doc[cont] = gtk_label_new(row);
		separadoresvc[cont][2] = gtk_separator_new(0);
		
		strcpy(row,campos[3]);
		tipodoc[cont] = gtk_label_new(row);
		separadoresvc[cont][3] = gtk_separator_new(0);
		
		strcpy(row,campos[4]);

		switch(atoi(row))
		{	
			case 1:
				g_print("Tipo :%i\n",atoi(campos[4]));
				type[cont] = gtk_label_new("Cliente");
				break;
			case 2:
				g_print("Tipo :%i\n",atoi(campos[4]));
				type[cont] = gtk_label_new("Fornecedor");
				break;
			default:
				type[cont] = gtk_label_new("Fornecedor");
				break;
		}
		separadoresvc[cont][4] = gtk_separator_new(0);
		
		//tipo terceiro int campo[5]
		
		strcpy(row,campos[6]);
		address[cont] = gtk_label_new(row);
		separadoresvc[cont][6] = gtk_separator_new(0);

//		strcpy(row,campos[7]);
		cep[cont] = gtk_label_new("");
		separadoresvc[cont][7] = gtk_separator_new(0);
		
		strcpy(row,campos[8]);
		telefone[cont] = gtk_label_new(row);
		separadoresvc[cont][8] = gtk_separator_new(0);
		
		strcpy(row,campos[9]);
		contatot[cont] = gtk_label_new(row);
		separadoresvc[cont][9] = gtk_separator_new(0);
		
		strcpy(row,campos[10]);
		celular[cont] = gtk_label_new(row);
		separadoresvc[cont][10] = gtk_separator_new(0);
	
		strcpy(row,campos[11]);
		contatoc[cont] = gtk_label_new(row);
		separadoresvc[cont][11] = gtk_separator_new(0);
		
		strcpy(row,campos[12]);
		email[cont] = gtk_label_new(row);
		separadoresvc[cont][12] = gtk_separator_new(0);
		
		strcpy(row,campos[13]);
		contatoe[cont] = gtk_label_new(row);
		separadoresvc[cont][13] = gtk_separator_new(0);
		
		strcpy(row,campos[14]);
		_obs[cont] = gtk_label_new(row);
		separadoresvc[cont][14] = gtk_separator_new(0);
		cont++;
	
	}
	if(cont==0)
		return 0;
	
	colunasc = gtk_box_new(0,0);
	codigo_ter_list = gtk_box_new(1,0);
	nome_ter_list = gtk_box_new(1,0);
	doc_ter_list = gtk_box_new(1,0);
	tipodoc_ter_list = gtk_box_new(1,0);
	type_ter_list = gtk_box_new(1,0);
	address_ter_list = gtk_box_new(1,0);
	cep_ter_list = gtk_box_new(1,0);
	telefone_ter_list = gtk_box_new(1,0);
	contatot_ter_list = gtk_box_new(1,0);
	celular_ter_list = gtk_box_new(1,0);
	contatoc_ter_list = gtk_box_new(1,0);
	email_ter_list = gtk_box_new(1,0);
	contatoe_ter_list = gtk_box_new(1,0);
	obs_ter_list = gtk_box_new(1,0);
	
	codigo_list_label = gtk_label_new("Código do Terceiro\n");	
	nome_list_label = gtk_label_new("Nome do Terceiro\n");
	doc_list_label = gtk_label_new("Documento\n");
	tipodoc_list_label = gtk_label_new("Tipo Documento\n");
	type_list_label = gtk_label_new("Tipo de Terceiro\n");	
	address_list_label = gtk_label_new("Endereço\n");
	cep_list_label = gtk_label_new("CEP\n");
	telefone_list_label = gtk_label_new("Telefone\n");
	contatot_list_label = gtk_label_new("Contato TEL\n");	
	celular_list_label = gtk_label_new("Celular\n");	
	contatoc_list_label = gtk_label_new("Contato CEL\n");	
	email_list_label = gtk_label_new("Email\n");	
	contatoe_list_label = gtk_label_new("Contato Email\n");	
	obs_list_label = gtk_label_new("Observações\n");	

	gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(doc_ter_list),doc_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(tipodoc_ter_list),tipodoc_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(type_ter_list),type_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address_ter_list),address_list_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(cep_ter_list),cep_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(contatot_ter_list),contatot_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular_ter_list),celular_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(contatoc_ter_list),contatoc_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(email_ter_list),email_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(contatoe_ter_list),contatoe_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(obs_ter_list),obs_list_label,0,0,0);

	while(pos<cont)
	{
		
		gtk_container_add(GTK_CONTAINER(evento[pos]),codigoc[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),separadoresvc[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_ter_list),nomec[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_ter_list),separadoresvc[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(doc_ter_list),doc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(doc_ter_list),separadoresvc[pos][2],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(tipodoc_ter_list),tipodoc[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(tipodoc_ter_list),separadoresvc[pos][3],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(type_ter_list),type[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(type_ter_list),separadoresvc[pos][4],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(address_ter_list),address[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(address_ter_list),separadoresvc[pos][6],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(cep_ter_list),cep[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(cep_ter_list),separadoresvc[pos][7],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),separadoresvc[pos][8],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(contatot_ter_list),contatot[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(contatot_ter_list),separadoresvc[pos][9],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(celular_ter_list),celular[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(celular_ter_list),separadoresvc[pos][10],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(contatoc_ter_list),contatoc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(contatoc_ter_list),separadoresvc[pos][11],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(email_ter_list),email[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(email_ter_list),separadoresvc[pos][12],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(contatoe_ter_list),contatoe[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(contatoe_ter_list),separadoresvc[pos][13],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(obs_ter_list),_obs[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(obs_ter_list),separadoresvc[pos][14],0,0,10);
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(chama_ter_codigo),vet_codigosc[pos]);
		pos++;
		
	}
	gtk_widget_set_size_request(codigo_ter_list,70,30);
	gtk_widget_set_size_request(nome_ter_list,70,30);
	gtk_widget_set_size_request(doc_ter_list,70,30);
	gtk_widget_set_size_request(tipodoc_ter_list,75,30);
	gtk_widget_set_size_request(address_ter_list,70,30);
	gtk_widget_set_size_request(type_ter_list,70,30);
	gtk_widget_set_size_request(address_ter_list,70,30);
	gtk_widget_set_size_request(cep_ter_list,70,30);
	gtk_widget_set_size_request(telefone_ter_list,70,30);
	gtk_widget_set_size_request(contatot_ter_list,70,30);
	gtk_widget_set_size_request(celular_ter_list,70,30);
	gtk_widget_set_size_request(contatoc_ter_list,70,30);
	gtk_widget_set_size_request(email_ter_list,70,30);
	gtk_widget_set_size_request(contatoe_ter_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunasc),codigo_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),nome_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),doc_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),tipodoc_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),type_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),address_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),cep_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),telefone_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),contatot_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),celular_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),contatoc_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),email_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),contatoe_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasc),obs_ter_list,0,0,10);
		
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunasc,0,0,20);
	gtk_widget_show_all(colunasc);
	return 0;
}

int pesquisar_terceiros(GtkWidget *botao,gpointer *ponteiro)
{	
	GtkWidget *pesquisa;
	
	GtkWidget *lista_scroll_caixah, *lista_scroll_caixav, 
	*lista_scroll_windowv, *lista_scroll_windowh;

	pesquisa = gtk_search_entry_new();
	
	lista_ter_label = gtk_label_new("Terceiros");
	
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	lista_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_keep_above(GTK_WINDOW(lista_ter), TRUE);
	gtk_window_set_title(GTK_WINDOW(lista_ter),"Lista de Terceiros");
			
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_resizable(GTK_WINDOW(lista_ter),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"LISTAGEM TERCEIROS");
	
	gtk_widget_set_size_request(lista_ter,1000,600);
	abrir_css(DESKTOP_STYLE);

	lista_scroll_windowv = gtk_scrolled_window_new(NULL,NULL);
	lista_scroll_windowh = gtk_scrolled_window_new(NULL,NULL);
	
	gtk_widget_set_size_request(lista_scroll_caixav,1000,600);
	gtk_widget_set_size_request(lista_scroll_windowv,1800,600);
	gtk_widget_set_size_request(lista_scroll_caixah,1000,3000);
	gtk_widget_set_size_request(lista_scroll_windowh,1000,600);
	
	
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(lista_scroll_windowv),lista_scroll_caixav);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(lista_scroll_windowv),lista_scroll_caixav);
	#endif	
	
			
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixah),lista_scroll_windowv,0,0,20);
	
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(lista_scroll_windowh),lista_scroll_caixah);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(lista_scroll_windowh),lista_scroll_caixah);
	#endif	


	gtk_container_add(GTK_CONTAINER(lista_ter),lista_scroll_windowh);
	g_signal_connect(pesquisa,"key-press-event",G_CALLBACK(rec_ter_list),lista_scroll_caixav);
	g_signal_connect(lista_ter,"destroy",G_CALLBACK(close_window_callback),lista_ter);
	gtk_widget_show_all(lista_ter);
	
	return 0;
}
