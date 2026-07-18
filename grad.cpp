#include <iostream>
#include <string_view>
#include <memory>
#include <unordered_set>

struct IExprWrapper;
using Expr = std::shared_ptr<const IExprWrapper>;

struct IExprWrapper {
    virtual ~IExprWrapper() = default;

    virtual void print(std::ostream& out) const = 0;
    virtual size_t strength() const = 0;
    virtual Expr partial_derivative(const std::string_view& name) const = 0;
    virtual void get_all_names(std::unordered_set<std::string_view>& names) const = 0;
};

template<typename Wrapped>
struct ExprWrapper : IExprWrapper {
    const Wrapped wrapped;

    template<typename...Args>
    requires std::is_constructible_v<Wrapped, Args...>
    ExprWrapper(Args&&...args):
        wrapped(std::forward<Args>(args)...)
    {}

    template<typename...Args>
    requires (
        ! std::is_constructible_v<Wrapped, Args...>
        && requires(Args&&...args) {
            (wrapped{std::forward<Args>(args)...});
        }
    )
    ExprWrapper(Args&&...args):
        wrapped{std::forward<Args>(args)...}
    {}

    template<typename...Args>
    requires (
        ! std::is_constructible_v<Wrapped, Args...>
        && requires(Args&&...args) {
            (wrapped{{std::forward<Args>(args)...}};
        }
    )
    ExprWrapper(Args&&...args):
        wrapped{std::forward<Args>(args)...}
    {}

    void print(std::ostream& out) const override {
        return wrapped.print(out);
    }

    size_t strength() const override {
        return wrapped.strength();
    }

    Expr partial_derivative(const std::string_view& name) const override {
        return wrapped.partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const override {
        return wrapped.get_all_names(names);
    }
};

template<typename Backend, typename...Args>
Expr make_expr(Args&&...args) {
    return Expr{
        std::make_shared<
            ExprWrapper<
                Backend
            >
        >(std::forward<Args>(args)...)
    };
}

std::ostream& operator<<(std::ostream& out, const Expr& mid) {
    mid->print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////

Expr operator+(const Expr& left, const Expr& right);
Expr operator-(const Expr& left, const Expr& right);
Expr operator*(const Expr& left, const Expr& right);
Expr operator/(const Expr& left, const Expr& right);

////////////////////////////////////////////////////////////////////////////

enum expr_operator_levels: size_t {
    add_sub = 1111,
    mul_div = 2222,
    constant = 9999,
    variable = 7777,
};

struct ValExpr {
    double val;

    void print(std::ostream& out) const {
        out << val;
    }

    size_t strength() const {
        return expr_operator_levels::constant;
    }

    Expr partial_derivative(const std::string_view&) const {
        return make_expr<ValExpr>(0.0);
    }

    void get_all_names(std::unordered_set<std::string_view>&) const {}
};

struct VarExpr {
    std::string_view name_;

    void print(std::ostream& out) const {
        out << name_;
    }

    size_t strength() const {
        return expr_operator_levels::variable;
    }

    Expr partial_derivative(const std::string_view& name) const {
        if (name == name_) {
            return make_expr<ValExpr>(1.0);
        } else {
            return make_expr<ValExpr>(0.0);
        }
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        names.insert(name_);
    }
};

struct SumExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first->strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " + ";
        if (second->strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return expr_operator_levels::add_sub;
    }

    Expr partial_derivative(const std::string_view& name) const {
        return first->partial_derivative(name) + second->partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first->get_all_names(names);
        second->get_all_names(names);
    }
};

struct DifferenceExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first->strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " - ";
        if (second->strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return expr_operator_levels::add_sub;
    }

    Expr partial_derivative(const std::string_view& name) const {
        return first->partial_derivative(name) - second->partial_derivative(name);
    }


    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first->get_all_names(names);
        second->get_all_names(names);
    }
};

struct ProductExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first->strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " * ";
        if (second->strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return expr_operator_levels::mul_div;
    }

    Expr partial_derivative(const std::string_view& name) const {
        return first->partial_derivative(name) * second + first * second->partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first->get_all_names(names);
        second->get_all_names(names);
    }
};

struct QuotientExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first->strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " / ";
        if (second->strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return expr_operator_levels::mul_div;
    }

    Expr partial_derivative(const std::string_view& name) const {
        return (
            first->partial_derivative(name) * second - first * second->partial_derivative(name)
        ) / second / second;
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first->get_all_names(names);
        second->get_all_names(names);
    }
};

////////////////////////////////////////////////////////////////////////////

Expr operator+(const Expr& left, const Expr& right) {
    return make_expr<SumExpr>(left, right);
}

Expr operator-(const Expr& left, const Expr& right) {
    return make_expr<DifferenceExpr>(left, right);
}

Expr operator*(const Expr& left, const Expr& right) {
    return make_expr<ProductExpr>(left, right);
}

Expr operator/(const Expr& left, const Expr& right) {
    return make_expr<QuotientExpr>(left, right);
}

////////////////////////////////////////////////////////////////////////////

template<typename Parser>
struct IParserWrapper {
    virtual ~IParserWrapper() = default;
    virtual bool parse_impl(const char*& begin, const char* end) = 0;
};

