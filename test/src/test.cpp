#include <test.h>
#include <thread>
#include <string>

Msg Compare(const int *A, const int *B, uint32_t len){
    Msg res = OK;
    for(uint32_t i = 0; i < len; i++){
        if(A[i] != B[i]){
            res = FAIL;
            break;
        }
    }
    return res;
}


/* Tets without myltithreading*/
Msg test1(){
    Buffer myBuffer(32);
    int A[8] = {1,2,3,4,5,6,7,8}; // int = 4 bytes => 8*4 = 32 bytes
    int B[8]; 
    unsigned int ren1 = myBuffer.addBytes((uint8_t *)A, sizeof(A));
    unsigned int ren2 = myBuffer.readBytes((uint8_t *)B, sizeof(B));
    if((ren1 == sizeof(A) ) && (ren2 == sizeof(B)) && Compare(A,B,8))
        return OK;
    else
        return FAIL;
    
};

Msg test2(){
    Buffer myBuffer(16);
    int A[8] = {1,2,3,4,5,6,7,8}; // int = 4 bytes => 8*4 = 32 bytes
    int B[8]; 
    unsigned int ren1 = myBuffer.addBytes((uint8_t *)A, sizeof(A));
    unsigned int ren2 = myBuffer.readBytes((uint8_t *)B, sizeof(B));
    if((ren1 == 16 ) && (ren2 == 16) && Compare(A,B ,4))
        return OK;
    else
        return FAIL;
    
};

Msg test3(){
    Buffer myBuffer(16);
    int A[8] = {1,2,3,4,5,6,7,8}; // int = 4 bytes => 8*4 = 32 bytes
    myBuffer.addBytes((uint8_t *)A, sizeof(A));
    unsigned int ren1 = myBuffer.addBytes((uint8_t *)A, sizeof(A));

    if(ren1 == 0 )
        return OK;
    else
        return FAIL;
};

Msg test4(){
    Buffer myBuffer(16); 
    int B[8];
    unsigned int ren2 = myBuffer.readBytes((uint8_t *)B, sizeof(B));
    if(ren2 == 0 )
        return OK;
    else
        return FAIL;
};


Msg test5(){
    Buffer myBuffer(32);
    int A[8] = {1,2,3,4,5,6,7,8}; // int = 4 bytes => 8*4 = 32 bytes
    int B[8]; 
    int B_[5] = {3,4,1,2,5}; 
    unsigned int ren1 = myBuffer.addBytes((uint8_t *)A, sizeof(A[0])*7);
    unsigned int ren2 = myBuffer.readBytes((uint8_t *)B, sizeof(B[0])*5);
    unsigned int ren3 = myBuffer.addBytes((uint8_t *)A, sizeof(A[0])*4);
    unsigned int ren4 = myBuffer.readBytes((uint8_t *)B, sizeof(B[0])*4);
    unsigned int ren5 = myBuffer.readBytes((uint8_t *)B, sizeof(B[0])*4);

    if( (ren1 == sizeof(A[0])*7) && \
        (ren2 == sizeof(B[0])*5) && \
        (ren3 == sizeof(A[0])*4) && \
        (ren4 == sizeof(B[0])*4) && \
        (ren5 == sizeof(B[0])*2) && \
        Compare(B_, B ,5)
        )
        return OK;
    else
        return FAIL;
    
};


Msg test6(){
    unsigned int len = 32; // 8*sizeof(int)
    Buffer myBuffer(len); 
    int A[8] = {1,2,3,4,5,6,7,8};

    myBuffer.addBytes((uint8_t *)A, sizeof(A[0])*2);
    unsigned int ren1 = myBuffer.getQuantityEmptyBytes();
    myBuffer.addBytes((uint8_t *)A, sizeof(A[0])*4);
    unsigned int ren2 = myBuffer.getQuantityEmptyBytes();
    myBuffer.addBytes((uint8_t *)A, sizeof(A[0])*8);
    unsigned int ren3 = myBuffer.getQuantityEmptyBytes();
    if( (ren1 == len - sizeof(A[0])*2) && \
        (ren2 == len - sizeof(A[0])*6) && \
        (ren3 == 0) \
     )
        return OK;
    else
        return FAIL;
};

Msg test7(){
    Buffer buf1(0);
    Buffer buf2(10);
    Buffer buf3(1000);
    if( (buf1.getLength() == 0) && \
        (buf2.getLength() == 10) && \
        (buf3.getLength() == 1000)\
     )
        return OK;
    else
        return FAIL;
}

/* Tets with myltithreading*/

Msg test8(){
    std::string str1 = "The class thread represents a single thread of execution. Threads allow multiple functions to execute concurrently. \
Threads begin execution immediately upon construction of the associated thread object (pending any OS scheduling delays), starting at the top-level function provided as a constructor argument. The return value of the top-level function is ignored and if it terminates by throwing an exception, std::terminate is called. The top-level function may communicate its return value or an exception to the caller via std::promise or by modifying shared variables (which may require synchronization, see std::mutex and std::atomic) \
std::thread objects may also be in the state that does not represent any thread (after default construction, move from, detach, or join), and a thread of execution may be not associated with any thread objects (after detach).\
No two std::thread objects may represent the same thread of execution; std::thread is not CopyConstructible or CopyAssignable, although it is MoveConstructible and MoveAssignable.";
    std::string str2 = "The mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.\
mutex offers exclusive, non-recursive ownership semantics:\
A calling thread owns a mutex from the time that it successfully calls either lock or try_lock until it calls unlock.\
When a thread owns a mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the mutex.\
A calling thread must not own the mutex prior to calling lock or try_lock.\
The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, or a thread terminates while owning a mutex. The mutex class satisfies all requirements of Mutex and StandardLayoutType.\
std::mutex is neither copyable nor movable.";
    Buffer myBuffer(sizeof(str1)+sizeof(str2));
    bool start_flag = 0;

    std::thread t1([&myBuffer,&str1, &start_flag](){
        while(start_flag==0);
        myBuffer.addBytes((uint8_t *)&str1, sizeof(str1));       
    });
    std::thread t2([&myBuffer,&str2,&start_flag](){
        start_flag = 1;
        myBuffer.addBytes((uint8_t *)&str2, sizeof(str2));       
    });

    t1.join();
    t2.join();

    std::string str1_;
    std::string str2_;
    myBuffer.readBytes((uint8_t *)&str1_, sizeof(str1));
    myBuffer.readBytes((uint8_t *)&str2_, sizeof(str2));
    if( (str1 == str2_) && (str2 == str1_)) 
        return OK;
    else
        return FAIL;
       

}

int test(){
    Msg msg;

    cout << "1 - Ok; 0 - FALIL" << endl;

    //test addBytes and readBytes
    cout << "test1: " << test1() << endl;
    cout << "test2: " << test2() << endl;
    cout << "test3: " << test3() << endl;
    cout << "test4: " << test4() << endl;
    cout << "test5: " << test5() << endl;
        
    //test other methods
    cout << "test6: " << test6() << endl;
    cout << "test7: " << test7() << endl;

    //test multithreading
    cout << "test8: "  << test8() <<endl;

    return OK;
}