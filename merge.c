#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void merge(int *, unsigned long, unsigned long, unsigned long);
void merge_sort(int *, unsigned long, unsigned long);
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
	merge_sort(vetor, 0, tam - 1);	
	gettimeofday(&timevalB, NULL);

	printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);

	//imprimir_vetor(vetor, tam);

	free(vetor);
	return EXIT_SUCCESS;
}

void merge(int *vetor, unsigned long inicio, unsigned long meio, unsigned long fim) {
	unsigned long com1 = inicio, com2 = meio + 1, comAux = 0;

	int *vetAux = NULL;
	
	vetAux = (int *) malloc(sizeof(int) * (fim - inicio + 1));
 
	while (com1 <= meio && com2 <= fim) {
		if (vetor[com1] <= vetor[com2]) {
			vetAux[comAux] = vetor[com1];
			com1++;
		} else {
			vetAux[comAux] = vetor[com2];
			com2++;
		}
		comAux++;
	}
 
	while (com1 <= meio) {
		vetAux[comAux] = vetor[com1];
		comAux++;
		com1++;
	}
	
	while (com2 <= fim) { 
		vetAux[comAux] = vetor[com2];
		comAux++;
		com2++;
	}
 
	for (comAux = inicio; comAux <= fim; comAux++) {
		vetor[comAux] = vetAux[comAux - inicio];
	}
	
	free(vetAux);
}

void merge_sort(int *vetor, unsigned long inicio, unsigned long fim)
{
	unsigned long meio;
	if (inicio >= fim) {
		return;
	}

	meio = (fim + inicio) / 2;
	merge_sort(vetor, inicio, meio);
	merge_sort(vetor, meio + 1, fim);
	merge(vetor, inicio, meio, fim);
}

void imprimir_vetor(int *vetor, unsigned long tam)
{
	unsigned long i;
	for (i = 0; i < tam; i++) {
		printf("%d\t", vetor[i]);
	}
	printf("\n");
}
