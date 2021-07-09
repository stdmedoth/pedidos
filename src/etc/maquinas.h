enum{
  MAQUINA_ATIVA,
  MAQUINA_INATIVA
};

struct _maquina{
  int id;
  char *nome;
  char *hostname;
  char *ip;
  int ativa;
};

struct _maquina *maquina_atual=NULL;

struct _maquina *maquinas_criar_nova();

struct _maquina *maquinas_get_atual();
