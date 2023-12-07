module;
#include "compiler_module_test.hpp"
export module module_test;
export namespace module_test
{
    using module_test::module_import_std;
    template <typename T>
    using module_template_vector =  module_test::module_template_vector<T>;
    using module_test::cuda_mat;
}


