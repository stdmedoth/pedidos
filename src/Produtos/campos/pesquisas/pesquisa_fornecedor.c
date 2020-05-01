GtkWidget *pesq_forn;	
static GtkWidget *alvo_forn;
static int inclui_codigo_forn(GtkWidget *widget,GdkEvent *evento,char *forn_codigo)
{
	gtk_entry_set_text(GTK_ENTRY(alvo_forn),forn_codigo);
	gtk_widget_activate(alvo_forn);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",forn_codigo);
	gtk_widget_destroy(pesq_forn);
	gtk_widget_grab_focus(GTK_WIDGET(alvo_forn));
	return 0;
}

static GtkWidget *colunas_pesquisa_forn;
static GtkWidget **separadoresv_forn[30];
static int recebe_fornecedor(GtkWidget *widget,gpointer lista_scroll_caixav)
{
	int cont=0;
	int pos=0;
	char **vet_codigos_forn;
	GtkWidget **evento, **codigo_forn, **nome_forn, **sigla_forn;
	
	GtkWidget          
	*codigo_forn_list_label,
	*nome_forn_list_label,
	*cidade_forn_list_label;
	
	GtkWidget 
	*codigo_forn_list,
	*nome_forn_list,
	*cidade_forn_list;

	vet_codigos_forn = malloc(sizeof(gchar*)*MAX_LINHAS);
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigo_forn = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nome_forn = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	sigla_forn = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	
	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	
	GList *children,*iter;
	if(GTK_IS_WIDGET(colunas_pesquisa_forn))
	{
		children = gtk_container_get_children(GTK_CONTAINER(colunas_pesquisa_forn));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
		gtk_widget_destroy(GTK_WIDGET(colunas_pesquisa_forn));
	}
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));
	colunas_pesquisa_forn = gtk_box_new(0,0);	
	if(strlen(entrada)<=0)
		return 0;

	sprintf(query,"select code,razao,cidade from terceiros where razao like '%c%s%c';",ascii,entrada,ascii);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Nada encontrado %s na pesquisa\n",entrada);
		return 0;
	}
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadoresv_forn[cont] = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigos_forn[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigos_forn[cont],campos[0]);

		codigo_forn[cont] = gtk_label_new(campos[0]);
		separadoresv_forn[cont][0] = gtk_separator_new(0);
		
		nome_forn[cont] =  gtk_label_new(campos[1]);
		separadoresv_forn[cont][1] = gtk_separator_new(0);

		sigla_forn[cont] = gtk_label_new(campos[2]);
		separadoresv_forn[cont][2] = gtk_separator_new(0);
		
		
		cont++;
	}
	if(cont==0)
		return 0;
	
	
	codigo_forn_list = gtk_box_new(1,0);
	nome_forn_list = gtk_box_new(1,0);
	cidade_forn_list = gtk_box_new(1,0);
	
	codigo_forn_list_label = gtk_label_new("Código da Terceiro\n");	
	nome_forn_list_label = gtk_label_new("Nome\n");
	cidade_forn_list_label = gtk_label_new("Cidade\n");
	
	gtk_box_pack_start(GTK_BOX(codigo_forn_list),codigo_forn_list_label,0,0,0); //padrao de nome de variavel
	gtk_box_pack_start(GTK_BOX(nome_forn_list),nome_forn_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(cidade_forn_list),cidade_forn_list_label,0,0,0);
	
	while(pos<cont)
	{

		gtk_container_add(GTK_CONTAINER(evento[pos]),codigo_forn[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_forn_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_forn_list),separadoresv_forn[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_forn_list),nome_forn[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_forn_list),separadoresv_forn[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(cidade_forn_list),sigla_forn[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(cidade_forn_list),separadoresv_forn[pos][2],0,0,10);
			
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(inclui_codigo_forn),vet_codigos_forn[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_forn_list,70,30);
	gtk_widget_set_size_request(nome_forn_list,70,30);
	gtk_widget_set_size_request(cidade_forn_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_forn),codigo_forn_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_forn),nome_forn_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_forn),cidade_forn_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunas_pesquisa_forn,0,0,20);
	gtk_widget_show_all(colunas_pesquisa_forn);
	return 0;
}

static int lista_terceiros(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;
	GtkWidget *lista_scroll_caixah=NULL, *lista_scroll_caixav=NULL;
	GtkWidget *lista_scroll_windowv=NULL, *lista_scroll_windowh=NULL;
	alvo_forn =(GtkWidget*) ponteiro;
	pesquisa = gtk_search_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(pesquisa),"Digite o nome do terceiro");
	g_print("Abrindo listagem\n");
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	pesq_forn = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pesq_forn),3);
	gtk_window_set_keep_above(GTK_WINDOW(pesq_forn), TRUE);
	gtk_window_set_title(GTK_WINDOW(pesq_forn),"Lista de Fornecedor");
			
	gtk_window_set_position(GTK_WINDOW(pesq_forn),3);
	gtk_window_set_resizable(GTK_WINDOW(pesq_forn),FALSE);
	
	gtk_widget_set_size_request(pesq_forn,200,400);
	abrir_css(DESKTOP_STYLE);

	lista_scroll_windowv = gtk_scrolled_window_new(NULL,NULL);
	lista_scroll_windowh = gtk_scrolled_window_new(NULL,NULL);
	
	gtk_widget_set_size_request(lista_scroll_caixav,400,10000);
	gtk_widget_set_size_request(lista_scroll_windowv,400,400);
	gtk_widget_set_size_request(lista_scroll_caixah,400,400);
	gtk_widget_set_size_request(lista_scroll_windowh,400,400);
	
	
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

	gtk_container_add(GTK_CONTAINER(pesq_forn),lista_scroll_windowh);
	
	g_signal_connect(pesquisa,"activate",G_CALLBACK(recebe_fornecedor),lista_scroll_caixav);
	g_signal_connect(pesq_forn,"destroy",G_CALLBACK(close_window_callback),pesq_forn);

	gtk_widget_show_all(pesq_forn);	
	return 0;
}

