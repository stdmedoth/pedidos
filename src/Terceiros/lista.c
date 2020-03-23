#define TERC_QNT  10000
#define MAX_LINHAS (sizeof(GtkBox*)*14)*TERC_QNT

int lista_ter(GtkWidget *botao,gpointer *ponteiro)
{
	int cont=0,pos=0;
	char query[] = "select * from terceiros;";
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	GtkWidget *lista_ter, *separadorv1,*separadorv2,*separadorv3;
	GtkWidget *pesquisa_label,*pesquisa_entry;
	
	GtkWidget **separadorh1,**separadorh2,**separadorh3,**separadorh4;
	
	GtkWidget 
	*codigo_ter_list,  //codigo
	*nome_ter_list,    //razao
	*address_ter_list, //endereco
	*type_ter_list;    //tipo

	GtkWidget          
	*codigo_list_label, //codigo label
	*nome_list_label,   //razao label
	*address_list_label,//endereco label
	*type_list_label;   //tipo label
	
	GtkWidget *colunas; //visual
	//vetores como as linhas
	GtkWidget **codigo,**nome,**address,**type;
	
	GtkWidget *lista_scroll_caixa,*lista_scroll_window,*lista_ter_label;
	
	lista_ter_label = gtk_label_new("Terceiros");
 	lista_scroll_caixa	 = gtk_box_new(1,0);
	lista_scroll_window = gtk_scrolled_window_new(NULL,NULL);
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(lista_scroll_window),lista_scroll_caixa);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(lista_scroll_window),lista_scroll_caixa);
	#endif	

	codigo_list_label = gtk_label_new("Código do Terceiro\n");
	gtk_widget_set_name(codigo_list_label,"fila");
	
	nome_list_label = gtk_label_new("Nome do Terceiro\n");
	gtk_widget_set_name(nome_list_label,"fila");
	
	address_list_label = gtk_label_new("Endereço do Terceiro\n");
	gtk_widget_set_name(address_list_label,"fila");
	
	type_list_label = gtk_label_new("Tipo de Terceiro\n");	
	gtk_widget_set_name(type_list_label,"fila");
	
	lista_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_keep_above(GTK_WINDOW(lista_ter), TRUE);
	gtk_window_set_title(GTK_WINDOW(lista_ter),"Lista de Terceiros");
	
	codigo_ter_list = gtk_box_new(1,0);
	nome_ter_list = gtk_box_new(1,0);
	address_ter_list = gtk_box_new(1,0);
	type_ter_list = gtk_box_new(1,0);
	
	colunas = gtk_box_new(0,0);
	
	gtk_widget_set_name(codigo_ter_list,"colunas_listagem");
	gtk_widget_set_name(nome_ter_list,"colunas_listagem");
	gtk_widget_set_name(address_ter_list,"colunas_listagem");
	gtk_widget_set_name(type_ter_list,"colunas_listagem");
	gtk_widget_set_name(colunas,"janela_colunas");
	
	separadorv1 = gtk_separator_new(1);
	gtk_widget_set_name(separadorv1,"separador");
	separadorv2 = gtk_separator_new(1);
	gtk_widget_set_name(separadorv2,"separador");
	separadorv3 = gtk_separator_new(1);
	gtk_widget_set_name(separadorv3,"separador");
	
	gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address_ter_list),address_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(type_ter_list),type_list_label,0,0,0);
	
	vetor = consultar(query);
	
	codigo = malloc(MAX_LINHAS);
	nome = malloc(MAX_LINHAS);
	address = malloc(MAX_LINHAS);
	type = malloc(MAX_LINHAS);
	separadorh1 = malloc(MAX_LINHAS);
	separadorh2 = malloc(MAX_LINHAS);
	separadorh3 = malloc(MAX_LINHAS);
	separadorh4 = malloc(MAX_LINHAS);
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		codigo[cont] = gtk_label_new(campos[pos]);
		separadorh1[cont] = gtk_separator_new(0);
		
		nome[cont] =  gtk_label_new(campos[pos+1]);
		separadorh2[cont] = gtk_separator_new(0);
		
		address[cont] = gtk_label_new(campos[pos+2]);
		separadorh3[cont] = gtk_separator_new(0);
		
		type[cont] = gtk_label_new(campos[pos+3]);
		separadorh4[cont] = gtk_separator_new(0);
		
		cont++;
		pos = 0;
	}
	
	while(pos<cont)
	{
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),separadorh1[pos],0,0,0);
		
		gtk_box_pack_start(GTK_BOX(nome_ter_list),nome[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(nome_ter_list),separadorh2[pos],0,0,0);
		
		gtk_box_pack_start(GTK_BOX(address_ter_list),address[pos],0,0,10);
		gtk_box_pack_start(GTK_BOX(address_ter_list),separadorh3[pos],0,0,0);
		
		gtk_box_pack_start(GTK_BOX(type_ter_list),type[pos],0,0,10);		
		gtk_box_pack_start(GTK_BOX(type_ter_list),separadorh4[pos],0,0,0);
		pos++;
	}
	
	gtk_box_pack_start(GTK_BOX(colunas),codigo_ter_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separadorv1,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),nome_ter_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separadorv2,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),address_ter_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separadorv3,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),type_ter_list,0,0,0);

	gtk_widget_set_size_request(codigo_ter_list,30,30);
	gtk_widget_set_size_request(nome_ter_list,225,30);
	gtk_widget_set_size_request(address_ter_list,225,30);
	gtk_widget_set_size_request(type_ter_list,75,30);
	
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixa),lista_ter_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(lista_scroll_caixa),colunas,0,0,20);
	gtk_container_add(GTK_CONTAINER(lista_ter),lista_scroll_window);


	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_resizable(GTK_WINDOW(lista_ter),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"LISTAGEM TERCEIROS");
	gtk_widget_set_size_request(lista_ter,1200,600);

	gtk_widget_show_all(lista_ter);
	return 0;
	
	return 0;
}
