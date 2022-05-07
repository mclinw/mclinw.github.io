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
# if file exist
```C
static bool checkIfFileExists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    return (exist == 0);
}
```