#include <iostream>
#include <string_view>
#include <memory>
#include <unordered_set>

struct IExpr;
using Expr = std::shared_ptr<const IExpr>;

struct IExpr {
    virtual ~IExpr() = default;

    virtual void print(std::ostream& out) const = 0;
    virtual size_t strength() const = 0;
    virtual Expr partial_derivative(const std::string_view& name) const = 0;
    virtual void get_all_names(std::unordered_set<std::string_view>& names) const = 0;
};

template <typename Backend, typename... Args>
Expr make_expr(Args&&... args) {
    return Expr{std::make_shared<Backend>(std::forward<Args>(args)...)};
}

////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& out, const Expr& item) {
    item->print(out);
    return out;
}

Expr operator+(const Expr& left, const Expr& right);
Expr operator-(const Expr& left, const Expr& right);
Expr operator*(const Expr& left, const Expr& right);
Expr operator/(const Expr& left, const Expr& right);

enum expr_operator_levels : size_t {
    add_sub = 1111,
    mul_div = 2222,
    constant = 9999,
    variable = 7777,
};

////////////////////////////////////////////////////////////////////////////

struct ValExprContents {
    double val;
};

struct ValExpr : ValExprContents, IExpr {

    template <typename... Args>
    ValExpr(Args&&... args) : ValExprContents{std::forward<Args>(args)...} {
    }

    void print(std::ostream& out) const {
        out << val;
    }

    size_t strength() const {
        return expr_operator_levels::constant;
    }

    Expr partial_derivative(const std::string_view&) const {
        return make_expr<ValExpr>(0.0);
    }

    void get_all_names(std::unordered_set<std::string_view>&) const {
    }
};

struct VarExprContents {
    std::string_view name_;
};

struct VarExpr : VarExprContents, IExpr {

    template <typename... Args>
    VarExpr(Args&&... args) : VarExprContents{std::forward<Args>(args)...} {
    }

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

struct SumExprContents {
    Expr first, second;
};

struct SumExpr : SumExprContents, IExpr {

    template <typename... Args>
    SumExpr(Args&&... args) : SumExprContents{std::forward<Args>(args)...} {
    }

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

struct DifferenceExprContents {
    Expr first, second;
};

struct DifferenceExpr : DifferenceExprContents, IExpr {

    template <typename... Args>
    DifferenceExpr(Args&&... args) : DifferenceExprContents{std::forward<Args>(args)...} {
    }

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

struct ProductExprContents {
    Expr first, second;
};

struct ProductExpr : ProductExprContents, IExpr {

    template <typename... Args>
    ProductExpr(Args&&... args) : ProductExprContents{std::forward<Args>(args)...} {
    }

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

struct QuotientExprContents {
    Expr first, second;
};

struct QuotientExpr : QuotientExprContents, IExpr {

    template <typename... Args>
    QuotientExpr(Args&&... args) : QuotientExprContents{std::forward<Args>(args)...} {
    }

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
        return (first->partial_derivative(name) * second - first * second->partial_derivative(name)) / second / second;
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

struct IParser {
    virtual ~IParser() = default;
    virtual bool parse_impl(const char*& begin, const char* end) const = 0;

    bool parse_whole(const char* begin, const char* end = nullptr) const {
        if (end == nullptr) {
            end = begin + strlen(begin);
        }
        return parse(begin, end) and begin == end;
    }

    bool parse(const char*& begin, const char* end = nullptr) const {
        if (end == nullptr) {
            end = begin + strlen(begin);
        }
        const char* begin_backup = begin;
        if (parse_impl(begin, end)) {
            return true;
        }
        begin = begin_backup;
        return false;
    }
};

using Parser = std::shared_ptr<IParser>;

template <typename Backend, typename... Args>
Parser make_parser(Args&&... args) {
    return Parser{std::make_shared<Backend>(std::forward<Args>(args)...)};
}

template <template <typename...> class Backend, typename... Args>
auto make_parser(Args&&... args) {
    return Parser{std::make_shared<decltype(Backend(std::forward<Args>(args)...))>(std::forward<Args>(args)...)};
}

Parser operator+(const Parser& left, const Parser& right);
Parser operator|(const Parser& left, const Parser& right);
Parser operator~(const Parser& item);

////////////////////////////////////////////////////////////////////////////

struct EpsilonParserContents {};

struct EpsilonParser : EpsilonParserContents, IParser {

    template <typename... Args>
    EpsilonParser(Args&&... args) : EpsilonParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*&, const char*) const {
        return true;
    }
};

template <typename F>
struct TestSignedCharFuncParserContents {
    F f;
};

template <typename F>
struct TestSignedCharFuncParser : TestSignedCharFuncParserContents<F>, IParser {

