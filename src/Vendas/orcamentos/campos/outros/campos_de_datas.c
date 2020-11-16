void rec_tipo_condpag(){
  if(orc_pag_tipo_int == CONDPAG_S_FIN){
     orc_pag_sem_finan();
  }

  if(orc_pag_tipo_int == CONDPAG_DT_LVR){
    orc_pag_datas_livres();
  }

  if(orc_pag_tipo_int == CONDPAG_DIAS || orc_pag_tipo_int == CONDPAG_MESES){
    orc_pag_datas_fun();
  }
}

GtkWidget *orc_campos_datas(){
  GtkWidget *orc_pag_datas_parcqnt_frame, *orc_pag_datas_parcqnt_fixed,*rest_parcqnt_box;
  GtkWidget *orc_pag_datas_livres_rest_frame, *orc_pag_datas_livres_rest_fixed;
  GtkWidget *orc_pag_datas_livres_scroll,
  *orc_pag_datas_livres_scroll_box;

  GtkWidget *orc_pag_datas_livres_label1,
  *orc_pag_datas_livres_label2,
  *orc_pag_datas_livres_box,
  *orc_pag_datas_livres_frame;

  GtkWidget *orc_pag_datas_livres_label2_fixed,
  *orc_pag_datas_livres_label1_fixed;

  orc_pag_datas_entry1 = malloc(sizeof(GtkEntry*)*MAX_PARCELAS_QNT);
  orc_pag_datas_entry2 = malloc(sizeof(GtkEntry*)*MAX_PARCELAS_QNT);

  orc_pag_datas_parcqnt = gtk_spin_button_new_with_range(1,MAX_PARCELAS_QNT,1);
  gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_parcqnt),5);
  orc_pag_datas_parcqnt_frame = gtk_frame_new("Num. Parcelas:");
  orc_pag_datas_parcqnt_fixed = gtk_fixed_new();

  rest_parcqnt_box = gtk_box_new(1,0);
  orc_pag_datas = gtk_box_new(0,0);

  orc_pag_datas_livres_rest = gtk_entry_new();
  gtk_widget_set_sensitive(orc_pag_datas_livres_rest,FALSE);
  gtk_widget_set_name(orc_pag_datas_livres_rest,"entry_unsensetivate");
  gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_livres_rest),5);
  orc_pag_datas_livres_rest_frame = gtk_frame_new("Valor Restante:");
  orc_pag_datas_livres_rest_fixed = gtk_fixed_new();

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_parcqnt_frame),orc_pag_datas_parcqnt);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_parcqnt_fixed),orc_pag_datas_parcqnt_frame,10,20);

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_rest_frame),orc_pag_datas_livres_rest);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_rest_fixed),orc_pag_datas_livres_rest_frame,10,20);

  orc_pag_datas_livres_qnt_entry = gtk_entry_new();
  orc_pag_datas_livres_label1 = gtk_label_new("Datas");
  orc_pag_datas_livres_label2 = gtk_label_new("Valor");
  orc_pag_datas_livres_label1_fixed = gtk_fixed_new();
  orc_pag_datas_livres_label2_fixed = gtk_fixed_new();
  orc_pag_datas_grid = gtk_grid_new();
  orc_pag_datas_livres_box = gtk_box_new(0,0);
  gtk_widget_set_name(orc_pag_datas_livres_box,"caixa_frame");
  orc_pag_datas_livres_frame = gtk_frame_new("Datas Livres");
  orc_pag_datas_livres_fixed = gtk_fixed_new();
  orc_pag_datas_livres_scroll = gtk_scrolled_window_new(NULL,NULL);
  orc_pag_datas_livres_scroll_box = gtk_box_new(0,0);

  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_label1_fixed),orc_pag_datas_livres_label1,20,20);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_label2_fixed),orc_pag_datas_livres_label2,20,20);

  gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_livres_label1_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_livres_label2_fixed,1,0,1,1);

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_scroll),orc_pag_datas_grid);
  gtk_box_pack_start(GTK_BOX(orc_pag_datas_livres_scroll_box),orc_pag_datas_livres_scroll,0,0,0);

  gtk_box_pack_start(GTK_BOX(orc_pag_datas_livres_box),orc_pag_datas_livres_scroll_box,0,0,5);

  gtk_box_pack_start(GTK_BOX(rest_parcqnt_box),orc_pag_datas_parcqnt_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(rest_parcqnt_box),orc_pag_datas_livres_rest_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(orc_pag_datas_livres_box),rest_parcqnt_box,0,0,5);

  gtk_widget_set_size_request(orc_pag_datas_livres_scroll,330,200);
  gtk_widget_set_size_request(orc_pag_datas_livres_box,330,200);
  gtk_widget_set_size_request(orc_pag_datas_grid,330,200);

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_frame),orc_pag_datas_livres_box);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_fixed),orc_pag_datas_livres_frame,20,20);

  gtk_box_pack_start(GTK_BOX(orc_pag_datas),orc_pag_datas_livres_fixed,0,0,0);

  g_signal_connect(orc_pag_datas_parcqnt,"activate",G_CALLBACK(orc_pag_datas_livres),NULL);
  g_signal_connect(orc_pag_datas_parcqnt,"value-changed",G_CALLBACK(rec_tipo_condpag),NULL);

  return orc_pag_datas;
}
