#ifndef SENSORES_H
#define SENSORES_H
#include <time.h>

typedef struct sensores_t {
    char nome[32];
    char tipo[16];
} Sensores;

time_t gerar_timestamp_aleatorio(struct tm *inicial, struct tm *final);
time_t converter_para_timestamp(int dia, int mes, int ano, int hora, int min, int seg);
void gerar_valor_aleatorio(const char *tipo, char *saida);

#endif
