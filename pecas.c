#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pecas.h"
#include "matriz.h"
#include "funcional.h"

void coloca_pecas_maquina(int linha, int coluna, int** gabarito)
{
	tipo_pecas* peca_aloc;											//Função que coloca as peças no gabarito da máquina.
	int espacos_alocados = 0;										//Enquanto houver espaço para colocar mais peças, ela
	while(espacos_para_pecas(linha, coluna) > espacos_alocados)		//sorteia uma peça, procura por posições válidas para
	{																//alocar ela na matriz com a função "acha_posicoes_validas"
		peca_aloc = aloca_peca(1 + gera_random(5));					//e se houver posições, ele coloca a peça no gabarito,
		acha_posicoes_validas(linha, coluna, peca_aloc, gabarito);	//em seguida, liberando a alocação dinâmica.
		espacos_alocados += peca_aloc->tamanho;
		free(peca_aloc);
	}
}

void acha_posicoes_validas(int linha, int coluna, tipo_pecas* peca, int** gabarito);

bool testa_quantidade_pecas(int dimensao_peca, int num_pecas, int linha, int coluna, int pecas_alocadas)
{																					//Função para testar se a quantidade de peças
	return dimensao_peca*num_pecas <= ((linha*coluna*3)/10) - pecas_alocadas;		//a serem colocadas inseridas pelo jogador po-
}																					//dem ser colocadas.

tipo_pecas *aloca_peca(int tamanho_peca)
{
	tipo_pecas* peca_aloc;												//Função para alocar uma peça.

	peca_aloc = (tipo_pecas*) malloc(sizeof(tipo_pecas));
	peca_aloc->sentido = gera_random(2);
	peca_aloc->tamanho = tamanho_peca;
	peca_aloc->encaixa = false;

	return peca_aloc;
}

void quantidade_pecas(int linha, int coluna, int** gabarito)
{
	tipo_pecas* peca_aloc;														//Função que pede a quantidade de peças para o jogador
	int dimensao_peca = 5;														//inserir no seu gabarito. Se houver espaços e o número
	int num_pecas = 0;															//de peças inseridas pelo jogador couber naquela matriz,
	int espacos_alocados = 0;													//o programa vai colocando peças, uma a uma, gerando po-
																				//sições aleatórias na inserção dessas peças e verifican-
	while(dimensao_peca)														//do para ver se as posições são válidas. Caso forem, o
	{																			//programa coloca a peça no gabarito e parte para a pró-
		if(espacos_para_pecas(linha, coluna) > espacos_alocados)				//xima.
		{
			printf("Quantas pecas de %d espacos voce quer?\n", dimensao_peca);
			scanf("%d", &num_pecas);

			if(testa_quantidade_pecas(dimensao_peca, num_pecas, linha, coluna, espacos_alocados))
			{
				espacos_alocados += num_pecas * dimensao_peca;
				for (int i = 0; i < num_pecas; i++)
				{
					peca_aloc = aloca_peca(dimensao_peca);
					acha_posicoes_validas(linha, coluna, peca_aloc, gabarito);
					free(peca_aloc);
				}
			} else {															//Caso o jogador insira uma quantia de peças superior
				printf("O numero de pecas excede o limite do gabarito!\n");	//à capacidade do gabarito, o programa pede para que
				dimensao_peca++;												//ele insira novamente o número de peças.
			}
		}
		dimensao_peca--;

		if(!dimensao_peca && espacos_para_pecas(linha, coluna) > espacos_alocados)						//Caso o jogador insira uma
		{																								//quantia inferior à capacidade
			printf("-----------------------------------\nAinda existem posicoes livres para pecas!\n");	//gabarito, e ainda hajam posi-
			dimensao_peca = 5;																			//ções para colocar peças, o pro-
		}																								//grama volta para a peça de maior
	}																									//tamanho e pede para que ele insira
}																										//novamente o número de peças.

void define_posicoes(int linha, int coluna, int *posicao_linha, int *posicao_coluna, tipo_pecas* peca)
{																									//Função para gerar posições
	do{ 																							//aleatórias válidas. Uso a
		*posicao_linha = gera_random(linha);														//subtração dentro do laço para
		*posicao_coluna = gera_random(coluna);														//que o programa não coloque uma peça
	} while (peca->tamanho > linha - *posicao_linha || peca->tamanho > coluna - *posicao_coluna);	//numa posição inválida, perdendo
}																									//alguma parte da peça fora da matriz.
																									
bool analisa_posicao_peca(int posicao_linha, int posicao_coluna, tipo_pecas* peca, int** gabarito)
{
	int aux = 0;

	for (int i = 0; i < peca->tamanho; i++)
		if (gabarito[peca->sentido ? posicao_linha + i : posicao_linha][peca->sentido ? posicao_coluna : posicao_coluna + i] == 0)
			aux++;
										//Função para testar se a peça encaixa na posição enviada por parâmetro.
	if(aux == peca->tamanho)
		peca->encaixa = true;

	return aux == peca->tamanho;
}

void coloca_peca(int posicao_linha, int posicao_coluna, tipo_pecas* peca, int** gabarito)
{
	if (peca->sentido)															//Função para colocar a peça no gabarito..
		for (int i = 0; i < peca->tamanho; i++)
		{
			if (gabarito[posicao_linha + i][posicao_coluna] == 0)
				switch(peca->tamanho)
				{
					case 1:
						gabarito[posicao_linha + i][posicao_coluna] = 1;
						break;
					case 2:
						gabarito[posicao_linha + i][posicao_coluna] = 2;
						break;
					case 3:
						gabarito[posicao_linha + i][posicao_coluna] = 3;
						break;
					case 4:
						gabarito[posicao_linha + i][posicao_coluna] = 4;
						break;
					case 5:
						gabarito[posicao_linha + i][posicao_coluna] = 5;
						break;
				}
		}
	else
		for (int i = 0; i < peca->tamanho; i++)
		{
			if (gabarito[posicao_linha][posicao_coluna + i] == 0)
								switch(peca->tamanho)
				{
					case 1:
						gabarito[posicao_linha][posicao_coluna + i] = 1;
						break;
					case 2:
						gabarito[posicao_linha][posicao_coluna + i] = 2;
						break;
					case 3:
						gabarito[posicao_linha][posicao_coluna + i] = 3;
						break;
					case 4:
						gabarito[posicao_linha][posicao_coluna + i] = 4;
						break;
					case 5:
						gabarito[posicao_linha][posicao_coluna + i] = 5;
						break;
				}
		}
}

void acha_posicoes_validas(int linha, int coluna, tipo_pecas* peca, int** gabarito)
{
	int posicao_linha = 0, posicao_coluna = 0;															//Função chamada para analisar
																										//a validade da posição gerada.
	do {																								//Caso seja uma posição vazia,
		define_posicoes(linha, coluna, &posicao_linha, &posicao_coluna, peca);							//e couber a peça naquelas posições,
	} while (!analisa_posicao_peca(posicao_linha, posicao_coluna, peca, gabarito) && !peca->encaixa);	//o programa coloca a peça, senão
																										//o programa vai gerar posições
	coloca_peca(posicao_linha, posicao_coluna, peca, gabarito);							  				//aleatórias até achar uma posição
}																										//válida.