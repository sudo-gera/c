auto flag(int);     // E1


template<bool B> requires (!B)
struct setter {
    friend auto flag(int) {}        // E2

    static constexpr bool b = B;
};


// E3
template<bool FlagVal>
[[nodiscard]]
consteval auto nonconstant_constant_impl() {
    if constexpr (FlagVal) {
        return true;
    }
    else {
        // E3.1
        setter<FlagVal> s;
        return s.b;
    }
}


// E4
template<
    auto Arg = 0,
    bool FlagVal = requires { flag(Arg); },             // E4.1
    auto Val = nonconstant_constant_impl<FlagVal>()     // E4.2
>
constexpr auto nonconstant_constant = Val;

constexpr bool a = nonconstant_constant<>;      // First evaluation in this translation unit
constexpr bool b = nonconstant_constant<>;
// This assertion passes.
static_assert(a != b);
