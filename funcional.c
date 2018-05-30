#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"
#include "funcional.h"

int gera_random(int limite)
{									//Função para gerar um número aleatório e limitar ele com a variável passada por parâmetro.
	return rand() % limite;
}

int seleciona_modo_jogo()
{
	int menu_selecao = 0;								
	do {												
		printf("-----------JOGO BATALHA NAVAL!-----------\nSelecione o modo de jogo.\n1. VS Maquina.\n2. VS Jogador.\n");
		scanf("%d", &menu_selecao);
	} while (menu_selecao != 1 && menu_selecao != 2);							//Função que seleciona o modo de jogo.
																				//Se retornar 1, seleciona joga_vs_maquina.
	return menu_selecao;													    //Se retornar 2, seleciona joga_vs_jogador.
}

void joga_vs_jogador(int linha, int coluna, int** tabuleiro_jogador1, int** tabuleiro_jogador2, int** matriz_gabarito1, int** matriz_gabarito2, int espacos_alocados_jogador1, int espacos_alocados_jogador2)
{
	bool termina_jogo = false;
	bool troca_jogador = true;
	while (!termina_jogo)
	{																									//Função que roda o jogo
		if(troca_jogador)																				//com os dois jogadores.
		{
			printf("----------JOGADOR 1----------\n");
			jogador_joga(linha, coluna, tabuleiro_jogador1, matriz_gabarito2);
			desenha_tabuleiro(linha, coluna, tabuleiro_jogador1);
			termina_jogo = testa_vitoria(linha, coluna, espacos_alocados_jogador1, tabuleiro_jogador1);
			troca_jogador = false;
		} else {
			printf("----------JOGADOR 2----------\n");
			jogador_joga(linha, coluna, tabuleiro_jogador2, matriz_gabarito1);
			desenha_tabuleiro(linha, coluna, tabuleiro_jogador2);
			termina_jogo = testa_vitoria(linha, coluna, espacos_alocados_jogador2, tabuleiro_jogador2);
			troca_jogador = true;
		}
	}
	imprime_resultado(troca_jogador);
}

void joga_vs_maquina(int linha, int coluna, int** tabuleiro_jogador1, int** tabuleiro_jogador2, int** matriz_gabarito1, int** matriz_gabarito2, int espacos_alocados_jogador1, int espacos_alocados_jogador2, tipo_posicao* posicao);

void imprime_resultado(bool troca_jogador)
{
	if (!troca_jogador)							//Função que imprime o resultado no fim do jogo
		printf("Jogador 1 ganhou!\n");			//chamada no fim das funções "joga_vs_maquina" e
	else										//"joga_vs_jogador".
		printf("Jogador 2 ganhou!\n");
}

bool testa_vitoria(int linha, int coluna, int espacos_alocados, int** tabuleiro)
{
	int pecas_marcadas = 0;										//Função que testa se o número de espacos liberados na matriz
	for (int i = 0; i < linha; i++)								//corrente corresponde ao número de posições alocadas no gaba-
		for (int j = 0; j < coluna; j++)						//rito. Essa função é atribuída a uma variável booleana nomea-
			if (tabuleiro[i][j] != 6 && tabuleiro[i][j] != 0)	//da "termina_jogo" nas funções "joga_vs_maquina" e 
				pecas_marcadas++;								//"jogador_vs_jogador". Caso retorne verdadeira, satisfaz a con-
	return pecas_marcadas == espacos_alocados;					//dição do laço e termina o jogo.
}

int espacos_alocados(int linha, int coluna, int** gabarito)
{
	int total_alocados = 0;						//Função que calcula o total de espaços alocados no gabarito enviado.
	for (int i = 0; i < linha; i++)
		for (int j = 0; j < coluna; j++)
			if (gabarito[i][j] != 6)
				total_alocados++;
	return total_alocados;
}

void marca_posicoes_agua_gabarito(int linha, int coluna, int** gabarito)
{
	for (int i = 0; i < linha; i++)				//Função que substitui as posições "0" do gabarito por "6".
		for (int j = 0; j < coluna; j++)		//É feito isso para que a função "desenha_tabuleiro" marque
			if (gabarito[i][j] == 0)			//corretamente a posição que indica uma água. Caso isso não
				gabarito[i][j] = 6;				//fosse feito, ele imprimiria uma posição vazia, o que não
}												//era a intenção.

