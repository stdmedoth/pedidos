int mkt_mail_excluir_fun(){

    if(mkt_mail_code_fun())
      return 1;

    MYSQL_RES *res;
    MYSQL_ROW row;
    gchar *query = malloc(MAX_QUERY_LEN);

    sprintf(query,"select * from emails_model where code = %i", atoi(mkt_mail_code_gchar));
    if(!(res = consultar(query))){
      popup(NULL,"Não foi  possivel consultar o modelo");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      popup(NULL,"Modelo não existente");
      return 1;
    }

    sprintf(query,"delete from emails_footer where email_id = %i", atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar footer");
      return 1;
    }

    sprintf(query,"delete from emails_body where email_id = %i", atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar corpo");
      return 1;
    }

    sprintf(query,"delete from emails_header where email_id = %i", atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar heeader");
      return 1;
    }

    sprintf(query,"delete from emails_model where code = %i", atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível deletar Modelo");
      return 1;
    }

    popup(NULL,"Modelo excluído com sucesso");
    mkt_mail_cancelar_fun();

    return 0;
}
