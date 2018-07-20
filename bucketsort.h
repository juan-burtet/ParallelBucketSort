// bucketsort.h
#ifndef _BUCKETSORT_H_
#define _BUCKETSORT_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

/** Struct para representar um balde
  * array - vetor
  * size - tamanho do balde
  */
typedef struct {
  int *array;
  size_t size;
}Bucket;

/** Função que faz o bucket sort utilizando openmp
	* @param array - vetor a ser ordenado
	* @param size - tamanho do vetor
	* @param max_value - maior valor do vetor
	* @param n_threads - quantidade de threads
	* @return vetor ordenado
	*/
int *bucket_sort_openmp(int *array, size_t size, int max_value, int n_threads);

/** Função que faz o bucket sort utilizando pthreads
	* @param array - vetor a ser ordenado
	* @param size - tamanho do vetor
	* @param max_value - maior valor do vetor
	* @param n_threads - quantidade de threads
	* @return vetor ordenado
	*/
int *bucket_sort_pthreads(int *array, size_t size, int max_value, int n_threads);

/** Aloca os baldes na memória
	*	@param n_arrays - Quantidade de arrays a serem retornados
	* @return n vetores
	*/
Bucket *allocate_buckets(int n_arrays);

/** Função que retorna para qual balde o valor vai
	* @param value - valor passado
	* @param max - valor maximo
	* @param n_buckets - quantidade de baldes
	* @return indice de qual vetor
	*/
int get_bucket_index(int value, int max, int n_buckets);

/** Função que adiciona um valor ao bucket
	* @param array - Balde
	* @param value - valor adicionado ao balde
	* @return Balde com o valor inserido
	*/
Bucket add_bucket_value(Bucket array, int value);

/** Algoritmo de ordenação Bubble Sort
	* @param array - Struct com o vetor e seu tamanho
	*/
void bubble_sort(void *array);

/** Função que combina os baldes no vetor resultado
	* @param sort_array - vetor que vai ficar ordenado
	* @param buckets - vetor de baldes
	* @param n_buckets - quantidade de baldes
	*/
void combine_buckets(int *sort_array, Bucket *buckets, int n_buckets);

/** Libera os baldes da memória
	* @param buckets - baldes
	* @param n_buckets - quantidade de baldes
	*/
void free_buckets(Bucket *buckets, int n_buckets);

#endif
