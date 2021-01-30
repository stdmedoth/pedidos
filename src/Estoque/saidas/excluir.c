int est_said_excluir_fun(){

  if(est_said_codigo_fun())
		return 1;

  char *query = malloc(MAX_QUERY_LEN);
  sprintf(query,"delete from movimento_estoque where code = %s", est_said_cod_gchar);
  if(enviar_query(query)){
    popup(NULL,"Erro ao tentar movimentar estoque");
    return 1;
  }
  popup(NULL, "Excluido com sucesso");
  est_said_cancelar_fun();

  return 0;
}
