#include <stdio.h>
#include "processos.h"

int main() {
    Processo processos[MAX_PROCESSOS];
    int num_processos = ler_dados("processo_043_202409032338.txt", processos, MAX_PROCESSOS);

    if (num_processos == -1) {
        return 1;
    }

    ordenar_por_id(processos, num_processos);
    printf("Processos ordenados por ID:\n");
    for (int i = 0; i < num_processos; i++) {
        printf("%lld, %s, %s, %d, %d, %d\n", 
               processos[i].id, processos[i].numero, 
               processos[i].data_ajuizamento, 
               processos[i].id_classe, 
               processos[i].id_assunto, 
               processos[i].ano_eleicao);
    }

    ordenar_por_data(processos, num_processos);
    printf("\nProcessos ordenados por data de ajuizamento (decrescente):\n");
    for (int i = 0; i < num_processos; i++) {
        printf("%lld, %s, %s, %d, %d, %d\n", 
               processos[i].id, processos[i].numero, 
               processos[i].data_ajuizamento, 
               processos[i].id_classe, 
               processos[i].id_assunto, 
               processos[i].ano_eleicao);
    }

    int id_classe_exemplo = 12554;
    int count_classe = contar_por_id_classe(processos, num_processos, id_classe_exemplo);
    printf("\nNúmero de processos com id_classe %d: %d\n", id_classe_exemplo, count_classe);

    int num_assuntos = contar_assuntos_distintos(processos, num_processos);
    printf("Número de assuntos distintos: %d\n", num_assuntos);

    if (num_processos > 0) {
        int dias_tramitacao = calcular_dias_tramitacao(&processos[0]);
        printf("Dias em tramitação para o primeiro processo: %d\n", dias_tramitacao);
    }

    escrever_csv("processos_ordenados.csv", processos, num_processos, "ordem_id");
    return 0;
}
