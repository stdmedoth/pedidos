int add_icones(void);

#define MAX_ICO_QNT 24
#define LINE_ICO_QNT 2
#define ICOL 5
#define CAD_ICO_QNT 10
#define EST_ICO_QNT 3
#define CMP_ICO_QNT 4
#define FIN_ICO_QNT 6
#define REL_ICO_QNT 6

GtkWidget **eventos;

static GtkWidget **principall;
static GtkWidget **cadastrosl;
static GtkWidget **comprasl;
static GtkWidget **faturamentol;
static GtkWidget **estoquel;
static GtkWidget **financeirol;
static GtkWidget **marketingl;
static GtkWidget **relatoriosl;
static GtkWidget **tecnicosl;

#include "cad_ico.h"
#include "est_ico.h"
#include "vnd_ico.h"
#include "cmp_ico.h"
#include "fin_ico.h"
#include "mkt_ico.h"
#include "rel_ico.h"
#include "tcn_ico.h"
