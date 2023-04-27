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
using std::unique_ptr, std::shared_ptr;

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

#if 1
#define nv 1

struct Alloc {
    size_t count = 0;
    unordered_map<void*, pair<vector<max_align_t>, size_t>> mem;
    void* Calloc(size_t q, size_t w) {
        decltype(mem)::mapped_type::first_type tmp(q * w / sizeof(max_align_t) + 1);
        auto ptr = tmp.data();
        mem[ptr] = {std::move(tmp), q * w};
        return ptr;
    }

    void* Malloc(size_t q) {
        return Calloc(q, 1);
    }

    void Free(void* p) {
        mem.erase(p);
    }

    void* Realloc(void* p, size_t q) {
        if (p) {
            auto w = mem[p].second;
            if (q > w) {
                auto o = Malloc(q);
                memcpy(o, p, w);
                Free(p);
                return o;
            }
            return p;
        }
        return Malloc(q);
    }
};

auto mem = Alloc();

struct BnFs {
    int32_t sign;
    uint32_t size;
    uint32_t* vect;
};

using Bn = struct BnFs;

#ifdef HOME
auto print_one(const Bn* q) {
    char b[99999];
    b[0] = 0;
    // sprintf(b+strlen(b) , "\x1b[92m%s\x1b[0m" , q -> sign == 1 ? "+" : q -> sign == -1 ? "-" : q -> sign > 1 ? "++" :
    // q -> sign < -1 ? "--" : "0") ;
    int c = 0;
    if (q->size) {
        for (int t = q->size - 1; t > -1; --t) {
            if (c % 2) {
                // sprintf(b+strlen(b) , "\x1b[92m") ;
            }
            // sprintf(b+strlen(b) , "%0*x" , 8 , q -> vect[t]) ;
            if (c % 2) {
                // sprintf(b+strlen(b) , "\x1b[0m") ;
            }
            ++c;
        }
    } else {
        // sprintf(b+strlen(b) , "\x1b[93m%0*llx\x1b[0m" , 16 , uint64_t(q -> vect)) ;
    }
    return str(b);
}

auto print_one(Bn* q) {
    return print_one((const Bn*)q);
}
#endif

Bn* BnFnew() {
    // #if STACK
    // adata[dsize].sign = 0 ;
    // adata[dsize].size = 0 ;
    // adata[dsize].vect = 0 ;
    // return adata+dsize++ ;
    // #else
    return static_cast<Bn*>(mem.Calloc(sizeof(Bn), 1));
    // #endif
}

static int BnFswap(Bn* q, Bn* e) {
    Bn r = *q;
    *q = *e;
    *e = r;
    return 0;
}

Bn* BnFinit(Bn const* orig) {
    // #if STACK
    // Bn*q = adata+dsize++ ;
    // #else
    Bn* q = static_cast<Bn*>(mem.Malloc(sizeof(Bn)));
    // #endif
    *q = *orig;
    if (orig->size) {
        q->vect = static_cast<uint32_t*>(mem.Malloc(q->size * sizeof(uint32_t)));
        memcpy(q->vect, orig->vect, q->size * sizeof(uint32_t));
        // for (size_t w = 0 ; w < q -> size ; ++w) {
        // q -> vect[w] = orig -> vect[w] ;
        //}
    }
    return q;
}

int BnFdelete(Bn* q) {
    if (q->size and q->vect) {
        mem.Free(q->vect);
    }
    // #if !STACK
    mem.Free(q);
    // #endif
    return 0;
}

static int BnFdel(Bn* q) {
    if (q->size and q->vect) {
        mem.Free(q->vect);
    }
    return 0;
}

static int BnFinitBn(Bn* q, const Bn* orig) {
    // ic(orig)
    if (q->size and q->vect) {
        mem.Free(q->vect);
    }
    *q = *orig;
    if (q->size) {
        q->vect = static_cast<uint32_t*>(mem.Malloc(q->size * sizeof(uint32_t)));
        memcpy(q->vect, orig->vect, q->size * sizeof(uint32_t));
        // for (size_t w = 0 ; w < q -> size ; ++w) {
        // q -> vect[w] = orig -> vect[w] ;
        //}
    }
    return 0;
}

int BnFinitInt(Bn* q, int e) {
    if (q->size and q->vect) {
        mem.Free(q->vect);
    }
    q->sign = e > 0 ? 1 : e < 0 ? -1 : 0;
    q->size = 0;
    q->vect = reinterpret_cast<uint32_t*>(static_cast<uint64_t>(q->sign * static_cast<int64_t>(e)));
    // q -> vect = static_cast<uint32_t*>mem.Malloc(sizeof(uint32_t)*1) ;
    // q -> size = 1 ;
    // q -> sign = e > 0 ? 1 : e < 0 ? -1 : 0 ;
    // q -> vect[0] = q -> sign*e ;
    return 0;
}

int BnFcmp(Bn const* q, Bn const* e) {
    if (q->sign != e->sign) {
        return ((q->sign) - (e->sign));
    }
    const uint32_t* qv = q->size ? q->vect : reinterpret_cast<const uint32_t*>(&(q->vect));
    const uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : reinterpret_cast<const uint32_t*>(&(e->vect));
    const uint32_t es = e->size ? e->size : 2;
    for (size_t c = (qs > es ? qs : es) - 1;; --c) {
        size_t a = qs > c ? qv[c] : 0;
        size_t s = es > c ? ev[c] : 0;
        if (a != s) {
            return ((a > s) * 2 - 1) * q->sign;
        }
        if (!c) {
            break;
        }
    }
    return 0;
}

static int BnFMAddTo(Bn* q, Bn const* e) {
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : reinterpret_cast<const uint32_t*>(&(e->vect));
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        qs -= 1;
    }
    while (es and ev[es - 1] == 0) {
        es -= 1;
    }
    qs = (qs > es ? qs : es) + 1;
    if (q->size and qs > q->size) {
        q->vect = static_cast<uint32_t*>(mem.Realloc(q->vect, qs * sizeof(uint32_t)));
        qv = q->vect;
        memset(q->vect + q->size, 0, (qs - q->size) * sizeof(uint32_t));
        // for (size_t w = q -> size ; w < qs ; ++w) {
        // q -> vect[w] = 0 ;
        //}
        q->size = qs;
    } else if (q->size == 0 and qs > 2) {
        auto tmp_p = reinterpret_cast<uint64_t*>(&(q->vect));
        uint64_t tmp = *tmp_p;
        q->vect = static_cast<uint32_t*>(mem.Calloc(1, qs * sizeof(uint32_t)));
        auto tmp_wp = reinterpret_cast<uint64_t*>(q->vect);
        *tmp_wp = tmp;
        // *static_cast<uint64_t*>(q -> vect) = tmp ;
        qv = q->vect;
        q->size = qs;
    } else if (q->size and qs < 3) {
        uint64_t tmp = *reinterpret_cast<uint64_t*>(q->vect);
        mem.Free(q->vect);
        q->size = 0;

        auto tmp_wp = reinterpret_cast<uint64_t*>(&(q->vect));
        *tmp_wp = tmp;

        // *static_cast<uint64_t*>&(q -> vect) = tmp ;
        qv = reinterpret_cast<uint32_t*>(&(q->vect));
    }
    uint64_t buff = 0;
    for (size_t w = 0; w < qs; ++w) {
        buff += qv[w];
        if (w < es) {
            buff += ev[w];
        }
        qv[w] = buff & 4294967295;
        buff >>= 32;
    }
    return 0;
}

static int BnFMAddToFast(Bn* q, Bn const* e, uint64_t start) {
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : reinterpret_cast<const uint32_t*>(&(e->vect));
    uint32_t es = e->size ? e->size : 2;
    if (qs and qv[qs - 1] == 0) {
        qs -= 1;
    }
    if (es and ev[es - 1] == 0) {
        es -= 1;
    }
    qs = (qs > es ? qs : es) + 1;
    if (q->size and qs > q->size) {
        q->vect = static_cast<uint32_t*>(mem.Realloc(q->vect, qs * sizeof(uint32_t)));
        qv = q->vect;
        // for (size_t w = q -> size ; w < qs ; ++w) {
        // q -> vect[w] = 0 ;
        //}
        memset(q->vect + q->size, 0, (qs - q->size) * sizeof(uint32_t));
        q->size = qs;
    } else if (q->size == 0 and qs > 2) {
        auto tmp_p = reinterpret_cast<uint64_t*>(&(q->vect));
        uint64_t tmp = *tmp_p;

        // uint64_t tmp = *static_cast<uint64_t*>&(q -> vect) ;
        q->vect = static_cast<uint32_t*>(mem.Calloc(1, qs * sizeof(uint32_t)));
        *reinterpret_cast<uint64_t*>(q->vect) = tmp;
        qv = q->vect;
        q->size = qs;
    } else if (q->size and qs < 3) {
        uint64_t tmp = *reinterpret_cast<uint64_t*>(q->vect);
        mem.Free(q->vect);
        q->size = 0;

        auto tmp_wp = reinterpret_cast<uint64_t*>(&(q->vect));
        *tmp_wp = tmp;

        // *static_cast<uint64_t*>&(q -> vect) = tmp ;
        qv = reinterpret_cast<uint32_t*>(&(q->vect));
    }
    uint64_t buff = 0;
    for (size_t w = start; w < qs; ++w) {
        buff += qv[w];
        if (w < es) {
            buff += ev[w];
        }
        qv[w] = buff & 4294967295;
        buff >>= 32;
        if (!buff and w > start) {
            return 0;
        }
    }
    return 0;
}

