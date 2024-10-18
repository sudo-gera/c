#include <vector>
#include <memory>
#include <cinttypes>
#include <cstdint>
#include <cassert>
#include <optional>
#include <iostream>
#include <set>
#include <random>

#undef assert
#define assert assert_m

int64_t x__div(int64_t l, int64_t r) {
    assert(r);
    return l / r;
}
int64_t x__max(int64_t a, int64_t b) {
    return a > b ? a : b;
}
int64_t x__min(int64_t a, int64_t b) {
    return a < b ? a : b;
}
template <typename T>
int64_t list_size(const std::vector<T>& a) {
    return a.size();
}
template <typename T>
int64_t len(const std::vector<T>& a) {
    return a.size();
}
template <typename T>
bool list_contains(const std::vector<T>& a, const T& e) {
    return std::find(a.begin(), a.end(), e) != a.end();
}
template <typename T>
int64_t list_index(const std::vector<T>& a, const T& e) {
    return std::find(a.begin(), a.end(), e) - a.begin();
}
template <typename T>
void list_insert(std::vector<T>& a, int64_t pos, const T& e) {
    a.insert(a.begin() + pos, e);
}
template <typename T>
void list_append(std::vector<T>& a, const T& e) {
    a.push_back(e);
}
template <typename T>
void list_erase(std::vector<T>& a, int64_t e) {
    std::vector<T> f;
    // assert(0 <= e);
    // assert(e < (int64_t)a.size());
    std::copy(a.begin(), a.begin() + e, std::back_inserter(f));
    std::copy(a.begin() + e + 1, a.end(), std::back_inserter(f));
    swap(f, a);
}
auto x__print_one(auto&& a) {
    std::cout << a << " ";
    return 0;
}
void x__print(auto&&... a) {
    int d[] = {x__print_one(a)...};
    (void)d;
    std::cout << std::endl;
}
auto tuple_get_0(auto&& a) {
    return a.first;
}
auto tuple_get_1(auto&& a) {
    return a.second;
}
template <typename T>
void list_slice_assign(std::vector<T>& a, int64_t begin, int64_t end, std::vector<T> v) {
    std::vector<T> f;
    std::copy(a.begin(), a.begin() + begin, std::back_inserter(f));
    std::copy(v.begin(), v.end(), std::back_inserter(f));
    std::copy(a.begin() + end, a.end(), std::back_inserter(f));
    swap(a, f);
}
template <typename T>
void list_slice_assign_zero(std::vector<T>& a, int64_t begin, int64_t end) {
    list_slice_assign(a, begin, end, std::vector<T>());
}
template <typename T>
void list_slice_assign_one(std::vector<T>& a, int64_t begin, int64_t end, T val) {
    list_slice_assign(a, begin, end, std::vector<T>({std::move(val)}));
}
template <typename T>
void list_reverse(std::vector<T>& a) {
    std::reverse(a.begin(), a.end());
}
template <typename T>
struct node_ptr;
template <typename T>
struct node {
    std::vector<T> data;
    std::vector<node_ptr<T>> down = std::vector<node_ptr<T>>(1);
    std::weak_ptr<node<T>> maybe_parent;
};
template <typename T>
struct node_ptr {
    std::shared_ptr<node<T>> data_;
    T& data(int64_t f) {
        assert(f < data_size());
        assert(0 <= f);
        return data_->data[f];
    }
    node_ptr<T>& down(int64_t f){
        assert(f < down_size());
        assert(0 <= f);
        return data_->down[f];
    }
    int64_t down_size(){
        return data_->down.size();
    }
    int64_t data_size(){
        return data_->data.size();
    }
    bool down_contains(auto&&q){
        return list_contains(data_->down, std::forward<decltype(q)>(q));;
    }
    bool data_contains(auto&&q){
        return list_contains(data_->data, std::forward<decltype(q)>(q));;
    }
    int64_t down_index(auto&&q){
        return list_index(data_->down, std::forward<decltype(q)>(q));;
    }
    int64_t data_index(auto&&q){
        return list_index(data_->data, std::forward<decltype(q)>(q));;
    }
    void down_insert(auto&&q, auto&&w){
        return list_insert(data_->down, std::forward<decltype(q)>(q), std::forward<decltype(w)>(w));;
    }
    void data_insert(auto&&q, auto&&w){
        return list_insert(data_->data, std::forward<decltype(q)>(q), std::forward<decltype(w)>(w));;
    }
    void data_slice_assign_zero(auto&&...q){
        return list_slice_assign_zero(data_->data, std::forward<decltype(q)>(q)...);
    }
    void down_slice_assign_zero(auto&&...q){
        return list_slice_assign_zero(data_->down, std::forward<decltype(q)>(q)...);
    }
    void data_slice_assign_one(auto&&...q){
        return list_slice_assign_one(data_->data, std::forward<decltype(q)>(q)...);
    }
    void down_slice_assign_one(auto&&...q){
        return list_slice_assign_one(data_->down, std::forward<decltype(q)>(q)...);
    }
    void data_erase(auto&&...q){
        return list_erase(data_->data, std::forward<decltype(q)>(q)...);
    }
    void down_erase(auto&&...q){
        return list_erase(data_->down, std::forward<decltype(q)>(q)...);
    }
    void data_append(auto&&...q){
        return list_append(data_->data, std::forward<decltype(q)>(q)...);
    }
    void down_append(auto&&...q){
        return list_append(data_->down, std::forward<decltype(q)>(q)...);
    }
    void data_slice_assign_self(int64_t q_0, int64_t q_1, node_ptr& o){
        return list_slice_assign(data_->data, q_0, q_1, o.data_->data);
    }
    void down_slice_assign_self(int64_t q_0, int64_t q_1, node_ptr& o){
        return list_slice_assign(data_->down, q_0,q_1, o.data_->down);
    }
    operator std::shared_ptr<T>() const {
        return data_;
    }
    operator bool() const {
        return data_ != nullptr;
    }
    bool operator!=(std::nullptr_t) {
        return data_ != nullptr;
    }
    bool operator==(std::nullptr_t) {
        return data_ == nullptr;
    }
    node_ptr(std::shared_ptr<node<T>> a) : data_(a) {
    }
    node_ptr(nullptr_t) {
    }
    node_ptr() {
    }
    auto& operator*(){
        return *data_;
    }
    auto operator->(){
        return &*data_;
    }
};
template <typename T>
node_ptr<T> create_node() {
    return node_ptr<T>(std::make_shared<node<T>>());
}
template <typename T>
node_ptr<T> node_copy(node_ptr<T> self) {
    if (self) {
        return node_ptr<T>{std::make_shared<node<T>>(*self.data_)};
    } else {
        return node_ptr<T>{std::shared_ptr<node<T>>()};
    }
}
template <typename T>
auto node_insert(node_ptr<T> self, T&& elem, int64_t max_len) -> node_ptr<T> {
    assert(self != nullptr);
    self = node_copy(self);
    if (self.data_contains(elem)) {
        int64_t t = self.data_index(elem);
        self.data(t) = std::move(elem);
    } else if (self.down(0) == nullptr) {
        int64_t w = 0;
        while (w < (self.data_size()) and self.data(w) < elem) {
            w += 1;
        }
        self.data_insert(w, elem);
        node_ptr<T> tmp_3 = {nullptr};
        tmp_3 = nullptr;
        self.down_insert( 0, tmp_3);
    } else if (true) {
        int64_t w = 0;
        while (w < (self.data_size()) and self.data(w) < elem) {
            w += 1;
        }
        self.down(w) = node_insert(self.down(w), std::move(elem), max_len);
        node_ptr tmp = self.down(w);
        assert(tmp != nullptr);
        if ((tmp.data_size()) > max_len) {
            assert((tmp.data_size()) == 1 + max_len);
            node_ptr q = node_copy(tmp);
            node_ptr a = node_copy(q);
            a.data_slice_assign_zero( x__div(max_len, 2), (a.data_size()));
            a.down_slice_assign_zero( x__div(max_len, 2) + 1, (a.down_size()));
            auto kw = std::move(q.data(x__div(max_len, 2)));
            q.data_slice_assign_zero( 0, x__div(max_len, 2) + 1);
            q.down_slice_assign_zero(0, x__div(max_len, 2) + 1);
            self.data_insert( w, kw);
            self.down(w) = q;
            self.down_insert( w, a);
        }
    }
    return self;
}
template <typename T>
auto node_find_path(node_ptr<T> self, const T& elem) -> std::vector<std::pair<node_ptr<T>, int64_t>> {
    std::vector<std::pair<node_ptr<T>, int64_t>> output;
    if (node_find_path_(self, elem, output)) {
        return output;
    }
    return std::vector<std::pair<node_ptr<T>, int64_t>>();
}
template <typename T>
auto node_set_parent(node_ptr<T> self) -> void {
    for (auto& child: self.down()){
        if (child){
            child->maybe_parent = self.data_;
            node_set_parent(child);
        }
    }
}
template <typename T>
auto node_check(node_ptr<T> self, std::set<int64_t>* s = nullptr, int64_t l = 0) -> void{
    if (self == nullptr){
        return;
    }
    std::set<int64_t> aaa;
    if (not s){
        s = &aaa;
    }
    for (int64_t child_i=0; child_i<self.down_size(); ++child_i){
        auto& child = self.down(child_i);
        node_check(child, s, l + 1);
    }
    assert(self.down_size() == self.data_size() + 1);
    for (int64_t q = 0 ; q < self.data_size() ; ++q){
        assert ((self.down(q) == nullptr) == (self.down(q+1) == nullptr));
    }
    if (self.down(0) == nullptr){
        s->insert(l);
    }
    assert(s->size() == 1);
    for (int64_t q = 1 ; q < self.data_size() ; ++q){
        assert (self.data(q-1) < self.data(q));
    }
    if (l != *s->begin()){
        for (int64_t q = 0 ; q < self.data_size() ; ++q){
            assert (self.down(q).data(self.down(q).data_size()-1) < self.data(q));
            assert (self.data(q) < self.down(q+1).data(0));
        }
    }
}
template <typename T, typename OUT_IT>
auto node_find_path_(node_ptr<T> self, const T& elem, OUT_IT& output) -> bool {
    if (self.data_contains(elem)) {
        list_append(output, std::pair<node_ptr<T>, int64_t>{self, self.data_index( (elem))});
        return true;
    }
    if (self.down(0) == nullptr) {
        return false;
    }
    int64_t w = 0;
    while (w < self.data_size() and self.data(w) < elem) {
        w += 1;
    }
    node_ptr tmp = self.down(w);
    assert(tmp != nullptr);
    if (node_find_path_(tmp, elem, output)) {
        list_append(output, std::pair{self, w});
        return true;
    }
    return false;
}
template<typename T>
struct node_iter{
    node_ptr<T> self;
    int64_t pos;
    auto& operator++(){
        if (self.down(0) == nullptr){
            if (pos + 1 < self.data_size()){
                pos += 1;
                return *this;
            }
            while (1){
                auto p = node_ptr{self->maybe_parent.lock()};
                assert (p != nullptr);
                auto i = p.down_index( self);
                if (i + 1 == p.down_size()){
                    self = p;
                    continue;
                }
                self = p;
                pos = i;
                return *this;
            }
        }else{
            self = self.down(pos + 1);
            while (self.down(0)){
                self = self.down(0);
            }
            pos = 0;
        }
        return *this;
    }
    auto operator--(){
        if (self.down(0) == nullptr){
            if (pos - 1 >= 0){
                pos -= 1;
                return *this;
            }
            while (1){
                auto p = node_ptr{self->maybe_parent.lock()};
                assert (p != nullptr);
                auto i = p.down_index( self);
                if (i == 0){
                    self = p;
                    continue;
                }
                self = p;
                pos = i - 1;
                return *this;
            }
        }else{
            self = self.down(pos);
            while (self.down(self.down_size()-1)){
                self = self.down(self.down_size()-1);
            }
            pos = self.down_size() - 1;
        }
        return *this;
    }
    auto& operator*(){
        return self.data(pos);
    }
    auto operator->(){
        return &*self;
    }
};
template<typename T>
bool operator==(node_iter<T> left, node_iter<T> right){
    return left.self == right.self;
}
template<typename T>
bool operator!=(node_iter<T> left, node_iter<T> right){
    return left.self != right.self;
}
template<typename T>
node_iter<T> node_begin(node_ptr<T> self){
    while (self and self.down(0)){
        self = self.down(0);
    }
    return node_iter<T>{self, 0};
}
template<typename T>
node_iter<T> node_end(node_ptr<T> self){
    while (self and self.down(self.down_size()-1)){
        self = self.down(self.down_size()-1);
    }
    return node_iter<T>{self, self.data_size() - 1};
}
template <typename T>
auto node_erase(node_ptr<T> self, const T& elem, int64_t max_len) -> node_ptr<T> {
    node_ptr<T> t;
    self = node_copy(self);
    if (self.down(0) == nullptr) {
        node_check(self);
        int64_t t_ = self.data_index( (elem));
        self.data(t_);
        self.data_erase( t_);
        self.down_erase( 0);
        node_check(self);
    } else if (true) {
        node_check(self);
        int64_t w = 0;
        while (w < (self.data_size()) and self.data(w) < elem) {
            w += 1;
        }
        node_ptr tmp = self.down(w);
        assert(tmp != nullptr);
        self.down(w) = node_erase(tmp, elem, max_len);
        tmp = self.down(w);
        assert(tmp != nullptr);
        if ((tmp.data_size()) < x__div(max_len, 2)) {
            node_check(self);
            assert((tmp.data_size()) == x__div(max_len, 2) - 1);
            int64_t e = 0;
            if (w) {
                e = w - 1;
            } else if (true) {
                e = w + 1;
            }
            int64_t q = x__max(w, e);
            int64_t r = x__min(w, e);
            node_ptr tmp = self.down(e);
            assert(tmp != nullptr);
            if ((tmp.data_size()) == x__div(max_len, 2)) {
                node_check(self);
                tmp = self.down(q);
                assert(tmp != nullptr);
                t = node_copy(tmp);
                tmp = self.down(r);
                assert(tmp != nullptr);
                tmp.data_append( self.data(r));
                t.data_slice_assign_self( 0, 0, tmp);
                tmp = self.down(r);
                assert(tmp != nullptr);
                t.down_slice_assign_self( 0, 0, tmp);
                self.down_slice_assign_one(r, q + 1, t);
                self.down_slice_assign_zero(r, q);
                node_check(self);
            } else if (true) {
                node_check(self);
                tmp = self.down(w);
                assert(tmp != nullptr);
                t = node_copy(tmp);
                int64_t l = (q - w) * (t.down_size());
                int64_t tmp_1 = l;
                if (tmp_1 < 0) {
                    tmp_1 += t.data_size();
                }
                if (tmp_1 < 0) {
                    tmp_1 = 0;
                }
                if (tmp_1 > t.data_size()) {
                    tmp_1 = t.data_size();
                }
                t.data_slice_assign_one( tmp_1, tmp_1, self.data(r));
                tmp = self.down(e);
                assert(tmp != nullptr);
                tmp_1 = l;
                t.down_slice_assign_one( tmp_1, tmp_1,
                                      tmp.down((e - q + tmp.down_size()) % tmp.down_size()));
                self.down(w) = t;
                tmp = self.down(e);
                assert(tmp != nullptr);
                self.data(r) = tmp.data((e - q + tmp.data_size()) % tmp.data_size());
                tmp = self.down(e);
                assert(tmp != nullptr);
                t = node_copy(tmp);
                tmp_1 = e - q;
                if (tmp_1 < 0) {
                    tmp_1 += t.data_size();
                }
                int64_t tmp_2 = t.data_size() * (q - e) + (q - w);
                if (tmp_2 < 0) {
                    tmp_2 += t.data_size();
                }
                t.data_slice_assign_zero( tmp_1, tmp_2);
                tmp_1 = e - q;
                if (tmp_1 < 0) {
                    tmp_1 += t.down_size();
                }
                tmp_2 = t.down_size() * (q - e) + (q - w);
                if (tmp_2 < 0) {
                    tmp_2 += t.data_size();
                }
                t.down_slice_assign_zero( tmp_1, tmp_2);
                self.down(e) = t;
                node_check(self);
            }
            node_check(self);
        }
        node_check(self);
    }
    return self;
}
template <typename T>
auto node_to_list(node_ptr<T> self, std::vector<T>& l) -> std::vector<T>& {
    if (self.down(0) == nullptr) {
        int64_t i_ = 0;
        while (i_ < self.data_size()) {
            auto w_ = self.data(i_);
            l.append(w_);
            i_ += 1;
        }
    } else if (true) {
        node_ptr tmp = self.down(0);
        assert(tmp != nullptr);
        node_to_list(tmp, l);
        int64_t i_ = 0;
        while (i_ < self.data_size()) {
            int64_t w = i_;
            l.append(self.data(w));
            tmp = self.down(w + 1);
            node_to_list(tmp, l);
            i_ += 1;
        }
    }
    return l;
}
template <typename T>
auto node_chval(node_ptr<T> self, const std::vector<std::pair<node_ptr<T>, int64_t>>& a, int64_t t, T kw, int64_t n)
    -> node_ptr<T> {
    self = node_copy(self);
    if (n) {
        int64_t v = tuple_get_1(a[n]);
        node_ptr tmp = self.down(v);
        assert(tmp != nullptr);
        self.down(v) = node_chval(tmp, a, t, kw, n - 1);
    } else if (true) {
        self.data(t) = kw;
    }
    return self;
}
template <typename T>
struct b_set {
    node_ptr<T> root;
    int64_t max_len = 5;
    auto add(T&& v) -> void {
        auto& self = *this;
        node_check(self.root);
        node_ptr<T> q = create_node<T>();
        q.down(0) = self.root;
        q = node_insert(q, std::move(v), self.max_len);
        if (not (q.data_size())) {
            node_ptr<T> tmp = q.down(0);
            assert(tmp);
            q = tmp;
        }
        self.root = q;
    }
    auto find(const T& v) -> std::vector<T> {
        auto& self = *this;
        node_check(self.root);
        node_ptr r = self.root;
        if (r == nullptr) {
            return std::vector<T>();
        }
        assert(r != nullptr);
        auto f = node_find_path(r, v);
        if (not list_size(f)) {
            return std::vector<T>();
        }
        auto& _f = f[0];
        return std::vector<T>({tuple_get_0(_f).data(tuple_get_1(_f))});
    }
    auto contains(const T& v) -> bool {
        auto& self = *this;
        node_check(self.root);
        return bool(len(self.find(v)));
    }
    auto check() -> void {
        auto& self = *this;
        node_check(self.root);
    }
    auto remove(const T& v) -> void {
        auto& self = *this;
        node_check(self.root);
        node_ptr r = self.root;
        if (r == nullptr) {
            node_check(self.root);
            return;
        }
        assert(r != nullptr);
        auto a = node_find_path(r, v);
        if (not list_size(a)) {
            node_check(self.root);
            return;
        }
        assert(list_size(a));
        list_reverse(a);
        node_check(r);
        if (tuple_get_0(a[list_size(a) - 1]).down(0) != nullptr) {
            node_ptr t =
                tuple_get_0(a[list_size(a) - 1]).down(tuple_get_0(a[list_size(a) - 1]).data_index(v) + 1);
            assert(t != nullptr);
            while (t.down(0) != nullptr) {
                t = t.down(0);
                assert(t != nullptr);
            }
            auto kw = t.data(0);
            node_check(r);
            r = node_erase(r, kw, self.max_len);
            node_check(r);
            a = node_find_path(r, v);
            assert(list_size(a));
            int64_t t_ = tuple_get_0(a[0]).data_index( v);
            node_check(r);
            r = node_chval(r, a, t_, kw, list_size(a) - 1);
            node_check(r);
        } else if (true) {
            node_check(r);
            r = node_erase(r, v, self.max_len);
            node_check(r);
        }
        node_check(r);
        if ((r.data_size()) == 0) {
            r = r.down(0);
        }
        self.root = r;
        node_check(self.root);
    }
    auto to_list() -> std::vector<T> {
        auto& self = *this;
        node_check(self.root);
        node_ptr r = self.root;
        if (r == nullptr) {
            return std::vector<T>();
        }
        assert(r != nullptr);
        return node_to_list(r, std::vector<T>());
        return std::vector<T>();
    }
    auto begin(){
        auto& self = *this;
        node_check(self.root);
        return node_begin(self.root);
    }
    auto end(){
        auto& self = *this;
        node_check(self.root);
        return node_end(self.root);
    }
};
template <typename K, typename V>
struct item {
    K k;
    std::optional<V> v;
    auto operator<(const item<K, V>& o) -> bool {
        auto& self = *this;
        return self.k < o.k;
    }
    auto operator==(const item<K, V>& o) -> bool {
        auto& self = *this;
        {
            return self.k == o.k;
        }
    }
    auto to_list() -> std::pair<K, std::optional<V>> {
        auto& self = *this;
        return {k, v};
    }
};
template <typename K, typename V>
struct b_dict {
    b_set<item<K, V>> b_set_;
    auto operator[](const K& k) -> V {
        auto& self = *this;
        auto r = self.b_set.find(item(k));
        if (not r) {
            return std::optional<V>();
        }
        auto tmp = r[0].v;
        assert(tmp != nullptr);
        return {tmp};
    }
    auto setitem(const K& k, V&& v) -> void {
        auto& self = *this;
        self.b_set.add(item(k, v));
    }
    auto delitem(const K& k) -> void {
        auto& self = *this;
        self.b_set.remove(item(k));
    }
    auto contains(const K& k) -> bool {
        auto& self = *this;
        return bool(self.b_set.find(item(k)));
    }
};
int main() {
    b_set<int> a;
    assert(not a.contains(9));
    a.add(9);
    a.add(8);
    a.add(7);
    a.add(6);
    a.add(5);
    a.add(4);
    assert(a.contains(9));
    assert(a.contains(8));
    assert(a.contains(7));
    assert(a.contains(6));
    assert(a.contains(5));
    assert(a.contains(4));
    assert(not a.contains(3));
    a.remove(9);
    a.remove(7);
    a.remove(5);
    a.remove(3);
    assert(not a.contains(9));
    assert(a.contains(8));
    assert(not a.contains(7));
    assert(a.contains(6));
    assert(not a.contains(5));
    assert(a.contains(4));
    assert(not a.contains(3));
    assert(not a.contains(2));
    a = b_set<int>();
    std::set<int> s;
    std::mt19937_64 rand;
    for (size_t q = 0; q < 9999; ++q) {
        std::vector<std::function<void()>> funcs;
        funcs.push_back([&]() {
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
        });
        assert(funcs.size() == 1);
        funcs.push_back([&]() {
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
        });
        assert(funcs.size() == 2);
        funcs.push_back([&]() {
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
            }
        });
        funcs.push_back([&]() {
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
            }
        });
        funcs.push_back([&]() {
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d % g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&]() {
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d % g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&]() {
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d % g.size()];
            assert(s.count(w));
            assert(a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
        });
        funcs.push_back([&]() {
            int w = rand();
            assert(s.count(w) == a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
        });
        funcs.push_back([&]() {
            auto tmp = a;
            a = tmp;
        });
        assert(funcs.size());
        size_t s = rand();
        funcs[s % funcs.size()]();
    }
    std::vector<b_set<int>> as(1);
    std::vector<std::set<int>> ss(1);
    size_t ap = 0;
    size_t sp = 0;
    for (size_t q = 0; q < 99999; ++q) {
        std::vector<std::function<void()>> funcs;
        funcs.push_back([&]() { // 0
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
            a.check();
        });
        funcs.push_back([&]() { // 1
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
            a.check();
        });
        funcs.push_back([&]() { // 2
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
            }
            a.check();
        });
        funcs.push_back([&]() { // 3
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
            }
            a.check();
        });
        funcs.push_back([&]() { // 4
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
            }
            a.check();
        });
        funcs.push_back([&]() { // 5
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
            }
            a.check();
        });
        funcs.push_back([&]() { // 6
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            if (s.size()){
                std::vector<int> g(s.begin(), s.end());
                int64_t d = rand();
                int w = g[d % g.size()];
                assert(s.count(w));
                assert(a.contains(w));
                s.erase(w);
                a.remove(w);
                assert(not s.count(w));
                assert(not a.contains(w));
            }
            a.check();
        });
        funcs.push_back([&]() { // 7
            a.check();
            auto&a=as[ap];
            auto&s=ss[sp];
            int w = rand();
            assert(s.count(w) == a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
            a.check();
        });
        funcs.push_back([&]() { // 8
            auto&a=as[ap];
            auto&s=ss[sp];
            a.check();
            as.push_back(a);
            ss.push_back(s);
            {
                auto&a=as[ap];
                a.check();
            }
            ap = as.size()-1;
            sp = ss.size()-1;
            {
                auto&a=as[ap];
                a.check();
            }
        });
        funcs.push_back([&]() { // 9
            {
                auto&a=as[ap];
                a.check();
            }
            size_t w = rand();
            ap = w % as.size();
            sp = w % ss.size();
            {
                auto&a=as[ap];
                a.check();
            }
        });
        // funcs.push_back([&]() { // 10
        //     node_set_parent(a.root);
        //     auto ai = a.begin();
        //     auto si = s.begin();
        //     while (1){
        //         assert ((ai == a.end()) == (si == s.end()));
        //         if (ai == a.end()){
        //             break;
        //         }
        //         assert (*ai == *si);
        //         ++ai;
        //         ++si;
        //     }
        //     assert ((ai == a.end()) and (si == s.end()));
        // });
        // funcs.push_back([&]() { // 11
        //     node_set_parent(a.root);
        //     auto ai = a.end();
        //     auto si = s.end();
        //     while (1){
        //         assert ((ai == a.begin()) == (si == s.begin()));
        //         if (ai == a.begin()){
        //             break;
        //         }
        //         assert (*ai == *si);
        //         --ai;
        //         --si;
        //     }
        //     assert ((ai == a.begin()) and (si == s.begin()));
        // });
        size_t s = rand();
        s = s % funcs.size();
        x__print(s);
        funcs[s]();
        x__print("ap =", ap);
        for (size_t ap = 0 ; ap < as.size() ; ++ ap){
            {
                x__print("check.ap =", ap);
                auto&a=as[ap];
                a.check();
            }
        }
    }
}
