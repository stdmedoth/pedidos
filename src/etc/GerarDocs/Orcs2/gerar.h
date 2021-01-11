#define MM_TO_POINTS(mm)  mm*2
#define WB_TO_RGB(color) color/255.00

#define ORC_CLI_INFOS_HPOS 50
#define ORC_CLI_INFOS_VPOS 320.0

#define ORC_EMP_INFOS_VPOS 100
#define ORC_EMP_INFOS_HPOS 400.0

#define ASS_ORC_HPOS 50.0
#define ASS_ORC_VPOS 526.0

#define ORC_ENTRGA_HPOS 50.0
#define ORC_ENTRGA_VPOS 806.0

#define ORC_ITENS_HPOS 50.0
#define ORC_ITENS_VPOS 970.0

#define ORC_CONDPAG_HPOS 50.0
#define ORC_CONDPAG_VPOS 1380.0

#define TITLE_TEXT_FONT_SIZE 24
#define ITENS_TEXT_FONT_SIZE 18
#define DESCR_TEXT_FONT_SIZE 15

int gera_doc_orc(struct _orc *orc, GtkPrintContext *context);