static int BnFMSubTo(Bn* q, Bn const* e) {
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : reinterpret_cast<const uint32_t*>(&(e->vect));
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        qs -= 1;
    }
    while (es and ev[es - 1] == 0) {
        es -= 1;
    }
    qs = (qs > es ? qs : es) + 1;
    if (q->size and qs > q->size) {
        q->vect = static_cast<uint32_t*>(mem.Realloc(q->vect, qs * sizeof(uint32_t)));
        qv = q->vect;
        // for (size_t w = q -> size ; w < qs ; ++w) {
        // q -> vect[w] = 0 ;
        //}
        memset(q->vect + q->size, 0, (qs - q->size) * sizeof(uint32_t));
        q->size = qs;
    } else if (q->size == 0 and qs > 2) {
        auto tmp_p = reinterpret_cast<uint64_t*>(&(q->vect));
        uint64_t tmp = *tmp_p;
        q->vect = static_cast<uint32_t*>(mem.Calloc(1, qs * sizeof(uint32_t)));
        *reinterpret_cast<uint64_t*>(q->vect) = tmp;
        qv = q->vect;
        q->size = qs;
    } else if (q->size and qs < 3) {
        uint64_t tmp = *reinterpret_cast<uint64_t*>(q->vect);
        mem.Free(q->vect);
        q->size = 0;

        auto tmp_wp = reinterpret_cast<uint64_t*>(&(q->vect));
        *tmp_wp = tmp;

        // *static_cast<uint64_t*>&(q -> vect) = tmp ;
        qv = reinterpret_cast<uint32_t*>(&(q->vect));
    }
    int64_t buff = 0;
    for (size_t w = 0; w < qs; ++w) {
        buff += qv[w];
        if (w < es) {
            buff -= ev[w];
        }
        qv[w] = buff & 4294967295;
        buff >>= 32;
    }
    size_t b = 0;
    for (size_t w = 0; w < qs; ++w) {
        if (qv[w]) {
            b = 1;
            break;
        }
    }
    if (!b) {
        q->sign = 0;
    }
    return 0;
}

int BnFaddTo(Bn* q, const Bn* e) {
    int j = q->sign;
    int k = e->sign;
    int l = 0;
    {
        int32_t qs = q->sign;
        q->sign = e->sign;
        l = BnFcmp(q, e);
        q->sign = qs;
    }
    if (!k) {
        return 0;
    }
    Bn data[1];
    memset(data, 0, sizeof(data));
    Bn* h = data + 0;
    if (j <= 0) {
        if (k < 0) {
            BnFMAddTo(q, e);
            q->sign = -1;
        } else {
            if (l >= 0) {
                BnFMSubTo(q, e);
            } else {
                BnFswap(h, q);
                BnFinitBn(q, e);
                BnFMSubTo(q, h);
            }
        }
    } else {
        if (k < 0) {
            if (l <= 0) {
                BnFMSubTo(q, e);
            } else {
                BnFswap(h, q);
                BnFinitBn(q, e);
                BnFMSubTo(q, h);
            }
        } else {
            BnFMAddTo(q, e);
            q->sign = 1;
        }
    }
    BnFdel(h);
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    size_t b = 0;
    for (size_t w = 0; w < qs; ++w) {
        if (qv[w]) {
            b = 1;
            break;
        }
    }
    if (!b) {
        q->sign = 0;
    }
    return 0;
}

int BnFsubTo(Bn* q, const Bn* e) {
    q->sign *= -1;
    BnFaddTo(q, e);
    q->sign *= -1;
    return 0;
}

Bn* BnFadd(const Bn* q, const Bn* w) {
    Bn* h = BnFinit(q);
    BnFaddTo(h, w);
    return h;
}

Bn* BnFsub(const Bn* q, const Bn* w) {
    Bn* h = BnFinit(q);
    BnFsubTo(h, w);
    return h;
}

uint64_t BnFfftPow(uint64_t q, uint64_t w, uint64_t e) {
    uint64_t res = 1;
    while (w) {
        if (w % 2) {
            res *= q;
            res %= e;
        }
        q *= q;
        q %= e;
        w /= 2;
    }
    return res;
}

uint64_t bn_ffft_mod = 3221225473;
uint64_t bn_ffft_root = 13;
uint64_t bn_ffft_ro = 1073741824;

uint64_t bn_ffft_rp0[65536];
uint64_t bn_ffft_rp1[65536];

void BnFfftPrepare() {
    bn_ffft_rp0[0] = 1;

    for (size_t w = 1; w < 65536; ++w) {
        bn_ffft_rp0[w] = bn_ffft_rp0[w - 1] * bn_ffft_root % bn_ffft_mod;
    }

    bn_ffft_rp1[0] = 1;
    bn_ffft_rp1[1] = bn_ffft_root * bn_ffft_rp0[65536 - 1];
    bn_ffft_rp1[1] %= bn_ffft_mod;

    for (size_t w = 2; w < 65536; ++w) {
        bn_ffft_rp1[w] = bn_ffft_rp1[w - 1] * bn_ffft_rp1[1] % bn_ffft_mod;
    }
}

uint64_t BnFfftRoots(uint64_t n, uint64_t k) {
    assert(bn_ffft_rp0[0] == 1);
    k %= n;
    auto p = static_cast<size_t>(bn_ffft_ro / n * k);
    auto pp = reinterpret_cast<uint16_t*>(&p);
    return (bn_ffft_rp0[pp[0]] * bn_ffft_rp1[pp[1]]) % bn_ffft_mod;
}

uint64_t* bn_ffft_bi = nullptr;
uint64_t bn_ffft_bil = 0;
uint64_t bn_ffft_bim = 0;

uint64_t BnFfftBitinv(uint64_t t, uint64_t l) {
    while (bn_ffft_bil <= t) {
        uint64_t r = bn_ffft_bil;
        uint64_t x = 0;
        for (uint64_t c = 0; c < 32; ++c) {
            x *= 2;
            x += r % 2;
            r /= 2;
        }
        if (bn_ffft_bil == bn_ffft_bim) {
            auto t = static_cast<uint64_t*>(mem.Malloc(sizeof(uint64_t) * (bn_ffft_bim * 2 + 1)));
            memcpy(t, bn_ffft_bi, bn_ffft_bim * sizeof(bn_ffft_bi[0]));
            mem.Free(bn_ffft_bi);
            bn_ffft_bi = t;
            bn_ffft_bim *= 2;
            bn_ffft_bim += 1;
        }
        bn_ffft_bi[bn_ffft_bil++] = x;
    }
    return bn_ffft_bi[t] >> (32 - l);
}

void BnFfftPrep(uint64_t* a, uint64_t n) {
    uint64_t l = 0;
    uint64_t o = n;
    while (o) {
        o /= 2;
        l += 1;
    }
    l -= 1;
    for (size_t w = 0; w < n; ++w) {
        size_t r = w;
        auto x = static_cast<size_t>(BnFfftBitinv(r, l));
        if (w < x) {
            uint64_t t = a[w];
            a[w] = a[x];
            a[x] = t;
        }
    }
}

void BnFfftFftr(uint64_t* a, int inv, uint64_t b, uint64_t e) {
    if (bn_ffft_rp0[0] != 1) {
        BnFfftPrepare();
    }
    uint64_t n = e - b;
    uint64_t h = n / 2;
    uint64_t val_n = n;
    uint64_t val_b = b;
    uint64_t val_e = e;
    n = 2;
    while (n <= val_n) {
        for (b = val_b; b != val_e; b += n) {
            e = b + n;
            h = n / 2;
            for (uint64_t k = 0; k < h; k++) {
                uint64_t a0 = a[b + k];
                uint64_t a1 = a[b + k + h];
                uint64_t t = inv < 0 ? n - k : n + k;
                uint64_t r = BnFfftRoots(n, t);
                r *= a1;
                r %= bn_ffft_mod;
                a[b + k] = (a0 + r) % bn_ffft_mod;
                a[b + k + h] = (a0 + bn_ffft_mod - r) % bn_ffft_mod;
            }
        }
        n *= 2;
    }
}

void BnFfftFft(uint64_t* a, uint64_t n, int inv) {
    uint64_t b = 0;
    uint64_t e = n;
    BnFfftPrep(a, n);
    BnFfftFftr(a, inv, b, e);
    if (inv == -1) {
        for (uint64_t w = 0; w < n; ++w) {
            a[w] *= BnFfftPow(n, bn_ffft_mod - 2, bn_ffft_mod);
            a[w] %= bn_ffft_mod;
        }
    }
}

int BnFmulTo(Bn* q, const Bn* e) {
    uint64_t base = 16;
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : reinterpret_cast<const uint32_t*>(&(e->vect));
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    while (es and ev[es - 1] == 0) {
        --es;
    }
    Bn data[2];
    memset(data, 0, sizeof(data));
    Bn* res = data + 1;
    if (qs + es > 512) {
        auto qb = reinterpret_cast<uint8_t*>(qv);
        auto eb = reinterpret_cast<const uint8_t*>(ev);
        size_t l = qs;
        if (es > qs) {
            l = es;
        }
        size_t dl = 1;
        while (dl < l) {
            dl *= 2;
        }
        l = dl * 2 * 8;
        auto a = static_cast<uint64_t*>(mem.Calloc(l, sizeof(uint64_t)));
        for (size_t w = 0; w < qs * 4; w++) {
            a[w * 2] = qb[w] & 0xF;
            a[w * 2 + 1] = qb[w] >> 4;
        }
        auto s = static_cast<uint64_t*>(mem.Calloc(l, sizeof(uint64_t)));
        for (size_t w = 0; w < es * 4; w++) {
            s[w * 2] = eb[w] & 0xF;
            s[w * 2 + 1] = eb[w] >> 4;
        }
        BnFfftFft(a, l, 1);
        BnFfftFft(s, l, 1);
        for (size_t w = 0; w < l; w++) {
            a[w] *= s[w];
            a[w] %= bn_ffft_mod;
        }
        BnFfftFft(a, l, -1);
        for (size_t w = 1; w < l; w++) {
            a[w] += a[w - 1] / base;
            a[w - 1] %= base;
        }
        res->size = qs + es;
        res->vect = static_cast<uint32_t*>(mem.Calloc(1, res->size * sizeof(uint32_t)));
        res->sign = q->sign * e->sign;

        auto rb = reinterpret_cast<uint8_t*>(res->vect);

        for (size_t w = 0; w < res->size * 4; ++w) {
            rb[w] |= a[2 * w];
            rb[w] |= a[2 * w + 1] << 4;
        }
        mem.Free(a);
        mem.Free(s);
    } else if (qs + es > 2) {
        // ic(itervect(qv , qv+qs))
        Bn* tmp = data + 0;
        res->size = qs + es;
        tmp->size = qs + es;
        res->vect = static_cast<uint32_t*>(mem.Calloc(1, res->size * sizeof(uint32_t)));
        tmp->vect = static_cast<uint32_t*>(mem.Calloc(1, tmp->size * sizeof(uint32_t)));
        // memset(res -> vect , 0 , (res -> size)*sizeof(uint32_t)) ;
        // memset(tmp -> vect , 0 , (tmp -> size)*sizeof(uint32_t)) ;
        // for (size_t w = 0 ; w < res -> size ; ++w) {
        // res -> vect[w] = 0 ;
        // tmp -> vect[w] = 0 ;
        //}
        // ic(itervect(qv , qv+qs))
        tmp->sign = 1;
        for (size_t w = 0; w < qs; ++w) {
            if (qv[w]) {
                for (size_t r = 0; r < es; ++r) {
                    uint64_t val_tmp = (static_cast<uint64_t>(qv[w])) * (static_cast<uint64_t>(ev[r]));
                    *(tmp->vect + w + r) = val_tmp & 4294967295;
                    *(tmp->vect + w + r + 1) = val_tmp >> 32;
                    BnFMAddToFast(res, tmp, w + r);
                    *(tmp->vect + w + r) = 0;
                    *(tmp->vect + w + r + 1) = 0;
                }
            }
        }
        res->sign = q->sign * e->sign;
        BnFdel(tmp);
    } else {
        res->sign = q->sign * e->sign;
        res->size = 0;

        auto tmp_wp = reinterpret_cast<uint64_t*>(&(res->vect));
        *tmp_wp = *reinterpret_cast<uint64_t*>(qv) * *reinterpret_cast<const uint64_t*>(ev);
    }
    BnFswap(res, q);
    BnFdel(res);
    return 0;
}

