static void
add_items (int terceiro)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from contatos where terceiro = %i",terceiro);
  contatos_ter = terceiro;
  Contato contato;
  g_return_if_fail (cont_lis != NULL);

  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível buscar contatos");
    return ;
  }
  while((row=mysql_fetch_row(res))){
    contato.id = atoi(row[CTTO_ID_COL]);;
    contato.nome = g_strdup (row[CTTO_NOME_COL]);
    contato.telefone = g_strdup (row[CTTO_TEL_COL]);
    contato.celular = g_strdup (row[CTTO_CEL_COL]);
    contato.email = g_strdup (row[CTTO_EMAIL_COL]);


    cntts[contato.id].id = atoi(row[CTTO_ID_COL]);
    cntts[contato.id].ativo = 1;
    cntts[contato.id].nome = g_strdup (row[CTTO_NOME_COL]);
    cntts[contato.id].telefone = g_strdup (row[CTTO_TEL_COL]);
    cntts[contato.id].celular = g_strdup (row[CTTO_CEL_COL]);
    cntts[contato.id].email = g_strdup (row[CTTO_EMAIL_COL]);
    contatos_qnt = contato.id+1;
    cntt_exists[contato.id] = 1;
    g_array_append_vals (cont_lis, &contato, 1);
  }
}

static GtkTreeModel *
create_items_model ()
{
  gint i = 0;
  GtkListStore *model;
  GtkTreeIter iter;

  /* create array */
  cont_lis = g_array_sized_new (FALSE, FALSE, sizeof (Contato), 1);

  /* create list store */
  model = gtk_list_store_new (NUM_ITEM_COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING);

  add_items(contatos_ter);

  /* add items */
  for (i = 0; i < cont_lis->len; i++)
    {
      gtk_list_store_append (model, &iter);

      gtk_list_store_set (model, &iter,
                          COLUMN_CTTO_ID,
                          g_array_index (cont_lis, Contato, i).id,
                          COLUMN_CTTO_NOME,
                          g_array_index (cont_lis, Contato, i).nome,
                          COLUMN_CTTO_CEL,
                          g_array_index (cont_lis, Contato, i).telefone,
                          COLUMN_CTTO_TEL,
                          g_array_index (cont_lis, Contato, i).celular,
                          COLUMN_CTTO_EMAIL,
                          g_array_index (cont_lis, Contato, i).email,
                          -1);
    }

  return GTK_TREE_MODEL (model);
}

static GtkTreeModel *
create_numbers_model (void)
{
#define N_NUMBERS 10
  gint i = 0;
  GtkListStore *model;
  GtkTreeIter iter;

  /* create list store */
  model = gtk_list_store_new (NUM_NUMBER_COLUMNS, G_TYPE_STRING, G_TYPE_INT);

  /* add numbers */
  for (i = 0; i < N_NUMBERS; i++)
    {
      char str[2];

      str[0] = '0' + i;
      str[1] = '\0';

      gtk_list_store_append (model, &iter);

      gtk_list_store_set (model, &iter,
                          COLUMN_NUMBER_TEXT, str,
                          -1);
    }

  return GTK_TREE_MODEL (model);

#undef N_NUMBERS
}

static void
add_item (GtkWidget *button, gpointer data)
{
  Contato contato;
  GtkTreeIter current, iter;
  GtkTreePath *path;
  GtkTreeModel *model;
  GtkTreeViewColumn *column;
  GtkTreeView *treeview = (GtkTreeView *)data;

  g_return_if_fail (cont_lis != NULL);

  contato.id = contatos_qnt;
  contato.nome = g_strdup ("Nome");
  contato.telefone = g_strdup ("Telefone");
  contato.celular = g_strdup ("Celular");
  contato.email = g_strdup ("Email");
  g_array_append_vals (cont_lis, &contato, 1);

  /* Insert a new row below the current one */
  gtk_tree_view_get_cursor (treeview, &path, NULL);
  model = gtk_tree_view_get_model (treeview);
  if (path)
    {
      gtk_tree_model_get_iter (model, &current, path);
      gtk_tree_path_free (path);
      gtk_list_store_insert_after (GTK_LIST_STORE (model), &iter, &current);
    }
  else
    {
      gtk_list_store_insert (GTK_LIST_STORE (model), &iter, -1);
    }

  /* Set the data for the new row */
  gtk_list_store_set (GTK_LIST_STORE(model), &iter,
                      COLUMN_CTTO_ID,
                      contato.id,
                      COLUMN_CTTO_NOME,
                      contato.nome,
                      COLUMN_CTTO_CEL,
                      contato.telefone,
                      COLUMN_CTTO_TEL,
                      contato.celular,
                      COLUMN_CTTO_EMAIL,
                      contato.email,
                      -1);
  contatos_qnt++;
  /* Move focus to the new row */
  path = gtk_tree_model_get_path (model, &iter);
  column = gtk_tree_view_get_column (treeview, 0);
  gtk_tree_view_set_cursor (treeview, path, column, FALSE);

  gtk_tree_path_free (path);
}

