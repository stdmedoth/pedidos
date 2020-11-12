int cotac_get_itens_qnt(){
  int qnt=0;
  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    if(cotac_ativo[cont]){
      qnt++;
    }
  }
  return qnt;
}

int cotac_get_livre_pos(){
  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    if(!cotac_ativo[cont]){
      return cont;
    }else{
      gtk_widget_set_sensitive(cotac_rem_button[cont],TRUE);
    }
  }
  return MAX_COTAC_ITENS;
}

int contac_get_ult_pos(){
  int pos=0;
  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    if(cotac_ativo[cont]){
      pos = cont;
    }
  }
  return pos;
}

int cotac_add_item(){;
  int pos = cotac_get_livre_pos();
  cotac_pPos[pos] = pos;
  cotac_ativo[pos] = 1;

  if(pos == MAX_COTAC_ITENS){
    popup(NULL,"Limite de Itens");
    return 1;
  }

  printf("ponteiro '%i'\n", cotac_pPos[pos]);
  GtkWidget *cotac_prod_prod_frame = gtk_frame_new("Produto");
  GtkWidget *cotac_prod_prod_box = gtk_box_new(0,0);
  GtkWidget *cotac_prod_qnt_frame = gtk_frame_new("Quantidade");
  GtkWidget *cotac_prod_qnt_box = gtk_box_new(0,0);
  GtkWidget *cotac_prod_prc_frame = gtk_frame_new("Preço");
  GtkWidget *cotac_prod_prc_box = gtk_box_new(0,0);

  cotac_prod_cod_entry[pos] = gtk_entry_new();
  cotac_prod_nome_entry[pos] = gtk_entry_new();
  cotac_psq_prod_button[pos] = gtk_button_new();

  cotac_rem_button[pos] = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(cotac_rem_button[pos]),gtk_image_new_from_file(IMG_MENOS));
  gtk_widget_set_sensitive(cotac_rem_button[pos],FALSE);

  gtk_button_set_image(GTK_BUTTON(cotac_psq_prod_button[pos]),gtk_image_new_from_file(IMG_PESQ));
  gtk_editable_set_editable(GTK_EDITABLE(cotac_prod_nome_entry[pos]),FALSE);
  gtk_entry_set_width_chars(GTK_ENTRY(cotac_prod_cod_entry[pos]),9);
  gtk_entry_set_width_chars(GTK_ENTRY(cotac_prod_nome_entry[pos]),20);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prod_box),cotac_prod_cod_entry[pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prod_box),cotac_psq_prod_button[pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prod_box),cotac_prod_nome_entry[pos],0,0,5);
  gtk_container_add(GTK_CONTAINER(cotac_prod_prod_frame),cotac_prod_prod_box);

  if(GTK_IS_WIDGET(cotac_add_button)){
		gtk_widget_destroy(cotac_add_button);
	}

  GtkWidget *img_cotac_add_button = gtk_image_new_from_file(IMG_MAIS);
	cotac_add_button  = gtk_button_new();
	g_object_ref(cotac_add_button);
	g_object_ref_sink(cotac_add_button);
	gtk_button_set_image(GTK_BUTTON(cotac_add_button),img_cotac_add_button);

  cotac_prod_qnt_entry[pos] = gtk_spin_button_new_with_range(1,100,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_qnt_box),cotac_prod_qnt_entry[pos],0,0,5);
  gtk_container_add(GTK_CONTAINER(cotac_prod_qnt_frame),cotac_prod_qnt_box);

  cotac_prod_prc_entry[pos] = gtk_spin_button_new_with_range(1,100,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prc_box),cotac_prod_prc_entry[pos],0,0,5);
  gtk_container_add(GTK_CONTAINER(cotac_prod_prc_frame),cotac_prod_prc_box);

  GtkWidget *cotac_prod_linha = gtk_box_new(0,0);
  char *item_name = malloc(20);
  sprintf(item_name,"Item %i",pos+1);
  cotac_prod_frames[pos] = gtk_frame_new(item_name);

  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_prod_prod_frame,0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_prod_qnt_frame,0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_prod_prc_frame,0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_rem_button[pos],0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_add_button,0,0,1);
  gtk_container_add(GTK_CONTAINER(cotac_prod_frames[pos]),cotac_prod_linha);

  gtk_grid_attach (GTK_GRID(cotac_itens_grid), cotac_prod_frames[pos],0,pos,1,1);

  #pragma GCC diagnostic ignored "-Wint-conversion"
  g_signal_connect(cotac_rem_button[pos], "clicked", G_CALLBACK(cotac_rem_item), cotac_pPos[pos]);

  g_signal_connect(cotac_prod_cod_entry[pos],"activate",G_CALLBACK(cotat_itens_prod_fun),cotac_pPos[pos]);
  g_signal_connect(cotac_prod_qnt_entry[pos],"activate",G_CALLBACK(cotat_itens_qnt_fun),cotac_pPos[pos]);
  g_signal_connect(cotac_prod_prc_entry[pos],"activate",G_CALLBACK(cotat_itens_prc_fun),cotac_pPos[pos]);
  #pragma GCC diagnostic warning "-Wint-conversion"

  g_signal_connect(cotac_add_button,"clicked",G_CALLBACK(cotac_add_item),NULL);
  g_signal_connect(cotac_itens_grid,"size-allocate",G_CALLBACK(auto_vmover_scroll),cotac_scroll);

  cotac_pPos[pos] = 1;
  gtk_widget_grab_focus(cotac_prod_cod_entry[pos]);
  gtk_widget_show_all(cotac_itens_grid);
  return 0;
}
