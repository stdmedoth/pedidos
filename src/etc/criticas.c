int critica_real(gchar *valor, GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	char *formatar;

	formatar = malloc(MAX_PRECO_LEN);
	mensagem = malloc(strlen("Caracter  incorreto")+MAX_PRECO_LEN);

	if(strlen(valor)<=0)
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

	for(int cont=0;cont<=strlen(valor);cont++)
	{
		if(valor[cont]==44)
			valor[cont] = 46;
	}
	strcpy(formatar,valor);
	sprintf(valor,"%.2f",atof(formatar));

	if(entrada && GTK_ENTRY(entrada)!=NULL)
		gtk_entry_set_text(GTK_ENTRY(entrada),valor);

	return 0;
}
