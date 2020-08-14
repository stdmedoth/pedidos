void relat_icon_view_select(GtkIconView *icon_view, GtkTreePath *path, gpointer data){
  GtkTreeIter iter;
  char *posicao;
  GdkPixbuf *pixbuf;
  int identificacao=0;
  g_print("recebendo valor do treeicon");

  if(gtk_tree_model_get_iter(GTK_TREE_MODEL(data),&iter,path))
    gtk_tree_model_get(GTK_TREE_MODEL(data),&iter,0,&posicao,1,&pixbuf,2,&identificacao,-1);
  else
    g_print("Não foi possivel encontrar iter\n");

  if(janelas_gerenciadas.vetor_janelas[identificacao].fun)
    janelas_gerenciadas.vetor_janelas[identificacao].fun();
  g_print("posicao = :%s\n",posicao);
}

int relat_icon_view_wnd(){
  int N_COLUMNS=3;
  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *search_entry = gtk_search_entry_new() ;
  GtkTreeIter iter;
  GtkTreeStore *modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,GDK_TYPE_PIXBUF,G_TYPE_INT);
  GtkWidget *icon_view = gtk_icon_view_new();

  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].reg_id = REG_REL_FIX_ICONS_WIN;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN].janela_pointer = janela;

  gtk_widget_set_name(janela,"relat-fixos");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Relatórios Fixos");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"text-x-generic");

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,0,"Relatório Produtos",1,
    gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_FIX_PROD_IMG))),
    2,REG_REL_FIX_PROD_WIN,-1);

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,0,"Relatório Terceiros",1,
    gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_FIX_TER_IMG))),
    2,REG_REL_FIX_TER_WIN,-1);

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,0,"Relatório Vendas",1,
    gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_FIX_VND_IMG))),
    2,REG_REL_FIX_VND_WIN,-1);

  gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view),GTK_TREE_MODEL(modelo));
  //gtk_icon_view_set_activate_on_single_click(GTK_ICON_VIEW(icon_view),TRUE);

  g_signal_connect(icon_view,"item-activated",G_CALLBACK(relat_icon_view_select), modelo);

  gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),0);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),1);

  gtk_container_add(GTK_CONTAINER(janela),icon_view);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_REL_FIX_ICONS_WIN]);


  gtk_widget_show_all(janela);
  return 0;
}
