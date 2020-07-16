  static int copia_orc_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  int task_atual_int=0;
  char task_atual_char[MAX_CODE_LEN];

  copiando_orc=1;

  if(codigo_orc())
    return 1;

  task_atual_int = tasker("orcamentos");

  sprintf(query,"insert into orcamentos select %i,vendedor, cliente, dia, pag_cond, total, observacoes from orcamentos where code = %s",task_atual_int,codigo_orc_gchar);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel criar orcamento para cópia");
    return 1;
  }

  sprintf(query,"insert into Produto_Orcamento select %i,item,produto,subgrupo,unidades,valor_unit,valor_orig,tipodesc,desconto,total,observacoes from Produto_Orcamento where code = %s;",task_atual_int,codigo_orc_gchar);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel copiar produtos do orcamento");
    return 1;
  }

  cancela_orc();

  sprintf(task_atual_char,"%i",task_atual_int);
  gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),task_atual_char);

  altera_orc();

  gtk_widget_set_sensitive(copia_orc_button,FALSE);

  return 0;
}
