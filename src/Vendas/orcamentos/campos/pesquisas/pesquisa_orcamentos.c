GtkWidget *pesq_orc;	
static GtkWidget *alvo_o;
static int inclui_codigo_o(GtkWidget *widget,GdkEvent *evento,char *orc_codigo)
{
	if(GTK_IS_WIDGET(alvo_o))
		gtk_entry_set_text(GTK_ENTRY(alvo_o),orc_codigo);
	altera_orc();
	//gtk_widget_activate(alvo_o);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",orc_codigo);
	if(GTK_IS_WIDGET(pesq_orc))
		gtk_widget_destroy(pesq_orc);
	if(GTK_IS_WIDGET(alvo_o))
		gtk_widget_grab_focus(GTK_WIDGET(alvo_o));
	return 0;
}

static GtkWidget *colunas_pesquisa_o,*caixona_orc;
static GtkWidget *lista_scroll_windowv_o=NULL;
static GtkWidget **separadoresv_o[10];

static int recebe_orcamentos(GtkWidget *widget, gpointer lista_scroll_caixav_o)
{
	int cont=0;
	int pos=0;
	char **vet_codigos_o;
	char *formatar;
	GtkWidget **evento, **codigo_o, **cliente_o, **total;
	
	GtkWidget          
	*codigo_prod_list_label,
	*cliente_prod_list_label,
	*total_list_label;
	
	GtkWidget 
	*codigo_prod_list,
	*cliente_prod_list,
	*total_prod_list;
	
	vet_codigos_o = malloc(sizeof(gchar*)*MAX_LINHAS);
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigo_o = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	cliente_o = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	total = malloc(sizeof(GtkLabel*)*MAX_LINHAS);


	formatar = malloc(MAX_PRECO_LEN*2);
	
	char query[QUERY_LEN];
	gchar *entrada;
	
	int ascii = 37;
	entrada = malloc(ENTRADA);
	
	GList *children,*iter;
	if(GTK_IS_WIDGET(colunas_pesquisa_o))
	{
		children = gtk_container_get_children(GTK_CONTAINER(colunas_pesquisa_o));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
		gtk_widget_destroy(GTK_WIDGET(colunas_pesquisa_o));
	}
	if(GTK_IS_WIDGET(lista_scroll_caixav_o))
	{
		children = gtk_container_get_children(GTK_CONTAINER(lista_scroll_caixav_o));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
		  gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);
		gtk_widget_destroy(GTK_WIDGET(lista_scroll_caixav_o));
	}
	

	
	gtk_widget_set_size_request(lista_scroll_caixav_o,400,400);
	gtk_widget_set_size_request(lista_scroll_windowv_o,400,400);
	
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));
	colunas_pesquisa_o = gtk_box_new(0,0);	
	
