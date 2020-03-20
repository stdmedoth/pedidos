int lista_ter(GtkWidget *botao,gpointer *ponteiro)
{
	int cont=0,pos=0;
	char query[] = "select * from terceiros;";
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	GtkWidget *lista_ter, *separador1,*separador2,*separador3;
	GtkWidget *codigo_ter_list,*nome_ter_list,*address_ter_list,*type_ter_list,*colunas;
	GtkWidget *codigo_list_label,*nome_list_label,*address_list_label,*type_list_label;
	GtkWidget **codigo,**nome,**address,**type;
	
	codigo_list_label = gtk_label_new("Código do Terceiro\n");
	nome_list_label = gtk_label_new("Nome do Terceiro\n");
	address_list_label = gtk_label_new("Endereço do Terceiro\n");
	type_list_label = gtk_label_new("Tipo de Terceiro\n");	
	/*pintar de vermelhor
	GdkColor cor_coluna;
	gdk_color_parse("red",&cor_coluna);
	gtk_widget_modify_fg(codigo_list_label,GTK_STATE_NORMAL,&cor_coluna);
	gtk_widget_modify_fg(nome_list_label,GTK_STATE_NORMAL,&cor_coluna);
	gtk_widget_modify_fg(address_list_label,GTK_STATE_NORMAL,&cor_coluna);
	gtk_widget_modify_fg(type_list_label,GTK_STATE_NORMAL,&cor_coluna);
	*/
	lista_ter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_keep_above(GTK_WINDOW(lista_ter), TRUE);
	gtk_window_set_title(GTK_WINDOW(lista_ter),"Listagem de Terceiros");
	
	
	codigo_ter_list = gtk_box_new(1,0);
	nome_ter_list = gtk_box_new(1,0);
	address_ter_list = gtk_box_new(1,0);
	type_ter_list = gtk_box_new(1,0);
	colunas = gtk_box_new(0,0);
	
	separador1 = gtk_separator_new(1);
	separador2 = gtk_separator_new(1);
	separador3 = gtk_separator_new(1);
	
	gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_ter_list),nome_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address_ter_list),address_list_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(type_ter_list),type_list_label,0,0,0);
	
	vetor = consultar(query);
	codigo = malloc(10000);
	nome = malloc(10000);
	address = malloc(10000);
	type = malloc(10000);
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		codigo[cont] = gtk_label_new(campos[pos]);
		nome[cont] =  gtk_label_new(campos[pos+1]);
		address[cont] = gtk_label_new(campos[pos+2]);
		type[cont] = gtk_label_new(campos[pos+3]);
		cont++;
		pos = 0;
	}
	
	while(codigo[pos]!=NULL&&pos<cont)
	{
		gtk_box_pack_start(GTK_BOX(codigo_ter_list),codigo[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(nome_ter_list),nome[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(address_ter_list),address[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(type_ter_list),type[pos],0,0,0);		
		pos++;
	}
	
	gtk_box_pack_start(GTK_BOX(colunas),codigo_ter_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separador1,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),nome_ter_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separador2,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),address_ter_list,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),separador3,0,0,0);
	gtk_box_pack_start(GTK_BOX(colunas),type_ter_list,0,0,0);
	gtk_widget_set_size_request(codigo_ter_list,150,30);
	gtk_widget_set_size_request(nome_ter_list,450,30);
	gtk_widget_set_size_request(address_ter_list,450,30);
	gtk_widget_set_size_request(type_ter_list,150,30);
	gtk_window_set_position(GTK_WINDOW(lista_ter),3);
	gtk_window_set_resizable(GTK_WINDOW(lista_ter),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"LISTAGEM TERCEIROS");
	gtk_widget_set_size_request(lista_ter,1200,600);
	gtk_container_add(GTK_CONTAINER(lista_ter),colunas);
	gtk_widget_show_all(lista_ter);
	return 0;
	
	return 0;
}
