- [Modern C++](#modern-c)
  - [auto](#auto)
  - [constexpr](#constexpr)
  - [Enum class](#enum-class)
  - [Forwarding constructors](#forwarding-constructors)
  - [In-class initializers](#in-class-initializers)
  - [initializer list](#initializer-list)
- [move](#move)
  - [lvalue \& rvalue](#lvalue--rvalue)
  - [nullptr: Use nullptr instead of using 0 or NULL](#nullptr-use-nullptr-instead-of-using-0-or-null)
  - [override and final](#override-and-final)
  - [Range loop](#range-loop)
- [references](#references)


# Modern C++ 
features since C++11

## auto
---
## constexpr
* constexpr indicates a value that's constant and known during compilation.
* const indicates a value that's only constant; it's not compulsory to know during compilation.
```C++
int sz; 
constexpr auto arraySize1 = sz; // error! sz's value unknown at compilation 
std::array<int, sz> data1; // error! same problem 

constexpr auto arraySize2 = 10; // fine, 10 is a compile-time constant 
std::array<int, arraySize2> data2; // fine, arraySize2 is constexpr

const auto arraySize3 = sz; // fine, arraySize is const copy of sz 
std::array<int, arraySize3> data; // error! arraySize's value unknown at compilation 
```
* The constexpr specifier declares that it is possible to evaluate the value of the function or variable at compile time
```C++
struct S { 
    constexpr S(int);
}; 
const S s0(0);     // constructor called at runtime
constexpr S s1(1); // constructor called at compile time
```
---
## Enum class
Prefer scoped enum class to simple unscoped enum
Avoid name conflicts
Avoid implicit conversion to int
```C++
enum class Color { red, green = 20, blue }; 
Color r = Color::blue; 
switch(r) { 
  case Color::red :
    std::cout << "red\n"; 
    break; 
  case Color::green:
    std::cout << "green\n";
    break; 
  case Color::blue : 
    std::cout << "blue\n"; 
    break; 
} 
int n = r; // error: no scoped enum to int conversion 
Color r2 = 20; // error: no conversion from int to Color
int n = static_cast<int>(r); // OK, n = 21 
```
---
## Forwarding constructors
Those allow a constructor to “call” another one.  It is an alternative to specifying default value to parameters giving more flexibility.
```C++

class C {
public:
   C(int, std::string);
   C(std::string s) : C(0, s) { /* some more things */ }
};
```

---
## In-class initializers
More easily ensures that all the members are initialized in all the constructors.
```C++
class Trivial {
public:
   Trivial() = default;
   // some other constructors
private:
   int i_{0};
   int j_{42};
};
```
All constructors which do not specify an initial value for i_ or j_ are using the in-class specified one.

---
## initializer list
X x3{1, 1.2};


---
# move 
to understand move, we need to understand lvalue & rvalue first. 
## lvalue & rvalue
* lvalues and rvalues are not restricted to assignment statements; that's just where the names originate. It turns out that every value in your code is an lvalue or rvalue. 
    > To distinguish the two easily, ask yourself, "Does it have a name?" If it does, it's an lvalue (except for enumerators in an enumeration or non-type template parameters). Otherwise, it's an rvalue.
* Lvalues are addressable and rvalues are not. For instance, you can write &a, but not &42.
    > a = 42;    // lvalue = rvalue
* Before C++11, the notions of lvalue- and rvalue-ness of values was important to compiler writers, but there was no way to express such things in user code.
    >C++11 introduced rvalue references to enable move semantics and enable perfect forwarding.
* "Old style", "normal" references are lvalue references, written like T & or T const &.
    >Rvalue references use a double ampersand, like T && or T const &&.

https://vlsj-cqi01.cadence.com/tzlaine_talks/rvalues/slides/#/0/34
* If you write any of these operations, you probably need to write all of them, unless your type is move-only, or doesn't have a move that is more efficient than copy: copy constructor, move constructor, assignment operator, move assignment operator, and destructor.
* Use std::move() on an lvalue to treat it as an rvalue; remember that this is only a cast.
* An object with a name is an lvalue (except enumerators and non-type template parameters).
* Rvalue reference parameters have names.
* In general, a moved-from object can only be assigned to and destructed.
* For some template parameter T, a function parameter T && x may be a universal reference or an rvalue reference, depending on whether the template-head is on the function that takes x or not.

```C++
template<typename T>
void foo(T && x);     // universal reference

template<typename T>
struct foo {
    void bar(T && x); // rvalue reference
};
```

* Pass sink parameters (parameters that are always copied or moved from) by value.
```C++
std::string append_if_unique(std::string str, std::string const & suffix)
{
    if (str.find(suffix) == std::string::npos)
        str += suffix;
    return str;
}

std::string foo = /* ... */;
foo = append_if_unique(foo, "aaa");
auto bar = append_if_unique(std::move(foo), "bbb");
```
* When returning values, just use return x. Don't use std::move(); it will only cause problems.
---
## nullptr: Use nullptr instead of using 0 or NULL
* nullptr has advantages over both 0 and NULL.  It is clearly mark the intend to have a null pointer value like NULL but won’t induce into error about its true type.
```C++
void f(leWireElement* elem) {}
void f(int) {}
f(NULL)    // call f(int)
f(nullPtr) // call f(leWireElement* elem)
```
* Don’t test pointer as if they were boolean

```C++
if (ptr) { 
	…
}
//should be ->
if (ptr != nullptr) {
	…
}
```
* [C++11 nullptr](https://shengyu7697.github.io/cpp-nullptr/)
---
## override and final
Those allows to annotate functions which overrides virtual functions of the base class.
```C++
class Base {
public:
   virtual void f();
   virtual void g();
   void h();
};
class Derived: Base {
public:
   void f() override;
   void g() final;
   void h() override; // error as Base::f is not virtual
}
class DerivedTwice: Derived {
public:
   void g() override; // error as Derived::g is final
};
```
---

## Range loop
Allow to iterate on a STL containers
```C++
int sum{0};
for (auto&& i: getValues()) {
   sum += i;
}
```
---
# references
* [Modern C++ (Lecture & Tutorials)](https://www.youtube.com/playlist?list=PLgnQpQtFTOGRM59sr3nSL8BmeMZR9GCIA)
* [Modern C++ Tutorial: C++ 11/14/17/20 On the Fly](https://changkun.de/modern-cpp/en-us/00-preface/)
* [What is Moden C++?](https://www.modernescpp.com/index.php/what-is-modern-c#:~:text=Modern%20C%2B%2B%20stands%20for%20C%2B%2B,14%2C%20and%20C%2B%2B17.&text=If%20you%20look%20at%20the,the%20second%20modern%20C%2B%2B.)
* https://github.com/PacktPublishing/Complete-Modern-C-/tree/master/Section%2001
