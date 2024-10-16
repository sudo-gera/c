#include <vector>
#include <iostream>
#include <memory>

#define elif else if
#define True true
#define False false

using namespace std;

struct empty_vec{
    template<typename T>
    operator std::vector<T>(){
        return std::vector<T>();
    }
};

template <typename T>
struct node {
    vector<T> data;
    vector<shared_ptr<node>> down;
};
template <typename T>
auto node_insert(shared_ptr<node<T>> self, T elem, size_t max_len) -> std::shared_ptr<node<T>> {
    check(self);
    assert((self));
    self = make_shared<node<T>>(*self);
    if (list_contains(self.data, elem)) {
        auto t = list_index(self.data, elem);
        self.data[t] = elem;
    }
    elif (self.down[0] == nullptr) {
        auto w = 0;
        while (w < list_size(self.data) and self.data[w] < elem) {
            w += 1;
        }
        list_insert(self.data, w, elem);
        list_insert(self.down, 0, nullptr);
    }
    else {
        auto w = 0;
        while (w < list_size(self.data) and self.data[w] < elem) {
            w += 1;
        }
        self.down[w] = insert(self.down[w], elem, max_len);
        auto tmp = self.down[w];
        assert(tmp != nullptr);
        if (list_size(tmp.data) > max_len) {
            assert(list_size(tmp.data) == 1 + max_len);
            auto q = tmp.copy();
            auto a = q.copy();
            list_slice_assign(a.data, max_len / 2,list_size(a.data), (empty_vec()));
            list_slice_assign(a.down, max_len / 2 + 1,list_size(a.down),(empty_vec()));
            auto kw = q.data[max_len / 2];
            list_slice_assign(q.data, 0, max_len / 2 + 1, (empty_vec()));
            list_slice_assign(q.down, 0,max_len / 2 + 1, (empty_vec()));
            list_insert(self.data, w, kw);
            self.down[w] = q;
            list_insert(self.down, w, a);
        }
    }
    return self;
}

// auto find_path(shared_ptr<node<T>> self,T elem) -> list[tuple[node[T], int]] | nullptr {
// output:
//     list[tuple[node[T], int]] = (empty_vec());
//     if (node_find_path_(self, elem, output)) {
//         return output;
//     }
//     return nullptr;
// }

template<typename T>
auto find_path_(shared_ptr<node<T>> self,T  elem,pair<shared_ptr<node<T>>, size_t>* output) -> bool {
    // node_check(self);
    if (list_contains(self.data, elem)) {
        output++[0] = ((self, list_index(self.data, (elem))));
        return True;
    }
    if (self.down[0] == nullptr) {
        return False;
    }
    auto w = 0;
    while (w < list_size(self.data) and self.data[w] < elem) {
        w += 1;
    }
    auto tmp = self.down[w];
    assert(tmp != nullptr);
    if (node_find_path_(tmp, elem, output)) {
        output++[0] = ((self, w));
        return True;
    }
    return False;
}

template<typename T>
auto erase(shared_ptr<node<T>> self, T elem, size_t max_len) -> shared_ptr<node<T>> {
    node_check(self);
    self = self.copy();
    if (self.down[0] == nullptr) {
        auto t_ = list_index(self.data, (elem));
        list_erase(self.data, t_);
        list_erase(self.down, 0);
    } else {
        auto w = 0;
        while (w < list_size(self.data) and self.data[w] < elem) {
            w += 1;
        }
        auto tmp = self.down[w];
        assert(tmp != nullptr);
        self.down[w] = node_erase(tmp, elem, max_len);
        tmp = self.down[w];
        assert(tmp != nullptr);
        if (list_size(tmp.data) < max_len / 2){
                assert(list_size(tmp.data) == max_len / 2 - 1);
                auto e = w ? w - 1 : w + 1;
                auto q = max(w, e);
                auto r = min(w, e);
                tmp = self.down[e];
                assert(tmp != nullptr);
                if (list_size(tmp.data) == max_len / 2){
                        tmp = self.down[q];
                        assert(tmp != nullptr);
                        auto t = tmp.copy();
                        tmp = self.down[r];
                        assert(tmp != nullptr);
                        auto __t = tmp.data;
                        list_append(__t, self.data[r]);
                        list_slice_assign(t.data, 0, 0, __t);
                        tmp = self.down[r];
                        assert(tmp != nullptr);
                        list_slice_assign(t.down, 0, 0, tmp.down);
                        list_slice_assign(self.down, r, q + 1, vector({t}));
                        list_slice_assign(self.data, r, q, (empty_vec()));
                    }
                else{
                        tmp = self.down[w];
                        assert(tmp != nullptr);
                        auto t = tmp.copy();
                        auto l = (q - w) * list_size(t.down);
                        list_slice_assign(t.data, l, l, vector({self.data[r]}));
                        tmp = self.down[e];
                        assert(tmp != nullptr);
                        list_slice_assign(t.down, l, l,
                                          vector({tmp.down[(e - q + list_size(tmp.down)) % list_size(tmp.down)]}));
                        self.down[w] = t;
                        tmp = self.down[e];
                        assert(tmp != nullptr);
                        self.data[r] = tmp.data[(e - q + list_size(tmp.data)) % list_size(tmp.data)];
                        tmp = self.down[e];
                        assert(tmp != nullptr);
                        t = tmp.copy();
                        list_slice_assign(t.data, e - q, list_size(t.data) * (q - e) + (q - w), (empty_vec()));
                        list_slice_assign(t.down, e - q, list_size(t.down) * (q - e) + (q - w), (empty_vec()));
                        self.down[e] = t;
                    }
            }
    }
    return self;
}

