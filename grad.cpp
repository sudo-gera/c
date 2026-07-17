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

