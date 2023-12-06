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

}