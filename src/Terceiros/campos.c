MYSQL_ROW campos;
GtkWidget *filas;

int altera_ter();
#include "campos/vars/campos_ter.h"
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
#include "campos/endereco.c"
#include "campos/tipo.c"
#include "campos/contatos.c"
#include "campos/observacoes.c"
#include "campos/email.c"
#include "campos/precos.c"
#include "campos/numrua.c"
#include "campos/cidade.c"
#include "campos/uf.c"
#include "campos/transportadora.c"
#include "campos/outros/prazo.c"
#include "campos/outros/calcular_prazo.c"
#include "campos/outros/verifica_frete.c"
#include "campos/outros/grupos_preco.c"
#include "campos/outros/grupo.c"
#include "campos/outros/produtos.c"


#define CAD_QUERY_TER "insert into terceiros\
(razao, code_nfe, doc,   ie,	  tipo_doc, tipoc,  tipo,  cep,   endereco,  cidade,   uf,   numrua,  tiporua,  celular,   contatoc,  telefone,  contatot,  email,  contatoe,		transp_nome,	transp_num,	transp_logradouro,  transp_cidade, transp_estado,	transp_cep,      transp_telefone,   transp_cnpj,    transp_ie,    transp_obs,       obs,    frete_pago,    vlr_frete_pago,    prazo ) values\
('%s', '%s', '%s',  '%s',      %i,    '%s',   %i,    '%s',   '%s',     '%s',    '%s',    %s,       %i,      '%s',      '%s',      '%s',      '%s',     '%s',    '%s' ,			'%s',			%s,			'%s',            	'%s',  	   		'%s',		'%s',				'%s',			  '%s',			  '%s',			'%s',			'%s',	   %i,				%s,		      '%s');"
#define CAD_QUERY_TER_VAR nomes_ter, codigos_ter_nfe, doc_ter, inscr_ter, tipo_doc, tipo_ter, terci_tipo, cep_ter, endereco_ter, cidade_ter, uf_ter, address_num, tipo_log, celular_ter, contatoc_ter, telefone_ter, contatot_ter, email_ter, contatoe_ter, transp_nome, transp_num, transp_logradouro, transp_cidade, transp_estado, transp_cep,transp_telefone,transp_cnpj,transp_ie,transp_obs,observacoes_ter, frete_frag_int, vlr_frete_pago_gchar, prazo_ter

#define UPDATE_QUERY_TER "update terceiros set razao = '%s', code_nfe = '%s', doc = '%s', tipo_doc = %i, ie = '%s' ,tipoc = '%s', tipo = %i, cep = '%s', endereco = '%s', cidade = '%s', uf = '%s', numrua = %s,tiporua = %i, telefone = '%s',contatot = '%s',celular = '%s',contatoc = '%s', email = '%s', contatoe = '%s', transp_nome = '%s', transp_num = %s ,transp_logradouro = '%s',transp_cidade = '%s' ,transp_estado = '%s' , transp_cep = '%s' , transp_telefone = '%s' , transp_cnpj = '%s', transp_ie = '%s', transp_obs = '%s', obs = '%s', frete_pago =  %i, vlr_frete_pago = %s , prazo = '%s' where code = %s;"
#define UPDATE_QUERY_TER_VAR nomes_ter, codigos_ter_nfe,  doc_ter, tipo_doc, inscr_ter, tipo_ter, terci_tipo, cep_ter,endereco_ter, cidade_ter, uf_ter,address_num, tipo_log,telefone_ter,contatot_ter,celular_ter,contatoc_ter,email_ter, contatoe_ter, transp_nome, transp_num, transp_logradouro , transp_cidade, transp_estado, transp_cep, transp_telefone, transp_cnpj, transp_ie, transp_obs, observacoes_ter, frete_frag_int, vlr_frete_pago_gchar, prazo_ter, codigos_ter
