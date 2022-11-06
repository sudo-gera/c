#include <bits/stdc++.h>
using namespace std;

#define cat(q,w) q##w
#define unique_name(q) cat(_unique_name_,q)

#define setup_recursion(...) \
    struct another_layer{\
        void* return_ptr;\
        layer::return_type rt_str;\
    };\
    vector<pair<layer,another_layer>> call_stack;\
    call_stack.emplace_back();\
    call_stack.push_back({{__VA_ARGS__},{&&end}});\
    void* setup_locals_ret=&&start;\
    setup_locals:\
    auto*locals_pair=&call_stack.back();\
    auto&locals=locals_pair[0].first;\
    auto&another_locals=locals_pair[0].second;\
    auto&last_returned=another_locals.rt_str;\
    auto&to_return=locals_pair[-1].second.rt_str;\
    goto *setup_locals_ret;\
    end:\
    return last_returned;\
    start:


#define call(...)\
    ({\
        {\
            call_stack.push_back({{__VA_ARGS__},{&&unique_name(__LINE__)}});\
            setup_locals_ret=&&start;\
            goto setup_locals;\
        }\
        unique_name(__LINE__):\
        {}\
    })

#define ret(...)\
    {\
        to_return=(__VA_ARGS__);\
        setup_locals_ret=another_locals.return_ptr;\
        call_stack.pop_back();\
        goto setup_locals;\
    }

using llu=long long unsigned;

// auto run0(string _n){
//     struct layer{
//         string n;
//         string r;
//         using return_type=string;
//     };
//     setup_recursion(_n);
//     if (stoul(locals.n)<2){
//         ret(locals.n);
//     }
//     call(to_string(stoul(locals.n)-1));
//     locals.r=last_returned;
//     call(to_string(stoul(locals.n)-2));
//     locals.r=to_string(stoul(locals.r)+stoul(last_returned));
//     // locals.r=to_string(stoul((call(to_string(stoul(locals.n)-1)),last_returned))+
//     // stoul((call(to_string(stoul(locals.n)-1)),last_returned)));
//     ret(locals.r);
// }

llu run(llu _m,llu _n){
    struct layer{
        llu m,n;
        using return_type=llu;
    };
    setup_recursion(_m,_n);
    if (locals.m==0){
        ret(locals.n+1);
    }
    if (locals.n==0){
        call(locals.m-1,1);
        ret(last_returned);
    }
    call(locals.m,locals.n-1);
    call(locals.m-1,last_returned);
    ret(last_returned);
}

llu run1(llu m,llu n){
    if (m==0){
        return (n+1);
    }
    if (n==0){
        return run1(m-1,1);
    }
    return (run1(m-1,run1(m,n-1)));
}



int main(){
    // for (uint64_t w=0;w<16;++w){
    //     cout<<w<<" "<<run0(to_string(w))<<endl;
    // }

    // cout<<run1(3,12)<<endl;
    cout<<run(3,12)<<endl;
}
