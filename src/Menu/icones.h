GtkWidget **eventos;
#include "cad_ico.c"
#include "cmp_ico.c"


int add_icones()
{

	int cont;
	eventos      = malloc(sizeof(GtkEventBox*)*MAX_ICO_QNT);
	principall   = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);
	cadastrosl   = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);
        comprasl     = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);
        faturamentol = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);
        estoquel     = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);
        financeirol  = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);
        relatoriosl  = malloc(sizeof(GtkBox*)*LINE_ICO_QNT);

	for(cont=0;cont<LINE_ICO_QNT;cont++)
	{
		principall[cont]   = gtk_box_new(0,0);
		cadastrosl[cont]   = gtk_box_new(0,0);
		comprasl[cont]     = gtk_box_new(0,0);
		faturamentol[cont] = gtk_box_new(0,0);
		estoquel[cont]     = gtk_box_new(0,0);
		financeirol[cont]  = gtk_box_new(0,0);
		relatoriosl[cont]  = gtk_box_new(0,0);
	}

	cad_ico();
	cmp_ico();
	return 0;
}