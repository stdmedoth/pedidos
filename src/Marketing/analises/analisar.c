int mkt_analise(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"Análise de Marketing");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Análise de Marketing");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);

	janelas_gerenciadas.vetor_janelas[REG_ANLMKT_WND].reg_id = REG_ANLMKT_WND;
	janelas_gerenciadas.vetor_janelas[REG_ANLMKT_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_ANLMKT_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_ANLMKT_WND].janela_pointer = janela;

  gtk_widget_show_all(janela);

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_ANLMKT_WND]);

  return 0;
}
