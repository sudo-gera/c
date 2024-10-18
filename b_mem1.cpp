# 1 "b_mem.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 495 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "b_mem.cpp" 2







const char* x__8 = """_" "_""";
# 95 "b_mem.cpp"
const char* x__95 = """_" "_""";
# 120 "b_mem.cpp"
int64_t x__div(int64_t l, int64_t r){
    assert(r);
    return l / r;
}

int64_t x__max(int64_t a, int64_t b){
    return a>b?a:b;
}

int64_t x__min(int64_t a, int64_t b){
    return a<b?a:b;
}

template<typename T>
int64_t list_size(const std::vector<T>& a){
    return a.size();
}

template<typename T>
int64_t len(const std::vector<T>& a){
    return a.size();
}

template<typename T>
bool list_contains(const std::vector<T>& a, const T& e){
    return std::find(a.begin(), a.end(), e) != a.end();
}

template<typename T>
int64_t list_index(const std::vector<T>& a, const T& e){
    return std::find(a.begin(), a.end(), e) - a.begin();
}

template<typename T>
void list_insert(std::vector<T>& a, int64_t pos, const T& e){
    a.insert(a.begin() + pos, e);
}

template<typename T>
void list_append(std::vector<T>& a, const T& e){
    a.push_back(e);
}

template<typename T>
void list_erase(std::vector<T>& a, int64_t e){
    std::vector<T> f;
    std::copy(a.begin(), a.begin()+e, std::back_inserter(f));
    std::copy(a.begin()+e+1, a.end(), std::back_inserter(f));
    swap(f, a);
}



auto print_one(auto&&a){
    std::cout << a << " ";
    return 0;
}

void print(auto&&...a){
    (print_one(a),...);
    std::cout << std::endl;
}



auto tuple_get_0(auto&&a){
    return a.first;
}

auto tuple_get_1(auto&&a){
    return a.second;
}

template<typename T>
void list_slice_assign(std::vector<T>& a, int64_t begin, int64_t end, std::vector<T> v){
    std::vector<T> f;
    std::copy(a.begin(), a.begin() + begin, std::back_inserter(f));
    std::copy(v.begin(), v.end(), std::back_inserter(f));
    std::copy(a.begin() + end, a.end() , std::back_inserter(f));
    swap(a, f);
}

template<typename T>
void list_slice_assign_zero(std::vector<T>& a, int64_t begin, int64_t end){
    list_slice_assign(a, begin, end, std::vector<T>());
}

template<typename T>
void list_slice_assign_one(std::vector<T>& a, int64_t begin, int64_t end, T val){
    list_slice_assign(a, begin, end, std::vector<T>({std::move(val)}));
}

template<typename T>
void list_reverse(std::vector<T>& a){
    std::reverse(a.begin(), a.end());
}


template<typename T>
struct node;

template<typename T>
struct node_s{
    std::vector<T> data;
    std::vector<node<T>> down = std::vector<node<T>>(1);
};

template<typename T>
struct node{
    std::shared_ptr<node_s<T>> data_;
    std::vector<T>& data(){
        return data_->data;
    }
    std::vector<node<T>>& down(){
        return data_->down;
    }
    operator std::shared_ptr<T>()const{
        return data_;
    }
    operator bool()const{
        return data_ != nullptr;
    }
    bool operator!=(std::nullptr_t){
        return data_ != nullptr;
    }
    bool operator==(std::nullptr_t){
        return data_ == nullptr;
    }
    node(std::shared_ptr<node_s<T>> a): data_(a){}
    node(nullptr_t){}
    node(){}
};

template<typename T>
node<T> create_node(){
    return node<T>(std::make_shared<node_s<T>>());
}


template<typename T>
node<T> node_copy(node<T> self){
    if (self){
        return node<T>{std::make_shared<node_s<T>>(*self.data_)};
    }else{
        return node<T>{std::shared_ptr<node_s<T>>()};
    }
}

