int terci_tipo=0;

int escolha_tipo_ter()
{
	int pos=0;
	pos = gtk_combo_box_get_active(GTK_COMBO_BOX(type_ter_field));
	tipo_ter = malloc(MAX_TIPO_LEN);

	switch(pos)
	{
		case 0:
			terci_tipo = 0;
			if(terceiros.criticar.tipo==0)
			{
				strcpy(tipo_ter,"");
				gtk_widget_grab_focus(prazo_ter_field);
				return 0;
			}
			terci_tipo = 1;
			strcpy(tipo_ter,"Cliente");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			gtk_widget_grab_focus(celular_ter_field);
			break;
		case 1:
			terci_tipo = 1;
			strcpy(tipo_ter,"Cliente");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			gtk_widget_grab_focus(celular_ter_field);
			break;
		case 2:
			terci_tipo = 2;
			strcpy(tipo_ter,"Fornecedor");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			gtk_widget_grab_focus(celular_ter_field);
			break;
		case 3:
			terci_tipo = 3;
			strcpy(tipo_ter,"Cliente/Fornecedor");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			gtk_widget_grab_focus(celular_ter_field);
			break;
	}

	return 0;
}
