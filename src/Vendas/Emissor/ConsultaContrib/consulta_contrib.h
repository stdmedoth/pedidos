int consulta_contrib_wnd(struct _terc_infos *contrib);

int consulta_contrib_consulta(gchar *cnpj, gchar *uf, struct _terc_infos *contrib);

xmlDocPtr consulta_contrib_cria_xml(gchar *cnpj, gchar *uf);


struct {
  gchar *cnpj;
  gchar *uf;
  gchar *cStat;
  gchar *xMotivo;
  gchar *xNome;
  gchar *IE;
  gchar *CEP;
  gchar *xLgr;
  gchar *nro;
  gchar *xBairro;
  gchar *xMun;
  gchar *UF;
}consulta_cnpj;
