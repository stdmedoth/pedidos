int prod_ncm_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  gchar *codnome_ncm = (gchar*) gtk_entry_get_text (GTK_ENTRY(prod_ncm_entry));

  if(!strlen(codnome_ncm)){
    sprintf(query, "select code, cod_ncm, nome_ncm from ncm where cod_ncm = '00000000'");
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar NCM base");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"NCM base não existente");
      return 1;
    }else{
      prod_ncm_gchar = strdup(row[0]);
      gtk_entry_set_text(GTK_ENTRY(prod_ncm_entry),row[1]);
    }
    gtk_widget_grab_focus(prod_origem_combo);
    return 0;
  }

  sprintf(query, "select code, cod_ncm, nome_ncm from ncm where cod_ncm = '%s'", codnome_ncm);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar NCM");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"NCM não existente");
    return 1;
  }
  prod_ncm_gchar = strdup(row[0]);
  gtk_entry_set_text(GTK_ENTRY(campo_nome_ncm),row[2]);
  
  gtk_widget_grab_focus(prod_origem_combo);
  return 0;
}
