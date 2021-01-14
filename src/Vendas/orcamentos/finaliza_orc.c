int finalizacao_orc(){

  tracelogger_set_func_name("finalizacao_orc");
  int len;
	GtkWidget *finalizacao, *fields, *fixed, *box;
  GtkWidget *gerar_ask,*ped_ask;
  int resultado;

	finalizacao = gtk_dialog_new_with_buttons("Finaliza Orçamento",GTK_WINDOW(janela_orcamento),GTK_DIALOG_MODAL,"OK!",GTK_RESPONSE_ACCEPT,NULL);

	gtk_window_set_title(GTK_WINDOW(finalizacao),"Finaliza Orçamento");
	gtk_window_set_icon_name(GTK_WINDOW(finalizacao),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(finalizacao),TRUE);

	gtk_window_set_position(GTK_WINDOW(finalizacao),3);

  gerar_ask = gtk_check_button_new_with_label("Gerar Impressão?");
  ped_ask = gtk_check_button_new_with_label("Gerar Pedido?");

  if(codigo_orc())
    return 1;

  int orc_code = atoi(codigo_orc_gchar);

  if(orc_has_ped(orc_code))
    gtk_widget_set_sensitive(ped_ask,FALSE);


	fields = gtk_bin_get_child(GTK_BIN(finalizacao));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gerar_ask,0,0,10);
  gtk_box_pack_start(GTK_BOX(box),ped_ask,0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(finalizacao),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(finalizacao),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(finalizacao);

	resultado = gtk_dialog_run(GTK_DIALOG(finalizacao));
	if(resultado == GTK_RESPONSE_ACCEPT){
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ped_ask))){
      gera_orc_ped();
    }

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gerar_ask))){
      gerar_orc();
    }
  }

	gtk_widget_destroy(finalizacao);
  return 0;
}