const char* x__268 = """_" "_""";
# 285 "b_mem.cpp"
template<typename T>
auto node_insert(node<T> self, T&& elem, int64_t max_len) -> node<T>{




    assert (self != nullptr);
    self = node_copy(self);
    if (list_contains(self.data(), elem))



        {



        int64_t
        t = list_index(self.data(), elem);
        self.data()[t] = elem;



        }



    else if (self.down()[0] == nullptr)



        {
        int64_t



        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)




            {




            w += 1;




            }




        list_insert(self.data(), w, elem);




        node<T> tmp_3 = {nullptr};




        tmp_3 = nullptr;
        list_insert(self.down(), 0, tmp_3);



        }



    else if (true)



        {
        int64_t



        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)



            {



            w += 1;



            }



        self.down()[w] = node_insert(self.down()[w], std::move(elem), max_len);



        node



        tmp = self.down()[w];



        assert (tmp != nullptr);
        if (list_size(tmp.data()) > max_len)



            {



            assert (list_size(tmp.data()) == 1 + max_len);



            node



            q = node_copy(tmp);



            node



            a = node_copy(q);
            list_slice_assign_zero(a.data(),x__div( max_len , 2),list_size(a.data()));
            list_slice_assign_zero(a.down(),x__div( max_len , 2) + 1,list_size(a.down()));



            auto



            kw = q.data()[x__div(max_len , 2)];
            list_slice_assign_zero(q.data(), 0,x__div( max_len , 2) + 1);
            list_slice_assign_zero(q.down(), 0,x__div(max_len , 2) + 1);
            list_insert(self.data(), w, kw);
            self.down()[w] = q;
            list_insert(self.down(), w, a);



            }






        }



    return self;



    }







template<typename T>
auto node_find_path(node<T> self, const T& elem) -> std::vector<std::pair<node<T>, int64_t>>{
# 475 "b_mem.cpp"
    std::vector<std::pair<node<T>, int64_t>> output;





    if (node_find_path_(self, elem, output))



        {



        return output;



        }







    return std::vector<std::pair<node<T>, int64_t>>();
# 510 "b_mem.cpp"
    }







template<typename T, typename OUT_IT>
auto node_find_path_(node<T> self , const T& elem, OUT_IT& output) -> bool{





    if (list_contains(self.data(), elem))




        {
# 539 "b_mem.cpp"
        list_append(output, std::pair{self, list_index(self.data(), (elem))});
# 548 "b_mem.cpp"
        return true;




        }




    if (self.down()[0] == nullptr)




        {




        return false;




        }







    int64_t




    w = 0;
    while (w < list_size(self.data()) and self.data()[w] < elem)




        {




        w += 1;




        }







    node




    tmp = self.down()[w];



    assert (tmp != nullptr);
    if (node_find_path_(tmp, elem, output))




        {
# 634 "b_mem.cpp"
        list_append(output, std::pair{self, w});






        return true;




        }




    return false;




    }







template<typename T>
auto node_erase(node<T> self , const T& elem, int64_t max_len) -> node<T>{
# 674 "b_mem.cpp"
    node<T> t;





    self = node_copy(self);
    if (self.down()[0] == nullptr)




        {







        int64_t




        t_ = list_index(self.data(), (elem));
        list_erase(self.data(), t_);
        list_erase(self.down(), 0);




        }




    else if (true)



        {







        int64_t





        w = 0;
        while (w < list_size(self.data()) and self.data()[w] < elem)



            {



            w += 1;



            }







        node




        tmp = self.down()[w];



        assert (tmp != nullptr);
        self.down()[w] = node_erase(tmp, elem, max_len);
        tmp = self.down()[w];



        assert (tmp != nullptr);
        if (list_size(tmp.data()) <x__div( max_len , 2))



            {



            assert (list_size(tmp.data()) ==x__div( max_len , 2) - 1);




            int64_t




            e = 0;
            if (w)




                {




                e = w - 1;




                }




            else if (true)




                {




                e = w + 1;




                }







            int64_t




            q = x__max(w, e);




            int64_t




            r = x__min(w, e);




            node




            tmp = self.down()[e];



            assert (tmp != nullptr);
            if (list_size(tmp.data()) ==x__div( max_len , 2))



                {



                tmp = self.down()[q];



                assert (tmp != nullptr);
                t = node_copy(tmp);
                tmp = self.down()[r];



                assert (tmp != nullptr);




                auto&




                __t = tmp.data();
                list_append(__t, self.data()[r]);
                list_slice_assign(t.data(), 0, 0, __t);
                tmp = self.down()[r];



                assert (tmp != nullptr);
                list_slice_assign(t.down(), 0,0,tmp.down());
                list_slice_assign_one(self.down(), r,q + 1, t);
                list_slice_assign_zero(self.data(), r,q );



                }



            else if (true)



                {



                tmp = self.down()[w];



                assert (tmp != nullptr);
                t = node_copy(tmp);




                int64_t




                l = (q - w) * list_size(t.down());





                int64_t




                tmp_1 = l;
                if (tmp_1 < 0)




                    {




                    tmp_1 += list_size(t.data());




                    }




                if (tmp_1 < 0)




                    {




                    tmp_1 = 0;




                    }




                if (tmp_1 > list_size(t.data()))




                    {




                    tmp_1 = list_size(t.data());




                    }




                list_slice_assign_one(t.data(), tmp_1, tmp_1, self.data()[r]);
                tmp = self.down()[e];



                assert (tmp != nullptr);
                tmp_1 = l;
                list_slice_assign_one(t.down(), tmp_1, tmp_1, tmp.down()[(e - q + list_size(tmp.down())) % list_size(tmp.down())]);
                self.down()[w] = t;
                tmp = self.down()[e];



                assert (tmp != nullptr);
                self.data()[r] = tmp.data()[(e - q + list_size(tmp.data())) % list_size(tmp.data())];
                tmp = self.down()[e];



                assert (tmp != nullptr);
                t = node_copy(tmp);
                tmp_1 = e - q;
                if (tmp_1 < 0)




                    {




                    tmp_1 += list_size(t.data());




                    }







                int64_t




                tmp_2 = list_size(t.data()) * (q - e) + (q - w);
                if (tmp_2 < 0)




                    {




                    tmp_2 += list_size(t.data());




                    }




                list_slice_assign_zero(t.data(), tmp_1, tmp_2);
                tmp_1 = e - q;
                if (tmp_1 < 0)




                    {




                    tmp_1 += list_size(t.down());




                    }




                tmp_2 = list_size(t.down()) * (q - e) + (q - w);
                if (tmp_2 < 0)




                    {




                    tmp_2 += list_size(t.data());




                    }




                list_slice_assign_zero(t.down(), tmp_1, tmp_2);
                self.down()[e] = t;




                }







            }







        }




    return self;




    }







