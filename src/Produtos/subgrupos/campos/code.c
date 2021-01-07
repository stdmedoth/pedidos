int cod_subgrp(){
	subgrpcode = malloc(MAX_CODE_LEN);
	subgrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_entry));
	if(stoi(subgrpcode)==-1)
	{
		popup(NULL,"O campo deve ser preenchido com um código");
		return 1;
	}
	if(strlen(subgrpcode)>MAX_CODE_LEN)
	{
		popup(NULL,"O código está muito extenso");
		return 1;
	}

	if(alterando_subgrp==0&&concluindo_subgrp==0)
	{
		altera_subgrupo();
	}
	return 0;
}
