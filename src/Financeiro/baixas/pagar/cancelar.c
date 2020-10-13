int cad_bxs_pag_cancelar_fun(){

  char *titulo = malloc(MAX_CODE_LEN);
  sprintf(titulo,"%i",pag_baixas.titulo_code);

  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_code_entry),titulo);
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_code_id_spin),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_cli_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_parcela_spin),"0");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datavencimento_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_valor_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_parcvalor_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_bxrvalor_entry),"");

  cad_bxs_pag_alterando=0;
  cad_bxs_pag_concluindo=0;

  gtk_widget_set_sensitive(cad_bxs_pag_code_id_spin,TRUE);
  gtk_widget_set_sensitive(cad_bxs_pag_code_button,TRUE);
  gtk_widget_set_sensitive(cad_bxs_pag_parcela_spin,TRUE);
  gtk_widget_set_sensitive(cad_bxs_pag_alterar_button,TRUE);

  gtk_widget_grab_focus(cad_bxs_pag_code_entry);

  return 0;
}
