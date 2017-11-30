#ifndef _TARGET_H_
#define _TARGET_H_

float *cblas_sgemm_run(float *A ,float *B,float *C, int M,int K,int N); 
float *clblas_sgemm_run(float *A ,float *B,float *C,float *result, int M,int K,int N);
float *cblas_sdot_run(float *A ,float *B,float *C, int N);
float *clblas_sdot_run(float *A ,float *B, float *C,float *result, int N);
float *clblas_sasum_run(float *A , float *C,float *result, int N);
float *cblas_sasum_run(float *A ,float *C, int N);

#endif /* _TARGET_H_ */
