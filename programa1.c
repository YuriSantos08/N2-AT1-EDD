#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long timestamp;
    char id_sensor[50];
    char valor[50];
} Leitura;

int sensor_existente(const char *nome) {
    return (
        strcmp(nome, "sensor1") == 0 ||
        strcmp(nome, "sensor2") == 0 ||
        strcmp(nome, "sensor3") == 0 ||
        strcmp(nome, "sensor4") == 0
    );
}

FILE *abrir_arquivo_sensor(const char *sensor) {
    char nome_arquivo[64];
    sprintf(nome_arquivo, "%s.txt", sensor);
    FILE *final = fopen(nome_arquivo, "w"); 
    if (final == NULL) {
        printf("Erro ao abrir arquivo para sensor: %s\n", sensor);
        exit(1);
    }
    return final;
}

int comparacao_timestamp(const void *a, const void *b) {
    Leitura *l1 = (Leitura *)a;
    Leitura *l2 = (Leitura *)b;
    if (l1->timestamp < l2->timestamp) return -1;
    else if (l1->timestamp > l2->timestamp) return 1;
    else return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Utilize: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    FILE *arq = fopen(argv[1], "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo para leitura.\n");
        return 1;
    }

    Leitura sensor1_leituras[2000], sensor2_leituras[2000];
    Leitura sensor3_leituras[2000], sensor4_leituras[2000];
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

    char linha[256];

    while (fgets(linha, sizeof(linha), arq)) {
        Leitura l;
        int campos = sscanf(linha, "%lld %s %s", &l.timestamp, l.id_sensor, l.valor);
        if (campos != 3) {
            printf("Linha mal formatada: %s", linha);
            continue;
        }

        if (!sensor_existente(l.id_sensor)) {
            printf("Sensor desconhecido: %s\n", l.id_sensor);
            continue;
        }

        if (strcmp(l.id_sensor, "sensor1") == 0) {
            if (count1 < 2000)
                sensor1_leituras[count1++] = l;
            else
                printf("Limite do sensor1 alcançado!\n");
        }
        else if (strcmp(l.id_sensor, "sensor2") == 0) {
            if (count2 < 2000)
                sensor2_leituras[count2++] = l;
            else
                printf("Limite do sensor2 alcançado!\n");
        }
        else if (strcmp(l.id_sensor, "sensor3") == 0) {
            if (count3 < 2000)
                sensor3_leituras[count3++] = l;
            else
                printf("Limite do sensor3 alcançado!\n");
        }
        else if (strcmp(l.id_sensor, "sensor4") == 0) {
            if (count4 < 2000)
                sensor4_leituras[count4++] = l;
            else
                printf("Limite do sensor4 alcançado!\n");
        }
    }
    fclose(arq);

    qsort(sensor1_leituras, count1, sizeof(Leitura), comparacao_timestamp);
    qsort(sensor2_leituras, count2, sizeof(Leitura), comparacao_timestamp);
    qsort(sensor3_leituras, count3, sizeof(Leitura), comparacao_timestamp);
    qsort(sensor4_leituras, count4, sizeof(Leitura), comparacao_timestamp);

    FILE *arq_sensor1 = abrir_arquivo_sensor("sensor1");
    for (int i = 0; i < count1; i++)
        fprintf(arq_sensor1, "%lld %s %s\n", sensor1_leituras[i].timestamp, sensor1_leituras[i].id_sensor, sensor1_leituras[i].valor);
    fclose(arq_sensor1);

    FILE *arq_sensor2 = abrir_arquivo_sensor("sensor2");
    for (int i = 0; i < count2; i++)
        fprintf(arq_sensor2, "%lld %s %s\n", sensor2_leituras[i].timestamp, sensor2_leituras[i].id_sensor, sensor2_leituras[i].valor);
    fclose(arq_sensor2);

    FILE *arq_sensor3 = abrir_arquivo_sensor("sensor3");
    for (int i = 0; i < count3; i++)
        fprintf(arq_sensor3, "%lld %s %s\n", sensor3_leituras[i].timestamp, sensor3_leituras[i].id_sensor, sensor3_leituras[i].valor);
    fclose(arq_sensor3);

    FILE *arq_sensor4 = abrir_arquivo_sensor("sensor4");
    for (int i = 0; i < count4; i++)
        fprintf(arq_sensor4, "%lld %s %s\n", sensor4_leituras[i].timestamp, sensor4_leituras[i].id_sensor, sensor4_leituras[i].valor);
    fclose(arq_sensor4);

    printf("Leituras foram separadas e ordenadas com sucesso.\n");
    return 0;
}
