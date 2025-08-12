#include <stdio.h>
#include <string.h>

int main() {
    char estado1[100], estado2[100];
    char codigo1[24], codigo2[24];
    char cidade1[27], cidade2[27];
    unsigned long int populacao1, populacao2;
    float pib1, pib2, area1, area2;
    int pontos1, pontos2;

    // ===== CARTA 1 =====
    printf("=== CARTA 1 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado1, sizeof(estado1), stdin);
    estado1[strcspn(estado1, "\n")] = 0;

    printf("Digite o codigo da carta:\n");
    scanf("%23s", codigo1);
    getchar();

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
    getchar();

    // ===== CARTA 2 =====
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

    // ===== CÁLCULOS =====
    float densidade1 = populacao1 / area1;
    float densidade2 = populacao2 / area2;

    float pibPerCapita1 = pib1 / populacao1;
    float pibPerCapita2 = pib2 / populacao2;

    float superPoder1 = populacao1 + area1 + pib1 + pontos1 + pibPerCapita1 + (1 / densidade1);
    float superPoder2 = populacao2 + area2 + pib2 + pontos2 + pibPerCapita2 + (1 / densidade2);

    // ===== DESCRIÇÃO =====
    printf("\n=== Descricao carta 1 ===\n");
    printf("Estado: %s\n", estado1);
    printf("Codigo carta: %s\n", codigo1);
    printf("Cidade: %s\n", cidade1);
    printf("Populacao: %lu\n", populacao1);
    printf("Area: %.2f km2\n", area1);
    printf("PIB: %.2f\n", pib1);
    printf("Pontos turisticos: %d\n", pontos1);
    printf("Densidade Populacional: %.2f\n", densidade1);
    printf("PIB per Capita: %.2f\n", pibPerCapita1);
    printf("Super Poder: %.2f\n", superPoder1);

    printf("\n=== Descricao carta 2 ===\n");
    printf("Estado: %s\n", estado2);
    printf("Codigo carta: %s\n", codigo2);
    printf("Cidade: %s\n", cidade2);
    printf("Populacao: %lu\n", populacao2);
    printf("Area: %.2f km2\n", area2);
    printf("PIB: %.2f\n", pib2);
    printf("Pontos turisticos: %d\n", pontos2);
    printf("Densidade Populacional: %.2f\n", densidade2);
    printf("PIB per Capita: %.2f\n", pibPerCapita2);
    printf("Super Poder: %.2f\n", superPoder2);

    // ===== COMPARAÇÃO =====
    printf("\n=== Comparacao ===\n");
    printf("Populacao: %d\n", populacao1 > populacao2);
    printf("Area: %d\n", area1 > area2);
    printf("PIB: %d\n", pib1 > pib2);
    printf("Pontos turisticos: %d\n", pontos1 > pontos2);
    printf("Densidade Populacional: %d\n", densidade1 < densidade2); // menor vence
    printf("PIB per Capita: %d\n", pibPerCapita1 > pibPerCapita2);
    printf("Super Poder: %d\n", superPoder1 > superPoder2);

    return 0;
}
