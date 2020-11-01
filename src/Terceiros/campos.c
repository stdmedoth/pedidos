GtkWidget *filas;

int altera_ter();
#include "campos/vars/campos_ter.h"
#include "campos/contatos.h"
#include "campos/vars/vinculo_precos.h"
#include "campos/vars/listagem_ter.h"
#include "campos/codigo.c"
#include "campos/code_ter_nfe.c"
#include "campos/cnpj.c"
#include "campos/inscricao.c"
#include "campos/cpf.c"
#include "campos/escolher_doc.c"
#include "campos/nome.c"
#include "campos/cep.c"
#include "campos/bairro.c"
#include "campos/endereco.c"
#include "campos/complemento.c"
#include "campos/tipo.c"
#include "campos/contatos.c"
#include "campos/observacoes.c"
#include "campos/email.c"
#include "campos/precos.c"
#include "campos/numrua.c"
#include "campos/cidade.c"
#include "campos/uf.c"
#include "campos/vinc_transporte.c"
#include "campos/transportadora.c"
#include "campos/outros/prazo.c"
#include "campos/outros/calcular_prazo.c"
#include "campos/outros/verifica_frete.c"
#include "campos/outros/vinculo_precos.c"
#include "campos/outros/produtos.c"


#define CAD_QUERY_TER "insert into terceiros\
(razao, code_nfe, doc,   ie,     tipo_doc, tipoc,  tipo,  cep,   endereco, complmt, bairro, cidade,   uf,   numrua,  tiporua,   transp_code,    transp_num,    transp_logradouro, transp_bairro, transp_cidade, transp_estado,    transp_cep,         transp_obs,       obs,    frete_pago,    vlr_frete_pago,    prazo ) values\
('%s',   '%s',   '%s',  '%s',      %i,    '%s',    %i,   '%s',     '%s',     '%s',   '%s',    '%s',  '%s',   %s,      %i,        '%i',           %i,              '%s',               '%s',        '%s',          '%s',            '%s',              '%s',          '%s',       %i,               %s,          '%s');"

#define CAD_QUERY_TER_VAR nomes_ter, codigos_ter_nfe, doc_ter, inscr_ter, tipo_doc, tipo_ter, terci_tipo, cep_ter, endereco_ter, complmt_ter, bairro_ter, cidade_ter, uf_ter, address_num, tipo_log, atoi(transp_codigo), atoi(transp_num), transp_logradouro, transp_bairro, transp_cidade, transp_estado, transp_cep, transp_obs,observacoes_ter, frete_frag_int, vlr_frete_pago_gchar, prazo_ter

#define UPDATE_QUERY_TER "update terceiros set razao = '%s', code_nfe = '%s', doc = '%s', tipo_doc = %i, ie = '%s' ,tipoc = '%s', tipo = %i, cep = '%s', endereco = '%s', complmt = '%s', bairro = '%s', cidade = '%s', uf = '%s', numrua = %i, tiporua = %i, transp_code = '%i', transp_num = %i ,transp_logradouro = '%s',transp_cidade = '%s', transp_bairro = '%s' ,transp_estado = '%s' , transp_cep = '%s' ,  transp_obs = '%s', obs = '%s', frete_pago =  %i, vlr_frete_pago = %s , prazo = '%s' where code = %s;"

#define UPDATE_QUERY_TER_VAR nomes_ter, codigos_ter_nfe,  doc_ter, tipo_doc, inscr_ter, tipo_ter, terci_tipo, cep_ter,endereco_ter, complmt_ter, bairro_ter, cidade_ter, uf_ter, atoi(address_num), tipo_log, atoi(transp_codigo), atoi(transp_num), transp_logradouro , transp_cidade,  transp_bairro, transp_estado, transp_cep, transp_obs, observacoes_ter, frete_frag_int, vlr_frete_pago_gchar, prazo_ter, codigos_ter
