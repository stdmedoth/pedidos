enum {
  CAIXA_FECHADO,
  CAIXA_ABERTO,
};

enum{
  CX_ABERTURA,
  CX_REFORCO,
  CX_SANGRIA,
  CX_FECHAMENTO
};

struct _caixa{
  int id;
  char nome[50];
  int operador;
  int status;
};


struct _caixa *caixa_get_aberto();

void signal_caixa_encerramento(GtkWidget *button, struct _caixa *caixa);

int janela_caixa_encerrar(struct _caixa *caixa);

int caixas_qnt();

int janela_abrir_caixa(struct _maquina *maquina, struct _caixa *caixa);

int janela_criar_caixa();
