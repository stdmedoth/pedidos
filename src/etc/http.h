struct curl_memory {
  char *response;
  size_t size;
};

size_t curl_receber_resultado(void *data, size_t size, size_t nmemb, void *userp);
