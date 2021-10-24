#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"

int main()
{
    MatrizEsparsa *esparsa;
    int i, j, numLinhas, numColunas;
    int **matrix;

    printf("Numero de linhas: ");
    scanf("%d", &numLinhas);

    printf("Numero de colunas: ");
    scanf("%d", &numColunas);

    matrix = criar_matriz_bidimensional(numLinhas, numColunas);

    for(i=0; i<numLinhas; i++){
        for(j=0; j<numColunas; j++){
            printf("Linha[%d] Coluna[%d] -> ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    esparsa = converter_bidimensonal_para_esparsa(matrix, numLinhas, numColunas);

    imprimir_esparsa_teste(esparsa);

    inserir_remover_trocar_item_na_matriz(0, 0, 1, esparsa);

    imprimir_esparsa_teste(esparsa);

    liberar_matriz_esparsa(esparsa);

    return 0;
}
