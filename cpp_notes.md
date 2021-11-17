# C/C++ questions
## size of Primitive Data Types
C stacndard only defines min size for primitive data types. 

2 <= sizeof(short) <= sizeof(int) <= sizeof(long) >= 4

note, long / pointer / size_t (unsigned type) are platform-dependency (32-bits/64-bits)

## padding, alignment, union
Variable access shall be aligned according to CPU architecture spec. As a result, padding is needed between struct vars.
reference: https://magicjackting.pixnet.net/blog/post/221968938

```C
//32-bit machine , 1-byte padding bt ch and sz (uint16 must align to 2)
    struct {
        uint8_t  ch;
        uint16_t sz;
    } st1;

//32-bit machine , 3-byte padding bt ch and sz  (uint16 must align to 4)
    struct {
        uint8_t  ch;
        uint32_t sz;
    } st2;
```

## pointer & reference
```C
int A[3];// array of 3 ints
int* A[3]; // array of 3 pointers to int
int (*A) [3]; //pointer to an array of 3 int elements
int (&A) [3]; //reference to an array of 3 int elements
Int& [3] ; // x 

int *& p ;// reference to int pointer (int*)
```
* Difference bt reference and pointer : reference can’t be changed.  
    >That’s why there must be assigned an initial value while reference declared.
```C++
int a = 1;
int b =2;

int &ref = a; 
ref = b; // meaning is the same as a=2

int &ref;  // error: no initialization
```

### const char const * const c_ptr;
```C
const char *p; //pointer to constant char
char *const p;  // constant pointer

// constant pointer points to an constant char
const char *const p;
char const *const p;

//find error
const char* p1;	// pointer to const char*
char *const p2;	// error ! uninitialized const pointer
p1 = “abc”;
p2 = “abc”;//error: assignment of read-only variable ‘p2’
```

## call by value, call by reference (address) 
In the call by value method, a copy of the parameter is passed to the functions. For these copied values a new memory is assigned and changes made to these values do not reflect the variable in the main function.
In call by reference method, we pass the address of the variable and the address is used to access the actual argument used in the function call. So changes made in the parameter alter the passing argument.

