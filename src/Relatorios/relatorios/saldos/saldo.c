void relat_sld_fun()
{
	GtkWidget *janela;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	
	
	gtk_widget_set_size_request(janela,500,300);
	gtk_widget_show_all(janela);
}