template<typename T>
auto node_to_list(node<T> self, std::vector<T>& l) -> std::vector<T>&{





    if (self.down()[0] == nullptr)




        {







        int64_t




        i_ = 0;
        while (i_ < list_size(self.data()))




            {







            auto




            w_ = self.data()[i_];
            l.append(w_);
            i_ += 1;




            }







        }




    else if (true)




        {







        node




        tmp = self.down()[0];
        assert (tmp != nullptr);



        node_to_list(tmp, l);




        int64_t




        i_ = 0;
        while (i_ < list_size(self.data()))




            {







            int64_t




            w = i_;
            l.append(self.data()[w]);
            tmp = self.down()[w + 1];





            node_to_list(tmp, l);
            i_ += 1;




            }







        }




    return l;




    }







template<typename T>
auto node_chval(node<T> self, const std::vector<std::pair<node<T>, int64_t>>& a,int64_t t,T kw,int64_t n) -> node<T>{





    self = node_copy(self);
    if (n)




        {







        int64_t




        v = tuple_get_1(a[n]);




        node




        tmp = self.down()[v];



        assert (tmp != nullptr);
        self.down()[v] = node_chval(tmp, a, t, kw, n - 1);




        }




    else if (true)




        {
# 1374 "b_mem.cpp"
        self.data()[t] = kw;




        }




    return self;




    }
# 1403 "b_mem.cpp"
template<typename T>
struct b_set{
    node<T> root;
    int64_t max_len = 5;
# 1435 "b_mem.cpp"
    auto add(T&& v) -> void{
        auto& self = *this;
# 1445 "b_mem.cpp"
        node<T> q = create_node<T>();
        q.down()[0] = self.root;






        q = node_insert(q, std::move(v), self.max_len);
        if (not list_size(q.data()))




            {







            node<T>




            tmp = q.down()[0];




            assert (tmp);

            q = tmp;




            }




        self.root = q;




        }







    auto find(const T& v) -> std::vector<T>{
        auto& self = *this;
# 1512 "b_mem.cpp"
        node




        r = self.root;
        if (r == nullptr)




            {
            return std::vector<T>();
            }





        assert (r != nullptr);







        auto




        f = node_find_path(r, v);
        if (not list_size(f))




            {
            return std::vector<T>();
# 1560 "b_mem.cpp"
            }
# 1573 "b_mem.cpp"
        auto&




        _f = f[0];





        return std::vector<T>({tuple_get_0(_f).data()[tuple_get_1(_f)]});
        }







    auto contains(const T& v) -> bool{
        auto& self = *this;





        return bool(len(self.find(v)));




        }







