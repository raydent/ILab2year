#include "TIS.hpp"

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}
template <typename T>
bool operator == (const vertex2D_t<T> &c1, const vertex2D_t<T> &c2) {
    return (c1.x == c2.x && c1.y == c2.y);
}
template <typename T>
void vertex2D_t<T>::add(vertex2D_t<T> rhs){
    x += rhs.x;
    y += rhs.y;
}

template <typename T>
vec2D_t<T> vec2D_t<T>::makeVec(vertex2D_t<T> A_, vertex2D_t<T> B_){
    x = (B_.x - A_.x);
    y = (B_.y - A_.y);
    A = A_;
    B  = B_;
    x == 0 ? k = 0 : k = y / x;
    return *this;
}

template <typename T>
double vec2D_t<T>::cross_product(vec2D_t<T> rhs){
    return ((y * rhs.x) - (x * rhs.y));
}

template <typename T>
double vec2D_t<T>::cross_product(vertex2D_t<T> rhs){
    vec2D_t BC {B, rhs};
    return cross_product(BC);
}
template <typename T>
void vec2D_t<T>::clipPolygon(vertex2D_t<T> C, std::list<vertex2D_t<T>>& polygon){
    std::vector<vertex2D_t<T>> pointarr;
    std::vector<int> arr1;
    vertex2D_t<T> tempvert;
    bool state = 0;
    vec2D_t<T> temp{0, 0};
    int j = 0;
    int k = 0;
    auto it = polygon.begin();
    auto it2 = polygon.begin();
    assert(it2 != polygon.end());
    it2++;
    for(; it2 != polygon.end(); it++, it2++){
        k++;
        auto temp2 = temp.makeVec(*it, *(it2));
        tempvert = findCrossing(temp2, state);
        if (state == 1){
            pointarr.push_back(tempvert);
            arr1.push_back(k);
            j++;
        }
    }
    tempvert = findCrossing(temp.makeVec(*(it), *polygon.begin()), state);
    if (state == 1){
        pointarr.push_back(tempvert);
        arr1.push_back(polygon.size() - 1);
        j++;
    }
    auto arrit = pointarr.begin();
    for(int i = 0; i < j; i++){
        it = polygon.begin();
        if(i == 0){
            polygon.push_front(arrit[i]);
        }
        else{
            while(arr1[i] != 0){
                it++;
                arr1[i]--;
            }
            for(int f = 0; f < i; f++){
                it++;
            }
            printf("inserting, %f %f\n", arrit[i].x, arrit[i].y);
            polygon.insert(it, arrit[i]);
        }
    }
    int elemnum = 0;
    for(it = polygon.begin(); it != polygon.end(); it++){
        if (rightside(C, *it) != 1){
            printf("erasing, %f %f\n", it -> x, it -> y);
            polygon.erase(it);
            printf("vertices started\n");
            for(auto specit = polygon.begin(); specit != polygon.end(); specit++){
                printf("%f %f\n", specit -> x, specit -> y);
            }
            printf("vertices ended\n");
            it = polygon.begin();
            for(int i = 0; i < elemnum - 1; i++){
                it++;
            }
        }
        elemnum++;
    }
    polygon.unique();
}
template <typename T>
double triangle_t<T>::intersection_area(const triangle_t<T> &rhs){
    std::list<vertex2D_t<T>> polygon;
    polygon.push_front(rhs.A);
    polygon.push_front(rhs.B);
    polygon.push_front(rhs.C);
    printf("AB\n");
    printf("A.x = %f A.y = %f\nB.x = %f B.y = %f\nC.x = %f C.y = %f\n", A.x, A.y, B.x, B.y, C.x, C.y);
    for(auto it = polygon.begin(); it != polygon.end(); it++){
        printf("%f %f\n", it -> x, it -> y);
    }
    printf("start\n");
    AB.clipPolygon(C, polygon);
    for(auto it = polygon.begin(); it != polygon.end(); it++){
        printf("%f %f\n", it -> x, it -> y);
    }
    printf("BC\n");
    for(auto it = polygon.begin(); it != polygon.end(); it++){
        printf("%f %f\n", it -> x, it -> y);
    }
    BC.clipPolygon(A, polygon);
    printf("CA\n");
    for(auto it = polygon.begin(); it != polygon.end(); it++){
        printf("%f %f\n", it -> x, it -> y);
    }
    CA.clipPolygon(B, polygon);
    for(auto it = polygon.begin(); it != polygon.end(); it++){
        printf("%f %f\n", it -> x, it -> y);
    }
    return 0;
}

