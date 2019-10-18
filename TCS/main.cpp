#include "TIS.hpp"

int main(){
    // vertex2D_t<double> A{0, 0};
    // vertex2D_t<double> B{0, 2};
    // vertex2D_t<double> C{2, 0};
    // vertex2D_t<double> D{2, 2};
    // triangle_t<double> lhs{A, B, C};
    // triangle_t<double> rhs{C, D, A};
    // vertex2D_t<double> A{0, 0};
    // vertex2D_t<double> B{2, 4};
    // vertex2D_t<double> C{4, 0};
    // vertex2D_t<double> D{0, 1};
    // vertex2D_t<double> E{2, 5};
    // vertex2D_t<double> F{4, 1};
    // triangle_t<double> lhs{A, B, C};
    // triangle_t<double> rhs{D, E, F};
    // vertex2D_t<double> A{0, 1};
    // vertex2D_t<double> B{2, 3};
    // vertex2D_t<double> C{4, 1};
    // vertex2D_t<double> D{1, 0};
    // vertex2D_t<double> E{4, 3};
    // vertex2D_t<double> F{6, 0};
    // triangle_t<double> lhs{A, B, C};
    // triangle_t<double> rhs{D, E, F};
    vertex2D_t<double> A{0, 0};
    vertex2D_t<double> B{4, 4};
    vertex2D_t<double> C{8, 0};
    vertex2D_t<double> D{4, -1};
    vertex2D_t<double> E{2, 1};
    vertex2D_t<double> F{6, 1};
    triangle_t<double> lhs{A, B, C};
    triangle_t<double> rhs{D, E, F};
    // vertex2D_t<double> A{0, 0};
    // vertex2D_t<double> B{-3, 3};
    // vertex2D_t<double> C{3, 3};
    // vertex2D_t<double> D{-3, 1};
    // vertex2D_t<double> E{0, 4};
    // vertex2D_t<double> F{3, 1};
    // triangle_t<double> lhs{A, B, C};
    // triangle_t<double> rhs{D, E, F};

    lhs.print();
    rhs.print();
    bool state = 0;
    //std::cout << lhs.AB.k << " " << rhs.BC.k << "\n";
    lhs.BC.print();
    rhs.CA.print();
    // vertex2D_t<double> temp = rhs.BC.findCrossing(lhs.CA, state);
    double square = rhs.intersection_area(lhs);
    // std::cout << temp.x << " " << temp.y << " " << state << " " <<  "\n";
}
