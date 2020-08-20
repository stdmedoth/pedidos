int rel_fix_fin_rec(){

  GtkWidget *janela;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"relatorio");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Relatório de Títulos à Receber");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"money");
	gtk_window_set_transient_for(GTK_WINDOW(janela),
  GTK_WINDOW(janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].janela_pointer));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	gtk_widget_set_size_request(janela,800,600);

	janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].reg_id = REG_REL_FIX_EST_WIN;
	janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].janela_pointer = janela;



  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN]);
  return 0;
}
