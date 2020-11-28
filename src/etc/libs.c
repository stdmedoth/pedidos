#include "libs.h"


#include "init.c"
#include "../Menu/icones.c"
#include "../Menu/abas.c"

#include "receber_confs.c"

#include "xml_tools.c"
#include "tools.c"
#include "popups.c"
#include "maquinas.c"
#include "criticas.c"
#include "pesquisador.c"
#include "css.c"
#include "http.c"
#include "impressao.c"
#include "temas.c"
#include "barra_icones.c"
#include "../Inicio/pega_data.c"
#include "analisa_campos.c"

#include "operadores.c"

#include "../Parametros/parametros.c"

#include "../pesquisadores/grupos.c"
#include "../pesquisadores/datas.c"
#include "../pesquisadores/subgrupos.c"
#include "../pesquisadores/subgrupos_todos.c"
#include "../pesquisadores/terceiros.c"
#include "../pesquisadores/unidades.c"
#include "../pesquisadores/produtos.c"
#include "../pesquisadores/estoques.c"
#include "../pesquisadores/orcamentos.c"
#include "../pesquisadores/pedidos.c"
#include "../pesquisadores/ceps.c"
#include "../pesquisadores/movimentos_said_estoque.c"
#include "../pesquisadores/movimentos_ent_estoque.c"
#include "../pesquisadores/relatorios.c"
#include "../pesquisadores/cond_pag.c"
#include "../pesquisadores/operadores.c"
#include "../pesquisadores/fin_rec.c"
#include "../pesquisadores/fin_pag.c"
#include "../pesquisadores/cidades.c"
#include "../pesquisadores/requisicoes.c"
#include "../pesquisadores/bancos.c"
#include "../pesquisadores/serv_transporte.c"

#include "../Canones/Cadastro_Operadores.c"
#include "../Canones/cad_ceps/cadastro_ceps.c"
#include "../Canones/Vinculos_Chaves.c"
#include "../Inicio/fechar.c"

#include "../Terceiros/cadastro_terceiros.c"
#include "../Terceiros/pesquisa_cad.c"

#include "../Produtos/cadastro_produtos.c"

#include "../Unidades/cadastro_unidades.c"

#include "../Compras/cadastro_compras.c"
#include "../Compras/entradas/entradas.c"
#include "../Compras/ordens/ordem.c"
#include "../Compras/cotacoes/cotacao.c"
#include "../Compras/solicitacoes/solicitacao.c"

#include "../Vendas/condicoes_pag/cad_pag.c"
#include "../Vendas/condicoes_pag/campos/pag_cod.c"
#include "../Vendas/condicoes_pag/campos/pag_nome.c"
#include "../Vendas/condicoes_pag/campos/pag_init.c"
#include "../Vendas/condicoes_pag/campos/pag_tipo.c"
#include "../Vendas/condicoes_pag/campos/pag_parc_qnt.c"
#include "../Vendas/condicoes_pag/campos/pag_parc.c"
#include "../Vendas/condicoes_pag/campos/pag_datas.c"
#include "../Vendas/condicoes_pag/campos/pag_dia_fixo.c"
#include "../Vendas/condicoes_pag/cancelar.c"
#include "../Vendas/condicoes_pag/concluir.c"
#include "../Vendas/condicoes_pag/alterar.c"
#include "../Vendas/condicoes_pag/excluir.c"

#include "../Vendas/orcamentos/campos/entrega_campos.c"
#include "../Vendas/orcamentos/orcamentos.c"
#include "../Vendas/orcamentos/gerar_totais.c"
#include "../Vendas/orcamentos/janela/adicionar_linha.c"
#include "../Vendas/orcamentos/janela/tirar_linha.c"

#include "../Vendas/Emissor/CFe/rec_infos_cupom.c"
#include "../Vendas/Emissor/CFe/cfe.c"

#include "../Vendas/pdv/pdv_princ_wnd.c"
#include "../Vendas/pdv/caixa.c"

#include "GerarDocs/Orcs/banco.c"
#include "GerarDocs/Orcs/header.c"
#include "GerarDocs/Orcs/infos_header.c"
#include "GerarDocs/Orcs/observacao.c"
#include "GerarDocs/Orcs/titulo.c"
#include "GerarDocs/Orcs/transporte.c"
#include "GerarDocs/Orcs/itens.c"
#include "GerarDocs/Orcs/rec_datas.c"
#include "GerarDocs/Orcs/cliente.c"
#include "GerarDocs/Orcs/gerar_orcs.c"

#include "../Vendas/pedidos/emitir.c"
#include "../Vendas/pedidos/cancelar.c"
#include "../Vendas/pedidos/excluir.c"
#include "../Vendas/pedidos/pedidos.c"
#include "../Vendas/pedidos/gerar.c"
#include "../Vendas/pedidos/envia_email.c"
#include "../Vendas/pedidos/status.c"

#include "../Transportes/cad_trsp.c"

#include "../Estoque/cadastro/codigo.c"
#include "../Estoque/cadastro/nome.c"
#include "../Estoque/saldos/saldos.c"
#include "../Estoque/entradas/entradas.c"
#include "../Estoque/saidas/saidas.c"
#include "../Estoque/cadastro/conclui.c"
#include "../Estoque/cadastro/cancela.c"
#include "../Estoque/cadastro/altera.c"
#include "../Estoque/cadastro/exclui.c"
#include "../Estoque/cadastro/estoque.c"

#include "../Financeiro/titulos/receber/cadastro_titulos.c"
#include "../Financeiro/titulos/receber/campos/funcoes.c"
#include "../Financeiro/titulos/pagar/cadastro_titulos.c"
#include "../Financeiro/baixas/receber/cadastro_baixas.c"
#include "../Financeiro/baixas/pagar/cadastro_baixas.c"
#include "../Financeiro/bancos/cad_bancos.c"
#include "../Financeiro/titulos/pagar/contas_fixas/contas_fixas.c"
#include "../Financeiro/titulos/etc/importacao/importador.c"
#include "../Financeiro/titulos/etc/importacao/iniciar.c"


#include "../Vendas/faturamento.c"
#include "../Relatorios/relatorios.c"
#include "../Relatorios/relatorios/produtos/produtos.c"
#include "../Relatorios/pesquisar/relat_ptabs.c"
#include "../Relatorios/relatorios/terceiros/terceiros.c"
#include "../Relatorios/relatorios/movimentos/movimentos.c"
#include "../Relatorios/relatorios/orc_prod/orc_prods.c"

#include "../Relatorios/fixados/iconview.c"
#include "../Relatorios/fixados/produtos/principal.c"
#include "../Relatorios/fixados/vendas/principal.c"
#include "../Relatorios/fixados/estoques/principal.c"
#include "../Relatorios/fixados/financeiro/receber/principal.c"
#include "../Relatorios/fixados/financeiro/pagar/principal.c"

#include "../Marketing/analises/analisar.c"
#include "../Marketing/emails/modela_email.c"

#include "../Suporte/suporte.c"
#include "../Suporte/adicionar.c"
#include "../Suporte/atualiza.c"
#include "../Suporte/email.c"

#include "../Integracoes/woocommerce/produtos.c"
#include "../Integracoes/woocommerce/clientes.c"

#include "../Gestao/enviar_email.c"
#include "../Gestao/Notificacao/notificacao.c"
#include "../Kanban/kanban.c"

#include "../Tecnico/cad_empresa/cad_empresa.c"
#include "../Tecnico/contratos/contratos.c"

#include "../Canones/gerenciador_janelas.c"
