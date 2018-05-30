/* Prototypes das funções do matriz.c */

void desenha_tabuleiro(int linha, int coluna, int** tabuleiro);

void zera_matriz(int linha, int coluna, int** matriz_tabuleiro);

int **aloca_matriz(int linha, int coluna);

void libera_matriz(int** matriz);

int espacos_para_pecas(int linha, int coluna);