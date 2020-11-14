int cotac_get_itens_qnt(int cod){
  int qnt=0;
  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    if(cotac_ativo[cod][cont]){
      qnt++;
    }
  }
  return qnt;
}

int cotac_get_livre_pos(){

  if(cotac_get_participante())
    return 1;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));

  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    g_print("recebendo infos em fornecedor %i posicao %i\n", cod, cont);
    if(cotac_ativo[cod][cont] == 0){
      g_print("index %i valor ativo %i\n",cod, cotac_ativo[cod][cont]);
      g_print("enviando %i...\n",cont);
      return cont;
    }
  }

  return 0;
}

int contac_get_ult_pos(){
  int pos=0;

  if(cotac_get_participante())
    return 0;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));

  for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
    if(cotac_ativo[cod][cont] != 0){
      pos = cont;
    }
  }
  return pos;
}

int cotac_add_item(GtkWidget *button, int cod){;

  int pos = cotac_get_livre_pos();

  if(pos >= MAX_COTAC_ITENS-1){
    popup(NULL,"Limite de Itens");
    return 1;
  }

  g_print("participante = %i\n", cod);
  g_print("pos = %i\n", pos);
  cotac_ativo[cod][pos] = 1;
  cotac_pPos[cod][pos] = pos;

  printf("ponteiro '%i'\n", cotac_pPos[cod][pos]);

  GtkWidget *cotac_prod_prod_frame = gtk_frame_new("Requisição");
  GtkWidget *cotac_prod_prod_box = gtk_box_new(0,0);
  GtkWidget *cotac_prod_qnt_frame = gtk_frame_new("Quantidade");
  GtkWidget *cotac_prod_qnt_box = gtk_box_new(0,0);
  GtkWidget *cotac_prod_prc_frame = gtk_frame_new("Preço");
  GtkWidget *cotac_prod_prc_box = gtk_box_new(0,0);

  cotac_prod_cod_entry[cod][pos] = gtk_entry_new();
  cotac_prod_nome_entry[cod][pos] = gtk_entry_new();
  cotac_psq_prod_button[cod][pos] = gtk_button_new();

  cotac_rem_button[cod][pos] = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(cotac_rem_button[cod][pos]),gtk_image_new_from_file(IMG_MENOS));
  gtk_widget_set_sensitive(cotac_rem_button[cod][pos],FALSE);

  gtk_button_set_image(GTK_BUTTON(cotac_psq_prod_button[cod][pos]),gtk_image_new_from_file(IMG_PESQ));
  gtk_editable_set_editable(GTK_EDITABLE(cotac_prod_nome_entry[cod][pos]),FALSE);
  gtk_entry_set_width_chars(GTK_ENTRY(cotac_prod_cod_entry[cod][pos]),9);
  gtk_entry_set_width_chars(GTK_ENTRY(cotac_prod_nome_entry[cod][pos]),20);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prod_box),cotac_prod_cod_entry[cod][pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prod_box),cotac_psq_prod_button[cod][pos],0,0,5);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prod_box),cotac_prod_nome_entry[cod][pos],0,0,5);
  gtk_container_add(GTK_CONTAINER(cotac_prod_prod_frame),cotac_prod_prod_box);

  if(cotac_container_exists[cod] && pos){
    if(cotac_add_button[cod]){
      gtk_widget_destroy(cotac_add_button[cod]);
  	}
  }

  GtkWidget *img_cotac_add_button = gtk_image_new_from_file(IMG_MAIS);
	cotac_add_button[cod]  = gtk_button_new();
	g_object_ref(cotac_add_button[cod]);
	g_object_ref_sink(cotac_add_button[cod]);
	gtk_button_set_image(GTK_BUTTON(cotac_add_button[cod]),img_cotac_add_button);

  cotac_prod_qnt_entry[cod][pos] = gtk_spin_button_new_with_range(1,1000000,1);
  gtk_entry_set_width_chars(GTK_ENTRY(cotac_prod_qnt_entry[cod][pos]),15);
  gtk_box_pack_start(GTK_BOX(cotac_prod_qnt_box),cotac_prod_qnt_entry[cod][pos],0,0,5);
  gtk_container_add(GTK_CONTAINER(cotac_prod_qnt_frame),cotac_prod_qnt_box);

  cotac_prod_prc_entry[cod][pos] = gtk_spin_button_new_with_range(0,1000000,0.05);
  gtk_entry_set_width_chars(GTK_ENTRY(cotac_prod_prc_entry[cod][pos]),15);
  gtk_box_pack_start(GTK_BOX(cotac_prod_prc_box),cotac_prod_prc_entry[cod][pos],0,0,5);
  gtk_container_add(GTK_CONTAINER(cotac_prod_prc_frame),cotac_prod_prc_box);

  GtkWidget *cotac_prod_linha = gtk_box_new(0,0);
  char *item_name = malloc(20);
  sprintf(item_name,"Item %i",pos+1);
  cotac_prod_frames[cod][pos] = gtk_frame_new(item_name);

  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_prod_prod_frame,0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_prod_qnt_frame,0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_prod_prc_frame,0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_rem_button[cod][pos],0,0,1);
  gtk_box_pack_start(GTK_BOX(cotac_prod_linha),cotac_add_button[cod],0,0,1);
  gtk_container_add(GTK_CONTAINER(cotac_prod_frames[cod][pos]),cotac_prod_linha);

  gtk_grid_attach (GTK_GRID(cotac_itens_grid[cod]), cotac_prod_frames[cod][pos],0,pos,1,1);

  #pragma GCC diagnostic ignored "-Wint-conversion"
  static int num;
  num = cod;
  g_signal_connect(cotac_add_button[cod],"clicked",G_CALLBACK(cotac_add_item), num);

  g_signal_connect(cotac_psq_prod_button[cod][pos],"clicked",G_CALLBACK(psq_req),cotac_prod_cod_entry[cod][pos]);

  g_signal_connect(cotac_prod_cod_entry[cod][pos],"activate",G_CALLBACK(cotat_itens_prod_fun), cotac_pPos[cod][pos]);
  g_signal_connect(cotac_prod_qnt_entry[cod][pos],"activate",G_CALLBACK(cotat_itens_qnt_fun), cotac_pPos[cod][pos]);
  g_signal_connect(cotac_prod_prc_entry[cod][pos],"activate",G_CALLBACK(cotat_itens_prc_fun), cotac_pPos[cod][pos]);

  g_signal_connect(cotac_rem_button[cod][pos], "clicked", G_CALLBACK(cotac_rem_item), cotac_pPos[cod][pos]);

  #pragma GCC diagnostic warning "-Wint-conversion"

  g_signal_connect(cotac_itens_grid[cod],"size-allocate",G_CALLBACK(auto_vmover_scroll),cotac_scroll[cod]);

  gtk_widget_grab_focus(cotac_prod_cod_entry[cod][pos]);
  gtk_widget_show_all(cotac_itens_grid[cod]);
  return 0;
}
