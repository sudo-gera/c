#include <iostream>
#include <string_view>
#include <memory>
#include <unordered_set>
#include <cassert>
#include <vector>
#include <tuple>
#include <cstring>
#include <algorithm>

bool double_equal(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) <= epsilon * std::max(std::fabs(a), std::fabs(b));
}

////////////////////////////////////////////////////////////////////////////

struct IExpr;
using Expr = std::shared_ptr<const IExpr>;

struct IExpr : std::enable_shared_from_this<IExpr>{
    virtual ~IExpr() = default;

    virtual void print(std::ostream& out) const = 0;
    virtual size_t strength() const = 0;
    virtual Expr partial_derivative(const std::string_view& name) const = 0;
    virtual void get_all_names(std::unordered_set<std::string_view>& names) const = 0;
    virtual Expr optimize() const = 0;
    void print_in_pars(std::ostream& out, bool with_pars = false) const {
        if (with_pars) {
            out << "(";
            print(out);
            out << ")";
        }else{
            print(out);
        }
    }
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

Expr operator+(const Expr& item);
Expr operator-(const Expr& item);
Expr operator+(const Expr& left, const Expr& right);
Expr operator-(const Expr& left, const Expr& right);
Expr operator*(const Expr& left, const Expr& right);
Expr operator/(const Expr& left, const Expr& right);

enum expr_operator_levels : size_t {
    unary = 7777,
    add_sub = 1111,
    mul_div = 2222,
    constant = 9999,
    variable = 8888,
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

    Expr optimize() const {
        return shared_from_this();
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

    Expr optimize() const {
        return shared_from_this();
    }
};

struct UnaryPlusExprContents {
    Expr item;
};

struct UnaryPlusExpr : UnaryPlusExprContents, IExpr {

    template <typename... Args>
    UnaryPlusExpr(Args&&... args) : UnaryPlusExprContents{std::forward<Args>(args)...} {
    }

    void print(std::ostream& out) const {
        out << "+";
        item->print_in_pars(out, item->strength() < strength());
    }

    size_t strength() const {
        return expr_operator_levels::unary;
    }

    Expr partial_derivative(const std::string_view& name) const {
        return +item->partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        item->get_all_names(names);
    }

    Expr optimize() const {
        return item->optimize();
    }
};

struct UnaryMinusExprContents {
    Expr item;
};

struct UnaryMinusExpr : UnaryMinusExprContents, IExpr {

    template <typename... Args>
    UnaryMinusExpr(Args&&... args) : UnaryMinusExprContents{std::forward<Args>(args)...} {
    }

    void print(std::ostream& out) const {
        out << "-";
        item->print_in_pars(out, item->strength() < strength());
    }

    size_t strength() const {
        return expr_operator_levels::unary;
    }

    Expr partial_derivative(const std::string_view& name) const {
        return -item->partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        item->get_all_names(names);
    }

    Expr optimize() const ;
};

struct SumExprContents {
    Expr first, second;
};

struct SumExpr : SumExprContents, IExpr {

    template <typename... Args>
    SumExpr(Args&&... args) : SumExprContents{std::forward<Args>(args)...} {
    }

    void print(std::ostream& out) const {
        first->print_in_pars(out, first->strength() < strength());
        out << " + ";
        first->print_in_pars(out, second->strength() <= strength());
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

    Expr optimize() const {
        auto first_o = first->optimize();
        auto second_o = second->optimize();
        if (auto first_a = dynamic_cast<const ValExpr*>(first_o.get())){
            if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
                return make_expr<ValExpr>(first_a->val + second_a->val);
            }
            if (double_equal(first_a->val, 0)) {
                return second_o;
            }
        }
        if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
            if (double_equal(second_a->val, 0)) {
                return first_o;
            }
        }
        return make_expr<SumExpr>(first_o, second_o);
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
        first->print_in_pars(out, first->strength() < strength());
        out << " - ";
        first->print_in_pars(out, second->strength() <= strength());
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

