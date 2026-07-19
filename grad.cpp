#include <iostream>
#include <string_view>
#include <memory>
#include <unordered_set>
#include <cassert>
#include <vector>
#include <tuple>
#include <cstring>

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

template <typename ParsingContext>
struct IParser;

template <typename ParsingContext>
using Parser = std::shared_ptr<const IParser<ParsingContext>>;

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;             // Deletes copy ctor
    NonCopyable& operator=(const NonCopyable&) = delete;  // Deletes copy assignment
    NonCopyable(NonCopyable&&) = default;                 // Keeps move ctor
    NonCopyable& operator=(NonCopyable&&) = default;      // Keeps move assignment
};

template <typename Arg>
struct ParsingContextContents {
    const char* begin;
    const char* end = nullptr;
    std::vector<Arg> args = {};
};

template <typename Arg_>
struct ParsingContext : ParsingContextContents<Arg_> {
    using Arg = Arg_;

    template <typename... Args>
    ParsingContext(Args&&... args) : ParsingContextContents<Arg_>{std::forward<Args>(args)...} {
    }

    template <typename Backend, typename... Args>
    static Parser<ParsingContext> make_parser(Args&&... args) {
        return Parser<ParsingContext>{std::make_shared<Backend>((ParsingContext*)nullptr, std::forward<Args>(args)...)};
    }

    template <template <typename...> class Backend, typename... Args>
    static auto make_parser(Args&&... args) {
        return Parser<ParsingContext>(
            std::make_shared<decltype(Backend((ParsingContext*)nullptr, std::forward<Args>(args)...))>(
                (ParsingContext*)nullptr, std::forward<Args>(args)...));
    }
};

template <typename ParsingContext>
struct IParser {
    virtual ~IParser() = default;

    virtual bool parse_impl(ParsingContext& ctx) const = 0;

    bool parse_whole(ParsingContext ctx) const {
        if (ctx.end == nullptr) {
            ctx.end = ctx.begin + strlen(ctx.begin);
        }
        return parse(ctx) and ctx.begin == ctx.end;
    }

    bool parse(ParsingContext& ctx) const {
        if (ctx.end == nullptr) {
            ctx.end = ctx.begin + strlen(ctx.begin);
        }
        const char* begin_backup = ctx.begin;
        size_t args_backup = ctx.args.size();
        if (parse_impl(ctx)) {
            return true;
        }
        ctx.begin = begin_backup;
        ctx.args.resize(args_backup);
        return false;
    }
};

template <typename ParsingContext>
Parser<ParsingContext> operator+(const Parser<ParsingContext>& left, const Parser<ParsingContext>& right);
template <typename ParsingContext>
Parser<ParsingContext> operator|(const Parser<ParsingContext>& left, const Parser<ParsingContext>& right);
template <typename ParsingContext>
Parser<ParsingContext> operator~(const Parser<ParsingContext>& item);

////////////////////////////////////////////////////////////////////////////

struct EpsilonParserContents {};

template <typename ParsingContext>
struct EpsilonParser : EpsilonParserContents, IParser<ParsingContext> {

    template <typename... Args>
    EpsilonParser(ParsingContext*, Args&&... args) : EpsilonParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext&) const {
        return true;
    }
};

template <typename F, typename ParsingContext>
struct TestSignedCharFuncParserContents {
    F f;
};

template <typename F, typename ParsingContext>
struct TestSignedCharFuncParser : TestSignedCharFuncParserContents<F, ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    TestSignedCharFuncParser(ParsingContext*, Args&&... args)
        : TestSignedCharFuncParserContents<F, ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return ctx.begin != ctx.end and this->f(ctx.begin[0]) and ctx.begin++;
    }
};

template <typename F, typename ParsingContext>
TestSignedCharFuncParser(ParsingContext*, F) -> TestSignedCharFuncParser<F, ParsingContext>;

template <typename F, typename ParsingContext>
struct TestUnsignedCharFuncParserContents {
    F f;
};

