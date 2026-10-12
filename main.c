#include <stdio.h>
#include "pilha.h"
#include "hanoi.h"

#define TAM_LINHA 128

static int lerLinha(char *linha) {
    if (fgets(linha, TAM_LINHA, stdin) == NULL) {
        return 0;
    }

    return 1;
}

static void exibirMenu(void) {
    printf("==========================================\n");
    printf("     TORRE DE HANOI - ESTRUTURA DE DADOS\n");
    printf("==========================================\n");
    printf(" 1 - Jogar\n");
    printf(" 2 - Regras e comandos\n");
    printf(" 3 - Sair\n");
    printf("==========================================\n");
}

static void exibirRegras(void) {
    printf("\nREGRAS\n");
    printf("  - Existem tres pinos (A, B e C) e os discos comecam todos no pino A,\n");
    printf("    do maior (base) para o menor (topo).\n");
    printf("  - O objetivo e levar todos os discos para o pino C.\n");
    printf("  - Movimente um disco por vez, sempre o disco do topo de um pino.\n");
    printf("  - Um disco maior nunca pode ficar sobre um disco menor.\n\n");

    printf("COMANDOS DURANTE A PARTIDA\n");
    printf("  A B (ou 1 2)  move o disco do topo do pino de origem para o destino\n");
    printf("  d             desfaz a ultima jogada\n");
    printf("  r             reinicia a partida\n");
    printf("  s             resolucao automatica (reinicia a partida)\n");
    printf("  q             volta ao menu\n\n");
}

static int escolherDiscos(void) {
    char linha[TAM_LINHA];
    int discos = 0;
    int lidos;

    do {
        printf("\nNumero de discos (%d a %d): ", MIN_DISCOS, MAX_DISCOS);

        if (!lerLinha(linha)) {
            return MIN_DISCOS;
        }

        lidos = sscanf(linha, "%d", &discos);

        if (lidos != 1 || discos < MIN_DISCOS || discos > MAX_DISCOS) {
            printf("Valor invalido. Escolha entre %d e %d discos.\n", MIN_DISCOS, MAX_DISCOS);
        }
    } while (lidos != 1 || discos < MIN_DISCOS || discos > MAX_DISCOS);

    return discos;
}

static void jogar(Jogo *jogo) {
    char linha[TAM_LINHA];
    char origem;
    char destino;
    int lidos;
    int pinoOrigem;
    int pinoDestino;
    int automatico = 0;

    reiniciarJogo(jogo);
    exibirJogo(jogo);

    while (!jogoVencido(jogo)) {
        printf("Jogada (origem destino) ou comando [d/r/s/q]: ");

        if (!lerLinha(linha)) {
            printf("\n");
            return;
        }

        lidos = sscanf(linha, " %c %c", &origem, &destino);

        if (lidos == 1 && indicePino(origem) < 0) {
            switch (origem) {
            case 'd':
            case 'D':
                if (desfazerJogada(jogo)) {
                    exibirJogo(jogo);
                } else {
                    printf("Nao ha jogadas para desfazer.\n\n");
                }
                break;
            case 'r':
            case 'R':
                reiniciarJogo(jogo);
                exibirJogo(jogo);
                break;
            case 's':
            case 'S':
                reiniciarJogo(jogo);
                resolverAutomaticamente(jogo);
                exibirJogo(jogo);
                automatico = 1;
                break;
            case 'q':
            case 'Q':
                printf("\nVoltando ao menu.\n\n");
                return;
            default:
                printf("Entrada invalida. Use o formato \"A B\" ou um dos comandos.\n\n");
                break;
            }
            continue;
        }

        if (lidos == 1) {
            printf("Informe tambem o pino de destino (ex: %c B).\n\n", origem);
            continue;
        }

        if (lidos != 2) {
            printf("Entrada invalida. Use o formato \"A B\" ou um dos comandos.\n\n");
            continue;
        }

        pinoOrigem = indicePino(origem);
        pinoDestino = indicePino(destino);

        if (pinoOrigem < 0 || pinoDestino < 0) {
            printf("Pinos validos: A, B e C (ou 1, 2 e 3).\n\n");
            continue;
        }

        if (pinoOrigem == pinoDestino) {
            printf("Origem e destino iguais. Escolha pinos diferentes.\n\n");
            continue;
        }

        if (isEmpty(&jogo->pinos[pinoOrigem])) {
            printf("O pino %c esta vazio.\n\n", nomePino(pinoOrigem));
            continue;
        }

        if (!jogadaValida(jogo, pinoOrigem, pinoDestino)) {
            printf("Jogada invalida: um disco maior nao pode ficar sobre um menor.\n\n");
            continue;
        }

        moverDisco(jogo, pinoOrigem, pinoDestino);
        exibirJogo(jogo);
    }

    if (automatico) {
        printf("Resolucao automatica concluida em %d movimentos (minimo: %d).\n\n",
               jogo->movimentos, movimentosMinimos(jogo));
    } else {
        printf("Parabens! Voce venceu em %d movimentos.\n", jogo->movimentos);
        printf("Minimo possivel: %d movimentos.\n", movimentosMinimos(jogo));

        if (jogo->movimentos == movimentosMinimos(jogo)) {
            printf("Solucao otima!\n");
        }
        printf("\n");
    }
}

int main(void) {
    Jogo jogo;
    char linha[TAM_LINHA];
    int opcao;
    int discos;

    exibirMenu();

    while (1) {
        printf("Opcao: ");

        if (!lerLinha(linha)) {
            break;
        }

        if (sscanf(linha, "%d", &opcao) != 1) {
            printf("Opcao invalida.\n\n");
            continue;
        }

        if (opcao == 1) {
            discos = escolherDiscos();
            iniciarJogo(&jogo, discos);
            jogar(&jogo);
            liberarJogo(&jogo);
            exibirMenu();
        } else if (opcao == 2) {
            exibirRegras();
        } else if (opcao == 3) {
            printf("Encerrando o jogo.\n");
            break;
        } else {
            printf("Opcao invalida.\n\n");
        }
    }

    return 0;
}
