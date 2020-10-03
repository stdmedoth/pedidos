extern GtkWidget *botao_iniciar;
extern GtkWidget *imagem_barra;
extern GtkWidget *layout_barra;
extern GtkWidget *lista_abas, *frame_lista_abas;
extern int controle_menu;
extern void botao_encerrar();
extern void fechar_sessao();
static int notificacao_pendencias=0;

int clique_menu(void)
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
		gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Fecha");
		controle_menu=1;
	}

	return 0;
}


int barra_icones_add(){

  return 0;
}


int *barra_icones_rem(){

  return 0;
}

GtkWidget *barra_icones_wnd(){

	GtkWidget *penden_button, *param_button, *sair_button, *logoff_button, *suport_button;

  penden_button = gtk_button_new();

  if(!notificacao_pendencias)
    gtk_button_set_image(GTK_BUTTON(penden_button),gtk_image_new_from_icon_name("emblem-generic",GTK_ICON_SIZE_DIALOG));
  else
    gtk_button_set_image(GTK_BUTTON(penden_button),gtk_image_new_from_icon_name("emblem-important",GTK_ICON_SIZE_DIALOG));

	param_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(param_button),gtk_image_new_from_icon_name("emblem-system",GTK_ICON_SIZE_DIALOG));

	sair_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(sair_button),gtk_image_new_from_icon_name("application-exit",GTK_ICON_SIZE_DIALOG));

	logoff_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(logoff_button),gtk_image_new_from_icon_name("emblem-synchronizing",GTK_ICON_SIZE_DIALOG));

	suport_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(suport_button),gtk_image_new_from_icon_name("system-help",GTK_ICON_SIZE_DIALOG));


  imagem_barra = gtk_box_new(1,0);
	gtk_widget_set_name(imagem_barra,"barra");
	layout_barra  = gtk_layout_new(NULL,NULL);
	botao_iniciar = gtk_button_new_with_label("Menu");
	gtk_button_set_image(GTK_BUTTON(botao_iniciar),gtk_image_new_from_icon_name("help-contents",GTK_ICON_SIZE_SMALL_TOOLBAR));
  gtk_widget_set_name(botao_iniciar,"botao_iniciar");

  /*basicos*/
  gtk_layout_put(GTK_LAYOUT(layout_barra),imagem_barra,0,0);
  gtk_layout_put(GTK_LAYOUT(layout_barra),botao_iniciar,0,1);

  /*ferramentas*/
  gtk_layout_put(GTK_LAYOUT(layout_barra),penden_button,0,60);
  gtk_layout_put(GTK_LAYOUT(layout_barra),suport_button,0,120);
  gtk_layout_put(GTK_LAYOUT(layout_barra),param_button,0,180);

  /*sessao*/
  gtk_layout_put(GTK_LAYOUT(layout_barra),logoff_button,0,590);
  gtk_layout_put(GTK_LAYOUT(layout_barra),sair_button,0,650);

  gtk_widget_set_size_request(GTK_WIDGET(botao_iniciar),75,60);
  gtk_widget_set_size_request(GTK_WIDGET(penden_button),75,60);
  gtk_widget_set_size_request(GTK_WIDGET(param_button),75,60);
  gtk_widget_set_size_request(GTK_WIDGET(logoff_button),75,60);
  gtk_widget_set_size_request(GTK_WIDGET(sair_button),75,60);
  gtk_widget_set_size_request(GTK_WIDGET(suport_button),75,60);


  g_signal_connect(GTK_WIDGET(botao_iniciar),"clicked",G_CALLBACK(clique_menu),NULL);

  g_signal_connect(GTK_BUTTON(sair_button),"clicked",G_CALLBACK(botao_encerrar),janela_principal);

	g_signal_connect(GTK_BUTTON(penden_button),"clicked",G_CALLBACK(notificacoes_wnd),NULL);

  g_signal_connect(GTK_BUTTON(param_button),"clicked",G_CALLBACK(parametrizar),NULL);

  g_signal_connect(GTK_BUTTON(suport_button),"clicked",G_CALLBACK(suporte_princ_wnd),NULL);

  g_signal_connect(GTK_BUTTON(logoff_button),"clicked",G_CALLBACK(fechar_sessao),NULL);


  gtk_widget_set_size_request(layout_barra,80,750);

  gtk_widget_show_all(layout_barra);

  return layout_barra;

}
