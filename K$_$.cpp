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
#include <fstream>
#include <utility>
using std::back_inserter, std::list, std::hash, std::reverse, std::queue;
using std::cerr;
using std::cin, std::cout, std::endl, std::vector, std::string, std::sort;
using std::copy_if, std::exit, std::enable_if, std::enable_if, std::stack;
using std::generate, std::generate_n, std::remove_reference_t, std::iota;
using std::lower_bound, std::upper_bound, std::flush, std::prev, std::next;
using std::min, std::max, std::tuple, std::tie, std::get, std::make_tuple;
using std::move, std::swap, std::generate, std::generate_n, std::deque;
using std::pair, std::set, std::unordered_set, std::map, std::unordered_map;
using std::ref, std::cref, std::reference_wrapper, std::remove_reference;
using std::string_view, std::random_device, std::mt19937, std::mt19937_64;
using std::stringstream, std::istream, std::ostream, std::rotate;
using std::tuple_cat, std::find, std::find_if, std::find_if_not;
using std::tuple_element, std::tuple_size, std::is_same, std::forward;
using std::tuple_size, std::lexicographical_compare, std::set_intersection;
using std::tuple_size_v, std::is_same_v, std::enable_if_t, std::tuple_element_t;
using std::uniform_int_distribution, std::make_unique, std::make_shared;
using std::unique, std::decay_t, std::is_convertible_v, std::array;
using std::unique_ptr, std::shared_ptr, std::transform, std::apply;

