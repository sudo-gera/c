#include <type_traits>
#include <iostream>
#include <tuple>

template<typename type_2_search, typename ...all_types> class type_search;

template<typename type_2_search,
     typename type_2_compare,
     typename ...all_types> class type_compare
    : public type_search<type_2_search, all_types...>
{
};

template<typename type_2_search,
     typename ...all_types>
class type_compare<type_2_search, type_2_search, all_types...>
    : public std::true_type {};

template<typename type_2_search>
class type_search<type_2_search> : public std::false_type {};

template<typename type_2_search, typename first_type, typename ...all_types>
class type_search<type_2_search, first_type, all_types...> :
    public type_compare<type_2_search, first_type, all_types...>
{
};

// add_2_bag_if_type_in_tuple adds the type to tuple_bag
//
// The third template parameter is a tuple_bag
//
// If the 2nd template parameter is true, add the first parameter to the
// bag of types, otherwise the bag of types is unchanged.

template<typename type, bool value, typename tuple_bag>
class add_2_bag_if_type_in_tuple;

template<typename type, typename tuple_bag>
class add_2_bag_if_type_in_tuple<type, false, tuple_bag> {
 public:

    typedef tuple_bag type_t;
};

template<typename type, typename ...types>
class add_2_bag_if_type_in_tuple<type, true, std::tuple<types...>> {
 public:

    typedef std::tuple<type, types...> type_t;
};

/////////


template<typename tuple1_types,
     typename tuple2_types> class compute_intersection;

template<typename ...tuple2_types>
class compute_intersection<std::tuple<>,
               std::tuple<tuple2_types...>> {
public:

    typedef std::tuple<> type_t;
};

template<typename tuple1_type,
     typename ...tuple1_types, typename ...tuple2_types>
class compute_intersection<std::tuple<tuple1_type, tuple1_types...>,
               std::tuple<tuple2_types...>> {
public:

    typedef typename compute_intersection<std::tuple<tuple1_types...>,
                          std::tuple<tuple2_types...>>
        ::type_t previous_bag_t;

    typedef typename add_2_bag_if_type_in_tuple<
        tuple1_type,
        type_search<tuple1_type, tuple2_types...>::value,
        previous_bag_t>::type_t type_t;
};

int main()
{
    // Test case: no intersection

    typedef compute_intersection<std::tuple<int>, std::tuple<char>>::type_t
        one_type;

    std::tuple<> one=one_type();

    // Test case: one of the types intersect

    typedef compute_intersection<std::tuple<int, char>,
                     std::tuple<char, double>>::type_t
        two_type;

    std::tuple<char> two = two_type();

    // Test case, two types intersect, but in different order:

    typedef compute_intersection<std::tuple<int, char, int *>,
                     std::tuple<int *, char, double>>::type_t
        three_type;

    std::tuple<char, int *> three = three_type();
}
