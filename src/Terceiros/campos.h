GtkWidget *filas;
static GtkWidget *entry_preco_ter_label;
static GtkWidget *entry_preco_ter_prcvist;
static GtkWidget *entry_preco_ter_prcfat;
static GtkWidget *grid1_ter_preco=NULL;
static int atualizando_ter_precos=0;

int produto_ter();
int notebook_preco_ter();
int altera_ter();

#include "campos/vars/campos_ter.h"
#include "campos/nome_fantasia.h"
#include "campos/cliente_desde.h"
#include "campos/cep.h"
#include "campos/contatos.h"
#include "campos/vars/vinculo_precos.h"
#include "campos/vars/listagem_ter.h"



#define CAD_QUERY_TER "insert into terceiros\
(razao, nome_fantasia, code_nfe, doc,   ie,     tipo_doc, tipoc,  tipo, relacionamento_desde , cep,   endereco, complmt, bairro, cidade,   uf,   numrua,  tiporua,   transp_code,    transp_num,    transp_logradouro, transp_bairro, transp_cidade, transp_estado,    transp_cep,         transp_obs,       obs,    frete_pago,    vlr_frete_pago,    prazo ) values\
('%s',   '%s',          '%s',   '%s',  '%s',      %i,     '%s',    %i,      %s,                '%s',     '%s',     '%s',   '%s',    '%s',  '%s',   %s,      %i,        '%i',           %i,              '%s',               '%s',        '%s',          '%s',            '%s',              '%s',          '%s',       %i,               %s,          %s);"
#define CAD_QUERY_TER_VAR nomes_ter, ter_nome_fantasia_gchar, codigos_ter_nfe, doc_ter, inscr_ter, tipo_doc, tipo_ter, terci_tipo, ter_cliente_desde_gchar, cep_ter, endereco_ter, complmt_ter, bairro_ter, cidade_ter, uf_ter, address_num, tipo_log, atoi(transp_codigo), atoi(transp_num), transp_logradouro, transp_bairro, transp_cidade, transp_estado, transp_cep, transp_obs,observacoes_ter, ter_com_entrega, vlr_frete_pago_gchar, prazo_ter

#define UPDATE_QUERY_TER "update terceiros set razao = '%s', nome_fantasia = '%s', code_nfe = '%s', doc = '%s', tipo_doc = %i, ie = '%s' ,tipoc = '%s', tipo = %i, relacionamento_desde = %s, cep = '%s', endereco = '%s', complmt = '%s', bairro = '%s', cidade = '%s', uf = '%s', numrua = %i, tiporua = %i, transp_code = '%i', transp_num = %i ,transp_logradouro = '%s',transp_cidade = '%s', transp_bairro = '%s' ,transp_estado = '%s' , transp_cep = '%s' ,  transp_obs = '%s', obs = '%s', frete_pago =  %i, vlr_frete_pago = %s , prazo = %s where code = %s;"
#define UPDATE_QUERY_TER_VAR nomes_ter, ter_nome_fantasia_gchar, codigos_ter_nfe,  doc_ter, tipo_doc, inscr_ter, tipo_ter, terci_tipo, ter_cliente_desde_gchar, cep_ter,endereco_ter, complmt_ter, bairro_ter, cidade_ter, uf_ter, atoi(address_num), tipo_log, atoi(transp_codigo), atoi(transp_num), transp_logradouro , transp_cidade,  transp_bairro, transp_estado, transp_cep, transp_obs, observacoes_ter, ter_com_entrega, vlr_frete_pago_gchar, prazo_ter, codigos_ter