template <typename T = void>
struct Scan {
    template <typename Y = T>
    auto operator()() {
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
auto PushBack(T& a, typename T::value_type s) {
    a.push_back(s);
}

auto Sqrt(auto q) {
    return sqrt(static_cast<double>(q));
}

#ifndef ic
#define ic(...)
#endif

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
    auto tuple() const {  // NOLINT
        return make_tuple(x, y);
    }
    auto SqAbs() {
        return x * x + y * y;
    }
#ifdef __all__
    __all__(x, y)
#endif
};

// template <typename T, typename Y>
// decltype(0 <=> 0) operator<=>(T q, Y w) {
//     return int((w < q) - (q < w)) <=> 0;
// }

template <typename T>
auto operator<(Vect<T> q, Vect<T> e) {
    return q.tuple() < e.tuple();
}

template <typename T>
auto operator>(Vect<T> q, Vect<T> e) {
    return q.tuple() > e.tuple();
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
    return Vect<T>{q.x * e, q.y * e};
}

template <typename T>
auto operator/(Vect<T> q, T e) {
    return Vect<T>{q.x / e, q.y / e};
}

template <typename T>
auto operator*(T q, Vect<T> e) {
    return Vect<T>{q * e.x, q * e.y};
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

////////////////////////////////////////////////////////////////////////////

// #define CHECK

vector<array<size_t, 3>> colors = {{230, 25, 75},   {60, 180, 75},   {255, 225, 25},  {67, 99, 216},   {245, 130, 49},
                                   {145, 30, 180},  {70, 240, 240},  {240, 50, 230},  {188, 246, 12},  {250, 190, 190},
                                   {0, 128, 128},   {230, 190, 255}, {154, 99, 36},   {255, 250, 200}, {128, 0, 0},
                                   {170, 255, 195}, {128, 128, 0},   {255, 216, 177}, {0, 0, 117},     {128, 128, 128},
                                   {255, 255, 255}, {0, 0, 0}};
auto colors_ptr = colors.begin();
using BestInt = long long;  //  NOLINT
using BestFloat = long double;

using Point = Vect<BestInt>;
using FPoint = Vect<BestFloat>;

struct Line {
    Point q;
    Point w;
    Line(Point a, Point s) {
        q = min(a, s);
        w = max(a, s);
    }
    auto tuple() const {  //  NOLINT
        return make_tuple(q, w);
    }
#ifdef __all__
    __all__(q, w)
#endif
};

struct Triangle;

using GlobalLine = pair<const Line, pair<Triangle*, Triangle*>>;

struct Triangle {
    Triangle(Triangle&&) = delete;
    Triangle(const Triangle&) = delete;
    array<Point, 3> q;
    array<Triangle*, 3> r = {0, 0, 0};
    array<size_t, 3> c = {0, 0, 0};
    array<GlobalLine*, 3> l = {0, 0, 0};
    array<bool, 3> s = {false, false, false};
    size_t n = -1;
    Triangle* self = nullptr;
    Triangle(Point a, Point s, Point d) {
        q[0] = a;
        q[1] = s;
        q[2] = d;
        if ((d - s) / (s - a) < 0) {
            swap(q[2], q[1]);
        }
        self = this;
    }
    void Rotate(size_t n) {
#ifdef CHECK
        assert(n != 3);
#endif
        rotate(q.begin(), q.begin() + n, q.end());
        rotate(r.begin(), r.begin() + n, r.end());
        rotate(l.begin(), l.begin() + n, l.end());
        rotate(s.begin(), s.begin() + n, s.end());
    }
    void Replace(Triangle* s, Triangle* r) {
        auto q = this;
        assert(q);
        for (size_t e = 0; e < 3; ++e) {
            if (q->r[e] == s) {
                q->r[e] = r;
                break;
            }
        }
    }
    void Check() {
        for (size_t w = 0; w < 3; ++w) {
            if (r[w]) {
                size_t c = 0;
                for (size_t e = 0; e < 3; ++e) {
                    if (r[w]->r[e] == this) {
                        c += 1;
                        assert(r[w]->q[(e + 1) % 3] == q[(w + 2) % 3]);
                        assert(r[w]->q[(e + 2) % 3] == q[(w + 1) % 3]);
                    }
                }
                assert(c == 1);
            }
            if (l[w]) {
                size_t c = 0;
                if (l[w]->second.first == this) {
                    assert(l[w]->second.second == r[w]);
                    c += 1;
                }
                if (l[w]->second.second == this) {
                    assert(l[w]->second.first == r[w]);
                    c += 1;
                }
                assert(c == 1);
            }
        }
    }
    auto CircumCenter() {
        array<FPoint, 3> w;
        for (size_t e = 0; e < 3; ++e) {
            w[e] = {static_cast<BestFloat>(q[e].x), static_cast<BestFloat>(q[e].y)};
        }
        array<BestFloat, 3> s;
        for (size_t e = 0; e < 3; ++e) {
            s[e] = (w[(e + 1) % 3] - w[e]).SqAbs();
            s[e] *= (w[(e + 2) % 3] - w[e]).SqAbs();
            s[e] = Sqrt(s[e]);
            s[e] = (w[(e + 1) % 3] - w[e]) / (w[(e + 2) % 3] - w[e]) / s[e];
        }
        array<BestFloat, 3> c;
        for (size_t e = 0; e < 3; ++e) {
            c[e] = (w[(e + 1) % 3] - w[e]).SqAbs();
            c[e] *= (w[(e + 2) % 3] - w[e]).SqAbs();
            c[e] = Sqrt(c[e]);
            c[e] = (w[(e + 1) % 3] - w[e]) * (w[(e + 2) % 3] - w[e]) / c[e];
        }
        array<BestFloat, 3> d;
        for (size_t e = 0; e < 3; ++e) {
            d[e] = s[e] * c[e] * 2;
        }
        FPoint num = {0, 0};
        BestFloat den = 0;
        for (size_t e = 0; e < 3; ++e) {
            num += d[e] * w[e];
            den += d[e];
        }
        return num / den;
    }
#ifdef __all__
    __all__(q, r, c, self, l, s, n)
#endif
};

/// source https://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set

namespace std {
namespace {

/// Code from boost
/// Reciprocal of the golden ratio helps spread entropy
///     and handles duplicates.
/// See Mike Seymour in magic-numbers-in-boosthash-combine:
///     http://stackoverflow.com/questions/4948780

template <class T>
inline void hash_combine(std::size_t& seed, T const& v)  //  NOLINT
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    static void apply(size_t& seed, Tuple const& tuple)  //  NOLINT
    {
        HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
    }
};

template <class Tuple>
struct HashValueImpl<Tuple, 0> {
    static void apply(size_t& seed, Tuple const& tuple)  //  NOLINT
    {
        hash_combine(seed, std::get<0>(tuple));
    }
};
}  // namespace

template <typename... TT>
struct hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const& tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};
}  // namespace std

