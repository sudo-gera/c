#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#ifndef assert
#include <cassert>
#endif
#include <tuple>
#include <numeric>
#include <list>
#include <string_view>
#include <cstring>
#include <functional>
#include <type_traits>
#include <deque>
#include <array>
#include <queue>
#include <stack>
#include <random>
#include <string_view>
#include <memory>
#include <sstream>
#include <unistd.h>
using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::stack;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::string_view, std::random_device, std::mt19937, std::mt19937_64;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::uniform_int_distribution, std::make_unique, std::make_shared;
using std::unique, std::decay_t, std::is_convertible_v, std::array;
using std::unique_ptr, std::shared_ptr, std::transform, std::apply;
using std::stringstream, std::istream, std::ostream;

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
        // Y val;
        // cin >> val;
        // return val;
        return *this;
    }
    template <typename Y = T>
    operator Y() {  // NOLINT
        Y val;
        cin >> val;
        return val;
    }
};

auto scan = Scan();

struct Mod {
    __int128_t a = 0;
};

auto operator%(__int128_t a, Mod) {
    return Mod{a};
}

auto operator%(Mod a, __int128_t b) {
    return (a.a % b + b) % b;
}

auto mod = Mod();

template <typename T>
auto ScanVector(T& x) {
    generate_n(x.begin(), x.size(), scan);
}

///////////////////////////////////////////////////end of lib

template <typename T>
struct Vect;

template <typename T>
auto operator*(Vect<T>, T);

template <typename T>
auto operator*(Vect<T>, Vect<T>);

template <typename T>
struct Vect {
    T x = 0;
    T y = 0;
    auto& operator*=(T e) {
        *this = *this * e;
        return *this;
    }
    auto& operator+=(Vect<T> e) {
        *this = *this + e;
        return *this;
    }
    Vect operator-() const {
        return {-x, -y};
    }
    auto tuple() {  // NOLINT
        return make_tuple(x, y);
    }
    auto SqAbs() {
        return x * x + y * y;
    }
};

template <typename T, typename Y>
decltype(0<=>0) operator<=>(T q, Y w) {
    return int((w < q) - (q < w))<=>0;
}

template <typename T>
auto operator<=>(Vect<T> q, Vect<T> e) {
    return q.tuple() <=> e.tuple();
}

template <typename T>
bool operator==(Vect<T> q, Vect<T> e) {
    return q.tuple() == e.tuple();
}

template <typename T>
auto& operator>>(istream& s, Vect<T>& v) {
    s >> v.x >> v.y;
    return s;
}

template <typename T>
auto operator*(Vect<T> q, Vect<T> w) {
    return q.x * w.x + q.y * w.y;
}

template <typename T>
auto operator/(Vect<T> q, Vect<T> w) {
    return q.x * w.y - q.y * w.x;
}

template <typename T>
auto operator*(Vect<T> q, T e) {
    return Vect<T>{q.x * e , q.y * e};
}

template <typename T>
auto operator/(Vect<T> q, T e) {
    return Vect<T>{q.x / e , q.y / e};
}

template <typename T>
auto operator*(T q, Vect<T> e) {
    return Vect<T>{q * e.x , q * e.y};
}

template <typename T>
auto operator+(Vect<T> q, Vect<T> w) {
    return Vect<T>{q.x + w.x, q.y + w.y};
}

template <typename T>
auto operator-(Vect<T> q, Vect<T> w) {
    return Vect<T>{q.x - w.x, q.y - w.y};
}

auto Sign(auto t) {
    return (t > 0) - (t < 0);
}

auto Abs(auto a) {
    return a < 0 ? -a : a;
}

using Point=Vect<int>;

struct Triangle{
    Point q[3];
    Triangle* r[3]{0,0,0};
    Triangle(Point a,Point s,Point d){
        q[0]=a;
        q[1]=s;
        q[2]=d;
    }
};

struct Line{
    Point q;
    Point w;
    Line(Point a,Point s){
        q=min(a,s);
        w=max(a,s);
    }
    auto tuple(){
        return make_tuple(q,w);
    }
    // Triangle* e=nullptr;
    // Triangle* r=nullptr;
};

bool operator<(Line q,Line e){
    return q.tuple()<e.tuple();
}

void Replace(Triangle*q,Triangle*s,Triangle*r){
    assert(q);
    for (size_t e=0;;++e){
        assert(e<3);
        if (q->r[e]==s){
            q->r[e]=r;
            break;
        }
    }
}

void Link(Triangle*q,Triangle*w){
    Replace(q,nullptr,w);
    Replace(w,nullptr,q);
}

void UnLink(Triangle*q,Triangle*w){
    Replace(q,w,nullptr);
    Replace(w,q,nullptr);
}

map<
    Line,
    pair<Triangle*,Triangle*>
> t_by_l;

deque<Triangle> ts;

void Draw(Triangle&t);

void CreateTriangle(auto&&...args){
    ts.emplace_back(std::forward<decltype(args)>(args)...);
    Triangle* t=&ts.back();
    Draw(*t);
    for (size_t q=0;q<3;++q){
        auto l=Line(t->q[q],t->q[(q+1)%3]);
        auto&tp=t_by_l[l];
        if (tp.first){
            tp.second=t;
        }else{
            tp.first=t;
        }
    }
}

