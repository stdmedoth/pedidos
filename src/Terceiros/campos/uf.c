int get_terceiro_origem(int code){
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *query = malloc(MAX_QUERY_LEN);

	sprintf(query,"select uf from terceiros where code = %i",code);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar origem do terceiro");
		return -1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Terceiro não existe");
		return -1;
	}
	if(!strcmp(cad_emp_strc.UF,row[0])){
		return TER_DENTRO_ESTADO;
	}else{
		return TER_FORA_ESTADO;
	}
}

int uf_terc()
{
	uf_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(uf_ter_field));
	if(strlen(uf_ter)<=0){
		if(terceiros.criticar.uf==0){
			uf_ter = malloc(MAX_UF_LEN);
			strcpy(uf_ter,"");
			if(escolha_tipo_ter()!=0)
				return 1;

			return 0;
		}
		popup(NULL,"Por favor insira a uf do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(uf_ter_field));
		return 1;
	}

	if(strlen(uf_ter)>MAX_UF_LEN){
		popup(NULL,"UF muito grande\nPor favor use sigla");
		gtk_widget_grab_focus(uf_ter_field);
		return 1;
	}

	if(escolha_tipo_ter()!=0)
		return 1;

	return 0;
}
