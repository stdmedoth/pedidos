#include "xml_tools.h"
#include "tools.h"
#include "impressao.h"
#include "vars.h"
#include "stoi.h"
#include "css.h"
#include "criticas.h"
#include "barra_icones.h"
#include "analisa_campos.h"


#include "../Canones/gerenciador_janelas.h"
#include "../Canones/cad_ceps/cadastro_ceps.h"
#include "operadores.h"
#include "../Inicio/pega_data.h"

#include "../Parametros/orc_params.h"
#include "../Parametros/prod_params.h"
#include "../Parametros/ter_params.h"
#include "../Parametros/personalizacao.h"
#include "../Parametros/parametros.h"

#include "../Terceiros/cadastro_terceiros.h"
#include "../Terceiros/pesquisa_cad.h"

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

#include "rec_orc_infos.h"

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

#include "../Tecnico/cad_empresa/cad_empresa.h"
#include "../Emissor/cria_xml.h"

#include "../Estoque/cadastro/conclui.h"
#include "../Estoque/cadastro/cancela.h"
#include "../Estoque/cadastro/altera.h"
#include "../Estoque/cadastro/exclui.h"

#include "../Gestao/enviar_email.h"
#include "../Gestao/Notificacao/notificacao.h"

#include "../Kanban/kanban.h"

#include "receber_confs.c"
#include "xml_tools.c"
#include "tools.c"
#include "criticas.c"
#include "pesquisador.c"
#include "css.c"
#include "impressao.c"
#include "temas.c"
#include "barra_icones.c"
#include "../Inicio/pega_data.c"
#include "analisa_campos.c"

#include "operadores.c"

#include "../Parametros/orc_params.c"
#include "../Parametros/prod_params.c"
#include "../Parametros/ter_params.c"
#include "../Parametros/personalizacao.c"
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

#include "rec_orc_infos.c"

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

#include "../Suporte/suporte.c"
#include "../Suporte/adicionar.c"
#include "../Suporte/atualiza.c"
#include "../Suporte/email.c"

#include "../Gestao/enviar_email.c"
#include "../Gestao/Notificacao/notificacao.c"
#include "../Kanban/kanban.c"

#include "../Emissor/cria_xml.c"

#include "../Tecnico/cad_empresa/cad_empresa.c"

#include "../Canones/gerenciador_janelas.c"
