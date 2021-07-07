int planilha_icon_view_wnd(){

  int N_COLUMNS=4;
  planilha_relats_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *search_entry = gtk_search_entry_new() ;
  GtkTreeIter iter;
  GtkTreeStore *modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,GDK_TYPE_PIXBUF,G_TYPE_INT, G_TYPE_INT);
  GtkWidget *icon_view = gtk_icon_view_new();

  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_ICONS_WIN].reg_id = REG_REL_PLANL_ICONS_WIN;
  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_ICONS_WIN].aberta = 1;
  if(ger_janela_aberta(planilha_relats_wnd, &janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_ICONS_WIN]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_ICONS_WIN].janela_pointer = planilha_relats_wnd;

  gtk_widget_set_name(planilha_relats_wnd,"relat-fixos");
  gtk_window_set_position(GTK_WINDOW(planilha_relats_wnd),3);
  gtk_window_set_resizable(GTK_WINDOW(planilha_relats_wnd),FALSE);
  gtk_window_set_title(GTK_WINDOW(planilha_relats_wnd),"Relatórios Planilhas");
  gtk_window_set_icon_name(GTK_WINDOW(planilha_relats_wnd),"text-x-generic");
  gtk_window_set_transient_for(GTK_WINDOW(planilha_relats_wnd),GTK_WINDOW(janela_principal));

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
    0,janelas_nomes[REG_REL_PLANL_TER_WIN],
    1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_PLANL_TER_IMG))),
    2,REG_REL_PLANL_TER_WIN,
    3,PLANL_MOD_TERCEIROS,
    -1);

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
    0,janelas_nomes[REG_REL_PLANL_PRODS_WIN],
    1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_PLANL_PROD_IMG))),
    2,REG_REL_PLANL_PRODS_WIN,
    3,PLANL_MOD_PRODUTOS,
    -1);

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
    0,janelas_nomes[REG_REL_PLANL_MOV_WIN],
    1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_PLANL_MOV_IMG))),
    2,REG_REL_PLANL_MOV_WIN,
    3,PLANL_MOD_MOVIMENTOS,
    -1);

  gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view),GTK_TREE_MODEL(modelo));
  //gtk_icon_view_set_activate_on_single_click(GTK_ICON_VIEW(icon_view),TRUE);

  gtk_icon_view_set_columns (GTK_ICON_VIEW(icon_view),3);
  gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),0);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),1);

  gtk_container_add(GTK_CONTAINER(planilha_relats_wnd),icon_view);

  g_signal_connect(icon_view,"item-activated",G_CALLBACK(icon_view_select_caller_with_intarg), modelo);
  g_signal_connect(planilha_relats_wnd,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_PLANL_ICONS_WIN]);

  gtk_widget_show_all(planilha_relats_wnd);
  return 0;
}
