#include <stdio.h>

void calcular_autonomia(float combustivel[], float eficiencia[], float autonomia[], int n){
    
    for (int i = 0; i < n; i++){
        autonomia[i] = combustivel[i] * eficiencia[i];
    }
    
}

void relatorio_frota(int ids[], float combustivel[], float eficiencia[], float autonomia[], int n, float distancia_alvo){
    
    calcular_autonomia(combustivel, eficiencia, autonomia, n);
    
    printf("\nRELATÓRIO\n");
    for(int i = 0; i < n; i++){
        if (autonomia[i] >= distancia_alvo) {
            printf("Veiculo %d - Autonomia: %.2f km - STATUS: AUTORIZADO\n", ids[i], autonomia[i]);
        } else {
            printf("Veiculo %d - Autonomia: %.2f km - STATUS: REJEITADO\n", ids[i], autonomia[i]);
        }
    }
    
}

int main()
{
    int ids[20] = {10, 20, 30, 40};
    float combustivel[20] = {1200, 900, 1000, 550};
    float eficiencia[20] = {2.80, 4.00, 1.90, 5.20};
    float autonomia[20];
    
    int n;
    int limite = 4;
    int total = 20;
    float distancia_alvo;
    int i;
    
    printf("Digite a quantidade de novos caminhões a serem inseridos: ");
    scanf("%d", &n);
    
    if (n < 0 || limite + n > total) {
        printf("Falha na operação: limite de %d posições excedido.\n", total);
        return 0;
    }
    
    for (i = limite; i < limite + n; i++) {
        printf("\nNOVO CAMINHÃO %d \n", i + 1);
        
        printf("Digite o ID: ");
        scanf("%d", &ids[i]);
        
        printf("Digite o Nível de Combustível (litros): ");
        scanf("%f", &combustivel[i]);
        
        printf("Digite a Eficiência (km/L): ");
        scanf("%f", &eficiencia[i]);
    }
    
    limite += n;
    
    printf("\nDigite distância do trajeto alvo (km): ");
    scanf("%f", &distancia_alvo);
    
    relatorio_frota(ids, combustivel, eficiencia, autonomia, limite, distancia_alvo);

    return 0;
    
}
