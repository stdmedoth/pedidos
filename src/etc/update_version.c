void update_version_view(GtkWidget *about_dialog){
  if(!versions){
    return ;
  }

  char version_name[ strlen(versions[update_choosed_version].name) + strlen(versions[update_choosed_version].created_time) + 60];
  if(! strcmp(GET_APP_VERSION_NAME(), versions[update_choosed_version].name) ){
    sprintf(version_name, "%s,  criado em %s (Versão atual)", versions[update_choosed_version].name, versions[update_choosed_version].created_time);
  }else{
    sprintf(version_name, "%s,  criado em %s", versions[update_choosed_version].name,versions[update_choosed_version].created_time);
  }
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), version_name);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), versions[update_choosed_version].about);
}

void choose_version_change_previous(GtkWidget *button, GtkWidget *about_dialog){

  if(update_choosed_version > 0){
    update_choosed_version--;
  }
  update_version_view(about_dialog);

}

void choose_version_change_next(GtkWidget *button, GtkWidget *about_dialog){

  if(update_choosed_version < choose_versions_qnt-1){
    update_choosed_version++;
  }

  update_version_view(about_dialog);
}

void download_changelog_files_on_updateview(GtkWidget *button, gpointer janela){
  gtk_widget_hide(janela);
  download_changelog_files();
}

int choose_version_for_download(){

  GtkWidget *janela = gtk_about_dialog_new ();
  gtk_window_set_position(GTK_WINDOW(janela), 3);

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(janela), "Calisto Pedidos");
  update_version_view(janela);
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(janela), gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(LOGO_PEQUENA))));
  char *autores[] = {"João Calisto", NULL};
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(janela), (const char**)autores);

  enum{
    ESCOLHER_VERSAO,
    CANCELAR_DOWNLOAD,
  };

  GList *childrens = gtk_container_get_children(GTK_CONTAINER(janela));
  GtkWidget *about_container = childrens->data;
  GtkWidget *changelog_files_version_button = gtk_button_new_with_label("Transferir arquivos da versão");
  if(about_container){

    GtkWidget *migrateversion_button_frame = gtk_frame_new("Banco de Dados");
    GtkWidget *migrateversion_button_box = gtk_box_new(0,0);
    GtkWidget *migrateup_version_button = gtk_button_new_with_label("Up");
    GtkWidget *migratedown_version_button = gtk_button_new_with_label("Down");
    GtkWidget *version_assets_button = gtk_button_new_with_label("Anexos");
    


    gtk_widget_set_name(migrateup_version_button, "button_primary");
    gtk_widget_set_name(version_assets_button, "button_primary");
    gtk_widget_set_name(changelog_files_version_button, "button_primary");
    gtk_widget_set_name(migratedown_version_button, "button_danger");
    gtk_box_pack_start(GTK_BOX(migrateversion_button_box), migrateup_version_button, 0,0,5);
    gtk_box_pack_start(GTK_BOX(migrateversion_button_box), migratedown_version_button, 0,0,5);
    gtk_container_add(GTK_CONTAINER(migrateversion_button_frame), migrateversion_button_box);

    GtkWidget *versoes_button_box = gtk_box_new(0,0);
    GtkWidget *versao_anterior = gtk_button_new_with_label("Anterior");
    GtkWidget *versao_posterior = gtk_button_new_with_label("Próxima");
    gtk_box_pack_start(GTK_BOX(versoes_button_box), versao_anterior,0,0,5);
    gtk_box_pack_start(GTK_BOX(versoes_button_box), versao_posterior,0,0,5);
    gtk_box_pack_start(GTK_BOX(versoes_button_box), migrateversion_button_frame,0,0,5);
    gtk_box_pack_start(GTK_BOX(versoes_button_box), changelog_files_version_button,0,0,5);
    gtk_box_pack_start(GTK_BOX(versoes_button_box), version_assets_button,0,0,5);

    gtk_box_pack_start(GTK_BOX(about_container), versoes_button_box,0,0,5);

    g_signal_connect(versao_anterior, "clicked", G_CALLBACK(choose_version_change_previous), janela);
    g_signal_connect(versao_posterior, "clicked", G_CALLBACK(choose_version_change_next), janela);

    g_signal_connect(migrateup_version_button, "clicked", G_CALLBACK(update_migrates), NULL);
    g_signal_connect(migratedown_version_button, "clicked", G_CALLBACK(remove_migrates), NULL);
    g_signal_connect(changelog_files_version_button, "clicked", G_CALLBACK(download_changelog_files_on_updateview), janela);
    g_signal_connect(version_assets_button, "clicked", G_CALLBACK(show_version_assets), janela);

  }else{
    file_logger("Não foi possível receber container de gtk_container_get_children() na view de update");
  }

  GtkWidget *escolher_versao = gtk_button_new_with_label("Iniciar download da Versão");
  gtk_widget_set_name(escolher_versao, "button_secondary");
  GtkWidget *cancelar_download = gtk_button_new_with_label("Cancelar");

  gtk_dialog_add_action_widget(GTK_DIALOG(janela), escolher_versao, ESCOLHER_VERSAO);
  gtk_dialog_add_action_widget(GTK_DIALOG(janela), cancelar_download, CANCELAR_DOWNLOAD);

  gtk_widget_show_all(janela);

  int response = gtk_dialog_run(GTK_DIALOG(janela));
  const char *version = NULL;
  switch(response){
    case ESCOLHER_VERSAO:

    gtk_widget_destroy(janela);
    return update_choosed_version;

    case CANCELAR_DOWNLOAD:

    break;

    default:

    break;
  }
  gtk_widget_destroy(janela);

  return NO_VERSION_DEFINED; // apenas para simulação! corrigir isso depois
}

