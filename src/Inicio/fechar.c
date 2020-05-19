int encerrar(GtkWidget *buttton,gpointer parent)
{
	GtkWidget * mensagem;
	int resultado;
	mensagem = gtk_dialog_new_with_buttons("Sair?",GTK_WINDOW(parent),GTK_DIALOG_DESTROY_WITH_PARENT,"Sim",GTK_RESPONSE_ACCEPT,"Não",GTK_RESPONSE_REJECT,NULL);
	gtk_window_set_icon_name(GTK_WINDOW(janela_grupo),"system-log-out");
	gtk_window_set_position(GTK_WINDOW(mensagem),3);
	gtk_window_set_keep_above(GTK_WINDOW(mensagem),TRUE);
	resultado = gtk_dialog_run(GTK_DIALOG(mensagem));
	switch(resultado)
	{
		case GTK_RESPONSE_ACCEPT:
			encerrando();
			break;
		default: 
			
			break;
	}
	
	gtk_widget_destroy(mensagem);
	return 0;
}