static void
remove_item (GtkWidget *widget, gpointer data)
{
  GtkTreeIter iter;
  GtkTreeView *treeview = (GtkTreeView *)data;
  GtkTreeModel *model = gtk_tree_view_get_model (treeview);
  GtkTreeSelection *selection = gtk_tree_view_get_selection (treeview);
  char query[MAX_QUERY_LEN];
  if (gtk_tree_selection_get_selected (selection, NULL, &iter))
    {
      gint i;
      GtkTreePath *path;

      path = gtk_tree_model_get_path (model, &iter);
      i = gtk_tree_path_get_indices (path)[0];
      sprintf(query,"delete from contatos where code = %i and terceiro = %i",cntts[i].id,contatos_ter);
      if(enviar_query(query)){
        popup(NULL,"Não foi possível deletar contato");
        return ;
      }

      cntts[i].ativo = 0;
      contatos_qnt--;
      gtk_list_store_remove (GTK_LIST_STORE (model), &iter);

      g_array_remove_index (cont_lis, i);

      gtk_tree_path_free (path);
    }
}

static gboolean
separator_row (GtkTreeModel *model,
               GtkTreeIter  *iter,
               gpointer      data)
{
  GtkTreePath *path;
  gint idx;

  path = gtk_tree_model_get_path (model, iter);
  idx = gtk_tree_path_get_indices (path)[0];

  gtk_tree_path_free (path);

  return idx == 5;
}

static void
editing_started (GtkCellRenderer *cell,
                 GtkCellEditable *editable,
                 const gchar     *path,
                 gpointer         data)
{
  gtk_combo_box_set_row_separator_func (GTK_COMBO_BOX (editable),
                                        separator_row, NULL, NULL);
}

