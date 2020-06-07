int cad_rel_tabel_fun()
{
	cad_rel_tabel_int = gtk_combo_box_get_active(GTK_COMBO_BOX(cad_rel_tabel_combo));
	if(cad_rel_tabel_int == 0 )
	{
		popup(NULL,"Selecione a tabela");
		gtk_widget_grab_focus(cad_rel_tabel_combo);
		return 1;
	}
	return 0;
}
