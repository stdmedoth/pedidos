void intgr_params_testar(){

	if(!mysql_init(&intgr_con))
	{
		popup(NULL,"Não foi possivel iniciar conector");
		autologger((char*)mysql_error(&conectar));
		return ;
	}

	if(!mysql_real_connect(&intgr_con,integracoes.config.server, integracoes.config.user,integracoes.config.pass,integracoes.config.banco,0,NULL,0))
	{
		popup(NULL,"Não foi possível conectar");
		return ;
	}
	popup(NULL,"Conexão efetuada");

}

void criar_intgr_params(FILE *xmlf){
	xmlDocPtr intgr_xml = xmlNewDoc((const xmlChar *)"1.0");
	xmlNodePtr root = xmlNewNode(NULL, (const xmlChar *)"intgr_params");
	xmlNodePtr intgr_id = xmlNewNode(NULL, (const xmlChar *)"intgr_id");
	xmlNodePtr user = xmlNewNode(NULL, (const xmlChar *)"usuario");
	xmlNodePtr pass = xmlNewNode(NULL, (const xmlChar *)"senha");
	xmlNodePtr database = xmlNewNode(NULL, (const xmlChar *)"banco");
	xmlNodePtr server = xmlNewNode(NULL, (const xmlChar *)"servidor");
	xmlNodePtr prefix_tabs = xmlNewNode(NULL, (const xmlChar *)"prefix_tabs");


	xmlNodeAddContent(intgr_id,(const xmlChar *)"0");
	xmlNodeAddContent(server,(const xmlChar *)"server");
	xmlNodeAddContent(user,(const xmlChar *)"usuario");
	xmlNodeAddContent(pass,(const xmlChar *)"senha");
	xmlNodeAddContent(database,(const xmlChar *)"banco");
	xmlNodeAddContent(prefix_tabs,(const xmlChar *)"wp_");

	xmlAddChild(root,intgr_id);
	xmlAddChild(root,user);
	xmlAddChild(root,pass);
	xmlAddChild(root,database);
	xmlAddChild(root,server);
	xmlAddChild(root,prefix_tabs);

	xmlDocSetRootElement(intgr_xml,root);

	xmlDocDump(xmlf,intgr_xml);

	fclose(xmlf);
	return ;
}