template <typename T>
concept tuplable = requires(T v) { v.tuple(); };

template <tuplable T>
struct std::hash<T> {
    auto operator()(auto&& v) const {
        return std::hash<decltype(v.tuple())>()(v.tuple());
    }
};

bool operator<(Line q, Line e) {
    return q.tuple() < e.tuple();
}

bool operator==(Line q, Line e) {
    return q.tuple() == e.tuple();
}

void Link(GlobalLine* l) {
    Triangle* q = l->second.first;
    Triangle* w = l->second.second;
    for (size_t a = 0; a < 3; ++a) {
        for (size_t s = 0; s < 3; ++s) {
            if (q->q[2] == w->q[1] and q->q[1] == w->q[2]) {
#ifdef CHECK
                assert(q->r[0] == nullptr);
                assert(w->r[0] == nullptr);
#endif
                q->Replace(nullptr, w);
                w->Replace(nullptr, q);
                return;
            }
            w->Rotate(1);
        }
        q->Rotate(1);
    }
}

// void UnLink(GlobalLine* l) {
//     Triangle* q=l->second.first;
//     Triangle* w=l->second.second;
//     q->Replace(w, nullptr);
//     w->Replace(q, nullptr);
// }

void Rotate(GlobalLine* l) {
    Triangle* q = l->second.first;
    Triangle* w = l->second.second;
    q->Rotate(find(q->r.begin(), q->r.end(), w) - q->r.begin());
    w->Rotate(find(w->r.begin(), w->r.end(), q) - w->r.begin());
}

unordered_map<Line, pair<Triangle*, Triangle*>> edges;

vector<FPoint> nodes;

deque<Triangle> ts;

void Draw(Triangle& t);

void SetupEdges(Triangle* t) {
    for (size_t q = 0; q < 3; ++q) {
        auto l = Line(t->q[(q + 2) % 3], t->q[(q + 1) % 3]);
        auto& tp = edges[l];
        if (tp.first) {
            if (tp.second) {
                ic(t[0]) ic(tp.first[0]) ic(tp.second[0])
            }
            assert(tp.second == nullptr);
            tp.second = t;
        } else {
            tp.first = t;
        }
        t->l[q] = &*edges.find(l);
    }
}

void CreateTriangle(auto&&... args) {
    ts.emplace_back(std::forward<decltype(args)>(args)...);
    Triangle* t = &ts.back();
    t->c = *colors_ptr++;
    if (colors_ptr == colors.end()) {
        colors_ptr = colors.begin();
    }
    SetupEdges(t);
}

auto IfRound(GlobalLine* l) {
    Triangle* q = l->second.first;
    Triangle* w = l->second.second;
    auto t =
        __int128_t((q->q[1] - q->q[0]) / (q->q[2] - q->q[0])) * __int128_t((w->q[1] - w->q[0]) * (w->q[2] - w->q[0])) +
        __int128_t((q->q[1] - q->q[0]) * (q->q[2] - q->q[0])) * __int128_t((w->q[1] - w->q[0]) / (w->q[2] - w->q[0]));
    return t;
}

