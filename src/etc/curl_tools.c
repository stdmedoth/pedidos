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
