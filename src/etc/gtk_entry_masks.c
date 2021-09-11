int gtk_entry_cellphone(GtkEditable *editable, gpointer user_data){
  printf("editando %s\n", (gchar*)user_data);
  return 0;
}

int gtk_entry_telephone(GtkEditable *editable, gpointer user_data){

  return 0;
}
