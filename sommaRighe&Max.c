#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

/*Calcola la somma di ogni riga e salvala in un array e infine trova il massimo valore presente nell'array */

int main(int argc, char const *argv[])
{
	int *mat,*arr,sumTot,max;
	int N,M;
	int i,j;
	int numThreads;
	numThreads = 4;
	N=3; M=3;

	mat = (int *) malloc((N*M)*sizeof(int));
	arr = (int *) malloc(N*sizeof(int));

	srand(time(NULL));

	//GENERA VALORI CASUALI DA 1 A 10
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			*(mat+i*M+j) = 1+rand()%10;
		}
		arr[i] = 0;
	}


	/* STAMPA
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			printf("%d ",*(mat+i*M+j));
		}
		printf("\n");
	}
	*/
	
	omp_set_num_threads(numThreads);

	double t0 = omp_get_wtime();
	#pragma omp parallel for private(i,j) reduction(+: arr[: N]) collapse (2)
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			arr[i] += *(mat+i*M+j);
		}


	}
	double t1 = omp_get_wtime();
	printf("\nTEMPO %e\n",t1-t0);
	
	printf("Array\n");
	for(i=0;i<N;i++)
		printf("%d ",*(arr+i));


	max=*(arr+0);

	t0 = omp_get_wtime();
	#pragma omp parallel for private(i) reduction(max: max)
	for(i=1;i<N;i++){
		if(*(arr+i)>max)
			max = *(arr+i);		
	}

	t1 = omp_get_wtime();
	printf("\nTEMPO %e\n",t1-t0);
	printf("\nmax %d\n",max);

	return 0;
}