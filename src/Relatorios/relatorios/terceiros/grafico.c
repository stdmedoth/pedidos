int relat_ter_grafico_fun(){

  GtkWidget *janela_grafico = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *treeview, *scroll, *box;

  gtk_widget_set_name(janela_grafico,"graf_ter_relat");
	gtk_window_set_position(GTK_WINDOW(janela_grafico),3);
	gtk_window_set_resizable(GTK_WINDOW(janela_grafico),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela_grafico),"Relatório de Terceiros");
	gtk_window_set_icon_name(GTK_WINDOW(janela_grafico),"system-software-install");
	gtk_window_set_transient_for(GTK_WINDOW(janela_grafico),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela_grafico), 10);

  char query[MAX_QUERY_LEN];
  sprintf(query,"select b.nome, b.tipo_dado from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s", relat_ter_codigo_gchar);
  treeview = get_relat_treeview(query, relat_ter_query_gchar);
  if(!treeview)
    return 1;
  box = gtk_box_new(0,0);
  scroll = gtk_scrolled_window_new(NULL,NULL);

  gtk_container_add(GTK_CONTAINER(scroll), treeview);
  gtk_box_pack_start(GTK_BOX(box), scroll,0,0,0);
  gtk_container_add(GTK_CONTAINER(janela_grafico), box);

  gtk_widget_set_size_request(treeview, 800, 300);
  gtk_widget_set_size_request(scroll, 800, 300);
  gtk_widget_set_size_request(box, 800, 300);

  gtk_widget_show_all(janela_grafico);
  return 0;
}
