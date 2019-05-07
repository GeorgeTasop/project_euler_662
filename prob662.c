#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int fibbonacci(int);
void k_from_n(int *end, int *start, int n, int x, int y, int *pp);

int main(int argc, char const *argv[])
{
	int i=2, j, k, f;
	int triads[300];
	int *ind, *end;
	ind = triads;
	f = fibbonacci(i);
	//while ( f <= 8){ 	//Gia to (10,10)
	while ( f <= 7){ 		// Gia to (3,4)
		
		printf("Fibonacci %d = %d\n", i, f);
		
		for (j=0;j<=f;j++){
			for (k=0;k<=f;k++){
				if (k*k + j*j == f*f){
					*ind = k;
					ind++;
					*ind = j;
					ind++;
					*ind = f;
					ind++;
				}
			}
		}
		i++;
		f = fibbonacci(i);
	}
	*ind = -1;
	ind = triads;
	i=1;
	int count = 0;
	while(*ind != -1){
		printf("%d ", *ind);
		ind++;
		if (i%3==0){
			printf("\n");
			count++;
		}
		i++;
	}

	end = ind - 3;
	*ind = 1000000;
	*(ind + 1)= 1000000;
	*(ind + 2) = 1000000;

	// for(i=0;i<3;i++){
	// 	k_from_n(end, i, count);
	// }
	//------------------Number of steps
	// printf("PRINTING VALUES IN ADDRESS START: \n");
	// printf("%d,%d,%d,%d,%d,%d\n", *(triads),*(triads+1), *(triads+2), *(triads+3), *(triads+4), *(triads+6));
	
	printf("\nCalculating number of steps...\n");
	clock_t begin = clock();

	int x = 7;
	int y = 7;
	int paths = 0;
	int steps;
 	#pragma omp parallel for schedule(dynamic) private(steps) reduction(+:paths)
 	for (steps=1;steps<=x+y;steps++){
		k_from_n(end, triads, steps, x, y, &paths);
		// printf("steps = %d\n", steps);
	}	
	printf("Paths: %d\n", paths);
	
	
	clock_t end_t = clock();
	double time_spent = (double)(end_t - begin) / CLOCKS_PER_SEC;
	printf("\nTime spent: %f\n", time_spent);
	return 0;
}

/*			   Πινακας

	   start-->	1 0 1 
				0 1 1 
				2 0 2 
				0 2 2 
				3 0 3 
				0 3 3 
				5 0 5 
				4 3 5 
				3 4 5 
		 end--> 0 5 5 
		 		∞ ∞ ∞
				
				
				

*/

void k_from_n(int *end, int *start, int n, int x, int y, int *pp){
	
	printf("\n-----------THREAD %d: WITH %d STEPS----------\n", omp_get_thread_num(), n);
	int *indx[n+1];
	int p = 0;
	int sum_x, sum_y;

	//---------Calculating Bounds---------------------------------
	int upper_bound, lower_bound;
	upper_bound = (x+y)/n;
	lower_bound = x + y - n + 1;
	if (lower_bound <= 1){
		lower_bound = *(start + 2) + 1;
	}
	//lower_bound = 5;

	// indx[0] = start + 2;
	// while (indx[0] != end + 5){
	// 	if (*indx[0]>=upper_bound){
	// 		printf("*indx[0] = %d\n", *indx[0]);
	// 		start = indx[0] - 2; 
	// 		break;
	// 	}
	// 	else{
	// 		indx[0] += 3;
	// 	}
	// }
	printf("upper bound = %d, start = %d\n",upper_bound, *start );
	printf("lower bound = %d\n", lower_bound);
	//----------------------------------------------------------------

	for (int a=0; a<n+1; a++) {
		// indx[a]=end;
		indx[a]=start;
	}
	
	// while (indx[n]==end){
	while (indx[n]==start){
	

		// for (int d=0;d<n;d++){
		// 	//printf("With %d steps: ",n );
		// 	printf("x = %d, y = %d \n", *indx[d], *(indx[d] - 1));
		// }
		sum_y = 0;
		sum_x = 0;
		for (int d=0;d<n;d++){

			// sum_x += *indx[d];
			// sum_y += *(indx[d] - 1);
			sum_x += *indx[d];
			sum_y += *(indx[d] + 1);
			//printf("x[%d]= %d, y[%d]= %d  ",d, *indx[d], d, *(indx[d] + 1) );
		}
		
		if (sum_x == x && sum_y == y){
			// if (n!=7) printf("sumx = %d, sumy = %d\n",sum_x, sum_y );
			(*pp)++;

			// if (n!=7) {for (int d=0;d<n;d++){
			// 	printf("x = %d, y = %d \n", *indx[d], *(indx[d] + 1));
			// }
			// printf("\n");}
			
		}

		indx[0] += 3;
		
	  	// while(indx[p]==start-2) {
		// while(indx[p]==end+3) {
		//printf("mphka sto prwto\n");
		//printf("*(indx[p] + 2)= %d\n", *(indx[p] + 2));
		while(*(indx[p] + 2)>lower_bound) {
			//printf("mphka, p = %d\n", p);
	    	// indx[p]=end;
	    	// indx[++p] -= 3;
	    	indx[p]=start;
	    	indx[++p] += 3; 
	    	// if(indx[p]!=start-2) {
	    	// if(indx[p]!=end+3) {
	    	if(*(indx[p] + 2)<=lower_bound) {
	      		p=0;
	    	}
	 	 }
	}
	printf("Thread %d: Path till now = %d\n", omp_get_thread_num(), *pp);
	
}





int fibbonacci(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fibbonacci(n-1) + fibbonacci(n-2));
   }
}
