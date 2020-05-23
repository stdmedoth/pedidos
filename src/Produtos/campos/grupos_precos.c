static GtkWidget **entry_preco_grupo_label;
static GtkWidget **entry_preco_grupo_prcvist;
static GtkWidget **entry_preco_grupo_prcfat;
static GtkWidget *grid1_grupo=NULL;
static int grupos_qnt=0;

int preco_faturado()
{
	
	return 0;
}
int preco_a_vista()
{
	precos_faturado_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(preco_faturado_prod_field));
	if(strlen(precos_faturado_prod)>MAX_MRC_LEN)
	{
		popup(NULL,"Fator inserida é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(preco_faturado_prod_field));
		return 1;
	}
	else
	if(strlen(precos_faturado_prod)<=0)
	{
		if(produtos.criticar.fator==0)
		{
			//gtk_widget_grab_focus(concluir);
			return 0; 
		}
		popup(NULL,"Por favor, insira uma fator");
		gtk_widget_grab_focus(GTK_WIDGET(preco_faturado_prod_field));
		return 1;		
	}
	else
	{
		//gtk_widget_grab_focus(concluir);
	}
	g_print("fator: %s\n",precos_faturado_prod);

	return 0;
}


GtkWidget *notebook_preco_grupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	
	entry_preco_grupo_label = malloc(MAX_SUBGRUPO*sizeof(GtkLabel));
	entry_preco_grupo_prcvist = malloc(MAX_SUBGRUPO*sizeof(GtkEntry));
	entry_preco_grupo_prcfat = malloc(MAX_SUBGRUPO*sizeof(GtkEntry));
	int cont=1;
	
	if(grupos_prod==NULL)
		return grid1_grupo;	
	
	gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
	gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
	gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
	
	gtk_grid_insert_column (GTK_GRID(grid1_grupo),0);
	gtk_grid_insert_column (GTK_GRID(grid1_grupo),1);
	gtk_grid_insert_column (GTK_GRID(grid1_grupo),2);
		
	sprintf(query,"select nome from grupos where pai = '%s'",grupos_prod);

	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao verificar grupos para precos");
		return NULL;
	}

	gtk_grid_attach(GTK_GRID(grid1_grupo),gtk_label_new("À Vista"),1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid1_grupo),gtk_label_new("Faturado"),2,0,1,1);
	grupos_qnt=0;
	while((row = mysql_fetch_row(res))!=NULL)
	{
		entry_preco_grupo_label[cont] = gtk_button_new_with_label(row[0]);
		entry_preco_grupo_prcvist[cont] = gtk_entry_new();
		entry_preco_grupo_prcfat[cont] = gtk_entry_new();
		
		gtk_grid_attach(GTK_GRID(grid1_grupo),entry_preco_grupo_label[cont],0,cont,1,1);
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry_preco_grupo_prcvist[cont]),"R$ 00,00");
		gtk_grid_attach(GTK_GRID(grid1_grupo),entry_preco_grupo_prcvist[cont],1,cont,1,1);
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry_preco_grupo_prcfat[cont]),"R$ 00,00");
		gtk_grid_attach(GTK_GRID(grid1_grupo),entry_preco_grupo_prcfat[cont],2,cont,1,1);
		cont++;
		grupos_qnt++;
	}
	
	if(grupos_qnt==0)
	{
		gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
		gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
		gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
		popup(NULL,"Nenhum subgrupo para o grupo");
		
	}
	
	gtk_widget_show_all(grid1_grupo);
	return grid1_grupo;
}
