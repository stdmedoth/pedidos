int mkt_envmail_model_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  gchar *modelo_email = (gchar*) gtk_entry_get_text(GTK_ENTRY(mkt_envmail_model_entry));
  if(!strlen(modelo_email)){
    popup(NULL,"Necessário inserir modelo de email");
    return 1;
  }

  sprintf(query,"select m.nome, h.conteudo, b.conteudo, f.conteudo from emails_model as m join emails_header as h join emails_body as b join emails_footer as f on h.code = m.code and b.code = m.code and f.code = m.code where m.code = %s", modelo_email);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível buscar modelo de email");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Modelo de email não existente");
    return 1;
  }
  gtk_widget_grab_focus(mkt_envmail_list_treeview);
  return 0;
}
int mkt_envmail_enviar_distri(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  gchar *modelo_email = (gchar*) gtk_entry_get_text(GTK_ENTRY(mkt_envmail_model_entry));
  if(!strlen(modelo_email)){
    popup(NULL,"Necessário inserir modelo de email");
    return 1;
  }

  sprintf(query,"select m.nome, h.conteudo, b.conteudo, f.conteudo from emails_model as m join emails_header as h join emails_body as b join emails_footer as f on h.code = m.code and b.code = m.code and f.code = m.code where m.code = %s", modelo_email);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível buscar modelo de email");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Modelo de email não existente");
    return 1;
  }

  gchar *assunto = strdup(row[0]);
  if(!strlen(assunto)){
    popup(NULL,"Modelo sem assunto");
    return 1;
  }
  gchar *conteudo = malloc(strlen(row[1]) + strlen(row[2]) + strlen(row[3]) + 100);
  sprintf(conteudo,
    "<html>"
      "<head>%s</head>"
      "<body>%s</body>"
      "<footer>%s</footer>"
      "</html>",
      row[1], row[2], row[3]);

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
  };

  GtkTreeIter env_iter;
  GtkTreeStore *envmodel = (GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(mkt_envmail_envlist_treeview));
  if(!envmodel){
    popup(NULL,"TreeView sem modelo");
    return 1;
  }
  if(!gtk_tree_model_iter_children(GTK_TREE_MODEL(envmodel), &env_iter, NULL)){
    popup(NULL,"Sem emails a enviar");
    return 1;
  }

  char *id = malloc(MAX_CODE_LEN);
  char *nome = malloc(MAX_NAME_LEN);
  char *email = malloc(MAX_EMAIL_LEN);
  char *celular = malloc(MAX_CEL_LEN);
  char *telefone = malloc(MAX_TEL_LEN);

  if(envmodel){
    while((1)){
      gtk_tree_model_get (GTK_TREE_MODEL(envmodel), &env_iter,
        ID, &id,
        NOME, &nome,
        EMAIL, &email,
        CELULAR, &celular,
        TELEFONE, &telefone,
        -1);

      char *conteudo_editado;
      if(nome && strlen(nome))
        conteudo_editado = replaceWord(conteudo, "mktmail_nome_cliente", nome);
      else
        conteudo_editado = strdup(conteudo);

      if(conteudo_editado && strlen(conteudo_editado)){

        while (g_main_context_pending(NULL))
          g_main_context_iteration(NULL,FALSE);

        if(enviar_email_html(assunto, nome, email, conteudo_editado))
          autologger("Email não enviado");
      }else{
        autologger("Não foi possível formatar html do email");
      }

      if(!gtk_tree_store_remove(GTK_TREE_STORE(envmodel), &env_iter))
        break;

    }
  }
  popup(NULL,"Processo finalizado");

  return 0;
}

void mkt_models_envlist_add_contato(){

   enum{
     ID,
     NOME,
     EMAIL,
     CELULAR,
     TELEFONE,
   };

  GtkTreeSelection *selection;
 	GtkTreeModel *list_model, *env_model;
 	GtkTreeIter list_iter, env_iter;
  char *id = malloc(MAX_CODE_LEN);
  char *nome = malloc(MAX_NAME_LEN);
  char *email = malloc(MAX_EMAIL_LEN);
  char *celular = malloc(MAX_CEL_LEN);
  char *telefone = malloc(MAX_TEL_LEN);

 	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (mkt_envmail_list_treeview));
 	if(!gtk_tree_selection_get_selected(selection, &list_model, &list_iter))
 		return ;

 	gtk_tree_model_get (list_model, &list_iter,
    ID, &id,
    NOME, &nome,
    EMAIL, &email,
    CELULAR, &celular,
    TELEFONE, &telefone,
    -1);

  env_model = gtk_tree_view_get_model(GTK_TREE_VIEW(mkt_envmail_envlist_treeview));
  if(!env_model)
    return ;

  gtk_tree_store_append(GTK_TREE_STORE(env_model),&env_iter,NULL);
  gtk_tree_store_set(GTK_TREE_STORE(env_model),&env_iter,
  ID,id,
  NOME,nome,
  EMAIL,email,
  CELULAR,celular,
  TELEFONE,telefone,
  -1);

  gtk_tree_store_remove(GTK_TREE_STORE(list_model),&list_iter);
 }

