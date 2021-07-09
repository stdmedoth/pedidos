int cad_emp_concluir(){
  MYSQL_RES*res;
  MYSQL_ROW row;
  GtkTextIter inicio,fim;
  char query[MAX_QUERY_LEN];

  GtkTextBuffer *sobre_buffer;

  char *code, *nome,*cnpj,*ie,*im,*logr,*cep,
  *bairro,*cidade,*uf,*telefone,
  *celular, *smtp_server,*smtp_port,
  *email, *senhaemail, *sobre, *path_img_init,
  *path_script, *regime_trib, *digcertpath, *digcertpass;

  int numrua,tiporua,regime_issq;

  code = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_code_entry));
  if(!strlen(code)){
    popup(NULL,"Código deve ser inserido");
    return 1;
  }

  nome = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_nome_entry));
  if(!strlen(nome))
    nome = strdup("");

  cnpj = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_cpnj_entry));
  if(!strlen(cnpj))
    cnpj = strdup("");
  char *char_cnpj = string_to_int(cnpj);
  if(!strlen(char_cnpj))
    char_cnpj = strdup("");

  ie = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_ie_entry));
  if(!strlen(ie))
    ie = strdup("");

  im = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_im_entry));
  if(!strlen(im))
    im = strdup("");

  regime_trib = (gchar*) gtk_combo_box_get_active_id(GTK_COMBO_BOX(cad_emp_regime_combo));
  if(!strlen(regime_trib))
    regime_trib = strdup("");
  regime_issq = 1;//gtk_combo_box_get_active(GTK_COMBO_BOX(cad_emp_regime_combo));

  logr = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_logr_entry));
  if(!strlen(logr))
    logr = strdup("");

  cep = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_cep_entry));
  if(!strlen(cep))
    cep = strdup("");

  bairro = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_bairro_entry));
  if(!strlen(bairro))
    bairro = strdup("");

  cidade = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_cidade_entry));
  if(!strlen(cidade))
    cidade = strdup("");

  uf = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_uf_entry));
  if(!strlen(uf))
    uf = strdup("");

  numrua = gtk_spin_button_get_value(GTK_SPIN_BUTTON(cad_emp_numrua_spin));
  tiporua = gtk_combo_box_get_active(GTK_COMBO_BOX(cad_emp_tiporua_combo));

  telefone = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_telefone_entry));
  if(!strlen(telefone))
    telefone = strdup("");

  celular = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_celular_entry));
  if(!strlen(celular))
    celular = strdup("");

  smtp_server = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_smtp_entry));
  if(!strlen(smtp_server))
    smtp_server = strdup("");

  smtp_port = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_smtp_port_entry));
  if(!strlen(smtp_port))
    smtp_port = strdup("587");

  sobre_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cad_emp_sobre_text_view));
  gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(sobre_buffer),&inicio,&fim);

  sobre = gtk_text_buffer_get_text(sobre_buffer,&inicio,&fim,TRUE);
  if(!strlen(sobre))
    sobre = strdup("");


  email = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_email_entry));
  if(!strlen(email))
    email = strdup("");

  senhaemail = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_emailsenha_entry));
  if(!strlen(senhaemail))
    senhaemail = strdup("");

  path_img_init = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_img_init_entry));
  if(!strlen(path_img_init))
    path_img_init = strdup("");

  path_script =  (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_script_path_entry));
  if(!strlen(path_script))
    path_script = strdup("");

  digcertpath = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_digcert_path_entry));
  digcertpass = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_digcert_pass_entry));

  char *query_digcertpath = malloc( strlen(digcertpath) *2);
  mysql_real_escape_string(&conectar, query_digcertpath, digcertpath, strlen(digcertpath));
  //informativos

  if(!row_exists("empresa", atoi(code))){
    sprintf(query,
      "insert into empresa(code, cnpj,razao, ie, im, regime_tributario, regime_issqn, digcert_path, digcert_pass, cep, endereco, bairro, cidade, uf, numrua, tiporua, telefone, celular, smtp, porta, email, senhaemail, sobre ) \
      values('%s', '%s','%s', '%s', '%s', '%s','%i', '%s', '%s', '%s','%s','%s','%s','%s','%i','%i','%s','%s','%s','%i','%s','%s','%s')",
      code, char_cnpj, nome, ie, im, regime_trib, regime_issq, query_digcertpath, digcertpass, cep, logr, bairro,
      cidade,uf, numrua,tiporua, telefone,
      celular,smtp_server, atoi(smtp_port), email, senhaemail,sobre);
  }else{

    sprintf(query,"update empresa set cnpj = '%s', ie = '%s', im = '%s', regime_tributario = '%s', regime_issqn = '%i', digcert_path = '%s', digcert_pass = '%s', razao = '%s', cep = '%s', endereco = '%s', bairro = '%s', cidade  = '%s', uf = '%s', numrua = '%i', tiporua = '%i', telefone = '%s', celular = '%s',smtp = '%s', porta = '%i', email = '%s', senhaemail = '%s', sobre = '%s' where code = %s",
      char_cnpj,ie, im, regime_trib, regime_issq, query_digcertpath,
      digcertpass, nome  ,cep, logr, bairro,
      cidade,uf, numrua,tiporua, telefone,
      celular, smtp_server, atoi(smtp_port), email, senhaemail, sobre, code);
  }

  if(enviar_query(query)){
    popup(NULL,"Erro ao atualizar informações da empresa");
    return 1;
  }

  char *query_path_img_init = malloc( strlen(path_img_init) *2);
  char *query_path_script = malloc( strlen(path_script) *2);

  mysql_real_escape_string(&conectar, query_path_img_init, path_img_init, strlen(path_img_init));
  mysql_real_escape_string(&conectar, query_path_script, path_script,strlen(path_script));

  //personalizacao
  if(!row_exists("empresa", atoi(code))){
    sprintf(query,"insert into tecn_pers_elem(code,path_img_init,script_bin_path) values(1,'%s','%s')",
    query_path_img_init, query_path_script);
  }else{
    sprintf(query,"update tecn_pers_elem set path_img_init = '%s', script_bin_path = '%s'",
    query_path_img_init, query_path_script);
  }

  if(enviar_query(query)){
    popup(NULL,"Erro ao atualizar Personalizações técnicas");
    return 1;
  }

  if(cad_emp_recebe())
    return 1;
  cad_emp_prim=0;
  popup(NULL,"Informações atualizadas com suceeso");

  return 0;
}
