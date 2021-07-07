GtkWidget *planilha_export_conf_wnd;
int planilha_init_export(int module);


#define PLANL_MOD_TERCEIROS 0
#define PLANL_MOD_PRODUTOS 1
#define PLANL_MOD_MOVIMENTOS 2
#define PLANL_MOD_QNT 3

GtkWidget 
*planilha_export_module_combo,
*planilha_export_open_check,
*planilha_export_path_entry,
*planilha_export_path_button;