template <typename F, typename ParsingContext>
struct TestUnsignedCharFuncParser : TestUnsignedCharFuncParserContents<F, ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    TestUnsignedCharFuncParser(ParsingContext*, Args&&... args)
        : TestUnsignedCharFuncParserContents<F, ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return ctx.begin != ctx.end and this->f((unsigned char)(ctx.begin[0])) and ctx.begin++;
    }
};

template <typename F, typename ParsingContext>
TestUnsignedCharFuncParser(ParsingContext*, F) -> TestUnsignedCharFuncParser<F, ParsingContext>;

struct CharParserContents {
    char item;
};

template <typename ParsingContext>
struct CharParser : CharParserContents, IParser<ParsingContext> {

    template <typename... Args>
    CharParser(ParsingContext*, Args&&... args) : CharParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return ctx.begin != ctx.end and this->item == ctx.begin[0] and ctx.begin++;
    }
};

struct CharRangeParserContents {
    char lowest, highest;
};

template <typename ParsingContext>
struct CharRangeParser : CharRangeParserContents, IParser<ParsingContext> {

    template <typename... Args>
    CharRangeParser(ParsingContext*, Args&&... args) : CharRangeParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return ctx.begin != ctx.end and this->lowest <= ctx.begin[0] and ctx.begin[0] <= this->highest and ctx.begin++;
    }
};

////////////////////////////////////////////////////////////////////////////

template <typename ParsingContext>
struct ConcatParserContents {
    Parser<ParsingContext> left, right;
};

template <typename ParsingContext>
struct ConcatParser : ConcatParserContents<ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    ConcatParser(ParsingContext*, Args&&... args) : ConcatParserContents<ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return this->left->parse(ctx) && this->right->parse(ctx);
    }
};

template <typename ParsingContext>
struct AlternativesParserContents {
    Parser<ParsingContext> left, right;
};

template <typename ParsingContext>
struct AlternativesParser : AlternativesParserContents<ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    AlternativesParser(ParsingContext*, Args&&... args)
        : AlternativesParserContents<ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return this->left->parse(ctx) || this->right->parse(ctx);
    }
};

template <typename ParsingContext>
struct StarParserContents {
    Parser<ParsingContext> item;
};

template <typename ParsingContext>
struct StarParser : StarParserContents<ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    StarParser(ParsingContext*, Args&&... args) : StarParserContents<ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        while (this->item->parse(ctx))
            ;
        return true;
    }
};

template <typename C, typename ParsingContext>
struct CallbackParserContents {
    Parser<ParsingContext> item;
    C callback;
};

template <typename C, typename ParsingContext>
    requires(std::invocable<C, typename ParsingContext::Arg*, typename ParsingContext::Arg*, const char*, const char*>)
struct CallbackParser : CallbackParserContents<C, ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    CallbackParser(ParsingContext*, Args&&... args)
        : CallbackParserContents<C, ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        size_t args_backup = ctx.args.size();
        const char* begin_backup = ctx.begin;
        if (this->item->parse(ctx)) {
            typename ParsingContext::Arg res = this->callback(
                ctx.args.data() + args_backup, ctx.args.data() + ctx.args.size(), begin_backup, ctx.begin);
            ctx.args.resize(args_backup);
            ctx.args.push_back(std::move(res));
            return true;
        }
        return false;
    }
};

template <typename C, typename P, typename ParsingContext>
CallbackParser(ParsingContext*, P, C) -> CallbackParser<C, ParsingContext>;

template <typename F, typename ParsingContext>
struct ReturnedParserContents {
    F f;
};

template <typename F, typename ParsingContext>
struct ReturnedParser : ReturnedParserContents<F, ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    ReturnedParser(ParsingContext*, Args&&... args)
        : ReturnedParserContents<F, ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return this->f()->parse(ctx);
    }
};

template <typename F, typename ParsingContext>
ReturnedParser(ParsingContext*, F) -> ReturnedParser<F, ParsingContext>;

////////////////////////////////////////////////////////////////////////////

