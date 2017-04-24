
	

//This code will help you, and it's fairly self-explanatory:

#include <stdio.h>      /* Standard Library of Input and Output */
#include <math.h>
#include <complex.h>    /* Standard Library of Complex Numbers */
#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif

#define q	3		/* for 2^3 points */
#define N	(1<<q)		/* N-point FFT, iFFT */

 

/* Print a vector of complexes as ordered pairs. */
static void
print_vector(
	     const char *title,
	     complex *x,
	     int n)
{
  int i;
  
 
  printf("%s (dim=%d):", title, n);
  
  //for(i=0; i<n; i++ ) printf(" %5.2f,%5.2f ", x[i].Re,x[i].Im);
  for(i=0; i<n; i++ ) {
	//printf("address of v 0x%x \n",x);
	printf("%5.2f,%5.2fi",creal(x[i]), cimag(x[i]));
	//x++;  
  }
  printf("\n");
  //putchar('\n');
  return;
} 

void
fft( complex *v, int n, complex *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
	//printf("in fft\n");
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    double x,xi,y,yi;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    //print_vector("even", ve, N/2);
    //print_vector("odd", vo, N/2);
    fft( ve, n/2, v );
    fft( vo, n/2, v );
    for(m=0; m<n/2; m++) {
	  //w.Re -> x & 	w.Im -> xi
      x = cos(2*PI*m/(double)n);
      xi = sin(2*PI*m/(double)n);
      //printf("w.Re & w.Im%6f,%6fi\n",x, xi);
      //z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;
      y = x*creal(vo[m]) - xi*cimag(vo[m]);
      //z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;
      yi = x*cimag(vo[m]) + xi*creal(vo[m]);
      
      //v[  m  ].Re = ve[m].Re + z.Re;
      x = creal(ve[m]) + y;
      //v[  m  ].Im = ve[m].Im + z.Im;
      xi = cimag(ve[m]) + yi;
      v[  m  ] = x + xi;
      
      //v[m+n/2].Re = ve[m].Re - z.Re;
      x = creal(ve[m]) - y;
      //v[m+n/2].Im = ve[m].Im - z.Im;
      xi = cimag(ve[m]) - yi;
      v[m+n/2] = x + xi;	
   }
}
return;
}

void
ifft( complex *v, int n, complex *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
	//printf("in fft\n");
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    double x,xi,y,yi;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    //print_vector("even", ve, N/2);
    //print_vector("odd", vo, N/2);
    ifft( ve, n/2, v );
    ifft( vo, n/2, v );
    for(m=0; m<n/2; m++) {
	  //w.Re -> x & 	w.Im -> xi
      x = cos(2*PI*m/(double)n);
      xi = sin(2*PI*m/(double)n);
      //printf("w.Re & w.Im%6f,%6fi\n",x, xi);
      //z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;
      y = x*creal(vo[m]) - xi*cimag(vo[m]);
      //z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;
      yi = x*cimag(vo[m]) + xi*creal(vo[m]);
      
      //v[  m  ].Re = ve[m].Re + z.Re;
      x = creal(ve[m]) + y;
      //v[  m  ].Im = ve[m].Im + z.Im;
      xi = cimag(ve[m]) + yi;
      v[  m  ] = x + xi;
      
      //v[m+n/2].Re = ve[m].Re - z.Re;
      x = creal(ve[m]) - y;
      //v[m+n/2].Im = ve[m].Im - z.Im;
      xi = cimag(ve[m]) - yi;
      v[m+n/2] = x + xi;	
   }

}
return;
}

void fft_pas() {

    double complex z1 = 1.0 + 3.0 * I;
    double complex z2 = 1.0 - 4.0 * I;
    complex v[N], v1[N], scratch[N];
    double x,xi;
    int k;

    //printf("Working with complex numbers:\n\v");

    //printf("Starting values: Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(z1), cimag(z1), creal(z2), cimag(z2));

    double complex sum = z1 + z2;
    //printf("The sum: Z1 + Z2 = %.2f %+.2fi\n", creal(sum), cimag(sum));

    double complex difference = z1 - z2;
    //printf("The difference: Z1 - Z2 = %.2f %+.2fi\n", creal(difference), cimag(difference));

    double complex product = z1 * z2;
    //printf("The product: Z1 x Z2 = %.2f %+.2fi\n", creal(product), cimag(product));

    double complex quotient = z1 / z2;
    //printf("The quotient: Z1 / Z2 = %.2f %+.2fi\n", creal(quotient), cimag(quotient));

    double complex conjugate = conj(z1);
    //printf("The conjugate of Z1 = %.2f %+.2fi\n", creal(conjugate), cimag(conjugate));
    for(k=0; k<N; k++) {
		x = 0.125*cos(2*PI*k/(double)N);
		xi = 0.125*sin(2*PI*k/(double)N);
		z1 = x + xi*I;
		v[k] = z1;
		//printf("%6f,%6fi\n",creal(v[k]), cimag(v[k]));
	}
	//printf("address of v 0x%x \n",&v);
	print_vector("Orig", v, N);
	fft( v, N, scratch );
	print_vector("fft", v, N);
	ifft( v, N, scratch );
	print_vector("ifft", v, N);
    //return 0;
}
