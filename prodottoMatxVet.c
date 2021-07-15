#include <stdio.h>
#include <omp.h>

/* PRODTTO MATRICE PER VETTORE */

int main(int argc, char const *argv[])
{
	int N=9,M=9;
	int A[N][M],x[N],y[N];
	int i,j;
	for (i = 0; i < N; i++)
	{
		for(j=0; j<M; j++){
			A[i][j]=i+j+1;
		}
		y[i]=0;
		x[i]=i+1;
	}
	


	#pragma omp parallel for collapse(2) private(i,j) reduction(+:y)
		for (i = 0; i < N;i++)
		{
			for(j=0;j<M;j++)
				y[i] += A[i][j]*x[i]; 
		}

	//STAMPA
	for (i = 0; i < N; i++)
		printf("%d\n",y[i]);
			

	return 0;
}