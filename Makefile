CC := gcc
CFLAGS := -c -Wall -Wextra
GCC := g++
GOOGLE := googletest-release-1.8.0/googletest
LIB := -lOpenCL -lclBLAS -lopenblas

all:
	$(CC) $(CFLAGS)  -I/opt/AMDAPPSDK-2.9-1/include/ clblas_tg.c
	$(GCC) test.cpp $(GOOGLE)/src/gtest_main.cc gtest/gtest-all.cc -I/opt/AMDAPPSDK-2.9-1/include/ -L/usr/local/lib64  -I. -lpthread clblas_tg.o  $(LIB)
	./a.out

gtest-gen:
	python $(GOOGLE)/scripts/fuse_gtest_files.py ./
