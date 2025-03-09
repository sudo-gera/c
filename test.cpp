#include <any>

struct base{};
struct der:base{};

int main(){
    std::any a = der();
    std::any_cast<der&>(a);
}