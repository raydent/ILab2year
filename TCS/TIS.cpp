#include "TIS.hpp"

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
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
    it2++;
    //printf("get temp2 = %f %f %f\n", temp2.x, temp2.y, temp2.k);
    for(; it2 != polygon.end(); it++, it2++){
        k++;
        auto temp2 = temp.makeVec(*it, *(it2));
        tempvert = findCrossing(temp2, state);
        printf("1\n");
        if (state == 1){
            printf("tepvert.x = %f .y = %f\n", tempvert.x, tempvert.y);
            pointarr[j] = tempvert;
            printf("get\n");
            arr1[j] = k;
            j++;
        }
    }
    pointarr[j] = findCrossing(temp.makeVec(*(it), *polygon.begin()), state);
    if (state == 1){
        arr1[j] = polygon.size() - 1;
        j++;
    }
    auto arrit = pointarr.begin();
    for(int i = 0; i < j; i++){
        it = polygon.begin();
        while(arr1[i] != 0){
            it++;
        }
        for(int f = 0; f < i; f++){
            it++;
        }
        polygon.insert(it, arrit[i]);
    }
    int elemnum = 0;
    for(it = polygon.begin(); it != polygon.end(); it++){
        if (rightside(C, *it) != 1){
            polygon.erase(it);
            it = polygon.begin();
            for(int i = 0; i < elemnum - 1; i++){
                it++;
            }
        }
        elemnum++;
    }
}
template <typename T>
double triangle_t<T>::intersection_area(const triangle_t<T> &rhs){
    std::list<vertex2D_t<T>> polygon;
    polygon.push_front(rhs.A);
    polygon.push_front(rhs.B);
    polygon.push_front(rhs.C);
    for(auto it = polygon.begin(); it != polygon.end(); it++){
        printf("%f %f\n", it -> x, it -> y);
    }
    AB.clipPolygon(C, polygon);
    BC.clipPolygon(A, polygon);
    CA.clipPolygon(B, polygon);
    // for(auto it = polygon.begin(); it != polygon.end(); it++){
    //     printf("%f %f\n", it -> x, it -> y);
    // }
    return 0;
}

template <typename T>
bool vec2D_t<T>::rightside(vertex2D_t<T> C, vertex2D_t<T> rhs){
    double crossC = cross_product(C);
    double crossRhs = cross_product(rhs);
    if (crossRhs == 0)
        return 1;
    if (sign(crossRhs) != sign(crossC))
        return 0;
    return 1;
}

template <typename T>
vertex2D_t<T> vec2D_t<T>::findCrossing(vec2D_t<T> rhs, bool& state){
    state = 0;
    printf("0\n");
    vertex2D_t<T> trash{0, 0};
    if (k == rhs.k){
        printf("returning trash\n");
        return trash;
    }
    else {
        if (k == 0){
            double x0 = A.x;
            if (sign(x0 - rhs.A.x) != sign (x0 - rhs.B.x)){
                printf("case 1\n");
                state = 1;
                double y0 = (A.x - rhs.A.x) * k + rhs.A.y;
                vertex2D_t<T> ret{x0, y0};
                return ret;
            }
            printf("returning second trash\n");
            return trash;
        }
        if (rhs.k == 0){
            printf("2\n");
            double x0 = rhs.A.x;
            if (sign(x0 - A.x) != sign (x0 - B.x)){
                printf("case 2\n");
                state = 1;
                double y0 = (x - A.x) * k + A.y;
                vertex2D_t<T> ret{x0, y0};
                return ret;
            }
            printf("returning third trash\n");
            return trash;
        }
        double x0 = (rhs.A.y - A.y - rhs.k * rhs.A.x + k * A.x) / (k - rhs.k);
        if (x0 == rhs.A.x || x0 == rhs.B.x){
            printf("case 3\n");
            state = 1;
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k};
            return ret;
        }
        if (sign(x0 - rhs.A.x) != sign (x0 - rhs.B.x)){
            printf("case 4\n");
            state = 1;
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k};
            return ret;
        }
        printf("returning fourth trash\n");
        return trash;
    }
    return trash;
}


template <typename T>
void triangle_t<T>::print(){
    std::cout << A.x << " " << A.y << " " << B.x << " " << B.y << " " << C.x << " " << C.y << " " << AB.x << " " << AB.y << " " << AB.k << "\n";
}

template class vertex2D_t<double>;
template class triangle_t<double>;
template class vec2D_t<double>;
