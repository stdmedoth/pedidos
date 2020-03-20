int listagem_und()
{
	int pos=0,cont=0;
	GtkWidget *lista_prod, *separador1,*separador2,*separador3;
	GtkWidget *codigo_list,*nome_list,*preco_list,*fornecedor_list,*colunas;
	GtkWidget *codigo_list_label,*nome_list_label,*preco_list_label,*fornecedor_list_label;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	GtkWidget **codigo,**nome,**preco,**supp;
	char query[] = "select * from produtos";
	vetor = consultar(query);
	
	lista_prod = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(lista_prod),"Listagem de Produtos");
	gtk_window_set_position(GTK_WINDOW(lista_prod),3);
	gtk_window_set_resizable(GTK_WINDOW(lista_prod),FALSE);
	
	codigo_list_label = gtk_label_new("Código do produto\n");
	nome_list_label = gtk_label_new("Nome do produto\n");
	preco_list_label = gtk_label_new("Preco do produto\n");
	fornecedor_list_label = gtk_label_new("Fornecedor do produto\n");
	
	/*pintar de vermelho
	gtk_widget_modify_fg(codigo_list_label,GTK_STATE_NORMAL,&columns);
	gtk_widget_modify_fg(nome_list_label,GTK_STATE_NORMAL,&columns);
	gtk_widget_modify_fg(preco_list_label,GTK_STATE_NORMAL,&columns);
	gtk_widget_modify_fg(fornecedor_list_label,GTK_STATE_NORMAL,&columns);
	*/
	codigo_list = gtk_box_new(1,0);
	nome_list = gtk_box_new(1,0);
	preco_list = gtk_box_new(1,0);
	fornecedor_list = gtk_box_new(1,0);
	colunas = gtk_box_new(0,0);
	
	separador1 = gtk_separator_new(1);
	separador2 = gtk_separator_new(1);
	separador3 = gtk_separator_new(1);
	
	gtk_box_pack_start(GTK_BOX(codigo_list),codigo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_list),nome_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(preco_list),preco_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(fornecedor_list),fornecedor_list_label,0,0,0);
	
	codigo = malloc(10000);
	nome = malloc(10000);
	preco = malloc(10000);
	supp = malloc(10000);
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		codigo[cont] = gtk_label_new(campos[pos]);
		nome[cont] =  gtk_label_new(campos[pos+1]);
		preco[cont] = gtk_label_new(campos[pos+2]);
		supp[cont] = gtk_label_new(campos[pos+3]);
		cont++;
		pos = 0;
	}
	while(codigo[pos]!=NULL&&pos<cont)
	{
		gtk_box_pack_start(GTK_BOX(codigo_list),codigo[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(nome_list),nome[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(preco_list),preco[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(fornecedor_list),supp[pos],0,0,0);		
		pos++;
	}
	
	gtk_box_pack_start(GTK_BOX(colunas),codigo_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separador1,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),nome_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separador2,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),preco_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separador3,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),fornecedor_list,0,0,0);
	gtk_widget_set_size_request(codigo_list,150,30);
	gtk_widget_set_size_request(nome_list,450,30);
	gtk_widget_set_size_request(preco_list,150,30);
	gtk_widget_set_size_request(fornecedor_list,450,30);
	gtk_widget_set_size_request(lista_prod,1200,600);
	gtk_container_add(GTK_CONTAINER(lista_prod),colunas);
	gtk_widget_grab_focus(GTK_WIDGET(code_field));
	gtk_widget_show_all(lista_prod);
	return 0;
}