// auto to_list(shared_ptr<node<T>> self,vector< l : list[T]) -> list[T] {
//     if (self.down[0] is nullptr):{
//         for
//             i_ in range(list_size(self.data)) {
//                 w_ = self.data[i_];
//                 l.append(w_);
//             }
//         }
//     else:{
//             node_to_list(self.down[0], l);
//         for
//             w in range(list_size(self.data)) {
//                 l.append(self.data[w]);
//                 tmp = self.down[w + 1];
//                 assert(isinstance(tmp, node));
//                 node_to_list(tmp, l);
//             }
//         }
//     return l;
// }

// auto chval(shared_ptr<node<T>> self, a : list[tuple[node[T], int]], t : int, kw : T, n : int) -> node[T] {
//     self = self.copy();
//     if (n):{
//             v = a[n][1];
//             tmp = self.down[v];
//             assert(tmp != nullptr);
//             self.down[v] = node_chval(tmp, a, t, kw, n - 1)
//         }
//     else {
//         assert(self.data != nullptr);
//         assert(isinstance(t, int));
//         self.data[t] = kw
//     }
//     return self
// }

// / class b_set(typing.Generic[T]):

// /     def __init__(self) -> nullptr:
// /         self.root: Node[T] = nullptr;
// /         self.max_len = 99;

// /     def add(self, v: T) -> nullptr:
// /         q = node(data=List((empty_vec())), down=List([self.root, ]));
// /         q = node_insert(q, v, self.max_len);
// /         if (not list_size(q.data)):
// /             tmp = q.down[0];
// /             assert (tmp != nullptr);
// /             q = tmp;
// /         self.root = q;

// /     def find(self, v: T) -> list[T]:
// /         r = self.root;
// /         if (r is nullptr):
// /             return (empty_vec());
// /         f = node_find_path(r, v);
// /         if (f is nullptr):
// /             return (empty_vec());
// /         _f = f[0];
// /         return [_f[0].data[_f[1]]];

// /     def __contains__(self, v: T) -> bool:
// /         return bool(self.find(v));

// /     def remove(self, v: T) -> nullptr:
// /         r = self.root;
// /         if (r is nullptr):
// /             return;
// /         a = node_find_path(r, v);
// /         if (a is nullptr):
// /             return;
// /         a = a[::-1];
// /         if (a[-1][0].down[0] != nullptr):
// /             t = a[-1][0].down[list_index(a[-1][0].data, v) + 1];
// /             assert (t != nullptr);
// /             while (t.down[0] != nullptr):
// /                 t = t.down[0];
// /             kw = t.data[0];
// /             r = node_erase(r, kw, self.max_len);
// /             a = node_find_path(r, v);
// /             assert (a != nullptr);
// /             del t;
// /             t_ = list_index(a[0][0].data, v);
// /             r = node_chval(r, a, t_, kw, len(a) - 1);
// /         else:
// /             r = node_erase(r, v, self.max_len);
// /         if (list_size(r.data) == 0):
// /             r = r.down[0];
// /         self.root = r;

// /     def __repr__(self) -> str:
// /         r = self.root;
// /         return repr(r);

// /     def to_list(self) -> list[T]:
// /         r = self.root;
// /         if (r is nullptr):
// /             return (empty_vec());
// /         return node_to_list(r, (empty_vec()));

// /     def __del__(self) -> nullptr:
// /         pass;

// / K = typing.TypeVar('K', bound=ComparableProto);
// / K = typing.TypeVar('K') ; # type: ignore
// / V = typing.TypeVar('V');

// / @functools.total_ordering
// / class item(typing.Generic[K, V]):

