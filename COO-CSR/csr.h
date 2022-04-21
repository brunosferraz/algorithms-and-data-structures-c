#ifndef CSR_H
#define CSR_H

/*! Troca duas posicoes de um vetor.
 *
 * \param v vetor
 * \param i primeira posicao
 * \param i segunda posicao
 *
 */
void swap(int v[], int i, int j);

/*! Procedimento auxiliar do coo_sort() corrige a arvore heap.
 *
 * \param v_row vetor de linhas
 * \param v_col vetor de colunas
 * \param v_data vetor de dados
 * \param k indice violando a heap
 * \param size tamanho do vetor de coordenadas
 *
 */
void fixDown(int v_row[], int v_col[], int v_data[], int k, int size);

/*! Ordena o vetor de coordenadas a partir do vetor v_row.
 *
 * \param v_row vetor de linhas
 * \param v_col vetor de colunas
 * \param v_data vetor de dados
 * \param size tamanho do vetor de coordenadas
 *
 */
void coo_sort(int v_row[], int v_col[], int v_data[], int size);

/*! Converte o vetor de coordenadas para CSR.
 *
 * \param v_row vetor de linhas
 * \param v_col vetor de colunas
 * \param v_data vetor de dados
 * \param v_row_csr vetor que recebe as posicoes dos elementos em v_row
 * \param max_row quantidade de elementos de v_row_csr (linhas da matriz + 1)
 *
 */
void coo_to_csr(int v_row[], int v_col[], int v_data[], int v_row_csr[], int max_row);

/*! Busca um elemento da matriz no vetor CSR.
 *
 * \param i linha de busca
 * \param j coluna de busca
 * \param v_data vetor de dados
 * \param v_data vetor de colunas
 * \param v_row_csr vetor CSR
 * \param size quantidade de elementos em v_row_csr
 * \return elemento e 0 caso não seja encontrado
 *
 */
int csr_search(int i, int j, int v_data[], int v_col[], int v_row_csr[], int size);

#endif