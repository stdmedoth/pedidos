int relat_fix_prod(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].reg_id = REG_REL_FIX_PROD_WIN;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].janela_pointer = janela;

  gtk_widget_set_name(janela,"relat-produtos");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Relatório Fixo de Produtos");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"system-software-install");

  if(personalizacao.janela_keep_above==1)
    gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);

  gtk_widget_set_size_request(janela,800,500);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN]);

  gtk_widget_show_all(janela);
  return 0;
}
