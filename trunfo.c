#include <stdio.h>
#include <string.h> // Necessário para strcspn

int main() {
    char estado1[100], estado2[100];
    char codigo1[24], codigo2[24];
    char cidade1[27], cidade2[27];
    unsigned long int populacao1, populacao2;
    float pib1, pib2, area1, area2;
    int pontos1, pontos2;
    float pcap1, pcap2;
    float dens1, dens2;

    printf("=== CARTA 1 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado1, sizeof(estado1), stdin);
    estado1[strcspn(estado1, "\n")] = 0; 
    printf("O nome do estado e: %s \n", estado1);

    printf("Digite o codigo da carta:\n");
    scanf("%s", codigo1);
    printf("O nome da carta e: %s \n", codigo1);

    getchar();
    printf("Digite o nome da cidade:\n");
    fgets(cidade1, sizeof(cidade1), stdin);
    cidade1[strcspn(cidade1, "\n")] = 0;
    printf("O nome da cidade e: %s \n", cidade1); 

    printf("Digite a quantidade da populacao:\n");
    scanf("%lu", &populacao1);
    printf("A populacao e: %lu\n", populacao1);

    printf("Digite o tamanho da area em km:\n");
    scanf("%f", &area1);
    printf("A area e: %.2f km2\n", area1);

    printf("Digite o pib:\n");
    scanf("%f", &pib1);
    printf("O pib e: %.2f \n", pib1);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &pontos1);
    printf("Os pontos turisticos sao: %d \n", pontos1);

    dens1 = populacao1 / area1;
    printf("A densidade populacional: %.2f\n", dens1);

    pcap1 = (pib1 * 1000000) / populacao1;
    printf("O per capita e: %.2f\n", pcap1);

    printf("\n===Descricao completa===\n");

    printf("Estado: %s\n", estado1); 
    printf("Codigo carta: %d\n", codigo1);
    printf("Cidade: %s\n", cidade1);
    printf("Populacao: %lu\n", populacao1);
    printf("Area: %f\n", area1);
    printf("Pontos turisticos: %d\n", pontos1);
   

    getchar(); // limpar buffer

    printf("\n=== CARTA 2 ===\n");

    printf("Digite o nome do estado:\n");
    fgets(estado2, sizeof(estado2), stdin);
    estado2[strcspn(estado2, "\n")] = 0; 

    printf("Digite o codigo da carta:\n");
    scanf("%s", codigo2);
    printf("O codigo da carta e: %s \n", codigo2);

    getchar();
    printf("Digite o nome da cidade:\n");
    fgets(cidade2, sizeof(cidade2), stdin);
    cidade2[strcspn(cidade2, "\n")] = 0;
    printf("O nome da cidade e: %s\n", cidade2);

    printf("Digite a quantidade da populacao:\n");
    scanf("%lu", &populacao2);
    printf("A populacao e: %lu \n", populacao2);

    printf("Digite o tamanho da area:\n");
    scanf("%f", &area2);
    printf("A area em km e: %.2f \n", area2);

    printf("Digite o pib:\n");
    scanf("%f", &pib2);
    printf("O pib e: %.2f \n", pib2);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &pontos2);
    printf("Os pontos turisticos sao: %d \n", pontos2);

    dens2 = populacao2 / area2;
    printf("A densidade populacional: %.2f\n", dens2);

    pcap2 = (pib2 * 1000000) / populacao2;
    printf("O per capita e: %.2f\n", pcap2);

    return 0;
}
