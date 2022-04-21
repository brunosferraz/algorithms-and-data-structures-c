#ifndef STACK_H
#define STACK_H

typedef char T;

typedef struct {
   T v[MAX];
   int top;
} stack;

// Recebe um ponteiro da estrutura pilha. Inicializa a pilha.
void initialize(stack *s);

// Recebe um ponteiro da estrutura pilha. Devolve 1 caso esteja vazia e 0 caso contrario.
int empty(stack *s);

// Recebe um ponteiro da estrutura pilha. Devolve 1 caso esteja cheia e 0 caso contrario.
int full(stack *s);

// Recebe um ponteiro da estrutura pilha e um elemento. Insere o elemento na pilha.
void push(stack *s, T data);

// Recebe um ponteiro da estrutura pilha e uma variavel para armazenar o valor removido.
// Remove o elemento da pilha, devolve 1 se a operacao foi feita corretamente e 0 caso contrario
int pop(stack *s, T *data);

#endif