bool Flip(GlobalLine* l) {
    Triangle* q = l->second.first;
    Triangle* w = l->second.second;
    // ic(*q)
    // ic(*w)
    Rotate(l);
#ifdef CHECK
    // assert(edges.count(Line({q->q[1], q->q[2]})));
#endif
    array<Point, 8> a = {
        q->q[0], q->q[1], w->q[0], w->q[1], q->q[0], q->q[1], w->q[0], w->q[1],
    };
    int s = 0;
    for (size_t d = 0; d < 4; ++d) {
        s += Sign((a[d] - a[d + 1]) / (a[d + 1] - a[d + 2]));
    }
    if (abs(s) != 4) {
        return false;
    }
    // ic(*q)
    // ic(*w)
    auto t = IfRound(l);
    // ic(t)
    if (t <= 0) {
        return false;
    }
#ifdef CHECK
    // auto node=edges.extract(Line({q->q[1], q->q[2]}));
#endif
    tie(q->q, q->r, q->l, w->q, w->r, w->l) =
        make_tuple(decltype(q->q){q->q[2], q->q[0], w->q[0]}, decltype(q->r){q->r[0], w->r[2], q->r[1]},
                   decltype(q->l){q->l[0], w->l[2], q->l[1]}, decltype(w->q){w->q[2], w->q[0], q->q[0]},
                   decltype(w->r){w->r[0], q->r[2], w->r[1]}, decltype(w->l){w->l[0], q->l[2], w->l[1]});
#ifdef CHECK
    // node.key()=Line({q->q[1], q->q[2]});
    // edges.insert(move(node));
#endif
    if (q->r[1]) {
        q->r[1]->Replace(w, q);
#ifdef CHECK
        assert(q->l[1]->second.first == w or q->l[1]->second.second == w);
#endif
        (q->l[1]->second.first == w ? q->l[1]->second.first : q->l[1]->second.second) = q;
    }
    if (w->r[1]) {
        w->r[1]->Replace(q, w);
#ifdef CHECK
        assert(w->l[1]->second.first == q or w->l[1]->second.second == q);
#endif
        (w->l[1]->second.first == q ? w->l[1]->second.first : w->l[1]->second.second) = w;
    }
#ifdef CHECK
    // edges[{q->q[0], q->q[2]}] = {q, q->r[1]};
    // edges[{w->q[0], w->q[2]}] = {w, w->r[1]};
    for (auto t : q->r) {
        if (t) {
            assert(t->r[0] == q or t->r[1] == q or t->r[2] == q);
        }
    }
    for (auto t : w->r) {
        if (t) {
            assert(t->r[0] == w or t->r[1] == w or t->r[2] == w);
        }
    }
    // ic(*q)
    // ic(*w)
    t = IfRound(l);
    // ic(t)
    assert(t < 0);
#endif
    return true;
}

#if __has_include("/Users/gera/c/test.py__1")
std::ofstream screen("stream.py");

void Draw(Point p, size_t color = 0) {
    screen << "pygame.draw.circle(screen, (" << color << "," << color << "," << color << "), (" << p.x + 400 << ", "
           << -p.y + 400 << "), 4, 1)\n";
}

void Draw(Line l, size_t color = 0) {
    screen << "pygame.draw.line(screen, (" << color << "," << color << "," << color << ") , (" << l.q.x + 400 << ","
           << -l.q.y + 400 << "), (" << l.w.x + 400 << "," << -l.w.y + 400 << "))\n";
}

void Draw1(Line l, array<size_t, 3>& color) {
    for (auto& w : color) {
        w = (size_t)min(BestInt(w), BestInt(255));
    }
    screen << "pygame.draw.line(screen, (" << color[0] << "," << color[1] << "," << color[2] << ") , (" << l.q.x + 400
           << "," << -l.q.y + 400 << "), (" << l.w.x + 400 << "," << -l.w.y + 400 << "))\n";
}

