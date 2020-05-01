int critica_real(gchar *valor, GtkWidget *entrada)
{
	int cont,ok=0,pos,qnt=0;
	char *mensagem;
	char *formatar;
	
	g_print("Iniciando funcao critica_real()\n");
	formatar = malloc(MAX_PRECO_LEN);
	mensagem = malloc(strlen("Caracter   incorreto")+MAX_PRECO_LEN);
	if(strlen(valor)<=0)
	{
		valor = malloc(MAX_PRECO_LEN);
		strcpy(valor,"0");
	}
	g_print("Verificando formato do numero float.\n");
	//transformar virgula em ponto
	for(pos=0;pos<=strlen(valor);pos++)
	{
		if(valor[pos]==44||valor[pos]==46)
		{
			if(valor[pos+1]==46||qnt>=1)
			{
				sprintf(mensagem,"Inserido Virgula duplicada\n");
				g_print(mensagem);
				popup(NULL,mensagem);
				return 1;
			}
			#ifdef __linux__
			valor[pos] = 46;
			#endif
			#ifdef WIN32
			valor[pos] = 44;
			#endif
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
	g_print("de: %s\n",valor);
	memset(formatar,0x0,MAX_PRECO_LEN);
	sprintf(formatar,"%.2f",atof(valor));
	
	for(pos=0;pos<=strlen(formatar);pos++)
	{
		if(formatar[pos]==44)
			formatar[pos] = 46;
		valor[pos] = formatar[pos];
	}

	g_print("para: %s\n",valor);
	if(!GTK_IS_WIDGET(entrada))
	{
		g_print("Finalizando funcao critica_real() sem gtk_entry_set_text\n");
		return 0;
	}
	
	gtk_entry_set_text(GTK_ENTRY(entrada),valor);
	g_print("Finalizando funcao critica_real() com gtk_entry_set_text\n");
	
	return 0;
}
