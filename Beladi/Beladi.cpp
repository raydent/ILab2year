#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>


struct page {
    int index;
    char data[60];
};

bool operator == (const page &c1, const page &c2) {
    return c1.index == c2.index;
}
bool operator != (const page &c1, const page &c2) {
    return c1.index != c2.index;
}

page* intArrToPageArr(int* arr, int arrLen);
int countProximity(page* pagePointer, int arrLen, int index);
template <typename T> bool beladi(T* pagePointer, int arrLen, int cacheCapacity, std::list <T> &myList, std::unordered_map <int, T> &myMap);
int caching(page* pageArr, int arrLen, int cacheCapacity);
template <typename T>  typename std::unordered_map <int, T>::iterator findElemMaxProximity(T* pagePointer, int arrLen, std::unordered_map <int, T> myMap);

int main() {
    int cacheCapacity = 0;
    int arrLen = 0;
    std::cin >> cacheCapacity;
    std::cin >> arrLen;
    int* numArr = new int[arrLen];
    for(int i = 0; i < arrLen; i++) {
        std::cin >> numArr[i];
    }
    page* pageArr = intArrToPageArr(numArr, arrLen);
    int cacheHit = caching(pageArr, arrLen, cacheCapacity);
    std::cout << cacheHit << '\n';
    delete[] pageArr;
    delete[] numArr;
}
page* intArrToPageArr(int* arr, int arrLen) {
    page *pageArr = new page[arrLen];
    for (int i = 0; i < arrLen; i++) {
        pageArr[i].index = arr[i];
    }
    return pageArr;
}
int caching(page* pageArr, int arrLen, int cacheCapacity) {
    int cacheHitCount = 0;
    std::list <page> myList;
    std::unordered_map <int, page> myMap;
    for (int i = 0; i < arrLen; i++){
        cacheHitCount += beladi(pageArr + i, arrLen - i, cacheCapacity, myList, myMap);
    }
    return cacheHitCount;
}
template <typename T> bool beladi(T* pagePointer, int arrLen, int cacheCapacity, std::list <T> &myList, std::unordered_map <int, T> &myMap){
    auto hit = myMap.find(pagePointer[0].index);
    if (hit == myMap.end()) {
        if (myList.size() >= cacheCapacity) {
            auto toBeDeleted = findElemMaxProximity(pagePointer, arrLen, myMap);
            myMap.erase((*toBeDeleted).first);
            myList.remove((*toBeDeleted).second);
        }
        myList.push_front(pagePointer[0]);
        myMap[pagePointer[0].index] = *myList.begin();
        return false;
    }
    return true;
}
int countProximity(page* pagePointer, int arrLen, int index) {
    int count = 0;
    for (count = 0; count < arrLen; count++) {
        if(pagePointer[count].index == index) {
            break;
        }
    }
    return count;
}
template <typename T>  typename std::unordered_map <int, T>::iterator findElemMaxProximity(T* pagePointer, int arrLen, std::unordered_map <int, T> myMap) {
    for (int i = 0; i < arrLen; i++){
        if (myMap.size() == 1)
            break;
        if (myMap.find(pagePointer[i].index) != myMap.end()){
            myMap.erase(pagePointer[i].index);
        }
    }
    return myMap.begin();
}
