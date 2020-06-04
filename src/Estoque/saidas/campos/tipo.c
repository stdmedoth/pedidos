int est_said_tipo_fun()
{
	
	est_said_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(est_said_tipo_combo));
	
	if(est_said_tipo_int==0)
	{
		popup(NULL,"Escolha o tipo de movimentação");
		gtk_widget_grab_focus(est_said_tipo_combo);
		return 1;
	}
	
	gtk_widget_grab_focus(est_said_prod_entry);
	
	return 0;
}