    Expr optimize() const {
        auto first_o = first->optimize();
        auto second_o = second->optimize();
        if (auto first_a = dynamic_cast<const ValExpr*>(first_o.get())){
            if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
                return make_expr<ValExpr>(first_a->val - second_a->val);
            }
            if (double_equal(first_a->val, 0)) {
                return make_expr<UnaryMinusExpr>(second_o)->optimize();
            }
        }
        if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
            if (double_equal(second_a->val, 0)) {
                return first_o;
            }
        }
        return make_expr<DifferenceExpr>(first_o, second_o);
    }
};

Expr UnaryMinusExpr::optimize() const {
    auto item_o = item->optimize();
    if (auto item_a = dynamic_cast<const ValExpr*>(item_o.get())){
        return make_expr<ValExpr>(-item_a->val);
    }
    if (auto item_a = dynamic_cast<const DifferenceExpr*>(item_o.get())){
        return make_expr<DifferenceExpr>(item_a->second, item_a->first)->optimize();
    }
    return make_expr<UnaryMinusExpr>(item_o);
}

struct ProductExprContents {
    Expr first, second;
};

struct ProductExpr : ProductExprContents, IExpr {

    template <typename... Args>
    ProductExpr(Args&&... args) : ProductExprContents{std::forward<Args>(args)...} {
    }

    void print(std::ostream& out) const {
        first->print_in_pars(out, first->strength() < strength());
        out << " * ";
        first->print_in_pars(out, second->strength() <= strength());
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

    Expr optimize() const {
        auto first_o = first->optimize();
        auto second_o = second->optimize();
        if (auto first_a = dynamic_cast<const ValExpr*>(first_o.get())){
            if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
                return make_expr<ValExpr>(first_a->val * second_a->val);
            }
            if (double_equal(first_a->val, -1)) {
                return make_expr<UnaryMinusExpr>(second_o)->optimize();
            }
            if (double_equal(first_a->val, 0)) {
                return make_expr<ValExpr>(0.0);
            }
            if (double_equal(first_a->val, 1)) {
                return second_o;
            }
        }
        if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
            if (double_equal(second_a->val, -1)) {
                return make_expr<UnaryMinusExpr>(first_o)->optimize();
            }
            if (double_equal(second_a->val, 0.0)) {
                return make_expr<ValExpr>(0.0);
            }
            if (double_equal(second_a->val, 1)) {
                return first_o;
            }
        }
        return make_expr<ProductExpr>(first_o, second_o);
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
        first->print_in_pars(out, first->strength() < strength());
        out << " / ";
        first->print_in_pars(out, second->strength() <= strength());
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

    Expr optimize() const {
        auto first_o = first->optimize();
        auto second_o = second->optimize();
        if (auto first_a = dynamic_cast<const ValExpr*>(first_o.get())){
            if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
                return make_expr<ValExpr>(first_a->val / second_a->val);
            }
            if (double_equal(first_a->val, 0)) {
                return make_expr<ValExpr>(0.0);
            }
        }
        if (auto second_a = dynamic_cast<const ValExpr*>(second_o.get())){
            if (double_equal(second_a->val, -1)) {
                return make_expr<UnaryMinusExpr>(first_o)->optimize();
            }
            if (double_equal(second_a->val, 1)) {
                return first_o;
            }
        }
        return make_expr<QuotientExpr>(first_o, second_o);
    }
};

////////////////////////////////////////////////////////////////////////////

Expr operator+(const Expr& item) {
    return make_expr<UnaryPlusExpr>(item);
}

Expr operator-(const Expr& item) {
    return make_expr<UnaryMinusExpr>(item);
}

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
    size_t depth = 0;
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
struct IParser;

template <typename ParsingContext>
Parser<ParsingContext> operator+(const Parser<ParsingContext>& left, const Parser<ParsingContext>& right);
template <typename ParsingContext>
Parser<ParsingContext> operator|(const Parser<ParsingContext>& left, const Parser<ParsingContext>& right);
template <typename ParsingContext>
Parser<ParsingContext> operator~(const Parser<ParsingContext>& item);
template <typename ParsingContext, typename F>
Parser<ParsingContext> operator>>(const Parser<ParsingContext>& item, F&& f);
template <typename ParsingContext>
Parser<ParsingContext> operator<<(const Parser<ParsingContext>& item, const char* name);
template <typename ParsingContext>
std::ostream& operator<<(std::ostream& out, const Parser<ParsingContext>& item);
template <typename ParsingContext>
std::ostream& operator<<(std::ostream& out, const IParser<ParsingContext>& item);

