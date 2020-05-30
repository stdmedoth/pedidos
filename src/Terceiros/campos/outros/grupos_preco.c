static GtkWidget **entry_preco_ter_grupo_label;
static GtkWidget **entry_preco_ter_grupo_prcvist;
static GtkWidget **entry_preco_ter_grupo_prcfat;
static GtkWidget *grid1_ter_grupo=NULL;
static int ter_grupos_qnt=1;
static int grupos_ter_load=0;
int grupo_ter();
int produto_ter();
int notebook_preco_ter_grupo();
static int ter_grupos_preco_code[MAX_SUBGRUPO];


int insere_preco_ter_grupos()
{

	MYSQL_RES *res;
	MYSQL_ROW row;
	int cont=1;
	char query[MAX_QUERY_LEN];
	gchar *preco_fat=NULL, *preco_vist=NULL;
	
	preco_fat = malloc(MAX_PRECO_LEN);
	preco_vist = malloc(MAX_PRECO_LEN);	
	
	if(code_terc()!=0)
		return 1;
	
	if(produto_ter()!=0)
		return 1;
	
	sprintf(query,"select * from produtos where code = %s",prods_ter);
	if((res=consultar(query))==NULL)
	{
		popup(NULL,"Erro ao verificar existencia do produto");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		GtkWidget *opcao, *caixa, *label, *fixed;
		caixa = gtk_box_new(1,0);
		label = gtk_label_new("O Produto ainda não existe\nContinuar?");
		fixed = gtk_fixed_new();
		gtk_box_pack_start(GTK_BOX(caixa),label,0,0,10);
		gtk_fixed_put(GTK_FIXED(fixed),caixa,10,10);
		opcao = gtk_dialog_new_with_buttons("Produtos",NULL,4,"Continuar",GTK_RESPONSE_ACCEPT,"Cancelar",GTK_RESPONSE_REJECT,NULL);
		gtk_window_set_position(GTK_WINDOW(opcao),3);
		gtk_box_pack_start(GTK_BOX(gtk_bin_get_child(GTK_BIN(opcao))),fixed,0,0,0);
		gtk_widget_show_all(opcao);
		int resposta = gtk_dialog_run(GTK_DIALOG(opcao));
		
		switch(resposta)
		{
			case GTK_RESPONSE_ACCEPT:
				gtk_widget_destroy(opcao);
				break;
			case GTK_RESPONSE_REJECT:
				gtk_widget_destroy(opcao);
				return 0;
		}
	}

	g_print("Há %i grupos para serem inserido os preços\n",ter_grupos_qnt);
	
	for(cont=1;cont<ter_grupos_qnt;cont++)
	{
		preco_fat = (gchar*) gtk_entry_get_text(GTK_ENTRY(entry_preco_ter_grupo_prcfat[cont]));
		preco_vist = (gchar*) gtk_entry_get_text(GTK_ENTRY(entry_preco_ter_grupo_prcvist[cont]));
		if(critica_real(preco_fat, entry_preco_ter_grupo_prcfat[cont])!=0)
		{
			gtk_widget_grab_focus(entry_preco_ter_grupo_prcfat[cont]);
			return 1;
		}	
		
		if(critica_real(preco_vist, entry_preco_ter_grupo_prcvist[cont])!=0)
		{
			gtk_widget_grab_focus(entry_preco_ter_grupo_prcvist[cont]);
			return 1;
		}		
		g_print("_get_ valores para o grupo %i na posicao %i\n", ter_grupos_preco_code[cont],cont);		
				
		g_print("Grupo código: %i\n",ter_grupos_preco_code[cont]);
		g_print("Preço à Vista: %s\n",preco_vist);
		g_print("Preço Faturado: %s\n",preco_fat);
		
		sprintf(query,"select * from preco_cliente where grupo = %i and produto = %s and cliente = %s", ter_grupos_preco_code[cont],prods_ter,codigos_ter);
		
		if((res=consultar(query))==NULL)
		{
			popup(NULL,"Erro ao verificar conteudo do subgrupo");
			return 1;
		}

		if((row = mysql_fetch_row(res))==NULL)
		{
			sprintf(query,"insert into preco_cliente(produto,grupo,cliente,valor_fat,valor_vist) values(%s,%i,%s,%s,%s)",
			prods_ter,ter_grupos_preco_code[cont],codigos_ter,preco_fat,preco_vist);
		}
		else
		{
			sprintf(query,"update preco_cliente set valor_fat = %s, valor_vist = %s where produto = %s and grupo = %i and cliente = %s",
			preco_fat,preco_vist,codigos_ter,ter_grupos_preco_code[cont],codigos_ter);
		}
		
		if(enviar_query(query)!=0)
		{
			popup(NULL,"Erro ao atualizar conteudo do subgrupo");
			return 1;
		}
		
	}
	popup(NULL,"Preços vinculados ao subgrupo com sucesso");
	notebook_preco_ter_grupo();
	return 0;
}


