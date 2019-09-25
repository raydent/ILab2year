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
std::list <page> myList;
std::unordered_map <int, page> myMap;
bool operator == (page c1, page c2){
    return c1.index == c2.index;
}
bool operator != (page c1, page c2){
  return c1.index != c2.index;
}
page* intArrToPageArr(int* arr, int arrLen);
int countProximity(page* pagePointer, int arrLen, int index);
bool beladi(page* pagePointer, int arrLen, int cacheCapacity);
int caching(page* pageArr, int arrLen, int cacheCapacity);
std::list<page>::iterator findElemMaxProximity(page* pagePointer, int arrLen);
int main(){
  int cacheCapacity = 0;
  int arrLen = 0;
  std::cin >> cacheCapacity;
  std::cin >> arrLen;
  int numArr[arrLen];
  for(int i = 0; i < arrLen; i++){
    std::cin >> numArr[i];
  }
  page* pageArr = intArrToPageArr(numArr, arrLen);
  // for(int i = 0; i < arrLen; i++){
  //   std::cout << pageArr[i].index << '\n';
  // }
  int cacheHit = caching(pageArr, arrLen, cacheCapacity);
  std::cout << cacheHit << '\n';
  delete[] pageArr;
}
page* intArrToPageArr(int* arr, int arrLen){
  page *pageArr = new page[arrLen];
  for (int i = 0; i < arrLen; i++){
    pageArr[i].index = arr[i];
  }
  return pageArr;
}
int caching(page* pageArr, int arrLen, int cacheCapacity){
  int cacheHitCount = 0;
  for (int i = 0; i < arrLen; i++){
    cacheHitCount += beladi(pageArr + i, arrLen - i, cacheCapacity);
  }
  return cacheHitCount;
}
bool beladi(page* pagePointer, int arrLen, int cacheCapacity){
  auto hit = myMap.find(pagePointer[0].index);
  // std::cout << "mylist size = " << myList.size() << '\n';
  if (hit == myMap.end()) {
    // std:: cout << "map end\n";
    if (myList.size() >= cacheCapacity) {
      auto toBeDeleted = findElemMaxProximity(pagePointer, arrLen);
      myMap.erase(toBeDeleted -> index);
      myList.remove(*toBeDeleted);
    }
    myList.push_front(pagePointer[0]);
    myMap[pagePointer[0].index] = *myList.begin();
    //std::cout << myList.size() << '\n';
    return false;
  }
  auto eltit = hit->second;
  // if (eltit != *myList.begin()){
  //   myList.push_front(pagePointer[0]);
  //   myMap[pagePointer[0].index] = *myList.begin();
  // }
  return true;
}
// bool lookup(const T *elem) {
//   auto hit = hash_.find(elem->id);
//   if (hit == hash_.end()) {
//     if (full()) {
//       hash_.erase(cache_.back().id);
//       cache_.pop_back();
//     }
//     cache_.push_front(*elem);
//     hash_[elem->id] = cache_.begin();
//     return false;
// }
//   auto eltit = hit->second;
//   if (eltit != cache_.begin())
//     cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
//   return true;
// }
int countProximity(page* pagePointer, int arrLen, int index){
  int count = 0;
  for (count = 0; count < arrLen; count++){
    if(pagePointer[count].index == index){
      break;
    }
  }
  return count;
}
std::list<page>::iterator findElemMaxProximity(page* pagePointer, int arrLen){
  std::list<page>::iterator maxIt = myList.end();
  int proximity = 0;
  int maxProximity = 0;
  for(std::list<page>::iterator it = myList.begin(); it != myList.end(); ++it){
    if(arrLen != 0){
      proximity = countProximity(pagePointer + 1, arrLen - 1, it -> index);
      if (proximity > maxProximity){
        maxIt = it;
        maxProximity = proximity;
      }
    }
  }
  return maxIt;
}
