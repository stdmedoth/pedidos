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
    header = strdup( "" );
  }

  sprintf(query,"SELECT * FROM emails_body WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    body = strdup( row[EMLBODY_CONTEUDO] );
  }else{
    body = strdup( "" );
  }

  sprintf(query,"SELECT * FROM emails_footer WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    footer = strdup( row[EMLFOOTER_CONTEUDO] );
  }else{
    footer = strdup( "" );
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

  char *editedheader = NULL;
  char *editedbody=NULL;
  char *editedfooter=NULL;

  //for(int cont=0;mail_tags_vet[cont];cont++){
  //  editedbody = replaceWord(body, mail_tags_vet[cont], mail_tags_vet[cont]);
  //}

  gchar *full_ender=NULL;
  struct _terc_infos *cli = terceiros_get_simp_terceiro(5);
  if(!cli){
    popup(NULL,"Não foi possível consultar cliente");
    return 1;
  }

  editedbody = replaceWord(body, mail_tags_vet[MAIL_TAG_EMP_NOME][0], cad_emp_strc.xNome);

  if((full_ender = get_full_ender_from_cep(cad_emp_strc.CEP, cad_emp_strc.nro))){
    editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_EMP_ENDER][0], full_ender);
  }

  editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_EMP_TEL][0], cad_emp_strc.telefone);

  editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_CLI_NOME][0], cli->razao);

  if((full_ender = get_full_ender_from_cep(cli->cep, cli->i_nro))){
    editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_CLI_ENDER][0], full_ender);
  }

  if(cli->contatos_qnt){
    editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_CLI_CONTATO][0], cli->contatos[0].nome);
    editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_CLI_TEL][0], cli->contatos[0].telefone);
    editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_CLI_CEL][0], cli->contatos[0].celular);
  }

  editedbody = replaceWord(editedbody, mail_tags_vet[MAIL_TAG_DATA][0], data_sys);

  if(!editedbody){
    popup(NULL,"Não foi possível editar tags do email");
    return 1;
  }

  if(!editedheader)
    editedheader = strdup(header);

  if(!editedbody)
    editedbody = strdup(body);

  if(!editedfooter)
    editedfooter = strdup(footer);

  fprintf(file, "<html>");
  fprintf(file, "%s", editedheader);
  fprintf(file, "%s", editedbody);
  fprintf(file, "%s", editedfooter);
  fprintf(file, "</html>");
  fclose(file);

  if(escolher_finalizacao(path)){
    return 1;
  }


  return 0;
}
