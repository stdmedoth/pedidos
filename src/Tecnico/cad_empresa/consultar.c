int cad_emp_consulta(){
  MYSQL_RES*res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query,"select * from empresa");
  if(!(res = consultar(query))){
    cad_emp_prim=1;
    popup(NULL,"Erro ao receber informações da empresa");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    cad_emp_prim=1;
    popup(NULL,"Empresa sem informações");
    return 1;
  }

  strcpy(cad_emp_strc.CNPJ,row[EMP_CNPJ_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_cpnj_entry),row[EMP_CNPJ_COL]);
  strcpy(cad_emp_strc.xNome,row[EMP_NOME_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_nome_entry),row[EMP_NOME_COL]);
  strcpy(cad_emp_strc.CEP,row[EMP_CEP_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_cep_entry),row[EMP_CEP_COL]);
  strcpy(cad_emp_strc.xLgr,row[EMP_LOGR_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_logr_entry),row[EMP_LOGR_COL]);
  strcpy(cad_emp_strc.xBairro,row[EMP_BAIR_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_bairro_entry),row[EMP_BAIR_COL]);
  strcpy(cad_emp_strc.xMun,row[EMP_CID_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_cidade_entry),row[EMP_CID_COL]);
  strcpy(cad_emp_strc.UF,row[EMP_UF_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_uf_entry),row[EMP_UF_COL]);
  cad_emp_strc.nro = atoi(row[EMP_NRUA_COL]);
  cad_emp_strc.tipo_rua = atoi(row[EMP_TRUA_COL]);
  strcpy(cad_emp_strc.telefone,row[EMP_TEL_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_telefone_entry),row[EMP_TEL_COL]);
  strcpy(cad_emp_strc.celular,row[EMP_CEL_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_celular_entry),row[EMP_CEL_COL]);
  strcpy(cad_emp_strc.email,row[EMP_EMAIL_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_email_entry),row[EMP_EMAIL_COL]);

  sprintf(query,"select * from tecn_pers_elem");
  if(!(res = consultar(query))){
    person_tecn_prim=1;
    popup(NULL,"Erro ao receber informações da empresa");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    person_tecn_prim=1;
    popup(NULL,"Empresa sem informações");
    return 1;
  }

  strcpy(cad_emp_strc.init_image_path,row[1]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_img_init_entry),row[1]);

  strcpy(cad_emp_strc.script_bin_path,row[2]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_script_path_entry),row[2]);


  return 0;
}

int cad_emp_recebe(){
  MYSQL_RES*res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query,"select * from empresa");
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao receber informações da empresa");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    cad_emp_prim=1;
    popup(NULL,"Empresa sem informações");
    return 1;
  }

  strcpy(cad_emp_strc.CNPJ,row[EMP_CNPJ_COL]);
  strcpy(cad_emp_strc.xNome,row[EMP_NOME_COL]);
  strcpy(cad_emp_strc.CEP,row[EMP_CEP_COL]);
  strcpy(cad_emp_strc.xLgr,row[EMP_LOGR_COL]);
  strcpy(cad_emp_strc.xBairro,row[EMP_BAIR_COL]);
  strcpy(cad_emp_strc.xMun,row[EMP_CID_COL]);
  strcpy(cad_emp_strc.UF,row[EMP_UF_COL]);
  cad_emp_strc.nro = atoi(row[EMP_NRUA_COL]);
  cad_emp_strc.tipo_rua = atoi(row[EMP_TRUA_COL]);
  strcpy(cad_emp_strc.telefone,row[EMP_TEL_COL]);
  strcpy(cad_emp_strc.celular,row[EMP_CEL_COL]);
  strcpy(cad_emp_strc.email,row[EMP_EMAIL_COL]);

  sprintf(query,"select * from tecn_pers_elem");
  if(!(res = consultar(query))){
    person_tecn_prim=1;
    popup(NULL,"Erro ao receber informações da empresa");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    person_tecn_prim=1;
    popup(NULL,"Empresa sem informações Técnicas");
    return 1;
  }

  strcpy(cad_emp_strc.init_image_path,row[1]);
  strcpy(cad_emp_strc.script_bin_path,row[2]);

  return 0;
}