void Draw2(Line l, array<size_t, 3>& color, array<size_t, 3>& color1) {
    Draw1(Line{(l.q * BestInt(3) + l.w * BestInt(0)) / BestInt(3), (l.q * BestInt(2) + l.w * BestInt(1)) / BestInt(3)},
          color);
    Draw1(Line{(l.q * BestInt(2) + l.w * BestInt(1)) / BestInt(3), (l.q * BestInt(1) + l.w * BestInt(2)) / BestInt(3)},
          color);
    Draw1(Line{(l.q * BestInt(1) + l.w * BestInt(2)) / BestInt(3), (l.q * BestInt(0) + l.w * BestInt(3)) / BestInt(3)},
          color);
}

void Draw(Triangle& t) {
    auto c = (t.q[0] + t.q[1] + t.q[2]);
    auto a = array<array<size_t, 3>, 4>({t.r[0] ? t.r[0]->c : decltype(t.c){2550, 2550, 2550},
                                         t.r[1] ? t.r[1]->c : decltype(t.c){2550, 2550, 2550},
                                         t.r[2] ? t.r[2]->c : decltype(t.c){2550, 2550, 2550}, t.c});
    for (long long q = 0; q < 256; ++q) {
        for (long long qq = -1; qq < 2; ++qq) {
            auto qqq = q;
            auto s = a;
            for (auto& d : s) {
                d[0] = d[0] * q / 256;
                d[1] = d[1] * q / 256;
                d[2] = d[2] * q / 256;
            }
            auto qqp = Point{qq, qq};
            Draw2(Line{(t.q[0] * BestInt(256 - 1 - qqq) + c * BestInt(qqq) / BestInt(3)) / (256 - BestInt(1)) + qqp,
                       (t.q[1] * BestInt(256 - 1 - qqq) + c * BestInt(qqq) / BestInt(3)) / (256 - BestInt(1)) + qqp},
                  s[3], s[2]);
            Draw2(Line{(t.q[1] * BestInt(256 - 1 - qqq) + c * BestInt(qqq) / BestInt(3)) / (256 - BestInt(1)) + qqp,
                       (t.q[2] * BestInt(256 - 1 - qqq) + c * BestInt(qqq) / BestInt(3)) / (256 - BestInt(1)) + qqp},
                  s[3], s[0]);
            Draw2(Line{(t.q[2] * BestInt(256 - 1 - qqq) + c * BestInt(qqq) / BestInt(3)) / (256 - BestInt(1)) + qqp,
                       (t.q[0] * BestInt(256 - 1 - qqq) + c * BestInt(qqq) / BestInt(3)) / (256 - BestInt(1)) + qqp},
                  s[3], s[1]);
        }
    }
}
#endif

void Check() {
    for (auto& t : ts) {
        t.Check();
    }
    for (auto& p : edges) {
        if (p.second.first) {
            auto& t = p.second.first[0];
            size_t c = 0;
            for (size_t q = 0; q < 3; ++q) {
                if (Line{t.q[(q + 1) % 3], t.q[(q + 2) % 3]} == p.first) {
                    c += 1;
                    assert(t.r[q] == p.second.second);
                    assert(t.l[q] == &p);
                }
            }
            assert(c == 1);
        }
        if (p.second.second) {
            auto& t = p.second.second[0];
            size_t c = 0;
            for (size_t q = 0; q < 3; ++q) {
                if (Line{t.q[(q + 1) % 3], t.q[(q + 2) % 3]} == p.first) {
                    c += 1;
                    assert(t.r[q] == p.second.first);
                    assert(t.l[q] == &p);
                }
            }
            assert(c == 1);
        }
    }
}

