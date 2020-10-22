GtkWidget *lista_abas, *frame_lista_abas;
GtkWidget *botao_iniciar;
int controle_menu=0;

int menu(void)
{

	GtkWidget *principal,  *principal_label;
	GtkWidget *cadastros,  *cadastros_label;
	GtkWidget *compras,    *compras_label;
	GtkWidget *faturamento,*faturamento_label;
	GtkWidget *estoque,    *estoque_label;
	GtkWidget *financeiro, *financeiro_label;
	GtkWidget *relatorios, *relatorios_label;
	GtkWidget *tecnicos, *tecnicos_label;

	GtkWidget *lembrete_box, *lembrete_fixed , *lembrete_ico, *lembrete_label;

	//aba principal
	GtkWidget *texto_sobre, *logo_img;
	gchar *texto;
	texto = malloc(2000);
	logo_img = gtk_image_new_from_file(LOGO);

	strcpy(texto,cad_emp_strc.sobre);

	principal    = gtk_box_new(1,0);
	cadastros    = gtk_box_new(1,0);
	compras      = gtk_box_new(1,0);
	faturamento  = gtk_box_new(1,0);
	estoque      = gtk_box_new(1,0);
	financeiro   = gtk_box_new(1,0);
	relatorios   = gtk_box_new(1,0);
	tecnicos     = gtk_box_new(1,0);

	lista_abas = gtk_notebook_new();
	frame_lista_abas = gtk_frame_new(NULL);

	principal_label   = gtk_label_new("PRINCIPAL");
	cadastros_label   = gtk_label_new("CADASTROS");
	faturamento_label = gtk_label_new("FATURAMENTO");
	compras_label     = gtk_label_new("COMPRAS");
	estoque_label     = gtk_label_new("ESTOQUE");
	financeiro_label  = gtk_label_new("FINANCEIRO");
	relatorios_label  = gtk_label_new("RELATÓRIOS");
	tecnicos_label  = gtk_label_new("FERRAMENTAS TÉCNICAS");

	texto_sobre = gtk_label_new(texto);
	gtk_widget_set_name(texto_sobre,"texto_sobre");
	gtk_label_set_selectable(GTK_LABEL(texto_sobre),TRUE);

/*
	lembrete_fixed = gtk_fixed_new();
	lembrete_box   = gtk_box_new(1,0);
	lembrete_ico   = gtk_image_new_from_file(LMB_IMG);
	lembrete_label = gtk_label_new("Lembretes");
	gtk_box_pack_start(GTK_BOX(lembrete_box),lembrete_ico,0,0,0);
	gtk_box_pack_start(GTK_BOX(lembrete_box),lembrete_label,0,0,0);
*/


	//inserindo abas
	gtk_widget_set_name(lista_abas,"menu");
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
	if(ativar.tecnicos)
		gtk_notebook_append_page(GTK_NOTEBOOK(lista_abas),tecnicos,tecnicos_label);

	gtk_notebook_set_current_page (GTK_NOTEBOOK(lista_abas),1);

	gtk_box_pack_start(GTK_BOX(principal),texto_sobre,0,0,0);
	gtk_box_pack_start(GTK_BOX(principal),logo_img,0,0,0);

	add_icones();
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(cadastros),cadastrosl[cont],0,0,20);
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(faturamento),faturamentol[cont],0,0,20);
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(compras),comprasl[cont],0,0,20);
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(financeiro),financeirol[cont],0,0,20);
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(estoque),estoquel[cont],0,0,20);
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(relatorios),relatoriosl[cont],0,0,20);
	for(cont=0;cont<LINE_ICO_QNT;cont++)
		gtk_box_pack_start(GTK_BOX(tecnicos),tecnicosl[cont],0,0,20);

	gtk_widget_set_size_request(GTK_WIDGET(lista_abas),631,600);

	gtk_container_add(GTK_CONTAINER(frame_lista_abas),lista_abas);

	gtk_frame_set_shadow_type(GTK_FRAME(frame_lista_abas),GTK_SHADOW_ETCHED_OUT); //GTK_SHADOW_ETCHED_OUT || GTK_SHADOW_ETCHED_IN
	return 0;
}

int tecla_menu(GtkWidget *widget,GdkEventKey *evento)
{
	switch(evento->keyval)
	{
		case (ABRIR_MENU_TECLA):
			if(controle_menu)
			{
				gtk_widget_hide(lista_abas);
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Menu");
				controle_menu=0;
			}
			else
			{
				gtk_widget_show_all(lista_abas);
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Fecha");
				controle_menu=1;
			}
			break;
	}
	return 0;
}
