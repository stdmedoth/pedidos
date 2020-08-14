int relat_fix_vnd_prod_fun(){

  MYSQL_ROW row;
  MYSQL_RES *res;
  char query[MAX_QUERY_LEN];

  relat_fix_vnd_prod_gchar1 = (gchar*) gtk_entry_get_text(GTK_ENTRY(relat_fix_vnd_prod_entry1));
  relat_fix_vnd_prod_gchar2 = (gchar*) gtk_entry_get_text(GTK_ENTRY(relat_fix_vnd_prod_entry2));

  sprintf(query,"select grupo from produtos where code = %i",atoi(relat_fix_vnd_prod_gchar1));

  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar grupo do produto");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Produto não existente");
    return 1;
  }

  if(row[0])
    find_subgrupos_restrict->grupo = atoi(row[0]);
  else{
    popup(NULL,"Não Há grupos vinculados ao produto");
    return 1;
  }

  gtk_widget_grab_focus(relat_fix_vnd_grp_entry1);
  return 0;
}