template <typename ParsingContext>
struct IParser {
    virtual ~IParser() = default;

    virtual bool parse_impl(ParsingContext& ctx) const = 0;

    std::optional<typename ParsingContext::Arg> parse_whole(ParsingContext ctx) const {
        if (ctx.end == nullptr) {
            ctx.end = ctx.begin + strlen(ctx.begin);
        }
        if (parse(ctx) and ctx.begin == ctx.end and not ctx.args.empty()) {
            assert(ctx.args.size() == 1);
            return ctx.args[0];
        }
        return std::nullopt;
    }

    bool parse(ParsingContext& ctx) const {
        if (ctx.end == nullptr) {
            ctx.end = ctx.begin + strlen(ctx.begin);
        }
        const char* begin_backup = ctx.begin;
        size_t args_backup = ctx.args.size();
        // std::cout << std::string(ctx.depth, ' ') << *this << "\tentering " << ctx.begin << std::endl;
        ++ctx.depth;
        if (parse_impl(ctx)) {
            --ctx.depth;
            // std::cout << std::string(ctx.depth, ' ') << *this << "\t+exiting " << ctx.begin << std::endl;
            return true;
        }
        --ctx.depth;
        // std::cout << std::string(ctx.depth, ' ') << *this << "\t-exiting " << ctx.begin << std::endl;
        ctx.begin = begin_backup;
        ctx.args.resize(args_backup);
        return false;
    }

    virtual void print(std::ostream&) const = 0;
};

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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__ << "('" << this->item << "')";
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__ << "('" << this->lower << "', '" << this->highest << "')";
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
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

    void print(std::ostream& out) const {
        out << __PRETTY_FUNCTION__;
    }
};

template <typename F, typename ParsingContext>
ReturnedParser(ParsingContext*, F) -> ReturnedParser<F, ParsingContext>;

template <typename ParsingContext>
struct NamedParserContents {
    Parser<ParsingContext> item;
    const char* name;
};

template <typename ParsingContext>
struct NamedParser : NamedParserContents<ParsingContext>, IParser<ParsingContext> {

    template <typename... Args>
    NamedParser(ParsingContext*, Args&&... args) : NamedParserContents<ParsingContext>{std::forward<Args>(args)...} {
    }

    bool parse_impl(ParsingContext& ctx) const {
        return this->item->parse(ctx);
    }

    void print(std::ostream& out) const {
        out << this->name;
    }
};

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

template <typename ParsingContext>
Parser<ParsingContext> operator<<(const Parser<ParsingContext>& item, const char* name) {
    return ParsingContext::template make_parser<NamedParser>(item, name);
}

template <typename ParsingContext>
std::ostream& operator<<(std::ostream& out, const Parser<ParsingContext>& item) {
    item.print(out);
    return out;
}

