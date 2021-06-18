int ter_cliente_desde(){

  char *formatado;
  ter_cliente_desde_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(ter_cliente_desde_entry));

  if(strlen(ter_cliente_desde_gchar)<=0){
		ter_cliente_desde_gchar = "NULL";
    gtk_widget_grab_focus(name_ter_field);
		return 0;
	}

  if(!(formatado = formatar_data(ter_cliente_desde_gchar))){
    gtk_widget_grab_focus(ter_cliente_desde_entry);
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(ter_cliente_desde_entry),formatado);

  ter_cliente_desde_gchar = malloc(40 + MAX_DATE_LEN);
  sprintf(ter_cliente_desde_gchar, "STR_TO_DATE('%s', '%%d/%%m/%%Y')", formatado);

  gtk_widget_grab_focus(name_ter_field);

  return 0;
}
