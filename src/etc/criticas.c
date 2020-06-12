int critica_real(gchar *valor, GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	char *formatar;

	//g_print("Iniciando funcao critica_real()\n");

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

	strcpy(formatar,valor);
	sprintf(valor,"%.2f",atof(formatar));

	gtk_entry_set_text(GTK_ENTRY(entrada),valor);

	//g_print("Finalizando funcao critica_real()\n");
	return 0;
}
