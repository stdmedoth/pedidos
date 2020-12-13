int mkt_cad_distrib_add_fun(){

  distrib_pessoacode_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(distrib_pessoacode_entry));
  if(!strlen(distrib_pessoacode_gchar)){
    popup(NULL,"Não foi possível receber pessoa");
    return 1;
  }

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };

  sprintf(query,"select t.code, t.razao, c.email, c.telefone, c.celular from terceiros as d inner join terceiros as t inner join contatos as c on c.terceiro = t.code where t.code = %s", distrib_pessoacode_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da lista");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Pessoa sem contatos");
    return 1;
  }

  GtkTreeStore *model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(distrib_pessoas_treeview));
  GtkTreeIter campos;

  gtk_tree_store_append(model,&campos,NULL);
  gtk_tree_store_set(model,&campos,
  ID,row[ID],
  NOME,row[NOME],
  EMAIL,row[EMAIL],
  CELULAR,row[CELULAR],
  TELEFONE,row[TELEFONE],
  -1);

  return 0;
}
