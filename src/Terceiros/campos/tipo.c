int terci_tipo=0;

int escolha_tipo_ter()
{
	int pos=0;
	pos = gtk_combo_box_get_active(GTK_COMBO_BOX(type_ter_field));
	tipo_ter = malloc(MAX_TIPO_LEN);

	switch(pos)
	{
		case TIPO_TER_NULL:
			terci_tipo = 0;
			if(terceiros.criticar.tipo==0){
				strcpy(tipo_ter,"");
				gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),1);
				gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
				return 0;
			}
			terci_tipo = TIPO_TER_NULL;
			strcpy(tipo_ter,"Indiferente");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			break;
		case TIPO_TER_CLI:
			terci_tipo = TIPO_TER_CLI;
			strcpy(tipo_ter,"Cliente");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			break;
		case TIPO_TER_FRN:
			terci_tipo = TIPO_TER_FRN;
			strcpy(tipo_ter,"Fornecedor");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			break;
		case TIPO_TER_CLIFRN:
			terci_tipo = TIPO_TER_CLIFRN;
			strcpy(tipo_ter,"Cliente/Fornecedor");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			break;
		case TIPO_TER_TRSP:
			terci_tipo = TIPO_TER_TRSP;
			strcpy(tipo_ter,"Transportadora");
			g_print("O terceiro é %s\n",tipo_ter);
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
			break;
	}

	return 0;
}