void incrementa_posicao(int linha, int coluna, tipo_posicao* posicao, int** tabuleiro, int** gabarito)
{
	switch(posicao->direcao)					//Função que avança a posição atual
	{											//dependendo da direção que está avançando
		case 1:
			posicao->linha++;
			break;
		case 2:
			posicao->linha--;
			break;
		case 3:
			posicao->coluna++;
			break;
		case 4:
			posicao->coluna--;
			break;
	}
}

bool dentro_limites_matriz(int linha, int coluna, tipo_posicao* posicao, int** tabuleiro)
{
	switch(posicao->direcao)							//Função que verifica se a posição seguinte está dentro do tabuleiro.
	{													//Ela depende da direção que está avançando para incrementar ou linha
		case 1:											//ou coluna.
			if (posicao->linha > linha - 1)
			{
				posicao->vetor_opcoes[0] = 0;
				return false;
			}
		case 2:
			if (posicao->linha < 0)
			{
				posicao->vetor_opcoes[1] = 0;
				return false;
			}
		case 3:
			if (posicao->coluna > coluna - 1)
			{
				posicao->vetor_opcoes[2] = 0;
				return false;
			}
		case 4:
			if (posicao->coluna < 0)
			{
				posicao->vetor_opcoes[3] = 0;
				return false;
			}
	}
	return true;
}

void preenche_vetor_opcoes(tipo_posicao* posicao)
{
	for (int i = 0; i < 4; i++)						//Função que preenche o vetor de direções da estrutura.
		posicao->vetor_opcoes[i] = i+1;
}

void marca_tabuleiro(int posicao_linha, int posicao_coluna, int** tabuleiro, int** gabarito)
{																						//Função que marca o valor da peça no
	tabuleiro[posicao_linha][posicao_coluna] = gabarito[posicao_linha][posicao_coluna];	//tabuleiro, pegando o valor do gaba-
}																						//rito.


/* Função que verifica se a posição jogada pelo jogador é válida. Caso não for válida (ex.: jogou em uma posição já jogada), */
/* ele pede para jogar novamente em uma posição válida. */
bool verifica_posicao_jogada(int linha, int coluna, int posicao_linha, int posicao_coluna, int** tabuleiro)
{
	return !(posicao_linha < 0 || posicao_linha > linha - 1 || posicao_coluna < 0 || posicao_coluna > coluna - 1 || tabuleiro[posicao_linha][posicao_coluna] != 0);
}

void jogador_joga(int linha, int coluna, int** tabuleiro, int** gabarito)
{
	int linha_jogada = -1, coluna_jogada = -1;												//Função que lê as posições que o
																							//jogador joga. Ele só sai do laço
	while(!verifica_posicao_jogada(linha, coluna, linha_jogada, coluna_jogada, tabuleiro))	//se as posições jogadas são válidas.
	{
		printf("Informe as coordenadas desejadas.\nLinha: ");
		scanf("%d", &linha_jogada);
		printf("Coluna: ");
		scanf("%d", &coluna_jogada);
	}
	marca_tabuleiro(linha_jogada, coluna_jogada, tabuleiro, gabarito);
}

bool verifica_posicao(int** tabuleiro, tipo_posicao* posicao);

