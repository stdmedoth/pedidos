int ped_get_status(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);

  gchar *ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(!strlen(ped_code)){
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	struct _pedido *pedidoPtr = malloc(sizeof(struct _pedido));
  pedidoPtr->infos = malloc(sizeof(struct _ped_infos));
	pedidoPtr->infos->ped_code = atoi(ped_code);

  //verificando status do pedido
  sprintf(query,"select status from pedidos where code = %i",pedidoPtr->infos->ped_code);
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
  }else{
    popup(NULL,"Erro ao consultar status");
  }

  return 0;
}
