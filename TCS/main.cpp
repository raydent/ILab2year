#include "TIS.hpp"

int main(){
    std::vector<vertex2D_t<double>> vertarr(6);
    for(int i = 0; i < 6; i++){
        std::cin >> vertarr[i].x;
        std::cin >> vertarr[i].y;
    }
    triangle_t<double> lhs{vertarr[0], vertarr[1], vertarr[2]};
    triangle_t<double> rhs{vertarr[3], vertarr[4], vertarr[5]};
    double square = lhs.intersection_area(rhs);
    std::cout << square << "\n";
}
