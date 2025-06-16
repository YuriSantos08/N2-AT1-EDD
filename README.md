# Sistema de Processamento e Consulta de Leituras de Sensores

### Visão Geral

Este repositório contém três programas em C que fazem parte de um sistema para processamento e consulta de leituras de sensores em uma planta industrial inteligente:

* **Programa 1 (`programa1.c`)**: Organiza dados de um arquivo bruto, separando leituras por sensor e ordenando-as por timestamp.  
* **Programa 2 (`programa2.c`)**: Consulta a leitura de um sensor em um instante específico usando busca binária.  
* **Programa 3 (`programa3.c` e `main.c`)**: Gera um arquivo de teste com leituras aleatórias para sensores, com timestamps dentro de um intervalo definido.

---

## Estrutura de Pastas

```plaintext
├── programa1.c           # Implementação do Programa 1
├── programa2.c           # Implementação do Programa 2
├── programa3/            # Subpasta contendo arquivos do Programa 3
│   ├── main.c            # `main.c` do Programa 3 (gera arquivos de teste)
│   └── sensores.c        # Lógica de geração de timestamps e valores aleatórios
├── sensores.h            # Cabeçalho compartilhado para o Programa 3
└── README.md             # Documentação do projeto (este arquivo)
Requisitos
Compilador GCC (ou compatível).

Bibliotecas padrão do C (stdlib.h, stdio.h, string.h, time.h)

Sistema operacional compatível (Windows, Linux ou macOS)

Como Compilar e Executar
Compile cada programa individualmente usando o gcc. Exemplos:

# Programa 1 – Organização dos Dados
gcc programa1.c -o programa1
./programa1 leituras.txt

# Programa 2 – Consulta por Instante
gcc programa2.c -o programa2
./programa2 <nome_do_sensor> <dia> <mes> <ano> <hora> <min> <seg>

# Programa 3 – Geração de Arquivo de Teste
gcc programa3/main.c programa3/sensores.c -o programa3/programa3

# Exemplo de execução do Programa 3:
./programa3/programa3 01 01 2023 00 00 00 31 12 2023 23 59 59 sensor1 int sensor2 bool sensor3 float sensor4 string
Esses comandos gerarão três executáveis:

programa1

programa2

programa3

Uso
Programa 1
Processa um arquivo bruto de leituras, separa por sensor e gera arquivos ordenados (sensor1.txt, sensor2.txt, etc.).

./programa1 <arquivo_de_entrada>
<arquivo_de_entrada>: arquivo contendo linhas no formato:

<TIMESTAMP> <ID_SENSOR> <VALOR>
Saída: arquivos sensor1.txt, sensor2.txt, sensor3.txt e sensor4.txt com leituras em ordem crescente de timestamp.

Programa 2
Consulta a leitura mais próxima de um instante para um sensor específico.
./programa2 <ID_SENSOR> <dia> <mes> <ano> <hora> <min> <seg>
<ID_SENSOR>: nome do sensor (ex.: sensor1)

<dia> <mes> <ano> <hora> <min> <seg>: data e hora da consulta

Exemplo:

./programa2 sensor1 15 06 2025 14 30 00
Saída:

Leitura mais proxima do tempo informado:
<TIMESTAMP> sensor1 <VALOR>
Programa 3
Gera um arquivo de teste (leituras.txt) com leituras aleatórias para os sensores e tipos informados.

./programa3 <dia1> <mes1> <ano1> <hora1> <min1> <seg1> <dia2> <mes2> <ano2> <hora2> <min2> <seg2> <sensor1> <tipo1> [<sensor2> <tipo2> ...]
<dia1> <mes1> <ano1> <hora1> <min1> <seg1>: data e hora de início do intervalo

<dia2> <mes2> <ano2> <hora2> <min2> <seg2>: data e hora de fim do intervalo

<sensorX>: nome do sensor (string sem espaços)

<tipoX>: tipo de dado para as amostras (int, float, bool, string)

Exemplo:

./programa3 01 01 2023 00 00 00 31 12 2023 23 59 59 sensor1 int sensor2 bool sensor3 float
Saída: arquivo leituras.txt no formato:

<TIMESTAMP> <ID_SENSOR> <VALOR>

Observações e Dicas
Validação de argumentos: cada programa verifica número e formato dos argumentos, exibindo mensagens de erro em caso de uso incorreto.

Capacidade dos arrays: o Programa 1 suporta até 2000 leituras por sensor; para arquivos maiores.

Busca binária: o Programa 2 ordena as leituras antes e utiliza busca binária para eficiência.