int BnFmulTTo(Bn* q, const Bn* e) {
    // ic(q , e)
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : reinterpret_cast<const uint32_t*>(&(e->vect));
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    while (es and ev[es - 1] == 0) {
        --es;
    }
    Bn data[2];
    memset(data, 0, sizeof(data));
    Bn* res = data + 1;
    if (qs + es > 2) {
        // ic(itervect(qv , qv+qs))
        Bn* tmp = data + 0;
        res->size = qs + es;
        tmp->size = qs + es;
        res->vect = static_cast<uint32_t*>(mem.Calloc(1, res->size * sizeof(uint32_t)));
        tmp->vect = static_cast<uint32_t*>(mem.Calloc(1, tmp->size * sizeof(uint32_t)));
        // memset(res -> vect , 0 , (res -> size)*sizeof(uint32_t)) ;
        // memset(tmp -> vect , 0 , (tmp -> size)*sizeof(uint32_t)) ;
        // for (size_t w = 0 ; w < res -> size ; ++w) {
        // res -> vect[w] = 0 ;
        // tmp -> vect[w] = 0 ;
        //}
        // ic(itervect(qv , qv+qs))
        tmp->sign = 1;
        for (size_t w = 0; w < qs; ++w) {
            if (qv[w]) {
                for (size_t r = 0; r < es; ++r) {
                    uint64_t val_tmp = (static_cast<uint64_t>(qv[w])) * (static_cast<uint64_t>(ev[r]));
                    *(tmp->vect + w + r) = val_tmp & 4294967295;
                    *(tmp->vect + w + r + 1) = val_tmp >> 32;
                    BnFMAddToFast(res, tmp, w + r);
                    *(tmp->vect + w + r) = 0;
                    *(tmp->vect + w + r + 1) = 0;
                }
            }
        }
        res->sign = q->sign * e->sign;
        BnFdel(tmp);
    } else {
        res->sign = q->sign * e->sign;
        res->size = 0;

        auto tmp_wp = reinterpret_cast<uint64_t*>(&(res->vect));
        *tmp_wp = *reinterpret_cast<uint64_t*>(qv) * *reinterpret_cast<const uint64_t*>(ev);

        // *static_cast<uint64_t*>&(res -> vect) = *static_cast<uint64_t*>(qv)* *static_cast<const uint64_t*>(ev) ;
    }
    BnFswap(res, q);
    BnFdel(res);
    return 0;
}

Bn* BnFmul(const Bn* q, const Bn* w) {
    Bn* h = BnFinit(q);
    BnFmulTo(h, w);
    return h;
}

int BnFneg(Bn* q) {
    q->sign *= -1;
    return 0;
}

int BnFabs(Bn* q) {
    q->sign = static_cast<bool>(q->sign);
    return 0;
}

int BnFsign(const Bn* q) {
    return q->sign;
}

static int BnFhalf(Bn* q) {
    if (q->size) {
        q->vect[0] >>= 1;
    } else {

        auto tmp_wp = reinterpret_cast<uint64_t*>(&(q->vect));
        *tmp_wp >>= 1;

        // *static_cast<uint64_t*>&(q -> vect) >>= 1 ;
        if (!*tmp_wp) {
            q->sign = 0;
        }
        return 0;
    }
    for (size_t w = 1; w < q->size; ++w) {
        q->vect[w - 1] |= (q->vect[w] & 1) << 31;
        q->vect[w] >>= 1;
    }
    size_t b = 0;
    for (size_t w = 0; w < q->size; ++w) {
        if (q->vect[w]) {
            b = 1;
            break;
        }
    }
    if (!b) {
        q->sign = 0;
    }
    return 0;
}

int BnFMDivTo(Bn* q, Bn* e) {
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    uint32_t* ev = e->size ? e->vect : reinterpret_cast<uint32_t*>(&(e->vect));
    uint32_t es = e->size ? e->size : 2;
    // ic(q , e)
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    while (es and ev[es - 1] == 0) {
        --es;
    }
    assert(es);
    Bn data[2];
    memset(data, 0, sizeof(data));
    if (qs >= es) {
        Bn* t = data + 0;
        t->size = qs + 2;
        t->sign = 1;
        t->vect = static_cast<uint32_t*>(mem.Calloc(sizeof(uint32_t), t->size));
        memcpy(t->vect + qs - es + 2, ev, es * sizeof(uint32_t));
        // for(size_t w = 0 ; w < es ; ++w) {
        // (t -> vect+qs-es+2)[w] = ev[w] ;
        //}
        ssize_t f = (qs - es + 2) * 32;
        Bn* r = data + 1;
        uint32_t* rv = nullptr;
        uint32_t rs = 0;
        if (qs + 1 - es > 2) {
            r->size = qs + 1 - es;
            r->sign = 1;
            r->vect = static_cast<uint32_t*>(mem.Calloc(sizeof(uint32_t), r->size));
            rv = r->vect;
            rs = r->size;
        } else {
            r->size = 0;
            r->sign = 1;
            r->vect = nullptr;
            rv = reinterpret_cast<uint32_t*>(&(r->vect));
            rs = 2;
        }
        while (f >= 0) {
            // ic(q , r , a[f&31] , f)
            // if (BnFcmp(q , a[f&31]) >= 0) {
            // rv[f >> 5] |= (1LL << (f&31)) ;
            // BnFMSubTo(q , a[f&31]) ;
            //}
            // a[f&31] -> size -= 1 ;
            // a[f&31] -> vect += 1 ;
            // o[f&31] += 1 ;
            // f -= 1 ;
            // // BnFhalf(t) ;
            if (BnFcmp(q, t) >= 0) {
                rv[f >> 5] |= (1LL << (f & 31));
                BnFMSubTo(q, t);
            }
            // t -> size -= 1 ;
            // t -> vect += 1 ;
            // o[f&31] += 1 ;
            f -= 1;
            BnFhalf(t);
        }
        size_t b = 0;
        for (size_t w = 0; w < rs; ++w) {
            if (rv[w]) {
                b = 1;
                break;
            }
        }
        if (!b) {
            r->sign = 0;
        }
        // for (size_t w = 0 ; w < 32 ; ++w) {
        // a[w] -> vect -= o[w] ;
        // // ic(a[w] -> vect)
        // BnFdelete(a[w]) ;
        //}
        // mem.Free(o) ;
        // mem.Free(a) ;
        BnFswap(e, r);
        // BnFinitBn(e , r) ;
        BnFdel(r);
        BnFdel(t);
    } else {
        BnFinitInt(e, 0);
    }
    return 0;
}

int BnFdivTo(Bn* q, const Bn* e) {
    Bn data[2];
    memset(data, 0, sizeof(data));
    Bn* a = data + 0;
    Bn* d = data + 1;
    BnFinitBn(a, q);
    a->sign = static_cast<bool>(a->sign);
    BnFinitBn(d, e);
    d->sign = static_cast<bool>(d->sign);
    BnFMDivTo(a, d);
    if (q->sign * e->sign < 0) {
        if (a->sign) {
            BnFinitInt(a, -1);
            BnFsubTo(a, d);
            BnFdel(d);
            BnFswap(q, a);
            // BnFinitBn(q , a) ;
            BnFdel(a);
            return 0;
        }
        d->sign *= -1;
        BnFdel(a);
        BnFswap(q, d);
        // BnFinitBn(q , d) ;
        BnFdel(d);
        return 0;
    }
    BnFdel(a);
    BnFswap(q, d);
    // BnFinitBn(q , d) ;
    BnFdel(d);
    return 0;
}

Bn* BnFdiv(const Bn* q, const Bn* w) {
    Bn* h = BnFinit(q);
    BnFdivTo(h, w);
    return h;
}

int BnFmodTo(Bn* q, const Bn* e) {
    Bn data[2];
    memset(data, 0, sizeof(data));
    Bn* a = data + 0;
    Bn* d = data + 1;
    BnFinitBn(a, q);
    a->sign = static_cast<bool>(a->sign);
    BnFinitBn(d, e);
    d->sign = static_cast<bool>(d->sign);
    BnFMDivTo(a, d);
    // ic(a , d)
    if (q->sign * e->sign < 0) {
        if (a->sign) {
            a->sign = e->sign;
            BnFsubTo(a, e);
            a->sign = e->sign;
            BnFdel(d);
            BnFswap(q, a);
            BnFdel(a);
            return 0;
        }
        BnFdel(d);
        BnFswap(q, a);
        // BnFinitBn(q , a) ;
        BnFdel(a);
        return 0;
    }
    BnFdel(d);
    a->sign *= q->sign;
    BnFswap(q, a);
    // BnFinitBn(q , a) ;
    BnFdel(a);
    return 0;
}

Bn* BnFmod(const Bn* q, const Bn* w) {
    Bn* h = BnFinit(q);
    BnFmodTo(h, w);
    return h;
}

