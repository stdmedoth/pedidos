void param_dev_defs();

static struct  {
	int expirar_sessao;
	int inatividade_fecha;
	int produtos_fiscal;

	int vlr_bx_dif_tit;

	int retirar_orc_linha_item;

	int conf_format_file;

}param_funcionalidades;


enum FILE_FORMATS{
	JSON_FILE,
	XML_FILE
};
