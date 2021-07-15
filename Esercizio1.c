#include <stdio.h>
#include <omp.h>


/* ESTRAI I VALORI DELLA DIAGONALE PRINCIPALE DI UNA MATRICE E SALVALI IN UN ARRAY. 
   CALCOLA LA SOMMA DEGLI ELEMENTI DELL'ARRAY */
int main(int argc, char const *argv[])
{
	int a[8][8],vet[8];
	int sum= 0,idThread, resto, nloc, step, numThread, sumTot = 0;
	int i;

	for (i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			a[i][j]=j+i+1;
		}
	}


	#pragma omp parellel for private(i)
		for ( i = 0; i < 8; i++)
		{
			vet[i] = a[i][i];
			//printf("%d\n", vet[i]);
		}

	#pragma omp parallel private (idThread,nloc,step,i) reduction(+:sum)
	{
		numThread = omp_get_num_threads();
		idThread = omp_get_thread_num();
		nloc = 8/numThread;
		resto = 8%numThread;

		if (idThread<resto)
		{
			nloc++;
			step=0;
		}
		else step=resto;

		sum = 0;
		for (i = 0; i < nloc; i++)
		{
			sum += vet[i+nloc*idThread+step];
		}

		printf("idThread %d sum %d\n", idThread,sum);
		sumTot+= sum;


	}

	printf("sumTot %d\n", sumTot);
	return 0;
}
