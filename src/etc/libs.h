#include "css.c"
#include "vars.h"
#include "stoi.h"

#include "parametros.h"
#include "operadores.h"

#include "tools.c"
#include "criticas.c"
#include "pesquisador.c"
#include "personalizacao.c"
#include "parametros.c"
#include "operadores.c"
#include "temas.c"

#include "../Produtos/grupos/cad_grupo.h"
#include "../pesquisadores/grupos.h"
#include "../pesquisadores/datas.h"
#include "../pesquisadores/subgrupos.h"
#include "../pesquisadores/terceiros.h"
#include "../pesquisadores/unidades.h"
#include "../pesquisadores/produtos.h"
#include "../pesquisadores/orcamentos.h"
#include "../pesquisadores/pedidos.h"
#include "../pesquisadores/ceps.h"
#include "../Unidades/cadastro_unidades.h"
#include "../Estoque/saldos/saldos.h"
#include "../Estoque/entradas/entradas.h"
#include "../Estoque/saidas/saidas.h"
#include "../Estoque/cadastro/estoque.h"
#include "../Vendas/pedidos/pedidos.h"
#include "../Vendas/pedidos/emitir.h"
#include "../Vendas/pedidos/cancelar.h"
#include "../Vendas/orcamentos/orcamentos.h"

#include "../pesquisadores/grupos.c"
#include "../pesquisadores/datas.c"
#include "../pesquisadores/subgrupos.c"
#include "../pesquisadores/terceiros.c"
#include "../pesquisadores/unidades.c"
#include "../pesquisadores/produtos.c"
#include "../pesquisadores/orcamentos.c"
#include "../pesquisadores/pedidos.c"
#include "../pesquisadores/ceps.c"
#include "../Canones/Cadastro_Operadores.c"
#include "../Canones/Vinculos_Chaves.c"
#include "../Inicio/fechar.c"
#include "../Inicio/pega_data.c"
#include "../Terceiros/cadastro_terceiros.c"
#include "../Produtos/cadastro_produtos.c"
#include "../Unidades/cadastro_unidades.c"
#include "../Compras/cadastro_compras.c"
#include "../Vendas/orcamentos/orcamentos.c"
#include "../Vendas/pedidos/emitir.c"
#include "../Vendas/pedidos/cancelar.c"
#include "../Vendas/pedidos/pedidos.c"


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

#include "../Vendas/faturamento.c"
#include "../Listagens/relatorios.c"

