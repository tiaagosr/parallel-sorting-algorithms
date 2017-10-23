#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void heap_sort(int *, unsigned long);
void imprimir_vetor(int *, unsigned long);
int validador(int *, unsigned long);

int numThreads;

int main(int argc, char *argv[])
{
	struct timeval timevalA;
        struct timeval timevalB;

	int *vetor = NULL;
	unsigned long tam, i = 0;

	if (argc != 3) {
		printf("%s elementos, necessita de 2\n", (argv[0]-1));
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
	heap_sort(vetor, tam);
	gettimeofday(&timevalB, NULL);

	printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);

	//imprimir_vetor(vetor, tam);

	free(vetor);
	return EXIT_SUCCESS;
}

void heap_sort(int *vetor, unsigned long tam)
{
	unsigned long i, pai, filho, aux;

	i = tam / 2;

	for ( ; ; ) {
		if (i > 0) {
			i--;
			aux = vetor[i];
		} else {
			tam--;
			if (tam == 0) {
				return;
			}
      		aux = vetor[tam];
      		vetor[tam] = vetor[0];
  		}
		pai = i;
		filho = i * 2 + 1;

		while (filho < tam) {
			if ((filho + 1 < tam)  &&  (vetor[filho + 1] > vetor[filho])) {
				filho++;
			}
			if (vetor[filho] > aux) {
     			vetor[pai] = vetor[filho];
     			pai = filho;
     			filho = pai * 2 + 1;
      		} else {
				break;
			}
		}
		vetor[pai] = aux;
	}
}

void imprimir_vetor(int *vetor, unsigned long tam)
{
	unsigned long i;
	for (i = 0; i < tam; i++) {
		printf("%d\t", vetor[i]);
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