struct Parser {
    std::shared_ptr<IParserWrapper<Parser>> wrapped;

    bool parse_test(const char* begin, const char* end) {
        return parse(begin, end) and begin == end;
    }

    bool parse(const char*& begin, const char* end) {
        const char* begin_backup = begin;
        if (parse_impl(begin, end)) {
            return true;
        }
        begin = begin_backup;
        return false;
    }

    bool parse_impl(const char*& begin, const char* end) {
        return wrapped->parse_impl(begin, end);
    }
};

template<typename Wrapped>
struct ParserWrapper: IParserWrapper<Parser> {
    Wrapped wrapped;

    template<typename...Args>
    requires std::is_constructible_v<Wrapped, Args...>
    ParserWrapper(Args&&...args):
        wrapped(std::forward<Args>(args)...)
    {}

    template<typename...Args>
    requires (
        ! std::is_constructible_v<Wrapped, Args...>
        && std::is_aggregate_v<Wrapped>
    )
    ParserWrapper(Args&&...args):
        wrapped{std::forward<Args>(args)...}
    {}

    bool parse_impl(const char*& begin, const char* end) override {
        return wrapped.parse_impl(begin, end);
    }
};

template<typename Backend, typename...Args>
Parser make_parser(Args&&...args) {
    return Parser{
        std::make_shared<
            ParserWrapper<
                Backend
            >
        >(std::forward<Args>(args)...)
    };
}

template<template <typename...> class Backend, typename...Args>
auto make_parser(Args&&...args)
requires(
    requires(Args&&...args){
        (Backend(
            std::forward<Args>(args)...
        ));
    }
)
{
    return Parser{
        std::make_shared<
            ParserWrapper<
                decltype(
                    Backend(
                        std::forward<Args>(args)...
                    )
                )
            >
        >(std::forward<Args>(args)...)
    };
}

template<template <typename...> class Backend, typename...Args>
auto make_parser(Args&&...args)
requires(
    requires(Args&&...args){
        (Backend{
            std::forward<Args>(args)...
        });
    }
)
{
    return Parser{
        std::make_shared<
            ParserWrapper<
                decltype(
                    Backend{
                        std::forward<Args>(args)...
                    }
                )
            >
        >(std::forward<Args>(args)...)
    };
}

////////////////////////////////////////////////////////////////////////////

Parser operator&(const Parser& left, const Parser& right);
Parser operator|(const Parser& left, const Parser& right);
Parser operator~(const Parser& mid);

struct EpsilonParser {

    bool parse_impl(const char*&, const char*) {
        return true;
    }
};

template<typename F>
struct TestSignedCharFuncParser {
    F f;

    bool parse_impl(const char*& begin, const char* end) {
        return begin != end and f(begin[0]) and begin++;
    }
};

template <typename F>
TestSignedCharFuncParser(F) -> TestSignedCharFuncParser<F>;

template<typename F>
struct TestUnsignedCharFuncParser {
    F f;

    bool parse_impl(const char*& begin, const char* end) {
        return begin != end and f((unsigned char)(begin[0])) and begin++;
    }
};

template <typename F>
TestUnsignedCharFuncParser(F) -> TestUnsignedCharFuncParser<F>;

struct CharRangeParser {
    char lowest, highest;

    bool parse_impl(const char*& begin, const char* end) {
        return begin != end and lowest <= begin[0] and begin[0] <= highest and begin++;
    }
};

struct ConcatParser {
    Parser left, right;

    bool parse_impl(const char*& begin, const char* end) {
        return left.parse(begin, end) && right.parse(begin, end);
    }
};

struct AlternativeParser {
    Parser left, right;

    bool parse_impl(const char*& begin, const char* end) {
        return left.parse(begin, end) || right.parse(begin, end);
    }
};

struct StarParser {
    Parser mid;

    bool parse_impl(const char*& begin, const char* end) {
        while (mid.parse(begin, end));
        return true;
    }
};

////////////////////////////////////////////////////////////////////////////

Parser operator&(const Parser& left, const Parser& right) {
    return make_parser<ConcatParser>(left, right);
}

Parser operator|(const Parser& left, const Parser& right) {
    return make_parser<AlternativeParser>(left, right);
}

Parser operator~(const Parser& mid) {
    return make_parser<StarParser>(mid);
}

////////////////////////////////////////////////////////////////////////////

int main(){
    std::cout << (
        make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss")
    )->partial_derivative("aaa") << std::endl;
    std::cout << (
        make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss")
    )->partial_derivative("sss") << std::endl;


    Parser lower_parser = make_parser<CharRangeParser>('a', 'z');
    Parser upper_parser = make_parser<CharRangeParser>('A', 'Z');
    Parser alpha_parser = lower_parser | upper_parser;
    Parser digit_parser = make_parser<CharRangeParser>('0', '9');
    Parser alnum_parser = alpha_parser | digit_parser;
    Parser identifier_parser = alpha_parser & ~alnum_parser;
    auto data = "Hello123";
    std::cout << identifier_parser.parse_test(data, data+strlen(data)) << std::endl;
}


