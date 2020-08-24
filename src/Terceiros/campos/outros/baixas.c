int chamar_ter_cadbaixas(){

  if(code_terc() || name_terc())
    return 1;

  if(janelas_gerenciadas.vetor_janelas[CAD_BX_REC_WND].fun())
    return 1;

  gtk_button_clicked(GTK_BUTTON(cad_bxs_rec_code_button));

  while (g_main_context_pending(NULL))
    g_main_context_iteration(NULL,FALSE);

  gtk_entry_set_text(GTK_ENTRY(fin_rec_psq_entry),nomes_ter);
  gtk_widget_activate(fin_rec_psq_entry);

  return 0;
}


int chamar_ter_relbaixas(){

  int alterar_cliente=0;

  if(code_terc() || name_terc())
    return 1;

  if(janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].fun())
    return 1;

  while (g_main_context_pending(NULL))
    g_main_context_iteration(NULL,FALSE);

  gtk_entry_set_text(GTK_ENTRY(rel_fix_fin_rec_cli_entry1),codigos_ter);
  gtk_entry_set_text(GTK_ENTRY(rel_fix_fin_rec_cli_entry2),codigos_ter);
  gtk_widget_activate(rel_fix_fin_rec_cli_entry1);
  gtk_widget_activate(rel_fix_fin_rec_cli_entry2);

  return 0;
}
