int ordem_cmp_cancelar_fun(){

  gchar *task_num = malloc(12);
  sprintf(task_num, "%i", tasker("ordens_compra"));
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_code_entry), task_num);
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_forncode_entry), "");
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_fornnome_entry), "");
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_dtemissao_entry), "");
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_dtentrega_entry), "");
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_condpag_entry), "");
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_condpagnome_entry), "");
  gtk_combo_box_set_active(GTK_COMBO_BOX(ordem_cmp_status_combo), 0);

  //gtk_widget_set_sensitive(ordem_cmp_status_combo, FALSE);
  gtk_combo_box_set_button_sensitivity(GTK_COMBO_BOX(ordem_cmp_status_combo), GTK_SENSITIVITY_OFF);
  gtk_editable_set_editable(GTK_EDITABLE(ordem_cmp_fornnome_entry), FALSE);
  gtk_editable_set_editable(GTK_EDITABLE(ordem_cmp_condpagnome_entry), FALSE);

  ordem_cmp_alterando = 0;
  ordem_cmp_concluindo = 0;
  ordem_cmp_excluido_pos =0;
  for(int cont=0;cont<MAX_PROD;cont++){
    ordem_cmp_excluidos[cont] = 0;
  }

  enum {
    ID_COLUMN,
    PROD_NOME_COLUMN,
    PROD_QNT_COLUMN,
    PROD_VLR_COLUMN,
    N_COLUMNS
  };

  GtkTreeStore *req_model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_req_treeview));
  if(!req_model)
    req_model = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);

  g_object_ref(G_OBJECT(req_model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_req_treeview),NULL);
  gtk_tree_store_clear(req_model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_req_treeview),GTK_TREE_MODEL(req_model));

  GtkTreeStore *ordreq_model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview));
  if(!ordreq_model)
    ordreq_model = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);

  g_object_ref(G_OBJECT(ordreq_model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),NULL);
  gtk_tree_store_clear(ordreq_model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview),GTK_TREE_MODEL(ordreq_model));

  gtk_widget_set_sensitive(ordem_cmp_code_entry, TRUE);
  gtk_widget_set_sensitive(ordem_cmp_codepsq_button, TRUE);
  gtk_widget_set_sensitive(ordem_cmp_alterar_button, TRUE);

  gtk_widget_grab_focus(ordem_cmp_forncode_entry);
  return 0;
}
