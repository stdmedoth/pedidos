#undef PSQ_TER_QUERY
#define PSQ_TER_QUERY "select * from produtos where razao like '%c%s%c';"
GtkWidget **separadoresvp[30];
GtkWidget *lista_prod;	

int chama_prod_codigo(GtkWidget *widget,GdkEvent *evento,char *pcodigo)
{
	gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),pcodigo);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",pcodigo);
	if(altera_prod()==0)
		gtk_widget_destroy(lista_prod);
	return 0;
}
GtkWidget *colunasp;
int rec_prod_list(GtkWidget *widget,GdkEvent *event,gpointer lista_scroll_caixav)
{
	int cont=0;
	int pos=0;




	GtkWidget **evento, **codigop, **nomep, **preco,**peso,**unidade,
	**fornecedor, **grupo,**marca, **observacoes;
	
	char **vet_codigosp;
	
	GtkWidget          
	*codigo_prod_list_label,
	*nome_prod_list_label,
	*preco_list_label,
	*peso_list_label,
	*unidade_list_label,
	*fornecedor_list_label,
	*grupo_list_label,
	*marca_list_label,
	*observacoes_list_label;

	GtkWidget 
	*codigo_prod_list,
	*nome_prod_list,
	*preco_prod_list,
	*peso_prod_list,
	*unidade_prod_list,
	*fornecedor_prod_list,
	*grupo_prod_list,
	*marca_prod_list,
	*observacoes_prod_list;

	
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigop = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nomep = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	preco = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	peso = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	unidade = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	fornecedor = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	grupo = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	marca = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	observacoes = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	vet_codigosp = malloc(sizeof(char**)*MAX_CODE_LEN*MAX_PROD);
	
	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));

	if(GTK_IS_WIDGET(colunasp))
		gtk_widget_destroy(colunasp);
	
	colunasp = gtk_box_new(0,0);	

	sprintf(query,"select * from produtos where nome like '%c%s%c';",ascii,entrada,ascii);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Nada encontrado %s na pesquisa\n",entrada);
		return 0;
	}
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadoresvp[cont] = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigosp[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigosp[cont],campos[0]);

		codigop[cont] = gtk_label_new(campos[0]);
		separadoresvp[cont][0] = gtk_separator_new(0);
		
		nomep[cont] =  gtk_label_new(campos[1]);
		separadoresvp[cont][1] = gtk_separator_new(0);
		
		preco[cont] = gtk_label_new(campos[2]);
		separadoresvp[cont][2] = gtk_separator_new(0);
		
		peso[cont] = gtk_label_new(campos[3]);
		separadoresvp[cont][3] = gtk_separator_new(0);
		
		unidade[cont] = gtk_label_new(campos[4]);
		separadoresvp[cont][4] = gtk_separator_new(0);
		
		fornecedor[cont] = gtk_label_new(campos[5]);
		separadoresvp[cont][5] = gtk_separator_new(0);

		grupo[cont] = gtk_label_new(campos[6]);
		separadoresvp[cont][6] = gtk_separator_new(0);
		
		marca[cont] = gtk_label_new(campos[7]);
		separadoresvp[cont][7] = gtk_separator_new(0);
		
		observacoes[cont] = gtk_label_new(campos[8]);
		separadoresvp[cont][8] = gtk_separator_new(0);
		
		cont++;
	}
	if(cont==0)
		return 0;
	
	
	codigo_prod_list = gtk_box_new(1,0);
	nome_prod_list = gtk_box_new(1,0);
	preco_prod_list = gtk_box_new(1,0);
	peso_prod_list = gtk_box_new(1,0);
	unidade_prod_list = gtk_box_new(1,0);
	fornecedor_prod_list = gtk_box_new(1,0);
	grupo_prod_list = gtk_box_new(1,0);
	marca_prod_list = gtk_box_new(1,0);
	observacoes_prod_list = gtk_box_new(1,0);
	
	codigo_prod_list_label = gtk_label_new("Código do produto\n");	
	nome_prod_list_label = gtk_label_new("Nome do produto\n");
	preco_list_label = gtk_label_new("Preço\n");
	peso_list_label = gtk_label_new("Peso\n");
	unidade_list_label = gtk_label_new("Modelo Unidade\n");	
	fornecedor_list_label = gtk_label_new("Fornecedor\n");
	grupo_list_label = gtk_label_new("Grupo\n");
	marca_list_label = gtk_label_new("Marca\n");	
	observacoes_list_label = gtk_label_new("Observações\n");	
	
	gtk_box_pack_start(GTK_BOX(codigo_prod_list),codigo_prod_list_label,0,0,0); //padrao de nome de variavel
	gtk_box_pack_start(GTK_BOX(nome_prod_list),nome_prod_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(preco_prod_list),preco_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(peso_prod_list),peso_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(unidade_prod_list),unidade_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(fornecedor_prod_list),fornecedor_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(grupo_prod_list),grupo_list_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(marca_prod_list),marca_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(observacoes_prod_list),observacoes_list_label,0,0,0);
	
	while(pos<cont)
	{

		gtk_container_add(GTK_CONTAINER(evento[pos]),codigop[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),separadoresvp[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_prod_list),nomep[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_prod_list),separadoresvp[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(preco_prod_list),preco[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(preco_prod_list),separadoresvp[pos][2],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(peso_prod_list),peso[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(peso_prod_list),separadoresvp[pos][3],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(unidade_prod_list),unidade[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(unidade_prod_list),separadoresvp[pos][4],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(fornecedor_prod_list),fornecedor[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(fornecedor_prod_list),separadoresvp[pos][5],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(grupo_prod_list),grupo[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(grupo_prod_list),separadoresvp[pos][6],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(marca_prod_list),marca[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(marca_prod_list),separadoresvp[pos][7],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(observacoes_prod_list),observacoes[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(observacoes_prod_list),separadoresvp[pos][8],0,0,10);
	
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(chama_prod_codigo),vet_codigosp[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_prod_list,70,30);
	gtk_widget_set_size_request(nome_prod_list,70,30);
	gtk_widget_set_size_request(preco_prod_list,70,30);
	gtk_widget_set_size_request(peso_prod_list,75,30);
	gtk_widget_set_size_request(unidade_prod_list,70,30);
	gtk_widget_set_size_request(fornecedor_prod_list,70,30);
	gtk_widget_set_size_request(grupo_prod_list,70,30);
	gtk_widget_set_size_request(marca_prod_list,70,30);
	gtk_widget_set_size_request(observacoes_prod_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunasp),codigo_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),nome_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),preco_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),peso_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),unidade_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),fornecedor_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),grupo_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),marca_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunasp),observacoes_prod_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunasp,0,0,20);
	gtk_widget_show_all(colunasp);
	return 0;
}

int pesquisar_produtos(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;

	GtkWidget *lista_scroll_caixah, *lista_scroll_caixav, 
	*lista_scroll_windowv, *lista_scroll_windowh;
	
	pesquisa = gtk_search_entry_new();

	lista_ter_label = gtk_label_new("Produtos");
	
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	lista_prod = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(lista_prod),3);
	gtk_window_set_keep_above(GTK_WINDOW(lista_prod), TRUE);
	gtk_window_set_title(GTK_WINDOW(lista_prod),"Lista de Produtos");
			
	gtk_window_set_position(GTK_WINDOW(lista_prod),3);
	gtk_window_set_resizable(GTK_WINDOW(lista_prod),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"LISTAGEM PRODUTOS");
	
	gtk_widget_set_size_request(lista_prod,1000,600);
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


	gtk_container_add(GTK_CONTAINER(lista_prod),lista_scroll_windowh);
	g_signal_connect(pesquisa,"key-press-event",G_CALLBACK(rec_prod_list),lista_scroll_caixav);
	g_signal_connect(lista_prod,"destroy",G_CALLBACK(close_window_callback),lista_prod);
	gtk_widget_show_all(lista_prod);	
	return 0;
}
