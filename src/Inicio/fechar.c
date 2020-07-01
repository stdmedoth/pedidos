#define GTK_RESPONSE_RESTART 3
int init();
int encerrar(GtkWidget *buttton,GtkWindow *parent)
{
	GtkWidget * mensagem;
	GtkWidget *sair_label,*sair_box,*sair_fixed;
	int resultado;
	mensagem = gtk_dialog_new_with_buttons("Sair?",NULL,4,"Sim",GTK_RESPONSE_ACCEPT,"Não",GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_icon_name(GTK_WINDOW(mensagem),"system-log-out");
	gtk_window_set_position(GTK_WINDOW(mensagem),3);
	gtk_window_set_keep_above(GTK_WINDOW(mensagem),TRUE);

	sair_label = gtk_label_new("Você deseja realmente sair ?");
	sair_fixed = gtk_fixed_new();
	sair_box = gtk_bin_get_child(GTK_BIN(mensagem));
	gtk_dialog_set_default_response(GTK_DIALOG(mensagem),GTK_RESPONSE_REJECT);
	gtk_box_pack_start(GTK_BOX(sair_box),sair_label,0,0,10);

	gtk_widget_show_all(mensagem);

	resultado = gtk_dialog_run(GTK_DIALOG(mensagem));
	switch(resultado)
	{
		case GTK_RESPONSE_ACCEPT:
			encerrando();
			break;
		case GTK_RESPONSE_REJECT:

			break;
	}

	gtk_widget_destroy(mensagem);
	return 0;
}
