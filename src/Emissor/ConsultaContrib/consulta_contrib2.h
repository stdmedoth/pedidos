int consulta_contrib(const gchar *formated_cnpj, struct _terc_infos *contrib);

struct _consulta_cnpj{
  gchar *cnpj;
  gchar *uf;
  gchar *cStat;
  gchar *xMotivo;
  gchar *xNome;
  gchar *NFantasia;
  gchar *IE;
  gchar *CEP;
  gchar *xLgr;
  gchar *nro;
  gchar *xBairro;
  gchar *xMun;
  gchar *UF;

  struct _Contato *contato;
  int contatos_qnt;
}consulta_cnpj;
