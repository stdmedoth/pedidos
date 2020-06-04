int est_ent_tipo_fun()
{
	
	est_ent_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(est_ent_tipo_combo));
	
	if(est_ent_tipo_int==0)
	{
		popup(NULL,"Escolha o tipo de movimentação");
		gtk_widget_grab_focus(est_ent_tipo_combo);
		return 1;
	}
	
	gtk_widget_grab_focus(est_ent_prod_entry);
	
	return 0;
}
