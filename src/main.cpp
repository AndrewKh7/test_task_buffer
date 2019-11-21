#include <iostream>
#include <main.h>


using namespace std;
template<typename T>
void printArray(const T *arr, uint32_t len){
    for(uint32_t i = 0; i < len; i++)
        cout << ' ' <<arr[i];
    cout << endl;
}

int main(){
    cout << "Program started!" << endl;
    #ifdef DEBUG
        test();
    #endif
    return 0;
}