Point* Common(Triangle*q,Triangle*w,Triangle*e){
    for (auto&a:q->q){
        for (auto&s:w->q){
            for (auto&d:e->q){
                if (a==s and s==d){
                    return &a;
                }
            }
        }
    }
    return nullptr;
}

// void Flip(Triangle*q,Triangle*w){
//     assert(q and w);
//     UnLink(q,w);
//     Link(q,w);
//     Triangle* a[4];
//     size_t as=0;
//     for (auto e:q->r){
//         if (e!=w){
//             a[as++]=e;
//             UnLink(q,e);
//         }
//     }
//     assert(as==2);
//     for (auto e:w->r){
//         if (e!=q){
//             a[as++]=e;
//             UnLink(w,e);
//         }
//     }
//     assert(as==4);
//     UnLink(q,w);
//     if (
//         // not Common(q,a[2],a[3])
//     ){
//         swap(a[2],a[3]);
//     }
// }

stringstream screen;

void Draw(Point p,size_t color=0){
    // screen<<"pygame.draw.circle(screen, ("<<color<<","<<color<<","<<color<<"), ("<<p.x*64+400<<", "<<-p.y*64+400<<"), 4, 1)\n";
    screen<<"pygame.draw.circle(screen, ("<<color<<","<<color<<","<<color<<"), ("<<p.x+400<<", "<<-p.y+400<<"), 4, 1)\n";
}

void Draw(Line l,size_t color=0){
    // ic(l)
    // screen<<"pygame.draw.line(screen, ("<<color<<","<<color<<","<<color<<") , ("<<l.q.x*64+400<<","<<-l.q.y*64+400<<"), ("<<l.w.x*64+400<<","<<-l.w.y*64+400<<"))\n";
    screen<<"pygame.draw.line(screen, ("<<color<<","<<color<<","<<color<<") , ("<<l.q.x+400<<","<<-l.q.y+400<<"), ("<<l.w.x+400<<","<<-l.w.y+400<<"))\n";
}

void Draw1(Line l,size_t color=0){
    // ic(l)
    color=min(color,size_t(255));
    screen<<"pygame.draw.line(screen, ("<<color<<","<<color<<","<<color<<") , ("<<l.q.x+400<<","<<-l.q.y+400<<"), ("<<l.w.x+400<<","<<-l.w.y+400<<"))\n";
}

void Draw(Triangle&t){
    auto c=(t.q[0]+t.q[1]+t.q[2]);
    for (int q=0;q<1;++q){
        auto color=q;
        Draw1(Line{(t.q[0]*(255-q)+c*q/3)/255,(t.q[1]*(255-q)+c*q/3)/255},q);
        Draw1(Line{(t.q[1]*(255-q)+c*q/3)/255,(t.q[2]*(255-q)+c*q/3)/255},q);
        Draw1(Line{(t.q[2]*(255-q)+c*q/3)/255,(t.q[0]*(255-q)+c*q/3)/255},q);
    }
    // Draw(Line{t.q,t.w});
    // Draw(Line{t.w,t.e});
    // Draw(Line{t.e,t.q});
    Draw(t.q[0]);
    Draw(t.q[1]);
    Draw(t.q[2]);
}

int main(){
    size_t n=scan;
    vector<Point> a(n);
    ScanVector(a);
    // for (auto q:a){
    //     Draw(q);
    // }
    sort(a.begin(), a.end(), [&](auto q, auto e) { return make_tuple(q.x, q.y) < make_tuple(e.x, e.y); });
    sort(a.begin() + 1, a.end(), [&](auto q, auto e) {
        auto w = (q - a[0]) / (e - a[0]);
        if (w == 0) {
        // if ( (q - a[0]).SqAbs()*1LLU*(e - a[0]).SqAbs()>1LLU*w*w*100  ) {
            w = ((q - a[0]).SqAbs() - (e - a[0]).SqAbs());
        }
        return w > 0;
    });
    vector<Point> s({a[0]});
    Point* last=nullptr;
    for (size_t q=1;q<a.size();++q){
        if ((a[0]-s.back())/(a[q]-s.back())){
            if (last){
                CreateTriangle(a[0],a[q-1],*last);
            }
            last=&a[q-1];
            // Draw(Line{s.back(),a[q]});
            // Draw(Line{s.back(),a[0]});
            int tmp=0;
            while (s.size() > 1 and (tmp=(a[q]-s.end()[-1])/(s.end()[-1]-s.end()[-2])) >= 0){
                if (tmp>0){
                    CreateTriangle(s.end()[-1],s.end()[-2],a[q]);
                }
                s.pop_back();
                if (tmp>0){
                    // Draw(Line{s.back(),a[q]});
                }
            }
            s.push_back(a[q]);
        }else{
            if (q!=1){
                // Draw(Line{a[q],s.back()});
            }
            if (last){
                CreateTriangle(a[q],s.back(),*last);
            }
            s.push_back(a[q]);
            if (last){
                // Draw(Line{a[q],*last});
            }
        }
    }
    CreateTriangle(a.front(),a.back(),*last);
    // Draw(Line{a.front(),a.back()});
    cout<<screen.str()<<endl;

    // for (auto&q:t_by_l){
    //     if (q.second.first and q.second.second){
    //         Link(q.second.first,q.second.second);
    //     }
    // }



}
