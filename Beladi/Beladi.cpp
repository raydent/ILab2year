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

bool operator == (page c1, page c2)
{
    return c1.index == c2.index;
}
struct listWithCapacity {
  std::list <page> myList;
  int cacheCapacity;
};
page* intArrToPageArr(int* arr, int arrLen);
int countProximity(page* pagePointer, int arrLen, int index);
int Beladi(page* pagePointer, int arrLen, std :: unordered_map <int, page> map, listWithCapacity myList);
int caching(page* pageArr, int arrLen, int cacheCapacity);
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
  int cacheHit = caching(pageArr, arrLen, cacheCapacity);
  std::cout << cacheHit;
  // for(int i = 0; i < arrLen; i++){
  //   std::cout << numArr[i] << ' ';
  // }
}
page* intArrToPageArr(int* arr, int arrLen){
  page *pageArr = new page[arrLen];
  for (int i = 0; i < arrLen; i++){
    pageArr[i].index = arr[i];
  }
  return pageArr;
}
int caching(page* pageArr, int arrLen, int cacheCapacity){
  int listCurrentCapacity;
  int cacheHit = 0;
  listWithCapacity myList;
  std::list <page> list;
  myList.cacheCapacity = cacheCapacity;
  myList.myList = list;
  std :: unordered_map <int, page> map;
  for(int i = 0; i < arrLen; i++){
    cacheHit += Beladi(pageArr + i, arrLen - i, map, myList);
  }
  return cacheHit;
}
int Beladi(page* pagePointer, int arrLen, std :: unordered_map <int, page> map, listWithCapacity myList){
  //auto state = map.find(pagePointer[0].index);
  if(map.find(pagePointer[0].index) == map.end()){
    if (myList.myList.size() < myList.cacheCapacity){
      myList.myList.push_front(pagePointer[0]);
      map.insert({pagePointer[0].index, myList.myList.front()});
    }
    else {
      assert(myList.myList.size() == myList.cacheCapacity);
      auto frontPage = myList.myList.begin();
      auto curPage = frontPage;
      std::list<page>::iterator toBeDeleted = frontPage;
      int maxProximity = 0;
      int proximity = 0;
      proximity = countProximity (pagePointer, arrLen, pagePointer[0].index);
      if (proximity > maxProximity){
        maxProximity = proximity;
        toBeDeleted = curPage;
      }
      curPage = std::next(curPage, 1);
      while(curPage != frontPage){
        proximity = countProximity (pagePointer, arrLen, pagePointer[0].index);
        if (proximity > maxProximity){
          maxProximity = proximity;
          toBeDeleted = curPage;
        }
        curPage = std::next(curPage, 1);
      const page& deleting = *(toBeDeleted);
      int indexToBeDeleted = toBeDeleted -> index;
      myList.myList.remove(*toBeDeleted);
      myList.myList.push_front(pagePointer[0]);
      map.erase(indexToBeDeleted);
      map.insert({pagePointer[0].index, myList.myList.front()});
      }
    return 0;
    }
  }
  else{
    return 1;
  }
}
int countProximity(page* pagePointer, int arrLen, int index){
  int count = 0;
  for (count = 0; count < arrLen; count++){
    if(pagePointer[count].index == index){
      break;
    }
  }
  return count;
}
