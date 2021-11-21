#include "h"

auto run(int q){
    if (q){
        return run(q-1)+1;
    }
    return 0;
}

ima{
    auto h=run(9);
    print(h);
}