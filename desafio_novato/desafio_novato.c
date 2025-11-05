#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/*
 * Função: criarSala
 * -----------------
 * Cria uma nova sala com o nome especificado, alocada dinamicamente.
 * Retorna o ponteiro para a sala criada.
 */
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
 * Função: explorarSalas
 * ---------------------
 * Permite ao jogador explorar a mansão a partir da sala atual.
 * O jogador pode escolher ir para a esquerda (e), direita (d) ou sair (s).
 * A exploração termina quando o jogador chega a um cômodo sem saídas.
 */
void explorarSalas(Sala *atual) {
    char escolha;

    while (1) {
        printf("\nVocê está na %s.\n", atual->nome);

        // Verifica se a sala é uma folha (sem caminhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim da exploração! Não há mais caminhos.\n");
            break;
        }

        printf("Deseja ir para a esquerda (e), direita (d) ou sair (s)? ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho à esquerda!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há caminho à direita!\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("Exploração encerrada pelo jogador.\n");
            break;
        } 
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

/*
 * Função: liberarArvore
 * ---------------------
 * Libera toda a memória alocada para as salas da mansão.
 */
void liberarArvore(Sala *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

/*
 * Função: main
 * ------------
 * Cria automaticamente a estrutura da mansão (árvore binária),
 * e inicia a exploração a partir do Hall de entrada.
 */
int main() {
    // Criação automática da árvore da mansão
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porão");

    // Montagem da árvore (mapa fixo da mansão)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    printf("=== Detective Quest ===\n");
    printf("Explore a mansão para encontrar o culpado!\n");

    // Inicia a exploração
    explorarSalas(hall);

    // Libera memória antes de encerrar
    liberarArvore(hall);

    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}
