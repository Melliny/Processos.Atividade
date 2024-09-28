#ifndef PROCESSOS_H
#define PROCESSOS_H

#define LIMITE_PROCESSOS 20000

typedef struct {
    long long codigo;
    char numProcesso[25];
    char dataInicio[25];
    int classeProcesso;
    int assuntoProcesso;
    int anoEleitoral;
} RegistroProcesso;

int lerArquivo(const char *nomeArquivo, RegistroProcesso *listaProcessos, int limiteProcessos);
void ordenarPorCodigo(RegistroProcesso *listaProcessos, int qtdProcessos);
void ordenarPorDataInicial(RegistroProcesso *listaProcessos, int qtdProcessos);
int contarPorClasse(RegistroProcesso *listaProcessos, int qtdProcessos, int classeProcesso);
int contarAssuntosDiferentes(RegistroProcesso *listaProcessos, int qtdProcessos);
int calcularTempoTramitacao(RegistroProcesso *proc);

#endif
