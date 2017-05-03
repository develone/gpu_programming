/* Factored discrete Fourier transform, or FFT, and its inverse iFFT */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define q	8		/* for 2^3 points */
#define N	(1<<q)		/* N-point FFT, iFFT */

typedef float real;
typedef struct{real Re; real Im;} complex;

#ifndef PI
# define PI	M_PI
#endif


/* Print a vector of complexes as ordered pairs. */
static void
print_vector(
	     const char *title,
	     complex *x,
	     int n)
{
  int i;
  printf("%s (dim=%d):", title, n);
  for(i=0; i<n; i++ ) printf(" %5.2f,%5.2f ", x[i].Re,x[i].Im);
  putchar('\n');
  return;
}


/* 
   fft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute fft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute fft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = -sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */
void
fft( complex *v, int n, complex *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
    for(m=0; m<n/2; m++) {
      w.Re = cos(2*PI*m/(double)n);
      w.Im = -sin(2*PI*m/(double)n);
      z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
      z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
      v[  m  ].Re = ve[m].Re + z.Re;
      v[  m  ].Im = ve[m].Im + z.Im;
      v[m+n/2].Re = ve[m].Re - z.Re;
      v[m+n/2].Im = ve[m].Im - z.Im;
    }
  }
  return;
}

/* 
   ifft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute ifft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute ifft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */
void
ifft( complex *v, int n, complex *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    ifft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    ifft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
    for(m=0; m<n/2; m++) {
      w.Re = cos(2*PI*m/(double)n);
      w.Im = sin(2*PI*m/(double)n);
      z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
      z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
      v[  m  ].Re = ve[m].Re + z.Re;
      v[  m  ].Im = ve[m].Im + z.Im;
      v[m+n/2].Re = ve[m].Re - z.Re;
      v[m+n/2].Im = ve[m].Im - z.Im;
    }
  }
  return;
}
int octave_write_32(const char * fn,complex * d_ptr, int sz) {
	 
	FILE *subfileptr;
	int i;
	float mag[sz],*ptr;
	ptr=&mag[0];
	for(i=0;i<sz;i++) {
		//mag[i]= sqrt(d_ptr[i].Re*d_ptr[i].Re+d_ptr[i].Im*d_ptr[i].Im);
		mag[i]= (float)d_ptr[i].Re;
	}
	subfileptr = fopen(fn,"w");
	printf("file name %s data ptr 0x%x size %d \n",fn, d_ptr,sz);
	if (NULL == subfileptr) {
		/*
		fprintf(stderr, "Could not open red for writing\n");
		perror("RED-WR:");
		exit(EXIT_FAILURE);
		*/
		return(0);
	}
 
	if (sz != (int)fwrite(ptr,  sizeof(float), sz, subfileptr)) {
		fprintf(stderr, "Write of red failed\n"); perror("RED:");
		exit(EXIT_FAILURE);
	}
	
 	
	fclose(subfileptr);
	
	return(1);
}


int
main(void)
{
  complex v[N], v1[N], scratch[N];
  int k, freq1, freq2, num_periods, num_tsteps;
  const char *octave_output_file;
  float period1;
  double tstep;
  double w1;
	freq1 = 400; 
	freq2 = 2500; 
	period1 = (float)1 / freq1; 
	w1 = 2 * PI * freq1;
	num_periods = 48;  
	num_tsteps = N;
	
	tstep = ((num_periods * period1) / (double)num_tsteps); 
	printf(" %10.12f %f %f \n",PI,w1,tstep);
  /* Fill v[] with a function of known FFT: */
  for(k=0; k<N; k++) {
	  v[k].Im = 0.0;
	  //v[k].Im = sin(w1*k*tstep);
	  v[k].Re = sin(w1*k*tstep);
	  
	  //printf(" %f , %f",k*tstep,v[k].Re);
	  //v[k].Re = sin(w1)*k/(double)N;
    //v[k].Re = 0.75*cos(80*2*PI*k/(double)N)*(0.25*cos(20*2*PI*k/(double)N));
    //v[k].Im = 0.75*sin(80*2*PI*k/(double)N)*(0.25*sin(20*2*PI*k/(double)N));
    //v1[k].Re =  0.3*cos(2*PI*k/(double)N);
    //v1[k].Im = -0.3*sin(2*PI*k/(double)N);
  }
  //printf("\n");
  print_vector("Orig", v, N);
  octave_output_file = "orig-out.32t";
  octave_write_32(octave_output_file,v,N);    
  /* FFT, iFFT of v[]: */
  //print_vector("Orig", v, N);
  fft( v, N, scratch );
  //print_vector(" FFT", v, N);
  octave_output_file = "fft-out.32t";
  octave_write_32(octave_output_file,v,N);
  ifft( v, N, scratch );
  octave_output_file = "ifft-out.32t";
  octave_write_32(octave_output_file,v,N);
  //print_vector("iFFT", v, N);

  /* FFT, iFFT of v1[]: */
  /*
  print_vector("Orig", v1, N);
  fft( v1, N, scratch );
  print_vector(" FFT", v1, N);
  octave_output_file = "fft-out.32t";
  octave_write_32(octave_output_file,v,N);
  ifft( v1, N, scratch );
  print_vector("iFFT", v1, N);
  */
  exit(EXIT_SUCCESS);
}
