//Declaração de celula
typedef struct celula Cell;

//Declaração de lista encadeada
typedef struct lista ListaEncadeada;

//Declaração da matriz
typedef struct matriz MatrizEsparsa;

//Alocar matriz esparsa
MatrizEsparsa* criar_matriz_esparsa(unsigned int numeroLinhas, unsigned int numeroColunas);

//Alocar um celula
//static Cell* criar_nova_celula(int item, int linha, int coluna);

//Verificar se a posição possui uma celula
//static int validar_posicao_matriz_esparsa(int linha, int coluna, MatrizEsparsa* a);

//Buscar um item na matriz
int buscar_item(int linha, int coluna, MatrizEsparsa *a);

//Obter ultima célula antes da que esta va posição (l, c) -> retorna (l-1, c)
//static Cell* obter_celula_anterior_a_da_linha_na_coluna(int linha, ListaEncadeada *coluna);

//Inserir, remover ou trocar valor de um item na Matriz
bool inserir_remover_trocar_item_na_matriz(int item, int linha, int coluna, MatrizEsparsa *a); //->Remover não funciona

//Imprimir matriz esparsa
void imprimir_matriz_esparsa(MatrizEsparsa *a);

//Criar matriz bidemensional
int** criar_matriz_bidimensional(int nLinhas, int nColunas);

//Converter matriz bidimensional para esparsa
MatrizEsparsa* converter_bidimensonal_para_esparsa(int **a, int numeroLinhas, int numeroColunas);

//Imprimir como esta no exercicio do hackerrank
void imprimir_esparsa_teste(MatrizEsparsa *a);

//Desalocar matriz esparsa
bool liberar_matriz_esparsa(MatrizEsparsa *a);
