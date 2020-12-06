int mkt_cad_distrib_alterar_fun(){

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };

  mkt_cad_distrib_alterando = 1;

  GtkTreeIter campos;
  GtkTreeStore *model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(distrib_pessoas_treeview));
  if(!model)
    model = gtk_tree_store_new(N_COLS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING);

  g_object_ref(G_OBJECT(model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(distrib_pessoas_treeview),NULL);
  gtk_tree_store_clear(model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(distrib_pessoas_treeview),GTK_TREE_MODEL(model));

  GtkTreeStore *envmodel =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(distrib_pessoas_treeview));
  if(envmodel)
    gtk_tree_store_clear(envmodel);

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];
  distrib_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(distrib_code_entry));

  if(!strlen(distrib_code_gchar))
    return 1;

  sprintf(query,"select * from distribuicoes where code = %s", distrib_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da lista");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Lista não existente");
    return 1;
  }
  if(row[1])
    gtk_entry_set_text(GTK_ENTRY(distrib_nome_entry), row[1]);

  sprintf(query,"select t.code, t.razao, c.email, c.telefone, c.celular from PessoasDistribuicao as d inner join terceiros as t inner join contatos as c on t.code = d.pessoa and c.terceiro = t.code where d.distribuicao = %s", distrib_code_gchar);
  if(!(res = consultar(query))){
    return 1;
  }
  while((row = mysql_fetch_row(res))){

    if(!strlen(row[EMAIL]))
      continue;

    gtk_tree_store_append(model,&campos,NULL);
    gtk_tree_store_set(model,&campos,
    ID,row[ID],
    NOME,row[NOME],
    EMAIL,row[EMAIL],
    CELULAR,row[CELULAR],
    TELEFONE,row[TELEFONE],
    -1);
  }
  gtk_widget_grab_focus(distrib_nome_entry);
  return 0;
}
