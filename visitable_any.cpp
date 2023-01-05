#include <algorithm>
#include <any>
#include <cstddef>
#include <assert.h>
#include <exception>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <variant>

template <size_t n> struct visit_any_types {
  using type = std::tuple<>;
};

template <typename... T> constexpr auto visit_any_all() {
  bool v[] = {std::is_same_v<std::decay_t<T>, std::any>...};
  return std::find_if(v, v + sizeof...(T), [&](auto q) { return not q; }) ==
         v + sizeof...(T);
}

template <typename T>
using visit_any_one = std::enable_if_t<visit_any_all<T>(), int>;

#define add_visit_any(...)                                                     \
  template <> struct visit_any_types<__COUNTER__> {                            \
    using type = std::tuple<__VA_ARGS__>;                                      \
  };                                                                           \
  static_assert(dont_use_add_visit_any_after_end_visit_any(INT32_C(0)));

#define end_visit_any()                                                        \
  template <size_t n, size_t k>                                                \
  decltype(auto) visit_any(auto &a, const auto &f,                             \
                           visit_any_one<decltype(a)> = 0) {                   \
    using tu = typename visit_any_types<n>::type;                              \
    if constexpr (n == -1LLU) {                                                \
      std::cerr << "visit(any) failed: unknown type of value" << std::endl;    \
      std::cerr << "you can add your type by writing:" << std::endl;           \
      std::cerr << "" << std::endl;                                            \
      std::cerr << "add_visit_any(types...)" << std::endl;                     \
      throw std::exception();                                                  \
    } else if constexpr (k == std::tuple_size_v<tu>) {                         \
      return visit_any<n - 1, 0>(a, f);                                        \
    } else {                                                                   \
      using type = std::tuple_element_t<k, tu>;                                \
      if constexpr (requires { any_cast<type &>(a); }) {                       \
        if (typeid(type) == a.type()) {                                        \
          return f(any_cast<type &>(a));                                       \
        }                                                                      \
      }                                                                        \
      return visit_any<n, k + 1>(a, f);                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  void visit_any_f(auto &a, const auto &f, visit_any_one<decltype(a)>) {       \
    return visit_any<__COUNTER__, 0>(a, f);                                    \
  }                                                                            \
                                                                               \
  constexpr bool dont_use_add_visit_any_after_end_visit_any(int8_t t) {        \
    return 1;                                                                  \
  }                                                                            \
  bool use_end_visit_any_after_main_function(auto f) { return 1; }

constexpr bool dont_use_add_visit_any_after_end_visit_any(int16_t t) {
  return 1;
}

bool use_end_visit_any_after_main_function(auto f);

void visit_any_f(auto &a, const auto &f, visit_any_one<decltype(a)> = 0);

template <typename T> struct visit_any_ft {
  T f;
  visit_any_ft(T f) : f(f) {}
  template <typename Y, typename = visit_any_one<Y>> auto operator+(Y &a) {
    auto tmp = [&](auto &&...o) {
      visit_any_f(a, [&](auto &s) { return f(s, o...); });
    };
    return visit_any_ft<decltype(tmp)>(tmp);
  }
};

template <typename T>
visit_any_ft(T) -> visit_any_ft<std::remove_reference_t<T>>;

namespace std {
template <typename... T>
  requires(visit_any_all<T...>())
void visit(const auto &f, T &&...a) {
  assert(use_end_visit_any_after_main_function([]() {}));
  auto ff = visit_any_ft(f);
  return (ff + ... + a).f();
}
}; // namespace std


// add_visit_any(char, void);
// add_visit_any(int, const char *);
// // end_visit_any();

// int main() {
//   std::any a = -1, s = '0', d = "123";

//   auto f = [&](auto q, auto w, auto e) { ic(q, w, e); };

//   visit(f, a, s, d);
// }

// // add_visit_any(int, const char *);
