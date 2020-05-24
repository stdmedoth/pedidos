int cancelar_ped()
{
	GtkWidget *janela;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Cancelar");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"");
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	gtk_widget_set_size_request(janela,600,500);

	gtk_widget_show_all(janela);
	return 0;	
}
