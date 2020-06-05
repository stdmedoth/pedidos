int est_sald_est()
{
	est_sld_prod_est_int = gtk_combo_box_get_active(GTK_COMBO_BOX(est_sld_cod_combo));
	gtk_widget_grab_focus(est_sld_grp_cod_entry);
	est_sld_prod_fun();
	est_sald_subgrp_fun();
	return 0;
}
