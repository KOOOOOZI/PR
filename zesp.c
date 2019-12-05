#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

struct zespolona
{
	double re;
	double im;
};
int main(int argc,char* argv[])
{
	int N = 200;
	int x_max = 180;
	int y_max = 120; 
	int *tab = calloc(x_max * y_max , sizeof(int));
	#pragma omp parallel for
		for(int i = 0; i < x_max*y_max;i++)
		{
			int x = i % x_max;
			int y = i / x_max;
			struct zespolona p;
			p.re = (3.0*x)/x_max -2.0;
			p.im = (2.0*y)/y_max - 1.0;

			struct zespolona z;
			z.re = 0;
			z.im = 0;
			for(int n; n < N;n++)
			{
				struct zespolona z1;
			        z1.re = (z.re*z.re)-(z.im*z.im);
		       		z1.im = 2 * z.re * z.im;
		 		
				z1.re += p.re;
				z1.im += p.im;		
				if(z1.re * z1.re + z1.im*z1.im < 4)
				{
					tab[x*x_max+y] = 1;	
				}
			}
		}
	
	for(int i = 0; i < x_max;i++)
	{
		for(int j = 0; j < y_max;j++)
		{
			if(tab[i*x_max+j] == 1) printf(" ");
			else printf("#");
		}
		printf("\n");
	}
	return 0;
}
