int cad_titulos_pagar(){
    GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(janela),3);
    gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
    gtk_window_set_title(GTK_WINDOW(janela),"Títulos à Pagar");
    gtk_window_set_icon_name(GTK_WINDOW(janela),"document-edit");
    if(personalizacao.janela_keep_above==1)
      gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
    gtk_container_set_border_width (GTK_CONTAINER (janela), 10);


    gtk_widget_show_all(janela);
    return 0;
}
