gboolean sobre_infos_keyfun(GtkWidget *widget, GdkEventKey  *event, gpointer   user_data){

  if(event->keyval == GDK_KEY_F1){
    info_sobre_wnd();
    return TRUE;
  }
  return FALSE;
}

int info_sobre_wnd(){
  GtkWidget *janela = gtk_about_dialog_new ();
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(janela), "v1.0.0");
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(janela), "Calisto Pedidos");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(janela), "Software gerencial para controle de vendas, compras, financeiro, estoque e marketing.");
  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(janela), "GPL v2");
  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(janela), TRUE);
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(janela), "GitHub");
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(janela), "https://github.com/stdmedoth/pedidos");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(janela), gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(LOGO_PEQUENA))));
  char *autores[] = {"João Calisto", NULL};
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(janela), (const char**)autores);
  gtk_widget_show_all(janela);
  int response = gtk_dialog_run(GTK_DIALOG(janela));
  gtk_widget_destroy(janela);

  return 0;
}
