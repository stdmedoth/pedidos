int pesquisar_cad_sefaz(char *cnpj, char *uf);

void janela_cad_ter_consulta();

char  *format_cnpj_num(char *cnpj);

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

enum TER_ORIG{
  TER_DENTRO_ESTADO,
  TER_FORA_ESTADO,
  TER_FORA_PAIS,
};
