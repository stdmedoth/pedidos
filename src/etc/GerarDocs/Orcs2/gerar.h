#define MM_TO_POINTS(mm)  mm*2
#define WB_TO_RGB(color) color/255.00

#define ORC_TITLE_TEXT_FONT_SIZE 24
#define ORC_NORMAL_TEXT_FONT_SIZE 15
#define ORC_ITENS_TEXT_FONT_SIZE 12
#define ORC_DESCR_TEXT_FONT_SIZE 10

int gera_doc_orc(struct _orc *orc, GtkPrintContext *context);
