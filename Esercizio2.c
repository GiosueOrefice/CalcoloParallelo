#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

/*SOMMA DELLE RIGHE PARI DI UNA MATRICE  */

int main(int argc, char const *argv[])
{
	int mat[9][9],sum,sumTot=0,idThread,nThreads,i,j,resto,nloc;

	srand(time(NULL));

	for (i = 0; i < 9; i++)
	{
		for(j=0;j<9;j++)
				mat[i][j]=1+rand()%10;
	
	}

	


	#pragma omp parallel for collapse(2) reduction(+:sumTot)
		for ( i = 0; i < 9; i+=2)
		{
			for (j = 0; j < 9; j++)
				sumTot+= mat[i][j];	
		}

	printf("sumTot %d\n", sumTot);

	/* SEQUENZIALE
	sumTot=0;
	for ( i = 0; i < 9; i+=2)
		{
			for (j = 0; j < 9; j++)
			{
				
					sumTot+= mat[i][j];
					
				
			}
		}

	printf("sumTot %d\n", sumTot);

	*/
	return 0;
}
