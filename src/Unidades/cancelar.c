int und_cancelar_fun(){

  char task[MAX_CODE_LEN];
  sprintf(task,"%i",tasker("unidades"));
  gtk_entry_set_text(GTK_ENTRY(code_und_field),task);
  gtk_entry_set_text(GTK_ENTRY(name_und_field),"");
  gtk_entry_set_text(GTK_ENTRY(sigla_und_field),"");
  gtk_entry_set_text(GTK_ENTRY(mult_und_field),"");

  gtk_widget_set_sensitive(code_und_field,TRUE);
  gtk_widget_set_sensitive(und_alterar_button,TRUE);
  gtk_widget_set_sensitive(psq_cad_und_button,TRUE);

  gtk_widget_grab_focus(name_und_field);
  alterando_und=0;
  concluindo_und=0;

  return 0;
}
