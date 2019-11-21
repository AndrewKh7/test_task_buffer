#include <test.h>

Msg Compare(const uint8_t *A, const uint8_t *B, uint32_t len){
    Msg res = OK;
    for(uint32_t i = 0; i < len; i++){
        if(A[i] != B[i]){
            res = FAIL;
            break;
        }
    }
    return res;
}

Msg test1(){
    Buffer myBuffer(32);
    int A[8] = {1,2,3,4,5,6,7,8};
    int B[8]; 
    myBuffer.addBytes((uint8_t *)A, sizeof(A));
    myBuffer.readBytes((uint8_t *)B, sizeof(B));
    return Compare((uint8_t*)A, (uint8_t*)B ,8);
};


int test(){
    Msg msg;
    cout << "1 - Ok; 0 - FALIL" << endl;
    cout << "test1: " << test1() << endl;
    
        
    

    return OK;
}