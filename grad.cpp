#include <iostream>
#include <string_view>
#include <memory>

struct IExprMiddleend {
    virtual void print(std::ostream& out) const = 0;

    virtual ~IExprMiddleend() = default;
};

template<typename wrapped>
struct ExprMiddleend : IExprMiddleend {
    wrapped v;

    template<typename...Args>
    requires std::is_constructible_v<wrapped, Args...>
    ExprMiddleend(Args&&...args):
        v(std::forward<Args>(args)...)
    {}

    template<typename...Args>
    requires (
        ! std::is_constructible_v<wrapped, Args...>
        && std::is_aggregate_v<wrapped>
    )
    ExprMiddleend(Args&&...args):
        v{std::forward<Args>(args)...}
    {}

    void print(std::ostream& out) const {
        v.print(out);
    }
};

struct ExprFrontend {
    std::shared_ptr<IExprMiddleend> data;

    void print(std::ostream& out) const {
        return data->print(out);
    }
};

template<typename backend, typename...Args>
ExprFrontend make_expr(Args&&...args) {
    return ExprFrontend{
        std::make_shared<
            ExprMiddleend<
                backend
            >
        >(std::forward<Args>(args)...)
    };
}

std::ostream& operator<<(std::ostream& out, const ExprFrontend& thing) {
    thing.print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////

struct ValExprBackend {
    double val;

    void print(std::ostream& out) const {
        out << val;
    }
};

struct SumExprBackend {
    ExprFrontend first, second;

    void print(std::ostream& out) const {
        out << "(" << first << ") + (" << second << ")";
    }
};

ExprFrontend operator+(const ExprFrontend& left, const ExprFrontend& right) {
    return make_expr<SumExprBackend>(left, right);
}

int main(){
    std::cout << (
        make_expr<ValExprBackend>(3.4) + make_expr<ValExprBackend>(0.1) + make_expr<ValExprBackend>(0.2)
    ) << std::endl;
}

// struct Expr;

// struct IExpr {
//     virtual void print(std::ostream& out) const = 0;
// };

// struct Expr {
//     std::shared_ptr<IExpr> data;
// };

// std::ostream& operator<<(std::ostream& out, const Expr& value) {
//     value.data->print(out);
//     return out;
// }

// struct ConstantExpr: IExpr {
//     double value = 0;

//     void print(std::ostream& out) const override {
//         out << value;
//     }
// };

// struct VariableExpr: IExpr {
//     std::string_view name;

//     void print(std::ostream& out) const override {
//         out << name;
//     }
// };

// struct SumExpr: IExpr{
//     Expr left, right;

//     SumExpr(const Expr& left, const Expr& right):
//         left(left),
//         right(right)
//     {}

//     void print(std::ostream& out) const override {
//         out << "(" << left << ") + (" << right << ")";
//     }
// };

// struct ProductExpr: IExpr {
//     Expr left, right;

//     ProductExpr(const Expr& left, const Expr& right):
//         left(left),
//         right(right)
//     {}

//     void print(std::ostream& out) const override {
//         out << "(" << left << ") * (" << right << ")";
//     }
// };

// struct DifferenceExpr: IExpr {
//     Expr left, right;

//     DifferenceExpr(const Expr& left, const Expr& right):
//         left(left),
//         right(right)
//     {}

//     void print(std::ostream& out) const override {
//         out << "(" << left << ") - (" << right << ")";
//     }
// };

// struct QuotientExpr: IExpr {
//     Expr left, right;

//     QuotientExpr(const Expr& left, const Expr& right):
//         left(left),
//         right(right)
//     {}

//     void print(std::ostream& out) const override {
//         out << "(" << left << ") / (" << right << ")";
//     }
// };

// struct ReminderExpr: IExpr {
//     Expr left, right;

//     ReminderExpr(const Expr& left, const Expr& right):
//         left(left),
//         right(right)
//     {}

//     void print(std::ostream& out) const override {
//         out << "(" << left << ") % (" << right << ")";
//     }
// };

// Expr operator+(const Expr& left, const Expr& right) {
//     return Expr{std::make_unique<SumExpr>(left, right)};
// }

// Expr operator-(const Expr& left, const Expr& right) {
//     return Expr{std::make_unique<DifferenceExpr>(left, right)};
// }

// Expr operator*(const Expr& left, const Expr& right) {
//     return Expr{std::make_unique<ProductExpr>(left, right)};
// }

// Expr operator/(const Expr& left, const Expr& right) {
//     return Expr{std::make_unique<QuotientExpr>(left, right)};
// }

// Expr operator%(const Expr& left, const Expr& right) {
//     return Expr{std::make_unique<ReminderExpr>(left, right)};
// }

// int main() {

// }




// #include <memory>
// #include <vector>
// #include <iostream>

// struct aggregate {
//     int a,b,c;

// };

// template<typename wrapped>
// struct wrapper {
//     a v;

//     template<typename...Args>
//     requires std::is_constructible_v<wrapped, T...>
//     wrapper(Args&&...args):
//         v(std::forward<T>(args)...)
//     {}

//     template<typename...Args>
//     requires (
//         ! std::is_constructible_v<wrapped, T...>
//         && std::is_aggregate_v<wrapped>
//     )
//     wrapper(Args&&...args):
//         v{std::forward<T>(args)...}
//     {}
// };

// int main(){
//     wrapper<aggregate> x(1,2,3);
//     wrapper<std::vector<int>> a(4,4);
//     std::cout << a.v.size() << std::endl;
//     wrapper<std::vector<int>> s(4,4,4);
//     std::cout << s.v.size() << std::endl;
// }
