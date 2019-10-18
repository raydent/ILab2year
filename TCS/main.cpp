#include "TIS.hpp"

int main(){
    // vertex2D_t<double> A{0, 0};
    // vertex2D_t<double> B{0, 2};
    // vertex2D_t<double> C{2, 0};
    // vertex2D_t<double> D{2, 2};
    // triangle_t<double> lhs{A, B, C};
    // triangle_t<double> rhs{C, D, A};
    vertex2D_t<double> A{0, 1};
    vertex2D_t<double> B{2, 3};
    vertex2D_t<double> C{4, 1};
    vertex2D_t<double> D{1, 0};
    vertex2D_t<double> E{4, 3};
    vertex2D_t<double> F{6, 0};
    triangle_t<double> lhs{A, B, C};
    triangle_t<double> rhs{D, E, F};
    lhs.print();
    rhs.print();
    bool state = 0;
    //std::cout << lhs.AB.k << " " << rhs.BC.k << "\n";
    lhs.BC.print();
    rhs.CA.print();
    vertex2D_t<double> temp = lhs.BC.findCrossing(rhs.CA, state);
    //double square = lhs.intersection_area(rhs);
    std::cout << temp.x << " " << temp.y << " " << state << " " <<  "\n";
}