void iterate_version_assets_array (
  JsonArray *array, 
  guint index_,
  JsonNode *element_node, 
  gpointer user_data){


  if(index_ >= MAX_VERSION_ASSETS){
    return ;
  }

  JsonObject *obj = json_node_get_object(element_node);
  if(!obj){
    file_logger("Não foi possível receber objeto na iteração dos arquivos enexos (assets)");
    return ;
  }

  if(json_object_has_member(obj, "name")){
    versions[choose_versions_qnt].assets[index_] = strdup(json_object_get_string_member(obj, "name")); 
  }else{
    versions[choose_versions_qnt].assets[index_] = "";   
  }
  versions[choose_versions_qnt].assets_qnt++;
}

void iterate_version_array(JsonArray *array,
                     guint index_,
                     JsonNode *element_node,
                     gpointer user_data){

  if(index_ >= MAX_VERSION_QNT){
    return ;
  }

  JsonObject *obj = json_node_get_object(element_node);
  if(!obj){
    file_logger("Não foi possível receber objeto na iteração da versão");
    return ;
  }
  
  if(json_object_has_member(obj, "tag_name")){
    versions[index_].name = strdup(json_object_get_string_member(obj, "tag_name"));  
  }else{
    versions[index_].name = "";  
  }

  if(json_object_has_member(obj, "body")){
    versions[index_].about = strdup(json_object_get_string_member(obj, "body"));  
  }else{
    versions[index_].about = "";
  }

  if(json_object_has_member(obj, "created_at")){
    versions[index_].created_time = strdup(json_object_get_string_member(obj, "created_at"));  
  }else{
    versions[index_].created_time = "";
  }

  versions[index_].assets_qnt = 0;
  versions[index_].assets = malloc(sizeof(char *) * MAX_VERSION_ASSETS);
  if(json_object_has_member(obj, "assets")){
    JsonArray *assets = json_object_get_array_member(obj, "assets");
    json_array_foreach_element(assets, iterate_version_assets_array, NULL);
  }
  choose_versions_qnt++;
}

struct _versions *search_all_versions(){

  char url[strlen(VERSIONS_INFO_URL)];
  sprintf(url, "%s", VERSIONS_INFO_URL);
  JsonArray *json_array = get_json_array_response(url);
  if(!json_array){
    popup(NULL,"Não foi possível receber informações com as versões");
    return NULL;
  }
  if(versions){
    free(versions);
  }
  versions = malloc(sizeof(struct _versions) * MAX_VERSION_QNT);
  update_choosed_version = 0;
  choose_versions_qnt = 0;
  
