import module_test;
#include <iostream>
#include <assert.h>
void test_compiler_env()
{
    constexpr const int len = 3;
    float a[3] = {1, 2, 3};
    float b[3] = {1, 2, 3};
    auto c = module_test::cuda_mat<float>(a, b, len);
    for (int i{}; i < len; i++)
    {
        assert(c[i] == a[i] + b[i]);
    }
    module_test::module_template_vector<int> v(3);
    module_test::module_import_std();
    std::cout << "module compiler success!" << std::endl;
    std::cout << "cuda compiler success!" << std::endl;
}

int main()
{
    test_compiler_env();
    return 0;
}