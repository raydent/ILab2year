#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
const int K = 1;
struct page {
    int index;
    char data[60];
};

bool operator == (const page c1, const page c2) {
    return c1.index == c2.index;
}
bool operator != (const page c1, const page c2) {
    return c1.index != c2.index;
}
page* intArrToPageArr(int* arr, int arrLen);
int countProximity(page* pagePointer, int arrLen, int index);
bool beladi(page* pagePointer, int arrLen, int cacheCapacity, std::list <page> &myList, std::unordered_map <int, page> &myMap);
int caching(page* pageArr, int arrLen, int cacheCapacity);
std::list<page>::iterator findElemMaxProximity(page* pagePointer, int arrLen, std::list <page> &myList);
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
bool beladi(page* pagePointer, int arrLen, int cacheCapacity, std::list <page> &myList, std::unordered_map <int, page> &myMap) {
    auto hit = myMap.find(pagePointer[0].index);
    if (hit == myMap.end()) {
        if (myList.size() >= cacheCapacity) {
            auto toBeDeleted = findElemMaxProximity(pagePointer, arrLen, myList);
            myMap.erase(toBeDeleted -> index);
            myList.remove(*toBeDeleted);
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
std::list<page>::iterator findElemMaxProximity(page* pagePointer, int arrLen, std::list <page> &myList) {
    std::list<page>::iterator maxIt = myList.end();
    int proximity = 0;
    int maxProximity = 0;
    for(std::list <page> ::iterator it = myList.begin(); it != myList.end(); ++it) {
        if(arrLen != 0) {
            proximity = countProximity(pagePointer + 1, arrLen - 1, it -> index);
            if (proximity > maxProximity) {
                maxIt = it;
                maxProximity = proximity;
            }
        }
    }
    return maxIt;
}
