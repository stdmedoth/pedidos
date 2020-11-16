int ped_get_status(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  char *orc_path;
  gchar *code = malloc(20);

  if(!strlen(code = (gchar*) gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)))){
    gtk_widget_grab_focus(ped_cod_entry);
    popup(NULL,"Insira o código do orcamento");
    return 1;
  }

  ped_infos.ped_code = atoi(code);

  //verificando status do pedido
  sprintf(query,"select status from pedidos where code = %i",ped_infos.ped_code);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao buscar valor total nos dados");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Pedido não criado");
    return 1;
  }

  if(row[0]){
    gtk_combo_box_set_active(GTK_COMBO_BOX(emiteped_status_combo),atoi(row[0]));
    return atoi(row[0]);
  }
  else
    return -1;
}
