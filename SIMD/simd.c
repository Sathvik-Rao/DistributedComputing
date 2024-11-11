#include <stdio.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <stdlib.h>
#pragma GCC target("avx2")

unsigned  int  n = 80000;

double regular_method(double *x, double *y)
{
	double a=0.0;
	double b;
	double c;
    for(int i=0;i<40000;i++)
    {
	for (int j=0;j<n;j++)
	
		{	
		    b=(x[j]*y[j]);
		    c=(x[j]*y[j]);
			a=a+(b*c);
		}
    }
	
	return a;
}



double simd_vectorized_code(double *x, double *y)
{
    __m256d simdA;
    __m256d simdB;
    __m256d sum=_mm256_set_pd(0.0, 0.0, 0.0, 0.0);
    __m256d res1;
    __m256d res;
    __m256d res2;
    unsigned  int i;
    
for(int k=0;k<40000/8;k++)
  {
    for(i=0;i<n;i=i+4)
    {
        simdA = _mm256_setr_pd(x[i], x[i+1], x[i+2], x[i+3]);
        simdB = _mm256_setr_pd(y[i], y[i+1], y[i+2], y[i+3]);
        
        res = _mm256_mul_pd(simdA, simdB);
        res1=_mm256_mul_pd(simdA, simdB);
        res2=_mm256_mul_pd(res,res1);
        sum=_mm256_add_pd(sum,res2);    
}
    }
    return (sum[0]+sum[1]+sum[2]+sum[3])*8;
}



int main()
{
	double x[n];
	double y[n];
	for ( int i = 0; i < n; i++)
    {
    		    
                x[i] = 5.0; 
                y[i] = 4.0;
	}

    clock_t reg_start=clock();
	printf("\n Result of regular_method is =%.3f",regular_method(x,y));
    clock_t reg_end=clock();
    double reg_time=0.0;
	reg_time=reg_time+(double)(reg_end-reg_start);
	reg_time=reg_time/CLOCKS_PER_SEC;
	printf("\n Time taken for regular_method using non-SIMD is %.2f seconds.\n",reg_time);
	
	
	clock_t simd_start=clock();
	printf("\n Result of simd_vectorized_code is =%.2f",simd_vectorized_code(x,y));
	clock_t simd_end=clock();
	double simd_time=0.0;
	simd_time=simd_time+(double)(simd_end-simd_start);
	simd_time=simd_time/CLOCKS_PER_SEC;
	printf("\n Time taken for simd_vectorized_code using SIMD is %.2f seconds.",simd_time);

	printf("\n\nSIMD method  is %.2f faster than non-SIMD code snippet",reg_time/simd_time);
	return 0;
}

