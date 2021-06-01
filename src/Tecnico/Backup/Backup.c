int backup_fun(){

	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].reg_id = REG_BACKUP_WND;
	janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND]))
		return 1;

	gtk_widget_set_name(janela,"backups");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Backups");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"edit-paste");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  	gtk_widget_set_size_request(janela, 300,300);

  	

	janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].janela_pointer = janela;
	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND]);


	return 0;
}