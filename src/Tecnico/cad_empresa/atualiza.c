int cad_emp_atualiza(){
  MYSQL_RES*res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  char *nome,*cnpj,*logr,*cep,
  *bairro,*cidade,*uf,*telefone,*celular,*email,*path_img_init;

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
  email = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_emp_email_entry));
  path_img_init = (gchar *)gtk_entry_get_text(GTK_ENTRY(cad_emp_img_init_entry));

  //informativos
  if(cad_emp_prim){
    sprintf(query,"insert into empresa values('%s','%s','%s','%s','%s','%s','%s','%i','%i','%s','%s','%s')",
    cnpj, nome,cep, logr, bairro,
    cidade,uf, numrua,tiporua, telefone,
    celular, email);
  }else{
    sprintf(query,"update empresa set cnpj = '%s', razao = '%s', cep = '%s', endereco = '%s', bairro = '%s', cidade  = '%s', uf = '%s', numrua = '%i', tiporua = '%i', telefone = '%s', celular = '%s', email = '%s'",
    cnpj, nome  ,cep, logr, bairro,
    cidade,uf, numrua,tiporua, telefone,
    celular, email);
  }

  if(enviar_query(query)){
    popup(NULL,"Erro ao atualizar informações da empresa");
    return 1;
  }

  //personalizacao
  if(person_tecn_prim){
    sprintf(query,"insert into tecn_pers_elem(code,path_img_init) values(1,'%s')",
    path_img_init);
  }else{
    sprintf(query,"update tecn_pers_elem set path_img_init = '%s'",
    path_img_init);
  }

  if(enviar_query(query)){
    popup(NULL,"Erro ao atualizar Personalizações técnicas");
    return 1;
  }

  return 0;
}