// /     def __init__(self, k: K | item[K,V], v: V|nullptr=nullptr):
// /         if (not isinstance(k, item)):
// /             self.k : K = k;
// /             self.v : V|nullptr = v;
// /         else:
// /             self.k, self.v = k.k, k.v;

// /     def __lt__(self, o: item[K, V]) -> bool:
// /         return self.k < o.k;

// /     def __eq__(self, o: object|item[K, V]) -> bool:
// /         if (isinstance(o, item)):
// /             return self.k == o.k;
// /         return False;

// /     def __repr__(self) -> str:
// /         return 'item' + repr((self.k, self.v));

// /     def to_list(self) -> list[K|V|nullptr]:
// /         return [self.k, self.v];

// / class b_dict(typing.Generic[K, V]):

// /     def __init__(self) -> nullptr:
// /         self.b_set: b_set[item[K, V]] = b_set();

// /     def __getitem__(self, k:K)->V:
// /         r = self.b_set.find(item(k));
// /         if (not r):
// /             raise KeyError(k);
// /         tmp = r[0].v;
// /         assert (tmp != nullptr);
// /         return tmp;

// /     def __setitem__(self, k:K, v:V)->nullptr:
// /         self.b_set.add(item(k, v));

// /     def __delitem__(self, k:K)->nullptr:
// /         self.b_set.remove(item(k));

// /     def __repr__(self)->str:
// /         return repr(self.b_set);

// /     def __contains__(self, k:K) -> bool:
// /         return bool(self.b_set.find(item(k)));

// /     def to_dict(self) -> dict[K, V]:
// /         r_ = self.b_set.to_list();
// /         r = [w.to_list() for w in r_];
// /         return dict(r); # type: ignore

// / if (__name__ == '__main__'):
// /     # max_len=8;

// /     t=time.time();
// /     print([time.time()-t,(t:=time.time())][0]);

// /     sed = random.randint(-9999, 9999);
// /     print(sed);
// /     random.seed(sed);
// /     s_s: b_set[int] = b_set();
// /     a_s = set();
// /     for w in range(99):
// /         q = random.choice([0] * 3 + [1] + [2]);
// /         if (q == 0):
// /             r = random.randint(-9999, 9999);
// /             a_s.add(r);
// /             s_s.add(r);
// /         if (q == 1):
// /             r = random.choice(list(a_s)) if a_s and random.randint(
// /                 0, -1 + 2) else random.randint(0, -1 + 9);
// /             assert ((r in a_s) == (r in a_s));
// /             assert (r not in a_s or s_s.find(r)[0] == r);
// /         if (q == 2 and a_s):
// /             r = random.choice(list(a_s));
// /             a_s.remove(r);
// /             s_s.remove(r);
// /         f = set(s_s.to_list());
// /         assert (a_s == f);

// /     print([time.time()-t,(t:=time.time())][0]);
// /     # for w in range(199):
// /     #     r = random.randint(-9999, 9999);
// /     #     a_s.add(r);
// /     #     s_s.add(r);
// /     #     f = set(s_s.to_list());
// /     #     assert (a_s == f);

// /     # while (a_s):
// /     #     r = random.choice(list(a_s));
// /     #     a_s.remove(r);
// /     #     s_s.remove(r);
// /     #     f = set(s_s.to_list());
// /     #     assert (a_s == f);

// /     a_d: dict[int, int] = dict();
// /     s_d: b_dict[int, int] = b_dict();
// /     for w in range(49):
// /         q = random.choice([0] * 3 + [1] + [2] + [3]+[4]+[5]+[6]);
// /         if (q == 0):
// /             k = random.choice(list(a_d)) if a_d and random.randint(
// /                 0, 1) else random.randint(-9999, 9999);
// /             v = random.randint(-9999, 9999);
// /             a_d[k] = v;
// /             s_d[k] = v;
// /         if (q == 1):
// /             k = random.choice(list(a_d)) if a_d and random.randint(
// /                 0, 1) else random.randint(-9999, 9999);
// /             assert ((k in a_d) == (k in s_d));
// /         if (q == 2 and a_d):
// /             k = random.choice(list(a_d));
// /             a_d[k] == s_d[k];
// /         if (q == 3 and a_d):
// /             k = random.choice(list(a_d));
// /             del a_d[k];
// /             del s_d[k];
// /         if (q == 4 and a_d):
// /             k = random.randint(-9999, 9999);
// /             while (k in a_d):
// /                 k = random.randint(-9999, 9999);
// /             try:
// /                 del a_d[k];
// /                 assert (0);
// /             except KeyError:
// /                 pass;
// /             del s_d[k];
// /         if (q == 5 and a_d):
// /             k = random.randint(-9999, 9999);
// /             while (k in a_d):
// /                 k = random.randint(-9999, 9999);
// /             try:
// /                 a_d[k];
// /                 assert (0);
// /             except KeyError:
// /                 pass;
// /             try:
// /                 s_d[k];
// /                 assert (0);
// /             except KeyError:
// /                 pass;
// /         assert (s_d.to_dict() == a_d);
// /         # s_d = b_dict(s_d.getstr());