int atualizar_intgr_params(){

	xmlDocPtr intgr_xml = xmlReadFile(INTEGR_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(intgr_xml){
		xmlNodePtr root = xmlDocGetRootElement(intgr_xml);
		integracoes.config.intgr_id = gtk_combo_box_get_active(GTK_COMBO_BOX(integr_opc_wdt));
		integracoes.config.user =  (char*)gtk_entry_get_text(GTK_ENTRY(integr_usuario_wdt));
		integracoes.config.pass =  (char*)gtk_entry_get_text(GTK_ENTRY(integr_senha_wdt));
		integracoes.config.banco =  (char*)gtk_entry_get_text(GTK_ENTRY(integr_bd_wdt));
		integracoes.config.server = (char*)gtk_entry_get_text(GTK_ENTRY(integr_server_wdt));
		integracoes.config.prefix_tab =  (char*)gtk_entry_get_text(GTK_ENTRY(integr_tabprefix_wdt));

		xmlNodePtr intgr_id = getContentByTagName(root, "intgr_id");
		if(intgr_id){
			char intgr_id_char[12];
			sprintf(intgr_id_char,"%i", integracoes.config.intgr_id);
			xmlNodeSetContent(intgr_id, (xmlChar *)intgr_id_char);
		}

		xmlNodePtr user = getContentByTagName(root,"usuario");
		if(user){
			if(strlen(integracoes.config.user)){
				xmlNodeSetContent(user, (xmlChar *)integracoes.config.user);
			}else{
				xmlNodeSetContent(user,(xmlChar *)"usuario");
			}
		}

		xmlNodePtr pass = getContentByTagName(root,"senha");
		if(pass){
			if(strlen(integracoes.config.pass)){
				xmlNodeSetContent(pass, (xmlChar *)integracoes.config.pass);
			}else{
				xmlNodeSetContent(pass,(xmlChar *)"senha");
			}
		}

		xmlNodePtr database = getContentByTagName(root,"banco");
		if(database){
			if(strlen(integracoes.config.banco)){
				xmlNodeSetContent(database, (xmlChar *)integracoes.config.banco);
			}else{
				xmlNodeSetContent(database,(xmlChar *)"Banco de Dados");
			}
		}

		xmlNodePtr server = getContentByTagName(root,"servidor");
		if(server){
			if(strlen(integracoes.config.server)){
				xmlNodeSetContent(server, (xmlChar *)integracoes.config.server);
			}else{
				xmlNodeSetContent(server,(xmlChar *)"");
			}
		}

		xmlNodePtr prefix_tab = getContentByTagName(root,"prefix_tabs");
		if(prefix_tab){
			if(strlen(integracoes.config.prefix_tab)){
				xmlNodeSetContent(prefix_tab, (xmlChar *)integracoes.config.prefix_tab);
			}else{
				xmlNodeSetContent(prefix_tab,(xmlChar *)"wp_");
			}
		}

	}

	FILE *xmlf = fopen(INTEGR_PARAMS, "w");
	if(!xmlf){
		popup(NULL,"Não foi possível abrir arquivo de config");
		return 1;
	}
	xmlDocDump(xmlf,intgr_xml);

	if(configurar_parametros())
		return 1;

	return 0 ;
}


int receber_intgr_params(){

	xmlDocPtr intgr_xml = xmlReadFile(INTEGR_PARAMS, "UTF-8", XML_PARSE_RECOVER );

	if(intgr_xml){
		xmlNodePtr root = xmlDocGetRootElement(intgr_xml);

		xmlNodePtr intgr_id = getContentByTagName(root,"intgr_id");
		if(intgr_id){
			integracoes.config.intgr_id = atoi((const char *)intgr_id->content);
		}

		xmlNodePtr user = getContentByTagName(root,"usuario");
		if(user && user->content){
			integracoes.config.user = strdup((const char *)user->content);
		}

		xmlNodePtr senha = getContentByTagName(root,"senha");
		if(senha && senha->content){
			integracoes.config.pass = strdup((const char *)senha->content);
		}

		xmlNodePtr banco = getContentByTagName(root,"banco");
		if(banco && banco->content){
			integracoes.config.banco = strdup((const char *)banco->content);
		}

		xmlNodePtr server = getContentByTagName(root,"servidor");
		if(server && server->content){
			integracoes.config.server = strdup((const char *)server->content);
		}

		xmlNodePtr prefix_tab = getContentByTagName(root,"prefix_tabs");
		if(prefix_tab && prefix_tab->content){
			integracoes.config.prefix_tab = strdup((const char *)prefix_tab->content);
		}


	}else{
		FILE *xmlf = fopen(INTEGR_PARAMS, "r+");
		if(!xmlf){
			xmlf = fopen(INTEGR_PARAMS, "w");
			if(!xmlf){
				popup(NULL,"Não foi possível abrir arquivo de config");
				return 1;
			}
		}
		criar_intgr_params(xmlf);
	}
	return 0;
}


int ler_intgr_params(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int cont=0;
	query = malloc(sizeof(char*)*MAX_QUERY_LEN);

	xmlDocPtr intgr_xml = xmlReadFile(INTEGR_PARAMS, "UTF-8", XML_PARSE_RECOVER );
	if(intgr_xml){
		xmlNodePtr root = xmlDocGetRootElement(intgr_xml);

		xmlNodePtr intgr_id = getContentByTagName(root,"intgr_id");
		if(intgr_id){
			integracoes.config.intgr_id = atoi((const char *)intgr_id->content);
			if(integracoes.config.intgr_id)
				gtk_combo_box_set_active(GTK_COMBO_BOX(integr_opc_wdt),integracoes.config.intgr_id);
			else
				gtk_combo_box_set_active(GTK_COMBO_BOX(integr_opc_wdt),integracoes.config.intgr_id);
		}

		xmlNodePtr user = getContentByTagName(root,"usuario");
		if(user && user->content){
			integracoes.config.user = strdup((const char *)user->content);
			if(integracoes.config.user)
				gtk_entry_set_text(GTK_ENTRY(integr_usuario_wdt),integracoes.config.user);
			else
				gtk_entry_set_text(GTK_ENTRY(integr_usuario_wdt),"usuario");

		}

		xmlNodePtr senha = getContentByTagName(root,"senha");
		if(senha && senha->content){
			integracoes.config.pass = strdup((const char *)senha->content);
			if(integracoes.config.pass)
				gtk_entry_set_text(GTK_ENTRY(integr_senha_wdt),integracoes.config.pass);
			else
				gtk_entry_set_text(GTK_ENTRY(integr_senha_wdt),"senha");

		}

		xmlNodePtr banco = getContentByTagName(root,"banco");
		if(banco && banco->content){
			integracoes.config.banco = strdup((const char *)banco->content);
			if(integracoes.config.banco)
				gtk_entry_set_text(GTK_ENTRY(integr_bd_wdt),integracoes.config.banco);
			else
				gtk_entry_set_text(GTK_ENTRY(integr_bd_wdt),"banco");

		}

		xmlNodePtr server = getContentByTagName(root,"servidor");
		if(server && server->content){
			integracoes.config.server = strdup((const char *)server->content);
			if(integracoes.config.server)
				gtk_entry_set_text(GTK_ENTRY(integr_server_wdt),integracoes.config.server);
			else
				gtk_entry_set_text(GTK_ENTRY(integr_server_wdt),"servidor");
		}

		xmlNodePtr prefix_tab = getContentByTagName(root,"prefix_tabs");
		if(prefix_tab && prefix_tab->content){
			integracoes.config.prefix_tab = strdup((const char *)prefix_tab->content);
			if(strlen(integracoes.config.prefix_tab))
				gtk_entry_set_text(GTK_ENTRY(integr_tabprefix_wdt),integracoes.config.prefix_tab);
			else
				gtk_entry_set_text(GTK_ENTRY(integr_tabprefix_wdt),"wp_");
		}

	}else{
		FILE *xmlf = fopen(INTEGR_PARAMS, "r+");
		if(!xmlf){
			xmlf = fopen(INTEGR_PARAMS, "w");
			if(!xmlf){
				popup(NULL,"Não foi possível abrir arquivo de config");
				return 1;
			}
		}
		criar_intgr_params(xmlf);
	}

	return 0;
}
