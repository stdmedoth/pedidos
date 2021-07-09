void choose_version_change_previous(GtkWidget *button, GtkWidget *about_dialog){

  if(update_choosed_version > 0){
    update_choosed_version--;
  }
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), versions[update_choosed_version].name);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), versions[update_choosed_version].about);  
}

void choose_version_change_next(GtkWidget *button, GtkWidget *about_dialog){

  if(update_choosed_version < choose_versions_qnt-1){
    update_choosed_version++;
  }
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), versions[update_choosed_version].name);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), versions[update_choosed_version].about);
}
const char *choose_version_for_download(){

  GtkWidget *janela = gtk_about_dialog_new ();
  gtk_window_set_position(GTK_WINDOW(janela), 3);
  
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(janela), "Calisto Pedidos");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(janela), versions[update_choosed_version].name);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(janela), versions[update_choosed_version].about);
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(janela), gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(LOGO_PEQUENA))));
  char *autores[] = {"João Calisto", NULL};
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(janela), (const char**)autores);
  
  enum{
    ESCOLHER_VERSAO,
    CANCELAR_DOWNLOAD,
  };

  GList *childrens = gtk_container_get_children(GTK_CONTAINER(janela)); 
  GtkWidget *about_container = childrens->data;
  if(about_container){
    GtkWidget *versoes_button_box = gtk_box_new(0,0);
    GtkWidget *versao_anterior = gtk_button_new_with_label("Anterior");
    GtkWidget *versao_posterior = gtk_button_new_with_label("Próxima");
    gtk_box_pack_start(GTK_BOX(versoes_button_box), versao_anterior,0,0,5);
    gtk_box_pack_start(GTK_BOX(versoes_button_box), versao_posterior,0,0,5);
    gtk_box_pack_start(GTK_BOX(about_container), versoes_button_box,0,0,5);
    g_signal_connect(versao_anterior, "clicked", G_CALLBACK(choose_version_change_previous), janela);
    g_signal_connect(versao_posterior, "clicked", G_CALLBACK(choose_version_change_next), janela);
  }

  GtkWidget *escolher_versao = gtk_button_new_with_label("Iniciar download da Versão");
  GtkWidget *cancelar_download = gtk_button_new_with_label("Cancelar");
  
  gtk_dialog_add_action_widget(GTK_DIALOG(janela), escolher_versao, ESCOLHER_VERSAO);
  gtk_dialog_add_action_widget(GTK_DIALOG(janela), cancelar_download, CANCELAR_DOWNLOAD);

  gtk_widget_show_all(janela);
  int response = gtk_dialog_run(GTK_DIALOG(janela));
  const char *version = NULL;
  switch(response){
    case ESCOLHER_VERSAO:

      
      version = strdup(gtk_about_dialog_get_version(GTK_ABOUT_DIALOG(janela)));
      gtk_widget_destroy(janela);
      return version;

    case CANCELAR_DOWNLOAD:
      
      break;
      
    default: 

      break;
  }
  gtk_widget_destroy(janela);

  return NULL; // apenas para simulação! corrigir isso depois
}

struct _versions *search_all_versions(){

  char url[strlen(VERSIONS_INFO_URL)];
  sprintf(url, "%s", VERSIONS_INFO_URL);
  char *tmp_fileresponse = get_response(url);
  if(!tmp_fileresponse){
    popup(NULL,"Não foi possível receber informações com as versões");
    return NULL;
  }
  xmlDocPtr doc = xmlParseFile(tmp_fileresponse);
  if(!doc){
    popup(NULL,"Não foi possível receber informações com as versões");
    return NULL; 
  }

  xmlNodeSet *name_versoes = get_tags_by_namepath(doc,"/version_list/version/name");
  if(!name_versoes){
    popup(NULL,"Não foi possível receber nome das versões");
    return NULL;
  }
  xmlNodeSet *about_versoes = get_tags_by_namepath(doc,"/version_list/version/about");
  if(!about_versoes){
    popup(NULL,"Não foi possível receber nome das versões");
    return NULL;
  }

  if(versions){
    free(versions);  
  }
  versions = malloc(sizeof(struct _versions) * MAX_VERSION_QNT);
  update_choosed_version = 0;
  choose_versions_qnt = 0;

  for(int cont=0; cont < name_versoes->nodeNr && cont < MAX_VERSION_QNT; cont++){

    if(name_versoes->nodeTab[cont])
      versions[cont].name = strdup((char*)xmlNodeGetContent(name_versoes->nodeTab[cont]));
    if(about_versoes->nodeTab[cont])
      versions[cont].about = strdup((char*)xmlNodeGetContent(about_versoes->nodeTab[cont]));
    choose_versions_qnt++;
  }

  return versions;
}

