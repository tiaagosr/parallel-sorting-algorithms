#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void comb_sort(int *, unsigned long);
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
	comb_sort(vetor, tam);	
	gettimeofday(&timevalB, NULL);

	printf("%lf\n", timevalB.tv_sec - timevalA.tv_sec + (timevalB.tv_usec - timevalA.tv_usec) / (double) 1000000);

	//imprimir_vetor(vetor, tam);

	free(vetor);
	return EXIT_SUCCESS;
}

void comb_sort(int *vetor, unsigned long tam)
{
	unsigned long i, j;
	int intervalo, trocado = 1;
	int aux;
	
	intervalo = tam;

	while (intervalo > 1 || trocado == 1)
	{
		intervalo = intervalo * 10 / 13;
		if (intervalo == 9 || intervalo == 10) {
			intervalo = 11;
		}
		if (intervalo < 1) {
			intervalo = 1;
		}

		trocado = 0;

		for (i = 0, j = intervalo; j < tam; i++, j++)
		{
			if (vetor[i] > vetor[j])
			{
				aux = vetor[i];
				vetor[i] = vetor[j];
				vetor[j] = aux;
				trocado = 1;
			}
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
