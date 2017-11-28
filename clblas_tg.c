#include <sys/types.h>
#include <stdio.h>
#include <clBLAS.h>
#include "cblas.h"

/* #define M  4 */
/* #define N  3 */
/* #define K  5 */



float *clblas_sgemm_run(const float *A ,const float *B, const float *C,float *result, int M,int K,int N) {
  const cl_float alpha = 10;
  
  const size_t lda = K;        /* i.e. lda = K */
  
  const size_t ldb = N;        /* i.e. ldb = N */
  
  const cl_float beta = 20;
  
  const size_t ldc = N;        /* i.e. ldc = N */

  cl_int err;
  cl_platform_id platform = 0;
  cl_device_id device = 0;
  cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
  cl_context ctx = 0;
  cl_command_queue queue = 0;
  cl_mem bufA, bufB, bufC;
  cl_event event = NULL;

  /* Setup OpenCL environment. */
  err = clGetPlatformIDs( 1, &platform, NULL );
  err = clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL );

  props[1] = (cl_context_properties)platform;
  ctx = clCreateContext( props, 1, &device, NULL, NULL, &err );
  queue = clCreateCommandQueueWithProperties( ctx, device, NULL, &err );

  /* Setup clBLAS */
  err = clblasSetup( );

  /* Prepare OpenCL memory objects and place matrices inside them. */
  bufA = clCreateBuffer( ctx, CL_MEM_READ_ONLY, M * K * sizeof(*A),
			 NULL, &err );
  bufB = clCreateBuffer( ctx, CL_MEM_READ_ONLY, K * N * sizeof(*B),
			 NULL, &err );
  bufC = clCreateBuffer( ctx, CL_MEM_READ_WRITE, M * N * sizeof(*C),
			 NULL, &err );

  err = clEnqueueWriteBuffer( queue, bufA, CL_TRUE, 0,
			      M * K * sizeof( *A ), A, 0, NULL, NULL );
  err = clEnqueueWriteBuffer( queue, bufB, CL_TRUE, 0,
			      K * N * sizeof( *B ), B, 0, NULL, NULL );
  err = clEnqueueWriteBuffer( queue, bufC, CL_TRUE, 0,
			      M * N * sizeof( *C ), C, 0, NULL, NULL );

  /* Call clBLAS extended function. Perform gemm for the lower right sub-matrices */
  err = clblasSgemm( clblasRowMajor, clblasNoTrans, clblasNoTrans,
		     M, N, K,
		     alpha, bufA, 0, lda,
		     bufB, 0, ldb, beta,
		     bufC, 0, ldc,
		     1, &queue, 0, NULL, &event );

  /* Wait for calculations to be finished. */
  err = clWaitForEvents( 1, &event );

  /* Fetch results of calculations from GPU memory. */
  err = clEnqueueReadBuffer( queue, bufC, CL_TRUE, 0,
			     M * N * sizeof(*result),
			     result, 0, NULL, NULL );

  /* Release OpenCL memory objects. */
  clReleaseMemObject( bufC );
  clReleaseMemObject( bufB );
  clReleaseMemObject( bufA );

  /* Finalize work with clBLAS */
  clblasTeardown( );

  /* Release OpenCL working objects. */
  clReleaseCommandQueue( queue );
  clReleaseContext( ctx );

  //return ret;
  return result;
};

float *cblas_sgemm_run(cl_float *A ,cl_float *B,cl_float *C, int M,int K,int N) {
  
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 10, A, K,
	      B, N, 20, C, N);
  return C;
}