GtkTreeStore *mkt_models_list_get_model(){

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };
  GtkTreeIter campos;
  GtkTreeStore *model =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(mkt_envmail_list_treeview));
  if(!model)
    model = gtk_tree_store_new(N_COLS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING);

  g_object_ref(G_OBJECT(model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(mkt_envmail_list_treeview),NULL);
  gtk_tree_store_clear(model);
  gtk_tree_view_set_model(GTK_TREE_VIEW(mkt_envmail_list_treeview),GTK_TREE_MODEL(model));

  GtkTreeStore *envmodel =(GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(mkt_envmail_envlist_treeview));
  if(envmodel)
    gtk_tree_store_clear(envmodel);

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];
  gchar *distribuicao = (gchar*)gtk_entry_get_text(GTK_ENTRY(mkt_envmail_distrib_entry));

  if(!strlen(distribuicao))
    return NULL;

  sprintf(query,"select t.code, t.razao, c.email, c.telefone, c.celular from PessoasDistribuicao as d inner join terceiros as t inner join contatos as c on t.code = d.pessoa and c.terceiro = t.code where d.distribuicao = %s", distribuicao);
  if(!(res = consultar(query))){
    return NULL;
  }
  while((row = mysql_fetch_row(res))){

    if(!strlen(row[EMAIL]))
      continue;

    gtk_tree_store_append(model,&campos,NULL);
    gtk_tree_store_set(model,&campos,
    ID,row[ID],
    NOME,row[NOME],
    EMAIL,row[EMAIL],
    CELULAR,row[CELULAR],
    TELEFONE,row[TELEFONE],
    -1);
  }
  gtk_widget_grab_focus(mkt_envmail_model_entry);
  return model;
}

