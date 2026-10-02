#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_AMOSTRAS 100


/* 1 - Carrega 50 registros aleatorios */
void carregarDados(float velocidades[][2],
                   float sensores_frontais[][3],
                   float sensores_laterais[][2],
                   float processamento[][2],
                   int status[][3])
{
    int i;

    for (i = 0; i < 50; i++) {

        velocidades[i][0] = 40 + rand() % 81;
        velocidades[i][1] = 40 + rand() % 81;

        sensores_frontais[i][0] = 10 + rand() % 91;
        sensores_frontais[i][1] = 10 + rand() % 91;
        sensores_frontais[i][2] = 10 + rand() % 91;

        sensores_laterais[i][0] = 0.1 + (rand() % 141) / 100.0;
        sensores_laterais[i][1] = 0.1 + (rand() % 141) / 100.0;

        processamento[i][0] = 0;
        processamento[i][1] = 0;

        status[i][0] = 0;
        status[i][1] = 0;
        status[i][2] = 0;
    }
}


/* 2 - Calcula a mediana dos tres sensores */
void fazerMediana(float sensores[][3],
                  float processamento[][2],
                  int quantidade)
{
    int i;
    float a, b, c;

    for (i = 0; i < quantidade; i++) {

        a = sensores[i][0];
        b = sensores[i][1];
        c = sensores[i][2];

        if ((a >= b && a <= c) || (a >= c && a <= b))
            processamento[i][0] = a;

        else if ((b >= a && b <= c) || (b >= c && b <= a))
            processamento[i][0] = b;

        else
            processamento[i][0] = c;
    }
}


/* 3 - Calcula a distancia segura */
void calcularDistancia(float velocidades[][2],
                       float processamento[][2],
                       float atrito,
                       int sensibilidade,
                       int quantidade)
{
    int i;
    float tempo;
    float velocidade;

    if (sensibilidade == 1)
        tempo = 1.0;
    else if (sensibilidade == 2)
        tempo = 1.5;
    else
        tempo = 2.0;

    for (i = 0; i < quantidade; i++) {

        velocidade = velocidades[i][0] / 3.6;

        processamento[i][1] =
            (velocidade * tempo) +
            (velocidade * velocidade) /
            (2 * atrito * 9.81);
    }
}


/* 4 - Analisa o risco frontal */
void analisarRisco(float velocidades[][2],
                   float processamento[][2],
                   int status[][3],
                   int quantidade)
{
    int i;
    float velocidade_relativa;

    for (i = 0; i < quantidade; i++) {

        velocidade_relativa =
            velocidades[i][0] - velocidades[i][1];

        if (velocidade_relativa <= 0) {
            status[i][0] = 0;
        }
        else if (processamento[i][0] >= processamento[i][1]) {
            status[i][0] = 0;
        }
        else if (processamento[i][0] >=
                 processamento[i][1] * 0.5) {
            status[i][0] = 1;
        }
        else {
            status[i][0] = 2;
        }
    }
}


/* 5 - Analisa as duas faixas */
void analisarFaixas(float velocidades[][2],
                    float sensores_laterais[][2],
                    int status[][3],
                    int quantidade)
{
    int i;
    float margem;

    for (i = 0; i < quantidade; i++) {

        margem = 0.50;

        if (velocidades[i][0] > 80)
            margem +=
                (velocidades[i][0] - 80) * 0.01;


        /* Faixa esquerda */
        if (sensores_laterais[i][0] < margem)
            status[i][1] = 2;

        else if (sensores_laterais[i][0] < margem + 0.20)
            status[i][1] = 1;

        else
            status[i][1] = 0;


        /* Faixa direita */
        if (sensores_laterais[i][1] < margem)
            status[i][2] = 2;

        else if (sensores_laterais[i][1] < margem + 0.20)
            status[i][2] = 1;

        else
            status[i][2] = 0;
    }
}


/* 6 - Relatorio
   Esta e a unica funcao que usa printf */
