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
double triangle_t<T>::intersection_area(const triangle_t<T> &rhs){
    std::vector<vertex2D_t<T>> polygon;
    polygon[0] = rhs.A;
    polygon[1] = rhs.B;
    polygon[2] = rhs.C;
    formingPolygone(polygon, AB, C, rhs);
    formingPolygone(polygon, BC, A, rhs);
    formingPolygone(polygon, CA, B, rhs);

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
bool rightside(vec2D_t<T> AB, vertex2D_t<T> C, vertex2D_t<T> rhs){
    double crossC = AB.cross_product(C);
    double crossRhs = AB.cross_product(rhs);
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
    if (k == rhs.k)
        return trash;
    else {
        double x0 = (rhs.A.y - A.y - rhs.k * rhs.A.x + k * A.x) / (k - rhs.k);
        if (x0 == rhs.A.x || x0 == rhs.B.x){
            state = 1;
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * k};
            return ret;
        }
        if (sign(x0 - rhs.A.x) != sign (x0 - rhs.B.x)){
            state = 1;
            vertex2D_t<T> ret{x0, rhs.A.y + (x0 - rhs.A.x) * k};
            return ret;
        }
        else
            return trash;
    }
}

template <typename T>
bool lineTriangleIntersecSearch(std::vector<vertex2D_t<T>> &crossings, const vec2D_t<T>& line, const triangle_t<T> &rhs){
    bool state = 0;
    int i = 0;
    crossings[i] = line.findCrossing(rhs.AB, state);
    if (state == 1)
        i++;
    state = 0;
    crossings[i] = line.findCrossing(rhs.BC, state);
    if (state == 1 && i == 1)
        return 1;
    else if (state == 1)
        i++;
    state = 0;
    crossings[i] = line.findCrossing(rhs.CA, state);
    if (state == 1)
        return 1;
    return 0;
}

template <typename T>
void formingPolygone(std::vector<vertex2D_t<T>> & polygon, const vec2D_t<T> AB, const vertex2D_t<T> C, const triangle_t<T> &rhs){
    bool state = 0;
    std::vector<vertex2D_t<T>> crossings(2);

}

//template class sign<double>;
template class vertex2D_t<double>;
template class triangle_t<double>;
template class vec2D_t<double>;
// template class vec2D_t<int>;
// template class vec2D_t<double>::findCrossing(vec2D_t<double>, bool&);
//template class formingPolygone<double>;
