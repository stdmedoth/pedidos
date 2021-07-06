gint 
backup_clientes_gint, 
backup_produtos_gint,
backup_orcamentos_gint,
backup_pedidos_gint,
backup_estoques_gint,
backup_movimentacoes_gint,
backup_bancos_gint,
backup_titulos_rec_gint,
backup_baixas_rec_gint,
backup_titulos_pag_gint,
backup_baixas_pag_gint;

enum BACKUP_OBJ_COL{
	BACKUP_OBJ_MODULE,
	BACKUP_OBJ_TABLE,
	BACKUP_OBJ_QUERY,
};

char *backup_objs[][3] = {
	{"clientes", "clientes", "select * from terceiros"}, 
	{"clientes", "contatos", "select * from contatos"}, 
	
	{"produtos", "produtos", "select * from produtos"}, 
	{"produtos", "precos", "select * from precos"}, 
	{"produtos", "preco_cliente", "select * from preco_cliente"},

	{"orcamentos", "orcamentos", "select * from orcamentos"},
	{"orcamentos", "orc_datas_livres", "select * from orc_datas_livres"},
	{"orcamentos", "Produto_Orcamento", "select * from Produto_Orcamento"},
	{"orcamentos", "orcs_cheques", "select * from orcs_cheques"},

	{"pedidos", "pedidos", "select * from pedidos"},

	{NULL,NULL}
};


int backup_iniciar_exportacao();