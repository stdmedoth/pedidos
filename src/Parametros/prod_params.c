void criar_prod_params(FILE *xmlf){
	xmlDocPtr prod_xml = xmlNewDoc((const xmlChar *)"1.0");
	xmlNodePtr root = xmlNewNode(NULL,(const xmlChar *)"prod_params");
	xmlNodePtr prod_varios_grupos = xmlNewNode(NULL,(const xmlChar *)"prod_varios_grupos");

	xmlNodeAddContent(prod_varios_grupos,(const xmlChar *)"0");

	xmlAddChild(root,prod_varios_grupos);

	xmlDocSetRootElement(prod_xml,root);

	xmlDocDump(xmlf,prod_xml);

	fclose(xmlf);
	return ;
}

int atualizar_prod_criticas(){
	char *query;
	int cont=0;
	int erro;

	xmlDocPtr prod_xml = xmlReadFile(PROD_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(prod_xml){
		xmlNodePtr root = xmlDocGetRootElement(prod_xml);

		produtos.parametros.prod_varios_grupos = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(prod_varios_grupos_wdt));

		xmlNodePtr prod_varios_grupos = getContentByTagName(root,"prod_varios_grupos");
		if(produtos.parametros.prod_varios_grupos)
			xmlNodeSetContent(prod_varios_grupos,(xmlChar *)"1");
		else
			xmlNodeSetContent(prod_varios_grupos,(xmlChar *)"0");
	}

	FILE *xmlf = fopen(PROD_PARAMS, "w");
	if(!xmlf){
		popup(NULL,"Não foi possível abrir arquivo de parametros");
		return 1;
	}
	xmlDocDump(xmlf,prod_xml);

	if(configurar_parametros()==0)
		return 0;
	else
		return 1;
	return 0 ;
}


int receber_prod_params(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);

	xmlDocPtr prod_xml = xmlReadFile(PROD_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(prod_xml){
		xmlNodePtr root = xmlDocGetRootElement(prod_xml);

		xmlNodePtr orc_prod_mov = getContentByTagName(root,"prod_varios_grupos");
		if(orc_prod_mov){
			produtos.parametros.prod_varios_grupos = atoi((const char *)orc_prod_mov->content);
		}
	}else{
		FILE *xmlf = fopen(PROD_PARAMS, "r+");
		if(!xmlf){
			xmlf = fopen(PROD_PARAMS, "w");
			if(!xmlf){
				popup(NULL,"Não foi possível abrir arquivo de parametros");
				return 1;
			}
		}
		criar_prod_params(xmlf);
	}
	return 0;
}


int ler_prod_params(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);

	xmlDocPtr prod_xml = xmlReadFile(PROD_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(prod_xml){
		xmlNodePtr root = xmlDocGetRootElement(prod_xml);

		xmlNodePtr orc_prod_mov = getContentByTagName(root,"prod_varios_grupos");
		if(orc_prod_mov){
			produtos.parametros.prod_varios_grupos = atoi((const char *)orc_prod_mov->content);
			if(produtos.parametros.prod_varios_grupos)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(prod_varios_grupos_wdt),TRUE);
			else
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(prod_varios_grupos_wdt),FALSE);
		}
	}else{
		FILE *xmlf = fopen(PROD_PARAMS, "r+");
		if(!xmlf){
			xmlf = fopen(PROD_PARAMS, "w");
			if(!xmlf){
				popup(NULL,"Não foi possível abrir arquivo de parametros");
				return 1;
			}
		}
		criar_prod_params(xmlf);
	}

	return 0;
}
