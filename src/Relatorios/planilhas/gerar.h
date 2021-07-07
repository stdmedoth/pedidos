int planilhas_gerar();

const char *planilhas_gerar_querys[][2] = {
	{ENUM_TO_STR(PLANL_MOD_TERCEIROS), "SELECT * FROM terceiros"},
	{ENUM_TO_STR(PLANL_MOD_PRODUTOS), "SELECT * FROM produtos"},
	{ENUM_TO_STR(PLANL_MOD_MOVIMENTOS), "SELECT * FROM movimento_estoque"}, 
	{NULL, NULL}
};