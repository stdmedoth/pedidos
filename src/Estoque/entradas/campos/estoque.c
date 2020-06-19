int est_ent_est_fun()
{
	est_ent_est_int = gtk_combo_box_get_active(GTK_COMBO_BOX(est_ent_est_combo));	
	if(est_ent_est_int == 0)
	{
		popup(NULL,"Escolha o estoque");
		return 1;
	}
	
	return 0;
}
