
# 1 "test.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 470 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "test.cpp" 2

using namespace std;
using llu = long long unsigned;
# 38 "test.cpp"
constexpr auto _a = array<int, 0>();
constexpr auto _a0 = array<int, 1>({0});
constexpr auto _a1 = array<int, 1>({1});
constexpr auto _b = array<int, 0>();
constexpr auto _b0 = array<int, 1>({0});
constexpr auto _b1 = array<int, 1>({1});
constexpr auto a = span(_a);
constexpr auto a0 = span(_a0);
constexpr auto a1 = span(_a1);
constexpr auto b = span(_b);
constexpr auto b0 = span(_b0);
constexpr auto b1 = span(_b1);
constexpr auto _a00 = array<int, 2>({0, 0});
constexpr auto _a10 = array<int, 2>({1, 0});
constexpr auto _a01 = array<int, 2>({0, 1});
constexpr auto _a11 = array<int, 2>({1, 1});
constexpr auto a00 = span<const int, 2>(_a00);
constexpr auto a10 = span<const int, 2>(_a10);
constexpr auto a01 = span<const int, 2>(_a01);
constexpr auto a11 = span<const int, 2>(_a11);

static_assert(is_same_v<pair<integral_constant<llu, (a).size()>,
                             integral_constant<decay_t<decltype((a)[0])>,
                                               (a).size() ? (a)[0] : 0>>,
                        pair<integral_constant<llu, (a).size()>,
                             integral_constant<decay_t<decltype((a)[0])>,
                                               (a).size() ? (a)[0] : 0>>>);
static_assert(not is_same_v<pair<integral_constant<llu, (a0).size()>,
                                 integral_constant<decay_t<decltype((a0)[0])>,
                                                   (a0).size() ? (a0)[0] : 0>>,
                            pair<integral_constant<llu, (a).size()>,
                                 integral_constant<decay_t<decltype((a)[0])>,
                                                   (a).size() ? (a)[0] : 0>>>);
static_assert(is_same_v<pair<integral_constant<llu, (a0).size()>,
                             integral_constant<decay_t<decltype((a0)[0])>,
                                               (a0).size() ? (a0)[0] : 0>>,
                        pair<integral_constant<llu, (a0).size()>,
                             integral_constant<decay_t<decltype((a0)[0])>,
                                               (a0).size() ? (a0)[0] : 0>>>);
static_assert(is_same_v<pair<integral_constant<llu, (a1).size()>,
                             integral_constant<decay_t<decltype((a1)[0])>,
                                               (a1).size() ? (a1)[0] : 0>>,
                        pair<integral_constant<llu, (a1).size()>,
                             integral_constant<decay_t<decltype((a1)[0])>,
                                               (a1).size() ? (a1)[0] : 0>>>);
static_assert(
    not is_same_v<pair<integral_constant<llu, (a1).size()>,
                       integral_constant<decay_t<decltype((a1)[0])>,
                                         (a1).size() ? (a1)[0] : 0>>,
                  pair<integral_constant<llu, (a0).size()>,
                       integral_constant<decay_t<decltype((a0)[0])>,
                                         (a0).size() ? (a0)[0] : 0>>>);
static_assert(is_same_v<pair<integral_constant<llu, (a).size()>,
                             integral_constant<decay_t<decltype((a)[0])>,
                                               (a).size() ? (a)[0] : 0>>,
                        pair<integral_constant<llu, (_a).size()>,
                             integral_constant<decay_t<decltype((_a)[0])>,
                                               (_a).size() ? (_a)[0] : 0>>>);
static_assert(
    is_same_v<
        pair<pair<integral_constant<
                      llu, ((span<decay_t<decltype((a00))>::element_type,
                                  decay_t<decltype((a00))>::extent / 2>(
                                ((a00)).data(), ((a00)).size() / 2)))
                               .size()>,
                  integral_constant<
                      decay_t<decltype((
                          (span<decay_t<decltype((a00))>::element_type,
                                decay_t<decltype((a00))>::extent / 2>(
                              ((a00)).data(), ((a00)).size() / 2)))[0])>,
                      ((span<decay_t<decltype((a00))>::element_type,
                             decay_t<decltype((a00))>::extent / 2>(
                           ((a00)).data(), ((a00)).size() / 2)))
                              .size()
                          ? ((span<decay_t<decltype((a00))>::element_type,
                                   decay_t<decltype((a00))>::extent / 2>(
                                ((a00)).data(), ((a00)).size() / 2)))[0]
                          : 0>>,
             pair<integral_constant<
                      llu, ((span<decay_t<decltype((a00))>::element_type,
                                  decay_t<decltype((a00))>::extent -
                                      decay_t<decltype((a00))>::extent / 2>(
                                ((a00)).data() + ((a00)).size() / 2,
                                ((a00)).size() - ((a00)).size() / 2)))
                               .size()>,
                  integral_constant<
                      decay_t<decltype((
                          (span<decay_t<decltype((a00))>::element_type,
                                decay_t<decltype((a00))>::extent -
                                    decay_t<decltype((a00))>::extent / 2>(
                              ((a00)).data() + ((a00)).size() / 2,
                              ((a00)).size() - ((a00)).size() / 2)))[0])>,
                      ((span<decay_t<decltype((a00))>::element_type,
                             decay_t<decltype((a00))>::extent -
                                 decay_t<decltype((a00))>::extent / 2>(
                           ((a00)).data() + ((a00)).size() / 2,
                           ((a00)).size() - ((a00)).size() / 2)))
                              .size()
                          ? ((span<decay_t<decltype((a00))>::element_type,
                                   decay_t<decltype((a00))>::extent -
                                       decay_t<decltype((a00))>::extent / 2>(
                                ((a00)).data() + ((a00)).size() / 2,
                                ((a00)).size() - ((a00)).size() / 2)))[0]
                          : 0>>>,
        pair<integral_constant<llu, (a00).size()>,
             integral_constant<decay_t<decltype((a00)[0])>,
                               (a00).size() ? (a00)[0] : 0>>>);

int main() {}
