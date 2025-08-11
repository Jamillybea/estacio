#include <stdio.h>
#include <string.h>

int main() {
    char estado1[100], estado2[100];
    char codigo1[24], codigo2[24];
    char cidade1[27], cidade2[27];
    unsigned long int populacao1, populacao2;
    float pib1, pib2, area1, area2;
    int pontos1, pontos2;
    int jogador1 = 0, jogador2 = 0;
    float sup1, sup2;

    printf("=== CARTA 1 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado1, sizeof(estado1), stdin);
    estado1[strcspn(estado1, "\n")] = 0; 

    printf("Digite o codigo da carta:\n");
    scanf("%s", codigo1);

    printf("Digite o nome da cidade:\n");
    scanf("%s", cidade1); 

    printf("Digite a quantidade da populacao:\n");
    scanf("%f", &populacao1);

    printf("Digite o tamanho da area:\n");
    scanf("%f", &area1);

    printf("Digite o pib:\n");
    scanf("%f", &pib1);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &pontos1);

    getchar(); // remove o \n já que algumas perguntas estavam sendo puladas

    printf("\n=== CARTA 2 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado2, sizeof(estado2), stdin);
    estado2[strcspn(estado2, "\n")] = 0; 

    printf("Digite o codigo da carta:\n");
    scanf("%s", codigo2);

    printf("Digite o nome da cidade:\n");
    scanf("%s", cidade2);

    printf("Digite a quantidade da populacao:\n");
    scanf("%f", &populacao2);

    printf("Digite o tamanho da area:\n");
    scanf("%f", &area2);

    printf("Digite o pib:\n");
    scanf("%f", &pib2);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &pontos2);

    
    // COMPARAÇÕES
    if (populacao1 > populacao2) {
        jogador1++;
        printf("\nRodada (Populacao): Jogador 1 venceu! (Pontos: %d)\n", jogador1);
    } else if (populacao1 < populacao2) {
        jogador2++;
        printf("\nRodada (Populacao): Jogador 2 venceu! (Pontos: %d)\n", jogador2);
    } else {
        printf("\nRodada (Populacao): Empate!\n");
    }

    if (area1 > area2) {
        jogador1++;
        printf("Rodada (area): Jogador 1 venceu! (Pontos: %d)\n", jogador1);
    } else if (area1 < area2) {
        jogador2++;
        printf("Rodada (area): Jogador 2 venceu! (Pontos: %d)\n", jogador2);
    } else {
        printf("Rodada (area): Empate!\n");
    }

    if (pib1 > pib2) {
        jogador1++;
        printf("Rodada (PIB): Jogador 1 venceu! (Pontos: %d)\n", jogador1);
    } else if (pib1 < pib2) {
        jogador2++;
        printf("Rodada (PIB): Jogador 2 venceu! (Pontos: %d)\n", jogador2);
    } else {
        printf("Rodada (PIB): Empate!\n");
    }

    if (pontos1 > pontos2) {
        jogador1++;
        printf("Rodada (Pontos Turisticos): Jogador 1 venceu! (Pontos: %d)\n", jogador1);
    } else if (pontos1 < pontos2) {
        jogador2++;
        printf("Rodada (Pontos Turisticos): Jogador 2 venceu! (Pontos: %d)\n", jogador2);
    } else {
        printf("Rodada (Pontos Turisticos): Empate!\n");
    }

    printf("\n=== RESULTADO FINAL ===\n");
    if (jogador1 > jogador2) {
        printf("Jogador 1 venceu com %d pontos!\n", jogador1);
    } else if (jogador1 < jogador2) {
        printf("Jogador 2 venceu com %d pontos!\n", jogador2);
    } else {
        printf("Empate final! Ambos com %d pontos!\n", jogador1);
    }

    return 0;
}
