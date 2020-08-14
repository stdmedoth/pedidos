int cad_rec_ped_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  cad_rec_ped_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_rec_ped_entry));

  if(strlen(cad_rec_ped_gchar)){
    sprintf(query,"select cliente from pedidos where code = %s",cad_rec_ped_gchar);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível consultar pedido");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"O pedido não existe");
      return 1;
    }
  }
  gtk_widget_grab_focus(cad_rec_datacriacao_entry);

  return 0;
}
