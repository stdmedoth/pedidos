int rel_fix_fin_rec_combovalor_fun(){

  rel_fix_fin_rec_valor_int = (gint )gtk_combo_box_get_active(GTK_COMBO_BOX(rel_fix_fin_rec_valor_combo));

  if(rel_fix_fin_rec_valor_int)
    gtk_widget_set_sensitive(rel_fix_fin_rec_valor_entry,TRUE);
  else
    gtk_widget_set_sensitive(rel_fix_fin_rec_valor_entry,FALSE);


  gtk_widget_grab_focus(rel_fix_fin_rec_valor_entry);
  return 0;
}


int rel_fix_fin_rec_entryvalor_fun(){
  rel_fix_fin_rec_valor_gchar = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_rec_valor_entry));

  gtk_widget_grab_focus(rel_fix_fin_rec_datacriacao_entry1);
  return 0;
}
