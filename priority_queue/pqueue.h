#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdlib.h>

#define MAX 123

typedef void *Item;

typedef struct {
   void *array[MAX];
   int size;
   int (*menor_igual_maior)(Item i1, Item i2);
} pqueue;

// Funções públicas

/*! Inicializa uma fila de prioridade já alocada pelo usuario.
 *
 * \param q Endereco da fila a ser inicializada.
 * \param menor_igual_maior Função que compara dois elementos da fila.
 *          Esta função deve retornar:
 *          -1, caso i1<i2;
 * 			0, caso i1=i2;
 * 			1, caso i1>i2.
 */
void initialize(pqueue *q, int (*menor_igual_maior)(Item i1, Item i2));

/*! Insere um elemento na fila de prioridade;
 *
 * \param q Endereco da fila.
 * \param data Item a ser inserido na fila.
 */
void insert(pqueue *q, void *data);

/*! Retorna o elemento de menor prioridade da fila, função size() deve ser chamada antes.
 *
 * \param q Endereco da fila.
 * \return Elemento de menor prioridade.
 */
void *removeMin(pqueue *q);

/*! Retorna o tamanho do da fila de prioridade
 *
 * \param q Endereco da fila.
 * \return Tamanho da fila.
 */
int size(pqueue *q);

#endif