int BnFpowTo(Bn* q, int val_e) {
    auto e = static_cast<uint64_t>(static_cast<int64_t>(val_e));
    size_t s = 0;
    for (size_t w = 0; w < 64; ++w) {
        if ((1ULL << w) & e) {
            s = w + 1;
        }
    }
    if (s) {
        Bn a[64];
        memset(a, 0, sizeof(a));
        BnFinitBn(a + 0, q);
        for (size_t w = 1; w < s; ++w) {
            BnFinitBn(a + w, a + w - 1);
            BnFmulTo(a + w, a + w);
        }
        BnFinitInt(q, 1);
        for (size_t w = 0; w < s; ++w) {
            if ((1 << w) & e) {
                BnFmulTo(q, a + w);
            }
        }
        for (size_t w = 0; w < s; ++w) {
            BnFdel(a + w);
        }
        // mem.Free(a) ;
    } else {
        BnFinitInt(q, 1);
    }
    return 0;
}

int BnFroot2To(Bn* q) {
    Bn data[3];
    memset(data, 0, sizeof(data));
    Bn* r = data + 0;
    Bn* p = data + 1;
    // uint32_t*rv , pv ;
    // uint32_t ps , rs ;
    if (q->size + 1 > 2) {
        r->size = q->size + 1;
        r->sign = 1;
        r->vect = static_cast<uint32_t*>(mem.Calloc(sizeof(uint32_t), r->size));
        // rv = r -> vect ;
        // rs = r -> size ;
        p->size = q->size + 1;
        p->sign = 1;
        p->vect = static_cast<uint32_t*>(mem.Calloc(sizeof(uint32_t), p->size));
        p->vect[p->size - 1] = 1;
        // pv = p -> vect ;
        // ps = p -> size ;
    } else {
        r->size = 0;
        r->sign = 1;
        r->vect = nullptr;
        // rv = static_cast<uint32_t*>&(r -> vect) ;
        // rs = 2 ;
        p->size = 0;
        p->sign = 1;
        p->vect = reinterpret_cast<uint32_t*>(static_cast<uint64_t>(1LL << 32));
        // pv = static_cast<uint32_t*>&(p -> vect) ;
        // ps = 2 ;
    }
    Bn* u = data + 2;
    while (p->sign) {
        BnFinitBn(u, r);
        BnFaddTo(u, p);
        if (BnFcmp(q, u) >= 0) {
            BnFsubTo(q, u);
            BnFaddTo(r, p);
            BnFaddTo(r, p);
        }
        BnFhalf(r);
        BnFhalf(p);
        BnFhalf(p);
    }
    BnFdel(u);
    BnFswap(q, r);
    // BnFinitBn(q , r) ;
    BnFdel(r);
    BnFdel(p);
    return 0;
}

int BnFrootTo(Bn* q, int val__e) {
    if (val__e == 2) {
        return BnFroot2To(q);
    }
    Bn data[6];
    memset(data, 0, sizeof(data));
    auto e = static_cast<uint64_t>(static_cast<int64_t>(val__e));
    Bn* val_b = data + 0;
    Bn* val_e = data + 1;
    uint32_t tmp = q->size / e + 1;
    if (tmp > 2) {
        val_e->size = tmp;
        val_e->sign = 1;
        val_e->vect = static_cast<uint32_t*>(mem.Calloc(sizeof(uint32_t), val_e->size));
        val_e->vect[val_e->size - 1] = 1LL << 31;
    } else {
        val_e->size = 0;
        val_e->sign = 1;
        val_e->vect = reinterpret_cast<uint32_t*>(static_cast<uint64_t>(1ULL << 63));
    }
    Bn* val_c = data + 2;
    Bn* val_d = data + 3;
    Bn* val_f = data + 4;
    Bn* val_g = data + 5;
    BnFinitInt(val_g, 2);
    while (true) {
        BnFinitBn(val_f, val_e);
        BnFsubTo(val_f, val_b);
        if (BnFcmp(val_f, val_g) < 0) {
            break;
        }
        BnFinitBn(val_c, val_b);
        BnFaddTo(val_c, val_e);
        BnFhalf(val_c);
        BnFinitBn(val_d, val_c);
        BnFpowTo(val_d, static_cast<int>(e));
        int j = BnFcmp(val_d, q);
        if (j < 0) {
            BnFinitBn(val_b, val_c);
        } else if (j > 0) {
            BnFinitBn(val_e, val_c);
        } else if (j == 0) {
            BnFinitBn(val_e, val_c);
            BnFinitBn(val_b, val_c);
        }
    }
    BnFdel(val_c);
    BnFdel(val_d);
    BnFdel(val_f);
    BnFdel(val_g);
    BnFswap(q, val_b);
    // BnFinitBn(q , val_b) ;
    BnFdel(val_b);
    BnFdel(val_e);
    return 0;
}

int BnFInitStringRadix(Bn* q, const char* e, int t) {
    // size_t l = strlen(e) ;
    size_t l = 0;
    while (
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"[static_cast<int>(e[l])]) {
        e++;
    }
    if (e[l] == '+') {
        e++;
    }
    if (e[l] == '-') {
        l++;
    }
    while (static_cast<unsigned>(
               "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
               "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
               "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x0a\x0b\x0c\x0d\x0e\x0f\xFF"
               "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
               "\xFF\x0a\x0b\x0c\x0d\x0e\x0f\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
               "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"[static_cast<int>(e[l])]) < static_cast<unsigned>(t)) {
        l++;
    }
    auto qs = static_cast<uint32_t>(
        l / static_cast<unsigned>("\x00\x00\x20\x14\x10\x0d\x0c\x0b\x0a\x0a\x09\x09\x08\x08\x08\x08\x08\x07\x07\x07\x07"
                                  "\x07\x07\x07\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06"[t]) +
        1);
    if (q->size and q->vect) {
        mem.Free(q->vect);
    }
    if (qs > 2) {
        q->size = qs;
        q->vect = static_cast<uint32_t*>(mem.Calloc(sizeof(uint32_t), q->size));
    } else {
        q->size = 0;
        q->vect = nullptr;
    }
    q->sign = 0;
    Bn data[2];
    memset(data, 0, sizeof(data));
    Bn* a = data + 0;
    Bn* y = data + 1;
    BnFinitInt(y, t);
    size_t g = 0;
    if (l and e[0] == '-') {
        g = 1;
    }
    for (size_t w = g; w < l; ++w) {
        // ic(q , y , a)
        BnFmulTo(q, y);
        // ic(q , y , a)
        BnFinitInt(
            a,
            "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19"
            "\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03"
            "\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16"
            "\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10"
            "\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"
                [static_cast<int>(e[w])]);
        if (a->sign) {
            q->sign = 1;
        }
        BnFMAddToFast(q, a, 0);
    }
    q->sign *= "\x01\xff"[g];
    BnFdel(a);
    BnFdel(y);
    return 0;
}

int BnFInitString(Bn* q, const char* e) {
    return BnFInitStringRadix(q, e, 10);
}

char* BnFtoString(const Bn* q, int e) {
    const uint32_t* qv = q->size ? q->vect : reinterpret_cast<const uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    auto val_t = static_cast<uint64_t>(e);
    Bn data[1];
    memset(data, 0, sizeof(data));
    Bn* r = data + 0;
    // ic(int64_t(r) , int64_t(q))
    BnFinitBn(r, q);
    r->sign = static_cast<bool>(r->sign);
    uint32_t* rv = r->size ? r->vect : reinterpret_cast<uint32_t*>(&(r->vect));
    uint32_t rs = qs;
    char* a = static_cast<char*>(mem.Calloc(
        sizeof(char),
        2 + (qs + 1) * static_cast<unsigned>(
                           "\x00\x00\x20\x15\x10\x0e\x0d\x0c\x0b\x0b\x0a\x0a\x09\x09\x09\x09\x08\x08\x08\x08\x08"
                           "\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07"[val_t])));
    size_t s = 0;
    while (r->sign) {
        uint64_t b = 0;
        uint64_t t = 0;
        r->sign = 0;
        for (size_t val_w = rs; val_w > 0; --val_w) {
            size_t w = val_w - 1;
            t = rv[w];
            t += b << 32;
            b = t % val_t;
            t /= val_t;
            rv[w] = static_cast<uint32_t>(t);
            if (t) {
                r->sign = 1;
            }
        }
        a[s++] = static_cast<char>(b);
    }
    for (size_t w = 0; w < s; ++w) {
        a[w] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[static_cast<int>(a[w])];
    }
    if (q->sign < 0) {
        a[s++] = '-';
    }
    if (!s) {
        a[s++] = '0';
    }
    for (size_t w = 0; w * 2 < s; ++w) {
        char t = a[w];
        a[w] = a[s - 1 - w];
        a[s - 1 - w] = t;
    }
    BnFdel(r);
    return a;
}

Bn* BnFroot(Bn* q, int val_w) {
    // uint64_t w = static_cast<uint64_t>(val_w) ;
    Bn* h = BnFinit(q);
    BnFrootTo(h, val_w);
    return h;
}

Bn* BnFpow(Bn* q, int w) {
    Bn* h = BnFinit(q);
    BnFpowTo(h, w);
    return h;
}

#else
// 08.02.2022 stable

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

struct bn_s {
    int32_t sign;
    uint32_t size;
    uint32_t* vect;
};

typedef struct bn_s bn;

#ifdef HOME
auto print_one(const bn* q) {
    char b[99999];
    b[0] = 0;
    sprintf(b + strlen(b), "\x1b[92m%s\x1b[0m",
            q->sign == 1    ? "+"
            : q->sign == -1 ? "-"
            : q->sign > 1   ? "++"
            : q->sign < -1  ? "--"
                            : "0");
    int c = 0;
    if (q->size) {
        for (int t = q->size - 1; t > -1; --t) {
            if (c % 2) {
                sprintf(b + strlen(b), "\x1b[92m");
            }
            sprintf(b + strlen(b), "%0*x", 8, q->vect[t]);
            if (c % 2) {
                sprintf(b + strlen(b), "\x1b[0m");
            }
            ++c;
        }
    } else {
        sprintf(b + strlen(b), "\x1b[93m%0*llx\x1b[0m", 16, uint64_t(q->vect));
    }
    return str(b);
}

