#include <bits/stdc++.h>
using namespace std;
using llu=long long unsigned;

// #define repeater_0(to_r,sep,x) to_r(x)
// #define repeater_1(to_r,sep,x) repeater_0(to_r,sep,x##0) sep repeater_0(to_r,sep,x##1)
// #define repeater_2(to_r,sep,x) repeater_1(to_r,sep,x##0) sep repeater_1(to_r,sep,x##1)
// #define repeater_3(to_r,sep,x) repeater_2(to_r,sep,x##0) sep repeater_2(to_r,sep,x##1)
// #define repeater_4(to_r,sep,x) repeater_3(to_r,sep,x##0) sep repeater_3(to_r,sep,x##1)
// #define repeater_5(to_r,sep,x) repeater_4(to_r,sep,x##0) sep repeater_4(to_r,sep,x##1)
// #define repeater_6(to_r,sep,x) repeater_5(to_r,sep,x##0) sep repeater_5(to_r,sep,x##1)
// #define repeater_7(to_r,sep,x) repeater_6(to_r,sep,x##0) sep repeater_6(to_r,sep,x##1)
// #define repeater_8(to_r,sep,x) repeater_7(to_r,sep,x##0) sep repeater_7(to_r,sep,x##1)
// #define repeater_9(to_r,sep,x) repeater_8(to_r,sep,x##0) sep repeater_8(to_r,sep,x##1)
// #define repeat(to_r,sep,num) repeater_##num(to_r,sep,0b0)

// template<llu...n>
// struct range_h{
//     constexpr static auto len=sizeof...(n);
//     constexpr static auto tuple=make_tuple(n...);
//     range_h(){}
//     range_h(tuple<int){}
// };

// template<llu...n>
// auto range_f(range_h<n...>){
//     return range_h
// }

template<auto val>
struct int_const:integral_constant<remove_reference_t<decltype(val)>,val>{};

template<llu n>
struct range_c{
    static constexpr auto value=tuple_cat(range_c<n-1>::value,make_tuple(int_const<n-1>()));
};

template<>
struct range_c<0>{
    static constexpr auto value=tuple<>();
};

template<typename...ind>
static auto get_values(auto&&val, tuple<ind...>)->tuple<int_const<(val)[ind::value]>...>;


#define atot(val) \
    pair< \
        decltype(val), \
        decltype(get_values(val,range_c<(val).size()>::value)) \
    > \


// #define atot_0(val)\
//     pair<\
//         integral_constant<llu,(val).size()>,\
//         integral_constant<\
//             decay_t<decltype((val)[0])>,\
//             (val).size()?(val)[0]:0\
//         >\
//     >

// #define atot_dup(val,next)\
//     pair<\
//         next((\
//             span<\
//                 decay_t<decltype(val)>::element_type,\
//                 decay_t<decltype(val)>::extent/2\
//             >(\
//                 (val).data(),\
//                 (val).size()/2\
//             )\
//         )),\
//         next((\
//             span<\
//                 decay_t<decltype(val)>::element_type,\
//                 decay_t<decltype(val)>::extent-decay_t<decltype(val)>::extent/2\
//             >(\
//                 (val).data()+(val).size()/2,\
//                 (val).size()-(val).size()/2\
//             )\
//         ))\
//     >

// #define atot_1(val) atot_dup((val),atot_0)

constexpr auto _a =array<int,0>();
constexpr auto _a0=array<int,1>({0});
constexpr auto _a1=array<int,1>({1});
constexpr auto _b =array<int,0>();
constexpr auto _b0=array<int,1>({0});
constexpr auto _b1=array<int,1>({1});
constexpr auto a =span(_a );
constexpr auto a0=span(_a0);
constexpr auto a1=span(_a1);
constexpr auto b =span(_b );
constexpr auto b0=span(_b0);
constexpr auto b1=span(_b1);
constexpr auto _a00=array<int,2>({0,0});
constexpr auto _a10=array<int,2>({1,0});
constexpr auto _a01=array<int,2>({0,1});
constexpr auto _a11=array<int,2>({1,1});
constexpr auto a00=span<const int,2>(_a00);
constexpr auto a10=span<const int,2>(_a10);
constexpr auto a01=span<const int,2>(_a01);
constexpr auto a11=span<const int,2>(_a11);

#define atot_0 atot
#define atot_1 atot

static_assert(    is_same_v<atot_0(a ),atot_0(a )>);
static_assert(not is_same_v<atot_0(a0),atot_0(a )>);
static_assert(    is_same_v<atot_0(a0),atot_0(a0)>);
static_assert(    is_same_v<atot_0(a1),atot_0(a1)>);
static_assert(not is_same_v<atot_0(a1),atot_0(a0)>);
static_assert(    is_same_v<atot_0(a ),atot_0(_a)>);
static_assert(    is_same_v<atot_1(a00),atot_1(a00)>);
static_assert(not is_same_v<atot_1(a00),atot_1(a01)>);
static_assert(not is_same_v<atot_1(a10),atot_1(a00)>);
static_assert(not is_same_v<atot_1(a10),atot_1(a11)>);
static_assert(not is_same_v<atot_1(a11),atot_1(a01)>);
static_assert(    is_same_v<atot_1(a11),atot_1(a11)>);



int main(){}






