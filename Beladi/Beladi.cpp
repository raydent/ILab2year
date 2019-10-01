#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>
#include <map>

struct page {
    int index;
    // char data[60];
};
struct myHash {
    std::size_t operator()(page const& myPage) const noexcept
    {
        // std::size_t h1 = std::hash<std::string>{}(s.first_name);
        // std::size_t h2 = std::hash<std::string>{}(s.last_name);
        // return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
        std::size_t h = std::hash < int > {
        }
        (myPage.index);
        return h;
    }
};
template < typename T > struct fullCache {
    int cacheCapacity;
    std::unordered_map < int, page > myMap;
    std::unordered_multimap < page, int, myHash > numMap;
    std::list< page > myList;
};
//  template<> struct std::hash <page p> {
//     return std::hash<int>(p.index);
// };

bool operator == (const page &c1, const page &c2) {
    return c1.index == c2.index;
}
bool operator != (const page &c1, const page &c2) {
    return c1.index != c2.index;
}


template < typename T >
bool beladi(T* pagePointer, const int& arrLen, fullCache < T > & cache, int i);
int caching(std::vector < page >& pageArr, const int& arrLen, const int& cacheCapacity);
template < typename T >
auto findElemMaxProximity(T* pagePointer, const int& arrLen, std::unordered_map < int, T > & myMap, std::unordered_multimap < T, int, myHash > & numMap);

int main() {
    int cacheCapacity = 0;
    int arrLen = 0;
    std::cin >> cacheCapacity;
    std::cin >> arrLen;
    std::vector < page > pageArr(arrLen);
    for(int i = 0; i < arrLen; i++) {
        std::cin >> pageArr[i].index;
    }
    int cacheHit = caching(pageArr, arrLen, cacheCapacity);
    std::cout << cacheHit << '\n';
}
int caching(std::vector < page >& pageArr, const int& arrLen, const int& cacheCapacity) {
    int cacheHitCount = 0;
    fullCache <page> cache;
    cache.cacheCapacity = cacheCapacity;
    for(int i = 0; i < arrLen; i++) {
        // cache.numMap[pageArr[i]] = i;
        cache.numMap.insert(std::make_pair(pageArr[i], i));
        //printf("%d\n", cache.numMap[pageArr[i]]);
    }
    printf("%d\n", (int)cache.numMap.size());
    for (int i = 0; i < arrLen; i++) {
        cacheHitCount += beladi(&(pageArr[i]), arrLen - i, cache, i);
        cache.numMap.erase(pageArr[i]);
    }
    return cacheHitCount;
}
template < typename T >
bool beladi(T* pagePointer, const int& arrLen, fullCache < T > & cache, int i) {
    auto hit = cache.myMap.find(pagePointer[0].index);

    printf("%d\n", (int)cache.numMap.size());
    typedef std::unordered_multimap<page, int, myHash>::iterator iterator;
    std::pair<iterator, iterator> iterpair = cache.numMap.equal_range(pagePointer[0]);

    // Erase (b,15) pair
    //
    iterator it = iterpair.first;
    for (; it != iterpair.second; ++it) {
        if (it->second == i) {
            cache.numMap.erase(it);
            printf("element range is %d, range is %d id is %d\n", it -> second, i, pagePointer[0].index);
            break;
        }
    }
    if (hit == cache.myMap.end()) {
        if (cache.myList.size() >= cache.cacheCapacity) {
            auto toBeDeleted = findElemMaxProximity(pagePointer, arrLen, cache.myMap, cache.numMap);
            cache.myMap.erase((*toBeDeleted).first);
            cache.myList.remove((*toBeDeleted).second);
        }
        //cache.numMap.erase(pagePointer[0]);
        cache.myList.push_front(pagePointer[0]);
        cache.myMap[pagePointer[0].index] = *cache.myList.begin();
        return false;
    }
    return true;
}
template < typename T >
auto findElemMaxProximity(T* pagePointer, const int& arrLen, std::unordered_map < int, T > & myMap, std::unordered_multimap < T, int, myHash > & numMap) {

    int maxproximity = 0;
    auto maxIt = myMap.begin();
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        auto numIt = numMap.find(it -> second);
        //printf("%d ", it -> second.index);
        if (numIt != numMap.end()) {
            //printf("%d\n", numIt -> second);
            if (numIt -> second > maxproximity) {
                maxproximity = numIt -> second;
                maxIt = it;
            }
        }
    }
    return maxIt;
    //return myMap.begin();
}
