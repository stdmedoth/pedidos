int orc_date()
{
  data_orc_gchar = (char *)gtk_entry_get_text(GTK_ENTRY(data_orc_entry));
  if(!formatar_data(data_orc_gchar)){
    gtk_widget_grab_focus(data_orc_entry);
    return 1;
  }
  return 0;
}
