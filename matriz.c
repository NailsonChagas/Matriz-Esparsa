#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"

//Declaração de celula
struct celula{
    int valor;
    int CoordenadaLinha, CoordenadaColuna;
    Cell *next;
    Cell *down;
};

//Declaração de lista encadeada
struct lista{
    Cell *head;
};

//Declaração da matriz
struct matriz{
    int quantidadeDeLinhas;
    int quantidadeDeColunas;
    ListaEncadeada **linhas;
    ListaEncadeada **colunas;
};

//Alocar matriz esparsa
MatrizEsparsa* criar_matriz_esparsa(unsigned int numeroLinhas, unsigned int numeroColunas){
    MatrizEsparsa *a;
    int i;

    a = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));

    a->quantidadeDeLinhas = numeroLinhas;
    a->quantidadeDeColunas = numeroColunas;

    a->linhas = (ListaEncadeada**)malloc(sizeof(ListaEncadeada*) * numeroLinhas);
    a->colunas = (ListaEncadeada**)malloc(sizeof(ListaEncadeada*) * numeroColunas);

    if(numeroColunas == numeroLinhas){
        for(i=0; i<numeroLinhas; i++){
            a->linhas[i] = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
            a->linhas[i]->head = NULL;

            a->colunas[i] = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
            a->colunas[i]->head = NULL;
        }
    }
    else{
        for(i=0; i<numeroLinhas; i++){
            a->linhas[i] = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
            a->linhas[i]->head = NULL;
        }

        for(i=0; i<numeroColunas; i++){
            a->colunas[i] = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
            a->colunas[i]->head = NULL;
        }
    }
    return a;
}

//Alocar um celula
static Cell* criar_nova_celula(int item, int linha, int coluna){
    Cell *a = NULL;

    if(item != 0){
        a = (Cell*)malloc(sizeof(Cell));

        a->CoordenadaColuna = coluna;
        a->CoordenadaLinha = linha;
        a->valor = item;

        a->next = NULL;
        a->down = NULL;
    }
    return a;
}

//Verificar se a posição possui uma celula
static int validar_posicao_matriz_esparsa(int linha, int coluna, MatrizEsparsa* a){
    if((a != NULL) && (linha >= 0) && (coluna >= 0) && (linha < a->quantidadeDeLinhas) && (coluna < a->quantidadeDeColunas)){
        return 1;
    }
    return 0;
}

//Buscar item na matriz
int buscar_item(int linha, int coluna, MatrizEsparsa *a){
    Cell *aux;

    if(validar_posicao_matriz_esparsa(linha, coluna, a) == 1){
        aux = a->linhas[linha]->head;

        while((aux != NULL) && (aux->CoordenadaColuna < coluna)){
            aux = aux->next;
        }

        if((aux != NULL) && (aux->CoordenadaColuna == coluna)){
            return aux->valor;
        }
    }
    return 0;
}

//Obter ultima célula antes da que esta va posição (l, c) -> retorna (l-1, c)
static Cell* obter_celula_anterior_a_da_linha_na_coluna(int linha, ListaEncadeada *coluna){
    Cell *auxA, *auxB = NULL;

    if((linha >= 0) && (coluna != NULL)){
        auxA = coluna->head;

        while((auxA != NULL) && (auxA->CoordenadaLinha < linha)){
            auxB = auxA;
            auxA = auxA->down;
        }
    }
    return auxB;
}

