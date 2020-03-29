#undef PSQ_TER_QUERY
#define PSQ_TER_QUERY "select * from produtos where razao like '%c%s%c';"
MYSQL_RES *vetor;
MYSQL_ROW campos;
char **vet_codigos;
GtkWidget *filas;
GtkWidget **separadoresv[5];
GtkWidget *lista_prod, **separadoresh;
GtkWidget *pesquisa;
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

GtkWidget          
*codigo_list_label,
*nome_list_label,
*preco_list_label,
*peso_list_label,
*unidade_list_label,
*fornecedor_list_label,
*grupo_list_label,
*marca_list_label,
*observacoes_list_label;

GtkWidget *colunas; //visual
//vetores como as linhas
GtkWidget **codigo,**nome,**preco,**peso,**unidade,**fornecedor,**grupo,**marca,**observacoes;

GtkWidget *lista_scroll_caixah, *lista_scroll_caixav, *lista_scroll_windowv, *lista_scroll_windowh, *lista_ter_label;
/*entrys de terceiros*/

int chama_prod_codigo(GtkWidget *widget,GdkEvent *evento,char *pcodigo)
{
	gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),pcodigo);
	g_print("inserindo codigo %s no campo de código para efetuar alteracao\n",pcodigo);
	if(altera_prod()==0)
		gtk_widget_destroy(lista_prod);
	return 0;
}

int rec_prod_list(GtkWidget *widget)
{
	cont=0;
	pos=0;
	GtkWidget **evento;
	char query[QUERY_LEN];
	gchar *entrada;
	int ascii = 37;
	char **vet_codigos;
	vet_codigos = malloc(CODE_LEN*MAX_LINHAS);
	entrada = malloc(ENTRADA);
	entrada = (gchar*) gtk_entry_get_text(GTK_ENTRY(widget));
	
	evento = malloc(sizeof(GtkEventBox*)*MAX_LINHAS);
	codigo = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	nome = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	preco = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	peso = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	unidade = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	fornecedor = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	grupo = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	marca = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	observacoes = malloc(sizeof(GtkLabel*)*MAX_LINHAS);
	
	if(GTK_IS_WIDGET(colunas))
		gtk_widget_destroy(colunas);

	sprintf(query,"select * from produtos where nome like '%c%s%c';",ascii,entrada,ascii);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		g_print("Nada encontrado %s na pesquisa\n",entrada);
		return 1;
	}
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		separadoresv[cont] = malloc(MAX_LINHAS*ROWS_QNT);
		evento[cont] = gtk_event_box_new();
		
		vet_codigos[cont] = malloc(CODE_LEN);	
		strcpy(vet_codigos[cont],campos[0]);

		codigo[cont] = gtk_label_new(campos[0]);
		separadoresv[cont][0] = gtk_separator_new(0);
		
		nome[cont] =  gtk_label_new(campos[1]);
		separadoresv[cont][1] = gtk_separator_new(0);
		
		preco[cont] = gtk_label_new(campos[2]);
		separadoresv[cont][2] = gtk_separator_new(0);
		
		peso[cont] = gtk_label_new(campos[3]);
		separadoresv[cont][3] = gtk_separator_new(0);
		
		unidade[cont] = gtk_label_new(campos[4]);
		separadoresv[cont][5] = gtk_separator_new(0);
		
		fornecedor[cont] = gtk_label_new(campos[5]);
		separadoresv[cont][6] = gtk_separator_new(0);

		grupo[cont] = gtk_label_new(campos[6]);
		separadoresv[cont][7] = gtk_separator_new(0);
		
		marca[cont] = gtk_label_new(campos[7]);
		separadoresv[cont][8] = gtk_separator_new(0);
		
		observacoes[cont] = gtk_label_new(campos[8]);
		separadoresv[cont][9] = gtk_separator_new(0);
		
		cont++;
	}
	if(cont==0)
		return 0;
		
	colunas = gtk_box_new(0,0);
	codigo_prod_list = gtk_box_new(1,0);
	nome_prod_list = gtk_box_new(1,0);
	preco_prod_list = gtk_box_new(1,0);
	peso_prod_list = gtk_box_new(1,0);
	unidade_prod_list = gtk_box_new(1,0);
	fornecedor_prod_list = gtk_box_new(1,0);
	grupo_prod_list = gtk_box_new(1,0);
	marca_prod_list = gtk_box_new(1,0);
	observacoes_prod_list = gtk_box_new(1,0);
	
	codigo_list_label = gtk_label_new("Código do produto\n");	
	nome_list_label = gtk_label_new("Nome do produto\n");
	preco_list_label = gtk_label_new("Preço\n");
	peso_list_label = gtk_label_new("Peso\n");
	unidade_list_label = gtk_label_new("Modelo Unidade\n");	
	fornecedor_list_label = gtk_label_new("Fornecedor\n");
	grupo_list_label = gtk_label_new("Grupo\n");
	marca_list_label = gtk_label_new("Marca\n");	
	observacoes_list_label = gtk_label_new("Observações\n");	
	
	gtk_box_pack_start(GTK_BOX(codigo_prod_list),codigo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_prod_list),nome_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(preco_prod_list),preco_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(peso_prod_list),peso_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(unidade_prod_list),unidade_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(fornecedor_prod_list),fornecedor_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(grupo_prod_list),grupo_list_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(marca_prod_list),marca_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(observacoes_prod_list),observacoes_list_label,0,0,0);
	
	while(pos<cont)
	{
		gtk_container_add(GTK_CONTAINER(evento[pos]),codigo[pos]);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),evento[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_prod_list),separadoresv[pos][0],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(nome_prod_list),nome[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_prod_list),separadoresv[pos][1],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(preco_prod_list),preco[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(preco_prod_list),separadoresv[pos][2],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(peso_prod_list),peso[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(peso_prod_list),separadoresv[pos][3],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(unidade_prod_list),unidade[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(unidade_prod_list),separadoresv[pos][5],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(fornecedor_prod_list),fornecedor[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(fornecedor_prod_list),separadoresv[pos][6],0,0,10);
		
		gtk_box_pack_start(GTK_BOX(grupo_prod_list),grupo[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(grupo_prod_list),separadoresv[pos][7],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(marca_prod_list),marca[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(marca_prod_list),separadoresv[pos][8],0,0,10);
	
		gtk_box_pack_start(GTK_BOX(observacoes_prod_list),observacoes[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(observacoes_prod_list),separadoresv[pos][9],0,0,10);
	
		g_signal_connect(evento[pos],"button-press-event",G_CALLBACK(chama_prod_codigo),vet_codigos[pos]);
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
	
	gtk_box_pack_start(GTK_BOX(colunas),codigo_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),nome_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),preco_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),peso_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),unidade_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),fornecedor_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),grupo_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),marca_prod_list,0,0,10);
	gtk_box_pack_start(GTK_BOX(colunas),observacoes_prod_list,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixav),colunas,0,0,20);
	gtk_widget_show_all(colunas);
	return 0;
}

int pesquisar_produtos(GtkWidget *botao,gpointer *ponteiro)
{
	pesquisa = gtk_search_entry_new();
	lista_ter_label = gtk_label_new("Terceiros");
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
	g_signal_connect(pesquisa,"key-press-event",G_CALLBACK(rec_prod_list),pesquisa);
	gtk_widget_show_all(lista_prod);
	
	return 0;
}
