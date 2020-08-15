int cad_pag_cli_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  cad_pag_cli_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_pag_cli_entry));

  if(!strlen(cad_pag_cli_gchar)){
    popup(NULL,"Insira o Terceiro");
    gtk_widget_grab_focus(cad_pag_cli_entry);
    return 1;
  }

  sprintf(query,"select razao from terceiros where code = %s",cad_pag_cli_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar terceiro");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"O terceiro não existe");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cad_pag_cli_nome_entry),row[0]);
  gtk_widget_grab_focus(cad_pag_ped_entry);

  return 0;
}
