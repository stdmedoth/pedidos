JsonArray *get_json_array_response(char *url){

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char errorbuf[ CURL_ERROR_SIZE ] = "";

    global_progress_bar_active = 1;
    carregar_interface();

    curl = curl_easy_init();
    if (!curl) {
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível inicializar transferencia");
      return NULL;
    }
    char *filepath = malloc(MAX_PATH_LEN);
    sprintf(filepath,"%s%s", TMPDIR_PATH, randomizar_string());
    fp = fopen(filepath,"wb");
    if(!fp){
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível salvar arquivo");
      return NULL;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuf);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_file);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(curl, CURLOPT_ENCODING, "");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
    
    carregar_interface();
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      file_logger("Erro na transferencia:");
      file_logger(errorbuf);
      global_progress_bar_active = 0;
      curl_easy_cleanup(curl);
      fclose(fp);
      
      char msg[CURL_ERROR_SIZE + 100];
      sprintf(msg, "Não foi possível buscar url especificada:\n%s", errorbuf);
      file_logger(url);
      popup(NULL, msg);
      return NULL;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);


    JsonParser *parser = json_parser_new();
    GError *error = NULL;

    if(!json_parser_load_from_file(parser, filepath, &error)){
      return NULL;
    }

    JsonNode *root = json_parser_get_root (parser);
    if(!root){
      file_logger(filepath);
      file_logger("Não foi possível buscar root na consulta json");
      return NULL;
    }
    JsonArray *array = json_node_get_array(root);
    if(!array){
      file_logger(filepath);
      file_logger("Não foi possível buscar object na consulta json");
      return NULL;
    }
    global_progress_bar_active = 0;

    return array;
}

JsonObject *get_json_object_response(char *url){

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char errorbuf[ CURL_ERROR_SIZE ] = "";

    global_progress_bar_active = 1;
    carregar_interface();

    curl = curl_easy_init();
    if (!curl) {
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível inicializar transferencia");
      return NULL;
    }
    char *filepath = malloc(MAX_PATH_LEN);
    sprintf(filepath,"%s%s", TMPDIR_PATH, randomizar_string());
    fp = fopen(filepath,"wb");
    if(!fp){
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível salvar arquivo");
      return NULL;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuf);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_file);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(curl, CURLOPT_ENCODING, "");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
    
    carregar_interface();
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      file_logger("Erro na transferencia:");
      file_logger(errorbuf);
      global_progress_bar_active = 0;
      curl_easy_cleanup(curl);
      fclose(fp);
      
      char msg[CURL_ERROR_SIZE + 100];
      sprintf(msg, "Não foi possível buscar url especificada:\n%s", errorbuf);
      file_logger(url);
      popup(NULL, msg);
      return NULL;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);


    JsonParser *parser = json_parser_new();
    GError *error = NULL;

    if(!json_parser_load_from_file(parser, filepath, &error)){
      return NULL;
    }

    JsonNode *root = json_parser_get_root (parser);
    if(!root){
      file_logger(filepath);
      file_logger("Não foi possível buscar root na consulta json");
      return NULL;
    }
    JsonObject *obj = json_node_get_object(root);
    if(!obj){
      file_logger(filepath);
      file_logger("Não foi possível buscar object na consulta json");
      return NULL;
    }
    global_progress_bar_active = 0;

    return obj;
}

char *get_response(char *url){

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char errorbuf[ CURL_ERROR_SIZE ] = "";

    global_progress_bar_active = 1;
    carregar_interface();

    curl = curl_easy_init();
    if (!curl) {
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível inicializar transferencia");
      return NULL;
    }
    char *filepath = malloc(MAX_PATH_LEN);
    sprintf(filepath,"%s/%s", TMPDIR_PATH, randomizar_string());
    fp = fopen(filepath,"wb");
    if(!fp){
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível salvar arquivo");
      return NULL;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuf);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_file);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    carregar_interface();
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      file_logger("Erro na transferencia:");
      file_logger(errorbuf);
      global_progress_bar_active = 0;
      curl_easy_cleanup(curl);
      fclose(fp);
      
      char msg[CURL_ERROR_SIZE + 100];
      sprintf(msg, "Não foi possível transferir arquivo especificado:\n%s", errorbuf);
      popup(NULL, msg);
      return NULL;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);

    global_progress_bar_active = 0;

    return filepath;
}

int download_from_to(char *url, char *filepath){

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char errorbuf[ CURL_ERROR_SIZE ] = "";

    global_progress_bar_active = 1;
    carregar_interface();

    curl = curl_easy_init();
    if (!curl) {
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível inicializar transferencia");
      return 1;
    }
    fp = fopen(filepath,"wb");
    if(!fp){
      global_progress_bar_active = 0;
      popup(NULL,"Não foi possível salvar arquivo");
      return 1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuf);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_file);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    carregar_interface();
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      file_logger("Erro na transferencia:");
      file_logger(errorbuf);
      global_progress_bar_active = 0;
      curl_easy_cleanup(curl);
      fclose(fp);
      
      char msg[CURL_ERROR_SIZE + 100];
      sprintf(msg, "Não foi possível transferir arquivo especificado:\n%s", errorbuf);
      popup(NULL, msg);
      return 1;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);

    global_progress_bar_active = 0;

    return 0;
}
