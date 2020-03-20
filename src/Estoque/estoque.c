int cad_est()
{
	GtkWidget *janela;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Estoque");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_widget_set_size_request(GTK_WIDGET(janela),940,470);
	gtk_widget_show_all(janela);
	
	return 0;
}

