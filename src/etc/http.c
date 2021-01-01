size_t curl_receber_resultado(void *data, size_t size, size_t nmemb, void *userp){

  size_t realsize = size * nmemb;
  struct curl_memory *mem = (struct curl_memory *)userp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0;  /* out of memory! */

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}
