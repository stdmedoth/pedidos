int mkt_mail_modelpronto_fun(){

  CURL *curl = curl_easy_init();
  CURLcode res = CURLE_OK;
  static struct curl_memory chunk;

  if(curl_global_init(CURL_GLOBAL_ALL)){
    popup(NULL,"Não foi iniciar criar conexão");
    return 1;
  }
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, MODEL_SERVER_URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_receber_resultado);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
  }
  chunk.size = 0;
  res = curl_easy_perform(curl);

  if(res != CURLE_OK){
    popup(NULL,"Não foi possível conectar o serviço");
    return 1;
  }
  gchar *xmlstring;
  if(chunk.size)
    xmlstring = strdup(chunk.response);
  else{
    popup(NULL,"Sem resposta do servidor");
    return 1;
  }

  xmlDocPtr document = xmlReadDoc((xmlChar*)xmlstring, MODEL_SERVER_URL, "UTF-8", XML_PARSE_RECOVER);


  curl_easy_cleanup(curl);

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(janela,"Modelos de Emails");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_title(GTK_WINDOW(janela),"Modelos Base");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"mail-replied");

  if(janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND].janela_pointer)
    gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janelas_gerenciadas.vetor_janelas[REG_MODMAIL_WND].janela_pointer));
  else
    gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));

  gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  gtk_widget_show_all(janela);
  return 0;
}
