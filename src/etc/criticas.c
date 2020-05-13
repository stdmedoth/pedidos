int critica_real(char *preco,GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	mensagem = malloc(50);
	//transformar virgula em ponto
	if(strlen(preco)<=0)
	{
		preco = malloc(MAX_PRECO_LEN);
		sprintf(preco,"00.00");
	}
	for(pos=0;pos<=strlen(preco);pos++)
	{
		if(preco[pos]==44||preco[pos]==46)
		{
			qnt++;
			if(preco[pos+1]==46||qnt>1)
			{
				sprintf(mensagem,"Virgula duplicada para preço");
				g_print(mensagem);
				popup(NULL,mensagem);
				return 1;
			}
			preco[pos] = 46;

			qnt++;
		}
	}
	sprintf(preco,"%.2f",atof(preco));
	//verifica se é formado apenas de numeros e virgula
	for(pos=0;pos<=strlen(preco);pos++)
	{
		for(cont=48;cont<=57;cont++)
		{
			
		}
		for(cont=48;cont<=57;cont++)
		{
			g_print("strlen %li\n",strlen(preco));
			g_print("%c %c\n",preco[pos],cont);
			if(preco[pos]==cont)
			{
				ok = 0;
				break;
			}
			if(preco[pos]==44||preco[pos]==46)
			{
				ok = 0;
				break;
			}
			ok++;
		}
		if(ok>10)
		{
			sprintf(mensagem,"Caracter '%c' incorreto para preço",preco[pos-1]);
			popup(NULL,mensagem);
			return 1;
		}
	}
	if(GTK_IS_WIDGET(entrada))
	{
		gtk_entry_set_text(GTK_ENTRY(entrada),preco);
	}
	return 0;
}
