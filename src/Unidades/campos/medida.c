int medida_und()
{
	medidas_und = gtk_combo_box_get_active(GTK_COMBO_BOX(medida_und_combo_box));
	if(medidas_und==0)
	{
		popup(NULL,"insira a medida");
		return 1;
	}
	return 0;
}