void relatorio(float velocidades[][2],
               float sensores_frontais[][3],
               float sensores_laterais[][2],
               float processamento[][2],
               int status[][3],
               int quantidade)
{
    int i;
    int maior_status;

    for (i = 0; i < quantidade; i++) {

        printf("\n========================================\n");
        printf("           AMOSTRA %d\n", i + 1);
        printf("========================================\n");

        printf("\nDADOS DE ENTRADA\n");

        printf("Velocidade atual: %.2f km/h\n",
               velocidades[i][0]);

        printf("Velocidade frente: %.2f km/h\n",
               velocidades[i][1]);

        printf("Radar: %.2f m\n",
               sensores_frontais[i][0]);

        printf("Lidar: %.2f m\n",
               sensores_frontais[i][1]);

        printf("Camera: %.2f m\n",
               sensores_frontais[i][2]);

        printf("Faixa esquerda: %.2f m\n",
               sensores_laterais[i][0]);

        printf("Faixa direita: %.2f m\n",
               sensores_laterais[i][1]);


        printf("\nDADOS PROCESSADOS\n");

        printf("Distancia validada: %.2f m\n",
               processamento[i][0]);

        printf("Distancia segura: %.2f m\n",
               processamento[i][1]);


        printf("\nSTATUS FRONTAL: ");

        if (status[i][0] == 0)
            printf("SEGURO\n");

        else if (status[i][0] == 1)
            printf("ATENCAO\n");

        else
            printf("RISCO DE COLISAO (AEB ACIONADO)\n");


        printf("FAIXA ESQUERDA: ");

        if (status[i][1] == 0)
            printf("NORMAL\n");

        else if (status[i][1] == 1)
            printf("ATENCAO\n");

        else
            printf("PERIGO DE INVASAO\n");


        printf("FAIXA DIREITA: ");

        if (status[i][2] == 0)
            printf("NORMAL\n");

        else if (status[i][2] == 1)
            printf("ATENCAO\n");

        else
            printf("PERIGO DE INVASAO\n");


        /* Verifica o maior nivel de risco */
        maior_status = status[i][0];

        if (status[i][1] > maior_status)
            maior_status = status[i][1];

        if (status[i][2] > maior_status)
            maior_status = status[i][2];


        printf("\n");

        if (maior_status == 2)
            printf("STATUS GERAL: INTERVENCAO CRITICA EXIGIDA\n");

        else if (maior_status == 1)
            printf("STATUS GERAL: ATENCAO\n");

        else
            printf("STATUS GERAL: NORMAL\n");
    }
}


/* PROGRAMA PRINCIPAL */
int main()
{
    float velocidades[MAX_AMOSTRAS][2];
    float sensores_frontais[MAX_AMOSTRAS][3];
    float sensores_laterais[MAX_AMOSTRAS][2];
    float processamento[MAX_AMOSTRAS][2];
    int status[MAX_AMOSTRAS][3];

    float atrito;

    int sensibilidade;
    int opcao;
    int quantidade = 0;

    srand(time(NULL));


    /* Configuracao inicial */
    puts("Digite o atrito da via:");
    scanf("%f", &atrito);

    do {
        puts("\nSensibilidade do ADAS:");
        puts("1 - Esportivo");
        puts("2 - Normal");
        puts("3 - Seguro");

        scanf("%d", &sensibilidade);

    } while (sensibilidade < 1 || sensibilidade > 3);


    /* Menu */
    do {

        puts("\n================================");
        puts("          SAFEDRIVE");
        puts("================================");
        puts("1 - Carregar dados iniciais");
        puts("2 - Inserir nova amostra");
        puts("3 - Processar e exibir relatorio");
        puts("4 - Sair");
        puts("================================");

        scanf("%d", &opcao);


        /* OPCAO 1 */
        if (opcao == 1) {

            carregarDados(
                velocidades,
                sensores_frontais,
                sensores_laterais,
                processamento,
                status
            );

            quantidade = 50;

            puts("50 registros carregados.");
        }


        /* OPCAO 2 */
        else if (opcao == 2) {

            if (quantidade >= MAX_AMOSTRAS) {

                puts("Limite de 100 amostras atingido.");

            }
            else {

                puts("\nVelocidade atual:");
                scanf("%f", &velocidades[quantidade][0]);

                puts("Velocidade do veiculo a frente:");
                scanf("%f", &velocidades[quantidade][1]);

                puts("Radar:");
                scanf("%f", &sensores_frontais[quantidade][0]);

                puts("Lidar:");
                scanf("%f", &sensores_frontais[quantidade][1]);

                puts("Camera:");
                scanf("%f", &sensores_frontais[quantidade][2]);

                puts("Distancia da faixa esquerda:");
                scanf("%f", &sensores_laterais[quantidade][0]);

                puts("Distancia da faixa direita:");
                scanf("%f", &sensores_laterais[quantidade][1]);


                processamento[quantidade][0] = 0;
                processamento[quantidade][1] = 0;

                status[quantidade][0] = 0;
                status[quantidade][1] = 0;
                status[quantidade][2] = 0;

                quantidade++;

                puts("Amostra inserida.");
            }
        }


        /* OPCAO 3 */
        else if (opcao == 3) {

            if (quantidade == 0) {

                puts("Nenhuma amostra cadastrada.");

            }
            else {

                /* 1 - Mediana */
                fazerMediana(
                    sensores_frontais,
                    processamento,
                    quantidade
                );

                /* 2 - Distancia segura */
                calcularDistancia(
                    velocidades,
                    processamento,
                    atrito,
                    sensibilidade,
                    quantidade
                );

                /* 3 - Risco frontal */
                analisarRisco(
                    velocidades,
                    processamento,
                    status,
                    quantidade
                );

                /* 4 - Faixas */
                analisarFaixas(
                    velocidades,
                    sensores_laterais,
                    status,
                    quantidade
                );

                /* 5 - Relatorio */
                relatorio(
                    velocidades,
                    sensores_frontais,
                    sensores_laterais,
                    processamento,
                    status,
                    quantidade
                );
            }
        }


        /* OPCAO 4 */
        else if (opcao == 4) {

            puts("Programa encerrado.");
        }

        else {

            puts("Opcao invalida.");
        }

    } while (opcao != 4);


    return 0;
}
