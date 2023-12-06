#include "compiler_cuda_test.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

float *matAdd(float *a,float *b,int length)
{
    int device = 0;//设置使用第0块GPU进行运算
    cudaSetDevice(device);
    cudaDeviceProp devProp;
    cudaGetDeviceProperties(&devProp, device);
    int threadMaxSize = devProp.maxThreadsPerBlock;
    int blockSize = (length+threadMaxSize-1)/threadMaxSize;
    dim3 thread(threadMaxSize);
    dim3 block(blockSize);
    int size = length * sizeof(float);
    float *sum =(float *)malloc(size) ;
    float *sumGPU,*aGPU,*bGPU;
    cudaMalloc((void**)&sumGPU,size);
    cudaMalloc((void**)&aGPU,size);
    cudaMalloc((void**)&bGPU,size);
    //内存->显存
    cudaMemcpy((void*)aGPU,(void*)a,size,cudaMemcpyHostToDevice);
    cudaMemcpy((void*)bGPU,(void*)b,size,cudaMemcpyHostToDevice);
    //运算
    matAdd_cuda<float><<<block,thread>>>(aGPU,bGPU,sumGPU);
    //cudaThreadSynchronize();
    //显存->内存
    cudaMemcpy(sum,sumGPU,size,cudaMemcpyDeviceToHost);
    //释放显存
    cudaFree(sumGPU);
    cudaFree(aGPU);
    cudaFree(bGPU);
    return sum;
}