import module_test;
#include <iostream>
#include <assert.h>
void test_compiler_env()
{
    constexpr const int len = 3;
    float a[3] = {1, 2, 3};
    float b[3] = {1,};
    auto c = module_test::malloc_cuda_<float,0>(a,sizeof(float)*3);
    module_test::add_one_<float,0>(c,sizeof(float)*3);
    auto r = module_test::free_to_host_<float,0>(a,c,sizeof(float)*3);
    std::cout<<a[0]<<a[1]<<a[2];
    
}

int main()
{
    test_compiler_env();
    return 0;
}