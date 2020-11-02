#ifndef PEDIDOS_INCLUDES_HEADER
#define PEDIDOS_INCLUDES_HEADER

#include "basic_headers.h"
#include "Pedidos.h"
#include "init.h"
#include "../Menu/icones.h"
#include "../Menu/abas.h"

#include "fechar.h"
#include "receber_confs.h"
#include "xml_tools.h"
#include "tools.h"
#include "popups.h"
#include "maquinas.h"
#include "temas.h"
#include "impressao.h"
#include "vars.h"

#include "stoi.h"
#include "css.h"
#include "criticas.h"
#include "barra_icones.h"
#include "analisa_campos.h"

#include "../Canones/Cadastro_Operadores.h"
#include "../Canones/gerenciador_janelas.h"
#include "../Canones/cad_ceps/cadastro_ceps.h"
#include "operadores.h"
#include "../Inicio/pega_data.h"

#include "../Parametros/parametros.h"

#include "../Terceiros/cadastro_terceiros.h"
#include "../Terceiros/pesquisa_cad.h"

#include "../Produtos/cadastro_produtos.h"
#include "../Produtos/grupos/cad_grupo.h"

#include "../pesquisadores/grupos.h"
#include "../pesquisadores/datas.h"
#include "../pesquisadores/subgrupos.h"
#include "../pesquisadores/subgrupos_todos.h"
#include "../pesquisadores/terceiros.h"
#include "../pesquisadores/unidades.h"
#include "../pesquisadores/estoques.h"
#include "../pesquisadores/produtos.h"
#include "../pesquisadores/orcamentos.h"
#include "../pesquisadores/pedidos.h"
#include "../pesquisadores/ceps.h"
#include "../pesquisadores/movimentos_ent_estoque.h"
#include "../pesquisadores/movimentos_said_estoque.h"
#include "../pesquisadores/relatorios.h"
#include "../pesquisadores/cond_pag.h"
#include "../pesquisadores/operadores.h"
#include "../pesquisadores/fin_rec.h"
#include "../pesquisadores/fin_pag.h"
#include "../pesquisadores/cidades.h"
#include "../pesquisadores/bancos.h"
#include "../pesquisadores/serv_transporte.h"

#include "../Compras/cadastro_compras.h"
#include "../Compras/cotacao.h"
#include "../Compras/entradas.h"
#include "../Compras/ordem.h"
#include "../Compras/solicitacao.h"

#include "../Unidades/cadastro_unidades.h"

#include "../Estoque/saldos/saldos.h"
#include "../Estoque/entradas/entradas.h"
#include "../Estoque/saidas/saidas.h"
#include "../Estoque/cadastro/estoque.h"

#include "../Vendas/condicoes_pag/cad_pag.h"
#include "../Vendas/condicoes_pag/campos/pag_cod.h"
#include "../Vendas/condicoes_pag/campos/pag_nome.h"
#include "../Vendas/condicoes_pag/campos/pag_init.h"
#include "../Vendas/condicoes_pag/campos/pag_tipo.h"
#include "../Vendas/condicoes_pag/campos/pag_parc_qnt.h"
#include "../Vendas/condicoes_pag/campos/pag_parc.h"
#include "../Vendas/condicoes_pag/campos/pag_datas.h"
#include "../Vendas/condicoes_pag/campos/pag_dia_fixo.h"
#include "../Vendas/condicoes_pag/cancelar.h"
#include "../Vendas/condicoes_pag/concluir.h"
#include "../Vendas/condicoes_pag/alterar.h"
#include "../Vendas/condicoes_pag/excluir.h"

#include "../Vendas/pedidos/pedidos.h"
#include "../Vendas/pedidos/emitir.h"
#include "../Vendas/pedidos/envia_email.h"
#include "../Vendas/pedidos/cancelar.h"
#include "../Vendas/pedidos/excluir.h"
#include "../Vendas/pedidos/gerar.h"
#include "../Vendas/pedidos/status.h"

#include "../Vendas/orcamentos/orcamentos.h"
#include "../Vendas/orcamentos/gerar_totais.h"
#include "../Vendas/orcamentos/janela/adicionar_linha.h"
#include "../Vendas/orcamentos/janela/tirar_linha.h"
#include "../Vendas/orcamentos/campos/entrega_campos.h"

#include "../Vendas/Emissor/CFe/rec_infos_cupom.h"
#include "../Vendas/Emissor/CFe/cfe.h"

#include "../Vendas/pdv/pdv_princ_wnd.h"
#include "../Vendas/pdv/caixa.h"

#include "GerarDocs/Orcs/header.h"
#include "GerarDocs/Orcs/infos_header.h"
#include "GerarDocs/Orcs/observacao.h"
#include "GerarDocs/Orcs/titulo.h"
#include "GerarDocs/Orcs/banco.h"
#include "GerarDocs/Orcs/transporte.h"
#include "GerarDocs/Orcs/itens.h"
#include "GerarDocs/Orcs/rec_datas.h"
#include "GerarDocs/Orcs/cliente.h"
#include "GerarDocs/Orcs/gerar_orcs.h"

#include "../Transportes/cad_trsp.h"

#include "../Financeiro/titulos/receber/cadastro_titulos.h"
#include "../Financeiro/titulos/receber/campos/funcoes.h"
#include "../Financeiro/titulos/pagar/cadastro_titulos.h"
#include "../Financeiro/baixas/receber/cadastro_baixas.h"
#include "../Financeiro/baixas/pagar/cadastro_baixas.h"
#include "../Financeiro/bancos/cad_bancos.h"
#include "../Financeiro/titulos/pagar/contas_fixas/contas_fixas.h"
#include "../Financeiro/titulos/etc/importacao/importador.h"
#include "../Financeiro/titulos/etc/importacao/iniciar.h"

#include "../Relatorios/relatorios.h"
#include "../Relatorios/relatorios/produtos/produtos.h"
#include "../Relatorios/relatorios/terceiros/terceiros.h"
#include "../Relatorios/relatorios/movimentos/movimentos.h"
#include "../Relatorios/relatorios/orc_prod/orc_prods.h"

#include "../Relatorios/pesquisar/relat_ptabs.h"

#include "../Relatorios/fixados/iconview.h"
#include "../Relatorios/fixados/produtos/principal.h"
#include "../Relatorios/fixados/vendas/principal.h"
#include "../Relatorios/fixados/estoques/principal.h"
#include "../Relatorios/fixados/financeiro/receber/principal.h"
#include "../Relatorios/fixados/financeiro/pagar/principal.h"

#include "../Suporte/suporte.h"
#include "../Suporte/adicionar.h"
#include "../Suporte/atualiza.h"
#include "../Suporte/email.h"

#include "../Integracoes/woocommerce/produtos.h"
#include "../Integracoes/woocommerce/clientes.h"

#include "../Tecnico/cad_empresa/cad_empresa.h"

#include "../Estoque/cadastro/conclui.h"
#include "../Estoque/cadastro/cancela.h"
#include "../Estoque/cadastro/altera.h"
#include "../Estoque/cadastro/exclui.h"

#include "../Gestao/enviar_email.h"
#include "../Gestao/Notificacao/notificacao.h"

#include "../Kanban/kanban.h"


#endif
