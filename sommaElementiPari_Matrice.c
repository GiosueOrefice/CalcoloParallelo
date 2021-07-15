#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


/*SOMMA DEGLI ELEMENTI PARI DI UNA MATRICE (MATRICE CONSIDERATA COME ARRAY RIGA, QUINDI 0,2,4,ecc..) */
int main(int argc, char const *argv[])
{
	int *mat,N=8;
	int i,j;
	int pari=0,sumTOT=0;;

	mat = (int *) malloc((N*N)*sizeof(int));
	


	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			*(mat+i*N+j) = i+j+1;
		}
	}

	#pragma omp parallel for private(i,j) shared(mat) reduction(+:sumTOT,pari) collapse(2)
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
		 
				if((pari%2) == 0 )
					sumTOT += *(mat+i*N+j);

				pari++;
			
			}
		}


	printf("%d\n", sumTOT);


	/* SEQUENZIALE
	sumTOT =0;
	pari = 0;
	for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				if((pari %2) ==0 )
					sumTOT += *(mat+i*N+j);

					pari++;
			}
		}


	*/


	return 0;
}