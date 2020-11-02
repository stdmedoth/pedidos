enum{
  MAQUINA_ATIVA,
  MAQUINA_INATIVA
};

struct _maquina{
  int id;
  char nome[50];
  char hostname[50];
  char ip[15];
  int ativa;
};

struct _maquina *maquinas_criar_nova();

struct _maquina *maquinas_get_atual();