int notebook_preco_ter_grupo()
{
	MYSQL_RES *res, *res2;
	MYSQL_ROW row, row2;
	int grupo_nivel=0;
	char query[MAX_QUERY_LEN];
	char *formatar_preco;
	formatar_preco = malloc(MAX_PRECO_LEN);
	grupos_ter_load = 1;
	if(code_terc()!=0)
	{
		return 1;
	}
	if(grupo_ter()!=0)
	{
		return 1;
	}
	
	grupos_ter_load=0;
	entry_preco_ter_grupo_label = malloc(MAX_SUBGRUPO*sizeof(GtkLabel));
	entry_preco_ter_grupo_prcvist = malloc(MAX_SUBGRUPO*sizeof(GtkEntry));
	entry_preco_ter_grupo_prcfat = malloc(MAX_SUBGRUPO*sizeof(GtkEntry));
	
	int cont=1;
	
	gtk_grid_remove_column (GTK_GRID(grid1_ter_grupo),0);
	gtk_grid_remove_column (GTK_GRID(grid1_ter_grupo),0);
	gtk_grid_remove_column (GTK_GRID(grid1_ter_grupo),0);
	
	gtk_grid_insert_column (GTK_GRID(grid1_ter_grupo),0);
	gtk_grid_insert_column (GTK_GRID(grid1_ter_grupo),1);
	gtk_grid_insert_column (GTK_GRID(grid1_ter_grupo),2);
		
	sprintf(query,"select code,nome from grupos where pai = '%s'",grupos_ter);

	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao verificar grupos para precos");
		return 1;
	}
	
	gtk_grid_attach(GTK_GRID(grid1_ter_grupo),gtk_label_new("À Vista"),1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid1_ter_grupo),gtk_label_new("Faturado"),2,0,1,1);
	
	ter_grupos_qnt=1;
	
	while((row = mysql_fetch_row(res))!=NULL)
	{
		ter_grupos_preco_code[ter_grupos_qnt] = atoi(row[0]);
		entry_preco_ter_grupo_label[ter_grupos_qnt] = gtk_button_new_with_label(row[1]);
		entry_preco_ter_grupo_prcvist[ter_grupos_qnt] = gtk_entry_new();
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry_preco_ter_grupo_prcvist[ter_grupos_qnt]),GTK_ENTRY_ICON_PRIMARY,"money");
		entry_preco_ter_grupo_prcfat[ter_grupos_qnt] = gtk_entry_new();
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry_preco_ter_grupo_prcfat[ter_grupos_qnt]),GTK_ENTRY_ICON_PRIMARY,"money");
		g_print("Verificando valores para o grupo %s na posicao %i\n", row[0],ter_grupos_qnt);
		sprintf(query,"select valor_fat, valor_vist from preco_cliente where grupo = %s and cliente = %s and produto = %s",row[0],codigos_ter,prods_ter);
		res2 = consultar(query);
		if(res2 == NULL)
		{
			popup(NULL,"Erro ao verificar grupos para precos");
			return 1;
		}		
		if((row2 = mysql_fetch_row(res2))!=NULL)
		{
			sprintf(formatar_preco,"%.2f",atof(row2[0]));
			gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_grupo_prcfat[ter_grupos_qnt]),formatar_preco);

			sprintf(formatar_preco,"%.2f",atof(row2[1]));
			gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_grupo_prcvist[ter_grupos_qnt]),formatar_preco);
		}
		else
		{
			gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_grupo_prcfat[ter_grupos_qnt]),"00.00");
			gtk_entry_set_text(GTK_ENTRY(entry_preco_ter_grupo_prcvist[ter_grupos_qnt]),"00.00");
		}
		
		gtk_grid_attach(GTK_GRID(grid1_ter_grupo),entry_preco_ter_grupo_label[ter_grupos_qnt],0,ter_grupos_qnt,1,1);
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry_preco_ter_grupo_prcvist[ter_grupos_qnt]),"R$ 00,00");
		gtk_grid_attach(GTK_GRID(grid1_ter_grupo),entry_preco_ter_grupo_prcvist[ter_grupos_qnt],1,ter_grupos_qnt,1,1);
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry_preco_ter_grupo_prcfat[ter_grupos_qnt]),"R$ 00,00");
		gtk_grid_attach(GTK_GRID(grid1_ter_grupo),entry_preco_ter_grupo_prcfat[ter_grupos_qnt],2,ter_grupos_qnt,1,1);
		ter_grupos_qnt++;
	}
	sprintf(query,"select nivel from grupos where code = '%s'",grupos_ter);
	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao verificar nivel do grupo usado");
		return 1;
	}
	if((row = mysql_fetch_row(res))!=NULL)
	{
		grupo_nivel = atoi(row[0])+1;
	}
	
	if(ter_grupos_qnt==1&&concluindo_ter==0)
	{
		gtk_grid_remove_column (GTK_GRID(grid1_ter_grupo),0);
		gtk_grid_remove_column (GTK_GRID(grid1_ter_grupo),0);
		gtk_grid_remove_column (GTK_GRID(grid1_ter_grupo),0);
		popup(NULL,"Nenhum subgrupo para o grupo");
		
	}
	
	gtk_widget_show_all(grid1_ter_grupo);
	return 0;
}
