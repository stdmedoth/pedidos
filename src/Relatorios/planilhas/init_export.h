GtkWidget *planilha_export_conf_wnd;
int planilha_init_export(int module);

enum{
	PLANL_MOD_TERCEIROS,
	PLANL_MOD_PRODUTOS,
	PLANL_MOD_PEDIDOS,
	PLANL_MOD_ORCAMENTOS,
	PLANL_MOD_MOVIMENTOS,
	PLANL_MOD_FINAN_REC,
	PLANL_MOD_FINAN_PAG,
	PLANL_MOD_FINAN_FLUXO,
	PLANL_MOD_QNT
};

GtkWidget
*planilha_export_module_combo,
*planilha_export_open_check,
*planilha_export_path_entry,
*planilha_export_path_button;
