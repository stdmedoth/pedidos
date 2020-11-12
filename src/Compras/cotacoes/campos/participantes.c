int cotac_get_participante(){
  cotac_partc_gchar = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(cotac_partc_combo));
  if(!strlen(cotac_partc_gchar)){
    popup(NULL,"Não foi possível receber o Participante");
    return 1;
  }
  if(!strcmp(cotac_partc_gchar,"nulo")){
    popup(NULL,"Necessário escolher o Participante");
    return 1;
  }

  return 0;
}

struct _Terceiros *cotac_get_participantes(){
  GtkTreeIter iter;
  GtkTreeIter *pIter;
  gchar *id = malloc(20);
  gchar *nome = malloc(20);
  int cont=0;
  struct _Terceiros *pTerceiros = malloc(sizeof(struct _Terceiros *));
  pTerceiros->terceiro = malloc(sizeof(struct _Terceiros *)*MAX_COTAC_ITENS);

  GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(cotac_partc_combo));
  gtk_tree_model_get_iter_first(model,&iter);
  pIter = &iter;

  while(pIter){
    gtk_tree_model_get (model, &iter, 1, &id, -1);
    gtk_tree_model_get (model, &iter, 0, &nome, -1);
    g_print("Id: %s\n", id);
    g_print("Nome: %s\n", nome);
    pTerceiros->terceiro[cont].code = atoi(id);
    pTerceiros->terceiro[cont].razao = strdup(nome);
    cont++;
    if(!gtk_tree_model_iter_next(model,&iter))
      break;

    pIter = &iter;
  }
  pTerceiros->qnt = cont;

  return pTerceiros;
}

int cotac_partc_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  gchar *text = (gchar*) gtk_entry_get_text(GTK_ENTRY(cotac_partc_entry));
  if(!strlen(text)){
    popup(NULL,"Participante não existe");
    return 1;
  }

  GtkTreeIter iter;
  gchar *id = malloc(20);
  GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(cotac_partc_combo));
  gtk_combo_box_get_active_iter(GTK_COMBO_BOX(cotac_partc_combo), &iter);
  gtk_tree_model_get (model, &iter, 1, &id, -1);
  struct _Terceiros *terceiros = cotac_get_participantes();
  for(int cont=0;cont<terceiros->qnt;cont++){
    if(atoi(text)){
      if(atoi(text) == terceiros->terceiro[cont].code){
        popup(NULL,"Participante já inserido");
        return 1;
      }
    }
  }

  sprintf(query,"SELECT * FROM terceiros WHERE code = %s",text);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar fornecedor");
    return 1;
  }
  int prct = atoi(text);
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Fornecedor não existe");
    return 1;
  }
  if(strlen(row[RAZ_TER_COL])>20)
    row[RAZ_TER_COL][20] = '\0';


  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cotac_partc_combo),row[COD_TER_COL],row[RAZ_TER_COL]);
  return 0;
}


int cotac_partc_combo_fun(){

  if(cotac_get_participante())
    return 1;

  int prct = atoi(cotac_partc_gchar);
  if(!cotac_container_exists[prct]){
    cotac_container_exists[prct] = 1;
    cotac_itens_container[prct] = cotac_get_itens_container(prct);
    gtk_box_pack_start(GTK_BOX(cotac_partc_itens),cotac_itens_container[prct],0,0,0);
  }

  struct _Terceiros *terceiros = cotac_get_participantes();
  if(terceiros){
    for(int cont=0;cont<MAX_VETOR_POSCODE;cont++){
      if(cotac_container_exists[cont])
        gtk_widget_hide(cotac_itens_container[cont]);
    }
  }

  if(cotac_container_exists[prct])
    gtk_widget_show_all(cotac_itens_container[prct]);
  return 0;
}
