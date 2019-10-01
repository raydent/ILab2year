#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>



int main(){
    FILE* f = fopen("sawtest.txt", "w");
    int arrLen = 100;
    int cacheCapacity = 6;
    int dispersion = 20;
    fprintf(f, "%d %d ", cacheCapacity, arrLen);
    std::cout << arrLen << ' ' << cacheCapacity << ' ';
    srand(4541);
    int peaksnum = 4;
    for(int i = 0; i < peaksnum; i++){
        int peakval = rand() % 500;
        int sign = 1;
        for(int k = i * (arrLen / peaksnum); k < (i + 1) * (arrLen / peaksnum); k++){
            if (rand() % 2 == 1){
                sign == -1;
            }
            else {
                sign = 1;
            }
            fprintf(f, "%d ", peakval + sign * (rand() % dispersion));
        }
    }
}