auto print_one(bn* q) {
    return print_one((const bn*)q);
}
#endif

bn* bn_new() {
    // #if STACK
    // adata[dsize].sign = 0 ;
    // adata[dsize].size = 0 ;
    // adata[dsize].vect = 0 ;
    // return adata+dsize++ ;
    // #else
    return (bn*)calloc(sizeof(bn), 1);
    // #endif
}

static int bn_swap(bn* q, bn* e) {
    bn r = *q;
    *q = *e;
    *e = r;
    return 0;
}

bn* bn_init(bn const* orig) {
    // #if STACK
    // bn*q = adata+dsize++ ;
    // #else
    bn* q = (bn*)malloc(sizeof(bn));
    // #endif
    *q = *orig;
    if (orig->size) {
        q->vect = (uint32_t*)malloc(q->size * sizeof(uint32_t));
        memcpy(q->vect, orig->vect, q->size * sizeof(uint32_t));
        // for (size_t w = 0 ; w < q -> size ; ++w) {
        // q -> vect[w] = orig -> vect[w] ;
        //}
    }
    return q;
}

int bn_delete(bn* q) {
    if (q->size and q->vect) {
        free(q->vect);
    }
    // #if !STACK
    free(q);
    // #endif
    return 0;
}

static int bn_del(bn* q) {
    if (q->size and q->vect) {
        free(q->vect);
    }
    return 0;
}

static int bn_init_bn(bn* q, const bn* orig) {
    // ic(orig)
    if (q->size and q->vect) {
        free(q->vect);
    }
    *q = *orig;
    if (q->size) {
        q->vect = (uint32_t*)malloc(q->size * sizeof(uint32_t));
        memcpy(q->vect, orig->vect, q->size * sizeof(uint32_t));
        // for (size_t w = 0 ; w < q -> size ; ++w) {
        // q -> vect[w] = orig -> vect[w] ;
        //}
    }
    return 0;
}

int bn_init_int(bn* q, int e) {
    if (q->size and q->vect) {
        free(q->vect);
    }
    q->sign = e > 0 ? 1 : e < 0 ? -1 : 0;
    q->size = 0;
    q->vect = (uint32_t*)(uint64_t)(q->sign * (int64_t)(e));
    // q -> vect = (uint32_t*)malloc(sizeof(uint32_t)*1) ;
    // q -> size = 1 ;
    // q -> sign = e > 0 ? 1 : e < 0 ? -1 : 0 ;
    // q -> vect[0] = q -> sign*e ;
    return 0;
}

int bn_cmp(bn const* q, bn const* e) {
    if (q->sign != e->sign) {
        return ((q->sign) - (e->sign));
    }
    const uint32_t* qv = q->size ? q->vect : (const uint32_t*)&(q->vect);
    const uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : (const uint32_t*)&(e->vect);
    const uint32_t es = e->size ? e->size : 2;
    for (size_t c = (qs > es ? qs : es) - 1;; --c) {
        size_t a = qs > c ? qv[c] : 0;
        size_t s = es > c ? ev[c] : 0;
        if (a != s) {
            return ((a > s) * 2 - 1) * q->sign;
        }
        if (!c) {
            break;
        }
    }
    return 0;
}

static int bn_M_add_to(bn* q, bn const* e) {
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : (const uint32_t*)&(e->vect);
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        qs -= 1;
    }
    while (es and ev[es - 1] == 0) {
        es -= 1;
    }
    qs = (qs > es ? qs : es) + 1;
    if (q->size and qs > q->size) {
        q->vect = (uint32_t*)realloc(q->vect, qs * sizeof(uint32_t));
        qv = q->vect;
        memset(q->vect + q->size, 0, (qs - q->size) * sizeof(uint32_t));
        // for (size_t w = q -> size ; w < qs ; ++w) {
        // q -> vect[w] = 0 ;
        //}
        q->size = qs;
    } else if (q->size == 0 and qs > 2) {
        uint64_t* tmp_p = (uint64_t*)&(q->vect);
        uint64_t tmp = *tmp_p;
        q->vect = (uint32_t*)calloc(1, qs * sizeof(uint32_t));
        uint64_t* tmp_wp = (uint64_t*)(q->vect);
        *tmp_wp = tmp;
        // *(uint64_t*)(q -> vect) = tmp ;
        qv = q->vect;
        q->size = qs;
    } else if (q->size and qs < 3) {
        uint64_t tmp = *(uint64_t*)(q->vect);
        free(q->vect);
        q->size = 0;

        uint64_t* tmp_wp = (uint64_t*)&(q->vect);
        *tmp_wp = tmp;

        // *(uint64_t*)&(q -> vect) = tmp ;
        qv = (uint32_t*)&(q->vect);
    }
    uint64_t buff = 0;
    for (size_t w = 0; w < qs; ++w) {
        buff += qv[w];
        if (w < es) {
            buff += ev[w];
        }
        qv[w] = buff & 4294967295;
        buff >>= 32;
    }
    return 0;
}

static int bn_M_add_to_fast(bn* q, bn const* e, uint64_t start) {
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : (const uint32_t*)&(e->vect);
    uint32_t es = e->size ? e->size : 2;
    if (qs and qv[qs - 1] == 0) {
        qs -= 1;
    }
    if (es and ev[es - 1] == 0) {
        es -= 1;
    }
    qs = (qs > es ? qs : es) + 1;
    if (q->size and qs > q->size) {
        q->vect = (uint32_t*)realloc(q->vect, qs * sizeof(uint32_t));
        qv = q->vect;
        // for (size_t w = q -> size ; w < qs ; ++w) {
        // q -> vect[w] = 0 ;
        //}
        memset(q->vect + q->size, 0, (qs - q->size) * sizeof(uint32_t));
        q->size = qs;
    } else if (q->size == 0 and qs > 2) {
        uint64_t* tmp_p = (uint64_t*)&(q->vect);
        uint64_t tmp = *tmp_p;

        // uint64_t tmp = *(uint64_t*)&(q -> vect) ;
        q->vect = (uint32_t*)calloc(1, qs * sizeof(uint32_t));
        *(uint64_t*)(q->vect) = tmp;
        qv = q->vect;
        q->size = qs;
    } else if (q->size and qs < 3) {
        uint64_t tmp = *(uint64_t*)(q->vect);
        free(q->vect);
        q->size = 0;

        uint64_t* tmp_wp = (uint64_t*)&(q->vect);
        *tmp_wp = tmp;

        // *(uint64_t*)&(q -> vect) = tmp ;
        qv = (uint32_t*)&(q->vect);
    }
    uint64_t buff = 0;
    for (size_t w = start; w < qs; ++w) {
        buff += qv[w];
        if (w < es) {
            buff += ev[w];
        }
        qv[w] = buff & 4294967295;
        buff >>= 32;
        if (!buff and w > start) {
            return 0;
        }
    }
    return 0;
}

static int bn_M_sub_to(bn* q, bn const* e) {
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : (const uint32_t*)&(e->vect);
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        qs -= 1;
    }
    while (es and ev[es - 1] == 0) {
        es -= 1;
    }
    qs = (qs > es ? qs : es) + 1;
    if (q->size and qs > q->size) {
        q->vect = (uint32_t*)realloc(q->vect, qs * sizeof(uint32_t));
        qv = q->vect;
        // for (size_t w = q -> size ; w < qs ; ++w) {
        // q -> vect[w] = 0 ;
        //}
        memset(q->vect + q->size, 0, (qs - q->size) * sizeof(uint32_t));
        q->size = qs;
    } else if (q->size == 0 and qs > 2) {
        uint64_t* tmp_p = (uint64_t*)&(q->vect);
        uint64_t tmp = *tmp_p;
        q->vect = (uint32_t*)calloc(1, qs * sizeof(uint32_t));
        *(uint64_t*)(q->vect) = tmp;
        qv = q->vect;
        q->size = qs;
    } else if (q->size and qs < 3) {
        uint64_t tmp = *(uint64_t*)(q->vect);
        free(q->vect);
        q->size = 0;

        uint64_t* tmp_wp = (uint64_t*)&(q->vect);
        *tmp_wp = tmp;

        // *(uint64_t*)&(q -> vect) = tmp ;
        qv = (uint32_t*)&(q->vect);
    }
    int64_t buff = 0;
    for (size_t w = 0; w < qs; ++w) {
        buff += qv[w];
        if (w < es) {
            buff -= ev[w];
        }
        qv[w] = buff & 4294967295;
        buff >>= 32;
    }
    size_t b = 0;
    for (size_t w = 0; w < qs; ++w) {
        if (qv[w]) {
            b = 1;
            break;
        }
    }
    if (!b) {
        q->sign = 0;
    }
    return 0;
}

int bn_add_to(bn* q, const bn* e) {
    int j = q->sign;
    int k = e->sign;
    int l;
    {
        int32_t qs = q->sign;
        q->sign = e->sign;
        l = bn_cmp(q, e);
        q->sign = qs;
    }
    if (!k) {
        return 0;
    }
    bn data[1];
    memset(data, 0, sizeof(data));
    bn* h = data + 0;
    if (j <= 0) {
        if (k < 0) {
            bn_M_add_to(q, e);
            q->sign = -1;
        } else {
            if (l >= 0) {
                bn_M_sub_to(q, e);
            } else {
                bn_swap(h, q);
                bn_init_bn(q, e);
                bn_M_sub_to(q, h);
            }
        }
    } else {
        if (k < 0) {
            if (l <= 0) {
                bn_M_sub_to(q, e);
            } else {
                bn_swap(h, q);
                bn_init_bn(q, e);
                bn_M_sub_to(q, h);
            }
        } else {
            bn_M_add_to(q, e);
            q->sign = 1;
        }
    }
    bn_del(h);
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    size_t b = 0;
    for (size_t w = 0; w < qs; ++w) {
        if (qv[w]) {
            b = 1;
            break;
        }
    }
    if (!b) {
        q->sign = 0;
    }
    return 0;
}

int bn_sub_to(bn* q, const bn* e) {
    q->sign *= -1;
    bn_add_to(q, e);
    q->sign *= -1;
    return 0;
}

bn* bn_add(const bn* q, const bn* w) {
    bn* h = bn_init(q);
    bn_add_to(h, w);
    return h;
}

