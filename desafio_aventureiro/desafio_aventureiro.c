#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char *pista;
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

typedef struct PistaNode {
    char *pista;
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// ---------- Cria uma nova sala ----------
Sala* criarSala(char nome[], char *pista) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->pista = pista ? strdup(pista) : NULL;
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// ---------- Insere pista em ordem na BST ----------
PistaNode* inserirPista(PistaNode *raiz, char *pista) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        novo->pista = strdup(pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// ---------- Exibe pistas em ordem alfabética ----------
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// ---------- Exploração da mansão ----------
void explorarSalasComPistas(Sala *atual, PistaNode **pistas) {
    char escolha;
    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        if (atual->pista) {
            printf(">> Pista encontrada: \"%s\"\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
        } else {
            printf(">> Nenhuma pista neste cômodo.\n");
        }

        printf("Escolha o caminho: (e) esquerda | (d) direita | (s) sair: ");
        scanf(" %c", &escolha);

        if (escolha == 'e')
            atual = atual->esquerda;
        else if (escolha == 'd')
            atual = atual->direita;
        else if (escolha == 's')
            break;
        else
            printf("Opção inválida! Tente novamente.\n");
    }
}

int main() {
    // ---------- Criação do mapa fixo da mansão ----------
    Sala *hall = criarSala("Hall de Entrada", "O mordomo parece nervoso.");
    Sala *salaEstar = criarSala("Sala de Estar", "Uma luva rasgada está no sofá.");
    Sala *cozinha = criarSala("Cozinha", NULL);
    Sala *biblioteca = criarSala("Biblioteca", "Um livro aberto sobre venenos.");
    Sala *jardim = criarSala("Jardim", "Pegadas recentes na terra molhada.");
    Sala *porão = criarSala("Porão", "Um colar quebrado.");

    // Ligando as salas (mapa fixo)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porão;

    PistaNode *pistas = NULL;

    printf("=== Detective Quest: Coleta de Pistas ===\n");
    explorarSalasComPistas(hall, &pistas);

    printf("\n===== PISTAS COLETADAS =====\n");
    if (pistas)
        exibirPistas(pistas);
    else
        printf("Nenhuma pista foi coletada.\n");

    printf("\nFim da investigação!\n");
    return 0;
}