int mkt_models_envia_emails(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"envio_emails");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Envio de Emails");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"mail-replied");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	gtk_widget_set_size_request(janela,1200,600);

  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };


	janelas_gerenciadas.vetor_janelas[REG_ENVMAIL_WND].reg_id = REG_ENVMAIL_WND;
	janelas_gerenciadas.vetor_janelas[REG_ENVMAIL_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_ENVMAIL_WND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_ENVMAIL_WND].janela_pointer = janela;

  GtkWidget *mkt_envmail_list_scroll, *mkt_envmail_envlist_scroll;
  GtkWidget *mkt_envmail_list_frame, *mkt_envmail_envlist_frame;
  GtkWidget *mkt_envmail_list_fixed, *mkt_envmail_envlist_fixed;
  GtkWidget *linha1, *linha2, *linha3;
  GtkWidget *box1, *box2;
  GtkWidget *box;
  GtkWidget *opcoes_box;

  GtkTreeStore *model;
  GtkWidget *mkt_envmail_distrib_frame = gtk_frame_new("Distribuição");
  GtkWidget *mkt_envmail_distrib_box = gtk_box_new(0,0);
  GtkWidget *mkt_envmail_distrib_fixed = gtk_fixed_new();
  GtkWidget *mkt_envmail_distrib_psq_button = gtk_button_new();
  GtkWidget *mkt_envmail_model_frame = gtk_frame_new("Modelo");
  GtkWidget *mkt_envmail_model_box = gtk_box_new(0,0);
  GtkWidget *mkt_envmail_model_fixed = gtk_fixed_new();
  GtkWidget *mkt_envmail_model_psq_button = gtk_button_new();
  GtkTreeStore *mkt_envmail_list_model = gtk_tree_store_new(N_COLS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);
  GtkTreeStore *mkt_envmail_envlist_model = gtk_tree_store_new(N_COLS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);

  mkt_envmail_distrib_entry = gtk_entry_new();
  mkt_envmail_model_entry = gtk_entry_new();
  mkt_envmail_list_fixed = gtk_fixed_new();
  mkt_envmail_envlist_fixed = gtk_fixed_new();
  mkt_envmail_list_treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(mkt_envmail_list_model));
  mkt_envmail_envlist_treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(mkt_envmail_envlist_model));
  mkt_envmail_list_scroll = gtk_scrolled_window_new(NULL,NULL);
  mkt_envmail_envlist_scroll = gtk_scrolled_window_new(NULL,NULL);
  mkt_envmail_list_frame = gtk_frame_new("Distribuição atual:");
  mkt_envmail_envlist_frame = gtk_frame_new("Enviar para:");

  gtk_widget_set_size_request(mkt_envmail_list_scroll, 500, 400);
  gtk_widget_set_size_request(mkt_envmail_envlist_scroll, 500, 400);
  gtk_widget_set_size_request(mkt_envmail_list_treeview, 500, 400);
  gtk_widget_set_size_request(mkt_envmail_envlist_treeview, 500, 400);

  GtkCellRenderer *mkt_envmail_list_idcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_list_idcol = gtk_tree_view_column_new_with_attributes("Id", mkt_envmail_list_idcell, "text", ID, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_list_treeview ), mkt_envmail_list_idcol, ID);
  GtkCellRenderer *mkt_envmail_list_nomecell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_list_nomecol = gtk_tree_view_column_new_with_attributes("Nome", mkt_envmail_list_nomecell, "text", NOME, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_list_treeview ), mkt_envmail_list_nomecol, NOME);
  GtkCellRenderer *mkt_envmail_list_emailcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_list_emailcol = gtk_tree_view_column_new_with_attributes("Email", mkt_envmail_list_emailcell, "text", EMAIL, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_list_treeview ), mkt_envmail_list_emailcol, EMAIL);
  GtkCellRenderer *mkt_envmail_list_celularcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_list_celularcol = gtk_tree_view_column_new_with_attributes("Celular", mkt_envmail_list_celularcell, "text", CELULAR, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_list_treeview ), mkt_envmail_list_celularcol, CELULAR);
  GtkCellRenderer *mkt_envmail_list_telefonecell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_list_telefonecol = gtk_tree_view_column_new_with_attributes("Telefone" , mkt_envmail_list_telefonecell, "text", TELEFONE, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_list_treeview ), mkt_envmail_list_telefonecol, TELEFONE);

  GtkCellRenderer *mkt_envmail_envlist_idcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_envlist_idcol = gtk_tree_view_column_new_with_attributes("Id", mkt_envmail_envlist_idcell, "text", ID, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_envlist_treeview ), mkt_envmail_envlist_idcol, ID);
  GtkCellRenderer *mkt_envmail_envlist_nomecell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_envlist_nomecol = gtk_tree_view_column_new_with_attributes("Nome", mkt_envmail_envlist_nomecell, "text", NOME, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_envlist_treeview ), mkt_envmail_envlist_nomecol, NOME);
  GtkCellRenderer *mkt_envmail_envlist_emailcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_envlist_emailcol = gtk_tree_view_column_new_with_attributes("Email", mkt_envmail_envlist_emailcell, "text", EMAIL, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_envlist_treeview ), mkt_envmail_envlist_emailcol, EMAIL);
  GtkCellRenderer *mkt_envmail_envlist_celularcell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_envlist_celularcol = gtk_tree_view_column_new_with_attributes("Celular", mkt_envmail_envlist_celularcell, "text", CELULAR, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_envlist_treeview ), mkt_envmail_envlist_celularcol, CELULAR);
  GtkCellRenderer *mkt_envmail_envlist_telefonecell = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *mkt_envmail_envlist_telefonecol = gtk_tree_view_column_new_with_attributes("Telefone" , mkt_envmail_envlist_telefonecell, "text", TELEFONE, NULL);
  gtk_tree_view_insert_column (GTK_TREE_VIEW( mkt_envmail_envlist_treeview ), mkt_envmail_envlist_telefonecol, TELEFONE);

  gtk_tree_view_column_set_visible(mkt_envmail_envlist_idcol, FALSE);
  gtk_tree_view_column_set_visible(mkt_envmail_list_idcol, FALSE);


  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];
  GtkTreeIter campos;

  sprintf(query,"select t.code, t.razao, c.email, c.telefone, c.celular from PessoasDistribuicao as d inner join terceiros as t inner join contatos as c on t.code = d.pessoa and c.terceiro = t.code");
  if(!(res = consultar(query))){
    return 1;
  }

  while((row = mysql_fetch_row(res))){

    if(!strlen(row[EMAIL]))
      continue;

    gtk_tree_store_append(mkt_envmail_list_model,&campos,NULL);
    gtk_tree_store_set(mkt_envmail_list_model,&campos,
    ID,row[ID],
    NOME,row[NOME],
    EMAIL,row[EMAIL],
    CELULAR,row[CELULAR],
    TELEFONE,row[TELEFONE],
    -1);
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(mkt_envmail_list_treeview), GTK_TREE_MODEL(mkt_envmail_list_model));
  gtk_tree_view_set_model(GTK_TREE_VIEW(mkt_envmail_envlist_treeview), GTK_TREE_MODEL(mkt_envmail_envlist_model));

  mkt_envmail_concluir_button = gtk_button_new_with_label("Concluir");
  gtk_button_set_image(GTK_BUTTON(mkt_envmail_concluir_button), gtk_image_new_from_file(IMG_OK));
  mkt_envmail_cancelar_button = gtk_button_new_with_label("Cancelar");
  gtk_button_set_image(GTK_BUTTON(mkt_envmail_cancelar_button), gtk_image_new_from_file(IMG_CANCEL));
  mkt_envmail_envia_button = gtk_button_new_with_label("Enviar");
  gtk_button_set_image(GTK_BUTTON(mkt_envmail_envia_button), gtk_image_new_from_icon_name("mail-replied", GTK_ICON_SIZE_BUTTON));

  opcoes_box = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(opcoes_box), mkt_envmail_concluir_button,0,0,20);
  gtk_box_pack_start(GTK_BOX(opcoes_box), mkt_envmail_cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(opcoes_box), mkt_envmail_envia_button,0,0,5);

  gtk_container_add(GTK_CONTAINER(mkt_envmail_list_scroll), mkt_envmail_list_treeview);
  gtk_container_add(GTK_CONTAINER(mkt_envmail_envlist_scroll), mkt_envmail_envlist_treeview);
  gtk_container_add(GTK_CONTAINER(mkt_envmail_list_frame), mkt_envmail_list_scroll);
  gtk_container_add(GTK_CONTAINER(mkt_envmail_envlist_frame), mkt_envmail_envlist_scroll);
  gtk_fixed_put(GTK_FIXED(mkt_envmail_list_fixed), mkt_envmail_list_frame, 20, 20);
  gtk_fixed_put(GTK_FIXED(mkt_envmail_envlist_fixed), mkt_envmail_envlist_frame, 20, 20);

  gtk_entry_set_width_chars(GTK_ENTRY(mkt_envmail_distrib_entry), 8);
  gtk_entry_set_width_chars(GTK_ENTRY(mkt_envmail_model_entry), 8);
  gtk_entry_set_placeholder_text(GTK_ENTRY(mkt_envmail_distrib_entry), "Código");
  gtk_entry_set_placeholder_text(GTK_ENTRY(mkt_envmail_model_entry), "Modelo");
  gtk_button_set_image(GTK_BUTTON(mkt_envmail_distrib_psq_button), gtk_image_new_from_file(IMG_PESQ));
  gtk_button_set_image(GTK_BUTTON(mkt_envmail_model_psq_button), gtk_image_new_from_file(IMG_PESQ));

  gtk_box_pack_start(GTK_BOX(mkt_envmail_distrib_box), mkt_envmail_distrib_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_envmail_distrib_box), mkt_envmail_distrib_psq_button,0,0,5);
  gtk_container_add(GTK_CONTAINER(mkt_envmail_distrib_frame), mkt_envmail_distrib_box);
  gtk_fixed_put(GTK_FIXED(mkt_envmail_distrib_fixed), mkt_envmail_distrib_frame, 20,20);

  gtk_box_pack_start(GTK_BOX(mkt_envmail_model_box), mkt_envmail_model_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(mkt_envmail_model_box), mkt_envmail_model_psq_button,0,0,5);
  gtk_container_add(GTK_CONTAINER(mkt_envmail_model_frame), mkt_envmail_model_box);
  gtk_fixed_put(GTK_FIXED(mkt_envmail_model_fixed), mkt_envmail_model_frame, 20,20);

  linha1 = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(linha1), mkt_envmail_distrib_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha1), mkt_envmail_model_fixed,0,0,0);

  linha2 = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(linha2), mkt_envmail_list_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(linha2), mkt_envmail_envlist_fixed,0,0,0);

  box = gtk_box_new(1,0);
  box1 = gtk_box_new(1,0);
  box2 = gtk_box_new(1,0);

  gtk_box_pack_start(GTK_BOX(box1), linha1,0,0,0);
  gtk_box_pack_start(GTK_BOX(box2), linha2,0,0,0);

  gtk_box_pack_start(GTK_BOX(box), box1,0,0,5);
  gtk_box_pack_start(GTK_BOX(box), box2,0,0,5);
  gtk_box_pack_start(GTK_BOX(box), opcoes_box,0,0,5);


  gtk_container_add(GTK_CONTAINER(janela), box);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_ENVMAIL_WND]);
  g_signal_connect(mkt_envmail_list_treeview,"row-activated",G_CALLBACK(mkt_models_envlist_add_contato),NULL);
  g_signal_connect(mkt_envmail_distrib_entry,"activate",G_CALLBACK(mkt_models_list_get_model),NULL);
  g_signal_connect(mkt_envmail_model_entry,"activate",G_CALLBACK(mkt_envmail_model_fun),NULL);
  g_signal_connect(mkt_envmail_envia_button,"clicked",G_CALLBACK(mkt_envmail_enviar_distri),NULL);


  gtk_widget_show_all(janela);
  return 0;
}
