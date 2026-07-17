#include <iostream>
#include <string_view>
#include <memory>
#include <unordered_set>

template<typename Expr>
struct IExprWrapper {
    virtual ~IExprWrapper() = default;
    virtual void print(std::ostream& out) const = 0;

    virtual size_t strength() const = 0;

    virtual Expr partial_derivative(const std::string_view& name) const = 0;

    virtual void get_all_names(std::unordered_set<std::string_view>& names) const = 0;
};

struct Expr {
    std::shared_ptr<IExprWrapper<Expr>> data;

    void print(std::ostream& out) const {
        return data->print(out);
    }

    size_t strength() const {
        return data->strength();
    }

    Expr partial_derivative(const std::string_view& name) const {
        return data->partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        return data->get_all_names(names);
    }
};

template<typename wrapped>
struct ExprWrapper : IExprWrapper<Expr> {
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

    void print(std::ostream& out) const override {
        return v.print(out);
    }

    size_t strength() const override {
        return v.strength();
    }

    Expr partial_derivative(const std::string_view& name) const override {
        return v.partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const override {
        return v.get_all_names(names);
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

Expr operator+(const Expr& left, const Expr& right);
Expr operator-(const Expr& left, const Expr& right);
Expr operator*(const Expr& left, const Expr& right);
Expr operator/(const Expr& left, const Expr& right);

////////////////////////////////////////////////////////////////////////////

struct ValExpr {
    double val;

    void print(std::ostream& out) const {
        out << val;
    }

    size_t strength() const {
        return 0-1LLU;
    }

    Expr partial_derivative(const std::string_view& name) const {
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
        return 0-1LLU;
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

    Expr partial_derivative(const std::string_view& name) const {
        return first.partial_derivative(name) + second.partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first.get_all_names(names);
        second.get_all_names(names);
    }
};

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

    Expr partial_derivative(const std::string_view& name) const {
        return first.partial_derivative(name) - second.partial_derivative(name);
    }


    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first.get_all_names(names);
        second.get_all_names(names);
    }
};

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

    Expr partial_derivative(const std::string_view& name) const {
        return first.partial_derivative(name) * second + first * second.partial_derivative(name);
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first.get_all_names(names);
        second.get_all_names(names);
    }
};

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

    Expr partial_derivative(const std::string_view& name) const {
        return (
            first.partial_derivative(name) * second - first * second.partial_derivative(name)
        ) / second / second;
    }

    void get_all_names(std::unordered_set<std::string_view>& names) const {
        first.get_all_names(names);
        second.get_all_names(names);
    }
};

////////////////////////////////////////////////////////////////////////////

Expr operator+(const Expr& left, const Expr& right) {
    return make_expr<SumExpr>(left, right);
}

Expr operator-(const Expr& left, const Expr& right) {
    return make_expr<DifrerenceExpr>(left, right);
}

Expr operator*(const Expr& left, const Expr& right) {
    return make_expr<ProductExpr>(left, right);
}

Expr operator/(const Expr& left, const Expr& right) {
    return make_expr<QuotientExpr>(left, right);
}

////////////////////////////////////////////////////////////////////////////

int main(){
    std::cout << (
        make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss")
    ).partial_derivative("aaa") << std::endl;
    std::cout << (
        make_expr<VarExpr>("aaa") / make_expr<VarExpr>("sss")
    ).partial_derivative("sss") << std::endl;
}

