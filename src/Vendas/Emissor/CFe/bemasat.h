#ifdef WIN32

typedef int (__cdecl* Bematech_SAT_AtivarSAT) (int numeroSessao, int subComando, const char *codigoDeAtivacao, const char *CNPJ, int cUF );

typedef int (__cdecl* Bematech_SAT_ComunicarCertificadoICPBRASIL) (int numeroSessao,const char *codigoDeAtivacao, const char *certificado);

typedef int (__cdecl* Bematech_SAT_EnviarDadosVenda) (int numeroSessao, const char *codigoDeAtivacao, const char *dadosVenda);

typedef int (__cdecl* Bematech_SAT_CancelarUltimaVenda) (int numeroSessao, const char *codigoDeAtivacao, const char *chave,const char *dadosCancelamento);

typedef int (__cdecl* Bematech_SAT_ConsultarSAT) ( int numeroSessao );

typedef int (__cdecl* Bematech_SAT_TesteFimAFim) (int numeroSessao, const char *codigoDeAtivacao, const char *dadosVenda);

typedef int (__cdecl* Bematech_SAT_ConsultarStatusOperacional) (int numeroSessao, const char *codigoDeAtivacao);

typedef int (__cdecl* Bematech_SAT_ConsultarNumeroSessao) (int numeroSessao, const char *codigoDeAtivacao, int cNumeroDeSessao);

typedef int (__cdecl* Bematech_SAT_ConfigurarInterfaceDeRede) (int numeroSessao, const char *codigoDeAtivacao, const char *dadosConfiguracao);

typedef int (__cdecl* Bematech_SAT_AssociarAssinatura) (const char* numeroSessao, const char* cnpjValue, const char* assinaturaCNPJs);

typedef int (__cdecl* Bematech_SAT_AtualizarSoftwareSAT) (const char* numeroSessao, const char* codigoDeAtivacao);

typedef int (__cdecl* Bematech_SAT_ExtrairLogs) (const char* numeroSessao, const char* codigoDeAtivacao);

typedef int (__cdecl* Bematech_SAT_BloquearSAT) (const char* numeroSessao, const char* codigoDeAtivacao);

typedef int (__cdecl* Bematech_SAT_DesbloquearSAT) (const char* numeroSessao, const char* codigoDeAtivacao);

typedef int (__cdecl* Bematech_SAT_TrocarCodigoDeAtivacao) (int numeroSessao, const char *codigoDeAtivacao, int opcao, const char *novoCodigo, const char *confNovoCodigo);

#endif