void maquina_joga(int linha, int coluna, int** tabuleiro, int** gabarito, tipo_posicao* posicao)
{
	bool jogando = true;
																			//Função que o computador joga.
	int posicao_linha;
	int posicao_coluna;

	while(jogando)
	{
		do
		{																				//Vai gerar posições aleatórias até que
			posicao_linha = gera_random(linha);											//aquelaposição no tabuleiro esteja livre.
			posicao_coluna = gera_random(coluna);										//Após gerar uma posição livre para jogar,
		} while (tabuleiro[posicao_linha][posicao_coluna]);								//o programa vai analisar o que contém na-
																						//quela posição, consultando o gabarito.
																						//Se acertar uma água, ele marca a água e
		if(gabarito[posicao_linha][posicao_coluna] == 6 && !posicao->acertou_ultima)	//segue jogando posições aleatórias procu-
		{																				//rando uma peça, e se acertar uma peça,
			marca_tabuleiro(posicao_linha, posicao_coluna, tabuleiro, gabarito);		//ele verifica se essa peça está nas bordas
			posicao->acertou_ultima = false;											//para que não ocorra um erro no avanço da
			posicao->direcao = 0;														//posição, pegando uma posição não alocada
			preenche_vetor_opcoes(posicao);												//da matriz. Depois de verificar se a peça
			jogando = false;															//está nas bordas, a próxima jogada será
		} else {																		//procurando o restante da peça nas posições
			if (!posicao->acertou_ultima)												//adjacentes.
			{
				posicao->linha = posicao_linha;
				posicao->coluna = posicao_coluna;
				marca_tabuleiro(posicao_linha, posicao_coluna, tabuleiro, gabarito);
				posicao->acertou_ultima = true;
				jogando = false;
			} else {
				while(!posicao->direcao)
					posicao->direcao = posicao->vetor_opcoes[gera_random(4)];

				posicao->vetor_opcoes[posicao->direcao - 1] = 0;
				incrementa_posicao(posicao->linha, posicao->coluna, posicao, tabuleiro, gabarito);
				if(dentro_limites_matriz(linha, coluna, posicao, tabuleiro))
				{
					if(verifica_posicao(tabuleiro, posicao))
					{
						marca_tabuleiro(posicao->linha, posicao->coluna, tabuleiro, gabarito);
						jogando = false;

						if (tabuleiro[posicao->linha][posicao->coluna] == 6)
						{
							posicao->direcao = 0;
							preenche_vetor_opcoes(posicao);
							posicao->acertou_ultima = false;
						}
					} else {
						posicao->direcao = 0;
						preenche_vetor_opcoes(posicao);
						posicao->acertou_ultima = false;
					}
				} else {
					posicao->direcao = 0;
					preenche_vetor_opcoes(posicao);
					posicao->acertou_ultima = false;
				}
			}
		}
	}
}

bool verifica_posicao(int** tabuleiro, tipo_posicao* posicao)
{
	return !tabuleiro[posicao->linha][posicao->coluna];
}

void maquina_joga_se_acertou(int linha, int coluna, int** tabuleiro, int** gabarito, tipo_posicao* posicao)
{
	bool jogando = true;																	//Função que é chamada se a máquina já
	while(jogando)																			//acertou uma primeira vez.
	{																						//Vai sortear uma direção adjacente, se
		while(!posicao->direcao)															//acertar uma água, volta a sortear posicões
			posicao->direcao = posicao->vetor_opcoes[gera_random(4)];						//aleatórias. Assim que acertou a direção em
																							//que a peça está direcionada, ele vai marcan-									
		posicao->vetor_opcoes[posicao->direcao - 1] = 0;									//do o tabuleiro naquela direção até en-
		incrementa_posicao(posicao->linha, posicao->coluna, posicao, tabuleiro, gabarito);	//contrar uma posição "água".
		if(dentro_limites_matriz(linha, coluna, posicao, tabuleiro))						//Quando achar uma posição "água", o pro-
		{																					//grama volta a sortear posições aleató-
			if(verifica_posicao(tabuleiro, posicao))										//rias por todo o tabuleiro.
			{																				
				marca_tabuleiro(posicao->linha, posicao->coluna, tabuleiro, gabarito);
				jogando = false;

				if (tabuleiro[posicao->linha][posicao->coluna] == 6)
				{
					posicao->direcao = 0;
					preenche_vetor_opcoes(posicao);
					posicao->acertou_ultima = false;
				}
			} else {
				posicao->direcao = 0;
			}
		}
		else
			posicao->direcao = 0;
	}
}
void joga_vs_maquina(int linha, int coluna, int** tabuleiro_jogador1, int** tabuleiro_jogador2, int** matriz_gabarito1, int** matriz_gabarito2, int espacos_alocados_jogador1, int espacos_alocados_jogador2, tipo_posicao* posicao)
{
	bool termina_jogo = false;																//Função que roda o jogo
	bool troca_jogador = true;																//jogador contra a máquina.
	while (!termina_jogo)
	{
		if(troca_jogador)
		{
			printf("----------JOGADOR 1----------\n");
			jogador_joga(linha, coluna, tabuleiro_jogador1, matriz_gabarito2);
			desenha_tabuleiro(linha, coluna, tabuleiro_jogador1);
			termina_jogo = testa_vitoria(linha, coluna, espacos_alocados_jogador1, tabuleiro_jogador1);
			troca_jogador = false;
		} else {
			printf("----------COMPUTADOR----------\n");
			maquina_joga(linha, coluna, tabuleiro_jogador2, matriz_gabarito1, posicao);
			desenha_tabuleiro(linha, coluna, tabuleiro_jogador2);
			termina_jogo = testa_vitoria(linha, coluna, espacos_alocados_jogador2, tabuleiro_jogador2);
			troca_jogador = true;
		}
	}
	imprime_resultado(troca_jogador);
}