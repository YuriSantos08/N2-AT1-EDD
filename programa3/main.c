#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sensores.h"

int main(int argc, char *argv[]) {
    if ((argc - 13) % 2 != 0) {
        printf("Erro nos argumentos passados: cada sensor deve vir com um tipo (ex: temp float)\n");
        return 1;
    }

    srand(time(NULL));

    int dia1 = atoi(argv[1]);
    int mes1 = atoi(argv[2]);
    int ano1 = atoi(argv[3]);
    int hora1 = atoi(argv[4]);
    int min1 = atoi(argv[5]);
    int seg1 = atoi(argv[6]);

    int dia2 = atoi(argv[7]);
    int mes2 = atoi(argv[8]);
    int ano2 = atoi(argv[9]);
    int hora2 = atoi(argv[10]);
    int min2 = atoi(argv[11]);
    int seg2 = atoi(argv[12]);

    time_t inicio = converter_para_timestamp(dia1, mes1, ano1, hora1, min1, seg1);
    time_t fim= converter_para_timestamp(dia2, mes2, ano2, hora2, min2, seg2);

    if (inicio == -1 || fim == -1) {
        return 1;
    }

    printf("Inicio: %ld\n", inicio);
    printf("Fim: %ld\n", fim);

    int num_sensores = (argc - 13) / 2;
    Sensores sensores[num_sensores];

    for (int i = 0; i < num_sensores; i++) {
        strncpy(sensores[i].nome, argv[13 + i * 2], sizeof(sensores[i].nome) - 1);
        strncpy(sensores[i].tipo, argv[13 + i * 2 + 1], sizeof(sensores[i].tipo) - 1);
    }

    struct tm t_inicio = {0}, t_fim = {0};
    t_inicio.tm_mday = dia1; 
    t_inicio.tm_mon = mes1 - 1;
    t_inicio.tm_year = ano1 - 1900;
    t_inicio.tm_hour = hora1; 
    t_inicio.tm_min = min1; 
    t_inicio.tm_sec = seg1;

    t_fim.tm_mday = dia2; 
    t_fim.tm_mon = mes2 - 1;
     t_fim.tm_year = ano2 - 1900;
    t_fim.tm_hour = hora2; 
    t_fim.tm_min = min2; 
    t_fim.tm_sec = seg2;

    FILE *arq = fopen("leituras.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!!!!");
        return 1;
    }

char valor[64];
    
for (int i = 0; i < num_sensores; i++) {
        for (int j = 0; j < 2000; j++) {
            time_t ts = gerar_timestamp_aleatorio(&t_inicio, &t_fim);
            gerar_valor_aleatorio(sensores[i].tipo, valor);
            fprintf(arq, "%ld %s %s\n", ts, sensores[i].nome, valor);
        }
    }

    fclose(arq);
    printf("Arquivo 'leituras.txt' gerado com sucesso.\r\n");

    return 0;
}
