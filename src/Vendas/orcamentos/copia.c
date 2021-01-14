static int copia_orc_fun(){

  tracelogger_set_func_name("copia_orc_fun");
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN*2];
  int task_atual_int=0;
  char task_atual_char[MAX_CODE_LEN];

  copiando_orc=1;

  if(codigo_orc()){
    copiando_orc=0;
    return 1;
  }

  sprintf(query,"select code from orcamentos where code = %s",codigo_orc_gchar);
  if(!(res = consultar(query))){
    copiando_orc=0;
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Orçamento não existe para ser copiado");
    copiando_orc=0;
    return 1;
  }

  task_atual_int = tasker("orcamentos");

  sprintf(query,"insert into orcamentos select %i,tipo_mov,vendedor, cliente, dia, pag_cond, banco, total, observacoes from orcamentos where code = %s",task_atual_int,codigo_orc_gchar);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel criar orcamento para cópia");
    return 1;
  }

  sprintf(query,"insert into Produto_Orcamento select %i,item,produto,unidades,valor_unit,valor_orig,tipodesc,desconto,total,observacoes from Produto_Orcamento where code = %s;",task_atual_int,codigo_orc_gchar);

  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel copiar produtos do orcamento");
    return 1;
  }

  sprintf(task_atual_char,"%i",task_atual_int);
  gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),task_atual_char);

  if(altera_orc()!=0){
    popup(NULL,"Erro ao abrir cópia");
    return 1;
  }

  gtk_widget_set_sensitive(copia_orc_button,FALSE);

  return 0;
}
