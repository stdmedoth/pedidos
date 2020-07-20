int trocar_desktop(GtkWidget *widget,GtkWidget *event,int posicao)
{
	int numero = posicao;
	int erro;
	char *query;
	query = malloc(MAX_QUERY_LEN);

	if(inicializando == 1){
		sprintf(query,"update perfil_desktop set desktop_img = %i where code = %i",numero,sessao_oper.code);
		erro = enviar_query(query);
		if(erro!=0)
		{
			popup(NULL,"Não foi possivel inserir imagem");
		}
	}

	switch(numero)
	{
		case 0:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP1);
			break;
		case 1:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP2);
			break;
		case 2:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP3);
			break;
		case 3:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP4);
			break;
		case 4:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP5);
			break;
		case 5:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP6);
			break;
		default:
			gtk_image_set_from_file(GTK_IMAGE(imagem_desktop),DESKTOP1);
	}
	return 0;
}