template <typename T>
bool vec2D_t<T>::rightside(vertex2D_t<T> C, vertex2D_t<T> rhs){
    double crossC = cross_product(C);
    double crossRhs = cross_product(rhs);
    //printf("crossC = %f, crossRhs = %f, rhs.x = %f,rhs.y = %f,  C.x = %f, C.y = %f\n", crossC, crossRhs, rhs.x, rhs.y, C.x, C.y);
    if (crossRhs == 0)
        return 1;
    if (sign(crossRhs) != sign(crossC))
        return 0;
    return 1;
}

template <typename T>
vertex2D_t<T> vec2D_t<T>::findCrossing(vec2D_t<T> rhs, bool& state){
    state = 0;
    vertex2D_t<T> trash{0, 0};
    if (k == rhs.k){
        //printf("case0\n");
        return trash;
    }
    else {
        if (k == 0){
            if (y == 0){
                double y0 = A.y;
                if (sign(y0 - rhs.A.y) != sign(y0 - rhs.B.y)){
                    printf("case2.50\n");
                    double x0 = (y0 - rhs.A.y) / rhs.k + rhs.A.x;
                    vertex2D_t<T> ret{x0, y0};
                    state = 1;
                    return ret;
                }
                printf("case2.75\n");
                return trash;
            }
            double x0 = A.x;
            if (x0 == rhs.A.x || x0 == rhs.B.x){
                printf("case1\n");
                state = 0;
                return trash;
            }
            if (sign(x0 - rhs.A.x) != sign (x0 - rhs.B.x)){
                printf("case2\n");
                state = 1;
                double y0 = (A.x - rhs.A.x) * k + rhs.A.y;
                vertex2D_t<T> ret{x0, y0};
                printf("x0 = %f, y0 = %f\n", x0, y0);
                return ret;
            }
            printf("case2.25\n");
            return trash;
        }
        if (rhs.k == 0){
            if (rhs.y == 0){
                double y0 = rhs.A.y;
                printf("y0 = %f\n", y0);
                double x0 = (y0 - A.y) / k + A.x;
                if (sign(x0 - rhs.A.x) != sign(x0 - rhs.B.x)){
                    printf("case2.5\n");
                    vertex2D_t<T> ret{x0, y0};
                    state = 1;
                    return ret;
                }
                printf("case2.88\n");
                return trash;
            }
            double x0 = rhs.A.x;
            if (sign(x0 - A.x) != sign (x0 - B.x)){
                printf("case3\n");
                rhs.print();
                print();
                state = 1;
                double y0 = (x - A.x) * k + A.y;
                vertex2D_t<T> ret{x0, y0};
                return ret;
            }
            return trash;
        }
        double x0 = (rhs.A.y - A.y - rhs.k * rhs.A.x + k * A.x) / (k - rhs.k);
        if (x0 == rhs.A.x || x0 == rhs.B.x){
            printf("case4\n");
            state = 0;
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k};
            return ret;
        }
        if (sign(x0 - rhs.A.x) != sign (x0 - rhs.B.x)){
            printf("case5\n");
            printf("x0 = %f, y0 = %f\n", x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k);
            state = 1;
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k};
            return ret;
        }
        return trash;
    }
    return trash;
}
template <typename T>
void vec2D_t<T>::print(){
    //printf("x = %f y = %f A.x = %f A.y = %f B.x = %f B.y = %f k = %f\n", x, y, A.x, A.y, B.x, B.y, k);
    std::cout << x << " " << y << " " << A.x << " " << A.y << " " << B.x << " " << B.y << " " << k << "\n";
}

template <typename T>
void triangle_t<T>::print(){
    std::cout << A.x << " " << A.y << " " << B.x << " " << B.y << " " << C.x << " " << C.y << " " << AB.x << " " << AB.y << " " << AB.k << "\n";
}

template class vertex2D_t<double>;
template class triangle_t<double>;
template class vec2D_t<double>;
