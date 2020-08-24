int rel_fix_fin_rec_datacriacao1_fun(){
  rel_fix_fin_rec_datacriacao_gchar1 = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_rec_datacriacao_entry1));

  gtk_widget_grab_focus(rel_fix_fin_rec_datacriacao_entry2);
  return 0;
}


int rel_fix_fin_rec_datacriacao2_fun(){
  rel_fix_fin_rec_datacriacao_gchar2 = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_rec_datacriacao_entry2));

  if(gtk_widget_get_sensitive(rel_fix_fin_rec_databaixa_entry1))
    gtk_widget_grab_focus(rel_fix_fin_rec_databaixa_entry1);
  else
    gtk_widget_grab_focus(rel_fix_fin_rec_datavencimento_entry1);

  return 0;
}
