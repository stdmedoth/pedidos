char **mail_payload_text;
static int enviando_email = 0;

int enviar_email_orcamento(char *nome_destino,char *email_destino, char *arquivo_orcamento);

int enviar_email_suporte( char *arquivo_suporte );

int enviar_email_html(char *assunto, char *nome_destino, char *email_destino, char *conteudo);


struct upload_status {
  int lines_read;
  char* data;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
