/* Trabalho 1 de Laboratório de Programação II 	                  													  */
/* Aluno: Matheus Dalmolin da Silva 																				  */
/* O objetivo do trabalho foi desenvolver um jogo de batalha naval.                                                   */
/* No jogo, o jogador pode escolher entre enfrentar a máquina ou um outro jogador.                                    */
/* As peças são diferenciadas pelo seu tamanho.																	      */
/* Peças de tamanho 1 tem o identificador "0" no tabuleiro.                                                           */
/* Peças de tamanho 2 tem o identificador "V" no tabuleiro.                                                           */
/* Peças de tamanho 3 tem o identificador "W" no tabuleiro.                                                           */
/* Peças de tamanho 4 tem o identificador "T" no tabuleiro.                                                           */
/* Peças de tamanho 5 tem o identificador "X" no tabuleiro.                                                           */
/* Posições são representadas por "A" quando a jogada atinge uma posição que não há nenhuma peça, atingindo uma água. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "matriz.h"
#include "pecas.h"
#include "funcional.h"

int main()
{
	srand(time(NULL));
	
	/* Declaração das variáveis e atribuições dos valores iniciais. */
	int **tabuleiro_jogador1, **tabuleiro_jogador2, **matriz_gabarito1, **matriz_gabarito2, linha, coluna;
	int espacos_alocados_jogador1, espacos_alocados_jogador2;
	int menu_selecao;
	clock_t inicio, fim;
	tipo_posicao posicao;
	posicao.direcao = 0;
	posicao.acertou_ultima = false;
	preenche_vetor_opcoes(&posicao);

	/* Chama a função que seleciona o modo do jogo */
	menu_selecao = seleciona_modo_jogo();

	/* Início do contador de tempo. */
	inicio = clock();

	/* Define os parâmetros para alocar as matrizes dos tabuleiros e dos gabaritos. */
	printf("Informe o tamanho do tabuleiro.\nLinhas: ");
	scanf("%d", &linha);
	printf("Colunas: ");
	scanf("%d", &coluna);

	/* Alocação dinâmica dos tabuleiros e dos gabaritos. */
	tabuleiro_jogador1 = aloca_matriz(linha, coluna);
	matriz_gabarito1 = aloca_matriz(linha, coluna);
	tabuleiro_jogador2 = aloca_matriz(linha, coluna);
	matriz_gabarito2 = aloca_matriz(linha, coluna);

	/* Zero as matrizes para que não pegue lixo da memória. */
	zera_matriz(linha, coluna, tabuleiro_jogador1);
	zera_matriz(linha, coluna, matriz_gabarito1);
	zera_matriz(linha, coluna, tabuleiro_jogador2);
	zera_matriz(linha, coluna, matriz_gabarito2);

	/* Pede a quantidade de peças para o jogador e coloca na matriz. Em seguida, imprime um gabarito contendo as peças alocadas. */
	printf("----------JOGADOR 1----------\n");
	quantidade_pecas(linha, coluna, matriz_gabarito1);
	desenha_tabuleiro(linha, coluna, matriz_gabarito1);

	/* Chama a função para saber o número de espaços que contém peças. */
	//espacos_alocados_jogador1 = espacos_alocados(linha, coluna, matriz_gabarito2);

	/* Chama a função para substituir os "0" na matriz por "6". Isso porque a função "desenha_tabuleiro" identifica o "0" como */
	/* uma posição vazia e o "6" como uma posição água. */
	marca_posicoes_agua_gabarito(linha, coluna, matriz_gabarito1);

	/* Faz a seleção da máquina ou jogador. */
	if(menu_selecao == 1)
	{
		printf("----------COMPUTADOR----------\n");									  //Chama as funções para alocar as peças
		coloca_pecas_maquina(linha, coluna, matriz_gabarito2);						  //geradas randomicamente pela máquina.
		desenha_tabuleiro(linha, coluna, matriz_gabarito2);							  //Em seguida, chama a função "joga_vs_maquina"
		marca_posicoes_agua_gabarito(linha, coluna, matriz_gabarito2);				  //para começar a partida.
		espacos_alocados_jogador1 = espacos_alocados(linha, coluna, matriz_gabarito2);
		espacos_alocados_jogador2 = espacos_alocados(linha, coluna, matriz_gabarito1);
		joga_vs_maquina(linha, coluna, tabuleiro_jogador1, tabuleiro_jogador2, matriz_gabarito1, matriz_gabarito2, espacos_alocados_jogador1, espacos_alocados_jogador2, &posicao);
	} else {
		printf("----------JOGADOR 2----------\n");									  //Chama as funções para alocar as peças no 
		quantidade_pecas(linha, coluna, matriz_gabarito2);							  //tabuleiro, imprime um gabarito e em seguida
		desenha_tabuleiro(linha, coluna, matriz_gabarito2);						  	  //substitui as posições "0" do gabarito por "6".
		marca_posicoes_agua_gabarito(linha, coluna, matriz_gabarito2);
		espacos_alocados_jogador1 = espacos_alocados(linha, coluna, matriz_gabarito2);
		espacos_alocados_jogador2 = espacos_alocados(linha, coluna, matriz_gabarito1);
		joga_vs_jogador(linha, coluna, tabuleiro_jogador1, tabuleiro_jogador2, matriz_gabarito1, matriz_gabarito2, espacos_alocados_jogador1, espacos_alocados_jogador2);
	}

	/* Liberação das matrizes alocadas dinamicamente. */
	libera_matriz(tabuleiro_jogador1);
	libera_matriz(matriz_gabarito1);
	libera_matriz(tabuleiro_jogador2);
	libera_matriz(matriz_gabarito2);

	/* Fim do contador de tempo. */
	fim = clock();	
	printf("Tempo de duracao do jogo: %.2lf\n segundos.",((double)(fim - inicio)/CLOCKS_PER_SEC));
	
	return 0;
}