
int rec_fat_vist()
{
	int select=0;
	select = gtk_combo_box_get_active(GTK_COMBO_BOX(faturado_avista_combo));
	
	switch(select)
	{
		case 0:
			g_print("Tipo Faturado ou a vista não foi selecionado\n");
			tipo_pag = 0;
			break;
		case 1:
			g_print("Tipo Faturado foi selecionado\n");
			tipo_pag = 1;
			break;
		case 2:
			g_print("Tipo à vista foi selecionado\n");
			tipo_pag = 2;
			break;
	}
	for(int cont=0;cont<MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id==1)
		{
			qnt_prod_orc(NULL,cont);
		}
	}
	return 1;
}
