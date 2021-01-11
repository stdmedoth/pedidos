GtkWidget *mkt_email_get_tags(){

  GtkWidget *box = gtk_box_new(0,0);
  GtkWidget *scroll_box = gtk_box_new(1,0);
  GtkWidget *scroll = gtk_scrolled_window_new(NULL,NULL);

  gtk_widget_set_size_request(scroll_box,400,300);
  gtk_widget_set_size_request(scroll,400,300);
  gtk_widget_set_size_request(box,400,300);

  for(int cont=0; cont<MAIL_TAGS_QNT; cont++){
    gchar *tag_name = malloc( strlen(mail_tags_vet[cont][0]) + strlen(mail_tags_vet[cont][1]) + 10);

    sprintf(tag_name, "%s : %s",
      mail_tags_vet[cont][1],
      mail_tags_vet[cont][0]);

    GtkWidget *label_tag = gtk_label_new(tag_name);
    gtk_label_set_selectable (GTK_LABEL(label_tag), TRUE);
    gtk_box_pack_start(GTK_BOX(scroll_box), label_tag ,0, 0, 5);
  }
  gtk_container_add(GTK_CONTAINER(scroll), scroll_box);
  gtk_box_pack_start(GTK_BOX(box), scroll,0,0,0);

  return box;
}
