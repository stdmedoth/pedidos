int critica_real(gchar *valor,GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	char *formatar;
	formatar = malloc(50);
	mensagem = malloc(50);
	g_print("Verificando formato do numero float.\n");
	//transformar virgula em ponto
	for(pos=0;pos<=strlen(valor);pos++)
	{
		if(valor[pos]==44||valor[pos]==46)
		{
			if(valor[pos+1]==46||qnt>=1)
			{
				sprintf(mensagem,"Inserido Virgula duplicada");
				g_print(mensagem);
				popup(NULL,mensagem);
				return 1;
			}
			valor[pos] = 46;
			
			qnt++;
		}
	}
	//verifica se é formado apenas de numeros e virgula
	g_print("strlen %li\n",strlen(valor));
	ok=1;
	for(pos=0;pos<strlen(valor);pos++)
	{	
		for(cont=48;cont<=57;cont++)
		{
		
			g_print("%c %c\n",valor[pos],cont);
			if(valor[pos]==cont)
			{
				ok = 0;
				break;
			}
			if(valor[pos]==44||valor[pos]==46)
			{
				ok = 0;
				break;
			}
			ok++;	
		}
		if(ok!=0)
		{
			sprintf(mensagem,"Caracter '%c' incorreto",valor[pos]);
			popup(NULL,mensagem);
			return 1;
		}
	}
	sprintf(formatar,"%.2f",atof(valor));
	gtk_entry_set_text(GTK_ENTRY(entrada),formatar);
	return 0;
}
