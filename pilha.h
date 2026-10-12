#ifndef PILHA_H
#define PILHA_H

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct {
    No *topo;
    int tamanho;
} Pilha;

void inicializarPilha(Pilha *p);
void push(Pilha *p, int valor);
int pop(Pilha *p);
int peek(Pilha *p);
int isEmpty(Pilha *p);
int tamanhoPilha(Pilha *p);
int valorNaPosicao(Pilha *p, int posicao);
void freeStack(Pilha *p);

#endif