//Inserir, remover ou trocar valor de um item na Matriz
bool inserir_remover_trocar_item_na_matriz(int item, int linha, int coluna, MatrizEsparsa *a){//->Remover não funciona
    Cell *posicaoNaLinhaAnterior, *posicaoNaLinhaAtual, *posicaoAnteriorDaColuna, *nova;

    if((a == NULL) || (coluna < 0) || (linha < 0) || (linha >= a->quantidadeDeLinhas) || (coluna >= a->quantidadeDeColunas)){
        return false;
    }
    else{
        if(validar_posicao_matriz_esparsa(linha, coluna, a) == 1){
            posicaoNaLinhaAnterior = NULL;
            posicaoNaLinhaAtual = a->linhas[linha]->head;

            while((posicaoNaLinhaAtual != NULL) && (posicaoNaLinhaAtual->CoordenadaColuna < coluna)){
                posicaoNaLinhaAnterior = posicaoNaLinhaAtual;
                posicaoNaLinhaAtual = posicaoNaLinhaAtual->next;
            }

            if(item != 0){
                if((posicaoNaLinhaAtual != NULL) && (posicaoNaLinhaAtual->CoordenadaColuna == coluna)){ //Existe uma célula na posição
                    posicaoNaLinhaAtual->valor = item;
                    return true;
                }
                else{ // Não existe a célula na posição, então deve ser alocada
                    nova = criar_nova_celula(item, linha, coluna);
                    posicaoAnteriorDaColuna = obter_celula_anterior_a_da_linha_na_coluna(linha, a->colunas[coluna]);
                    //lidando com a linha
                    if(posicaoNaLinhaAnterior != NULL){
                        nova->next = posicaoNaLinhaAnterior->next;
                        posicaoNaLinhaAnterior->next = nova;
                    }
                    else{ //primero elemnto na linha
                        nova->next = a->linhas[linha]->head;
                        a->linhas[linha]->head = nova;
                    }

                    //linha com a coluna
                    if(posicaoAnteriorDaColuna != NULL){
                        nova->down = posicaoAnteriorDaColuna->down;
                        posicaoAnteriorDaColuna->down = nova;
                    }
                    else{//primeiro elemento na coluna
                        nova->down = a->colunas[coluna]->head;
                        a->colunas[coluna]->head = nova;
                    }
                    return true;
                }
            }
            else if((posicaoNaLinhaAtual != NULL) && (posicaoNaLinhaAtual->CoordenadaColuna == coluna)){ //item == 0 -> remover espaço
                /*posicaoAnteriorDaColuna = obter_celula_anterior_a_da_linha_na_coluna(linha, a->colunas[coluna]);
                posicaoAnteriorDaColuna->down = posicaoNaLinhaAtual->down;
                posicaoNaLinhaAnterior->next = posicaoNaLinhaAtual->next;

                free(posicaoNaLinhaAtual);*/

                posicaoAnteriorDaColuna = obter_celula_anterior_a_da_linha_na_coluna(linha, a->colunas[coluna]);

                if(posicaoAnteriorDaColuna != NULL){
                    posicaoAnteriorDaColuna->down = posicaoNaLinhaAtual->down;
                }
                else{
                    a->colunas[coluna]->head = posicaoNaLinhaAtual->down;
                }

                if(posicaoNaLinhaAnterior != NULL){
                    posicaoNaLinhaAnterior->next = posicaoNaLinhaAtual->next;
                }
                else{
                    a->linhas[linha]->head = posicaoNaLinhaAtual->next;
                }

                free(posicaoNaLinhaAtual);

                return true;
            }
        }
        return false;
    }
}

//Imprimir matriz esparsa
void imprimir_matriz_esparsa(MatrizEsparsa *a){
    int i, j;

    for(i=0; i < a->quantidadeDeLinhas; i++){
        for(j=0; j < a->quantidadeDeColunas; j++){
            printf("%d   ", buscar_item(i, j, a));
        }
        printf("\n\n");
    }
}

//Criar matriz bidemensional
int** criar_matriz_bidimensional(int nLinhas, int nColunas){
    int **a;
    int i;

    a = (int**)malloc(sizeof(int*) * nLinhas);

    for(i=0; i<nLinhas; i++){
        a[i] = (int*)malloc(sizeof(int) * nColunas);
    }

    return a;
}

//Converter matriz bidimensional para esparsa
MatrizEsparsa* converter_bidimensonal_para_esparsa(int **a, int numeroLinhas, int numeroColunas){
    MatrizEsparsa *b;
    int i, j;

    b = criar_matriz_esparsa(numeroLinhas, numeroColunas);

    for(i=0; i<numeroLinhas; i++){
        for(j=0; j<numeroColunas; j++){
            inserir_remover_trocar_item_na_matriz(a[i][j], i, j, b);
        }
    }

    return b;
}

//Imprimir como esta no exercicio do hackerrank
void imprimir_esparsa_teste(MatrizEsparsa *a){
    int i, j, cont;

    for(i=0; i < a->quantidadeDeLinhas; i++){
        printf("%d: -> ", i);
        cont = 0;
        for(j=0; j < a->quantidadeDeColunas; j++){
            if(buscar_item(i, j, a) != 0){
                if(cont == 0){
                    printf("%d,%d ", j, buscar_item(i, j, a));
                }
                else{
                    printf("-> %d,%d ", j, buscar_item(i, j, a));
                }
                cont++;
            }
        }
        printf("\n");
    }
}

//Desalocar matriz esparsa
bool liberar_matriz_esparsa(MatrizEsparsa *a){
    int i;
    Cell *atualDaLinha;

    if(a != NULL){
        //Desalocando linhas
        for(i=0; i<a->quantidadeDeLinhas; i++){
            atualDaLinha = a->linhas[i]->head;
            while(atualDaLinha != NULL){
                a->linhas[i]->head = atualDaLinha->next;

                free(atualDaLinha);

                atualDaLinha = a->linhas[i]->head;
            }
        }
        free(a->linhas);
        free(a->colunas);
        free(a);
    }
    return false;
}
