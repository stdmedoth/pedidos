int mkt_mail_visualizar_fun(){


  if( mkt_mail_code_fun())
    return 1;

  MYSQL_RES * res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  FILE *file;
  gchar *header, *body, *footer;

  mkt_email_visualizando = 1;
  sprintf(query,"SELECT * FROM emails_header WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    header = strdup(row[EMLHEADER_CONTEUDO]);
  }else{
    header = strdup( " " );
  }


  sprintf(query,"SELECT * FROM emails_body WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    body = strdup( row[EMLBODY_CONTEUDO] );
  }else{
    body = strdup( " " );
  }

  sprintf(query,"SELECT * FROM emails_footer WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    footer = strdup( row[EMLFOOTER_CONTEUDO] );
  }else{
    footer = strdup( " " );
  }
  if(!strlen(header) && !strlen(body) && !strlen(footer)){
    popup(NULL,"Modelo vazio");
    return 1;
  }
  gchar *path = malloc(strlen(MAILMKT_RELAT_PATH) + 20);
  sprintf(path,"%smodelemail%i.html", MAILMKT_RELAT_PATH,atoi(mkt_mail_code_gchar));

  file = fopen(path,"w");
  if(!file){
    popup(NULL,"Não foi possível abrir arquivo");
    return 1;
  }
  fprintf(file, "<html>");
  fprintf(file, header);
  fprintf(file, body);
  fprintf(file, footer);
  fprintf(file, "</html>");
  fclose(file);

  if(escolher_finalizacao(path)){
    return 1;
  }


  return 0;
}
