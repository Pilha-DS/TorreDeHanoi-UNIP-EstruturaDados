# Torre de Hanói

Trabalho prático da disciplina de Estrutura de Dados da UNIP, feito para complementar a nota.

O jogo roda no terminal e toda a mecânica dele é controlada por pilhas dinâmicas,
implementadas do zero como listas encadeadas com alocação dinâmica de memória.

Autores: Jonathan e Gabriel

## Regras do jogo

- São 3 pinos: A, B e C. No começo todos os discos ficam no pino A, do maior
  (embaixo) para o menor (em cima).
- O objetivo é passar todos os discos para o pino C.
- Só dá para mover o disco que está no topo de um pino, e um por vez.
- Um disco maior nunca pode ficar em cima de um disco menor.
- Dá para jogar com 3 até 10 discos. O número mínimo de jogadas é 2^n - 1
  (com 3 discos, por exemplo, são 7 jogadas).

## Comandos

Durante a partida:

- `A B` (ou `1 2`) move o disco do topo do pino A para o pino B
- `d` desfaz a última jogada
- `r` reinicia a partida
- `s` mostra a solução automática
- `q` volta para o menu

## Como compilar

Com o make:

    make

Sem o make:

    gcc -Wall -std=c11 main.c pilha.c hanoi.c -o hanoi

## Como executar

    ./hanoi

## Arquivos

- pilha.h / pilha.c - a pilha (push, pop, peek, isEmpty, freeStack)
- hanoi.h / hanoi.c - as regras do jogo
- main.c - o menu e a partida
- Makefile - compilação