bn* bn_sub(const bn* q, const bn* w) {
    bn* h = bn_init(q);
    bn_sub_to(h, w);
    return h;
}

uint64_t bn_fft_pow(uint64_t q, uint64_t w, uint64_t e) {
    uint64_t res = 1;
    while (w) {
        if (w % 2) {
            res *= q;
            res %= e;
        }
        q *= q;
        q %= e;
        w /= 2;
    }
    return res;
}

uint64_t bn_fft_mod = 3221225473;
uint64_t bn_fft_root = 13;
uint64_t bn_fft_ro = 1073741824;

uint64_t bn_fft_rp0[65536];
uint64_t bn_fft_rp1[65536];

void bn_fft_prepare() {
    bn_fft_rp0[0] = 1;

    for (size_t w = 1; w < 65536; ++w) {
        bn_fft_rp0[w] = bn_fft_rp0[w - 1] * bn_fft_root % bn_fft_mod;
    }

    bn_fft_rp1[0] = 1;
    bn_fft_rp1[1] = bn_fft_root * bn_fft_rp0[65536 - 1];
    bn_fft_rp1[1] %= bn_fft_mod;

    for (size_t w = 2; w < 65536; ++w) {
        bn_fft_rp1[w] = bn_fft_rp1[w - 1] * bn_fft_rp1[1] % bn_fft_mod;
    }
}

uint64_t bn_fft_roots(uint64_t n, uint64_t k) {
    assert(bn_fft_rp0[0] == 1);
    k %= n;
    uint64_t p = (size_t)(bn_fft_ro / n * k);
    uint16_t* pp = (uint16_t*)&p;
    return (bn_fft_rp0[pp[0]] * bn_fft_rp1[pp[1]]) % bn_fft_mod;
}

uint64_t* bn_fft_bi = 0;
uint64_t bn_fft_bil = 0;
uint64_t bn_fft_bim = 0;

uint64_t bn_fft_bitinv(uint64_t t, uint64_t l) {
    while (bn_fft_bil <= t) {
        uint64_t r = bn_fft_bil;
        uint64_t x = 0;
        for (uint64_t c = 0; c < 32; ++c) {
            x *= 2;
            x += r % 2;
            r /= 2;
        }
        if (bn_fft_bil == bn_fft_bim) {
            uint64_t* t = (uint64_t*)malloc(sizeof(uint64_t) * (bn_fft_bim * 2 + 1));
            memcpy(t, bn_fft_bi, bn_fft_bim * sizeof(bn_fft_bi[0]));
            free(bn_fft_bi);
            bn_fft_bi = t;
            bn_fft_bim *= 2;
            bn_fft_bim += 1;
        }
        bn_fft_bi[bn_fft_bil++] = x;
    }
    return bn_fft_bi[t] >> (32 - l);
}

void bn_fft_prep(uint64_t* a, uint64_t n) {
    uint64_t l = 0;
    uint64_t o = n;
    while (o) {
        o /= 2;
        l += 1;
    }
    l -= 1;
    for (size_t w = 0; w < n; ++w) {
        size_t r = w;
        size_t x = (size_t)bn_fft_bitinv(r, l);
        if (w < x) {
            uint64_t t = a[w];
            a[w] = a[x];
            a[x] = t;
        }
    }
}

void bn_fft_fftr(uint64_t* a, int inv, uint64_t b, uint64_t e) {
    if (bn_fft_rp0[0] != 1) {
        bn_fft_prepare();
    }
    uint64_t n = e - b;
    uint64_t h = n / 2;
    uint64_t _n = n;
    uint64_t _b = b;
    uint64_t _e = e;
    n = 2;
    while (n <= _n) {
        for (b = _b; b != _e; b += n) {
            e = b + n;
            h = n / 2;
            for (uint64_t k = 0; k < h; k++) {
                uint64_t a0 = a[b + k];
                uint64_t a1 = a[b + k + h];
                uint64_t t = inv < 0 ? n - k : n + k;
                uint64_t r = bn_fft_roots(n, t);
                r *= a1;
                r %= bn_fft_mod;
                a[b + k] = (a0 + r) % bn_fft_mod;
                a[b + k + h] = (a0 + bn_fft_mod - r) % bn_fft_mod;
            }
        }
        n *= 2;
    }
}

void bn_fft_fft(uint64_t* a, uint64_t n, int inv) {
    uint64_t b = 0;
    uint64_t e = n;
    bn_fft_prep(a, n);
    bn_fft_fftr(a, inv, b, e);
    if (inv == -1) {
        for (uint64_t w = 0; w < n; ++w) {
            a[w] *= bn_fft_pow(n, bn_fft_mod - 2, bn_fft_mod);
            a[w] %= bn_fft_mod;
        }
    }
}

int bn_mul_to(bn* q, const bn* e) {
    uint64_t base = 16;
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : (const uint32_t*)&(e->vect);
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    while (es and ev[es - 1] == 0) {
        --es;
    }
    bn data[2];
    memset(data, 0, sizeof(data));
    bn* res = data + 1;
    if (qs + es > 512) {
        uint8_t* qb = (uint8_t*)qv;
        uint8_t* eb = (uint8_t*)ev;
        size_t l = qs;
        if (es > qs) {
            l = es;
        }
        size_t dl = 1;
        while (dl < l) {
            dl *= 2;
        }
        l = dl * 2 * 8;
        uint64_t* a = (uint64_t*)calloc(l, sizeof(uint64_t));
        for (size_t w = 0; w < qs * 4; w++) {
            a[w * 2] = qb[w] & 0xF;
            a[w * 2 + 1] = qb[w] >> 4;
        }
        uint64_t* s = (uint64_t*)calloc(l, sizeof(uint64_t));
        for (size_t w = 0; w < es * 4; w++) {
            s[w * 2] = eb[w] & 0xF;
            s[w * 2 + 1] = eb[w] >> 4;
        }
        bn_fft_fft(a, l, 1);
        bn_fft_fft(s, l, 1);
        for (size_t w = 0; w < l; w++) {
            a[w] *= s[w];
            a[w] %= bn_fft_mod;
        }
        bn_fft_fft(a, l, -1);
        for (size_t w = 1; w < l; w++) {
            a[w] += a[w - 1] / base;
            a[w - 1] %= base;
        }
        res->size = qs + es;
        res->vect = (uint32_t*)calloc(1, res->size * sizeof(uint32_t));
        res->sign = q->sign * e->sign;

        uint8_t* rb = (uint8_t*)(res->vect);

        for (size_t w = 0; w < res->size * 4; ++w) {
            rb[w] |= a[2 * w];
            rb[w] |= a[2 * w + 1] << 4;
        }
        free(a);
        free(s);
    } else if (qs + es > 2) {
        // ic(itervect(qv , qv+qs))
        bn* tmp = data + 0;
        res->size = qs + es;
        tmp->size = qs + es;
        res->vect = (uint32_t*)calloc(1, res->size * sizeof(uint32_t));
        tmp->vect = (uint32_t*)calloc(1, tmp->size * sizeof(uint32_t));
        // memset(res -> vect , 0 , (res -> size)*sizeof(uint32_t)) ;
        // memset(tmp -> vect , 0 , (tmp -> size)*sizeof(uint32_t)) ;
        // for (size_t w = 0 ; w < res -> size ; ++w) {
        // res -> vect[w] = 0 ;
        // tmp -> vect[w] = 0 ;
        //}
        // ic(itervect(qv , qv+qs))
        tmp->sign = 1;
        for (size_t w = 0; w < qs; ++w) {
            if (qv[w]) {
                for (size_t r = 0; r < es; ++r) {
                    uint64_t _tmp = ((uint64_t)(qv[w])) * ((uint64_t)(ev[r]));
                    *(tmp->vect + w + r) = _tmp & 4294967295;
                    *(tmp->vect + w + r + 1) = _tmp >> 32;
                    bn_M_add_to_fast(res, tmp, w + r);
                    *(tmp->vect + w + r) = 0;
                    *(tmp->vect + w + r + 1) = 0;
                }
            }
        }
        res->sign = q->sign * e->sign;
        bn_del(tmp);
    } else {
        res->sign = q->sign * e->sign;
        res->size = 0;

        uint64_t* tmp_wp = (uint64_t*)&(res->vect);
        *tmp_wp = *(uint64_t*)(qv) * *(const uint64_t*)(ev);
    }
    bn_swap(res, q);
    bn_del(res);
    return 0;
}

int bn_mul__to(bn* q, const bn* e) {
    // ic(q , e)
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    const uint32_t* ev = e->size ? e->vect : (const uint32_t*)&(e->vect);
    uint32_t es = e->size ? e->size : 2;
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    while (es and ev[es - 1] == 0) {
        --es;
    }
    bn data[2];
    memset(data, 0, sizeof(data));
    bn* res = data + 1;
    if (qs + es > 2) {
        // ic(itervect(qv , qv+qs))
        bn* tmp = data + 0;
        res->size = qs + es;
        tmp->size = qs + es;
        res->vect = (uint32_t*)calloc(1, res->size * sizeof(uint32_t));
        tmp->vect = (uint32_t*)calloc(1, tmp->size * sizeof(uint32_t));
        // memset(res -> vect , 0 , (res -> size)*sizeof(uint32_t)) ;
        // memset(tmp -> vect , 0 , (tmp -> size)*sizeof(uint32_t)) ;
        // for (size_t w = 0 ; w < res -> size ; ++w) {
        // res -> vect[w] = 0 ;
        // tmp -> vect[w] = 0 ;
        //}
        // ic(itervect(qv , qv+qs))
        tmp->sign = 1;
        for (size_t w = 0; w < qs; ++w) {
            if (qv[w]) {
                for (size_t r = 0; r < es; ++r) {
                    uint64_t _tmp = ((uint64_t)(qv[w])) * ((uint64_t)(ev[r]));
                    *(tmp->vect + w + r) = _tmp & 4294967295;
                    *(tmp->vect + w + r + 1) = _tmp >> 32;
                    bn_M_add_to_fast(res, tmp, w + r);
                    *(tmp->vect + w + r) = 0;
                    *(tmp->vect + w + r + 1) = 0;
                }
            }
        }
        res->sign = q->sign * e->sign;
        bn_del(tmp);
    } else {
        res->sign = q->sign * e->sign;
        res->size = 0;

        uint64_t* tmp_wp = (uint64_t*)&(res->vect);
        *tmp_wp = *(uint64_t*)(qv) * *(const uint64_t*)(ev);

        // *(uint64_t*)&(res -> vect) = *(uint64_t*)(qv)* *(const uint64_t*)(ev) ;
    }
    bn_swap(res, q);
    bn_del(res);
    return 0;
}

