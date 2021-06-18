int ter_nome_fantasia_fun(){
  ter_nome_fantasia_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(ter_nome_fantasia_entry));
  if(strlen(ter_nome_fantasia_gchar)<=0){
    ter_nome_fantasia_gchar = strdup("");
    return 0;
  }

  gtk_widget_grab_focus(cep_ter_field);
  return 0;

}
