int PopupBinario(char *mensagem, char *positivo, char *negativo);

void popup(GtkWidget *widget,gchar *string);

void reportar_encerramento_brusco();

gpointer carregando_wnd();

xmlNodePtr confirmar_envio_email(gchar *destino, gchar *conteudo);

char *get_text_from_input(char *text, GtkWidget *parent_wnd);
