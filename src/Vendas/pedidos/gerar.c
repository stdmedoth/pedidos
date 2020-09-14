int gerar_ped()
{
	char *pedido_code =(char*) gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(strlen(pedido_code))
		gerar_orcs( atoi(pedido_code) );
	else{
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	return 0;
}
