int cad_pag_excluir_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  if(cad_pag_code_fun())
    return 1;

  int titulo = atoi(cad_pag_code_gchar);

  sprintf(query,"select parcelas_id from baixas_titulos where parcelas_id = %i",titulo);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar baixas");
    return 1;
  }
  if((row = mysql_fetch_row(res))){
    if(!PopupBinario(
      "Há baixas para este título, como proceder?",
      "Excluir baixas e continuar",
      "Manter baixas e cancelar"
    )){
      return 0;
    }
    sprintf(query,"delete from baixas_titulos where parcelas_id = %i",titulo);
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar baixas");
      return 1;
    }
  }

  if(PopupBinario(
    "Título ou Parcelas",
    "Deletar título com as parcelas",
    "Deletar apenas a parcela"
  )){
    sprintf(query,"delete from parcelas_tab where parcelas_id = %i",titulo);
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar parcelas");
      return 1;
    }
    sprintf(query,"delete from titulos where code = %i",titulo);
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar título");
      return 1;
    }
  }else{
    sprintf(query,"delete from parcelas_tab where parcelas_id = %i and posicao = %i",titulo,cad_pag_parcela_int);
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar parcelas");
      return 1;
    }
  }

  popup(NULL,"Título deletado com sucesso");

  return 0;
}
