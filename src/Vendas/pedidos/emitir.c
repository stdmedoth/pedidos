int emitir_ped()
{
	GtkWidget *janela;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	
	

	gtk_widget_show_all(janela);
	return 0;
}