## function pointer 
```C++
void fun(int a){ cout << a << endl; }

// fun_ptr is a pointer to function fun() 
void (*fun_ptr)(int) = &fun;  

// A function’s name can also be used to get functions’ address. For example, in the below program, we have removed address operator ‘&’ in assignment. We have also changed function call by removing *, the program still works.
void (*fun_ptr)(int) = fun;  

// 2 ways to Invoking fun() using fun_ptr
(*fun_ptr)(10);
fun_ptr(10);

//function pointer做為函式的參數
typedef void (*fun_ptr)(int);
int call_a_func2(fun_ptr call_this) {
    int output = call_this(7);
    return output;
}
// 不使用typedef的原始宣告方法
int call_a_func2(int (*call_this)(int)) {
    int output = call_this(7);
    return output;
}
call_a_func2(fun) ; 
```
<!-- 
```C++
// array of function pointers
void add(int a, int b)
{
    printf("Addition is %d\n", a+b);
}
void subtract(int a, int b)
{
    printf("Subtraction is %d\n", a-b);
}
void multiply(int a, int b)
{
    printf("Multiplication is %d\n", a*b);
}
// fun_ptr_arr is an array of function pointers
    void (*fun_ptr_arr[])(int, int) = {add, subtract, multiply};
   (*fun_ptr_arr[ch])(a, b);
``` -->
## difference between struct and class?
Answer: default access level different. struct public members by default, whlie class public private members by default 
## post-increment ‘itr++’ v.s. pre-increment ‘++itr’ operator.
post-increment ‘itr++’ operator is more expensive than the pre-increment ‘++itr’ operator.
The post-increment operator generates a copy of the element before proceeding with incrementing the element and returning the copy. Moreover, most compilers will automatically optimize i++ by converting it implicitly into ++i
## C++ memory allocation
* operator new/delete: similar to malloc/free in C in allocate raw memory in heap
* new operator/ delete operator  (expression): C++ Memory allocation
>‘new operator’ calls ‘operator new’ to allocate raw memory, then call constructor.
>‘delete operator’ calls dstor then call  ‘operator ‘delete to free memory in heap. 
```C++
X  *a  = new X() ;  // 2 steps: 1) call operator new + 2) call constructor
// X *a = new (operator new(sizeof(X)) X();
delete a ;  // 1) call destructor + 2) call operator delete
// a->~X();
// operator delete(a)

X *a  = new X[2] ; 
// void* buf = operator new[](3*sizeof(X));
// X *a = static_cast<X*>buf;
// for (int i = 0 ; i < 3; ++i) new (a+i) X; // placement new 

delete [] a ;
// for (int i = 0 ; i < 3; ++i) a[i].~X();
// operator delete[](a)
```
**Placement new operator**: a special version of operator new that allocates storage from a preallocated, large block of memory (this version already in #include<new>)

New operator syntax with placement new 
```C++
new (address) (type) initializer
```

As we can see, we can specify an address
where we want a new object of given type 
to be constructed.

```C++
X *a  = new (address) X() ;  // placement new 
delete a ; 
X *ar  = new (address) X[3] ;  // placement new 
delete [] ar ; 
```

The deallocation is done using delete operation when allocation is done by new but there is no placement delete, but if it is needed one can write it with the help of destructor
In general , placement new means an operator new overload version with extra argument , not required to be allocated address. [effective C++]

## template
A feature of the C++ programming language (template metaprogramming) that allow functions and classes to operate with generic types. This allows a function or class to work on many different data types without being rewritten for each one.
```C++
template<class X>//can replace 'class" keyword by "typename" keyword
X func( X a,X b) {return a;}
```
## difference between overloading V.S. template?
* Function templates make the function perform the same task for different data types.
* Function overloading makes the function to performs different task for different parameters you are passing.

## exception handling
a programming language construct designed to handle the occurrence of exceptions, special conditions that change the normal flow of program execution.
In general, an exception is handled (resolved) by saving the current state of execution in a predefined place and switching the execution to a specific subroutine known as an exception handler. Depending on the situation, the handler may later resume the execution at the original location using the saved information. For example, a page fault will usually allow the program to be resumed, while a division by zero might not be resolvable transparently.
```C++
try {
  // Block of code to try
  throw exception; // Throw an exception when a problem arise
}
catch () {
  // Block of code to handle errors
}
// throw exception could be any type like integer , string or object
throw 0;
throw “error”;
throw string(“error”);
throw exc_obj ;  // user-defined exception object , you can also declare exception obj by inherited std::exception
/* 
exception is catched by type using catch clauses.
The type of the exception object is compared against the exception declaration of each catch clause in turn unfile type match. the body if the catch clause is executed.
*/ 
try {
//throw exception; // Throw an exception when a problem arise
} catch (int i) {
    cerr << i <<end;
} catch (const char *msg) {
    cerr << msg <<end;
} catch (string &msg) {
    cerr << msg <<end;
} catch (user_obj &e) {    // any user-defined object
} catch (invalid_argument &e) {
    /*standard exception object inherited from std::exception with a member function what() to return error message */
    cerr << e.what() << endl;    
} catch (bad_alloc) {
/*
also can match a class type bad_alloc without declare an exception object because we are 
interested only in catching the exception type and not in actually manipulation the object in catch clause 
*/
    cerr << “heap memory exhausted\n” ;
}  
catch (...) {
// others not catch above 
}
```
### header stdexcept vs exception in c++
    * exception: Defines the base class (i.e., std::exception) for all exceptions thrown by the elements of the standard library, along with several types and utilities to assist handling exceptions.
    * stdexcept : Defines a set of standard exceptions that both the library and programs can use to report common errors.
```C++
#include <stdexcept>	
  throw invalid_argument("MyFunc argument too large.");
```
reference: https://stackoverflow.com/questions/25163105/stdexcept-vs-exception-headers-in-c

##  polymorphism 
The two types of polymorphism in c++ are:
1. Compile Time (static) Polymorphism: operation overloading/function overloading including template [effective C++ #41]
2. Runtime (dynamic) Polymorphism: virtual function

### What is the difference bt overload & override?
* override: same func name, choose func depend on object type 
base is virtual (runtime polymorphism)
* overload: same func name, choose func depend on diff parameters list

### operator overloading is compile-time polymorphism [effective C++ #41] 
In computer programming, operator overloadingis a specific case of polymorphism in which some or all of doperators like +, =, or == have different implementations depending on the types of their 		arguments.

### [Advanced] What is the 'override' keyword in C++ used for? 
The override[C++11] keyword serves two purposes:
1. It shows the reader of the code that "this is a virtual method, that is overriding a virtual method of the base class."
2. The compiler also knows that it's an override, so it can "check" that you are not altering/adding new methods that you think are overrides.
```C++
class base
{
  public:
    virtual int foo(float x) = 0;
};
class derived: public base
{
   public:
     int foo(float x) override { ... } // OK
}
class derived2: public base
{
   public:
     int foo(int x) override { ... } // ERROR: parameter list is different to base declaration
};
```
In derived2 the compiler will issue an error for "changing the type". Without override, at most the compiler would give a warning for "you are hiding virtual method by same name".

### virtual: dynamic binding
Let base class pointer / reference can transparently points to any derived class
* virtual destructor : only declare a virtual destructor if a class is designed to be inherited. [Effective C++ #7].

notes: 
* the destruction behavior is undefined if use base pointer points to derived instance
The sequence of calling destructors is from the **most derived to base**. ex: call destructor from derived class then call destructor of base class to avoid memory leakage 
```C++
#include <iostream>
using namespace std;
class Base{
public:
    virtual ~Base(){ cout << "Base"<< endl ; }
};
class Derive:public Base{
public:
    ~Derive()  {cout << "Derive"<< endl ;}
};
int main()
{
    Base *a = new Derive();
    delete a; 
    return 0;
}
/*
console output :
Derive
Base
*/
```
* virtual overhead : there is a virtual pointer in each class pointing to a virtual table. 
    > not declare any virtual member function if a class is not designed to be inherited - vtpr overhead (additional size of one pointer: 32-bit or 64-bit depends on machine)
* STL containers are not designed to be inherited, which means there is the destructor is not declared as virtual 
* pure virtual member function : for any Class with ANY pure virtual member function , that’s designed to be as abstract interface (not be instantiated)
```C++
class A{
public:
    virtual void foo()=0; // pure virtual
    A(){ cout<<"A "; }
    virtual ~A(){}
};
class B: public A
{
public:
    B(){ cout<<"B ";} 
    ~B(){}
}
A a ; // compile error: cannot declare variable ‘a’ to be of abstract type ‘A’
A *b = new B()  ; // compile error: construct can’t call A() .
```
## class access specifier public/protected/private

<!-- public/protected/private inheritance
inheritance->
base method
 |
V
public
protected
private
public method
public
protected
private
protected method
protected
protected
private
private method
X
X
X -->

## [Class] special member functions are declared/defined by compiler
Default constructor, copy constructor, assignment operator ,destructor ,address-of operator
if a class does not explicitly declare these member functions, compiler will:
1. implicitly declare them 
2. implicitly define them , if they are needed.
```C++
class X {
// public: 
//     X() ; //Default constructor 
//     X(const X&) ;//copy constructor 
//     ~X();// destructor 
//     X& operator=(const X&) ;//assignment operator
//     X* operator&() ;//address-of operator
}; 
```
## type conversion
### c style
```C
(Base_C) child_obj ? valid? YES // implicit type conversion
(Child_C) base_obj ? valid? NO
```
### c++ style
1.  static_case:**implicit** conversions between types (like int to float)
2.  const_cast: remove const
3.  reinterpret_cast: low level conversion like convert pointer to int (platform-dependency)
4. dynamic_case (安全向下轉型): save downcase to convert a base ptr to derived ptr. very slow
   * if you only have a base* point to an derived object, you want to execute derived member function , need to converted to derived.
   * [Advanced]: typeid operator to provide runtime identification, typeid returns type_info object to represent real class type  [Essential C++ P.164]
```C++
#include <typeinfo> // typeid operator
class B {
    public:
    virtual string who_am_i ()  { return typeid(*this).name() ; }
}; 
class D:public B {}; 
int test::cast()
{
    B* b = new B();
    cout << b->who_am_i()  << endl ;  //1B
    B* d = new D(); //1B
    cout <<  d->who_am_i()  << endl ;  //1D
    cout  << typeid(*b).name() << typeid(B).name() << endl ; //1B1B
    cout  << typeid(*d).name() << typeid(D).name() << endl ; //1D1D
    return 0 ;     
}
```
## C++ keywords : auto [C++11], extern, mutable, static
* auto [C++11]: 新的變數類型，讓編譯器自動判斷其變數的類型
1. compiler to determine the data type 
2. Initial is necessary. Otherwise, the compiler is not able to know the type.
```C++
auto x = 1;// 等同於 int x = 1;
auto y = sin(1.3);  // 等同於 double y = sin(1.3);
for(auto it = v.begin() ; it 1= v.end() ;++i) ; 
```
* extern: tell the compiler this var or function already be declared in another file (translation unit)
* mutable: A member data is declared as mutable , that means even a constant member function could change its value.
    > for logical constantness [effective c++]
* static 
```C
void f()
{
    static int i = 0; // is initialed when 1st time execution to this func
    printf(“%d ”,i++);
}
int main()
{
    for(int i=0;i<100;i++) f();
    return 0;
}
//output result: 0 1 2 ...99
```

# OO and Design
* 甚麼是《物件導向設計》?
    >《物件導向設計》最重要的精神是**模組化**(Modularity)與簡潔介面必須被**封裝**(Encapsulation)
**抽象**(Abstraction)資料型別保證只能被適當的方法操作
類別間的**繼承**（Inheritance）**組合**(Composition)，把曾經做過的東西加以設定並組合，以減輕工作量，同時減少錯誤發生的機會

* [封裝 encapsulation](http://www.parashift.com/c++-faq-lite/classes-and-objects.html#faq-7.4)
	Preventing unauthorized access to some piece of information or functionality.
The key money-saving insight is to separate the volatile part of some chunk of software from the stable part.
* [抽象 abstraction](http://en.wikipedia.org/wiki/Abstraction_(computer_science))
	The mechanism and practice of abstraction reduces and factors out details so that one can focus on a few concepts at a time. (abstraction - a concept or idea not associated with any specific instance)
* [繼承 inheritance](http://en.wikipedia.org/wiki/Inheritance_(computer_science))
	Inheritance is a way to compartmentalize and reuse code by creating collections of attributes and behaviors called objects which can be based on previously created objects.
* [多型 polymorphism](http://en.wikipedia.org/wiki/Type_polymorphism)
A programming language feature that allows values of different data types to be 		handled using a uniform interface.

## forbid to generate a object in stack
private constructor or private destructor

```C++
//related topic: singleton pattern
class singleton {
public:
    static singleton*  get_singleton() ;
protect :  //if design to be inherited 
    singleton (); // constructor 
private : 
    static  singleton*  _single ; 
}
```

## once-only header ( wrapper #ifndef )
If a header file happens to be included twice, the compiler will process its contents twice. This is very likely to cause an error, e.g. when the compiler sees the same structure definition twice. Even if it does not, it will certainly waste time.
The standard way to prevent this is to enclose the entire real contents of the file in a conditional, like this:
```C
/* File foo.  */
#ifndef FILE_FOO_SEEN
#define FILE_FOO_SEEN

the entire file

#endif /* !FILE_FOO_SEEN */
```
reference : https://gcc.gnu.org/onlinedocs/cpp/Once-Only-Headers.html

# fix or find error 
```C
void RemoveHead(node *head)
{
    free(head);
    head = head->next;
}
//fixed: 
void RemoveHead(node *head)
{
    node* tmp = head;
    head = head->next;
    free(tmp);
}
```
```C++
//find error?
class A
{
public:
    A(int a):_x(a),_y(_x){}
    int _y; 
    int _x; 
}
```
Answer: non-static data members are initialized **in the order they were declared** in the class definition (again regardless of the order of the mem-initializers).

```C++
char* a = new char[20];
delete a []; // delete [] a
```
```C++
string& print()
{
    string s(“abc”);
    return s; //error : return local var
}
// fix : return object when you should  [effective C++]
string print()
{
    string s(“abc”);
    return s; 
}
```
