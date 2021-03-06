int ped_get_status(){

  gchar *ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(!strlen(ped_code)){
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do pedido");
		return -1;
	}

  char *query = malloc(MAX_QUERY_LEN);
	struct _pedido *pedidoPtr = malloc( sizeof(struct _pedido) );
  pedidoPtr->infos = malloc( sizeof(struct _ped_infos) );
	pedidoPtr->infos->ped_code = atoi(ped_code);
  MYSQL_RES *res;
  MYSQL_ROW row;

  enum{
    STATUS
  };

  sprintf(query,"select status from pedidos where code = %i", pedidoPtr->infos->ped_code);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao buscar valor total nos dados");
    return -1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Pedido não criado");
    return -1;
  }

  if(!row[STATUS]){
    popup(NULL,"Erro ao consultar status");
    return -1;
  }

  //gtk_combo_box_set_active(GTK_COMBO_BOX(emiteped_status_combo), atoi(row[STATUS]));
  return atoi(row[STATUS]);
}
