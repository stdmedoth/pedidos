#define MM_TO_POINTS(mm)  mm*2
#define WB_TO_RGB(color) color/255.00

#define ORC_TITLE_TEXT_FONT_SIZE 24
#define ORC_NORMAL_TEXT_FONT_SIZE 15
#define ORC_ITENS_TEXT_FONT_SIZE 12
#define ORC_TINY_TEXT_FONT_SIZE 9
#define ORC_DESCR_TEXT_FONT_SIZE 10

int gera_doc_orc(struct _orc *orc, GtkPrintContext *context);

gchar *gerar_doc_orc_xml_paths[] = {
  "orc/orc_code",
  "orc/email",
  "orc/nome_cliente",
  "orc/cidade_cliente",
  "orc/ender_cliente",
  "orc/telefone_cliente",
  "orc/contato_cliente",

  "orc/img_logo",

  "orc/itens/codigo",
  "orc/itens/descricao",
  "orc/itens/unidade",
  "orc/itens/quantidade",
  "orc/itens/valor_unit",
  "orc/itens/subtotal",

  "orc/subtotal",
  "orc/desconto",
  "orc/total",

  "orc/parcelas",
  "orc/condicao_pagamento",

  "orc/observacao",

  "orc/transporte/transportadora_nome",

  "orc/transporte/origem/cep",
  "orc/transporte/origem/logradouro",
  "orc/transporte/origem/numero",
  "orc/transporte/origem/bairro",
  "orc/transporte/origem/cidade",
  "orc/transporte/origem/uf",

  "orc/transporte/destino/cep",
  "orc/transporte/destino/logradouro",
  "orc/transporte/destino/numero",
  "orc/transporte/destino/bairro",
  "orc/transporte/destino/cidade",
  "orc/transporte/destino/uf",

  "orc/transporte/valor",
  "orc/transporte/desconto",
  "orc/transporte/observacao",
  NULL
};