static void
cell_edited (GtkCellRendererText *cell,
             const gchar         *path_string,
             const gchar         *new_text,
             gpointer             data)
{
  GtkTreeModel *model = (GtkTreeModel *)data;
  GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
  GtkTreeIter iter;

  gint column = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (cell), "column"));

  gtk_tree_model_get_iter (model, &iter, path);
  switch (column)
  {
    case COLUMN_CTTO_ID:
      {
        gint i;

        i = gtk_tree_path_get_indices (path)[0];
        g_array_index (cont_lis, Contato, i).id = atoi (new_text);

        cntts[i].id = atoi (new_text);
        cntts[i].ativo = 1;

        gtk_list_store_set (GTK_LIST_STORE (model), &iter, column,
                            g_array_index (cont_lis, Contato, i).id, -1);
      }
      break;

    case COLUMN_CTTO_NOME:
      {
        gint i;
        gchar *old_text;

        gtk_tree_model_get (model, &iter, column, &old_text, -1);
        g_free (old_text);

        i = gtk_tree_path_get_indices (path)[0];
        g_free (g_array_index (cont_lis, Contato, i).nome);
        g_array_index (cont_lis, Contato, i).nome = g_strdup (new_text);

        cntts[i].nome = g_strdup (new_text);
        cntts[i].ativo = 1;

        gtk_list_store_set (GTK_LIST_STORE (model), &iter, column,
                            g_array_index (cont_lis, Contato, i).nome, -1);
      }
      break;
    case COLUMN_CTTO_CEL:
      {
        gint i;
        gchar *old_text;

        gtk_tree_model_get (model, &iter, column, &old_text, -1);
        g_free (old_text);

        i = gtk_tree_path_get_indices (path)[0];
        g_free (g_array_index (cont_lis, Contato, i).celular);
        g_array_index (cont_lis, Contato, i).celular = g_strdup (new_text);

        cntts[i].ativo = 1;
        cntts[i].celular = g_strdup (new_text);

        gtk_list_store_set (GTK_LIST_STORE (model), &iter, column,
                            g_array_index (cont_lis, Contato, i).celular, -1);
      }
      break;
    case COLUMN_CTTO_TEL:
      {
        gint i;
        gchar *old_text;

        gtk_tree_model_get (model, &iter, column, &old_text, -1);
        g_free (old_text);

        i = gtk_tree_path_get_indices (path)[0];
        g_free (g_array_index (cont_lis, Contato, i).telefone);
        g_array_index (cont_lis, Contato, i).telefone = g_strdup (new_text);

        cntts[i].ativo = 1;
        cntts[i].telefone = g_strdup (new_text);

        gtk_list_store_set (GTK_LIST_STORE (model), &iter, column,
                            g_array_index (cont_lis, Contato, i).telefone, -1);
      }
      break;
    case COLUMN_CTTO_EMAIL:
      {
        gint i;
        gchar *old_text;

        gtk_tree_model_get (model, &iter, column, &old_text, -1);
        g_free (old_text);

        i = gtk_tree_path_get_indices (path)[0];
        g_free (g_array_index (cont_lis, Contato, i).email);
        g_array_index (cont_lis, Contato, i).email = g_strdup (new_text);

        cntts[i].ativo = 1;
        cntts[i].email = g_strdup (new_text);
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, column,
                            g_array_index (cont_lis, Contato, i).email, -1);
      }
      break;
    }

  gtk_tree_path_free (path);
}

static void
add_columns (GtkTreeView  *treeview,
             GtkTreeModel *items_model,
             GtkTreeModel *numbers_model)
{
  GtkCellRenderer *renderer;

  /* number column */
  renderer = gtk_cell_renderer_combo_new ();
  g_object_set (renderer,
                "model", numbers_model,
                "text-column", COLUMN_NUMBER_TEXT,
                "has-entry", FALSE,
                "editable", TRUE,
                NULL);
  g_signal_connect (renderer, "edited",
                    G_CALLBACK (cell_edited), items_model);
  g_signal_connect (renderer, "editing-started",
                    G_CALLBACK (editing_started), NULL);
  g_object_set_data (G_OBJECT (renderer), "column", GINT_TO_POINTER (COLUMN_CTTO_ID));

  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
                                               -1, "Id", renderer,
                                               "text", COLUMN_CTTO_ID,
                                               NULL);
  GtkTreeViewColumn *coluna = gtk_tree_view_get_column (GTK_TREE_VIEW (treeview),0);
  gtk_tree_view_column_set_visible(coluna,FALSE);

  renderer = gtk_cell_renderer_text_new ();
  g_object_set (renderer,
                "editable", TRUE,
                NULL);
  g_signal_connect (renderer, "edited",
                    G_CALLBACK (cell_edited), items_model);
  g_object_set_data (G_OBJECT (renderer), "column", GINT_TO_POINTER (COLUMN_CTTO_NOME));

  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
                                               -1, "Nome", renderer,
                                               "text", COLUMN_CTTO_NOME,
                                               NULL);

  renderer = gtk_cell_renderer_text_new ();
  g_object_set (renderer,
                "editable", TRUE,
                NULL);
  g_signal_connect (renderer, "edited",
                    G_CALLBACK (cell_edited), items_model);
  g_object_set_data (G_OBJECT (renderer), "column", GINT_TO_POINTER (COLUMN_CTTO_CEL));

  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
                                               -1, "Celular", renderer,
                                               "text", COLUMN_CTTO_CEL,
                                               NULL);
   renderer = gtk_cell_renderer_text_new ();
   g_object_set (renderer,
                 "editable", TRUE,
                 NULL);
   g_signal_connect (renderer, "edited",
                     G_CALLBACK (cell_edited), items_model);
   g_object_set_data (G_OBJECT (renderer), "column", GINT_TO_POINTER (COLUMN_CTTO_TEL));

   gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
                                                -1, "Telefone", renderer,
                                                "text", COLUMN_CTTO_TEL,
                                                NULL);
  renderer = gtk_cell_renderer_text_new ();
  g_object_set (renderer,
                "editable", TRUE,
                NULL);
  g_signal_connect (renderer, "edited",
                    G_CALLBACK (cell_edited), items_model);
  g_object_set_data (G_OBJECT (renderer), "column", GINT_TO_POINTER (COLUMN_CTTO_EMAIL));

  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeview),
                                               -1, "Email", renderer,
                                               "text", COLUMN_CTTO_EMAIL,
                                               NULL);
}

