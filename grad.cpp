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

template<typename ParserContext>
struct IParser;

template<typename ParserContext>
using Parser = std::shared_ptr<const IParser<ParserContext>>;

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;             // Deletes copy ctor
    NonCopyable& operator=(const NonCopyable&) = delete;  // Deletes copy assignment
    NonCopyable(NonCopyable&&) = default;                 // Keeps move ctor
    NonCopyable& operator=(NonCopyable&&) = default;      // Keeps move assignment
};

template <typename Arg>
struct ParserContextContents {
    const char* begin_;
    const char* end_ = nullptr;
    std::vector<Arg> args = {};
};

struct IParserContext : NonCopyable {
    virtual ~IParserContext() = default;
    virtual const char*&begin() = 0;
    virtual const char*& end() = 0;
    virtual size_t args_size() = 0;
    virtual void args_resize(size_t size) = 0;
    virtual void process_callback(void(*callback)(void*, size_t), size_t args_backup) = 0;
};

template <typename Arg>
struct ParserContext : ParserContextContents<Arg>, IParserContext {

    template <typename... Args>
    ParserContext(Args&&... args) : ParserContextContents<Arg>{std::forward<Args>(args)...} {
    }

    const char*& begin() {
        return this->begin_;
    }

    const char*& end() {
        return this->end_;
    }

    size_t args_size() {
        return this->args.size();
    }

    void args_resize(size_t size) {
        return this->args.resize(size);
    }

    void process_callback(void(*callback)(void*, size_t), size_t args_backup) {
        callback(this->args.data() + args_backup, this->args.size() - args_backup);
    }

    template <typename Backend, typename... Args>
    static Parser<ParserContext> make_parser(Args&&... args) {
        return Parser<ParserContext>{
            std::make_shared<Backend>(
                (ParserContext*)nullptr,
                std::forward<Args>(args)...
            )
        };
    }

    template <template <typename...> class Backend, typename... Args>
    static auto make_parser(Args&&... args) {
        return Parser<ParserContext>(
            std::make_shared<
                decltype(
                    Backend(
                        (ParserContext*)nullptr,
                        std::forward<Args>(args)...
                    )
                )
            >(
                (ParserContext*)nullptr,
                std::forward<Args>(args)...
            )
        );
    }
};

template<typename ParserContext>
struct IParser {
    virtual ~IParser() = default;

    virtual bool parse_impl(IParserContext& ctx) const = 0;

    bool parse_whole(IParserContext& ctx) const {
        if (ctx.end() == nullptr) {
            ctx.end() = ctx.begin() + strlen(ctx.begin());
        }
        return parse(ctx) and ctx.begin() == ctx.end();
    }

    bool parse(IParserContext& ctx) const {
        if (ctx.end() == nullptr) {
            ctx.end() = ctx.begin() + strlen(ctx.begin());
        }
        const char* begin_backup = ctx.begin();
        size_t args_backup = ctx.args_size();
        if (parse_impl(ctx)) {
            return true;
        }
        ctx.begin() = begin_backup;
        ctx.args_resize(args_backup);
        return false;
    }
};

template<typename ParserContext>
Parser<ParserContext> operator+(const Parser<ParserContext>& left, const Parser<ParserContext>& right);
template<typename ParserContext>
Parser<ParserContext> operator|(const Parser<ParserContext>& left, const Parser<ParserContext>& right);
template<typename ParserContext>
Parser<ParserContext> operator~(const Parser<ParserContext>& item);

////////////////////////////////////////////////////////////////////////////

struct EpsilonParserContents {};

template<typename ParserContext>
struct EpsilonParser : EpsilonParserContents, IParser<ParserContext> {

    template <typename... Args>
    EpsilonParser(ParserContext*, Args&&... args) : EpsilonParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext&) const {
        return true;
    }
};

template <typename F, typename ParserContext>
struct TestSignedCharFuncParserContents {
    F f;
};

template <typename F, typename ParserContext>
struct TestSignedCharFuncParser : TestSignedCharFuncParserContents<F, ParserContext>, IParser<ParserContext> {

    template <typename... Args>
    TestSignedCharFuncParser(ParserContext*, Args&&... args) : TestSignedCharFuncParserContents<F, ParserContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        return ctx.begin() != ctx.end() and this->f(ctx.begin()[0]) and ctx.begin()++;
    }
};

template <typename F, typename ParserContext>
TestSignedCharFuncParser(ParserContext*, F) -> TestSignedCharFuncParser<F, ParserContext>;

template <typename F, typename ParserContext>
struct TestUnsignedCharFuncParserContents {
    F f;
};

template <typename F, typename ParserContext>
struct TestUnsignedCharFuncParser : TestUnsignedCharFuncParserContents<F, ParserContext>, IParser<ParserContext> {

    template <typename... Args>
    TestUnsignedCharFuncParser(ParserContext*, Args&&... args) : TestUnsignedCharFuncParserContents<F, ParserContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        return ctx.begin() != ctx.end() and this->f((unsigned char)(ctx.begin()[0])) and ctx.begin()++;
    }
};

template <typename F, typename ParserContext>
TestUnsignedCharFuncParser(ParserContext*, F) -> TestUnsignedCharFuncParser<F, ParserContext>;

