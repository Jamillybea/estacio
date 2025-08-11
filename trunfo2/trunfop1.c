#include <stdio.h>
#include <string.h>

int main() {
    char estado1[100], estado2[100];
    char codigo1[24], codigo2[24];
    char cidade1[27], cidade2[27];
    unsigned long int populacao1, populacao2;
    float pib1, pib2, area1, area2;
    int pontos1, pontos2;

    printf("=== CARTA 1 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado1, sizeof(estado1), stdin);
    estado1[strcspn(estado1, "\n")] = 0;

    printf("Digite o codigo da carta:\n");
    scanf("%23s", codigo1);
    getchar(); // limpa o \n do buffer

    printf("Digite o nome da cidade:\n");
    fgets(cidade1, sizeof(cidade1), stdin);
    cidade1[strcspn(cidade1, "\n")] = 0;

    printf("Digite a quantidade da populacao:\n");
    scanf("%lu", &populacao1);

    printf("Digite o tamanho da area em km:\n");
    scanf("%f", &area1);

    printf("Digite o PIB:\n");
    scanf("%f", &pib1);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &pontos1);
    getchar(); // limpa o \n antes de usar fgets de novo

    printf("\n=== Descricao carta 1 ===\n");
    printf("Estado: %s\n", estado1);
    printf("Codigo carta: %s\n", codigo1);
    printf("Cidade: %s\n", cidade1);
    printf("Populacao: %lu\n", populacao1);
    printf("Area: %.2f km2\n", area1);
    printf("PIB: %.2f\n", pib1);
    printf("Pontos turisticos: %d\n", pontos1);

    printf("\n=== CARTA 2 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado2, sizeof(estado2), stdin);
    estado2[strcspn(estado2, "\n")] = 0;

    printf("Digite o codigo da carta:\n");
    scanf("%23s", codigo2);
    getchar();

    printf("Digite o nome da cidade:\n");
    fgets(cidade2, sizeof(cidade2), stdin);
    cidade2[strcspn(cidade2, "\n")] = 0;

    printf("Digite a quantidade da populacao:\n");
    scanf("%lu", &populacao2);

    printf("Digite o tamanho da area em km:\n");
    scanf("%f", &area2);

    printf("Digite o PIB:\n");
    scanf("%f", &pib2);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &pontos2);

    printf("\n=== Descricao carta 2 ===\n");
    printf("Estado: %s\n", estado2);
    printf("Codigo carta: %s\n", codigo2);
    printf("Cidade: %s\n", cidade2);
    printf("Populacao: %lu\n", populacao2);
    printf("Area: %.2f km2\n", area2);
    printf("PIB: %.2f\n", pib2);
    printf("Pontos turisticos: %d\n", pontos2);

    return 0;
}