bn* bn_mul(const bn* q, const bn* w) {
    bn* h = bn_init(q);
    bn_mul_to(h, w);
    return h;
}

int bn_neg(bn* q) {
    q->sign *= -1;
    return 0;
}

int bn_abs(bn* q) {
    q->sign = (bool)(q->sign);
    return 0;
}

int bn_sign(const bn* q) {
    return q->sign;
}

static int bn_half(bn* q) {
    if (q->size) {
        q->vect[0] >>= 1;
    } else {

        uint64_t* tmp_wp = (uint64_t*)&(q->vect);
        *tmp_wp >>= 1;

        // *(uint64_t*)&(q -> vect) >>= 1 ;
        if (!*tmp_wp) {
            q->sign = 0;
        }
        return 0;
    }
    for (size_t w = 1; w < q->size; ++w) {
        q->vect[w - 1] |= (q->vect[w] & 1) << 31;
        q->vect[w] >>= 1;
    }
    size_t b = 0;
    for (size_t w = 0; w < q->size; ++w) {
        if (q->vect[w]) {
            b = 1;
            break;
        }
    }
    if (!b) {
        q->sign = 0;
    }
    return 0;
}

int bn_M_div_to(bn* q, bn* e) {
    uint32_t* qv = q->size ? q->vect : (uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    uint32_t* ev = e->size ? e->vect : (uint32_t*)&(e->vect);
    uint32_t es = e->size ? e->size : 2;
    // ic(q , e)
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    while (es and ev[es - 1] == 0) {
        --es;
    }
    assert(es);
    bn data[2];
    memset(data, 0, sizeof(data));
    if (qs >= es) {
        bn* t = data + 0;
        t->size = qs + 2;
        t->sign = 1;
        t->vect = (uint32_t*)calloc(sizeof(uint32_t), t->size);
        memcpy(t->vect + qs - es + 2, ev, es * sizeof(uint32_t));
        // for(size_t w = 0 ; w < es ; ++w) {
        // (t -> vect+qs-es+2)[w] = ev[w] ;
        //}
        ssize_t f = (qs - es + 2) * 32;
        bn* r = data + 1;
        uint32_t* rv;
        uint32_t rs;
        if (qs + 1 - es > 2) {
            r->size = qs + 1 - es;
            r->sign = 1;
            r->vect = (uint32_t*)calloc(sizeof(uint32_t), r->size);
            rv = r->vect;
            rs = r->size;
        } else {
            r->size = 0;
            r->sign = 1;
            r->vect = 0;
            rv = (uint32_t*)&(r->vect);
            rs = 2;
        }
        while (f >= 0) {
            // ic(q , r , a[f&31] , f)
            // if (bn_cmp(q , a[f&31]) >= 0) {
            // rv[f >> 5] |= (1LL << (f&31)) ;
            // bn_M_sub_to(q , a[f&31]) ;
            //}
            // a[f&31] -> size -= 1 ;
            // a[f&31] -> vect += 1 ;
            // o[f&31] += 1 ;
            // f -= 1 ;
            // // bn_half(t) ;
            if (bn_cmp(q, t) >= 0) {
                rv[f >> 5] |= (1LL << (f & 31));
                bn_M_sub_to(q, t);
            }
            // t -> size -= 1 ;
            // t -> vect += 1 ;
            // o[f&31] += 1 ;
            f -= 1;
            bn_half(t);
        }
        size_t b = 0;
        for (size_t w = 0; w < rs; ++w) {
            if (rv[w]) {
                b = 1;
                break;
            }
        }
        if (!b) {
            r->sign = 0;
        }
        // for (size_t w = 0 ; w < 32 ; ++w) {
        // a[w] -> vect -= o[w] ;
        // // ic(a[w] -> vect)
        // bn_delete(a[w]) ;
        //}
        // free(o) ;
        // free(a) ;
        bn_swap(e, r);
        // bn_init_bn(e , r) ;
        bn_del(r);
        bn_del(t);
    } else {
        bn_init_int(e, 0);
    }
    return 0;
}

int bn_div_to(bn* q, const bn* e) {
    bn data[2];
    memset(data, 0, sizeof(data));
    bn* a = data + 0;
    bn* d = data + 1;
    bn_init_bn(a, q);
    a->sign = (bool)(a->sign);
    bn_init_bn(d, e);
    d->sign = (bool)(d->sign);
    bn_M_div_to(a, d);
    if (q->sign * e->sign < 0) {
        if (a->sign) {
            bn_init_int(a, -1);
            bn_sub_to(a, d);
            bn_del(d);
            bn_swap(q, a);
            // bn_init_bn(q , a) ;
            bn_del(a);
            return 0;
        }
        d->sign *= -1;
        bn_del(a);
        bn_swap(q, d);
        // bn_init_bn(q , d) ;
        bn_del(d);
        return 0;
    } else {
        bn_del(a);
        bn_swap(q, d);
        // bn_init_bn(q , d) ;
        bn_del(d);
        return 0;
    }
}

bn* bn_div(const bn* q, const bn* w) {
    bn* h = bn_init(q);
    bn_div_to(h, w);
    return h;
}

int bn_mod_to(bn* q, const bn* e) {
    bn data[2];
    memset(data, 0, sizeof(data));
    bn* a = data + 0;
    bn* d = data + 1;
    bn_init_bn(a, q);
    a->sign = (bool)(a->sign);
    bn_init_bn(d, e);
    d->sign = (bool)(d->sign);
    bn_M_div_to(a, d);
    // ic(a , d)
    if (q->sign * e->sign < 0) {
        if (a->sign) {
            a->sign = e->sign;
            bn_sub_to(a, e);
            a->sign = e->sign;
            bn_del(d);
            bn_swap(q, a);
            bn_del(a);
            return 0;
        }
        bn_del(d);
        bn_swap(q, a);
        // bn_init_bn(q , a) ;
        bn_del(a);
        return 0;
    } else {
        bn_del(d);
        a->sign *= q->sign;
        bn_swap(q, a);
        // bn_init_bn(q , a) ;
        bn_del(a);
        return 0;
    }
}

bn* bn_mod(const bn* q, const bn* w) {
    bn* h = bn_init(q);
    bn_mod_to(h, w);
    return h;
}

int bn_pow_to(bn* q, int _e) {
    uint64_t e = (uint64_t)(int64_t)(_e);
    size_t s = 0;
    for (size_t w = 0; w < 64; ++w) {
        if ((1ULL << w) & e) {
            s = w + 1;
        }
    }
    if (s) {
        bn a[64];
        memset(a, 0, sizeof(a));
        bn_init_bn(a + 0, q);
        for (size_t w = 1; w < s; ++w) {
            bn_init_bn(a + w, a + w - 1);
            bn_mul_to(a + w, a + w);
        }
        bn_init_int(q, 1);
        for (size_t w = 0; w < s; ++w) {
            if ((1 << w) & e) {
                bn_mul_to(q, a + w);
            }
        }
        for (size_t w = 0; w < s; ++w) {
            bn_del(a + w);
        }
        // free(a) ;
    } else {
        bn_init_int(q, 1);
    }
    return 0;
}

int bn_root2_to(bn* q) {
    bn data[3];
    memset(data, 0, sizeof(data));
    bn* r = data + 0;
    bn* p = data + 1;
    // uint32_t*rv , pv ;
    // uint32_t ps , rs ;
    if (q->size + 1 > 2) {
        r->size = q->size + 1;
        r->sign = 1;
        r->vect = (uint32_t*)calloc(sizeof(uint32_t), r->size);
        // rv = r -> vect ;
        // rs = r -> size ;
        p->size = q->size + 1;
        p->sign = 1;
        p->vect = (uint32_t*)calloc(sizeof(uint32_t), p->size);
        p->vect[p->size - 1] = 1;
        // pv = p -> vect ;
        // ps = p -> size ;
    } else {
        r->size = 0;
        r->sign = 1;
        r->vect = 0;
        // rv = (uint32_t*)&(r -> vect) ;
        // rs = 2 ;
        p->size = 0;
        p->sign = 1;
        p->vect = (uint32_t*)(uint64_t)(1LL << 32);
        // pv = (uint32_t*)&(p -> vect) ;
        // ps = 2 ;
    }
    bn* u = data + 2;
    while (p->sign) {
        bn_init_bn(u, r);
        bn_add_to(u, p);
        if (bn_cmp(q, u) >= 0) {
            bn_sub_to(q, u);
            bn_add_to(r, p);
            bn_add_to(r, p);
        }
        bn_half(r);
        bn_half(p);
        bn_half(p);
    }
    bn_del(u);
    bn_swap(q, r);
    // bn_init_bn(q , r) ;
    bn_del(r);
    bn_del(p);
    return 0;
}

int bn_root_to(bn* q, int __e) {
    if (__e == 2) {
        return bn_root2_to(q);
    }
    bn data[6];
    memset(data, 0, sizeof(data));
    uint64_t e = (uint64_t)(int64_t)(__e);
    bn* _b = data + 0;
    bn* _e = data + 1;
    uint32_t tmp = q->size / e + 1;
    if (tmp > 2) {
        _e->size = tmp;
        _e->sign = 1;
        _e->vect = (uint32_t*)calloc(sizeof(uint32_t), _e->size);
        _e->vect[_e->size - 1] = 1LL << 31;
    } else {
        _e->size = 0;
        _e->sign = 1;
        _e->vect = (uint32_t*)(uint64_t)(1ULL << 63);
    }
    bn* _c = data + 2;
    bn* _d = data + 3;
    bn* _f = data + 4;
    bn* _g = data + 5;
    bn_init_int(_g, 2);
    while (1) {
        bn_init_bn(_f, _e);
        bn_sub_to(_f, _b);
        if (bn_cmp(_f, _g) < 0) {
            break;
        }
        bn_init_bn(_c, _b);
        bn_add_to(_c, _e);
        bn_half(_c);
        bn_init_bn(_d, _c);
        bn_pow_to(_d, (int)(e));
        int j = bn_cmp(_d, q);
        if (j < 0) {
            bn_init_bn(_b, _c);
        } else if (j > 0) {
            bn_init_bn(_e, _c);
        } else if (j == 0) {
            bn_init_bn(_e, _c);
            bn_init_bn(_b, _c);
        }
    }
    bn_del(_c);
    bn_del(_d);
    bn_del(_f);
    bn_del(_g);
    bn_swap(q, _b);
    // bn_init_bn(q , _b) ;
    bn_del(_b);
    bn_del(_e);
    return 0;
}

int bn_init_string_radix(bn* q, const char* e, int t) {
    // size_t l = strlen(e) ;
    size_t l = 0;
    while (
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"[(int)(e[l])]) {
        e++;
    }
    if (e[l] == '+') {
        e++;
    }
    if (e[l] == '-') {
        l++;
    }
    while ((unsigned)("\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                      "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x0a\x0b\x0c\x0d\x0e\x0f\xFF"
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                      "\xFF\x0a\x0b\x0c\x0d\x0e\x0f\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"[(int)(e[l])]) < (unsigned)(t)) {
        l++;
    }
    uint32_t qs =
        (uint32_t)(l / (unsigned)("\x00\x00\x20\x14\x10\x0d\x0c\x0b\x0a\x0a\x09\x09\x08\x08\x08\x08\x08\x07\x07\x07\x07"
                                  "\x07\x07\x07\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06\x06"[t]) +
                   1);
    if (q->size and q->vect) {
        free(q->vect);
    }
    if (qs > 2) {
        q->size = qs;
        q->vect = (uint32_t*)calloc(sizeof(uint32_t), q->size);
    } else {
        q->size = 0;
        q->vect = 0;
    }
    q->sign = 0;
    bn data[2];
    memset(data, 0, sizeof(data));
    bn* a = data + 0;
    bn* y = data + 1;
    bn_init_int(y, t);
    size_t g = 0;
    if (l and e[0] == '-') {
        g = 1;
    }
    for (size_t w = g; w < l; ++w) {
        // ic(q , y , a)
        bn_mul_to(q, y);
        // ic(q , y , a)
        bn_init_int(
            a,
            "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19"
            "\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03"
            "\x04\x05\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16"
            "\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10"
            "\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d\x7e\x7f"[(
                int)(e[w])]);
        if (a->sign) {
            q->sign = 1;
        }
        bn_M_add_to_fast(q, a, 0);
    }
    q->sign *= "\x01\xff"[g];
    bn_del(a);
    bn_del(y);
    return 0;
}

int bn_init_string(bn* q, const char* e) {
    return bn_init_string_radix(q, e, 10);
}

char* bn_to_string(const bn* q, int e) {
    const uint32_t* qv = q->size ? q->vect : (const uint32_t*)&(q->vect);
    uint32_t qs = q->size ? q->size : 2;
    while (qs and qv[qs - 1] == 0) {
        --qs;
    }
    uint64_t _t = (uint64_t)(e);
    bn data[1];
    memset(data, 0, sizeof(data));
    bn* r = data + 0;
    // ic(int64_t(r) , int64_t(q))
    bn_init_bn(r, q);
    r->sign = (bool)(r->sign);
    uint32_t* rv = r->size ? r->vect : (uint32_t*)&(r->vect);
    uint32_t rs = qs;
    char* a = (char*)calloc(
        sizeof(char),
        2 + (qs + 1) * (unsigned)("\x00\x00\x20\x15\x10\x0e\x0d\x0c\x0b\x0b\x0a\x0a\x09\x09\x09\x09\x08\x08\x08\x08\x08"
                                  "\x08\x08\x08\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07"[_t]));
    size_t s = 0;
    while (r->sign) {
        uint64_t b = 0;
        uint64_t t = 0;
        r->sign = 0;
        for (size_t _w = rs; _w > 0; --_w) {
            size_t w = _w - 1;
            t = rv[w];
            t += b << 32;
            b = t % _t;
            t /= _t;
            rv[w] = (uint32_t)(t);
            if (t) {
                r->sign = 1;
            }
        }
        a[s++] = (char)(b);
    }
    for (size_t w = 0; w < s; ++w) {
        a[w] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(int)(a[w])];
    }
    if (q->sign < 0) {
        a[s++] = '-';
    }
    if (!s) {
        a[s++] = '0';
    }
    for (size_t w = 0; w * 2 < s; ++w) {
        char t = a[w];
        a[w] = a[s - 1 - w];
        a[s - 1 - w] = t;
    }
    bn_del(r);
    return a;
}

