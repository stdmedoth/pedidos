GtkWidget *lista_abas;
GtkWidget *botao_iniciar;
int controle_menu=0;
//modulos ativos
struct modulos
{
	int cadastro;
	int compras;
	int faturamento;
	int estoque;
	int financeiro;
	int relatorios;
}ativar;
int menu()
{	
	
	ativar.cadastro=1;
	ativar.compras=0;
	ativar.faturamento=1;
	ativar.estoque=1;
	ativar.financeiro=0;
	ativar.relatorios=1;
	
	GtkWidget *principal,  *principal_label;
	GtkWidget *cadastros,  *cadastros_label;
	GtkWidget *compras,    *compras_label;
	GtkWidget *faturamento,*faturamento_label;
	GtkWidget *estoque,    *estoque_label;
	GtkWidget *financeiro, *financeiro_label;
	GtkWidget *relatorios, *relatorios_label;
	
	GtkWidget *lembrete_box, *lembrete_fixed , *lembrete_ico, *lembrete_label;
	
	//aba principal
	GtkWidget *texto_principal;
	gchar *texto;
	texto = malloc(2000);
	//pegar mensagem
	FILE *arquivo;
	int pos=0,leitor=0,cont=0;
	arquivo = fopen(MSG_PRINC,"r");
	if(arquivo!=NULL)
	{
		while(leitor!=-1)
		{
			leitor = fgetc(arquivo);
			if(leitor==-1)
				break;
			printf("%i ",leitor);
			texto[pos] = leitor;
			if(pos>1999)
				break;
			pos++;
		}

		texto[strlen(texto)-29] = 0;
	}
	else
	{
		texto = "\n\n\n\n\
 O ERP Calisto é um software responsável por auxiliar\n\
 no gerenciamento de sua empresa,o sistema tem como\n\
 intuito, te dar uma melhor visão do que ocorre na sua empresa,\n\
 fornecer previsões e analisar os resultados, com o Calisto\n\
 a gestão da sua empresa estará bem organizada, de maneira segura e previsivel\n";	
	}
	principal    = gtk_box_new(1,0);
	cadastros    = gtk_box_new(1,0);
	compras      = gtk_box_new(1,0);
	faturamento  = gtk_box_new(1,0);
	estoque      = gtk_box_new(1,0);
	financeiro   = gtk_box_new(1,0);
	relatorios   = gtk_box_new(1,0);
	
		
	lista_abas = gtk_notebook_new();

	principal_label   = gtk_label_new("PRINCIPAL");
	cadastros_label   = gtk_label_new("CADASTROS");
	faturamento_label = gtk_label_new("FATURAMENTO");
	compras_label     = gtk_label_new("COMPRAS");
	estoque_label     = gtk_label_new("ESTOQUE");
	financeiro_label  = gtk_label_new("FINANCEIRO");
	relatorios_label  = gtk_label_new("RELATÓRIOS");
	
	texto_principal = gtk_label_new(texto);	

	lembrete_fixed = gtk_fixed_new();
	lembrete_box   = gtk_box_new(1,0);
	lembrete_ico   = gtk_image_new_from_file(LMB_IMG);
	lembrete_label = gtk_label_new("Lembretes");
	
	gtk_box_pack_start(GTK_BOX(lembrete_box),lembrete_ico,0,0,0);
	gtk_box_pack_start(GTK_BOX(lembrete_box),lembrete_label,0,0,0);
	gtk_fixed_put(GTK_FIXED(lembrete_fixed),lembrete_box,200,100);
	
	//inserindo abas

	gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),principal,principal_label);
	if(ativar.cadastro)
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),cadastros,cadastros_label);
	if(ativar.compras)	
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),compras,compras_label);
	if(ativar.faturamento)
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),faturamento,faturamento_label);
	if(ativar.estoque)
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),estoque,estoque_label);
	if(ativar.financeiro)
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),financeiro,financeiro_label);
	if(ativar.relatorios)
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),relatorios,relatorios_label); 
	gtk_notebook_set_current_page (GTK_NOTEBOOK(lista_abas),1);
	gtk_box_pack_start(GTK_BOX(principal),texto_principal,0,0,0);
	gtk_box_pack_start(GTK_BOX(principal),lembrete_fixed,0,0,0);
	add_icones();
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(cadastros),cadastrosl[cont],0,0,20);
	gtk_box_pack_start(GTK_BOX(compras),comprasl[0],0,0,20);
	gtk_widget_set_size_request(GTK_WIDGET(lista_abas),631,600);
	
	return 0;
}

int tecla_menu(GtkWidget *widget,GdkEventKey *evento)
{
	switch(evento->keyval)
	{
		case (GDK_KEY_Alt_L):
			if(controle_menu)
			{
				gtk_widget_hide(lista_abas);
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Menu");
				controle_menu=0;
			}	
			else
			{
				gtk_widget_show_all(lista_abas);
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"|----> ");
				controle_menu=1;	
			}
			break;	
	}	
	return 0;
}

int clique_menu()
{
	if(controle_menu)
	{
		gtk_widget_hide(lista_abas);
		gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Menu");
		controle_menu=0;
	}	
	else
	{
		gtk_widget_show_all(lista_abas);
		gtk_button_set_label(GTK_BUTTON(botao_iniciar),"|---> ");
		controle_menu=1;	
		gtk_widget_grab_focus(principall[0]);
	}
	return 0;
}
