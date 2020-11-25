int cotac_get_participante(){
  cotac_partc_gchar = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(cotac_partc_combo));
  if(!cotac_partc_gchar || !strlen(cotac_partc_gchar)){
    return 1;
  }

  if(!strcmp(cotac_partc_gchar,"nulo")){
    //popup(NULL,"Selecione o Participante");
    return 1;
  }

  return 0;
}

int cotac_get_participante_container_livres(){

  for(int cont=0;cont<MAX_PARTC_QNT;cont++){
    if(!cotac_container_exists[cont])
      return cont;
  }

  return 0;
}


int cotac_load_participante(){

  return 1;
}

struct _Terceiros *cotac_get_participantes(){
  GtkTreeIter iter;
  GtkTreeIter *pIter;
  gchar *id = malloc(20);
  gchar *nome = malloc(500);
  int cont=0;

  struct _Terceiros *pTerceiros = malloc(sizeof(struct _Terceiros));
  pTerceiros->terceiro = malloc(sizeof(struct _terc_infos)*MAX_PARTC_QNT);

  GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(cotac_partc_combo));

  gtk_tree_model_get_iter_first(model,&iter);
  pIter = &iter;

  while(pIter){

    if(cont >= MAX_PARTC_QNT){
      popup(NULL,"Máximo de participantes;");
      pTerceiros->qnt = cont;
      return NULL;
    }

    gtk_tree_model_get (model, &iter, 1, &id, -1);
    gtk_tree_model_get (model, &iter, 0, &nome, -1);
    g_print("Id: %s\n", id);
    g_print("Nome: %s\n", nome);
    if(strcmp(id,"nulo")){
      pTerceiros->terceiro[cont].index = cont;
      pTerceiros->terceiro[cont].code = atoi(id);
      pTerceiros->terceiro[cont].razao = strdup(nome);
      cont++;
    }
    if(!gtk_tree_model_iter_next(model,&iter))
      break;
    pIter = &iter;
  }
  pTerceiros->qnt = cont;

  return pTerceiros;
}

int cotac_get_participante_index(int participante_atual){
  struct _Terceiros *Participantes = cotac_get_participantes();
  int participante_index=0;
  for(int cont=0;cont<MAX_PARTC_QNT;cont++){
    if(Participantes->terceiro[cont].code == participante_atual){
      participante_index = Participantes->terceiro[cont].index;
      return participante_index;
    }
  }
  return -1;
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

  int pos = cotac_get_participante_container_livres();
  if(pos>=MAX_PARTC_QNT){
    popup(NULL,"Máximo de participantes excedido");
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
    popup(NULL,"Não foi possível consultar Participante");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Participante não existe");
    return 1;
  }

  if(strlen(row[RAZ_TER_COL])>20)
    row[RAZ_TER_COL][20] = '\0';

  gchar *code = strdup(row[COD_TER_COL]);
  gchar *razao = strdup(row[RAZ_TER_COL]);
  if(code && razao){
    g_print("id: %s - Razão %s\n",code, razao);
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cotac_partc_combo),code,razao);
    gtk_combo_box_set_active_id(GTK_COMBO_BOX(cotac_partc_combo),code);
    cotac_partc_combo_fun();
  }else{
    popup(NULL,"Não foi possivel inserir informações do Participante");
    return 1;
  }
  return 0;
}


int cotac_partc_combo_fun(){

  while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

  if(cotac_get_participante())
    return 1;

  int participante_atual = atoi(cotac_partc_gchar);
  int participante_index = cotac_get_participante_index(participante_atual);
  if(participante_index == -1){
    popup(NULL,"Erro ao indexar participante");
    return 1;
  }

  if(!cotac_container_exists[participante_index]){
    cotac_container_exists[participante_index] = 1;
    cotac_itens_container[participante_index] = cotac_get_itens_container(participante_index);
    gtk_grid_attach(GTK_GRID(cotac_partc_itens),cotac_itens_container[participante_index],participante_index,0,1,1);
  }

  for(int cont=0;cont<MAX_PARTC_QNT;cont++){
    if(cont != participante_index)
      if(cotac_container_exists[cont]){
        gtk_widget_hide(cotac_itens_container[cont]);
    }
  }

  if(cotac_container_exists[participante_index])
    gtk_widget_show_all(cotac_itens_container[participante_index]);

  while (g_main_context_pending(NULL))
		g_main_context_iteration(NULL,FALSE);

  return 0;
}

int cotac_partc_remove_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(cotac_get_participante())
    return 1;

  struct _Terceiros *terceiros = cotac_get_participantes();
  gchar *id = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(cotac_partc_combo));
  int position = gtk_combo_box_get_active(GTK_COMBO_BOX(cotac_partc_combo));
  for(int cont=0;cont<terceiros->qnt;cont++){
    if(atoi(id)){
      if(atoi(id) == terceiros->terceiro[cont].code){
        sprintf(query,"delete from cotacoes_participantes WHERE cotacoes_id = %i and participante = %i",cotacao_new->code, terceiros->terceiro[cont].code);
        if(enviar_query(query)){
          popup(NULL,"Não foi possível retirar Participante");
          return 1;
        }
        cotac_container_exists[terceiros->terceiro[cont].index] = 0;
        gtk_widget_destroy(cotac_itens_container[terceiros->terceiro[cont].index]);
        gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(cotac_partc_combo),position);
        gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_partc_combo),0);
        return 0;
      }
    }
  }
  popup(NULL,"Sem participantes");
  return 0;
}
