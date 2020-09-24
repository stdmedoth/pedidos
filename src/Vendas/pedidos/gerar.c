int ped_gerar()
{
	char *pedido_code =(char*) gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(strlen(pedido_code))
		gerar_orcs_full( atoi(pedido_code) );
	else{
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	return 0;
}