    auto remove(const T& v) -> void{
        auto& self = *this;
# 1623 "b_mem.cpp"
        node




        r = self.root;
        if (r == nullptr)




            {




            return;




            }




        assert (r != nullptr);







        auto




        a = node_find_path(r, v);
        if (not list_size(a))




            {




            return;




            }




        assert (list_size(a));




        list_reverse(a);
        if (tuple_get_0(a[list_size(a)-1]).down()[0] != nullptr)




            {







            node




            t = tuple_get_0(a[list_size(a)-1]).down()[list_index(tuple_get_0(a[list_size(a)-1]).data(), v) + 1];




            assert (t != nullptr);

            while (t.down()[0] != nullptr)




                {




                t = t.down()[0];




                assert (t != nullptr);




                }







            auto




            kw = t.data()[0];
            r = node_erase(r, kw, self.max_len);
            a = node_find_path(r, v);




            assert (list_size(a));




            int64_t




            t_ = list_index(tuple_get_0(a[0]).data(), v);
            r = node_chval(r, a, t_, kw, list_size(a) - 1);




            }




        else if (true)




            {




            r = node_erase(r, v, self.max_len);




            }




        if (list_size(r.data()) == 0)




            {




            r = r.down()[0];




            }




        self.root = r;




        }
# 1829 "b_mem.cpp"
    auto to_list() -> std::vector<T>{
        auto& self = *this;
# 1839 "b_mem.cpp"
        node




        r = self.root;
        if (r == nullptr)




            {
# 1859 "b_mem.cpp"
            return std::vector<T>();
            }






        assert (r != nullptr);




        return node_to_list(r, std::vector<T>());
# 1884 "b_mem.cpp"
    return std::vector<T>();
    }







};
# 1914 "b_mem.cpp"
    template<typename K, typename V>
    struct item{
        K k;
        std::optional<V> v;
# 1972 "b_mem.cpp"
    auto operator<(const item<K, V>& o) -> bool{
        auto& self = *this;





        return self.k < o.k;




        }







    auto operator==(const item<K, V>& o) -> bool{
        auto& self = *this;
# 2003 "b_mem.cpp"
            {







            return self.k == o.k;




            }
# 2028 "b_mem.cpp"
        }
# 2037 "b_mem.cpp"
    auto to_list() -> std::pair<K, std::optional<V>>{
        auto& self = *this;
# 2047 "b_mem.cpp"
        return {k, v};
# 2056 "b_mem.cpp"
        }
# 2065 "b_mem.cpp"
    };
# 2075 "b_mem.cpp"
template<typename K, typename V>
struct b_dict{
    b_set<item<K, V>> b_set_;
# 2091 "b_mem.cpp"
    auto operator[](const K& k) -> V{
        auto& self = *this;
# 2101 "b_mem.cpp"
        auto




        r = self.b_set.find(item(k));
        if (not r)




            {
            return std::optional<V>();
# 2123 "b_mem.cpp"
            }







        auto




        tmp = r[0].v;




        assert (tmp != nullptr);




        return {tmp};
# 2155 "b_mem.cpp"
        }







    auto setitem(const K& k, V&&v) -> void{
        auto& self = *this;





        self.b_set.add(item(k, v));




        }







    auto delitem(const K& k) -> void{
        auto& self = *this;





        self.b_set.remove(item(k));




        }







    auto contains(const K& k) -> bool{
        auto& self = *this;





        return bool(self.b_set.find(item(k)));




        }
# 2236 "b_mem.cpp"
    };




const char* x__2241 = """_" "_""";
# 2839 "b_mem.cpp"
int main(){
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
    assert( a.contains(8));
    assert(not a.contains(7));
    assert( a.contains(6));
    assert(not a.contains(5));
    assert( a.contains(4));
    assert(not a.contains(3));
    assert(not a.contains(2));

    a = b_set<int>();
    std::set<int> s;

    std::mt19937_64 rand;
    for (size_t q = 0; q < 999999; ++q){
        std::vector<std::function<void()>> funcs;
        funcs.push_back([&](){
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            int64_t w = rand();
            assert(s.count(w) == a.contains(w));
            a.add(w);
            s.insert(w);
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
        });
        funcs.push_back([&](){
            std::vector<int> g(s.begin(), s.end());
            int64_t d = rand();
            int w = g[d%g.size()];
            assert(s.count(w));
            assert(a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
        });
        funcs.push_back([&](){
            int w = rand();
            assert(s.count(w) == a.contains(w));
            s.erase(w);
            a.remove(w);
            assert(not s.count(w));
            assert(not a.contains(w));
        });
        funcs.push_back([&](){
            auto tmp = a;
            a = tmp;
        });
    }
}
