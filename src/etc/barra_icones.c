int clique_menu(void){

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

	return 0;
}


int barra_icones_add(gchar *Nome, int (*funcao) ()){
	GtkWidget *novo_icone = gtk_button_new();
	GtkWidget *img;
	if(!fopen(Nome, "r")){
		img = gtk_image_new_from_icon_name(Nome, GTK_ICON_SIZE_DIALOG);
	}else{
		img = gtk_image_new_from_file(Nome);
	}
	gtk_button_set_image(GTK_BUTTON(novo_icone), img);
	gtk_widget_set_size_request(GTK_WIDGET(novo_icone),75,60);
	gtk_widget_set_name(novo_icone,"bar_buttons_tertiary");
	g_signal_connect(GTK_BUTTON(novo_icone),"clicked",G_CALLBACK(funcao),NULL);

	if(ativar.ativo){
		gtk_layout_put(GTK_LAYOUT(layout_barra),novo_icone,0,ULT_BARRA_POS);
	}
  return 0;
}


int *barra_icones_rem(){

  return 0;
}

GtkWidget *penden_button, *param_button, *sair_button, *debug_button, *logoff_button, *suport_button, *kanban_button;

GtkWidget *barra_icones_wnd(){

	ult_barra_pos = 0;

	penden_button = gtk_button_new();

	notificacoes_button_update();

	param_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(param_button),gtk_image_new_from_icon_name("emblem-system",GTK_ICON_SIZE_DIALOG));

	suport_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(suport_button),gtk_image_new_from_icon_name("system-help",GTK_ICON_SIZE_DIALOG));

	kanban_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(kanban_button),gtk_image_new_from_icon_name("emblem-documents",GTK_ICON_SIZE_DIALOG));

	sair_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(sair_button),gtk_image_new_from_icon_name("application-exit",GTK_ICON_SIZE_DIALOG));

	logoff_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(logoff_button),gtk_image_new_from_icon_name("emblem-synchronizing",GTK_ICON_SIZE_DIALOG));

	debug_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(debug_button),gtk_image_new_from_icon_name("preferences-system",GTK_ICON_SIZE_DIALOG));

	gtk_widget_set_name(penden_button,"bar_buttons_secondary");
	gtk_widget_set_name(param_button,"bar_buttons_secondary");
	gtk_widget_set_name(sair_button,"bar_buttons_cancell");
	gtk_widget_set_name(debug_button,"bar_buttons_secondary");
	gtk_widget_set_name(logoff_button,"bar_buttons_cancell");
	gtk_widget_set_name(suport_button,"bar_buttons_secondary");
	gtk_widget_set_name(kanban_button,"bar_buttons_secondary");

  imagem_barra = gtk_box_new(1,0);
	gtk_widget_set_name(imagem_barra,"barra");
	layout_barra  = gtk_layout_new(NULL,NULL);
	botao_iniciar = gtk_button_new_with_label("Menu");
	gtk_widget_set_name(botao_iniciar,"bar_buttons_princ");
	gtk_button_set_image(GTK_BUTTON(botao_iniciar),gtk_image_new_from_icon_name("help-contents",GTK_ICON_SIZE_SMALL_TOOLBAR));

	/*basicos*/
  gtk_layout_put(GTK_LAYOUT(layout_barra),imagem_barra,0,0);
  gtk_layout_put(GTK_LAYOUT(layout_barra),botao_iniciar,0,1);

	if(ativar.financeiro)
		gtk_layout_put(GTK_LAYOUT(layout_barra),penden_button,0,ULT_BARRA_POS);

	if(ativar.ativo){
		/*ferramentas*/
		if(sessao_oper.nivel >= NIVEL_CRIADOR)
			gtk_layout_put(GTK_LAYOUT(layout_barra),debug_button,0,ULT_BARRA_POS);

	  gtk_layout_put(GTK_LAYOUT(layout_barra),suport_button,0,ULT_BARRA_POS);
		if(sessao_oper.nivel >= NIVEL_TATICO)
			gtk_layout_put(GTK_LAYOUT(layout_barra),param_button,0,ULT_BARRA_POS);
		gtk_layout_put(GTK_LAYOUT(layout_barra),kanban_button,0,ULT_BARRA_POS);

	}

	struct _maquina *maquina = maquinas_get_atual();
	if(maquina){
		struct _caixa *caixa = caixa_get_aberto(maquina);
		if(caixa->status == CAIXA_ABERTO && ativar.faturamento)
			barra_icones_add(CX_BAR_IMG, pdv_princ_wnd);
	}

	barra_icones_add("help-about", info_sobre_wnd);

  /*sessao*/
  gtk_layout_put(GTK_LAYOUT(layout_barra),logoff_button,0,590);
  gtk_layout_put(GTK_LAYOUT(layout_barra),sair_button,0,650);

	gtk_widget_set_size_request(GTK_WIDGET(botao_iniciar),75,60);

	gtk_widget_set_size_request(GTK_WIDGET(penden_button),75,60);

	gtk_widget_set_size_request(GTK_WIDGET(debug_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(suport_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(param_button),75,60);
	gtk_widget_set_size_request(GTK_WIDGET(kanban_button),75,60);

	gtk_widget_set_size_request(GTK_WIDGET(logoff_button),75,60);
  gtk_widget_set_size_request(GTK_WIDGET(sair_button),75,60);


  g_signal_connect(GTK_WIDGET(botao_iniciar),"clicked",G_CALLBACK(clique_menu),NULL);

  g_signal_connect(GTK_BUTTON(sair_button),"clicked",G_CALLBACK(botao_encerrar),janela_principal);

	g_signal_connect(GTK_BUTTON(penden_button),"clicked",G_CALLBACK(notificacoes_wnd),NULL);

  g_signal_connect(GTK_BUTTON(param_button),"clicked",G_CALLBACK(parametrizar),NULL);

	g_signal_connect(GTK_BUTTON(kanban_button),"clicked",G_CALLBACK(kanban_princ_wnd),NULL);

	g_signal_connect(GTK_BUTTON(suport_button),"clicked",G_CALLBACK(suporte_princ_wnd),NULL);

  g_signal_connect(GTK_BUTTON(logoff_button),"clicked",G_CALLBACK(fechar_sessao),NULL);

	g_signal_connect(GTK_BUTTON(debug_button),"clicked",G_CALLBACK(ativar_debug_fun),NULL);

  gtk_widget_set_size_request(layout_barra,80,750);

  gtk_widget_show_all(layout_barra);

  return layout_barra;

}
