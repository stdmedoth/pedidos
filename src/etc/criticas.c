int critica_real(char *preco,GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	mensagem = malloc(50);
	g_print("Verificando formato do numero float.\n");
	//transformar virgula em ponto
	for(pos=0;pos<=strlen(preco);pos++)
	{
		if(preco[pos]==44||preco[pos]==46)
		{
			qnt++;
			if(preco[pos+1]==46||qnt>1)
			{
				sprintf(mensagem,"Inserido Virgula duplicada");
				g_print(mensagem);
				popup(NULL,mensagem);
				return 1;
			}
			preco[pos] = 46;
			gtk_entry_set_text(GTK_ENTRY(entrada),preco);
			qnt++;
		}
	}
	//verifica se é formado apenas de numeros e virgula
	g_print("strlen %li\n",strlen(preco));
	ok=1;
	for(pos=0;pos<strlen(preco);pos++)
	{	
		for(cont=48;cont<=57;cont++)
		{
		
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
		if(ok!=0)
		{
			sprintf(mensagem,"Caracter '%c' incorreto",preco[pos]);
			popup(NULL,mensagem);
			return 1;
		}
	}
	return 0;
}
