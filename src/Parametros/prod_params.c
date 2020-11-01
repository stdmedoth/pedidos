void criar_prod_params(FILE *xmlf){
	xmlDocPtr prod_xml = xmlNewDoc((const xmlChar *)"1.0");
	xmlNodePtr root = xmlNewNode(NULL, (const xmlChar *)"prod_params");

	xmlDocSetRootElement(prod_xml,root);

	xmlDocDump(xmlf,prod_xml);

	fclose(xmlf);
	return ;
}

int atualizar_prod_params(){
	char *query;
	int cont=0;
	int erro;

	xmlDocPtr prod_xml = xmlReadFile(PROD_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(prod_xml){
		xmlNodePtr root = xmlDocGetRootElement(prod_xml);
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

	xmlDocPtr prod_xml = xmlReadFile(PROD_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(prod_xml){
		xmlNodePtr root = xmlDocGetRootElement(prod_xml);


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

	xmlDocPtr prod_xml = xmlReadFile(PROD_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(prod_xml){
		xmlNodePtr root = xmlDocGetRootElement(prod_xml);


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