template <typename ParsingContext>
std::ostream& operator<<(std::ostream& out, const IParser<ParsingContext>& item) {
    item.print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////

using parsing_context_for_expr = ParsingContext<Expr>;

Parser<parsing_context_for_expr> lower_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(islower) << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> upper_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isupper) << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> alpha_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isalpha) << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> digit_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isdigit) << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> alnum_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isalnum) << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> space_parser() {
    return parsing_context_for_expr::make_parser<TestUnsignedCharFuncParser>(isspace) << __PRETTY_FUNCTION__;
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
    return ~space_parser() << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> number_parser() {
    return (digit_parser() + ~digit_parser() >>
            [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                assert(args_begin == args_end);
                char data[1024];
                memset(data, 0, sizeof(data));
                assert(data_begin < data_end);
                assert(size_t(data_end - data_begin) < sizeof(data));
                memcpy(data, data_begin, data_end - data_begin);
                return make_expr<ValExpr>(std::stod(data));
            }) +
               spaces_parser()
           << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> identifier_parser() {
    return (alpha_parser() + ~alnum_parser() >>
            [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                assert(args_begin == args_end);
                assert(data_begin < data_end);
                return make_expr<VarExpr>(std::string_view{data_begin, size_t(data_end - data_begin)});
            }) +
               spaces_parser()
           << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> add_sub_parser();

Parser<parsing_context_for_expr> expr_parser() {
    return spaces_parser() + parsing_context_for_expr::make_parser<ReturnedParser>(add_sub_parser);
}

Parser<parsing_context_for_expr> parentheses_parser();

Parser<parsing_context_for_expr> simplest_parser() {
    return parsing_context_for_expr::make_parser<ReturnedParser>(parentheses_parser) | number_parser() |
           identifier_parser();
}

Parser<parsing_context_for_expr> add_sub_symbol_parser() {
    return ((plus_parser() | minus_parser()) >>
            [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                assert(data_begin < data_end);
                assert(args_end - args_begin == 0);
                return make_expr<VarExpr>(std::string_view{data_begin, size_t(data_end - data_begin)});
            }) +
               spaces_parser()
           << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> unary_add_sub_parser() {
    return add_sub_symbol_parser() + simplest_parser() >>
               [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                   assert(data_begin < data_end);
                   assert(args_end - args_begin == 2);
                   auto&& name = dynamic_cast<const VarExpr&>(*args_begin[0].get()).name_;
                   assert(name == "+" or name == "-");
                   if (name == "+") {
                       return make_expr<UnaryPlusExpr>(args_begin[1]);
                   } else {
                       return make_expr<UnaryMinusExpr>(args_begin[1]);
                   }
               } << __PRETTY_FUNCTION__ |
           simplest_parser();
}

Parser<parsing_context_for_expr> mul_div_symbol_parser() {
    return ((star_parser() | slash_parser()) >>
            [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
                assert(data_begin < data_end);
                assert(args_end - args_begin == 0);
                return make_expr<VarExpr>(std::string_view{data_begin, size_t(data_end - data_begin)});
            }) +
               spaces_parser()
           << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> mul_div_parser() {
    return unary_add_sub_parser() + ~(mul_div_symbol_parser() + unary_add_sub_parser()) >>
           [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
               assert(data_begin < data_end);
               assert((args_end - args_begin) % 2 == 1);
               Expr current = args_begin[0];
               for (auto args_i = args_begin + 1; args_i < args_end; args_i += 2) {
                   auto&& name = dynamic_cast<const VarExpr&>(*args_i[0].get()).name_;
                   assert(name == "*" or name == "/");
                   if (name == "*") {
                       current = current * args_i[1];
                   } else {
                       current = current / args_i[1];
                   }
               }
               return current;
           } << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> add_sub_parser() {
    return mul_div_parser() + ~(add_sub_symbol_parser() + mul_div_parser()) >>
           [](Expr* args_begin, Expr* args_end, const char* data_begin, const char* data_end) {
               assert(data_begin < data_end);
               assert((args_end - args_begin) % 2 == 1);
               Expr current = args_begin[0];
               for (auto args_i = args_begin + 1; args_i < args_end; args_i += 2) {
                   auto&& name = dynamic_cast<const VarExpr&>(*args_i[0].get()).name_;
                   assert(name == "+" or name == "-");
                   if (name == "+") {
                       current = current + args_i[1];
                   } else {
                       current = current - args_i[1];
                   }
               }
               return current;
           } << __PRETTY_FUNCTION__;
}

Parser<parsing_context_for_expr> parentheses_parser() {
    return lpar_parser() + spaces_parser() + expr_parser() + rpar_parser() + spaces_parser() << __PRETTY_FUNCTION__;
}

////////////////////////////////////////////////////////////////////////////

int main() {
    std::string input;
    std::getline(std::cin, input);
    auto expr = expr_parser()->parse_whole(ParsingContext<Expr>(input.c_str())).value();
    std::unordered_set<std::string_view> names;
    expr->get_all_names(names);
    for (auto&& name: names) {
        std::cout << name << ": " << expr->optimize()->partial_derivative(name)->optimize() << std::endl;
    }
}
