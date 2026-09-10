#include <stdio.h>

void calcular_estatisticas(float precos[], float dividendos[], int n){
    
    float maior = 0;
    float menor = 0;
    float soma = 0;
    int validos = 0;
    
    for (int i = 0; i < n; i++) {
        
        if (precos[i] <= 0 || dividendos[i] <= 0){
            continue;
        }
        
        float yield = (dividendos[i] / precos[i]) * 100;
        
        if (validos == 0) {
            maior = yield;
            menor = yield;
        } else {
            if (yield > maior) {
                maior = yield;
            }
            
            if (yield < menor) {
                menor = yield;
            }
        }
        
        soma = soma + yield;
        validos++;
        
        printf("\n--- ESTATISTICAS DA CARTEIRA ---\n");
        
        if (validos > 0){
            float media = soma / validos;
            printf("Dividend Yield Medio: %.2f%%\n", media);
            printf("Maior Yield: %.2f%% | Menor Yield: %.2f%%\n", maior, menor);
        } else {
    
            printf("Nenhum FII valido cadastrado.\n");
        }
        
    }
    
}

void calcular_bola_de_neve(int ids[], float precos[], float dividendos[], int n){
    
    printf("\n--- EFEITO BOLA DE NEVE ---\n");
    
    for (int i = 0; i < n; i++) {
        
        if (precos[i] <= 0 || dividendos[i] <= 0) {
            continue;
        }
        
        int quantidade = (int)(precos[i] / dividendos[i]);
        
        if (precos[i] / dividendos[i] > quantidade){
            quantidade++;
        }
        
        printf("FII %d: %d cotas necessarias.\n", ids[i], quantidade);
        
    }
    
}

void aplicar_desconto(float precos[], int n, float percentual) {
    for (int i = 0; i < n; i++) {

        if (precos[i] > 0) {
            precos[i] = precos[i] * (1 - percentual / 100);
        }
    }
}

int main(){
    
    int ids[50] = {101, 102, 103, 104, 105};
    float precos[50] = {100.00, 90.00, 120.00, 110.00, 80.00};
    float dividendos[50] = {1.00, 0.90, 1.20, 1.10, 0.80};
    int n;
    int total = 5;
    
    printf("Digite a quantidade de novos FIIs: ");
    scanf("%d", &n);
    
    if (n < 0 || total + n > 50) {
        printf("Quantidade Inválida!");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do FII %d ---\n", i + 1);
        
        printf("Digite o ID: ");
        scanf("%d", &ids[total]);
        
        printf("Digite o preço da cota: ");
        scanf("%d", &precos[total]);
     
        printf("Digite o dividendo mensal: ");
        scanf("%d", &dividendos[total]);
        
        total++;
        
    }
    
    calcular_estatisticas(precos, dividendos, total);
    calcular_bola_de_neve(ids, precos, dividendos, total);
    
    printf("\nAplicando estresse de mercado (-10%% nos precos)\n");
    aplicar_desconto(precos, total, 10);
    
    calcular_bola_de_neve(ids, precos, dividendos, total);
    
    return 0;
    
}
