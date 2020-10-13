int rel_fix_fin_pag_status_fun(){
  rel_fix_fin_pag_status_int = (gint) gtk_combo_box_get_active(GTK_COMBO_BOX(rel_fix_fin_pag_status_combo));

  if(rel_fix_fin_pag_status_int!=STAT_PENDENTE){
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_entry1,TRUE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_entry2,TRUE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_button1,TRUE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_button2,TRUE);

    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_entry1,TRUE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_entry2,TRUE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_button1,TRUE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_button2,TRUE);
  }
  else{
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_entry1,FALSE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_entry2,FALSE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_button1,FALSE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_databaixa_button2,FALSE);

    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_entry1,FALSE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_entry2,FALSE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_button1,FALSE);
    gtk_widget_set_sensitive(rel_fix_fin_pag_bx_button2,FALSE);
  }

  gtk_widget_grab_focus(rel_fix_fin_pag_valor_entry);
  return 0;
}
