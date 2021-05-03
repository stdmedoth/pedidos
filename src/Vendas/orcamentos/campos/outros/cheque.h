GtkWidget *orc_cheque_fixed;

GtkWidget 
*orc_cheque_code_entry,
*orc_cheque_conta_entry,
*orc_cheque_banco_entry,
*orc_cheque_serie_entry,
*orc_cheque_numero_entry,
*orc_cheque_pagante_entry,
*orc_cheque_emissao_entry;

gchar 
*orc_cheque_code_gchar,
*orc_cheque_banco_gchar,
*orc_cheque_conta_gchar,
*orc_cheque_serie_gchar,
*orc_cheque_numero_gchar,
*orc_cheque_pagante_gchar,
*orc_cheque_emissao_gchar,
*orc_cheque_valor_gchar;

enum ORC_CHEQUE_COLS{
	ORC_CHEQUE_CODE_COL,
	ORC_CHEQUE_ORC_COL,
	ORC_CHEQUE_CHQ_COL,
	ORC_CHEQUE_NUM_ROWS
};

int orc_cheque_finan();
GtkWidget *orc_cheque_get_widget();

#include "cheque_campos.h"