bn* bn_root(bn* q, int _w) {
    // uint64_t w = (uint64_t)(_w) ;
    bn* h = bn_init(q);
    bn_root_to(h, _w);
    return h;
}

bn* bn_pow(bn* q, int w) {
    bn* h = bn_init(q);
    bn_pow_to(h, w);
    return h;
}

#endif

auto Read() {
    size_t n = scan;
    vector<__int128_t> a(n + 1);
    for (auto& q : a) {
        int t = 0;
        cin >> t;
        q = t;
    }
    // int as=a[0]<0?-1:1;
    // if (as<0){
    // 	for (auto&q:a){
    // 		q=-q;
    // 	}
    // }
    reverse(a.begin(), a.end());
    for (size_t q = 0; q < a.size(); ++q) {
        // if (a[q-1]<0){
        a[q] += 100000000000000;
        // a[q]-=1;
        // }
    }
    a.push_back(0);
#ifdef nv
    auto am = static_cast<uint32_t*>(mem.Calloc(a.size(), sizeof(a[0])));
#else
    auto am = static_cast<uint32_t*>(calloc(a.size(), sizeof(a[0])));
#endif
    memcpy(am, a.data(), a.size() * sizeof(a[0]));
#ifdef nv
    BnFs f = {0, 0, nullptr};
#else
    bn_s f = {0, 0, nullptr};
#endif
    f.sign = 1;
    f.size = a.size() * sizeof(a[0]) / sizeof(int32_t);
    f.vect = am;
    // return make_tuple(f,as);
    return f;
}

int main() {
    auto a = Read();
    auto b = Read();
// cout<<BnFtoString(&a,10)<<endl;
// cout<<BnFtoString(&b,10)<<endl;
#ifdef nv
    BnFmulTo(&a, &b);
#else
    bn_mul_to(&a, &b);
#endif
    // cout<<BnFtoString(&a,10)<<endl;
    auto q = &a;
    uint32_t* qv = q->size ? q->vect : reinterpret_cast<uint32_t*>(&(q->vect));
    uint32_t qs = q->size ? q->size : 2;
    vector<__int128_t> d(qs);
    memcpy(d.data(), qv, qs * sizeof(int32_t));
// for (size_t w=0;w<qs;++w){
// 	d.dat
// 	d.push_back(qv[w]);
// }
#ifdef nv
    BnFdel(&b);
    BnFdel(&a);
#else
    bn_del(&a);
    bn_del(&b);
#endif
    d.push_back(0);
    for (size_t q = 0; q < d.size(); ++q) {
        // if (d[q-1]>9){
        // 	d[q-1]-=19;
        // 	d[q]+=1;
        // }
        d[q] %= 100000000000000;
        if (d[q] >= 100000000000000 / 2) {
            d[q] -= 100000000000000;
        }
    }
    while (d.back() == 0) {
        d.pop_back();
    }
    // ic(d)
    reverse(d.begin(), d.end());
    // if (as*bs<0){
    // 	for (auto&q:d){
    // 		q=-q;
    // 	}
    // }
    cout << d.size() - 1 << " ";
    for (auto& q : d) {
        cout << static_cast<ssize_t>(q) << " ";
    }
    cout << endl;
}

// auto Read(){
//     size_t n=scan;
//     vector<__int128_t> a(n+1);
// 	for (auto&q:a){
// 		int t;
// 		cin>>t;
// 		q=t;
// 	}
// 	int as=a[0]<0?-1:1;
// 	if (as<0){
// 		for (auto&q:a){
// 			q=-q;
// 		}
// 	}
//     reverse(a.begin(),a.end());
// 	size_t o=0;
// 	for (auto&q:a){
// 		q-=o;
// 		o=0;
// 		if (q<0){
// 			q+=256;
// 			o=1;
// 		}
// 		q=(q>>4<<64)+(q&0xf);
// 	}
// 	assert(!o);
// 	size_t m=n;
// 	size_t b=1;
// 	while (b<=2*m){
// 		b<<=1;
// 	}
// 	a.resize(b);
// 	return make_tuple(as,n,a);
// }

// int main(){
// 	auto [as,n,a]=Read();
// 	auto [bs,m,b]=Read();
// 	a.resize(max(a.size(),b.size()));
// 	b.resize(max(a.size(),b.size()));
// 	ic(a)
// 	ic(b)
// 	BnFfftFft(static_cast<uint64_t*>a.data(),a.size()*2,1);
// 	BnFfftFft(static_cast<uint64_t*>b.data(),b.size()*2,1);
// 	for (size_t q=0;q<a.size()*2;++q){
// 		(static_cast<uint64_t*>a.data())[q]*=(static_cast<uint64_t*>b.data())[q];
// 	}
// 	BnFfftFft(static_cast<uint64_t*>a.data(),a.size()*2,-1);
// 	ic(a)
// 	for (size_t q=1;q<a.size();++q){
// 		a[q]+=a[q-1]/16;
// 		a[q-1]%=16;
// 	}
// 	for (auto&q:a){
// 		q=(q&0xf)+(q>>64<<4);
// 	}
// 	size_t o=0;
// 	for (auto&q:a){
// 		q-=o;
// 		o=0;
// 		if (q>=128){
// 			q-=256;
// 			o=1;
// 		}
// 	}
// 	while(a.back()==0){
// 		a.pop_back();
// 	}
// 	reverse(a.begin(),a.end());
// 	if (as*bs<0){
// 		for (auto&q:a){
// 			q=-q;
// 		}
// 	}
// 	cout<<a.size()-1<<" ";
// 	for (auto&q:a){
// 		cout<<static_cast<ssize_t>q<<" ";
// 	}
// 	cout<<endl;
// }
