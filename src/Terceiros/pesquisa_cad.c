char  *format_cnpj_num(char *cnpj){
  int cont2=0;
  char *formated_cnpj = malloc(strlen(cnpj));
  strcpy(formated_cnpj,"");

  for(int cont=0;cont<strlen(cnpj);cont++){
    if(isdigit(cnpj[cont])){
      formated_cnpj[cont2] = cnpj[cont];
      cont2++;
    }
  }
  formated_cnpj[cont2] = '\0';
  return formated_cnpj;
}
void formatar_littobig(char *string){
  for(int cont=0;cont<strlen(string);cont++){
    if(isalpha(string[cont]) && islower(string[cont]))
      string[cont] -= 32;
  }
}
void rec_csnt_cad_vars(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    if(NULL == a_node)
    {
        return;
    }
    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if (cur_node->type == XML_ELEMENT_NODE)
        {
          if(cur_node->children->type == XML_TEXT_NODE){
            if(cur_node->name && cur_node->children && cur_node->children->content){
              if(!strcmp((char *)cur_node->name,"cStat")){
                consulta_cnpj.cStat = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.cStat, (gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"xMotivo")){
                consulta_cnpj.xMotivo = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.xMotivo, (gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"xNome")){
                consulta_cnpj.xNome = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.xNome, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(name_ter_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"IE")){
                consulta_cnpj.IE = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.IE, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(inscr_ter_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"CEP")){
                consulta_cnpj.CEP = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.CEP, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(cep_ter_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"xLgr")){
                consulta_cnpj.xLgr = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.xLgr, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(address_ter_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"nro")){
                consulta_cnpj.nro = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.nro, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(address_num_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"xBairro")){
                consulta_cnpj.xBairro = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.xBairro, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(bairro_ter_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"xMun")){
                consulta_cnpj.xMun = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.xMun, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),(gchar*)cur_node->children->content);
              }
              if(!strcmp((char *)cur_node->name,"UF")){
                consulta_cnpj.UF = malloc(strlen((gchar*)cur_node->children->content));
                strcpy(consulta_cnpj.UF, (gchar*)cur_node->children->content);
                gtk_entry_set_text(GTK_ENTRY(uf_ter_field),(gchar*)cur_node->children->content);
              }
            }
          }
        }
        rec_csnt_cad_vars(cur_node->children);
    }
}


int pesquisar_cad_sefaz(char *cnpj, char *uf){
  FILE *ter_infos_file;
  GSubprocess *processo=NULL;
  GError *erro=NULL;
  MYSQL_ROW row;
  MYSQL_RES *res;
  xmlDocPtr doc;

  char *formated_cnpj;
  doc = xmlNewDoc((xmlChar *)"1.0");
  xmlNodePtr cadTag = xmlNewNode(NULL, (xmlChar *)"cadastro");
  xmlNodePtr cnpjTag = xmlNewNode(NULL,(xmlChar *)"cnpj");
  xmlNodePtr ufTag = xmlNewNode(NULL,(xmlChar *)"uf");

  formated_cnpj = format_cnpj_num(cnpj);
  if(!cnpj){
    popup(NULL,"Erro ao formatar o cnpj");
    return 1;
  }

  xmlNodeSetContent(cnpjTag,(xmlChar *)formated_cnpj);
  xmlNodeSetContent(ufTag,(xmlChar *)uf);

  xmlAddChild(cadTag,cnpjTag);
  xmlAddChild(cadTag,ufTag);
  xmlDocSetRootElement(doc,cadTag);

  ter_infos_file = fopen(SCRPT_TER_INFOS_ENV,"w");
  if(!ter_infos_file){
    popup(NULL,"Não foi possivel abrir arquivo de comunicaçao");
    return 1;
  }

  if(xmlDocDump(ter_infos_file,doc)<=0){
    popup(NULL,"O arquivo de comunicaçao teve erro");
    return 1;
  }

  processo = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE,&erro,cad_emp_strc.script_bin_path,CAD_TER_PSQ_SCRIPT,NULL);
  if(!processo)
  {
    popup(NULL,"Não foi possivel enviar documento");
    autologger(erro->message);
    file_logger(erro->message);
    return 1;
  }

  return 0;
}


void janela_cad_ter_consulta(){

  	int len;
    GtkWidget *cnpj_entry,*uf_entry;
  	GtkWidget *janela_popup, *fields, *fixed, *box;
  	int resultado;
    xmlDocPtr recCadDoc;

  	janela_popup = gtk_dialog_new_with_buttons("Mensagem",NULL,GTK_DIALOG_MODAL,"Ok",GTK_RESPONSE_ACCEPT,"Cancelar",GTK_RESPONSE_REJECT,NULL);

  	gtk_window_set_title(GTK_WINDOW(janela_popup),"Mensagem");
  	gtk_window_set_icon_name(GTK_WINDOW(janela_popup),"user-availables");
  	gtk_window_set_keep_above(GTK_WINDOW(janela_popup),TRUE);

  	gtk_window_set_position(GTK_WINDOW(janela_popup),3);

  	fields = gtk_bin_get_child(GTK_BIN(janela_popup));
  	fixed = gtk_fixed_new();
  	box = gtk_box_new(0,0);
    cnpj_entry = gtk_entry_new();
    uf_entry = gtk_entry_new();

    if(escolha_doc()){
      return ;
    }
    gtk_entry_set_text(GTK_ENTRY(cnpj_entry),doc_ter);

  	gtk_box_pack_start(GTK_BOX(box),cnpj_entry,0,0,10);
    gtk_box_pack_start(GTK_BOX(box),uf_entry,0,0,10);
  	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

  	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

  	gtk_widget_grab_focus(uf_entry);
  	gtk_dialog_set_default_response(GTK_DIALOG(janela_popup),GTK_RESPONSE_ACCEPT);

  	gtk_widget_show_all(janela_popup);

  	resultado = gtk_dialog_run(GTK_DIALOG(janela_popup));
  	if(resultado == GTK_RESPONSE_ACCEPT){
      consulta_cnpj.cnpj =(gchar*) gtk_entry_get_text(GTK_ENTRY(cnpj_entry));
      consulta_cnpj.uf =(gchar*) gtk_entry_get_text(GTK_ENTRY(uf_entry));
      remove(SCRPT_TER_INFOS_RET);
      formatar_littobig(consulta_cnpj.uf);

      pesquisar_cad_sefaz(consulta_cnpj.cnpj,consulta_cnpj.uf);
      g_usleep(G_USEC_PER_SEC*4);
      recCadDoc = xmlParseFile(SCRPT_TER_INFOS_RET);
      if(!recCadDoc){
        popup(NULL,"Erro na comunicação do PHP com SEFAZ (LOGS)");
      }else{
        rec_csnt_cad_vars(xmlDocGetRootElement(recCadDoc));
        if(atoi(consulta_cnpj.cStat)!=111){
          popup(NULL,consulta_cnpj.xMotivo);
        }
      }
    }

    gtk_widget_destroy(janela_popup);
}
