#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <queue>
#include <cmath>


template <typename T>
struct vertex2D_t {
    T x, y;
    vertex2D_t(T x_ = 0, T y_ = 0): x(x_), y(y_){}
    void add(vertex2D_t rhs);
};

template <typename T>
struct polygon_t {
    std::list<vertex2D_t<T>> list;
    polygon_t(){;}
    polygon_t(vertex2D_t<T> A_, vertex2D_t<T> B_, vertex2D_t<T> C_) {list.push_front(A_); list.push_front(B_); list.push_front(C_);}
    void push(int position, vertex2D_t<T>& elem);
    double calc_square();
    void print();
};

template <typename T>
struct vec2D_t {
    T x, y;
    vertex2D_t<T> A, B;
    double k;
    vec2D_t(vertex2D_t<T> A_, vertex2D_t<T> B_) : x(B_.x - A_.x), y(B_.y - A_.y), A(A_), B(B_) {x == 0 ? k = 0 : k = y / x;}
    double cross_product(vec2D_t<T> rhs);
    double cross_product(vertex2D_t<T> rhs);
    bool findCrossing(vec2D_t<T> rhs, vertex2D_t<T>& ret1);
    void clipPolygon(vertex2D_t<T> C, polygon_t<T>& polygon);
    vec2D_t<T> makeVec(vertex2D_t<T> A_, vertex2D_t<T> B_);
    bool rightside(vertex2D_t<T> C, vertex2D_t<T> rhs);
    void remove_wrong_points_from_polygon(polygon_t<T>& polygon, vertex2D_t<T> C);
    void print();
};

template <typename T>
struct triangle_t {
    vertex2D_t<T> A, B, C;
    vec2D_t<T> AB, BC, CA;
    triangle_t(vertex2D_t<T> A_, vertex2D_t<T> B_, vertex2D_t<T> C_): A(A_), B(B_), C(C_), AB{A_, B_}, BC{B_, C_}, CA{C_, A_} {}
    double intersection_area(const triangle_t<T> &rhs);
    void print();
};

template <typename T>
double calc_square(std::list<vertex2D_t<T>> polygon);

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
void vec2D_t<T>::clipPolygon(vertex2D_t<T> C, polygon_t<T>& polygon){
    std::vector<vertex2D_t<T>> pointarr;
    std::vector<int> arr1;
    vertex2D_t<T> tempvert;
    bool state = false; //  проверяет, пересекает ли секущая прямая отрезок второго полигона, true/false
    vec2D_t<T> temp{0, 0};
    int j = 0;
    int elempos = 0;
    auto it = polygon.list.begin();
    auto it2 = polygon.list.begin();
    //assert(it2 != polygon.list.end());
    it2++;
    for(; it2 != polygon.list.end(); it++, it2++){
        elempos++;
        auto temp2 = temp.makeVec(*it, *(it2));
        if (findCrossing(temp2, tempvert)) {
            pointarr.push_back(tempvert);
            arr1.push_back(elempos);
        }
    }
    if (findCrossing(temp.makeVec(*(it), *polygon.list.begin()), tempvert)) {
        pointarr.push_back(tempvert);
        arr1.push_back(0);
    }
    auto arrit = pointarr.begin();
    it = polygon.list.begin();
    for(int i = 0; i < arr1.capacity(); i++){
        if (arr1[i] != 0)
            arr1[i] += i;
        polygon.push(arr1[i], arrit[i]);
    }
    remove_wrong_points_from_polygon(polygon, C);
}

template <typename T>
double triangle_t<T>::intersection_area(const triangle_t<T> &rhs){
    polygon_t<T> polygon(rhs.A, rhs.B, rhs.C);
    AB.clipPolygon(C, polygon);
    BC.clipPolygon(A, polygon);
    CA.clipPolygon(B, polygon);
    double square = polygon.calc_square();
    return square;
}

template <typename T>
bool vec2D_t<T>::rightside(vertex2D_t<T> C, vertex2D_t<T> rhs){
    double crossC = cross_product(C);
    double crossRhs = cross_product(rhs);
    if (crossRhs == 0)
        return 1;
    if (std::signbit(crossRhs) != std::signbit(crossC))
        return 0;
    return 1;
}

