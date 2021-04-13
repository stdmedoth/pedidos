enum FORMA_PAG_COLS{
	FORMA_PAG_CODE, 
	FORMA_PAG_NOME
};

struct _forma_pagamento{
	int code;
	char *nome;
};

struct _forma_pagamento_list{
	struct _forma_pagamento **fpags; 
	int qnt_fpags;
};

struct _forma_pagamento *get_forma_pagamento(int code_forma_pagamento);

struct _forma_pagamento **get_formas_pags();