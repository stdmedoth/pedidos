GtkWidget *pesq_und;	
static GtkWidget *alvo_und;
static int inclui_codigo_und(GtkWidget *widget,GdkEvent *evento,char *und_codigo)
{
	gtk_entry_set_text(GTK_ENTRY(alvo_und),und_codigo);
	gtk_widget_activate(alvo_und);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",und_codigo);
	gtk_widget_destroy(pesq_und);
	gtk_widget_grab_focus(GTK_WIDGET(alvo_und));
	return 0;
}

static GtkWidget *colunas_pesquisa_und;
static GtkWidget **separadoresv_und[30];
static int recebe_unidades(GtkWidget *widget,gpointer lista_scroll_caixav)
{
	int cont=0;
	int pos=0;
	char **vet_codigos_und;
	GtkWidget **evento, **codigo_und, **nome_und, **sigla_und;
	
	GtkWidget          
	*codigo_und_list_label,
	*nome_und_list_label,
	*sigla_und_list_label;
	
	GtkWidget 
	*codigo_und_list,
	*nome_und_list,
	*sigla_und_list;

	vet_codigos_und = malloc(sizeof(gchar*)*MAX_LINHAS);
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigo_und = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nome_und = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	sigla_und = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	
	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	
	GList *children,*iter;
	if(GTK_IS_WIDGET(colunas_pesquisa_und))
	{
		children = gtk_container_get_children(GTK_CONTAINER(colunas_pesquisa_und));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
		gtk_widget_destroy(GTK_WIDGET(colunas_pesquisa_und));
	}
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));
	colunas_pesquisa_und = gtk_box_new(0,0);	
	if(strlen(entrada)<=0)
		return 0;

	sprintf(query,"select code,nome,sigla from unidades where nome like '%c%s%c';",ascii,entrada,ascii);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Nada encontrado %s na pesquisa\n",entrada);
		return 0;
	}
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadoresv_und[cont] = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigos_und[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigos_und[cont],campos[0]);

		codigo_und[cont] = gtk_label_new(campos[0]);
		separadoresv_und[cont][0] = gtk_separator_new(0);
		
		nome_und[cont] =  gtk_label_new(campos[1]);
		separadoresv_und[cont][1] = gtk_separator_new(0);

		sigla_und[cont] = gtk_label_new(campos[2]);
		separadoresv_und[cont][2] = gtk_separator_new(0);
		
		
		cont++;
	}
	if(cont==0)
		return 0;
	
	
	codigo_und_list = gtk_box_new(1,0);
	nome_und_list = gtk_box_new(1,0);
	sigla_und_list = gtk_box_new(1,0);
	
	codigo_und_list_label = gtk_label_new("Código da unidade\n");	
	nome_und_list_label = gtk_label_new("Nome\n");
	sigla_und_list_label = gtk_label_new("Sigla\n");
	
	gtk_box_pack_start(GTK_BOX(codigo_und_list),codigo_und_list_label,0,0,0); //padrao de nome de variavel
	gtk_box_pack_start(GTK_BOX(nome_und_list),nome_und_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(sigla_und_list),sigla_und_list_label,0,0,0);
	
	while(pos<cont)
	{

		gtk_container_add(GTK_CONTAINER(evento[pos]),codigo_und[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_und_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_und_list),separadoresv_und[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_und_list),nome_und[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_und_list),separadoresv_und[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(sigla_und_list),sigla_und[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(sigla_und_list),separadoresv_und[pos][2],0,0,10);
			
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(inclui_codigo_und),vet_codigos_und[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_und_list,70,30);
	gtk_widget_set_size_request(nome_und_list,70,30);
	gtk_widget_set_size_request(sigla_und_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_und),codigo_und_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_und),nome_und_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_und),sigla_und_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunas_pesquisa_und,0,0,20);
	gtk_widget_show_all(colunas_pesquisa_und);
	return 0;
}

static int lista_unidades(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;
	GtkWidget *lista_scroll_caixah=NULL, *lista_scroll_caixav=NULL;
	GtkWidget *lista_scroll_windowv=NULL, *lista_scroll_windowh=NULL;
	alvo_und =(GtkWidget*) ponteiro;
	pesquisa = gtk_search_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(pesquisa),"Digite o nome do unidade");
	g_print("Abrindo listagem\n");
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	pesq_und = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pesq_und),3);
	gtk_window_set_keep_above(GTK_WINDOW(pesq_und), TRUE);
	gtk_window_set_title(GTK_WINDOW(pesq_und),"Lista de Unidades");
			
	gtk_window_set_position(GTK_WINDOW(pesq_und),3);
	gtk_window_set_resizable(GTK_WINDOW(pesq_und),FALSE);
	
	gtk_widget_set_size_request(pesq_und,200,400);
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

	gtk_container_add(GTK_CONTAINER(pesq_und),lista_scroll_windowh);
	
	g_signal_connect(pesquisa,"activate",G_CALLBACK(recebe_unidades),lista_scroll_caixav);
	g_signal_connect(pesq_und,"destroy",G_CALLBACK(close_window_callback),pesq_und);

	gtk_widget_show_all(pesq_und);	
	return 0;
}

