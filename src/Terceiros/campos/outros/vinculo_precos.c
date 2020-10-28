static GtkWidget *entry_preco_ter_label;
static GtkWidget *entry_preco_ter_prcvist;
static GtkWidget *entry_preco_ter_prcfat;
static GtkWidget *grid1_ter_preco=NULL;
static int ter_grupos_qnt=1;
static int grupos_ter_load=0;

int produto_ter();
int notebook_preco_ter();


int insere_preco_ter()
{
	//atualiza o banco de dados com os precos inseridos pelo usuario no cadastro de terceiros
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
		popup(NULL,"O produto não existe");
		return 1;
	}

	sprintf(query,"select * from terceiros where code = %s",codigos_ter);
	if((res=consultar(query))==NULL)
	{
		popup(NULL,"Erro ao verificar existencia do cliente");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"O cliente não existe! Verifique o código");
		gtk_widget_grab_focus(code_ter_field);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		return 1;
	}

	g_print("Há %i grupos para serem inserido os preços\n",ter_grupos_qnt);

	preco_fat = (gchar*) gtk_entry_get_text(GTK_ENTRY(entry_preco_ter_prcfat));
	preco_vist = (gchar*) gtk_entry_get_text(GTK_ENTRY(entry_preco_ter_prcvist));
	if(critica_real(preco_fat, entry_preco_ter_prcfat)!=0)
	{
		gtk_widget_grab_focus(entry_preco_ter_prcfat);
		return 1;
	}

	if(critica_real(preco_vist, entry_preco_ter_prcvist)!=0)
	{
		gtk_widget_grab_focus(entry_preco_ter_prcvist);
		return 1;
	}

	sprintf(query,"select * from preco_cliente where produto = %s and cliente = %s",prods_ter,codigos_ter);

	if((res=consultar(query))==NULL)
	{
		popup(NULL,"Erro ao verificar conteudo do subgrupo");
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL)
	{
		sprintf(query,"insert into preco_cliente(produto,cliente,valor_fat,valor_vist) values(%s,%s,%s,%s)",
		prods_ter,codigos_ter,preco_fat,preco_vist);
	}
	else
	{
		sprintf(query,"update preco_cliente set valor_fat = %s, valor_vist = %s where produto = %s and cliente = %s",
		preco_fat,preco_vist,codigos_ter,codigos_ter);
	}

	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao atualizar conteudo do subgrupo");
		return 1;
	}

	popup(NULL,"Preços vinculados ao subgrupo com sucesso");
	return 0;
}

GtkWidget *criar_precos_ter_wnd(){
	GtkWidget *caixa = gtk_box_new(0,0);
	entry_preco_ter_label = gtk_label_new("Preços");
	entry_preco_ter_prcfat = gtk_entry_new();
	entry_preco_ter_prcvist = gtk_entry_new();

	gtk_box_pack_start(GTK_BOX(caixa),entry_preco_ter_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa),entry_preco_ter_prcfat,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa),entry_preco_ter_prcvist,0,0,5);
	g_signal_connect(entry_preco_ter_prcfat,"activate",G_CALLBACK(passar_campo),entry_preco_ter_prcvist);
	g_signal_connect(entry_preco_ter_prcvist,"activate",G_CALLBACK(passar_campo),entry_preco_ter_prcfat);
	return caixa;
}