void ConvexHull(vector<Point>& a) {
    sort(a.begin(), a.end(), [&](auto q, auto e) { return make_tuple(q.x, q.y) < make_tuple(e.x, e.y); });
    sort(a.begin() + 1, a.end(), [&](auto q, auto e) {
        auto w = (q - a[0]) / (e - a[0]);
        if (w == 0) {
            w = ((q - a[0]).SqAbs() - (e - a[0]).SqAbs());
        }
        return w > 0;
    });
    vector<Point> s({a[0]});
    Point* last = nullptr;
    for (size_t q = 1; q < a.size(); ++q) {
        if ((a[0] - s.back()) / (a[q] - s.back())) {
            if (last) {
                CreateTriangle(a[0], a[q - 1], *last);
            }
            last = &a[q - 1];
            BestInt tmp = 0;
            while (s.size() > 1 and (tmp = (a[q] - s.end()[-1]) / (s.end()[-1] - s.end()[-2])) >= 0) {
                if (tmp > 0) {
                    CreateTriangle(s.end()[-1], s.end()[-2], a[q]);
                }
                s.pop_back();
            }
            s.push_back(a[q]);
        } else {
            if (last) {
                CreateTriangle(a[q], s.back(), *last);
            }
            s.push_back(a[q]);
        }
    }
    CreateTriangle(a.front(), a.back(), *last);
}

struct Dsu {
    struct DsuNode {
        size_t prev = 0;
        size_t size = 0;
#ifdef __all__
        __all__(prev, size)
#endif
    };
    vector<DsuNode> nodes;
#ifdef __all__
    __all__(nodes)
#endif
        explicit Dsu(size_t n)
        : nodes(n) {
        for (size_t q = 0; q < n; ++q) {
            nodes[q] = {q, 1};
        }
    }
    size_t NumOfSet(size_t n) {
        if (nodes[n].prev != n) {
            nodes[n].prev = NumOfSet(nodes[n].prev);
        }
        return nodes[n].prev;
    }
    void Merge(size_t left, size_t right) {
        left = NumOfSet(left);
        right = NumOfSet(right);
        if (nodes[left].size > nodes[right].size) {
            nodes[left].size += nodes[right].size;
            nodes[right].prev = left;
        } else {
            nodes[right].size += nodes[left].size;
            nodes[left].prev = right;
        }
    }
};

