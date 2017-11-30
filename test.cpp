#include "gtest/gtest.h" //

extern "C" {
  #include "target.h"
  #include <clBLAS.h>
  #include "cblas.h"
}

class fixtureName : public ::testing::Test {
protected:

  virtual void SetUp(){
  }

  virtual void TearDown(){
  }
};


TEST_F(fixtureName, sgemm)
{
  int M = 4;
  int N = 3;
  int K = 5;
  float A[M*K] = { 
    11, 12, 13, 14, 15, 
    21, 22, 23, 24, 25, 
    31, 32, 33, 34, 35, 
    41, 42, 43, 44, 45, 
  }; 

  float B[K*N] = {
    11, 12, 13,
    21, 22, 23,
    31, 32, 33,
    41, 42, 43,
    51, 52, 53,
  };

  float C[M*N] = {
    11, 12, 13,
    21, 22, 23,
    31, 32, 33,
    41, 42, 43,
  };
  float cl_result[M*N];

  clblas_sgemm_run(A,B,C,cl_result,M,K,N);
  cblas_sgemm_run(A,B,C,M,K,N);
  for (int i = 1;i  < sizeof C/sizeof(float);i ++)
    {EXPECT_FLOAT_EQ(C[i], cl_result[i]); }
}

TEST_F(fixtureName, sdot)
{
  int N = 3;
  float A[N] = { 
    11, 12, 13
  }; 

  float B[N] = {
    11, 12, 13,

  };
  float C[N];
  float cl_result[N];
  clblas_sdot_run(A,B,C,cl_result,N);
  cblas_sdot_run(A,B,C,N);
  for (int i = 1;i  < sizeof C/sizeof(float);i ++)
    {EXPECT_FLOAT_EQ(C[i], cl_result[i]); }
}

TEST_F(fixtureName, sasum)
{
  int N = 3;
  float A[N] = { 
    11, 12, 13
  }; 

  float C[N];
  float cl_result[N];
  clblas_sasum_run(A,C,cl_result,N);
  cblas_sasum_run(A,C,N);
  for (int i = 1;i  < sizeof C/sizeof(float);i ++)
    {EXPECT_FLOAT_EQ(C[i], cl_result[i]); }
}
