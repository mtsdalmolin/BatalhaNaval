typedef struct peca
{
	int tamanho;
	bool sentido;
	bool encaixa;
}tipo_pecas;

/* Prototypes das funções do pecas.c */

void acha_posicoes_validas(int linha, int coluna, tipo_pecas* peca, int** gabarito);

void coloca_peca(int posicao_linha, int posicao_coluna, tipo_pecas* peca, int** gabarito);

bool analisa_posicao_peca(int posicao_linha, int posicao_coluna, tipo_pecas* peca, int** gabarito);

void define_posicoes(int linha, int coluna, int *posicao_linha, int *posicao_coluna, tipo_pecas* peca);

void quantidade_pecas(int linha, int coluna, int** gabarito);

tipo_pecas *aloca_peca(int tamanho_peca);

bool testa_quantidade_pecas(int dimensao_peca, int num_pecas, int linha, int coluna, int pecas_alocadas);

void coloca_pecas_maquina(int linha, int coluna, int** gabarito);