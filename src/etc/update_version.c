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
  char *next_name_version;

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

    global_progress_bar_active = 1;
    next_name_version = search_last_version();
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