template <typename ParsingContext>
Parser<ParsingContext> operator+(const Parser<ParsingContext>& left, const Parser<ParsingContext>& right) {
    return ParsingContext::template make_parser<ConcatParser>(left, right);
}

template <typename ParsingContext>
Parser<ParsingContext> operator|(const Parser<ParsingContext>& left, const Parser<ParsingContext>& right) {
    return ParsingContext::template make_parser<AlternativesParser>(left, right);
}

template <typename ParsingContext>
Parser<ParsingContext> operator~(const Parser<ParsingContext>& item) {
    return ParsingContext::template make_parser<StarParser>(item);
}

template <typename ParsingContext, typename F>
Parser<ParsingContext> operator>>(const Parser<ParsingContext>& item, F&& f) {
    return ParsingContext::template make_parser<CallbackParser>(item, std::forward<F>(f));
}
////////////////////////////////////////////////////////////////////////////

using parsing_context_for_expr = ParsingContext<Expr>;

Parser<parsing_context_for_expr> lower_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(islower);
}

Parser<parsing_context_for_expr> upper_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isupper);
}

Parser<parsing_context_for_expr> alpha_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isalpha);
}

Parser<parsing_context_for_expr> digit_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isdigit);
}

Parser<parsing_context_for_expr> alnum_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isalnum);
}

Parser<parsing_context_for_expr> space_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isspace);
}

Parser<parsing_context_for_expr> lpar_parser() {
    return parsing_context_for_expr::make_parser<CharParser>('(');
}

Parser<parsing_context_for_expr> rpar_parser() {
    return parsing_context_for_expr::make_parser<CharParser>(')');
}

Parser<parsing_context_for_expr> plus_parser() {
    return parsing_context_for_expr::make_parser<CharParser>('+');
}

Parser<parsing_context_for_expr> minus_parser() {
    return parsing_context_for_expr::make_parser<CharParser>('-');
}

Parser<parsing_context_for_expr> star_parser() {
    return parsing_context_for_expr::make_parser<CharParser>('*');
}

Parser<parsing_context_for_expr> slash_parser() {
    return parsing_context_for_expr::make_parser<CharParser>('/');
}

Parser<parsing_context_for_expr> spaces_parser() {
    return ~parsing_context_for_expr::make_parser<ReturnedParser>(space_parser);
}

Parser<parsing_context_for_expr> number_parser() {
    return (parsing_context_for_expr::make_parser<ReturnedParser>(digit_parser) +
                ~parsing_context_for_expr::make_parser<ReturnedParser>(digit_parser) >>
            [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                assert(args_begin == args_end);
                char data[1024];
                memset(data, 0, sizeof(data));
                assert(data_begin < data_end);
                assert(size_t(data_end - data_begin) < sizeof(data));
                memcpy(data, data_begin, data_end - data_begin);
                return make_expr<ValExpr>(std::stod(data));
            }) +
           parsing_context_for_expr::make_parser<ReturnedParser>(spaces_parser);
}

Parser<parsing_context_for_expr> identifier_parser() {
    return (parsing_context_for_expr::make_parser<ReturnedParser>(alpha_parser) +
                ~parsing_context_for_expr::make_parser<ReturnedParser>(alnum_parser) >>
            [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                assert(args_begin == args_end);
                assert(data_begin < data_end);
                return make_expr<VarExpr>(std::string_view{data_begin, size_t(data_end - data_begin)});
            }) +
           parsing_context_for_expr::make_parser<ReturnedParser>(spaces_parser);
}

////////////////////////////////////////////////////////////////////////////

int main() {
    std::cout << (make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss"))->partial_derivative("aaa") << std::endl;
    std::cout << (make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss"))->partial_derivative("sss") << std::endl;

    std::cout << identifier_parser()->parse_whole(ParsingContext<Expr>("a123")) << std::endl;
    std::cout << number_parser()->parse_whole(ParsingContext<Expr>("123")) << std::endl;
}
