#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <queue>

template <typename T>
int sign(T val);

template <typename T>
class vertex2D_t {
public:
    T x, y;
    vertex2D_t(T x_ = 0, T y_ = 0): x(x_), y(y_){}
    void add(vertex2D_t rhs);
};

template <typename T>
class vec2D_t {
public:
    T x, y;
    vertex2D_t<T> A, B;
    double k;
    vec2D_t(vertex2D_t<T> A_, vertex2D_t<T> B_) : x(B_.x - A_.x), y(B_.y - A_.y), A(A_), B(B_) {x == 0 ? k = 0 : k = y / x;}
    double cross_product(vec2D_t<T> rhs);
    double cross_product(vertex2D_t<T> rhs);
    vertex2D_t<T> findCrossing(vec2D_t<T> rhs, bool& state);
    void clipPolygon(vertex2D_t<T> C, std::list<vertex2D_t<T>>& polygon);
    vec2D_t<T> makeVec(vertex2D_t<T> A_, vertex2D_t<T> B_);
    bool rightside(vertex2D_t<T> C, vertex2D_t<T> rhs);
};

template <typename T>
class triangle_t {
public:
    vertex2D_t<T> A, B, C;
    vec2D_t<T> AB, BC, CA;
    triangle_t(vertex2D_t<T> A_, vertex2D_t<T> B_, vertex2D_t<T> C_): A(A_), B(B_), C(C_), AB(A_, B_), BC(B_, C_), CA(C_, A_) {}
    double intersection_area(const triangle_t<T> &rhs);
    void print();
};
template <typename T>
void formingPolygone(std::vector<vertex2D_t<T>> & polygon, const vec2D_t<T> AB, const vertex2D_t<T> C, const triangle_t<T> &rhs);
