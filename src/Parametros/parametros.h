//combo_box de terceiros
static gchar **nomes_temas;
static int temas_qnt=0;
GtkWidget **campos_de_critica;

GtkWidget *tecn_param_nav_path1_entry, *tecn_param_nav_path2_entry, *tecn_param_nav_choose1_radio, *tecn_param_nav_choose2_radio;
GtkWidget *tecn_param_imp_path1_entry, *tecn_param_imp_path2_entry, *tecn_param_imp_path3_entry;

//quantidade de flags/aba
const int orc_critic_campos_qnt=3;

int parametrizar();

int temas();
//static int orc_prod_saldo_limite=0;

static GtkWidget *janela_init,
*janela_keep_above,
*tema_combo_box,
*est_orc_padrao;


#define CAMPOS_QNT 25
int vet_erro[CAMPOS_QNT+1];

static struct {
	int navegador_pdr;
	gchar navegador_path1[MAX_PATH_LEN];
	gchar navegador_path2[MAX_PATH_LEN];
}navegadores;

static struct {
	gchar imp_path1[MAX_PATH_LEN];
	gchar imp_path2[MAX_PATH_LEN];
	gchar imp_path3[MAX_PATH_LEN];
}impressoras;

static struct {
		int est_orc_padrao;
}orc_params;

#include "integr_params.h"
#include "param_dev.h"
#include "orc_params.h"
#include "personalizacao.h"
#include "prod_params.h"
#include "ter_params.h"
