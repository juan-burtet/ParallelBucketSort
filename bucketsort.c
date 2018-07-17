/*
### Implementar o Algoritmo de Ordenação Bucket Sort
  - Considerar Vetores de 3 Tamanhos:
    - __1.000__
    - __10.000__
    - __20.000__
  - Vetores do Tipo Inteiro, Positivo e gerados de forma randômica com a função _rand()_. 
  - Maior valor do vetor é definido por __RAND_MAX__
  - Desenvolver com _Pthreads_ e _OpenMP_
    - Executar com 1, 2, 4 e 8 threads
  - Resultado dos tempos de execução em PDF
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/** Struct usada para armazenar cada array
	*/
typedef struct{
	int *array;
	size_t size;
}ArrayStruct;


/** Função que faz o bucket sort utilizando openmp
	* @param array - vetor a ser ordenado
	* @param size - tamanho do vetor
	* @param max_value - maior valor do vetor
	* @param n_threads - quantidade de threads
	* @return vetor ordenado
	*/
int *bucket_sort_openmp(int *array, size_t size, int max_value, int n_threads){
	ArrayStruct *n_array = NULL;
	int *sort_array = NULL;

	// aloca os vetores para serem ordenados
	n_array = allocate_arrays(n_threads);


	// retorna o vetor ordenado
	return sort_array;
}//bucket_sort_openmp

/** Função que aloca os arrays para utilizar os baldes
	*	@param n_arrays - Quantidade de arrays a serem retornados
	* @return n vetores
	*/
ArrayStruct *allocate_arrays(int n_arrays){
	ArrayStruct *arrays;

	arrays = (ArrayStruct *) malloc(n_arrays * sizeof(ArrayStruct));
	for(int i = 0; i < n_arrays; i++){
		arrays[i].array = NULL;
		arrays[i].size = 0;
	}//for

	return arrays;
}//allocate_arrays

/** Função que retorna para qual balde o valor vai
	* @param value - valor passado
	* @param max - valor maximo
	* @param n_buckets - quantidade de baldes
	* @return indice de qual vetor
	*/
int get_bucket(int value, int max, int n_buckets){
	return (int) (value)/(max/n_buckets);
}//get_bucket