GtkWidget *
do_editable_cells ()
{
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *sw;
    GtkWidget *button;
    GtkWidget *treeview;
    GtkTreeModel *items_model;
    GtkTreeModel *numbers_model;

    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start (GTK_BOX (vbox),
                        gtk_label_new ("Contatos"),
                        FALSE, FALSE, 0);

    sw = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
                                         GTK_SHADOW_ETCHED_IN);
    gtk_widget_set_size_request(sw,300,200);
    g_signal_connect(sw,"size-allocate",G_CALLBACK(auto_hmover_scroll),sw);

    gtk_widget_set_size_request(vbox,300,200);
    gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 0);

    /* create models */
    items_model = create_items_model ();
    numbers_model = create_numbers_model ();

    /* create tree view */
    treeview = gtk_tree_view_new_with_model (items_model);
    contatos_treeview = treeview;
    gtk_tree_selection_set_mode (gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview)),
                                 GTK_SELECTION_SINGLE);

    add_columns (GTK_TREE_VIEW (treeview), items_model, numbers_model);

    g_object_unref (numbers_model);
    g_object_unref (items_model);

    gtk_container_add (GTK_CONTAINER (sw), treeview);

    /* some buttons */
    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_box_set_homogeneous (GTK_BOX (hbox), TRUE);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

    button = gtk_button_new_with_label ("Adicionar Contato");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (add_item), treeview);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label ("Remover Contato");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (remove_item), treeview);
    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

  return vbox;
}

int contatos_update(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];


  if(code_terc())
    return 1;

  contatos_ter = atoi(codigos_ter);
  for(int cont=0;cont<=contatos_qnt;cont++){
    if(cntts[cont].ativo){

      if(!cntts[cont].nome) cntts[cont].nome = "Nome";

      if(!cntts[cont].telefone) cntts[cont].telefone = "Telefone";

      if(!cntts[cont].celular) cntts[cont].celular = "Celular";

      if(!cntts[cont].email) cntts[cont].email = "Email";

      cntts[cont].id = cont;

      if(cntt_exists[cont]){
        sprintf(query,"update contatos set nome = '%s', telefone = '%s', celular = '%s', email = '%s' where terceiro = %i and code = %i",
        cntts[cont].nome,
        cntts[cont].telefone,
        cntts[cont].celular,
        cntts[cont].email,
        contatos_ter,
        cntts[cont].id);
      }else{
        sprintf(query,"insert into contatos(code,terceiro,nome, telefone, celular, email) values(%i, %i, '%s', '%s', '%s', '%s')",
        cntts[cont].id,
        contatos_ter,
        cntts[cont].nome,
        cntts[cont].telefone,
        cntts[cont].celular,
        cntts[cont].email);
      }
      if(enviar_query(query)){
        popup(NULL,"Não foi possível salvar contatos");
        return 1;
      }
    }
  }

  GtkListStore *contatos_model =(GtkListStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(	contatos_treeview ));
  if(contatos_model){
    g_object_ref(G_OBJECT(contatos_model));
    gtk_tree_view_set_model(GTK_TREE_VIEW(contatos_treeview),NULL);
    gtk_list_store_clear(contatos_model);
    gtk_tree_view_set_model(GTK_TREE_VIEW(contatos_treeview),GTK_TREE_MODEL(contatos_model));
  }
  return 0;
}
