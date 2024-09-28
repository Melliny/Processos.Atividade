#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "processos.h"

struct tm parseData(const char *dataStr) {
    struct tm data = {0};
    sscanf(dataStr, "%4d-%2d-%2d", &data.tm_year, &data.tm_mon, &data.tm_mday);
    data.tm_year -= 1900;
    data.tm_mon -= 1;  
    return data;
}

int lerArquivo(const char *nomeArquivo, RegistroProcesso *listaProcessos, int limiteProcessos) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao tentar abrir o arquivo.\n");
        return -1;
    }

    char linha[256];
    int contador = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) && contador < limiteProcessos) {
        sscanf(linha, "%lld,\"%[^\"]\",\"%[^\"]\",%d,%d,%d",
               &listaProcessos[contador].codigo,
               listaProcessos[contador].numProcesso,
               listaProcessos[contador].dataInicio,
               &listaProcessos[contador].classeProcesso,
               &listaProcessos[contador].assuntoProcesso,
               &listaProcessos[contador].anoEleitoral);
        contador++;
    }

    fclose(arquivo);
    return contador;
}

int compararCodigo(const void *a, const void *b) {
    const RegistroProcesso *proc1 = (const RegistroProcesso *)a;
    const RegistroProcesso *proc2 = (const RegistroProcesso *)b;
    return (proc1->codigo > proc2->codigo) - (proc1->codigo < proc2->codigo);
}

void ordenarPorCodigo(RegistroProcesso *listaProcessos, int qtdProcessos) {
    qsort(listaProcessos, qtdProcessos, sizeof(RegistroProcesso), compararCodigo);
}

int compararDataInicial(const void *a, const void *b) {
    const RegistroProcesso *proc1 = (const RegistroProcesso *)a;
    const RegistroProcesso *proc2 = (const RegistroProcesso *)b;
    struct tm data1 = parseData(proc1->dataInicio);
    struct tm data2 = parseData(proc2->dataInicio);
    return difftime(mktime(&data2), mktime(&data1));
}

void ordenarPorDataInicial(RegistroProcesso *listaProcessos, int qtdProcessos) {
    qsort(listaProcessos, qtdProcessos, sizeof(RegistroProcesso), compararDataInicial);
}

int contarPorClasse(RegistroProcesso *listaProcessos, int qtdProcessos, int classeProcesso) {
    int contador = 0;
    for (int i = 0; i < qtdProcessos; i++) {
        if (listaProcessos[i].classeProcesso == classeProcesso) {
            contador++;
        }
    }
    return contador;
}

int contarAssuntosDiferentes(RegistroProcesso *listaProcessos, int qtdProcessos) {
    int assuntosDiferentes[LIMITE_PROCESSOS] = {0};
    int contagem = 0;
    for (int i = 0; i < qtdProcessos; i++) {
        int encontrado = 0;
        for (int j = 0; j < contagem; j++) {
            if (assuntosDiferentes[j] == listaProcessos[i].assuntoProcesso) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            assuntosDiferentes[contagem++] = listaProcessos[i].assuntoProcesso;
        }
    }
    return contagem;
}

int calcularTempoTramitacao(RegistroProcesso *proc) {
    struct tm dataInicial = parseData(proc->dataInicio);
    time_t dataInicioTime = mktime(&dataInicial);
    time_t dataAtual = time(NULL);
    return (int)(difftime(dataAtual, dataInicioTime) / (60 * 60 * 24));
}