template <typename T>
bool vec2D_t<T>::findCrossing(vec2D_t<T> rhs, vertex2D_t<T>& ret1){
    vertex2D_t<T> trash{0, 0};
    if (k == rhs.k && ((y == rhs.y) || (x == rhs.x))){
        return false;
    }
    else {
        if (k == 0){
            if (y == 0){
                double y0 = A.y;
                if (y0 == rhs.A.y || y0 == rhs.B.y){
                    return false;
                }
                if (std::signbit(y0 - rhs.A.y) != std::signbit(y0 - rhs.B.y)){
                    double x0 = (y0 - rhs.A.y) / rhs.k + rhs.A.x;
                    vertex2D_t<T> ret{x0, y0};
                    ret1 = ret;
                    return true;
                }
                return false;
            }
            double x0 = A.x;
            if (x0 == rhs.A.x || x0 == rhs.B.x){
                return false;
            }
            if (std::signbit(x0 - rhs.A.x) != std::signbit (x0 - rhs.B.x)){
                double y0 = (A.x - rhs.A.x) * rhs.k + rhs.A.y;
                vertex2D_t<T> ret{x0, y0};
                ret1 = ret;
                return true;
            }
            return false;
        }
        if (rhs.k == 0){
            if (rhs.y == 0){
                double y0 = rhs.A.y;
                double x0 = (y0 - A.y) / k + A.x;
                if (x0 == rhs.A.x || x0 == rhs.B.x){
                    return false;
                }
                if (std::signbit(x0 - rhs.A.x) != std::signbit(x0 - rhs.B.x)){
                    vertex2D_t<T> ret{x0, y0};
                    ret1 = ret;
                    return true;
                }
                return false;
            }
            double x0 = rhs.A.x;
            if (std::signbit(x0 - A.x) != std::signbit (x0 - B.x)){
                double y0 = (x0 - A.x) * k + A.y;
                vertex2D_t<T> ret{x0, y0};
                ret1 = ret;
                return true;
            }
            return false;
        }
        double x0 = (rhs.A.y - A.y - rhs.k * rhs.A.x + k * A.x) / (k - rhs.k);
        if (x0 == rhs.A.x || x0 == rhs.B.x){
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k};
            ret1 = ret;
            return true;
        }
        if (std::signbit(x0 - rhs.A.x) != std::signbit (x0 - rhs.B.x)){
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * rhs.k};
            ret1 = ret;
            return true;
        }
        return false;
    }
    return false;
}

template <typename T>
void vec2D_t<T>::print(){
    std::cout << x << " " << y << " " << A.x << " " << A.y << " " << B.x << " " << B.y << " " << k << "\n";
}

template <typename T>
void triangle_t<T>::print(){
    std::cout << A.x << " " << A.y << " " << B.x << " " << B.y << " " << C.x << " " << C.y << " " << AB.x << " " << AB.y << " " << AB.k << "\n";
}

template <typename T>
double polygon_t<T>::calc_square(){
    double square = 0;
    auto it1 = list.begin();
    auto it2 = list.begin();
    it2++;
    for(; it2 != list.end(); it1++, it2++){
        square += (it1 -> x) * (it2 -> y) - (it2 -> x)*(it1 -> y);
    }
    it1 = list.end();
    it1--;
    it2 = list.begin();
    square += (it1 -> x) * (it2 -> y) - (it2 -> x)*(it1 -> y);
    square /= 2;
    return std::abs(square);
}

template <typename T>
void polygon_t<T>::push(int elempos, vertex2D_t<T>& elem){
    if (elempos == 0)
        list.push_front(elem);
    else{
        auto it = list.begin();
        while(elempos != 0){
            it++;
            elempos--;
        }
        if (it == list.end()){
            it--;
        }
        list.insert(it, elem);
    }
}

template <typename T>
void vec2D_t<T>::remove_wrong_points_from_polygon(polygon_t<T>& polygon, vertex2D_t<T> C){
    for(auto it = polygon.list.begin(); it != polygon.list.end(); it++){
        if (rightside(C, *it) != 1){
            auto tempit = it;
            tempit--;
            polygon.list.erase(it);
            it = tempit;
        }
    }
}

template <typename T>
void polygon_t<T>::print(){
    printf("vertexes starting\n");
    for(auto it = list.begin(), ite = list.end(); it != ite; ++it){
        printf("x = %f y = %f\n", it -> x, it -> y);
    }
    printf("vertexes ending\n");
}
