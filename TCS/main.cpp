#include "TIS.hpp"

int main(){
    vertex2D_t<double> A{0, 0};
    vertex2D_t<double> B{0, 2};
    vertex2D_t<double> C{2, 0};
    vertex2D_t<double> D{2, 2};
    triangle_t<double> lhs{A, B, C};
    triangle_t<double> rhs{A, D, C};
    // lhs.print();
    bool state = 0;
    std::cout << lhs.AB.k << " " << rhs.BC.k << "\n";
    vertex2D_t<double> temp = lhs.BC.findCrossing(rhs.AB, state);
    double square = lhs.intersection_area(rhs);
    std::cout << temp.x << " " << temp.y << " " << state << " " <<  "\n";
}