// /     print([time.time()-t,(t:=time.time())][0]);

// /     a_d = dict();
// /     s_d = b_dict();
// /     for w in range(199):
// /         k = random.randint(-9999, 9999);
// /         v = random.randint(-9999, 9999);
// /         s_d[k] = v;
// /         a_d[k] = v;

// /     # s_d = b_dict(s_d.getstr());

// /     print([time.time()-t,(t:=time.time())][0]);

// /     w = 0;
// /     while (a_d):
// /         k = random.choice(list(a_d));
// /         del a_d[k];
// /         del s_d[k];
// /         w += 1;
// /         if (w % 100 == 0):
// /             assert (s_d.to_dict() == a_d);
// /     assert (s_d.to_dict() == a_d);

// /     print([time.time()-t,(t:=time.time())][0]);

// /     a_d = dict();
// /     for w in range(999):
// /         k = random.randint(-9999, 9999);
// /         v = random.randint(-9999, 9999);
// /         s_d[k] = v;
// /         a_d[k] = v;

// /     print([time.time()-t,(t:=time.time())][0]);

// /     for w in range(19):
// /         q = random.choice([0] + [1] + [2] + [3]);
// /         if (q == 0):
// /             k = random.choice(list(a_d)) if a_d and random.randint(
// /                 0, 1) else random.randint(-9999, 9999);
// /             v = random.randint(-9999, 9999);
// /             a_d[k] = v;
// /             s_d[k] = v;
// /         if (q == 1):
// /             k = random.choice(list(a_d)) if a_d and random.randint(
// /                 0, 1) else random.randint(-9999, 9999);
// /             assert ((k in a_d) == (k in s_d));
// /         if (q == 2 and a_d):
// /             k = random.choice(list(a_d));
// /             a_d[k] == s_d[k];
// /         if (q == 3 and a_d):
// /             k = random.choice(list(a_d));
// /             del a_d[k];
// /             del s_d[k];

// /     print([time.time()-t,(t:=time.time())][0]);

// /     # root_set(0.0);

// /     # w = 0;
// /     # while (a_d):
// /     #     k = random.choice(list(a_d));
// /     #     del a_d[k];
// /     #     del s_d[k];
// /     #     w += 1;
// /     #     if (w % 100 == 0):
// /     #         assert (s_d.to_dict() == a_d);
// /     #         s_d = b_dict(s_d.getstr());
// /     # assert (s_d.to_dict() == a_d);
// /     # s_d = b_dict(s_d.getstr());

// /     print([time.time()-t,(t:=time.time())][0]);

// /     a :   dict[str, str] = dict();
// /     s : b_dict[str, str] = b_dict();
// /     for q in range(10**2*3):
// /         funcs = {}; # type: ignore
// /         @(lambda x: funcs.setdefault(len(funcs), x))
// /         @(lambda x: funcs.setdefault(len(funcs), x))
// /         def add() -> nullptr:
// /             k = random.randbytes(8).hex();
// /             v = random.randbytes(8).hex();
// /             assert ((k in a) == (k in s));
// /             a[k] = v;
// /             s[k] = v;
// /             assert (k in a);
// /             assert (k in s);
// /             assert (a[k] == s[k]);
// /         @(lambda x: funcs.setdefault(len(funcs), x))
// /         def mod() -> nullptr:
// /             if (a):
// /                 k = random.choice([*a.keys()]);
// /                 v = random.randbytes(8).hex();
// /                 assert (k in a);
// /                 assert (k in s);
// /                 a[k] = v;
// /                 s[k] = v;
// /                 assert (k in a);
// /                 assert (k in s);
// /                 assert (a[k] == s[k]);
// /         @(lambda x: funcs.setdefault(len(funcs), x))
// /         def get() -> nullptr:
// /             if (a):
// /                 k = random.choice([*a.keys()]);
// /                 assert (k in a);
// /                 assert (k in s);
// /                 assert (a[k] == s[k]);
// /         @(lambda x: funcs.setdefault(len(funcs), x))
// /         def rem() -> nullptr:
// /             if (a):
// /                 k = random.choice([*a.keys()]);
// /                 assert (k in a);
// /                 assert (k in s);
// /                 assert (a[k] == s[k]);
// /                 del a[k];
// /                 del s[k];
// /                 assert (k not in a);
// /                 assert (k not in s);
// /         random.choice(funcs)();
int main(){
    
}