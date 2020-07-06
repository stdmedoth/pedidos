int relat_ter_query_manual(){
  relat_ter_query_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(relat_ter_query_entry));
  relat_ter_gerar_fun();
  return 0;
}
