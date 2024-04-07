#include <atomic>


auto f(std::atomic<size_t>&a){
    return a.fetch_add(1);
}

int main(){
    std::atomic<size_t> a;
    f(a);
}