  json_array_foreach_element(json_array, iterate_version_array, NULL);

    
  return versions;
}

int download_new_version(void) {

  if(!PopupBinario("O sistema pesquisará online pelas versões do sistema", "Ok! continuar.", "Tentar mais tarde")){
    return 1;
  }

  CURL *curl;
  FILE *fp;
  CURLcode res;
  char *url = malloc(1000);
  char errorbuf[ CURL_ERROR_SIZE ] = "";
  const char *next_name_version=NULL;
  global_progress_bar_active = 1;
  global_progress_bar_text = strdup("Buscando versões");

  if(!search_all_versions()){
    return 1;
  }
  int version_pos = choose_version_for_download();
  if(version_pos == NO_VERSION_DEFINED){
    return 1;
  }
  if( (versions) && (versions[version_pos].name)){
    next_name_version = strdup(versions[version_pos].name);
    if(!next_name_version){
      return 1;
    }
  }

  carregar_interface();
  if(!versions[version_pos].assets_qnt){
    if( !PopupBinario("Esta versão não possui anexos para download, ainda deseja continuar o processo?", "Sim! continuar", "Não! parar processo") ){
      return 1;
    }
  }


  const char **files_not_downloaded = malloc(sizeof(char *) * versions[version_pos].assets_qnt);
  int files_not_downloaded_qnt = 0;
  for(int pos=0; pos < versions[version_pos].assets_qnt; pos++){
    carregar_interface();
    sprintf(url, "https://github.com/stdmedoth/pedidos/releases/download/%s/%s", versions[version_pos].name, versions[version_pos].assets[pos]);
    curl = curl_easy_init();
    if (curl) {
      char path[MAX_PATH_LEN];

      const char *ext_file = get_filename_ext(versions[version_pos].assets[pos]);

      if(!strcmp(versions[version_pos].assets[pos], APP_BINEXE_NAME)){
        sprintf(path,"%s/%sNew", APP_BINS_DIR, versions[version_pos].assets[pos]);
      }else{
        sprintf(path,"%s/%s", APP_BINS_DIR, versions[version_pos].assets[pos]);
      }


      global_progress_bar_text = strdup(versions[version_pos].name);
      fp = fopen(path,"wb");
      if(!fp){

        /* 
          verifica se o arquivo realmente é primordial para o funcionamento do sistema,
          de forma que pare a atualização
          Caso seja apenas uma .dll (em caso de nova atualização)
        */
        int stop_update = 1;
        for(int cont=0; update_ext_files_stopper_exceptions[cont]; cont++){
          if(!strcmp(ext_file, update_ext_files_stopper_exceptions[cont])){
            files_not_downloaded[files_not_downloaded_qnt] = strdup(versions[version_pos].assets[pos]);
            files_not_downloaded_qnt++;
            stop_update = 0;
          }
        }
        if(stop_update){
          global_progress_bar_active = 0;
          file_logger(path);
          file_logger(strerror(errno));
          popup(NULL,"Não foi possível armazenar versão atual");
          return 1;
        }
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

  if(files_not_downloaded_qnt){
    const char *not_downloaded_str = str_array_to_string_delim(files_not_downloaded, files_not_downloaded_qnt, '\n');
    const char *msg_prefix = "Aviso\nSegue abaixo alguns arquivos que não puderam ser baixados\n\n";
    char msg[ strlen(msg_prefix) + strlen(not_downloaded_str) ];
    sprintf(msg, "%s%s", msg_prefix, not_downloaded_str);
    popup(NULL,msg);
  }
  char msg[2000];
  sprintf(msg,"A versão %s foi transferida com sucesso!\nDeseja fechar o sistema para efetuar a atualização?", next_name_version);
  global_progress_bar_active = 0;
  if(PopupBinario(msg, "Fechar sistema e atualizar", "Deixar para depois")){
    encerrar(NULL, GTK_WINDOW(janelas_gerenciadas.principal.janela_pointer));
  }
  return 0;
}
