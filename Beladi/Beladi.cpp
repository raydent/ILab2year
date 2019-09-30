#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>

#include "profile.h"

struct page {
	int index;
	char data[60];
};

template <typename T> struct fullCache {
	std::unordered_map <int, T> myMap;
	std::list<T> myList;
	int cacheCapacity;
};

bool operator == (const page& c1, const page& c2) {
	return c1.index == c2.index;
}
bool operator != (const page& c1, const page& c2) {
	return c1.index != c2.index;
}

template <typename T> 
bool beladi(T* pagePointer, const int& arrLen, fullCache<T>& cache);

int caching(std::vector<page> pageArr, int arrLen, int cacheCapacity);

template <typename T>
auto findElemMaxProximity(T* pagePointer, const size_t& arrLen, std::unordered_map <int, T>& myMap);

int main() {
	int cacheCapacity = 0;
	int arrLen = 0;
	std::cin >> cacheCapacity;
	std::cin >> arrLen;
	std::vector<page> pageArr(arrLen);
	LOG_DURATION("start");
	for (int i = 0; i < arrLen; i++) {
		std::cin >> pageArr[i].index;
	}
	LOG_DURATION("1");
	int cacheHit = caching(pageArr, arrLen, cacheCapacity);
	LOG_DURATION("2");
	std::cout << cacheHit << '\n';
}
int caching(std::vector<page> pageArr, const int arrLen, const int cacheCapacity) {
	int cacheHitCount = 0;
	fullCache<page> cache;
	for (int i = 0; i < arrLen; i++) {
		cacheHitCount += beladi(&(pageArr[i]), arrLen - i, cache);
	}
	return cacheHitCount;
}
template <typename T>
bool beladi(T* pagePointer, const int& arrLen, fullCache<T>& cache) {
	auto hit = cache.myMap.find(pagePointer[0].index);
	if (hit == cache.myMap.end()) {
		if (cache.myList.size() >= cache.cacheCapacity) {
			auto toBeDeleted = findElemMaxProximity(pagePointer, arrLen, cache.myMap);
			cache.myMap.erase((*toBeDeleted).first);
			cache.myList.remove((*toBeDeleted).second);
		}
		cache.myList.push_front(pagePointer[0]);
		cache.myMap[pagePointer[0].index] = *cache.myList.begin();
		return false;
	}
	return true;
}
int countProximity(page* pagePointer, const size_t& arrLen, const int& index) {
	int count = 0;
	for (count = 0; count < arrLen; count++) {
		if (pagePointer[count].index == index) {
			break;
		}
	}
	return count;
}
template <typename T>
auto findElemMaxProximity(T* pagePointer, const size_t& arrLen, std::unordered_map <int, T>& myMap) {
	for (int i = 0; i < arrLen; i++) {
		if (myMap.size() == 1)
			break;
		if (myMap.find(pagePointer[i].index) != myMap.end()) {
			myMap.erase(pagePointer[i].index);
		}
	}
	return myMap.begin();
}
