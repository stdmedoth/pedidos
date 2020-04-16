GtkWidget *pesq_prod;	
static GtkWidget *alvop;
static int inclui_codigop(GtkWidget *widget,GdkEvent *evento,char *pcodigo)
{
	gtk_entry_set_text(GTK_ENTRY(alvop),pcodigo);
	gtk_widget_activate(alvop);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",pcodigo);
	gtk_widget_destroy(pesq_prod);
	gtk_widget_grab_focus(GTK_WIDGET(alvop));
	return 0;
}

static GtkWidget *colunas_pesquisap;
static int recebe_produtos(GtkWidget *widget,GdkEvent *event,gpointer lista_scroll_caixav)
{
	int cont=0;
	int pos=0;
	char **vet_codigosp;
	char *formatar;
	GtkWidget **evento, **codigop, **nomep, **preco;
	
	GtkWidget          
	*codigo_prod_list_label,
	*nome_prod_list_label,
	*preco_list_label;
	
	GtkWidget 
	*codigo_prod_list,
	*nome_prod_list,
	*preco_prod_list;

	vet_codigosp = malloc(sizeof(gchar*)*MAX_LINHAS);
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigop = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nomep = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	preco = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	formatar = malloc(sizeof(char)*MAX_PRECO_LEN);
	
	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	
	GList *children,*iter;
	if(GTK_IS_WIDGET(colunas_pesquisap))
	{
		children = gtk_container_get_children(GTK_CONTAINER(colunas_pesquisap));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
		gtk_widget_destroy(GTK_WIDGET(colunas_pesquisap));
	}
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));
	colunas_pesquisap = gtk_box_new(0,0);	
	if(strlen(entrada)<=0)
		return 0;

	sprintf(query,"select code,nome,preco from produtos where nome like '%c%s%c';",ascii,entrada,ascii);
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

		sprintf(formatar,"R$ %.2f",atof(campos[2]));		
		preco[cont] = gtk_label_new(formatar);
		separadoresvp[cont][2] = gtk_separator_new(0);
		
		
		cont++;
	}
	if(cont==0)
		return 0;
	
	
	codigo_prod_list = gtk_box_new(1,0);
	nome_prod_list = gtk_box_new(1,0);
	preco_prod_list = gtk_box_new(1,0);
	
	codigo_prod_list_label = gtk_label_new("Código do produto\n");	
	nome_prod_list_label = gtk_label_new("Nome do produto\n");
	preco_list_label = gtk_label_new("Preço\n");
	
	gtk_box_pack_start(GTK_BOX(codigo_prod_list),codigo_prod_list_label,0,0,0); //padrao de nome de variavel
	gtk_box_pack_start(GTK_BOX(nome_prod_list),nome_prod_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(preco_prod_list),preco_list_label,0,0,0);
	
	while(pos<cont)
	{

		gtk_container_add(GTK_CONTAINER(evento[pos]),codigop[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),separadoresvp[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_prod_list),nomep[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_prod_list),separadoresvp[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(preco_prod_list),preco[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(preco_prod_list),separadoresvp[pos][2],0,0,10);
			
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(inclui_codigop),vet_codigosp[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_prod_list,70,30);
	gtk_widget_set_size_request(nome_prod_list,70,30);
	gtk_widget_set_size_request(preco_prod_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunas_pesquisap),codigo_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisap),nome_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisap),preco_prod_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunas_pesquisap,0,0,20);
	gtk_widget_show_all(colunas_pesquisap);
	return 0;
}

static int lista_produtos(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;
	GtkWidget *lista_scroll_caixah=NULL, *lista_scroll_caixav=NULL;
	GtkWidget *lista_scroll_windowv=NULL, *lista_scroll_windowh=NULL;
	alvop =(GtkWidget*) ponteiro;
	pesquisa = gtk_search_entry_new();
	g_print("Abrindo listagem\n");
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	pesq_prod = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pesq_prod),3);
	gtk_window_set_keep_above(GTK_WINDOW(pesq_prod), TRUE);
	gtk_window_set_title(GTK_WINDOW(pesq_prod),"Lista de Produtos");
			
	gtk_window_set_position(GTK_WINDOW(pesq_prod),3);
	gtk_window_set_resizable(GTK_WINDOW(pesq_prod),FALSE);
	
	gtk_widget_set_size_request(pesq_prod,200,400);
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

	gtk_container_add(GTK_CONTAINER(pesq_prod),lista_scroll_windowh);
	
	g_signal_connect(pesquisa,"key-press-event",G_CALLBACK(recebe_produtos),lista_scroll_caixav);
	g_signal_connect(pesq_prod,"destroy",G_CALLBACK(close_window_callback),pesq_prod);

	gtk_widget_show_all(pesq_prod);	
	return 0;
}

