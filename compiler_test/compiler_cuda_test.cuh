//添加cuda库
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
//定义核函数 __global__为声明关键字
extern "C" float *matAdd(float *a,float *b,int length);
extern "C" void add_one(float *Gpu,int length,int device);
extern "C" float *malloc_cuda(float *host,size_t length,int device);
extern "C" float * free_to_host(float *host,float *gpu,size_t length,int device);






template <typename T>
__global__ void matAdd_cuda(T *a,T *b,T *sum)
{
    int i = blockIdx.x*blockDim.x+ threadIdx.x;
    sum[i] = a[i] + b[i];
};

template <typename T>
__global__ void add_one_cuda(T *a)
{
    int i = blockIdx.x*blockDim.x+ threadIdx.x;
    a[i] += 1;
};