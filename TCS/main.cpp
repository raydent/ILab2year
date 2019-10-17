#include "TIS.hpp"

int main(){
    vertex2D_t<double> A{2, 4};
    vertex2D_t<double> B{2, 6};
    vertex2D_t<double> C{4, 6};
    vertex2D_t<double> D{0, 6};
    vec2D_t<double> BC{B, C};
    vec2D_t<double> AB{A, B};
    vec2D_t<double> BD{B, D};
    double firstprod = AB.cross_product(BC);
    double secprod = AB.cross_product(BD);
    std::cout << firstprod << " " <<  secprod << " " << AB.A.x << " " << AB.B.y << " " << AB.k << "\n";
}
