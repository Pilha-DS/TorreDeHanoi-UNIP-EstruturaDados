#include <stdio.h>
#include <stdlib.h>
#include "hanoi.h"

void iniciarJogo(Jogo *jogo, int numDiscos) {
    int i;

    jogo->pinos = (Pilha *) malloc(NUM_PINOS * sizeof(Pilha));
    jogo->numDiscos = numDiscos;
    jogo->movimentos = 0;

    inicializarPilha(&jogo->historico);

    for (i = 0; i < NUM_PINOS; i++) {
        inicializarPilha(&jogo->pinos[i]);
    }

    for (i = numDiscos; i >= 1; i--) {
        push(&jogo->pinos[0], i);
    }
}

void reiniciarJogo(Jogo *jogo) {
    int i;

    for (i = 0; i < NUM_PINOS; i++) {
        freeStack(&jogo->pinos[i]);
    }

    freeStack(&jogo->historico);

    jogo->movimentos = 0;

    inicializarPilha(&jogo->historico);

    for (i = jogo->numDiscos; i >= 1; i--) {
        push(&jogo->pinos[0], i);
    }
}

void liberarJogo(Jogo *jogo) {
    int i;

    for (i = 0; i < NUM_PINOS; i++) {
        freeStack(&jogo->pinos[i]);
    }

    freeStack(&jogo->historico);

    free(jogo->pinos);
    jogo->pinos = NULL;
}

int jogadaValida(Jogo *jogo, int origem, int destino) {
    if (origem == destino) {
        return 0;
    }

    if (isEmpty(&jogo->pinos[origem])) {
        return 0;
    }

    if (isEmpty(&jogo->pinos[destino])) {
        return 1;
    }

    return peek(&jogo->pinos[origem]) < peek(&jogo->pinos[destino]);
}

int moverDisco(Jogo *jogo, int origem, int destino) {
    int disco;

    if (!jogadaValida(jogo, origem, destino)) {
        return 0;
    }

    disco = pop(&jogo->pinos[origem]);
    push(&jogo->pinos[destino], disco);
    push(&jogo->historico, origem * NUM_PINOS + destino);
    jogo->movimentos++;

    return 1;
}

int desfazerJogada(Jogo *jogo) {
    int jogada;
    int origem;
    int destino;
    int disco;

    if (isEmpty(&jogo->historico)) {
        return 0;
    }

    jogada = pop(&jogo->historico);
    origem = jogada / NUM_PINOS;
    destino = jogada % NUM_PINOS;

    disco = pop(&jogo->pinos[destino]);
    push(&jogo->pinos[origem], disco);
    jogo->movimentos--;

    return 1;
}

int jogoVencido(Jogo *jogo) {
    return tamanhoPilha(&jogo->pinos[NUM_PINOS - 1]) == jogo->numDiscos;
}

int movimentosMinimos(Jogo *jogo) {
    int total = 1;
    int i;

    for (i = 0; i < jogo->numDiscos; i++) {
        total = total * 2;
    }

    return total - 1;
}

int movimentosRestantes(Jogo *jogo) {
    int restantes = movimentosMinimos(jogo) - jogo->movimentos;

    if (restantes < 0) {
        return 0;
    }

    return restantes;
}

int indicePino(char caractere) {
    if (caractere >= 'a' && caractere <= 'z') {
        caractere = (char) (caractere - 'a' + 'A');
    }

    if (caractere >= 'A' && caractere <= 'A' + NUM_PINOS - 1) {
        return caractere - 'A';
    }

    if (caractere >= '1' && caractere <= '0' + NUM_PINOS) {
        return caractere - '1';
    }

    return -1;
}

char nomePino(int pino) {
    return (char) ('A' + pino);
}

static void imprimirCelula(int valor, int largura) {
    int preenchimento;
    int espacos;
    int i;

    printf(" ");

    if (valor < 1) {
        for (i = 0; i < largura; i++) {
            printf(" ");
        }
        return;
    }

    preenchimento = 2 * valor - 1;
    espacos = (largura - preenchimento) / 2;

    for (i = 0; i < espacos; i++) {
        printf(" ");
    }

    for (i = 0; i < preenchimento; i++) {
        printf("=");
    }

    for (i = 0; i < largura - preenchimento - espacos; i++) {
        printf(" ");
    }
}

void exibirJogo(Jogo *jogo) {
    int largura = 2 * jogo->numDiscos + 1;
    int linha;
    int coluna;
    int pino;
    int posicao;
    int valor;
    int i;

    printf("\n");

    for (linha = 0; linha < jogo->numDiscos; linha++) {
        for (pino = 0; pino < NUM_PINOS; pino++) {
            posicao = tamanhoPilha(&jogo->pinos[pino]) - jogo->numDiscos + linha;
            valor = valorNaPosicao(&jogo->pinos[pino], posicao);
            imprimirCelula(valor, largura);
        }
        printf("\n");
    }

    for (pino = 0; pino < NUM_PINOS; pino++) {
        printf(" ");
        for (i = 0; i < largura; i++) {
            printf("-");
        }
    }
    printf("\n");

    for (pino = 0; pino < NUM_PINOS; pino++) {
        printf(" ");
        for (coluna = 0; coluna < largura; coluna++) {
            if (coluna == largura / 2) {
                printf("%c", nomePino(pino));
            } else {
                printf(" ");
            }
        }
    }
    printf("\n\n");

    printf("Discos: %d | Movimentos: %d | Minimo: %d | Faltam: %d\n\n",
           jogo->numDiscos,
           jogo->movimentos,
           movimentosMinimos(jogo),
           movimentosRestantes(jogo));
}

static void resolverTorre(Jogo *jogo, int n, int origem, int destino, int auxiliar) {
    if (n == 0) {
        return;
    }

    resolverTorre(jogo, n - 1, origem, auxiliar, destino);

    moverDisco(jogo, origem, destino);
    printf("  Passo %4d: %c -> %c\n", jogo->movimentos, nomePino(origem), nomePino(destino));

    resolverTorre(jogo, n - 1, auxiliar, destino, origem);
}

void resolverAutomaticamente(Jogo *jogo) {
    printf("\nResolvendo com %d discos...\n\n", jogo->numDiscos);
    resolverTorre(jogo, jogo->numDiscos, 0, NUM_PINOS - 1, 1);
    printf("\nTotal de movimentos: %d\n", jogo->movimentos);
}
