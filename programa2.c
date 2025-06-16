#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    long long timestamp;
    char sensor[50];
    char valor[50];
} Leitura;

time_t converter_para_timestamp(int dia, int mes, int ano, int hora, int min, int seg) {
    struct tm t = {0};
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    t.tm_isdst = -1;

    time_t ts = mktime(&t);
    if (ts == -1) {
        printf("Data invalida.\n");
        exit(1);
    }
    return ts;
}

int comparar_timestamp(const void *a, const void *b) {
    Leitura *la = (Leitura *)a;
    Leitura *lb = (Leitura *)b;
    if (la->timestamp < lb->timestamp) return -1;
    else if (la->timestamp > lb->timestamp) return 1;
    else return 0;
}

int busca_binaria_proxima(Leitura *leituras, int n, long long ts) {
    int inicio = 0;
    int fim = n - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (leituras[meio].timestamp == ts) {
            return meio;
        } else if (leituras[meio].timestamp < ts) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (inicio >= n) return fim;
    if (fim < 0) return inicio;

    long long diff_inicio = labs(leituras[inicio].timestamp - ts);
    long long diff_fim = labs(leituras[fim].timestamp - ts);

    if (diff_inicio < diff_fim)
        return inicio;
    else
        return fim;
}

int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("Utilize: %s <sensor> <dia> <mes> <ano> <hora> <min> <seg>\n", argv[0]);
        return 1;
    }

    char sensor[50];
    strcpy(sensor, argv[1]);

    time_t ts_consulta = converter_para_timestamp(
        atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
        atoi(argv[5]), atoi(argv[6]), atoi(argv[7])
    );

    char nome_arquivo[64];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", sensor);

    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo do sensor %s\n", sensor);
        return 1;
    }

    Leitura *leituras = NULL;
    size_t capacidade = 1000, n = 0;
    leituras = malloc(sizeof(Leitura) * capacidade);
    if (leituras == NULL) {
        printf("Erro de memoria\n");
        fclose(arq);
        return 1;
    }

    Leitura l;
    while (fscanf(arq, "%lld %s %s", &l.timestamp, l.sensor, l.valor) == 3) {
        if (strcmp(l.sensor, sensor) == 0) {
            if (n >= capacidade) {
                capacidade *= 2;
                leituras = realloc(leituras, sizeof(Leitura) * capacidade);
                if (leituras == NULL) {
                    printf("Erro de memoria\n");
                    fclose(arq);
                    return 1;
                }
            }
            leituras[n++] = l;
        }
    }
    fclose(arq);

    if (n == 0) {
        printf("Nenhuma leitura encontrada para o sensor %s informado\n", sensor);
        free(leituras);
        return 1;
    }

    qsort(leituras, n, sizeof(Leitura), comparar_timestamp);

    int idx = busca_binaria_proxima(leituras, n, ts_consulta);

    printf("Leitura mais proxima do tempo informado:\n");
    printf("%lld %s %s\n", leituras[idx].timestamp, leituras[idx].sensor, leituras[idx].valor);

    free(leituras);
    return 0;
}
