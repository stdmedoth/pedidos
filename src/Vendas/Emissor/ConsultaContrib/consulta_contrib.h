struct MemoryStruct {
  char *memory;
  size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

int consulta_contrib_wnd();

int consulta_contrib_consulta(gchar *cnpj, gchar *uf);

xmlDocPtr consulta_contrib_cria_xml(gchar *cnpj, gchar *uf);


struct {
  gchar *cnpj;
  gchar *uf;
  gchar *cStat;
  gchar *xMotivo;
  gchar *xNome;
  gchar *IE;
  gchar *CEP;
  gchar *xLgr;
  gchar *nro;
  gchar *xBairro;
  gchar *xMun;
  gchar *UF;
}consulta_cnpj;
