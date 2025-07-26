#include <vector>

struct leak{
    std::vector<leak> data;
};

int main(){
    leak l = {{{{}}}};
    std::swap(l.data[0], l);
}
