int suporte_princ_add(){

  GtkWidget *descr_scrolls = gtk_scrolled_window_new(NULL,NULL);;

  sup_vet_posts_qnt[sup_posts_qnt] = sup_posts_qnt;

  postlist[sup_posts_qnt] = gtk_box_new(1,0);
  titulo_list[sup_posts_qnt] = gtk_entry_new();
  descr_list[sup_posts_qnt] = gtk_text_view_new();
  sup_deleta_button[sup_posts_qnt] = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(sup_deleta_button[sup_posts_qnt]),gtk_image_new_from_icon_name("user-trash",GTK_ICON_SIZE_SMALL_TOOLBAR));
  descr_scrolls = gtk_scrolled_window_new(NULL,NULL);


  gtk_widget_set_size_request(descr_scrolls,450,100);

  gtk_entry_set_width_chars(GTK_ENTRY(titulo_list[sup_posts_qnt]),35);
  //gtk_widget_set_size_request(descr_list[sup_posts_qnt],450,50);
  gtk_widget_set_name(descr_list[sup_posts_qnt],"textview");
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(descr_list[sup_posts_qnt]),GTK_WRAP_WORD);

  gtk_container_add(GTK_CONTAINER(descr_scrolls),descr_list[sup_posts_qnt]);

  gtk_box_pack_start(GTK_BOX(postlist[sup_posts_qnt]),titulo_list[sup_posts_qnt],0,0,5);
  gtk_box_pack_start(GTK_BOX(postlist[sup_posts_qnt]),descr_scrolls,0,0,5);
  gtk_box_pack_start(GTK_BOX(postlist[sup_posts_qnt]),sup_deleta_button[sup_posts_qnt],0,0,5);

  gtk_grid_attach(GTK_GRID(suport_grid),postlist[sup_posts_qnt],0,sup_posts_qnt,1,1);

  gtk_widget_grab_focus(titulo_list[sup_posts_qnt]);

  #pragma GCC diagnostic ignored "-Wint-conversion"
  g_signal_connect(titulo_list[sup_posts_qnt],"activate",G_CALLBACK(suporte_princ_atualiza_title),sup_vet_posts_qnt[sup_posts_qnt]);
  g_signal_connect(titulo_list[sup_posts_qnt],"focus-out-event",G_CALLBACK(suporte_princ_atualiza_title),sup_vet_posts_qnt[sup_posts_qnt]);

  g_signal_connect(descr_list[sup_posts_qnt],"focus-out-event",G_CALLBACK(suporte_princ_atualiza_descr),sup_vet_posts_qnt[sup_posts_qnt]);

  g_signal_connect(sup_deleta_button[sup_posts_qnt],"clicked",G_CALLBACK(suporte_princ_exclui_post),sup_vet_posts_qnt[sup_posts_qnt]);
  #pragma GCC diagnostic warning "-Wint-conversion"

  sup_posts_qnt++;
  sup_vet_posts_qnt[sup_posts_qnt] = sup_posts_qnt;


  gtk_widget_show_all(suport_grid);
  return 0;
}