int main() {
    // auto cl=clock();
    // size_t seed = 0;
    size_t n = scan;
    vector<Point> a(n);
    for (auto& q : a) {
        long double tmp = 0;
        cin >> tmp;
        q.x = llroundl(tmp * 1000);
        cin >> tmp;
        q.y = llroundl(tmp * 1000);
    }
    // ScanVector(a);
    auto o = a;
    sort(a.begin(), a.end());
    vector<Line> d;
    vector<pair<size_t, size_t>> h;
    if (n == 0) {
        return 0;
    }
    size_t c = 0;
    for (size_t q = 0; q < a.size(); ++q) {
        if ((a[(q + 0) % a.size()] - a[(q + 1) % a.size()]) / (a[(q + 1) % a.size()] - a[(q + 2) % a.size()])) {
            c = 1;
            break;
        }
    }
    if (c == 0) {
        h.resize(a.size() - 1);
        for (size_t q = 1; q < a.size(); ++q) {
            h[q - 1] = {q - 1, q};
        }
    } else {
        ConvexHull(a);

        for (auto& q : edges) {
            if (q.second.first and q.second.second) {
                Link(&q);
            }
        }
#ifdef CHECK
        Check();
#endif

        size_t c = -1;
        deque<GlobalLine*> tq;
        for (auto& p : edges) {
            tq.push_back(&p);
        }

        auto tmp = std::move(edges);
        assert(edges.empty());

        while (not tq.empty()) {
            auto l = tq.front();
            tq.pop_front();
            // if (true){
            auto tp = l->second;
            if (tp.first and tp.second) {
#ifdef CHECK
                // check();
#endif
                if (c-- == 0) {
                    break;
                }
                if (Flip(l)) {
                    tq.push_back(tp.first->l[2]);
                    tq.push_back(tp.first->l[1]);
                    tq.push_back(tp.second->l[2]);
                    tq.push_back(tp.second->l[1]);
                }
            }
            // }
        }

        // cerr<<__LINE__<<" "<<clock()-cl<<endl;
        // cl=clock();

        for (auto& q : ts) {
            PushBack(d, {q.q[0], q.q[1]});
            PushBack(d, {q.q[1], q.q[2]});
            PushBack(d, {q.q[2], q.q[0]});
        }
#ifdef CHECK
        // for (auto&q:d){
        //     assert(edges.count(q));
        //     auto&tp=*edges.find(q);
        //     if (tp.second.first and tp.second.second){
        //         assert(not Flip(&tp));
        //     }
        // }
#endif
        tmp.clear();
        edges.clear();
        for (auto& t : ts) {
            SetupEdges(&t);
        }

#ifdef CHECK
        Check();
#endif

        {
            auto& a = o;
            unordered_map<Point, size_t> s;
            for (auto& p : a) {
                s[p] = &p - &a[0];
            }

            vector<pair<size_t, size_t>> f;
            for (auto& p : edges) {
                PushBack(f, {s[p.first.q], s[p.first.w]});
            }
            // ic(f)
            sort(f.begin(), f.end(), [&](auto&& q, auto&& w) {
                return (a[q.first] - a[q.second]).SqAbs() < (a[w.first] - a[w.second]).SqAbs();
            });
            // ic(f)

            Dsu g(a.size());

            // ic(f)
            // ic(g)

            for (auto& p : f) {
                // ic(p.first,a[p.first])
                // ic(p.second,a[p.second])
                auto z = g.NumOfSet(p.first);
                auto x = g.NumOfSet(p.second);
                // ic(z,x)
                if (z != x) {
                    h.push_back(p);
                    g.Merge(z, x);
                }
                // ic(g)
            }
        }

        // for (auto&p:edges){
        //     auto&tp=p.second;
        //     if (tp.first and tp.second){
        //         Rotate(&p);
        //         if (IfRound(&p)==0){
        //             tp.first->s[0]=1;
        //             tp.second->s[0]=1;
        //             // ic(tp.first[0])
        //             // ic(tp.second[0])
        //         }
        //     }
        // }
        // size_t n=-1;
        // deque<Triangle*> tq1;
        // for (auto&t:ts){
        //     if (t.n==-1){
        //         t.n=++n;
        //         nodes.push_back(t.CircumCenter());
        //         tq1.push_back(&t);
        //         while (tq1.size()){
        //             auto&t=*tq1.front();
        //             tq1.pop_front();
        //             for (size_t q=0;q<3;++q){
        //                 // if (t.r[q]){
        //                 //     ic(t)
        //                 //     ic(t.r[q][0])
        //                 //     ic(n,q)
        //                 // }
        //                 if (t.s[q] and t.r[q]->n==-1){
        //                     t.r[q]->n=n;
        //                     tq1.push_back(t.r[q]);
        //                 }
        //             }
        //             // ic(tq1.size())
        //         }
        //     }
        // }
    }

    long double sum = 0;
    for (auto& p : h) {
        sum += Sqrt((o[p.first] - o[p.second]).SqAbs());
    }
    printf("%20.20Lf\n", sum / 1000);
    // cout<<sum<<endl;
    for (auto& p : h) {
        cout << p.first + 1 << " " << p.second + 1 << "\n";
    }

    // for (auto&p:h){
    //     Draw(Line{o[p.first],o[p.second]});
    // }

    // for (auto&p:a){
    //     Draw(p);
    // }

    // for (auto&t:ts){
    //     Draw(t);
    // }

    // for (auto&cc:nodes){
    //     Point ccp{(ssize_t)cc.x,(ssize_t)cc.y};
    //     ic(ccp)
    //     Draw(ccp);
    // }

    // for (auto&t:ts){
    //     auto cc=t.CircumCenter();
    //     Point ccp{(ssize_t)cc.x,(ssize_t)cc.y};
    //     ic(ccp)
    //     Draw(ccp);
    // }
}
