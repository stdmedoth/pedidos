int ped_excluir(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  char *ped_code;

  ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));

	if(strlen(ped_code)<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}

  sprintf(query,"select status from pedidos where code = %s",ped_code);
  if((res = consultar(query))==NULL){
    return 1;
  }

  if((row = mysql_fetch_row(res))==NULL){
    popup(NULL,"O pedido não existe");
    return 1;
  }

  if(atoi(row[0]) == STATUS_PED_EMIT){
    popup(NULL,"Pedido está emitido");
    return 1;
  }

  sprintf(query,"delete from pedidos where code = %s",ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao tentar deletar pedido");
		return 1;
	}
  popup(NULL,"Excluído com sucesso");
  return 0;
}
