int prod_precos_cancelar_fun(){

  gchar *task = malloc(12);

  sprintf(task, "%i", tasker("precos"));
  gtk_entry_set_text(GTK_ENTRY(prod_prc_code_entry), task);

  gtk_entry_set_text(GTK_ENTRY(prod_prc_prodcode_entry), "");
  gtk_entry_set_text(GTK_ENTRY(prod_prc_nome_entry), "");
  gtk_entry_set_text(GTK_ENTRY(prod_prc_prodnome_entry), "");
  gtk_entry_set_text(GTK_ENTRY(prod_prc_vlrfat_entry), "");
  gtk_entry_set_text(GTK_ENTRY(prod_prc_vlrvist_entry), "");

  prod_precos_alterando=0;
  prod_precos_concluindo=0;

  gtk_widget_set_sensitive(prod_prc_alterar_button, TRUE);
  gtk_widget_set_sensitive(prod_prc_codepsq_button, TRUE);
  gtk_widget_set_sensitive(prod_prc_code_entry, TRUE);
  gtk_widget_grab_focus(prod_prc_nome_entry);

  return 0;
}
