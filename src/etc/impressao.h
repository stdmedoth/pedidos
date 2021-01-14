#define IMP_PORT1           "LPT1"
#define IMP_PORT2           "LPT2"

int iniciar_impressao(char *gerado);

void carregar_navimps(void);

int desenhar_pdf(char *gerando_file);

int iniciar_escolha(GtkWidget *widget , char *gerando_file);

int escolher_finalizacao(char *gerando_file);