//	lista_scroll_windowv_o = gtk_scrolled_window_new(NULL,NULL);
	lista_scroll_caixav_o = gtk_box_new(1,0);
	
	sprintf(query,"select distinct a.code,b.razao,a.total from orcamentos as a join terceiros as b on a.cliente = b.code where b.razao like '%c%s%c' or b.doc = '%s';",ascii,entrada,ascii,entrada);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Nada encontrado %s na pesquisa\n",entrada);
		return 0;
	}
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadoresv_o[cont] = malloc(sizeof(GtkSeparator*)*MAX_LINHAS*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigos_o[cont] = malloc(CODE_LEN);	
		if(campos[0]!=NULL)
			strcpy(vet_codigos_o[cont],campos[0]);
		else
			strcpy(vet_codigos_o[cont],"1");
		
		if(campos[0]!=NULL)
			codigo_o[cont] = gtk_label_new(campos[0]);
		else
		codigo_o[cont] = gtk_label_new("vazio");
		separadoresv_o[cont][0] = gtk_separator_new(0);
		
		if(campos[1]!=NULL)
			cliente_o[cont] =  gtk_label_new(campos[1]);
		else
			cliente_o[cont] =  gtk_label_new("vazio");
		separadoresv_o[cont][1] = gtk_separator_new(0);
		
		if(campos[2]!=NULL)
			sprintf(formatar,"%s",campos[2]);
		else
			sprintf(formatar,"0,0");
		critica_real(formatar,NULL);
		sprintf(formatar,"R$ %.2f",atof(formatar));
		total[cont] = gtk_label_new(formatar);
		separadoresv_o[cont][2] = gtk_separator_new(0);
				
		cont++;
		if(cont==MAX_LINHAS)
			break;
	}
	if(cont==0)
		return 0;
	
	codigo_prod_list = gtk_box_new(1,0);
	cliente_prod_list = gtk_box_new(1,0);
	total_prod_list = gtk_box_new(1,0);
	
	codigo_prod_list_label = gtk_label_new("Código do orcamento\n");	
	cliente_prod_list_label = gtk_label_new("Cliente do orcamento\n");
	total_list_label = gtk_label_new("Total\n");
	
	gtk_box_pack_start(GTK_BOX(codigo_prod_list),codigo_prod_list_label,0,0,0); //padrao de cliente de variavel
	gtk_box_pack_start(GTK_BOX(cliente_prod_list),cliente_prod_list_label,0,0,0);		//mudou por causa de conflito
	gtk_box_pack_start(GTK_BOX(total_prod_list),total_list_label,0,0,0);
	
	while(pos<cont)
	{

		gtk_container_add(GTK_CONTAINER(evento[pos]),codigo_o[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),separadoresv_o[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(cliente_prod_list),cliente_o[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(cliente_prod_list),separadoresv_o[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(total_prod_list),total[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(total_prod_list),separadoresv_o[pos][2],0,0,10);
			
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(inclui_codigo_o),vet_codigos_o[pos]);
		pos++;
	}
	gtk_widget_set_size_request(codigo_prod_list,70,30);
	gtk_widget_set_size_request(cliente_prod_list,70,30);
	gtk_widget_set_size_request(total_prod_list,70,30);
	
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_o),codigo_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_o),cliente_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas_pesquisa_o),total_prod_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav_o),colunas_pesquisa_o,0,0,20);
	
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(lista_scroll_windowv_o),lista_scroll_caixav_o);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(lista_scroll_windowv_o),lista_scroll_caixav_o);
	#endif	
	
	gtk_box_pack_start(GTK_BOX(caixona_orc),lista_scroll_windowv_o,0,0,20);
	
	gtk_widget_show_all(caixona_orc);
	return 0;
}
static GtkWidget  *lista_scroll_caixav_o=NULL;
static int lista_orcamentos(GtkWidget *botao,gpointer *ponteiro)
{
	GtkWidget *pesquisa;	
	alvo_o =(GtkWidget*) ponteiro;
	pesquisa = gtk_search_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(pesquisa),"Digite o Nome/CPF/CNPJ do Cliente do Orçamento");
	g_print("Abrindo listagem\n");
	
	caixona_orc = gtk_box_new(1,0);
	colunas_pesquisa_o = gtk_box_new(0,0);	
	lista_scroll_windowv_o = gtk_scrolled_window_new(NULL,NULL);
	lista_scroll_caixav_o = gtk_box_new(1,0);
	
	pesq_orc = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pesq_orc),3);
	gtk_window_set_keep_above(GTK_WINDOW(pesq_orc), TRUE);
	gtk_window_set_title(GTK_WINDOW(pesq_orc),"Lista de Orçamentos");
			
	gtk_window_set_position(GTK_WINDOW(pesq_orc),3);
	gtk_window_set_resizable(GTK_WINDOW(pesq_orc),FALSE);
	
	gtk_widget_set_size_request(pesq_orc,500,400);
	abrir_css(DESKTOP_STYLE);
		
	gtk_box_pack_start(GTK_BOX(caixona_orc),pesquisa,0,0,20);
	
	gtk_container_add(GTK_CONTAINER(pesq_orc),caixona_orc);
	
	g_signal_connect(pesquisa,"activate",G_CALLBACK(recebe_orcamentos),lista_scroll_caixav_o);
	g_signal_connect(pesq_orc,"destroy",G_CALLBACK(close_window_callback),pesq_orc);

	gtk_widget_show_all(pesq_orc);	
	return 0;
}

