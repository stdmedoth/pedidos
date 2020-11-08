int cad_emp_atualiza(){
  MYSQL_RES*res;
  MYSQL_ROW row;
  GtkTextIter inicio,fim;
  char query[MAX_QUERY_LEN];

  GtkTextBuffer *sobre_buffer;

  char *nome,*cnpj,*logr,*cep,
  *bairro,*cidade,*uf,*telefone,
  *celular, *smtp_server,*smtp_port,
  *email, *senhaemail, *sobre, *path_img_init,
  *path_script;

  int numrua,tiporua;

  nome = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_nome_entry));
  cnpj = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_cpnj_entry));
  logr = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_logr_entry));
  cep = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_cep_entry));
  bairro = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_bairro_entry));
  cidade = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_cidade_entry));
  uf = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_uf_entry));
  numrua = gtk_spin_button_get_value(GTK_SPIN_BUTTON(cad_emp_numrua_spin));
  tiporua = gtk_combo_box_get_active(GTK_COMBO_BOX(cad_emp_tiporua_combo));
  telefone = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_telefone_entry));
  celular = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_celular_entry));
  smtp_server = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_smtp_entry));
  smtp_port = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_smtp_port_entry));
  sobre_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cad_emp_sobre_text_view));
  gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(sobre_buffer),&inicio,&fim);
  sobre = gtk_text_buffer_get_text(sobre_buffer,&inicio,&fim,TRUE);
  if(!smtp_port)
    smtp_port = strdup("587");

  email = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_email_entry));
  senhaemail = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_emailsenha_entry));
  path_img_init = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_img_init_entry));
  path_script =  (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_script_path_entry));

  char *char_cnpj = string_to_int(cnpj);
  //informativos
  if(cad_emp_prim){
    sprintf(query,"insert into empresa values('%s','%s','%s','%s','%s','%s','%s','%i','%i','%s','%s','%s','%i','%s','%s','%s')",
    char_cnpj, nome,cep, logr, bairro,
    cidade,uf, numrua,tiporua, telefone,
    celular,smtp_server, atoi(smtp_port), email, senhaemail,sobre);

  }else{

    sprintf(query,"update empresa set cnpj = '%s', razao = '%s', cep = '%s', endereco = '%s', bairro = '%s', cidade  = '%s', uf = '%s', numrua = '%i', tiporua = '%i', telefone = '%s', celular = '%s',smtp = '%s', porta = '%i', email = '%s', senhaemail = '%s', sobre = '%s'",
    char_cnpj, nome  ,cep, logr, bairro,
    cidade,uf, numrua,tiporua, telefone,
    celular, smtp_server, atoi(smtp_port), email, senhaemail, sobre);
  }

  if(enviar_query(query)){
    popup(NULL,"Erro ao atualizar informações da empresa");
    return 1;
  }
  char *query_path_img_init = malloc(strlen(path_img_init));
  char *query_path_script = malloc(strlen(path_script));

  mysql_real_escape_string(&conectar,query_path_img_init,path_img_init,strlen(path_img_init));
  mysql_real_escape_string(&conectar,query_path_script,path_script,strlen(path_script));

  //personalizacao
  if(person_tecn_prim){
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
