#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <queue>
struct page {
    int index;
    char data[60];
};
template <typename T>
struct cache_t {
  std::list<T>cache_;
  std::unordered_map <int, T*> index_;
  std::unordered_map <int, std::queue <int> > future_;
  int process(std::vector<T>& arr);
  void formFuture(const std::vector<T>& arr);
  bool beladi(T& thispage, cache_t<T>& cache);
  auto findElemMaxProximity(cache_t<T>& cache);
  int cacheCapacity;
};


bool operator == (const page &c1, const page &c2) {
    return c1.index == c2.index;
}
bool operator != (const page &c1, const page &c2) {
    return c1.index != c2.index;
}


int main() {
    int cacheCapacity = 0;
    int arrLen = 0;
    std::cin >> cacheCapacity;
    std::cin >> arrLen;
    std::vector <page> pageArr(arrLen);
    for(int i = 0; i < arrLen; i++) {
        std::cin >> pageArr[i].index;
    }
    cache_t <page> cache;
    cache.formFuture(pageArr);
    cache.cacheCapacity = cacheCapacity;
    int cacheHit = cache.process(pageArr);
    std::cout << cacheHit << '\n';
}

template <typename T>
int cache_t<T>::process(std::vector<T>& arr) {
    int cacheHit = 0;
    int size = arr.size();
    for(int i = 0; i < arr.size(); i++){
        cacheHit += beladi(arr[i], *this);
        future_[arr[i].index].pop();
    }
    return cacheHit;
}

template <typename T>
bool cache_t<T>::beladi(T& thispage, cache_t<T>& cache) {
    auto hit = cache.index_.find(thispage.index);
    if (hit == cache.index_.end()) {
        if (cache.cache_.size() >= cache.cacheCapacity) {
            auto toBeDeleted = findElemMaxProximity(cache);
            cache.index_.erase((*toBeDeleted).first);
            cache.cache_.remove(*(*toBeDeleted).second);
        }
        cache.cache_.push_front(thispage);
        cache.index_[thispage.index] = &*(cache.cache_.begin());
        return false;
    }
    return true;
}
template <typename T>
auto cache_t<T>::findElemMaxProximity(cache_t<T>& cache) {
    auto maxIt = cache.index_.begin();
    int maxprox = 0;
    for(auto it = cache.index_.begin(); it != cache.index_.end(); it++) {
        auto x = cache.future_[it -> first].front();
        if (x == 0){
            maxIt = it;
            break;
        }
        if (x  > maxprox) {
            maxprox = x;
            maxIt = it;
        }
    }
    return maxIt;
}
template <typename T>
void cache_t<T>::formFuture (const std::vector<T>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        future_[arr[i].index].push(i);
    }
}
