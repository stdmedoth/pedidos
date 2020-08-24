int trsp_cad_nument_fun(){
  trsp_cad_nument_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_nument_entry));

  if(!strlen(trsp_cad_nument_gchar)){
    popup(NULL,"O número da entrega precisa ser inserido");
    return 1;
  }

  gtk_widget_grab_focus(trsp_cad_orc_entry);
  return 0;
}
