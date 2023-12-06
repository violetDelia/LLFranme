//添加cuda库
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
//定义核函数 __global__为声明关键字
extern "C" float *matAdd(float *a,float *b,int length);

template <typename T>
__global__ void matAdd_cuda(T *a,T *b,T *sum)
{
    int i = blockIdx.x*blockDim.x+ threadIdx.x;
    sum[i] = a[i] + b[i];
};