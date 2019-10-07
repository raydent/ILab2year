#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstring>
int stringtonum(char* string);

int main(int args, char* argv[]){
    FILE* f = fopen(argv[1], "w");
    int arrLen = stringtonum(argv[2]);
    int cacheCapacity = stringtonum(argv[3]);
    int dispersion = stringtonum(argv[4]);
    int peaksnum = stringtonum(argv[5]);
    //fprintf(f, "%d %d ", cacheCapacity, arrLen);
    std::cout << arrLen << ' ' << cacheCapacity << ' ';
    srand(std::time(nullptr));
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
int stringtonum(char* string){
    int n = 0;
    int pow = 0;
    for (int i = 0; i < strlen(string); i++){
        n = string[i] - '0' + n * 10;
    }
    return n;
}
