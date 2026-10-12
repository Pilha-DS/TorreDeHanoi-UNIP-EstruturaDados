#include <stdlib.h>
#include "pilha.h"

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

void push(Pilha *p, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        return;
    }

    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

int pop(Pilha *p) {
    No *removido;
    int valor;

    if (isEmpty(p)) {
        return -1;
    }

    removido = p->topo;
    valor = removido->valor;
    p->topo = removido->prox;
    p->tamanho--;

    free(removido);

    return valor;
}

int peek(Pilha *p) {
    if (isEmpty(p)) {
        return -1;
    }

    return p->topo->valor;
}

int isEmpty(Pilha *p) {
    return p->topo == NULL;
}

int tamanhoPilha(Pilha *p) {
    return p->tamanho;
}

int valorNaPosicao(Pilha *p, int posicao) {
    No *atual = p->topo;
    int indice = 0;

    if (posicao < 0) {
        return -1;
    }

    while (atual != NULL && indice < posicao) {
        atual = atual->prox;
        indice++;
    }

    if (atual == NULL) {
        return -1;
    }

    return atual->valor;
}

void freeStack(Pilha *p) {
    No *atual = p->topo;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    p->topo = NULL;
    p->tamanho = 0;
}
