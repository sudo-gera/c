#include <iostream>
#include <vector>

struct incomplete;

#define EXPR ((std::vector<incomplete>()).resize(0))

int main(){
    if constexpr (requires{EXPR;}) {
        EXPR;
    }
}
