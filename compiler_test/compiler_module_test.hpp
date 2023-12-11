#include <vector>
#include "compiler_cuda_test.cuh"
#include <iostream>

namespace module_test
{
    template <typename T>
    using module_template_vector = std::vector<T>;

    template <typename T>
    float *cuda_mat(float *a, float *b, int len)
    {
        return matAdd(a, b, len);
    };

    void module_import_std();

    template <typename T,size_t device>
    float *malloc_cuda_(T *a, int len)
    {
        return malloc_cuda(a, len, device);
    };

    template <typename T,size_t device>
    void add_one_(T *a,  int len)
    {
        return add_one(a, len, device);
    };
    template <typename T,size_t device>
    float *free_to_host_(T *a, T *b, int len)
    {
        return free_to_host(a, b, len,device);
    };



}