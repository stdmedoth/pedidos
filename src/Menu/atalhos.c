void chama_menu(GtkWidget *widget){

	if(!aplicacao_inicializada())
		return ;

	GdkEventKey  event;
	event.keyval = ABRIR_MENU_TECLA;
	tecla_menu(widget, &event, NULL);
}

gboolean tecla_menu(GtkWidget *widget, GdkEventKey  *event, gpointer   user_data){

	if(!aplicacao_inicializada())
		return FALSE;

	switch(event->keyval){

		case ABRIR_MENU_TECLA:
			if(controle_menu){
				if(menu_notebook && GTK_IS_WIDGET(menu_notebook))
					menu_notebook_atual_pos = gtk_notebook_get_current_page(GTK_NOTEBOOK(menu_notebook));
				gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[REG_MENU_WND].janela_pointer);
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Menu");
				gtk_widget_set_sensitive(janela_principal, TRUE);
				controle_menu=0;
			}
			else{
				janelas_gerenciadas.vetor_janelas[REG_MENU_WND].fun();
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Fecha");
				gtk_widget_set_sensitive(janela_principal, FALSE);
				controle_menu=1;
			}
			break;

		case SAIR_MENU_TECLA:
			if(controle_menu){
				if(menu_notebook && GTK_IS_WIDGET(menu_notebook))
					menu_notebook_atual_pos = gtk_notebook_get_current_page(GTK_NOTEBOOK(menu_notebook));
				gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[REG_MENU_WND].janela_pointer);
				gtk_button_set_label(GTK_BUTTON(botao_iniciar),"Menu");
				gtk_widget_set_sensitive(janela_principal, TRUE);
				controle_menu=0;
			}
			break;
	}

	return FALSE;
}
