#include <iostream>
#include <string_view>
#include <memory>

struct IExprWrapper {
    virtual void print(std::ostream& out) const = 0;
    virtual size_t strength() const = 0;

    virtual ~IExprWrapper() = default;
};

template<typename wrapped>
struct ExprWrapper : IExprWrapper {
    wrapped v;

    template<typename...Args>
    requires std::is_constructible_v<wrapped, Args...>
    ExprWrapper(Args&&...args):
        v(std::forward<Args>(args)...)
    {}

    template<typename...Args>
    requires (
        ! std::is_constructible_v<wrapped, Args...>
        && std::is_aggregate_v<wrapped>
    )
    ExprWrapper(Args&&...args):
        v{std::forward<Args>(args)...}
    {}

    void print(std::ostream& out) const {
        return v.print(out);
    }

    virtual size_t strength() const {
        return v.strength();
    }
};

struct Expr {
    std::shared_ptr<IExprWrapper> data;

    void print(std::ostream& out) const {
        return data->print(out);
    }

    size_t strength() const {
        return data->strength();
    }
};

template<typename backend, typename...Args>
Expr make_expr(Args&&...args) {
    return Expr{
        std::make_shared<
            ExprWrapper<
                backend
            >
        >(std::forward<Args>(args)...)
    };
}

std::ostream& operator<<(std::ostream& out, const Expr& thing) {
    thing.print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////

struct ValExpr {
    double val;

    void print(std::ostream& out) const {
        out << val;
    }

    size_t strength() const {
        return 0-1LLU;
    }
};

struct VarExpr {
    std::string_view name;

    void print(std::ostream& out) const {
        out << name;
    }

    size_t strength() const {
        return 0-1LLU;
    }
};

struct SumExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first.strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " + ";
        if (second.strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return 10;
    }
};

Expr operator+(const Expr& left, const Expr& right) {
    return make_expr<SumExpr>(left, right);
}

struct DifrerenceExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first.strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " - ";
        if (second.strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return 10;
    }
};

Expr operator-(const Expr& left, const Expr& right) {
    return make_expr<DifrerenceExpr>(left, right);
}

struct ProductExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first.strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " * ";
        if (second.strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return 20;
    }
};

Expr operator*(const Expr& left, const Expr& right) {
    return make_expr<ProductExpr>(left, right);
}

struct QuotientExpr {
    Expr first, second;

    void print(std::ostream& out) const {
        if (first.strength() < strength()) {
            out << "(" << first << ")";
        } else {
            out << first;
        }
        out << " / ";
        if (second.strength() > strength()) {
            out << second;
        } else {
            out << "(" << second << ")";
        }
    }

    size_t strength() const {
        return 20;
    }
};

Expr operator/(const Expr& left, const Expr& right) {
    return make_expr<QuotientExpr>(left, right);
}

int main(){
    std::cout << (
        make_expr<ValExpr>(3.4) - make_expr<ValExpr>(0.1) + make_expr<ValExpr>(0.2)
    ) << std::endl;
}

