enum FORMA_PAG_COLS{
	FORMA_PAG_CODE, 
	FORMA_PAG_NOME,
	FORMA_PAG_TIPO
};

enum {
	FP_TIPO_NULL,
	FP_TIPO_DINHEIRO,
	FP_TIPO_CHEQUE,
	FP_TIPO_CARTAO,
	FP_TIPO_TRASNF,
	FP_TIPO_OUROS
};

struct _forma_pagamento{
	int code;
	char *nome;
	int tipo;
};

struct _forma_pagamento_list{
	struct _forma_pagamento **fpags; 
	int qnt_fpags;
};

struct _forma_pagamento *get_forma_pagamento(int code_forma_pagamento);

struct _forma_pagamento **get_formas_pags();