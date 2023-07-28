#include <bits/stdc++.h>
using namespace std;

auto heap_push(auto& one_indexed_ptr, size_t pos, auto&& val) {
    size_t par = pos / 2;
    while (par and one_indexed_ptr[par] > val) {
        one_indexed_ptr[pos] = one_indexed_ptr[par], pos = par, par /= 2;
    }
    one_indexed_ptr[pos] = val;
}

auto heap_pop(auto& one_indexed_ptr, size_t len) {
    auto cur_ptr = one_indexed_ptr + 1, swap_ptr = cur_ptr, left_ptr = cur_ptr, right_ptr = cur_ptr;
    auto last = one_indexed_ptr[len];
    while (left_ptr = cur_ptr - one_indexed_ptr + cur_ptr, right_ptr = left_ptr + 1,
           last > left_ptr[0] or last > right_ptr[0]) {
        swap_ptr = left_ptr[0] < right_ptr[0] ? left_ptr : right_ptr;
        cur_ptr[0] = swap_ptr[0], cur_ptr = swap_ptr;
    }
    cur_ptr[0] = last;
}

auto k_largest_heap(auto&& a, size_t n) {
    vector<size_t> result_vect(n * 2 + 1, -1);
    auto result = result_vect.data() - 1;
    size_t len = 1;
    for (auto& s : a) {
        heap_push(result, len, s);
        len == n + 1 ? heap_pop(result, len), len : len += 1;
    }
    result += 1;
    sort(result, result + n);
    result_vect.resize(n);
    return result_vect;
}

auto k_largest_chunk_sort(auto& a, size_t n) {
    vector<size_t> result_vect(n * 2);
    auto result = result_vect.data();
    size_t len = 0;
    for (auto& s : a) {
        result[len++] = s;
        if (len == n * 2) {
            sort(result_vect.rbegin(), result_vect.rend());
            len = n;
        }
    }
    sort(result_vect.rbegin(), result_vect.rend());
    result_vect.resize(n);
    reverse(result_vect.begin(), result_vect.end());
    return result_vect;
}

auto k_largest_sort_all(auto& a, size_t n) {
    vector<size_t> result_vect(a);
    sort(result_vect.rbegin(), result_vect.rend());
    result_vect.resize(n);
    reverse(result_vect.begin(), result_vect.end());
    return result_vect;
}

int main() {
    vector<size_t> a(10'000'000);
    auto rand = mt19937_64();
    for (auto& s : a) {
        s = rand();
    }
    while (1) {
        size_t k = rand();
        k = k % a.size() + 1;

        auto time = clock();
        auto z = k_largest_heap(a, k);
        auto heap_time = clock()-time;

        time = clock();
        auto x = k_largest_chunk_sort(a, k);
        auto chunk_sort_time = clock()-time;

        time = clock();
        auto c = k_largest_sort_all(a, k);
        auto sort_all_time = clock()-time;

        assert(z == x and x == c);
        printf("%zu\t%zu\t%zu\t%zu\n", k,heap_time, chunk_sort_time, sort_all_time);
        fflush(stdout);
    }
}
