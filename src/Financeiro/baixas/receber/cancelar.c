int cad_bxs_rec_cancelar_fun(){

  char *titulo = malloc(MAX_CODE_LEN);
  sprintf(titulo,"%i",rec_baixas.titulo_code);

  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_code_entry),titulo);
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_code_id_spin),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_cli_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_parcela_spin),"0");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_datacriacao_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_datavencimento_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_rec_valor_entry),"");

  cad_bxs_rec_alterando=0;
  cad_bxs_rec_concluindo=0;

  gtk_widget_set_sensitive(cad_bxs_rec_code_id_spin,TRUE);
  gtk_widget_set_sensitive(cad_bxs_rec_code_button,TRUE);
  gtk_widget_set_sensitive(cad_bxs_rec_alterar_button,TRUE);

  gtk_widget_grab_focus(cad_bxs_rec_code_entry);

  return 0;
}
