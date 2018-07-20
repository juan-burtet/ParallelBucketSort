// bucketsort.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <pthread.h>
#include "bucketsort.h"

/** Função que faz o bucket sort utilizando openmp
	* @param array - vetor a ser ordenado
	* @param size - tamanho do vetor
	* @param max_value - maior valor do vetor
	* @param n_threads - quantidade de threads
	* @return vetor ordenado
	*/
int *bucket_sort_openmp(int *array, size_t size, int max_value, int n_threads){
	Bucket *buckets = NULL;
	int *sort_array = NULL;
	long double start, final;

	// tempo inicial
	start = omp_get_wtime();

	// aloca os vetores para serem ordenados
	buckets = allocate_buckets(n_threads);

	// aloca o vetor ordenado
	sort_array = malloc(size * sizeof(int));

	// Adicionar os valores aos baldes
	for(size_t i = 0; i < size; i++){
		int index = get_bucket_index(array[i],max_value,n_threads);
		buckets[index] = add_bucket_value(buckets[index], array[i]);
	}//for

	// Divide em N Threads
	omp_set_dynamic(0);
	#pragma omp parallel num_threads(n_threads)
	{
		#pragma omp parallel for
		for(int i = 0; i < n_threads; i++)
			bubble_sort((void *) &buckets[i]);
	}

	// combina todos os valores
	combine_buckets(sort_array, buckets, n_threads);

	// tempo final
	final = omp_get_wtime() - start;

	// imprime o tempo final
	printf("| | | utilizando %d thread(s): %Lf\n", n_threads, final);

	// libera os baldes da memória
	free_buckets(buckets, n_threads);

	// retorna o vetor ordenado
	return sort_array;
}//bucket_sort_openmp

/** Função que faz o bucket sort utilizando pthreads
	* @param array - vetor a ser ordenado
	* @param size - tamanho do vetor
	* @param max_value - maior valor do vetor
	* @param n_threads - quantidade de threads
	* @return vetor ordenado
	*/
int *bucket_sort_pthreads(int *array, size_t size, int max_value, int n_threads){
  pthread_t threads[n_threads];
	Bucket *buckets = NULL;
	int *sort_array = NULL;
	long double start, final;

	// tempo inicial
	start = omp_get_wtime();

	// aloca os vetores para serem ordenados
	buckets = allocate_buckets(n_threads);

	// aloca o vetor ordenado
	sort_array = malloc(size * sizeof(int));

	// Adicionar os valores aos baldes
	for(size_t i = 0; i < size; i++){
		int index = get_bucket_index(array[i],max_value,n_threads);
		buckets[index] = add_bucket_value(buckets[index], array[i]);
	}//for

  // cada thread recebe um balde
	for(int i = 0; i < n_threads; i++)
  	pthread_create(&threads[i], NULL, (void *) bubble_sort, (void *) &buckets[i]);

	// espera as threads acabarem
	for(int i = 0; i < n_threads; i++){
		pthread_join(threads[i], NULL);
	}

	// combina todos os valores
	combine_buckets(sort_array, buckets, n_threads);

	// tempo final
	final = omp_get_wtime() - start;

	// imprime o tempo
	printf("| | | utilizando %d thread(s): %Lf\n", n_threads, final);

	// libera os baldes da memória
	free_buckets(buckets, n_threads);

	// retorna o vetor ordenado
	return sort_array;
}//bucket_sort_pthreads

/** Aloca os baldes na memória
	*	@param n_arrays - Quantidade de arrays a serem retornados
	* @return n vetores
	*/
Bucket *allocate_buckets(int n_arrays){
	Bucket *arrays;

	arrays = (Bucket *) malloc(n_arrays * sizeof(Bucket));
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
int get_bucket_index(int value, int max, int n_buckets){
	return (int) (value)/(max/n_buckets);
}//get_bucket

/** Função que adiciona um valor ao bucket
	* @param array - Balde
	* @param value - valor adicionado ao balde
	* @return Balde com o valor inserido
	*/
Bucket add_bucket_value(Bucket array, int value){
	//printf("size : %d\n", (int) array.size);
	array.array = realloc(array.array, (array.size + 1) * sizeof(int));
	array.array[array.size] = value;
	array.size++;
	return array;
}//add_bucket_value

/** Algoritmo de ordenação Bubble Sort
	* @param array - Struct com o vetor e seu tamanho
	*/
void bubble_sort(void *array){
	Bucket *sort = (Bucket *) array;
	char flag;
	int temp;

	for(size_t i = 0; i < sort->size; ++i){
		flag = 1;

		for(size_t j = 0; j < sort->size - 1 - i; ++j){

			// Se o atual for maior que o próximo, troca
			if(sort->array[j] > sort->array[j+1]){
				flag = 0;
				temp = sort->array[j];
				sort->array[j] = sort->array[j+1];
				sort->array[j+1] = temp;
			}//if

		}//for

		// Se não ouve trocas, está ordenado
		if(flag)
			return;
	}//for
	return;
}//buble_sort

/** Função que combina os baldes no vetor resultado
	* @param sort_array - vetor que vai ficar ordenado
	* @param buckets - vetor de baldes
	* @param n_buckets - quantidade de baldes
	*/
void combine_buckets(int *sort_array, Bucket *buckets, int n_buckets){
	int cont = 0;
	for(int i = 0; i < n_buckets; i++){
		for(size_t j = 0; j < buckets[i].size; j++)
			sort_array[cont++] = buckets[i].array[j];
	}//for
}//combine_buckets

/** Libera os baldes da memória
	* @param buckets - baldes
	* @param n_buckets - quantidade de baldes
	*/
void free_buckets(Bucket *buckets, int n_buckets){
	for(int i = 0; i < n_buckets; i++)
		free(buckets[i].array);
	free(buckets);
}//free_buckets
