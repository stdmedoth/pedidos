int critica_real(gchar *valor, GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	char *formatar;

	if(!valor)
	{
		valor = malloc(MAX_PRECO_LEN);
		strcpy(valor,"0.0");
		if(GTK_IS_WIDGET(entrada))
		{
			gtk_entry_set_text(GTK_ENTRY(entrada),valor);
			return 0;
		}
		return 0;
	}

	formatar = malloc(strlen(valor)+1);

	for(int cont=0;cont<strlen(valor);cont++)
	{
		if(valor[cont]==44){
			valor[cont] = 46;
		}else
		if(!(valor[cont] == 46)){
			if(!isdigit(valor[cont])){
				popup(NULL,"Insira valor");
				return 1;
			}
		}
	}

	//strcpy(formatar,valor);

	sprintf(formatar,"%.2f",atof(valor));

	if(entrada && GTK_ENTRY(entrada)!=NULL)
		gtk_entry_set_text(GTK_ENTRY(entrada),formatar);

	return 0;
}



int simp_critica_real(gchar *valor)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	char *formatar;

	if(!valor){
		g_print("valor nulo com ponteiro\n");
		return 1;
	}

	for(int cont=0;cont<strlen(valor);cont++){
		if(valor[cont] == 45){
			valor[cont] = 45;
		}else
		if(valor[cont] == 44){
			valor[cont] = 46;
		}else
		if( (valor[cont] != 46) && !isdigit(valor[cont]) && !isspace(valor[cont]) ){
			valor[cont] = ' ';
		}
	}
	return 0;
}
