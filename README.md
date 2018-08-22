# ParallelBucketSort

## Detalhes

  - Foi considerado Vetores de 3 Tamanhos:
    - __1.000__
    - __10.000__
    - __20.000__
  - Vetores do Tipo Inteiro, Positivo e gerados de forma randômica com a função _rand()_. 
  - Maior valor do vetor é definido por __RAND_MAX__
  - Desenvolver com _Pthreads_ e _OpenMP_
  - Executado com 1, 2, 4 e 8 threads

## Resultados

### Testes utilizando _OpenMP_

| Tamanho | 1 Thread | 2 Threads | 4 Threads | 8 Threads |
| ------- | -------- | --------- | --------- | --------- |
| 1000 | 0.002507s | 0.001473s | 0.000957s | 0.000797s |
| 10000 | 0.276220s | 0.087181s | 0.027309s | 0.016111s |
| 20000 | 1.089479s | 0.320982s | 0.091211s | 0.054764s |

### Testes utilizando _Pthreads_

| Tamanho | 1 Thread | 2 Threads | 4 Threads | 8 Threads |
| ------- | -------- | --------- | --------- | --------- |
| 1000 | 0.002423s | 0.000840s | 0.000475s | 0.000658s |
| 10000 | 0.259986s | 0.061345s | 0.015234s | 0.008425s |
| 20000 | 1.159037s | 0.286732s | 0.067732s | 0.030013s |

