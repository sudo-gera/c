#include <bits/stdc++.h>
using namespace std;

#define cat(q, w) q##w
#define unique_name(q) cat(_unique_name_, q)

#define recursive_loop(...)                                                        \
    for (                                                                          \
        struct {                                                                   \
            decltype(tie(__VA_ARGS__)) _tie;                                       \
            vector<pair<decltype(make_tuple(__VA_ARGS__)), void *>> call_stack;    \
            void *to_return_ptr;                                                   \
        } _rec{                                                                    \
            tie(__VA_ARGS__),                                                      \
            {{{}, &&start}},                                                       \
        };                                                                         \
        not({                                                                      \
            start:                                                                 \
            _rec.call_stack.empty();                                               \
        });                                                                        \
        assert(((void)"end without return", 0))                                    \
    )

#define call(...)                                                                  \
    {                                                                              \
        _rec.call_stack.push_back({_rec._tie, &&unique_name(__LINE__)});           \
        _rec._tie = decltype(_rec.call_stack[0].first){__VA_ARGS__};               \
        goto start;                                                                \
        unique_name(__LINE__) : {}                                                 \
    }

#define ret()                                                                      \
    {                                                                              \
        _rec._tie = _rec.call_stack.back().first;                                  \
        _rec.to_return_ptr = _rec.call_stack.back().second;                        \
        _rec.call_stack.pop_back();                                                \
        goto *_rec.to_return_ptr;                                                  \
    }

using llu = long long unsigned;

string run0(string n) {
    string ret_val;
    string r;
    recursive_loop(n, r) {
        if (stoul(n) < 2) {
            ret_val = n;
            ret();
        }
        call(to_string(stoul(n) - 1), "");
        r = ret_val;
        call(to_string(stoul(n) - 2), "");
        ret_val = to_string(stoul(r) + stoul(ret_val));
        ret();
    }
    return ret_val;
}

llu run(llu m, llu n) {
    llu ret_val=0;
    recursive_loop(m,n){
        if (m==0){
            ret_val=n+1;
            ret();
        }
        if (n==0){
            call(m-1,1);
            ret();
        }
        call(m,n-1);
        call(m-1,ret_val);
        ret();
    }
    return ret_val;
}

llu run1(llu m, llu n) {
    if (m == 0) {
        return (n + 1);
    }
    if (n == 0) {
        return run1(m - 1, 1);
    }
    return (run1(m - 1, run1(m, n - 1)));
}

int main() {
    // for (uint64_t w=0;w<16;++w){
    //     cout<<w<<" "<<run0(to_string(w))<<endl;
    // }

    // cout << run1(3, 12) << endl;
    cout <<  run(3, 12) << endl;
}
