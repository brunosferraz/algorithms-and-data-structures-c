#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H

/*!
 * Tipo do elemento armazenado na lista
 */
typedef char lista_item;

struct lista_no_struct {
   lista_item item;
   struct lista_no_struct* prox;
   struct lista_no_struct* ant;
};
typedef struct lista_no_struct lista_no;

struct lista_struct {
   int (*compara)(lista_item i1, lista_item i2);
   unsigned quantidade;
   lista_no* sentinela;
};
typedef struct lista_struct lista;

/*! Iterador da lista, faz referencia a um elemento
 *
 */
struct lista_iterador_struct {
   lista_no* p;
   lista* l;
};
typedef struct lista_iterador_struct lista_iterador;

/*! Inicializa uma lista ordenada. Primeiro procedimento a ser
 *  chamado para permitir o uso da lista.
 *
 * \param l Endereco da lista a ser inicializada
 * \param m Funcao que compara dois elementos da lista.
 * 			Esta função deve retornar:
 * 			-1, caso i1<i2;
 * 			0, caso i1=i2;
 * 			1, caso i1>i2.
 *
 */
void inicializa(lista* l, int (*cmp)(lista_item i1, lista_item i2));

/*! Desaloca uma lista. Ultimo procedimento a ser chamado.
 *
 * \param l Endereco da lista a ser desalocada
 *
 */
void destroi(lista* l);

/*!
 * Verifica se uma lista esta ou nao vazia.
 *
 * \param d Endereço da lista
 * \return Verdadeiro (diferente de zero) se a lista estiver vazia
 *
 */
int vazia(lista* l);

/*! Insere um determinado elemento na lista ordenada. O novo elemento será inserido antes dos
 * elementos maiores ou iguais.
 *
 * \param l Endereco da lista
 * \param item Elemento a ser inserido
 *
 */
void insere(lista* l, lista_item item);

/*! Remove todas as ocorrencias de um determinado elemento na lista ordenada, se existirem.
 *
 * \param l Endereco da lista
 * \param item Elemento a ser removido
 *
 */
void retira(lista* l, lista_item item);

/*!
 * Retorna um iterador para o elemento do inicio da lista, se houver.
 *
 * \param l Endereço da lista
 * \return Iterador para o menor elemento da lista, se houver
 *
 */
lista_iterador primeiro(lista* l);

/*!
 * Retorna um iterador para o elemento do final da lista, se houver.
 *
 * \param l Endereço da lista
 * \return Iterador para o maior elemento da lista, se houver
 *
 */
lista_iterador ultimo(lista* l);

/*!
 * Retorna o elemento referenciado pelo iterador, se houver
 *
 * \param i Iterador
 * \return Elemento da lista, se houver
 *
 */
lista_item elemento(lista_iterador i);

/*!
 * Avanca o iterador e retorna verdadeiro caso nao seja o final da lista
 *
 * \param i Endereco do Iterador
 * \return Falso caso nao tenha um proximo elemento
 *
 */
int proximo(lista_iterador* i);

/*!
 * Retrocede o iterador e retorna verdadeiro caso nao seja o inicio da lista
 *
 * \param i Endereco do Iterador
 * \return Falso caso nao tenha um elemento anterior
 *
 */
int anterior(lista_iterador* i);

/*!
 * Retorna se o elemento referenciado pelo iterador existe
 *
 * \param i Iterador
 * \return Falso caso o iterador nao aponte para um elemento
 *
 */
int acabou(lista_iterador i);

#endif