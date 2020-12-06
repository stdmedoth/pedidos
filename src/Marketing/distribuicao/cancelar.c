int mkt_cad_distrib_cancelar_fun(){

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };

  mkt_cad_distrib_concluindo = 0;
  mkt_cad_distrib_alterando = 0;

  GtkTreeStore *model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(distrib_pessoas_treeview));
  if(!model)
    model = gtk_tree_store_new(N_COLS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING);

  for(int cont=0;cont<MAX_MAILDISTRIB_CONTTS;cont++){
    mkt_cad_distrib_removidos[cont] = 0;
  }

  g_object_ref(G_OBJECT(model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(distrib_pessoas_treeview),NULL);
  gtk_tree_store_clear(model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(distrib_pessoas_treeview),GTK_TREE_MODEL(model));

  gtk_widget_hide(distrib_pessoacode_entry);
  gchar *task = malloc(12);
  sprintf(task,"%i", tasker("distribuicoes"));

  gtk_entry_set_text(GTK_ENTRY(distrib_code_entry), task);
  gtk_entry_set_text(GTK_ENTRY(distrib_nome_entry), "");

  gtk_widget_grab_focus(distrib_code_entry);
  return 0;
}
