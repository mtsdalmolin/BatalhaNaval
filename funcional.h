typedef struct posicao
{
	int linha;
	int coluna;
	int direcao;
	int vetor_opcoes[4];
	bool acertou_ultima;
} tipo_posicao;

/* Prototypes das funções do funcional.h */

void marca_posicoes_agua_gabarito(int linha, int coluna, int** gabarito);

void incrementa_posicao(int linha, int coluna, tipo_posicao* posicao, int** tabuleiro, int** gabarito);

bool dentro_limites_matriz(int linha, int coluna, tipo_posicao* posicao, int** tabuleiro);

void preenche_vetor_opcoes(tipo_posicao* posicao);

void marca_tabuleiro(int posicao_linha, int posicao_coluna, int** tabuleiro, int** gabarito);

bool verifica_posicao_jogada(int linha, int coluna, int posicao_linha, int posicao_coluna, int** tabuleiro);

void jogador_joga(int linha, int coluna, int** tabuleiro, int** gabarito);

bool verifica_posicao(int** tabuleiro, tipo_posicao* posicao);

void maquina_joga(int linha, int coluna, int** tabuleiro, int** gabarito, tipo_posicao* posicao);

void maquina_joga_se_acertou(int linha, int coluna, int** tabuleiro, int** gabarito, tipo_posicao* posicao);

void imprime_resultado(bool troca_jogador);

bool testa_vitoria(int linha, int coluna, int espacos_alocados, int** tabuleiro);

int espacos_alocados(int linha, int coluna, int** gabarito);

void joga_vs_maquina(int linha, int coluna, int** tabuleiro_jogador1, int** tabuleiro_jogador2, int** matriz_gabarito1, int** matriz_gabarito2, int espacos_alocados_jogador1, int espacos_alocados_jogador2, tipo_posicao* posicao);

void joga_vs_jogador(int linha, int coluna, int** tabuleiro_jogador1, int** tabuleiro_jogador2, int** matriz_gabarito1, int** matriz_gabarito2, int espacos_alocados_jogador1, int espacos_alocados_jogador2);

int seleciona_modo_jogo();

int gera_random(int limite);