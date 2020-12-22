int prod_precos_concluir_fun(){

  prod_precos_concluindo = 1;

  if(prod_precos_code_fun()){
    gtk_widget_grab_focus(prod_prc_code_entry);
    return 1;
  }

  if(prod_precos_prod_fun()){
    gtk_widget_grab_focus(prod_prc_prodcode_entry);
    return 1;
  }

  if(prod_precos_nome_fun()){
    gtk_widget_grab_focus(prod_prc_nome_entry);
    return 1;
  }

  if(prod_precos_vltfat_fun()){
    gtk_widget_grab_focus(prod_prc_vlrfat_entry);
    return 1;
  }

  if(prod_precos_vlrvist_fun()){
    gtk_widget_grab_focus(prod_prc_vlrvist_entry);
    return 1;
  }

  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  sprintf(query,"select * from precos where code = %s", prod_prc_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar preço");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    sprintf(query,"insert into precos(code, nome, produto, valor_fat, valor_vist) values(%s, '%s', %s, %s, %s)",
    prod_prc_code_gchar,
    prod_prc_nome_gchar,
    prod_prc_prodcode_gchar,
    prod_prc_vlrfat_gchar,
    prod_prc_vlrvist_gchar
  );

  }else{
    sprintf(query,"update precos set nome = '%s', produto = %s, valor_fat = %s, valor_vist = %s where code = %s",
    prod_prc_nome_gchar,
    prod_prc_prodcode_gchar,
    prod_prc_vlrfat_gchar,
    prod_prc_vlrvist_gchar,
    prod_prc_code_gchar
  );
  }
  if(enviar_query(query)){
    popup(NULL,"Não foi possível atualizar preço");
    return 1;
  }

  popup(NULL,"Preço atualizado com sucesso");
  prod_precos_cancelar_fun();
  return 0;
}
