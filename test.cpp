#include "visitable_var.cpp"

auto print = [](auto&&...a)
requires(requires{((std::cout << a, 0) + ... + 0);})
{
    (void)((std::cout << a << " ", 0)|...|0);
    std::cout << std::endl;
};

int main(){
    var a, s, d;
    a = 9;
    s = a;
    d = std::string("888");
    visit(print, a, s, d);
    auto tmp="1";
    a = tmp;
    visit(print, a);
    a = "2";
    visit(print, a);
    std::string f="3";
    const auto& g=f;
    a = g;
    const auto& ca = a;
    visit(print, ca);
    a = print;
    try{
        visit(print, a);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
}

END_OF_CODE

