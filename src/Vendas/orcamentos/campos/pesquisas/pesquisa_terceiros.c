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

static GtkWidget *colunas_pesquisa_oc;
static int recebe_terceiros(GtkWidget *widget,gpointer lista_scroll_caixav)
{
	int cont=0;
	int pos=0;
	char **vet_codigos_oc;
	GtkWidget **evento_oc, **codigo_oc, **nome_oc, **telefone_oc;
	GtkWidget ***separadores_oc;	
	
	GtkWidget          
	*codigo_ter_list_label,
	*nome_ter_list_label,
	*telefone_ter_list_label;
	
	GtkWidget 
	*codigo_ter_list,
	*nome_ter_list,
	*telefone_ter_list;


	separadores_oc = malloc(sizeof(GtkSeparator*)*MAX_LINHAS);
	vet_codigos_oc = malloc(sizeof(gchar*)*MAX_LINHAS);
	evento_oc = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigo_oc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nome_oc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	telefone_oc = malloc(sizeof(GtkLabel*)*MAX_LINHAS);

	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));

	GList *children,*iter;
	if(GTK_IS_WIDGET(colunas_pesquisa_oc))
	{
		children = gtk_container_get_children(GTK_CONTAINER(colunas_pesquisa_oc));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
	}
	
	colunas_pesquisa_oc = gtk_box_new(0,0);	
	
	sprintf(query,"select code,razao,telefone from terceiros where razao like '%c%s%c' or doc = '%s';",ascii,entrada,ascii,entrada);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Nada encontrado %s na pesquisa\n",entrada);
		return 0;
	}
	g_print("Iniciando recebimento dos campos\n");
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadores_oc[cont] = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*ROWS_QNT);
		evento_oc[cont] = gtk_event_box_new();
		
		vet_codigos_oc[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigos_oc[cont],campos[0]);

		codigo_oc[cont] = gtk_label_new(campos[0]);
		separadores_oc[cont][0] = gtk_separator_new(0);
		
		nome_oc[cont] =  gtk_label_new(campos[1]);
		separadores_oc[cont][1] = gtk_separator_new(0);
		
		telefone_oc[cont] = gtk_label_new(campos[2]);
		separadores_oc[cont][2] = gtk_separator_new(0);
		
		cont++;
	}
	if(cont==0)
		return 0;
	
	g_print("Preparando colunas\n");
	codigo_ter_list = gtk_box_new(1,0);
	nome_ter_list = gtk_box_new(1,0);
	telefone_ter_list = gtk_box_new(1,0);
	
	codigo_ter_list_label = gtk_label_new("Código do terceiro\n");	
	nome_ter_list_label = gtk_label_new("Nome do terceiro\n");
	telefone_ter_list_label = gtk_label_new("Preço\n");
	
	gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo_ter_list_label,0,0,0); //padrao de nome de variavel
	gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_ter_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone_ter_list_label,0,0,0);
	
	g_print("Encaixotamento dos Widgets\n");
	while(pos<cont)
	{
		gtk_container_add(GTK_CONTAINER(evento_oc[pos]),codigo_oc[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),evento_oc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),separadores_oc[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_oc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_ter_list),separadores_oc[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),telefone_oc[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(telefone_ter_list),separadores_oc[pos][2],0,0,10);
			
		g_signal_connect(evento_oc[pos],"button-press-event",G_CALLBACK(inclui_codigoc),vet_codigos_oc[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_ter_list,70,30);
	gtk_widget_set_size_request(nome_ter_list,70,30);
	gtk_widget_set_size_request(telefone_ter_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_oc),codigo_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_oc),nome_ter_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_oc),telefone_ter_list,0,0,10);

	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunas_pesquisa_oc,0,0,20);
	gtk_widget_show_all(lista_scroll_caixav);
	g_print("Campos inseridos dos campos\n");
	return 0;
}

static int listar_terceiros(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;
	GtkWidget *lista_scroll_caixah=NULL, *lista_scroll_caixav=NULL;
	GtkWidget *lista_scroll_windowv=NULL, *lista_scroll_windowh=NULL;
	alvoc =(GtkWidget*) ponteiro;
	pesquisa = gtk_search_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(pesquisa),"Digite o Nome/CPF/CNPJ do Cliente");
	g_print("Abrindo listagem\n");
	lista_scroll_caixav = gtk_box_new(1,0);
	lista_scroll_caixah = gtk_box_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),pesquisa,0,0,20);
	
	listar_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(listar_ter),3);
	gtk_window_set_keep_above(GTK_WINDOW(listar_ter), TRUE);
	gtk_window_set_title(GTK_WINDOW(listar_ter),"Lista de Terceiros");
			
	gtk_window_set_position(GTK_WINDOW(listar_ter),3);
	gtk_window_set_resizable(GTK_WINDOW(listar_ter),FALSE);
	
	gtk_widget_set_size_request(listar_ter,200,400);
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

	
	g_signal_connect(pesquisa,"activate",G_CALLBACK(recebe_terceiros),lista_scroll_caixav);
	g_signal_connect(listar_ter,"destroy",G_CALLBACK(close_window_callback),listar_ter);
	gtk_container_add(GTK_CONTAINER(listar_ter),lista_scroll_windowh);
	gtk_widget_show_all(listar_ter);	
	
	return 0;
}


