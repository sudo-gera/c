#include "any.cpp"

struct square{
    double x1,y1,x2,y2;
};

struct circle{
    double x,y,r;
};

void print_area(const square& s){
    std::cout << (s.x2 - s.x1) * (s.x2 - s.x1) + (s.y2 - s.y1) * (s.y2 - s.y1)  << std::endl;
}

void print_area(const circle& c){
    std::cout << c.r * c.r * M_PI  << std::endl;
}

void print_perimeter(const square& s){
    std::cout << sqrt( (s.x2 - s.x1) * (s.x2 - s.x1) + (s.y2 - s.y1) * (s.y2 - s.y1) ) * 4 << std::endl;
}

void print_perimeter(const circle& c){
    std::cout << c.r * M_PI * 2 << std::endl;
}

int main(){
    square s{
        .x1 = 0,
        .y1 = 0,
        .x2 = 3,
        .y2 = 4,
    };
    circle c{
        .x = 0,
        .y = 0,
        .r = 1,
    };

    any a;

    a = s;
    VISIT(print_perimeter, a);
    VISIT(print_area, a);

    a = c;
    VISIT(print_perimeter, a);
    VISIT(print_area, a);
}

END_OF_CODE
