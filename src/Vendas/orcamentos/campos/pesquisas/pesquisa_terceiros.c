GtkWidget *listar_ter;	
static GtkWidget *alvoc;
static int inclui_codigoc(GtkWidget *widget,GdkEvent *evento,char *pcodigo)
{
	gtk_entry_set_text(GTK_ENTRY(alvoc),pcodigo);
	gtk_widget_activate(alvoc);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",pcodigo);
	gtk_widget_grab_focus(alvoc);
	gtk_widget_destroy(listar_ter);
	return 0;
}

static GtkWidget *colunas_pesquisac;
static int recebe_terceiros(GtkWidget *widget,GdkEvent *event,gpointer lista_scroll_caixav)
{
	int cont=0;
	int pos=0;
	char **vet_codigosc;
	GtkWidget **evento, **codigop, **nomep, **telefone;
	
	GtkWidget          
	*codigo_ter_list_label,
	*nome_ter_list_label,
	*telefone_ter_list_label;
	
	GtkWidget 
	*codigo_ter_list,
	*nome_ter_list,
	*telefone_ter_list;

	vet_codigosc = malloc(sizeof(gchar*)*MAX_LINHAS);
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigop = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nomep = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	telefone = malloc(sizeof(GtkLabel*)*MAX_LINHAS);

	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));

	if(GTK_IS_WIDGET(colunas_pesquisac))
		gtk_widget_destroy(colunas_pesquisac);
	
	colunas_pesquisac = gtk_box_new(0,0);	

	sprintf(query,"select code,razao,telefone from terceiros where razao like '%c%s%c';",ascii,entrada,ascii);
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
		
		vet_codigosc[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigosc[cont],campos[0]);

		codigop[cont] = gtk_label_new(campos[0]);
		separadoresvp[cont][0] = gtk_separator_new(0);
		
		nomep[cont] =  gtk_label_new(campos[1]);
		separadoresvp[cont][1] = gtk_separator_new(0);
		
		telefone[cont] = gtk_label_new(campos[2]);
		separadoresvp[cont][2] = gtk_separator_new(0);
		
		cont++;
	}
	if(cont==0)
		return 0;
	
	
	codigo_ter_list = gtk_box_new(1,0);
	nome_ter_list = gtk_box_new(1,0);
	telefone_ter_list = gtk_box_new(1,0);
	
	codigo_ter_list_label = gtk_label_new("Código do terceiro\n");	
	nome_ter_list_label = gtk_label_new("Nome do terceiro\n");
	telefone_ter_list_label = gtk_label_new("Preço\n");
	
	gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo_ter_list_label,0,0,0); //padrao de nome de variavel
	gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_ter_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone_ter_list_label,0,0,0);
	
	while(pos<cont)
	{

		gtk_container_add(GTK_CONTAINER(evento[pos]),codigop[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),separadoresvp[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_ter_list),nomep[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_ter_list),separadoresvp[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),separadoresvp[pos][2],0,0,10);
			
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(inclui_codigoc),vet_codigosc[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_ter_list,70,30);
	gtk_widget_set_size_request(nome_ter_list,70,30);
	gtk_widget_set_size_request(telefone_ter_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunas_pesquisac),codigo_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisac),nome_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisac),telefone_ter_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunas_pesquisac,0,0,20);
	gtk_widget_show_all(colunas_pesquisac);
	return 0;
}

static int listar_terceiros(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;
	GtkWidget *lista_scroll_caixah=NULL, *lista_scroll_caixav=NULL;
	GtkWidget *lista_scroll_windowv=NULL, *lista_scroll_windowh=NULL;
	alvoc =(GtkWidget*) ponteiro;
	pesquisa = gtk_search_entry_new();
	g_print("Abrindo listagem\n");
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	listar_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(listar_ter),3);
	gtk_window_set_keep_above(GTK_WINDOW(listar_ter), TRUE);
	gtk_window_set_title(GTK_WINDOW(listar_ter),"Lista de Produtos");
			
	gtk_window_set_position(GTK_WINDOW(listar_ter),3);
	gtk_window_set_resizable(GTK_WINDOW(listar_ter),FALSE);
	
	gtk_widget_set_size_request(listar_ter,200,400);
	abrir_css(DESKTOP_STYLE);

	lista_scroll_windowv = gtk_scrolled_window_new(NULL,NULL);
	lista_scroll_windowh = gtk_scrolled_window_new(NULL,NULL);
	
	gtk_widget_set_size_request(lista_scroll_caixav,1000,600);
	gtk_widget_set_size_request(lista_scroll_windowv,400,400);
	gtk_widget_set_size_request(lista_scroll_caixah,1000,3000);
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

	gtk_container_add(GTK_CONTAINER(listar_ter),lista_scroll_windowh);
	
	g_signal_connect(pesquisa,"key-press-event",G_CALLBACK(recebe_terceiros),lista_scroll_caixav);
	g_signal_connect(listar_ter,"destroy",G_CALLBACK(close_window_callback),listar_ter);

	gtk_widget_show_all(listar_ter);	
	return 0;
}


