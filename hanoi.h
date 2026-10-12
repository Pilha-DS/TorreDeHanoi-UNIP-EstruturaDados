#ifndef HANOI_H
#define HANOI_H

#include "pilha.h"

#define NUM_PINOS 3
#define MIN_DISCOS 3
#define MAX_DISCOS 10

typedef struct {
    Pilha *pinos;
    Pilha historico;
    int numDiscos;
    int movimentos;
} Jogo;

void iniciarJogo(Jogo *jogo, int numDiscos);
void reiniciarJogo(Jogo *jogo);
void liberarJogo(Jogo *jogo);

int jogadaValida(Jogo *jogo, int origem, int destino);
int moverDisco(Jogo *jogo, int origem, int destino);
int desfazerJogada(Jogo *jogo);
int jogoVencido(Jogo *jogo);

int movimentosMinimos(Jogo *jogo);
int movimentosRestantes(Jogo *jogo);

int indicePino(char caractere);
char nomePino(int pino);

void exibirJogo(Jogo *jogo);
void resolverAutomaticamente(Jogo *jogo);

#endif