    template <typename... Args>
    TestSignedCharFuncParser(Args&&... args) : TestSignedCharFuncParserContents<F>{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return begin != end and TestSignedCharFuncParserContents<F>::f(begin[0]) and begin++;
    }
};

template <typename F>
TestSignedCharFuncParser(F) -> TestSignedCharFuncParser<F>;

template <typename F>
struct TestUnsignedCharFuncParserContents {
    F f;
};

template <typename F>
struct TestUnsignedCharFuncParser : TestUnsignedCharFuncParserContents<F>, IParser {

    template <typename... Args>
    TestUnsignedCharFuncParser(Args&&... args) : TestUnsignedCharFuncParserContents<F>{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return begin != end and TestUnsignedCharFuncParserContents<F>::f((unsigned char)(begin[0])) and begin++;
    }
};

template <typename F>
TestUnsignedCharFuncParser(F) -> TestUnsignedCharFuncParser<F>;

struct CharParserContents {
    char item;
};

struct CharParser : CharParserContents, IParser {

    template <typename... Args>
    CharParser(Args&&... args) : CharParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return begin != end and item == begin[0] and begin++;
    }
};

struct CharRangeParserContents {
    char lowest, highest;
};

struct CharRangeParser : CharRangeParserContents, IParser {

    template <typename... Args>
    CharRangeParser(Args&&... args) : CharRangeParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return begin != end and lowest <= begin[0] and begin[0] <= highest and begin++;
    }
};

////////////////////////////////////////////////////////////////////////////

struct ConcatParserContents {
    Parser left, right;
};

struct ConcatParser : ConcatParserContents, IParser {

    template <typename... Args>
    ConcatParser(Args&&... args) : ConcatParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return left->parse(begin, end) && right->parse(begin, end);
    }
};

struct AlternativesParserContents {
    Parser left, right;
};

struct AlternativesParser : AlternativesParserContents, IParser {

    template <typename... Args>
    AlternativesParser(Args&&... args) : AlternativesParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return left->parse(begin, end) || right->parse(begin, end);
    }
};

struct StarParserContents {
    Parser item;
};

struct StarParser : StarParserContents, IParser {

    template <typename... Args>
    StarParser(Args&&... args) : StarParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        while (item->parse(begin, end))
            ;
        return true;
    }
};

template<typename C>
struct CallbackParserContents {
    C callback;
};

template<typename C>
struct CallbackParser : CallbackParserContents<C>, IParser {

    template <typename... Args>
    CallbackParser(Args&&... args) : CallbackParserContents<C>{std::forward<Args>(args)...} {
    }

    bool parse_impl(const char*& begin, const char* end) const {
        return item->parse(begin, end);
    }
};

////////////////////////////////////////////////////////////////////////////

Parser operator+(const Parser& left, const Parser& right) {
    return make_parser<ConcatParser>(left, right);
}

Parser operator|(const Parser& left, const Parser& right) {
    return make_parser<AlternativesParser>(left, right);
}

Parser operator~(const Parser& item) {
    return make_parser<StarParser>(item);
}

////////////////////////////////////////////////////////////////////////////

int main() {
    std::cout << (make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss"))->partial_derivative("aaa") << std::endl;
    std::cout << (make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss"))->partial_derivative("sss") << std::endl;

    Parser lower_parser = make_parser<TestUnsignedCharFuncParser>(islower);
    Parser upper_parser = make_parser<TestUnsignedCharFuncParser>(isupper);
    Parser alpha_parser = make_parser<TestUnsignedCharFuncParser>(isalpha);
    Parser digit_parser = make_parser<TestUnsignedCharFuncParser>(isdigit);
    Parser alnum_parser = make_parser<TestUnsignedCharFuncParser>(isalnum);
    Parser space_parser = make_parser<TestUnsignedCharFuncParser>(isspace);
    Parser lpar_parser  = make_parser<CharParser>('(');
    Parser rpar_parser  = make_parser<CharParser>(')');
    Parser plus_parser  = make_parser<CharParser>('+');
    Parser minus_parser = make_parser<CharParser>('-');
    Parser star_parser  = make_parser<CharParser>('*');
    Parser slash_parser = make_parser<CharParser>('/');
    Parser identifier_parser = alpha_parser + ~alnum_parser;
    Parser number_parser = digit_parser + ~digit_parser;
    Parser spaces_parser = ~space_parser;
    auto data = "Hello123";
    std::cout << identifier_parser->parse_whole(data, data + strlen(data)) << std::endl;
}