struct CharParserContents {
    char item;
};

template<typename ParserContext>
struct CharParser : CharParserContents, IParser<ParserContext> {

    template <typename... Args>
    CharParser(ParserContext*, Args&&... args) : CharParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        return ctx.begin() != ctx.end() and this->item == ctx.begin()[0] and ctx.begin()++;
    }
};

struct CharRangeParserContents {
    char lowest, highest;
};

template<typename ParserContext>
struct CharRangeParser : CharRangeParserContents, IParser<ParserContext> {

    template <typename... Args>
    CharRangeParser(ParserContext*, Args&&... args) : CharRangeParserContents{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        return ctx.begin() != ctx.end() and this->lowest <= ctx.begin()[0] and ctx.begin()[0] <= this->highest and ctx.begin()++;
    }
};

////////////////////////////////////////////////////////////////////////////

template<typename ParserContext>
struct ConcatParserContents {
    Parser<ParserContext> left, right;
};

template<typename ParserContext>
struct ConcatParser : ConcatParserContents<ParserContext>, IParser<ParserContext> {

    template <typename... Args>
    ConcatParser(ParserContext*, Args&&... args) : ConcatParserContents<ParserContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        return this->left->parse(ctx) && this->right->parse(ctx);
    }
};

template<typename ParserContext>
struct AlternativesParserContents {
    Parser<ParserContext> left, right;
};

template<typename ParserContext>
struct AlternativesParser : AlternativesParserContents<ParserContext>, IParser<ParserContext> {

    template <typename... Args>
    AlternativesParser(ParserContext*, Args&&... args) : AlternativesParserContents<ParserContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        return this->left->parse(ctx) || this->right->parse(ctx);
    }
};

template<typename ParserContext>
struct StarParserContents {
    Parser<ParserContext> item;
};

template<typename ParserContext>
struct StarParser : StarParserContents<ParserContext>, IParser<ParserContext> {

    template <typename... Args>
    StarParser(ParserContext*, Args&&... args) : StarParserContents<ParserContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        while (this->item->parse(ctx))
            ;
        return true;
    }
};

template <typename C, typename ParserContext>
struct CallbackParserContents {
    Parser<ParserContext> item;
    C callback;
};

template <typename C, typename ParserContext>
struct CallbackParser : CallbackParserContents<C, ParserContext>, IParser<ParserContext> {

    template <typename... Args>
    CallbackParser(ParserContext*, Args&&... args) : CallbackParserContents<C, ParserContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(IParserContext& ctx) const {
        // size_t args_backup = ctx.args_size();
        // if (this->item->parse(ctx)){
        //     ctx.process_callback(
        //         [&](auto& args_vec){
        //             this->callback;
        //         },
        //         args_backup
        //     );
        // }
        return this->item->parse(ctx);
    }
};

////////////////////////////////////////////////////////////////////////////

template<typename ParserContext>
Parser<ParserContext> operator+(const Parser<ParserContext>& left, const Parser<ParserContext>& right) {
    return ParserContext::template make_parser<ConcatParser>(left, right);
}

template<typename ParserContext>
Parser<ParserContext> operator|(const Parser<ParserContext>& left, const Parser<ParserContext>& right) {
    return ParserContext::template make_parser<AlternativesParser>(left, right);
}

template<typename ParserContext>
Parser<ParserContext> operator~(const Parser<ParserContext>& item) {
    return ParserContext::template make_parser<StarParser>(item);
}

////////////////////////////////////////////////////////////////////////////

struct E {};

int main() {
    std::cout << (make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss"))->partial_derivative("aaa") << std::endl;
    std::cout << (make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss"))->partial_derivative("sss") << std::endl;

    auto data = "Hello123";
    ParserContext<E> ctx(data);
    auto lower_parser = decltype(ctx)::make_parser<TestUnsignedCharFuncParser>(islower);
    auto upper_parser = decltype(ctx)::make_parser<TestUnsignedCharFuncParser>(isupper);
    auto alpha_parser = decltype(ctx)::make_parser<TestUnsignedCharFuncParser>(isalpha);
    auto digit_parser = decltype(ctx)::make_parser<TestUnsignedCharFuncParser>(isdigit);
    auto alnum_parser = decltype(ctx)::make_parser<TestUnsignedCharFuncParser>(isalnum);
    auto space_parser = decltype(ctx)::make_parser<TestUnsignedCharFuncParser>(isspace);
    auto lpar_parser  = decltype(ctx)::make_parser<CharParser>('(');
    auto rpar_parser  = decltype(ctx)::make_parser<CharParser>(')');
    auto plus_parser  = decltype(ctx)::make_parser<CharParser>('+');
    auto minus_parser = decltype(ctx)::make_parser<CharParser>('-');
    auto star_parser  = decltype(ctx)::make_parser<CharParser>('*');
    auto slash_parser = decltype(ctx)::make_parser<CharParser>('/');
    auto identifier_parser = alpha_parser + ~alnum_parser;
    auto number_parser = digit_parser + ~digit_parser;
    auto spaces_parser = ~space_parser;
    std::cout << identifier_parser->parse_whole(ctx) << std::endl;
}
