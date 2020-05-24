static GtkWidget **entry_preco_grupo_label;
static GtkWidget **entry_preco_grupo_prcvist;
static GtkWidget **entry_preco_grupo_prcfat;
static GtkWidget *grid1_grupo=NULL;
static int grupos_qnt=1;
GtkWidget *notebook_preco_grupo();
static int grupos_preco_code[MAX_SUBGRUPO];
int preco_faturado()
{
	
	return 0;
}

int insere_preco_grupos()
{

	MYSQL_RES *res;
	MYSQL_ROW row;
	int cont=1;
	char query[MAX_QUERY_LEN];
	gchar *preco_fat=NULL, *preco_vist=NULL;
	
	preco_fat = malloc(MAX_PRECO_LEN);
	preco_vist = malloc(MAX_PRECO_LEN);	
	
	if(code_prod()!=0)
	{
		return 1;
	}
	
	sprintf(query,"select * from produtos where code = %s",codigos_prod);
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

	g_print("Há %i grupos para serem inserido os preços\n",grupos_qnt);
	
	for(cont=1;cont<grupos_qnt;cont++)
	{
		preco_fat = (gchar*) gtk_entry_get_text(GTK_ENTRY(entry_preco_grupo_prcfat[cont]));
		preco_vist = (gchar*) gtk_entry_get_text(GTK_ENTRY(entry_preco_grupo_prcvist[cont]));
		if(critica_real(preco_fat, entry_preco_grupo_prcfat[cont])!=0)
		{
			gtk_widget_grab_focus(entry_preco_grupo_prcfat[cont]);
			return 1;
		}	
		
		if(critica_real(preco_vist, entry_preco_grupo_prcvist[cont])!=0)
		{
			gtk_widget_grab_focus(entry_preco_grupo_prcvist[cont]);
			return 1;
		}		
		g_print("_get_ valores para o grupo %i na posicao %i\n", grupos_preco_code[cont],cont);		
				
		g_print("Grupo código: %i\n",grupos_preco_code[cont]);
		g_print("Preço à Vista: %s\n",preco_vist);
		g_print("Preço Faturado: %s\n",preco_fat);
		
		sprintf(query,"select * from preco_grupo where grupo = %i and produto = %s",
		grupos_preco_code[cont],codigos_prod);
		if((res=consultar(query))==NULL)
		{
			popup(NULL,"Erro ao verificar conteudo do subgrupo");
			return 1;
		}

		if((row = mysql_fetch_row(res))==NULL)
		{
			sprintf(query,"insert into preco_grupo(produto,grupo,valor_fat,valor_vist) values(%s,%i,%s,%s)",
			codigos_prod,grupos_preco_code[cont],preco_fat,preco_vist);
		}
		else
		{
			sprintf(query,"update preco_grupo set valor_fat = %s, valor_vist = %s where produto = %s and grupo = %i ",
			preco_fat,preco_vist,codigos_prod,grupos_preco_code[cont]);
		}
		
		if(enviar_query(query)!=0)
		{
			popup(NULL,"Erro ao atualizar conteudo do subgrupo");
			return 1;
		}
		
	}
	popup(NULL,"Preços vinculados ao subgrupo com sucesso");
	notebook_preco_grupo();
	return 0;
}


GtkWidget *notebook_preco_grupo()
{
	MYSQL_RES *res, *res2;
	MYSQL_ROW row, row2;
	char query[MAX_QUERY_LEN];
	char *formatar_preco;
	formatar_preco = malloc(MAX_PRECO_LEN);
	
	if(code_prod()!=0)
	{
		return NULL;
	}
	
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
		
	sprintf(query,"select code,nome from grupos where pai = '%s'",grupos_prod);

	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao verificar grupos para precos");
		return NULL;
	}
	
	gtk_grid_attach(GTK_GRID(grid1_grupo),gtk_label_new("À Vista"),1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid1_grupo),gtk_label_new("Faturado"),2,0,1,1);
	
	grupos_qnt=1;
	
	while((row = mysql_fetch_row(res))!=NULL)
	{
		grupos_preco_code[grupos_qnt] = atoi(row[0]);
		entry_preco_grupo_label[grupos_qnt] = gtk_button_new_with_label(row[1]);
		entry_preco_grupo_prcvist[grupos_qnt] = gtk_entry_new();
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry_preco_grupo_prcvist[grupos_qnt]),GTK_ENTRY_ICON_PRIMARY,"money");
		entry_preco_grupo_prcfat[grupos_qnt] = gtk_entry_new();
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry_preco_grupo_prcfat[grupos_qnt]),GTK_ENTRY_ICON_PRIMARY,"money");
		g_print("Verificando valores para o grupo %s na posicao %i\n", row[0],grupos_qnt);
		sprintf(query,"select valor_fat, valor_vist from preco_grupo where grupo = %s and produto = %s",row[0],codigos_prod);
		res2 = consultar(query);
		if(res2 == NULL)
		{
			popup(NULL,"Erro ao verificar grupos para precos");
			return NULL;
		}		
		if((row2 = mysql_fetch_row(res2))!=NULL)
		{
			sprintf(formatar_preco,"%.2f",atof(row2[0]));
			gtk_entry_set_text(GTK_ENTRY(entry_preco_grupo_prcfat[grupos_qnt]),formatar_preco);

			sprintf(formatar_preco,"%.2f",atof(row2[1]));
			gtk_entry_set_text(GTK_ENTRY(entry_preco_grupo_prcvist[grupos_qnt]),formatar_preco);
		}
		else
		{
			gtk_entry_set_text(GTK_ENTRY(entry_preco_grupo_prcfat[grupos_qnt]),"00.00");
			gtk_entry_set_text(GTK_ENTRY(entry_preco_grupo_prcvist[grupos_qnt]),"00.00");
		}
		
		gtk_grid_attach(GTK_GRID(grid1_grupo),entry_preco_grupo_label[grupos_qnt],0,grupos_qnt,1,1);
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry_preco_grupo_prcvist[grupos_qnt]),"R$ 00,00");
		gtk_grid_attach(GTK_GRID(grid1_grupo),entry_preco_grupo_prcvist[grupos_qnt],1,grupos_qnt,1,1);
		gtk_entry_set_placeholder_text(GTK_ENTRY(entry_preco_grupo_prcfat[grupos_qnt]),"R$ 00,00");
		gtk_grid_attach(GTK_GRID(grid1_grupo),entry_preco_grupo_prcfat[grupos_qnt],2,grupos_qnt,1,1);
		grupos_qnt++;
	}
	sprintf(query,"select nivel from grupos where code = '%s'",grupos_prod);
	res = consultar(query);
	if(res == NULL)
	{
		popup(NULL,"Erro ao verificar nivel do grupo usado");
		return NULL;
	}
	if((row = mysql_fetch_row(res))!=NULL)
	{
		grupo_nivel = atoi(row[0])+1;
	}
	
	if(grupos_qnt==1&&concluindo_prod==0)
	{
		gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
		gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
		gtk_grid_remove_column (GTK_GRID(grid1_grupo),0);
		popup(NULL,"Nenhum subgrupo para o grupo");
		
	}
	gtk_widget_show_all(grid1_grupo);
	return grid1_grupo;
}
