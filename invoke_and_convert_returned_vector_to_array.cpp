#include <vector>
#include <array>
#include <iostream>

//auto invoke_and_convert_returned_vector_to_array(auto vec){

//}

#if __INCLUDE_LEVEL__ == 0
constexpr auto get_all_primes_less_than(size_t val){
    std::vector<size_t> primes;
    for (size_t q = 2; q < val; ++q){
        primes.push_back(q);
        for (size_t w = 2; w < q; ++w){
            if (q % w == 0){
                primes.pop_back();
                break;
            }
        }
    }
    return primes;
}

int main(){
    auto p = get_all_primes_less_than(20);
    for (auto s:p){
        std::cout << s << std::endl;
    }
#endif
