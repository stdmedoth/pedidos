int download_new_version(void) {

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = malloc(1000);
    char *bins[] = {"PedidosComConsole.exe", "PedidosSemConsole.exe"};
    char *outfilenames[] = {"PedidosComConsoleNew.exe", "PedidosSemConsoleNew.exe"};
    //char *next_name_version = "v1.1.1.1_Win32-x";

    char *next_name_version = get_text_from_input("Insira o nome da versão a ser baixada:", NULL);
    if(!next_name_version){
      popup(NULL,"Nome da versão não inserida");
      return 1;
    }

    gpointer loading = carregando_wnd();
    carregar_interface();

    for(int pos=0;pos<2;pos++){
      carregar_interface();
      sprintf(url, "https://github.com/stdmedoth/pedidos/releases/download/%s/%s", next_name_version, bins[pos]);
      curl = curl_easy_init();
      if (curl) {
          char path[MAX_PATH_LEN];
          sprintf(path,"%s/%s", APP_BINS_DIR, outfilenames[pos]);
          fp = fopen(path,"wb");
          if(!fp){
            gtk_widget_destroy(loading);
            popup(NULL,"Não foi possível armazenar versão atual");
            return 1;
          }
          curl_easy_setopt(curl, CURLOPT_URL, url);
          curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_file);
  				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
          curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
          curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
          carregar_interface();
          res = curl_easy_perform(curl);
          if(res == CURLE_HTTP_RETURNED_ERROR) {
            gtk_widget_destroy(loading);
            curl_easy_cleanup(curl);
            fclose(fp);
            popup(NULL,"Não foi possível baixar versão especificada");
            return 1;
          }
          /* always cleanup */
          curl_easy_cleanup(curl);
          fclose(fp);
      }
    }
    gtk_widget_destroy(loading);

    char msg[2000];
    sprintf(msg,"A versão %s foi transferida com sucesso!\nDeseja fechar o sistema para efetuar a atualização?", next_name_version);
    if(PopupBinario(msg, "Fechar sistema e atualizar", "Deixar para depois")){
      encerrar(NULL, GTK_WINDOW(janelas_gerenciadas.principal.janela_pointer));
    }
    return 0;
}
