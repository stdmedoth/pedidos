int rec_fat_vist()
{
	int select=0;
	select = gtk_combo_box_get_active(GTK_COMBO_BOX(faturado_avista_combo));
	switch(select)
	{
		case 0:
			g_print("Tipo Faturado ou a vista não foi selecionado\n");
			orc_faturado = 0;
			orc_vista = 0;
			break;
		case 1:
			g_print("Tipo Faturado foi selecionado\n");
			orc_faturado = 1;
			orc_vista = 0;
			break;
		case 2:
			g_print("Tipo à vista foi selecionado\n");
			orc_vista = 1;
			orc_faturado = 0;
			break;
	}
	return 1;
}
