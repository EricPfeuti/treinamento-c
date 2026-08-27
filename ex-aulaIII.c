#include <stdio.h>

int cotaGeral = 500;

int imprimir() {
    int paginas;
    printf("Digite a quantidade de páginas para rotação: ");
    scanf("%d", &paginas);
    
    if (paginas <= 0 || paginas > cotaGeral) {
        printf("Falha! Quantidade inválida ou cota insuficiente!");
        return 0;
    }
    
    cotaGeral -= paginas;
    printf("Impressao realizada com sucesso!\n");
    return 1;
}

void recarregar() {
    int paginas;
    printf("Digite a quantidade de páginas para rotação: ");
    scanf("%d", &paginas);
    
    if (paginas > 0) {
        printf("Sucesso! Cota geral recarregada em %d páginas.\n", paginas);
        cotaGeral += paginas;
    } else {
        printf("Quantidade inválida!");
    }
  
}

void status() {
    printf("Status da cota geral é de %d páginas.\n", cotaGeral);
}

int main()
{
    int opcao;
    
    do {
        printf("1 - Imprimir\n");
        printf("2 - Recarregar Cota\n");
        printf("3 - Status\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                imprimir();
                break;
            case 2:
                recarregar();
                break;
            case 3:
                status();
                break;
            case 0:
                printf("Encerrando o sistema...");
                break;
            default:
                printf("Opção Inválida");
        } 
    } while(opcao != 0);
    
    return 0;
}
