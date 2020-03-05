// CppCon 2016: Arthur O'Dwyer Template Normal Programming (part 1 of 2)
// https://www.youtube.com/watch?v=vwrXHznaYLA&t=597s
// https://www.youtube.com/watch?v=VIz6xBvwYd8
// https://github.com/CppCon/CppCon2016/tree/master/Tutorials/Template%20Normal%20Programming%2C%20Part%201
#include<iostream>

// Function template: It is NOT a function. It is a template for MAKING FUNCTION.
template<typename T>
T abs(T x) { 
	return (x >= 0) ? x : -x; }
// Don't pay for what you don't use: If nobody calls abs<int>, it WON'T be INSTANTIATED by the compiler at all.

int main() {	
	printf("%d", abs<int>(-42)); // 42 (positive value / absolute value)

	double(*foo)(double) = abs<double>; // compiler will NOT instantiated for the type foo
	printf("%f", foo(-42));      // 42.000000 - type instantiated for the type foo
	return 0;
}

Class Template: It is NOT a class. It is a template for MAKING CLASS. It can create NEW TYPE.
Template class : It is a CLASS, created from 'class template'.

C style of making - Generic types:
struct myGenericList {
	void *data;
	myGenericList *next;
};
myGenericList *intList = ...;
myGenericList *doubleList = ...;

C++ style of making - Generic types using 'class template':
template<typename T>
struct myGenericList {
	T data;
	myGenericList<T> *next;
};

myGenericList<int>    *intList = ...;
myGenericList<double> *doubleList = ...;

// static data member(sdm) must be defined somewhere if you want to use it.

struct S { static int sdm; };
int main() { return S::sdm; } // ERROR: undefined reference to 'S::sdm;'

struct S { static int sdm; };
int S::sdm = 42; // definition
int main() { return S::sdm; } // OK

template<class T>
struct S { static int sdm; };

template<class T>
int S<T>::sdm = 42; // templated definition
// NOTE: 1. Above sdm definition even can be placed in a different header file. The same will NOT work for
// normal class and normal function. inline function sdm CAN be placed in a different header file.

// 2. inline and template: Whichever the scenario the inline works the template work as well

int main() { return S::sdm; } // OK

#  2 new kinds of templates:
C++11 : Introduced alias templates.
C++14 : Introduced vaiable templates.

variable template:It is a syntatic sugar of 'static data member' of a class template.

// class template with a static data member
template<typename T>
struct is_void {
	static const bool value = (some expression); // sdm
};

int main() {
	printf("%d", is_void<int>::value); // 0
	printf("%d", is_void<void>::value); // 1
}

// variable template
template<typename T>
const bool is_void_value = (some expression); // NOTE: It is NO longer a static !

int main() {
	printf("%d", is_void_value<int>); // 0
	printf("%d", is_void_value<void>); // 1
}

In the STL: the best of both worlds
template<typename T>
struct is_void {
	static constexpr bool value = (some expression);
};

template<typename T>
constexpr bool is_void_v = is_void<T>::value;

int main() {
	printf("%d", is_void<int>::value);  // 0
	printf("%d", is_void_v<void>);		// 1
}

Alias templates:
typedef std::vector<int> myvect_int; // C++03 alias syntax

using myvect_double = std::vector<double>; // C++11 using syntax
template<typename T> using myvec = std::vector<T>; // C+11 syntax

