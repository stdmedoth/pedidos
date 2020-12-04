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
  strcpy(cad_emp_strc.IE,row[EMP_IE_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_ie_entry),row[EMP_IE_COL]);
  strcpy(cad_emp_strc.IM,row[EMP_IM_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_im_entry),row[EMP_IM_COL]);
  strcpy(cad_emp_strc.RegTrib,row[EMP_REGTRIB_COL]);
  cad_emp_strc.RegTribInt = atoi(row[EMP_REGTRIB_COL]);
  gtk_combo_box_set_active_id(GTK_COMBO_BOX(cad_emp_regime_combo), row[EMP_REGTRIB_COL]);
  strcpy(cad_emp_strc.cRegTribISSQN,row[EMP_REGISSQN_COL]);

  if(row[EMP_SOBRE_COL]){
    strcpy(cad_emp_strc.sobre,row[EMP_SOBRE_COL]);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cad_emp_sobre_text_view));
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),row[EMP_SOBRE_COL], strlen(row[EMP_SOBRE_COL]));
  }

  strcpy(cad_emp_strc.smtp,row[EMP_SMTP_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_smtp_entry),row[EMP_SMTP_COL]);

  cad_emp_strc.smtp_port = atoi(row[EMP_SMTP_PORT_COL]);
  char smtp_port[6];
  sprintf(smtp_port,"%i",cad_emp_strc.smtp_port);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_smtp_port_entry),smtp_port);

  strcpy(cad_emp_strc.email,row[EMP_EMAIL_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_email_entry),row[EMP_EMAIL_COL]);
  strcpy(cad_emp_strc.email_senha,row[EMP_EMAILSEN_COL]);
  gtk_entry_set_text(GTK_ENTRY(cad_emp_emailsenha_entry),row[EMP_EMAILSEN_COL]);


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
    if(PopupBinario("Empresa ainda não informações, deseja criar um cadastro temporário?", "Sim! Criar agora", "Não! cadastrarei em breve")){
      struct _maquina *maquina = maquinas_get_atual();
      char *sobre = strdup("Uma base de gestão Calistu em criação");
      if(maquina){
        sprintf(query,"insert into empresa(razao, sobre) values('%s', '%s')",maquina->nome, sobre);
        if(enviar_query(query)){
          popup(NULL,"Não foi possível cadastrar base da empresa");
          return 1;
        }
      }
      sprintf(query,"select * from empresa");
      if(!(res = consultar(query)) || !(row = mysql_fetch_row(res))){
        popup(NULL,"Erro ao receber informações da empresa");
        return 1;
      }
    }else{
      return 1;
    }
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
  strcpy(cad_emp_strc.smtp,row[EMP_SMTP_COL]);
  cad_emp_strc.smtp_port = atoi(row[EMP_SMTP_PORT_COL]);
  strcpy(cad_emp_strc.email,row[EMP_EMAIL_COL]);
  strcpy(cad_emp_strc.email_senha,row[EMP_EMAILSEN_COL]);
  strcpy(cad_emp_strc.IE,row[EMP_IE_COL]);
  strcpy(cad_emp_strc.IM,row[EMP_IM_COL]);
  strcpy(cad_emp_strc.RegTrib,row[EMP_REGTRIB_COL]);
  cad_emp_strc.RegTribInt = atoi(row[EMP_REGTRIB_COL]);
  strcpy(cad_emp_strc.cRegTribISSQN,row[EMP_REGISSQN_COL]);

  if(row[EMP_SOBRE_COL]){
    strcpy(cad_emp_strc.sobre,row[EMP_SOBRE_COL]);
  }else{
    sprintf(cad_emp_strc.sobre,"Sistema para empresa '%s' responsável pelo CNPJ '%s', localizada no municipio de '%s'",cad_emp_strc.xNome, cad_emp_strc.CNPJ, cad_emp_strc.xMun);
  }

  //formatando link do servidor smtp
  sprintf(cad_emp_strc.url_smtp,"smtp://%s:%i",cad_emp_strc.smtp, cad_emp_strc.smtp_port);

  sprintf(query,"select * from tecn_pers_elem");
  if(!(res = consultar(query))){
    person_tecn_prim=1;
    popup(NULL,"Erro ao receber informações da empresa");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    person_tecn_prim=1;
    if(person_tecn_prim){
			if(PopupBinario("Não há personalização, Deseja Criar?", "Sim! adiante meu serviço", "Não! prefiro fazer eu mesmo")){
				sprintf(query,"insert into tecn_pers_elem(code, path_img_init, script_bin_path) values(%i, '%s' , '')",sessao_oper.code, INI_LOGO);
				if(enviar_query(query)){
					popup(NULL,"Não foi possível criar dados técnicos");
				}else{
          person_tecn_prim=0;
        }
			}
		}
    return 1;
  }

  strcpy(cad_emp_strc.init_image_path,row[1]);
  strcpy(cad_emp_strc.script_bin_path,row[2]);

  return 0;
}
