void criar_orc_params(FILE *xmlf){
	xmlDocPtr orc_xml = xmlNewDoc((const xmlChar *)"1.0");
	xmlNodePtr root = xmlNewNode(NULL,(const xmlChar *)"orc_param");
	xmlNodePtr orc_prod_mov = xmlNewNode(NULL,(const xmlChar *)"orc_prod_mov");
	xmlNodePtr orc_prod_saldo = xmlNewNode(NULL,(const xmlChar *)"orc_prod_saldo");
	xmlNodePtr orc_prod_sld_lmt = xmlNewNode(NULL,(const xmlChar *)"orc_prod_sld_lmt");
	xmlNodePtr orc_ped_canc = xmlNewNode(NULL,(const xmlChar *)"orc_ped_canc");

	xmlNodeAddContent(orc_prod_mov,(const xmlChar *)"1");
	xmlNodeAddContent(orc_prod_saldo,(const xmlChar *)"1");
	xmlNodeAddContent(orc_prod_sld_lmt,(const xmlChar *)"1");
	xmlNodeAddContent(orc_ped_canc,(const xmlChar *)"1");

	xmlAddChild(root,orc_prod_mov);
	xmlAddChild(root,orc_prod_saldo);
	xmlAddChild(root,orc_prod_sld_lmt);
	xmlAddChild(root,orc_ped_canc);

	xmlDocSetRootElement(orc_xml,root);

	xmlDocDump(xmlf,orc_xml);
	fclose(xmlf);
	return ;
}

int atualizar_orc_criticas(){
	char *query;
	int cont=0;
	int erro;

	xmlDocPtr orc_xml = xmlReadFile(ORC_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(orc_xml){
		xmlNodePtr root = xmlDocGetRootElement(orc_xml);

		orcamentos.criticar.prod_movimento = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orc_prod_mov_wdt));
		orcamentos.criticar.prod_saldo = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orc_prod_sld_wdt));
		orcamentos.criticar.prod_saldo_limite = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orc_prod_sld_lmt_wdt));
		orcamentos.criticar.orc_ped_cancelado = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orc_ped_canc_wdt));

		xmlNodePtr orc_prod_mov = getContentByTagName(root,"orc_prod_mov");
		if(orcamentos.criticar.prod_movimento)
			xmlNodeSetContent(orc_prod_mov,(xmlChar *)"1");
		else
			xmlNodeSetContent(orc_prod_mov,(xmlChar *)"0");

		xmlNodePtr orc_prod_saldo = getContentByTagName(root,"orc_prod_saldo");
		if(orcamentos.criticar.prod_saldo)
			xmlNodeSetContent(orc_prod_saldo,(xmlChar *)"1");
		else
			xmlNodeSetContent(orc_prod_saldo,(xmlChar *)"0");

		xmlNodePtr orc_prod_sld_lmt = getContentByTagName(root,"orc_prod_sld_lmt");
		if(orcamentos.criticar.prod_saldo_limite)
			xmlNodeSetContent(orc_prod_sld_lmt,(xmlChar *)"1");
		else
			xmlNodeSetContent(orc_prod_sld_lmt,(xmlChar *)"0");

		xmlNodePtr orc_ped_canc = getContentByTagName(root,"orc_ped_canc");
		if(orcamentos.criticar.orc_ped_cancelado)
			xmlNodeSetContent(orc_ped_canc,(xmlChar *)"1");
		else
			xmlNodeSetContent(orc_ped_canc,(xmlChar *)"0");
	}

	FILE *xmlf = fopen(ORC_PARAMS, "w");
	if(!xmlf){
		popup(NULL,"Não foi possível abrir arquivo de parametros");
		return 1;
	}
	xmlDocDump(xmlf,orc_xml);

	if(configurar_parametros()==0)
		return 0;
	else
		return 1;
	return 0 ;
}

int receber_orc_params(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);

	xmlDocPtr orc_xml = xmlReadFile(ORC_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(orc_xml){
		xmlNodePtr root = xmlDocGetRootElement(orc_xml);

		xmlNodePtr orc_prod_mov = getContentByTagName(root,"orc_prod_mov");
		if(orc_prod_mov){
			orcamentos.criticar.prod_movimento = atoi((const char *)orc_prod_mov->content);
		}

		xmlNodePtr orc_prod_saldo = getContentByTagName(root,"orc_prod_saldo");
		if(orc_prod_saldo){
			orcamentos.criticar.prod_saldo = atoi((const char *)orc_prod_saldo->content);
		}

		xmlNodePtr orc_prod_sld_lmt = getContentByTagName(root,"orc_prod_sld_lmt");
		if(orc_prod_sld_lmt){
			orcamentos.criticar.prod_saldo_limite = atoi((const char *)orc_prod_sld_lmt->content);
		}

		xmlNodePtr orc_ped_canc = getContentByTagName(root,"orc_ped_canc");
		if(orc_ped_canc){
			orcamentos.criticar.orc_ped_cancelado = atoi((const char *)orc_ped_canc->content);
		}
	}else{
		FILE *xmlf = fopen(ORC_PARAMS, "r+");
		if(!xmlf){
			xmlf = fopen(ORC_PARAMS, "w");
			if(!xmlf){
				popup(NULL,"Não foi possível abrir arquivo de parametros");
				return 1;
			}
		}
		criar_orc_params(xmlf);

	}
	return 0;
}


int ler_orc_params(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);

	xmlDocPtr orc_xml = xmlReadFile(ORC_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(orc_xml){
		xmlNodePtr root = xmlDocGetRootElement(orc_xml);

		xmlNodePtr orc_prod_mov = getContentByTagName(root,"orc_prod_mov");
		if(orc_prod_mov){
			orcamentos.criticar.prod_movimento = atoi((const char *)orc_prod_mov->content);
			if(orcamentos.criticar.prod_movimento)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_prod_mov_wdt),TRUE);
			else
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_prod_mov_wdt),FALSE);
		}

		xmlNodePtr orc_prod_saldo = getContentByTagName(root,"orc_prod_saldo");
		if(orc_prod_saldo){
			orcamentos.criticar.prod_saldo = atoi((const char *)orc_prod_saldo->content);
			if(orcamentos.criticar.prod_saldo)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_prod_sld_wdt),TRUE);
			else
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_prod_sld_wdt),FALSE);

		}

		xmlNodePtr orc_prod_sld_lmt = getContentByTagName(root,"orc_prod_sld_lmt");
		if(orc_prod_sld_lmt){
			orcamentos.criticar.prod_saldo_limite = atoi((const char *)orc_prod_sld_lmt->content);
			if(orcamentos.criticar.prod_saldo_limite)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_prod_sld_lmt_wdt),TRUE);
			else
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_prod_sld_lmt_wdt),FALSE);
		}

		xmlNodePtr orc_ped_canc = getContentByTagName(root,"orc_ped_canc");
		if(orc_ped_canc){
			orcamentos.criticar.orc_ped_cancelado = atoi((const char *)orc_ped_canc->content);
			if(orcamentos.criticar.orc_ped_cancelado)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_ped_canc_wdt),TRUE);
			else
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_ped_canc_wdt),FALSE);
		}
	}else{
		FILE *xmlf = fopen(ORC_PARAMS, "r+");
		if(!xmlf){
			xmlf = fopen(ORC_PARAMS, "w");
			if(!xmlf){
				popup(NULL,"Não foi possível abrir arquivo de parametros");
				return 1;
			}
		}
		criar_orc_params(xmlf);

	}

	return 0;
}
