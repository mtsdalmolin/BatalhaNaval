#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int espacos_para_pecas(int linha, int coluna)
{												//Função para calcular o percentual mínimo
	return (linha*coluna*3)/10;					//de espaços para alocar as peças. No caso
}												//estou usando 30% do tabuleiro.

void desenha_tabuleiro(int linha, int coluna, int** tabuleiro)
{
	int l = 0, m = 0;

	for (int i = 0; i < coluna; ++i)
		i == 0 ? printf("   %d", i) : i < 10 ? printf("  %d", i) : printf(" %d", i);

	printf("\n");										//Função usada para desenhar o tabuleiro no terminal.
														//Estou usando identificadores para as peças. Cada ta-
	for (int i = 0; i < linha; i++)						//manho tem o seu identificador na impressão, e para
	{													//as posições "vazia" e "água", uso outros dois iden-
		l < 10 ? printf(" %d", l) : printf("%d", l);	//tificadores diferentes das peças. O switch detalha
														//os identificadores com as respectivas peças. O ín-
		for (int j = 0; j < coluna; j++)				//dice dos casos refere-se ao tamanho das peças.
		{
			switch(tabuleiro[i][j])
				{
					case 1:
						printf("|O|");
						break;
					case 2:
						printf("|V|");
						break;
					case 3:
						printf("|W|");
						break;
					case 4:
						printf("|T|");
						break;
					case 5:
						printf("|X|");
						break;
					case 6:
						printf("|A|");
						break;
					default:
						printf("|_|");
				}
		}
		l++;
		printf("\n");
	}
}

void zera_matriz(int linha, int coluna, int** matriz_tabuleiro)
{												//Função que enche uma matriz[linha][coluna]
	for(int i=0; i<linha; i++)					//com zeros. Uso essa função para não ter pro
		for(int j=0; j<coluna; j++)				//blemas com lixo da memória antes de iniciar
			matriz_tabuleiro[i][j] = 0;			//o jogo.
}

int **aloca_matriz(int linha, int coluna)
{
	int **matriz_tabuleiro = (int**)malloc(linha*sizeof(int*));					//Função para alocar as matrizes dinamicamente.

	for(int i=0; i<linha; i++)
		matriz_tabuleiro[i] = (int*)malloc(coluna*sizeof(int));

	return matriz_tabuleiro;
}

void libera_matriz(int** matriz)
{
	free(matriz);						//Função para liberar as matrizes alocadas dinamicamente.
}
