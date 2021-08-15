static int qnt_prod_orc_calc=0, preco_prod_orc_calc=0;
static int tipodesc;
int desconto_prod_orc(GtkWidget *widget,int posicao);
int preco_prod_orc(GtkWidget *widget,int posicao);
int qnt_prod_orc(GtkWidget *widget,int posicao);
int calcula_prod_orc(GtkWidget *widget, int posicao);

#include "campos/form_pag.h"
#include "campos/orig_preco_orc.h"
#include "campos/cond_pag.h"
#include "campos/outros/cheque.h"
#include "campos/outros/banco.h"
#include "campos/outros/data_parc.h"
#include "campos/outros/campos_de_datas.h"
#include "campos/outros/datas_livres.h"
#include "campos/outros/sem_financeiro.h"

#include "alterar.h"
#include "concluir.h"
#include "excluir.h"
#include "cancelar.h"
