int ped_gerar()
{
	char *pedido_code =(char*) gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(!strlen(pedido_code)){
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	struct _orc *orc = orc_get_orc(atoi(pedido_code));
	if(!orc){
		popup(NULL,"Não foi possível criar estrutura do orçamento");
		return 1;
	}
	orc_print_operation_fun(orc);
	return 0;
}