int main{
	static_assert(is_same_v(myvect_int, std::vector<int>>);
	static_assert(is_same_v(myvect_double, std::vector<double>> );
	static_assert(is_same_v(myvect<float>, std::vector<float>> );
}



Puzzles:
// NOTE: NO implicit conversion is allowed in template deduction
1.
#include<algorithm>
short f();
int main() {
	int x = 42;
	return std::max(f(), x); // Error: f is short BUT x is int. NO matching for the template argument T in std::max(T, T)
}

// Solution 1: Make the arugments match exactly
return std::max(static_cast<int>(f()), x); 

// Solution 2: Make the paramenter stop contributing to deduction.
return std::max<int>(f(), x);

2. 
template<typename T, typename U>
void foo(std::array<T, sizeof U> x, std::array<U, sizeof T> y, int z) {
	puts(__PRETTY_FUNCTION__);
}
// std::array<T, sizeof U> x
// x tells/deduce  T is an int BUT does not tell anything about sizeof U - it is calculated by the compiler

int main() {
	foo(std::array<int, 8>{}, std::array<double, 4>{}, 0.0); // OK bcos sizeof int == 4, sizeof double == 8, 0.0 implicitly converts to int
	foo(std::array<int, 9>{}, std::array<double, 4>{}, 0.0); // Error: <int,9> NOT matches to <int,8>
	// <int,9> will NOT implicitly converted to <int,8>.
}


Unary + : There is NO unary + suport for lambda type BUT function pointer type  has.
Captureless lambda types are always implicitly convertible to function pointer type. But
being implicitly convertible to a thing does not mean actually being that thing!
Note: if you absolutly need the function-pointer conversion to happen, add a unary +

3. 
template<typename T, typename U>
void foo(T (*fptr)(U)) { // T <- double, U <- int
	puts(__PRETTY_FUNCTION__);
}

int main() {
	foo( [](double x) { return int(x); }); // ERROR:
	foo(+[](double x) { return int(x); }); // OK
}

4.How to call a specialization explicitly ?
template<typename T, typename U>
void add(T x, U y) {
	puts(__PRETTY_FUNCTION__);
}

int main() {
	add<int, int>('x', 3.1); // [T = int,  U = int] so x,y are NO longer contributing to the type deduction of T,U
	add<int>('x', 3.1);		 // [T = int,  U = double]
	add<>('x', 3.1);		 // [T = char, U = double]
	add('x', 3.1);			 // [T = char, U = double]
}

5. default template parameters:
template<typename T>
void add() { 
	puts(__PRETTY_FUNCTION__);
}

int main() {
	add<int>(); // OK: [T = int]
	add<>();    // ERROR: couldn't infer template argument T
	add();      // ERROR: couldn't infer template argument T
}

// Solution:
template<typename T = char *>
void add() {
	puts(__PRETTY_FUNCTION__);
}

int main() {
	add<int>(); // OK: [T = int]
	add<>();    // OK: [T = char *]
	add();      // OK: [T = char *]
}


ambersant & :

int i;

template<typename T>
void f(T t) { puts(__PRETTY_FUNCTION__); }
f(i);  // void f(T)   [T = int]

template<typename T>
void f(T *t) { puts(__PRETTY_FUNCTION__); }
f(&i); // void f(T*)  [T = int]

// Lvalue references
template<typename T>
void f(T& t) { puts(__PRETTY_FUNCTION__); }
f(i);  // void f(T&)  [T = int], 'i' is a Lvalue
f(static_cast<int&>(i)); // [T = int]
f(static_cast<int&&>(i)); // ERROR
f(static_cast<volatile int&>(i)); // [T = volatile int]
f(static_cast<volatile int&&>(i)); // Error
f(static_cast<const int&>(i)); // [T = cont int]
f(static_cast<const int&&>(i)); //  [T = cont int] - NO ERROR !!!

// Rvalue references
template<typename T>
void f(T&& t) { puts(__PRETTY_FUNCTION__); }
f(42); // void f(T&&) [T = int], '42' is a Rvalue. '42' is 'int&&' so T deduced either [T = int&&] or [T = int] (fewer ampersands preferred)
f(std::move(i)); // void f(T&&) [T = int], 'std::move(i)' is a Rvalue
f(i);  // void f(T&&) [T = int&] - reference collaspsig. 'i' is 'int&' so 'T&&' is 'int&'
const int j = 42;
f(j); // [T = const int&].'i' is 'const int&' 
f(std::move(j)); // [T = const int]. 'i' is 'const int&&'

template<typename T>
void foo(void (*f)(T)) { puts(__PRETTY_FUNCTION__); }
void bar(int&&) { }
foo(bar); // [T = int&&]

// Reference collapsing in C++03
template<typename T>
void foo(T t) {
	T&  x = ...; // int& x
	T&& y = ...; // int& y
}

int main() {
	int i;
	foo<int&>(i)
}

Reference collapsing:
&  + &  = &			L + L = L
&  + && = &			L + R = L
&& + &  = &			R + L = L
&& + && = &&		R + R = R


Year		  Template types	      Type deduction		Specialization
C++ 1998	Function Template			Supported				Supported
c++ 1998    Class Template				NOT supported			Supported
C++ 2011	Alias						NOT supported			   NO
C++ 2014	Variable					NOT supported			Supported
C++ 2017	NOTHING newly added			Now Class supports 
										type deduction BUT 
										NOT all compilers.

template<typename T = void>
struct foo { };
foo bar;    // ERROR
foo <> bar; // OK

// Template Specialization:
template<typename T>
struct is_void {
	static constexpr bool value = false;
};

template<>				// empty <>
struct is_void<void> {	// specialization for 'void'
	static constexpr bool value = true;
};

int main() {
	printf("%d", is_void<int>::value);  // 0
	printf("%d", is_void<void>::value);	// 1
}

template<typename T>
int my_sizeof() { return sizeof (T); }

template<>
int my_sizeof<void>() { return 1; }

template<typename T>
T abs(T x) {
	return (x >= 0) ? x : -x;
}

template<>
int abs<int>(int x) {
	if (x == INT_MIN) throw std::domain_error("oops");
	return (x >= 0) ? x : -x;
}

template<>
int abs<>(int x) { // <> by type deduction
	if (x == INT_MIN) throw std::domain_error("oops");
	return (x >= 0) ? x : -x;
}

template<>
int abs(int x) { // without <>. Most often you will see in practice.
	if (x == INT_MIN) throw std::domain_error("oops");
	return (x >= 0) ? x : -x;
}

template<typename T> using myvec = std::vector<T>;
template<> using myvec<void> = void; // Error: explicit specialization of alias templates is NOT permitted.

// 1. Alias templates can NOT be specialized.
template<typename T>
using myvec =  std::vector<T>

template<typename T>
void foo(myvec<T>& mv) {  // void foo(std::vector<T>&)
	puts(__PRETTY_FUNCTION__);
}

int main() {
	std::vector<int> v;
	foo(v); // void foo(myvec<T> &) [ T = int ]
}

// we can "propagate T through" the definition of myvec to find that foo<T> takes std::vector<T>

// 2. class templates can be specialized.
template<typename T>
struct myvec {
	using type = std::vector<T>;
};

template<typename T>
void foo(typename myvec<T>::type& mv) {
	puts(__PRETTY_FUNCTION__);
}

int main() {
	std::vector<int> v;
	foo(v); // could NOT infer template argument 'T'
}

// Bcos we don't know what myvec<T>::type is until we know what T is.

//3. So class templates can NOT do deduction
template<typename T>
struct myvec {
	explicit myvec(T t); // constructor
};

int main() {
	myvec v(1); // ERROR
}

// Bcos we don't know what parameters types myvec<T>::myvec might take, until we know what T is.
// Forward works: if T is int, we know that myvec<T>'s constructor take an int parameter.
// But what we need here is to go backward: if myvec<U>'s constructor takes an int parameter, determine the value of U.

// 3. Partial Specialization: It itself a template. It still requires further "customerization" by the user before it can be used.
template<typename T>
constexpr bool is_array = false;

template<typename Tp>
constexpr bool is_array<Tp[]> = true; // partial specialization

int main() {
	printf("%d", is_array<int>);   // 0
	printf("%d", is_array<int[]>); // 0
}

// 4. No. of template params on the partial specialization is completely UNRELATED to the no. of template params on the original template.

// this is the primary template
template<typename T>
constexpr bool is_array = false;

// there are the paratial specializations
template<typename Tp>
constexpr bool is_array<Tp[]> = true;

template<typename Tp, int N>
constexpr bool is_array<Tp[N]> = true;

template<> // this is a full specialization
constexpr bool is_array<void> = true;

// slide 71
////////////////////////////////////////////////////////////////
