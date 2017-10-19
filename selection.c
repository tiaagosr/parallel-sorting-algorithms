#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void selection_sort(int *, unsigned long);
void imprimir_vetor(int *, unsigned long);

int main(int argc, char *argv[])
{
	struct timeval timevalA;
        struct timeval timevalB;

	int *vetor = NULL;
	unsigned long tam, i = 0;

	if (argc != 2) {
		printf("%s elementos\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	
	tam = atoi(argv[1]);

	if (!(vetor = (int *) malloc(sizeof(int) * tam))) {
		printf("Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));		
	for (i = 0; i < tam; i++) {
		*(vetor + i) = random() % 10000;
	}

	gettimeofday(&timevalA, NULL);
	selection_sort(vetor, tam);	
	gettimeofday(&timevalB, NULL);

	printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);

	//imprimir_vetor(vetor, tam);

	free(vetor);
	return EXIT_SUCCESS;
}

void selection_sort(int *vetor, unsigned long tam)
{
	unsigned long i, j, min;
	int aux;
	
	for (i = 0; i < tam - 1; i++) {
		min = i;
		for (j = i + 1; j < tam; j++) {
			if (vetor[j] < vetor[min]) { 
         			min = j;
			}
 		}
		if (vetor[i] != vetor[min]) {
			aux = vetor[i];
			vetor[i] = vetor[min];
			vetor[min] = aux;
		}
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
