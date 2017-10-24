#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void comb_sort(int *, unsigned long, int numThreads);
void imprimir_vetor(int *, unsigned long);
int validador(int *, unsigned long);

int main(int argc, char *argv[])
{
  struct timeval timevalA;
        struct timeval timevalB;

  int *vetor = NULL, numThreads;
  unsigned long tam, i = 0;

	if (argc != 3) {
		printf("Necessita de 2 elementos\n");
		exit(EXIT_FAILURE);
	}

  tam = atoi(argv[1]);
  numThreads = atoi(argv[2]);
  
  if(!(numThreads > 0)){
		printf("Número de threads deve ser > 0\n");
		exit(EXIT_FAILURE);
	}

  if (!(vetor = (int *) malloc(sizeof(int) * tam))) {
    printf("Erro ao alocar memória\n");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
  for (i = 0; i < tam; i++) {
    *(vetor + i) = random() % 10000;
  }

  gettimeofday(&timevalA, NULL);
  comb_sort(vetor, tam, numThreads);
  gettimeofday(&timevalB, NULL);

  printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);

  printf("Ordenado: %d\n", validador(vetor, tam));
  //imprimir_vetor(vetor, tam);

  free(vetor);
  return EXIT_SUCCESS;
}

void comb_sort(int *vetor, unsigned long tam, int numThreads)
{
  long i, j, d;
  int intervalo, trocado = 1;
  int aux;

  intervalo = tam;

  
  while(intervalo > 1 || trocado == 1){
    intervalo = intervalo * 10 / 13;

		if (intervalo == 9 || intervalo == 10){
			intervalo = 11;
		}

		if (intervalo < 1){
			intervalo = 1;
		}

		trocado = 0;

    #pragma omp parallel for schedule(static) num_threads(numThreads) shared(vetor, intervalo, trocado, tam) private(aux, i)
		for(i=0; i < tam - intervalo; i++){
			if (vetor[i] > vetor[i+intervalo]){
				aux = vetor[i];
     		vetor[i] = vetor[i+intervalo];
				vetor[i+intervalo] = aux;
        if (trocado == 0){
        #pragma omp critical
      	trocado = 1;
        }
      }
		}
	}
}

void imprimir_vetor(int *vetor, unsigned long tam)
{
  unsigned long i;
  for (i = 0; i < tam; i++) {
    printf("%d\t ", vetor[i]);
  }
  printf("\n");
}

int validador(int *vetor, unsigned long tam)
{
  unsigned long i;
  for (i = 0; i < tam - 1; i++) {
    if (vetor[i] > vetor[i + 1]) {
      return 0;
    }
  }
  return 1;
}
