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


TEST_F(fixtureName, testOk)
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
  EXPECT_FLOAT_EQ(C[0], cl_result[0]);
  // printf("%f",C[0]);
  // EXPECT_FLOAT_EQ(1, C[0]);
}


// TEST_F(fixtureName, testNg)
// {
//   EXPECT_EQ(0, function(0));
//   EXPECT_EQ(1, function(10000));
// }
