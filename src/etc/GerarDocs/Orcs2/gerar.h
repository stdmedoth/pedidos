#define MM_TO_POINTS(mm)  mm*2
#define WB_TO_RGB(color) color/255.00

#define TITLE_TEXT_FONT_SIZE 24
#define ITENS_TEXT_FONT_SIZE 18
#define DESCR_TEXT_FONT_SIZE 15

int gera_doc_orc(struct _orc *orc, GtkPrintContext *context);