char *search_last_version(){

  CURL *curl;
  FILE *fp;
  CURLcode res;
  char url[] = LAST_VERSION_INFO_URL;
  char errorbuf[ CURL_ERROR_SIZE ] = "";
  char *last_version;

  struct upload_status upload_ctx;
  upload_ctx.lines_read = 0;
  struct MemoryStruct body_chunk;
  body_chunk.memory = malloc(1);
  body_chunk.size = 0;

  carregar_interface();

  curl = curl_easy_init();
  if (!curl) {
    popup(NULL,"Não foi possível inicializar curl na busca de versão atualizada");
    return NULL;
  }
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuf);
  //curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_NONE);
  curl_easy_setopt(curl, CURLOPT_CAINFO, MOZ_CERT);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body_chunk);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
  carregar_interface();
  res = curl_easy_perform(curl);
  if(res  != CURLE_OK){
    file_logger("Erro na atualização:");
    file_logger(errorbuf);
    curl_easy_cleanup(curl);
    popup(NULL,"Não foi possível buscar ultima versão");
    return NULL;
  }
  
  if(body_chunk.memory){
    last_version = strdup(body_chunk.memory);  
  }
  curl_easy_cleanup(curl);

  return last_version;
}

int download_new_version(void) {

  if(!PopupBinario("O sistema pesquisará por uma versão e iniciará a atualização", "Sim! continuar.", "Mais tarde")){
    return 1;
  }

  CURL *curl;
  FILE *fp;
  CURLcode res;
  char *url = malloc(1000);
  char errorbuf[ CURL_ERROR_SIZE ] = "";
  const char *next_name_version=NULL;
  global_progress_bar_active = 1;


    #ifdef WIN32
  int bins_qnt = 3;
  char *bins[] = {
    "PedidosComConsole.exe", 
    "PedidosSemConsole.exe", 
    "migrate.exe", 
    NULL
  };
  char *outfilenames[] = {
    "PedidosComConsoleNew.exe", 
    "PedidosSemConsoleNew.exe", 
    "migrate.exe", 
    NULL};
    #endif

    #ifdef __linux__
    int bins_qnt = 1;
    char *bins[] = {
      "Pedidos.o", 
      "migrate.exe", 
      NULL
    };
    char *outfilenames[] = {
      "PedidosNew.o", 
      "migrate.exe", 
      NULL
    };
    #endif

    if(search_all_versions()){
      next_name_version = choose_version_for_download();
      if(!next_name_version){
        return 1;
      }
    }

    if(!next_name_version){
      next_name_version = get_text_from_input("Insira o nome da versão a ser baixada:", NULL);
      if(!next_name_version){
        global_progress_bar_active = 0;
        popup(NULL,"Nome da versão não inserida");
        return 1;
      }  
    } 
    carregar_interface();

    for(int pos=0; bins[pos] != NULL ;pos++){
      carregar_interface();
      sprintf(url, "https://github.com/stdmedoth/pedidos/releases/download/%s/%s", next_name_version, bins[pos]);
      curl = curl_easy_init();
      if (curl) {
        char path[MAX_PATH_LEN];
        sprintf(path,"%s/%s", APP_BINS_DIR, outfilenames[pos]);
        fp = fopen(path,"wb");
        if(!fp){
          global_progress_bar_active = 0;
          popup(NULL,"Não foi possível armazenar versão atual");
          return 1;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuf);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        carregar_interface();
        res = curl_easy_perform(curl);
        if(res == CURLE_HTTP_RETURNED_ERROR){
          file_logger("Erro na atualização:");
          file_logger(url);
          file_logger(errorbuf);
          global_progress_bar_active = 0;
          curl_easy_cleanup(curl);
          fclose(fp);
          char msg[CURL_ERROR_SIZE + 100];
          sprintf(msg, "Não foi possível baixar versão especificada:\n%s", errorbuf);
          popup(NULL, msg);
          return 1;
        }
          /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
      }
    }
    
    for(int cont=0; files_remove_on_update[cont]; cont++){
      remove(files_remove_on_update[cont]);  
    }

    FILE *tmp_updt_fp = fopen(ATUALIZA_VERTMP,"wb");
    if(!tmp_updt_fp){
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível criar arquivo update warn");
      return 1;
    }
    fprintf(tmp_updt_fp,"1");
    fclose(tmp_updt_fp);


    char msg[2000];
    sprintf(msg,"A versão %s foi transferida com sucesso!\nDeseja fechar o sistema para efetuar a atualização?", next_name_version);
    global_progress_bar_active = 0;
    if(PopupBinario(msg, "Fechar sistema e atualizar", "Deixar para depois")){
      encerrar(NULL, GTK_WINDOW(janelas_gerenciadas.principal.janela_pointer));
    }
    return 0;
  }
