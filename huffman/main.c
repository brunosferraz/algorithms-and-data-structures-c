#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"

#define MAX_TEXT 500001

typedef struct node_ {
   unsigned char caracter;
   int freq;
   struct node_ *dir, *esq;
} node;

typedef struct {
   unsigned char caracter;
   unsigned char codigo[MAX_ASCII];
} tabFreq;

int compara(Item i1, Item i2) {
   node *nodeA = (node *)i1;
   node *nodeB = (node *)i2;

   if (nodeA->freq < nodeB->freq)
      return -1;
   else if (nodeA->freq == nodeB->freq)
      return 0;
   else
      return 1;
}

/*! Retorna verdadeiro caso seja um nó folha;
 *
 * \param p Endereço do nó.
 * \return Falso caso não seja um nó folha.
 */
int ehFolha(node *p) {
   return p->esq == NULL && p->dir == NULL;
}

/*! Constroi a trie de Huffman.
 *
 * \param root Endereço da raiz da trie.
 * \param freq Vetor com frequência de cada caracter.
 * \return Nova raiz da trie.
 */
node *construirTrie(node *root, int freq[]) {
   pqueue pq;
   initialize(&pq, compara);
   if (!root) {
      for (unsigned char i = 0; i < MAX_ASCII; i++) {
         if (freq[i] > 0) {
            node *n = (node *)malloc(sizeof(node));
            n->caracter = i;
            n->freq = freq[i];
            n->dir = n->esq = NULL;
            insert(&pq, n);
         }
      }
   }

   while (size(&pq) > 1) {
      node *x = removeMin(&pq);
      node *y = removeMin(&pq);
      node *parent = (node *)malloc(sizeof(node));
      parent->freq = x->freq + y->freq;
      parent->esq = x;
      parent->dir = y;
      insert(&pq, parent);
   }

   return removeMin(&pq);
}

/*! Destroi a trie de Huffman.
 *
 * \param root Endereço da raiz da trie.
 */
void destruirTrie(node *root) {
   if (root) {
      destruirTrie(root->esq);
      destruirTrie(root->dir);
      free(root);
   }
   return;
}

/*! Constroi o código correspondente de cada caracter.
 *
 * \param t Endereço da tabela de frequência.
 * \param root Endereço da raiz da trie.
 * \param arr Vetor para armazenar os códigos.
 * \param tam Tamanho de cada código.
 */
void construirCodigo(tabFreq *t, node *root, int arr[], int tam) {
   if (root->esq) {
      arr[tam] = 0;
      construirCodigo(t, root->esq, arr, tam + 1);
   }

   if (root->dir) {
      arr[tam] = 1;
      construirCodigo(t, root->dir, arr, tam + 1);
   }

   if (ehFolha(root)) {
      t[root->caracter].caracter = root->caracter;
      int i = 0;
      for (i = 0; i < tam; i++)
         t[root->caracter].codigo[i] = arr[i] + '0';
      t[root->caracter].codigo[i] = '\0';
   }
}

/*! Codifica o texto correspondente.
 *
 * \param t Endereço da tabela de frequência.
 * \param texto Vetor do texto a ser comprimido.
 * \param textoComprimido Vetor para armazenar o texto comprimido.
 * \return Tamanho do texto comprimido em bits.
 */
int codifica(tabFreq *t, unsigned char texto[], unsigned char textoComprimido[]) {
   int size = 0;
   for (int i = 0; texto[i] != '\0'; i++)
      for (int j = 0; t[texto[i]].codigo[j] != '\0'; j++, size++) {
         textoComprimido[size] = t[texto[i]].codigo[j];
      }
   textoComprimido[size] = '\0';

   return size;
}

int main() {
   unsigned char letter;
   unsigned char texto[MAX_TEXT];
   unsigned char *textoComprimido = (unsigned char *)malloc(MAX_TEXT * 5 * sizeof(unsigned char));
   int freq[MAX_ASCII];
   int codigo[MAX_ASCII];

   tabFreq t[MAX_ASCII];
   node *root = 0;

   int i;
   for (i = 0; i < MAX_ASCII; i++)
      freq[i] = 0;
   for (i = 0; scanf("%c", &letter) != EOF; i++) {
      freq[letter] += 1;
      texto[i] = letter;
   }
   texto[i] = '\0';

   root = construirTrie(root, freq);
   construirCodigo(t, root, codigo, 0);
   printf("%d\n", codifica(t, texto, textoComprimido));
   destruirTrie(root);
   free(textoComprimido);
}