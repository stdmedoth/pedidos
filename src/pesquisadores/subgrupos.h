struct duo_widget{
	int grupo;
	int posicao;
	GtkWidget *entry;
}*find_subgrupos_restrict;

GtkWidget *psq_subgrp_wnd;
int entry_subgrp_pesquisa(GtkEntry *widget, GtkTreeView *treeview);
int pesquisa_subgrp();
