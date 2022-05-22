notes about C programming 

# C-string 
```C++
    char s [] = "Hello";
    char* sg  = "Hello"; // global var space (non-writable constant)
    cout << (void*)s << endl; 
    cout << (void*)sg << "==" << (void*)"Hello" << endl;  // return same address by compilier optimization
// output : 
// 0x7ffc05d56aa2
// 0x55c5e4b43005==0x55c5e4b43005
```
---
# check if file exist
an efficient way to chek if a file exising is using stat system call
```C
static bool checkIfFileExists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    return (exist == 0);
}
```