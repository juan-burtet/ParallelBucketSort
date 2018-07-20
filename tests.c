// tests.c
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "bucketsort.h"

#define RANDOM_MAX 256

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
*/


int *random_array(size_t size);
void test_openmp(int *array, size_t size);
void test_pthreads(int *array, size_t size);
int is_sort(int *sort, size_t size);
void print_array(int *array, size_t size);


int main(void){
  int *array1K = NULL;
  int *array10K = NULL;
  int *array20K = NULL;

  // inicializa a seed
  srand( (unsigned) time(NULL) );

  // cria os vetores
  array1K = random_array(1000);
  array10K = random_array(10000);
  array20K = random_array(20000);

  // faz os testes em OpenMP
  printf("----------- TESTES OPENMP ------------\n");
  printf("--------------------------------------\n");
  test_openmp(array1K, 1000);
  test_openmp(array10K, 10000);
  test_openmp(array20K, 20000);

  // faz os testes em OpenMP
  printf("---------- TESTES PTHREADS -----------\n");
  printf("--------------------------------------\n");
  test_pthreads(array1K, 1000);
  test_pthreads(array10K, 10000);
  test_pthreads(array20K, 20000);

  // Libera a memória
  free(array1K);
  free(array10K);
  free(array20K);

  return 0;
}//main

/** Função que alloca um vetor de números aleatórios de tamanho "size"
  * @param size - tamanho do vetor
  */
int *random_array(size_t size){
  int *array = malloc(size * sizeof(int));

  for(size_t i = 0; i < size; i++)
    array[i] = (rand() % RANDOM_MAX);

  return array;
}//random_array

/** Testa a ordenação utilizando OpenMP com 1,2,4 e 8 threads
  * @param array - vetor a ser ordenado
  * @param size - tamanho do vetor
  */
void test_openmp(int *array, size_t size){
  int *sort = NULL;

  printf("| Vetor de tamanho %d:\n", (int) size);
  printf("| | Tempo para ordenação: \n");

  sort = bucket_sort_openmp(array, size, RANDOM_MAX, 1);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  sort = bucket_sort_openmp(array, size, RANDOM_MAX, 2);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  sort = bucket_sort_openmp(array, size, RANDOM_MAX, 4);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  sort = bucket_sort_openmp(array, size, RANDOM_MAX, 8);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  printf("| \n");
}//test_openmp

/** Testa a ordenação utilizando pthreads com 1,2,4 e 8 threads
  * @param array - vetor a ser ordenado
  * @param size - tamanho do vetor
  */
void test_pthreads(int *array, size_t size){
  int *sort = NULL;

  // Mensagem inicial dos testes
  printf("| Vetor de tamanho %d:\n", (int) size);
  printf("| | Tempo para ordenação: \n");

  sort = bucket_sort_pthreads(array, size, RANDOM_MAX, 1);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  sort = bucket_sort_pthreads(array, size, RANDOM_MAX, 2);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  sort = bucket_sort_pthreads(array, size, RANDOM_MAX, 4);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  sort = bucket_sort_pthreads(array, size, RANDOM_MAX, 8);
  if(!is_sort(sort,size)){
    printf("Vetor não ordenado!\n");
    exit(0);
  }//if
  free(sort);

  printf("| \n");
}//test_pthreads

/** Função que teste se o vetor esta ordenado
  * @param sort - vetor
  * @param size - tamanho do vetor
  */
int is_sort(int *sort, size_t size){
  for(size_t i = 1; i < size; i++){
    if (sort[i] < sort[i - 1])
      return 0;
  }
  return 1;
}//is_sort
