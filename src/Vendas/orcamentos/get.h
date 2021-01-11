struct _orc *orc_get_orc(int orc_code);

struct _orc_valores *orc_get_valores(struct _orc *orc);

struct _orc_parcelas *orc_get_parcelas(struct _orc *orc);

struct _transporte *orc_get_entrega(struct _orc *orc);

struct _orc_itens **orc_get_itens(struct _orc *orc);

int orc_get_itens_qnt(int orc_code);
