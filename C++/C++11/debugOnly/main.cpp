#if 1
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

  Year				Template types  
C++ 1998	Function and Class Templates
C++ 2011	Alias
C++ 2014	Variable
C++ 2017	NOTHING newly added

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



















































#else
// Ref: https://www.udemy.com/course/beg-cpp-temp/learn/lecture/6958216
#include <iostream>
#include <vector>
#include <list>

const char * GetErrorMessage(int errorNo) { return "Empty"; }

// typedef const char *(*PF)(int); // Option 1
using PF = const char *(*)(int);   // Option 2

void ShowError(PF pf) { 
	std::cout << pf(9); // Empty
}

// NOTE: typedef can NOT be templatized but 'using' can !!!
typedef std::vector<std::list<std::string>> Names_typedef; // Option 1
template<typename T>									   // Option 2 (preferred)
using Names_using = std::vector<std::list<T>>;

int main() {	
	PF pf = GetErrorMessage;
	ShowError(pf);

	Names_typedef names;			  // can NOT be templatized
	Names_using<std::string> players; // templatized
	Names_using<int> playerNumber;    // templatized

	Names_using<Names_using<std::string>> nested; // Nested as well !!
	return 0;
}

// Type definition - typedef:
typedef unsigned int INT;
UINT val{};

typedef long long LLONG;
LLONG elem{};

typedef std::vector<std::list<Employee>> Teams;
Teams testingTeams;
Teams::iterator it = testingTeams.begin();

typedef const char *(*ErrorFn)(int);
ErrorFn pfn = GetErrorMessage;

// Type Alias - using: (Preferred)
using INT = unsigned int;
UINT val{};

using LLONG = long long;
LLONG elem{};

using Teams = std::vector<std::list<Employee>> ;
Teams testingTeams;
Teams::iterator it = testingTeams.begin();

using ErrorFn = const char *(*)(int);
ErrorFn pfn = GetErrorMessage;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Class Templates Partial Specialization
// https://www.udemy.com/course/beg-cpp-temp/learn/lecture/6958214

#include<iostream>
using namespace std;

template<typename T, int columns>
class PrettyPrinter {
	T *m_pData;
public:
	PrettyPrinter(T *data) : m_pData(data) { }
	void Print() { 
		cout << "Columns:" << columns << endl;
		cout << "{ " << *m_pData << " }" << endl; 
	}
	T *GetData() { return m_pData; }
};

// Partial Specialization: Partially specialize some of the values(NOT ALL) of template parameters
// Here we are paritially specializing the 2nd non-template argument
template<typename T> // REMOVE: int columns
class PrettyPrinter<T, 80> { // Paritially specialize 'variable int columns' into 'constant final value'
	T *m_pData;
public:
	PrettyPrinter(T *data) : m_pData(data) { }
	void Print() {
		cout << "Using specialized 80" << endl;
		cout << "{ " << *m_pData << " }" << endl;
	}
	T *GetData() { return m_pData; }
};

int main() {
	int data = 123;
	PrettyPrinter<int, 40> p{ &data };
	p.Print();

	PrettyPrinter<int, 80> q{ &data };
	q.Print();

	return 0;
}


// Implementation of smart pointer which works with any type
template<typename T>
class SmartPointer {
	T *m_ptr;
public:
	SmartPointer(T *ptr):m_ptr(ptr) { }
	~SmartPointer() { delete m_ptr; }

	T * operator ->() { return m_ptr; } // overload -> and * operators
	T & operator  *() { return *m_ptr; } // NOTE: *m_ptr	
};

// Partially specialize for array type
template<typename T>
class SmartPointer<T[]> {		// T[] - Array Type
	T *m_ptr;
public:
	SmartPointer(T *ptr) :m_ptr(ptr) { }
	~SmartPointer() { delete[] m_ptr; }
	
	// T * operator ->() { return m_ptr; }  // NOT needed for array type
	// T & operator  *() { return *m_ptr; } // NOT needed for array type
	T & operator [](int index) { return m_ptr[index]; }	
};

int main() {
	SmartPointer<int> spi{ new int(3) }; // single value 3
	cout << *spi << endl;

	SmartPointer<int[]> spa{ new int[3] }; // Array of any 3 int values
	spa[0] = 7;
	cout << spa[0] << endl;

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Class Templates Explicit Specialization - Part 1 & 2
// https://www.udemy.com/course/beg-cpp-temp/learn/lecture/6958210
// https://www.udemy.com/course/beg-cpp-temp/learn/lecture/6958212


#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class PrettyPrinter {
	T *m_pData;
public:
	PrettyPrinter(T *data) : m_pData(data){ }
	void Print() { cout << "{ " << *m_pData << " }" << endl; }
	T *GetData() { return m_pData; }
};

// Explict specialization for char*
template<>
class PrettyPrinter<char*> {
	char *m_pData;
public:
	PrettyPrinter(char *data) : m_pData(data) { }
	void Print() { cout << "{ " << m_pData << " }" << endl; } //  *m_pData => m_pData
	char *GetData() { return m_pData; }
};


// Explict specialization for std::vector<int> - ENTIRE CLASS SPECIALIZATION
// Option 1:
template<>
class PrettyPrinter<std::vector<int>> {
	std::vector<int> *m_pData;
public:
	PrettyPrinter(std::vector<int> *data) : m_pData(data) { }
	void Print() { 
		// cout << "{ " << *m_pData << " }" << endl; // ERROR : m_pData - ptr to vector, *m_pData - return vector itself. << is NOT overloaded for pointer to vector.
		cout << "{ ";
		for (const auto &x : *m_pData) cout << x; // OK - NOT loop
		cout << " }";
	} 
	std::vector<int> *GetData() { return m_pData; }
};


// Explict specialization for std::vector<int> - ONLY PARTICULAR MEMBER FUNCTION SPECIALIZATION
// Option 1:
template<>
void PrettyPrinter<std::vector<int>>::Print() {
	cout << "{ ";
	for (const auto &x : *m_pData) cout << x; // OK - NOT loop
	cout << " }";
}

int main() {
	int i = 5;
	float f = 1.2;
	char *s{ "Hello Sridhar" };

	PrettyPrinter<int> obj1(&i);
	obj1.Print(); 					// { 5 }
	cout << obj1.GetData() << endl; // 00AFFD20
	PrettyPrinter<float> obj2(&f);
	obj2.Print(); 					 // { 1.2 }
	cout << *obj2.GetData() << endl; // 1.2

	// char* has lot of	PROBLEMS using the generalised class template
	// LIST OF PROBLEMS WITHOUT USING TEMPLATE SPECIALISATION FOR char*
	// Case 1: Passing argument issue. Here <T> is T* and (s) is also *s	
	// PrettyPrinter<char*> obj3(s); // ERROR: can NOT convert argument 1 from 'char *' to 'char **'

	// Case 2: Return type issue
	PrettyPrinter<char*> obj3(&s);	 // OK: <T> is T* and (&s) is &(*s) = s
	obj3.Print(); 					 // { Hello Sridhar }
	cout << *obj3.GetData() << endl; // Hello Sridhar
	// Return type of GetData() is T*. And 'T' itself 'char*' so return type is *(T*) = T**
	// char *pData = obj3.GetData(); // ERROR:can NOT convert from 'char **' to 'char *'

	// Case 2: Output issue
	char *s{ "Hello Sridhar" };
	PrettyPrinter<char> obj4(s); 	 // OK. NOTE: char* => char
	obj4.Print(); 					 // { H } - Prints only the first character
	cout << *obj4.GetData() << endl; // H
	cout << obj4.GetData() << endl;  // Hello Sridhar
	char *pData = obj4.GetData();
	cout << *pData << endl; 		 // H
	cout << pData << endl; 			 // Hello Sridhar
	// So we NEED template explicit specialisation.

	// USE EXPLICIT SPECIALISATION FOR char*
	PrettyPrinter<char*> obj5(s);	 // OK
	obj5.Print(); 					 // { Hello Sridhar }
	cout << *obj5.GetData() << endl; // H
	cout << obj5.GetData() << endl;  // Hello Sridhar
	char *pData = obj5.GetData();
	cout << *pData << endl; 		 // H
	cout << pData << endl; 			 // Hello Sridhar

	// USE EXPLICIT SPECIALISATION FOR vector<int>
	std::vector<int> v{ 1,2,3,4 };
	PrettyPrinter<std::vector<int>> pv(&v);
	pv.Print(); 					 // { 1234 }
	// cout << *pv.GetData() << endl; // ERROR: << is NOT overloaded for '*pv.GetData()'
	cout << pv.GetData() << endl;  // 010FFB60
	//int *pData = pv.GetData();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ref: Class Templates
// https://www.udemy.com/course/beg-cpp-temp/learn/lecture/6958208
#include<iostream>
using namespace std;

// Without Class Template
// Implement STACK class for ANY datat type
template<typename T, int size> // size is a 'non-type template argument'
class Stack {
	int m_Buffer[size];
	int m_Top{ -1 }; 
public:
	// 'T' - Can be user defined type so better go for 'const reference'
	void Push(const T &x) { m_Buffer[++m_Top] = x; }
	
	// void Pop() { --m_Top; }
	void Pop(); // Definition is outside of a class

	const T& Top() const { return m_Buffer[m_Top]; }

	bool isEmpty() { return m_Top == -1; }

	// Factory Method for creating an instance of a class (Stack)
	// static Stack Create() { return Stack<T, size>(); } // creates temp object and return by value
	static Stack Create();

	Stack() = default; // defalut constructor
	/*
	Stack(const Stack &obj) { // copy constructor
		m_Top = obj.m_Top;
		// <= bcos we are starting from -1 NOT 0
		for (int i = 0; i <= m_Top; ++i) m_Buffer[i] = obj.m_Buffer[i];
	}
	*/
	Stack(const Stack &obj);


};

// Member function outside the class
template<typename T, int size>
void Stack<T, size>::Pop() { --m_Top; }

template<typename T, int size>
Stack<T, size> // Must specify the return type of Stake once again
Stack<T, size>::Create() { return Stack<T, size>(); }

template<typename T, int size>
// Stack<T, size>::Stack(const Stack<T, size> &obj) { // NO need to specify the Stack type inside function argument
Stack<T, size>::Stack(const Stack &obj) { // shorthand declartion is good enough for function argument - const Stack &obj
	m_Top = obj.m_Top;
	// <= bcos we are starting from -1 NOT 0
	for (int i = 0; i <= m_Top; ++i) m_Buffer[i] = obj.m_Buffer[i];
}

int main() {	
	// Stack<float, 9>  s; // specify the class type in the form of 'template argument list' for instantiation
	Stack<float, 9>  s = Stack<float, 9>::Create(); // Instantiate using factory method
	// Stack<float, 10>  s = Stack<float, 9>::Create(); // ERROR: size should be same. Otherwise created object type is different from expected type.
	s.Push(1); s.Push(2); s.Push(3); s.Push(4);
	/*
	while (!s.isEmpty()) {
		cout << s.Top() << " "; // 4 3 2 1
		s.Pop(); // Must otherwise stack overflow
	}
	*/

	// create another object using copy constructor
	auto s2(s); 
	while (!s2.isEmpty()) {
		cout << s2.Top() << " "; // 4 3 2 1
		s2.Pop(); // Must otherwise stack overflow
	}

	return 0;
}

/*
// Without Class Template
// Implement STACK class ONLY for integers
class Stack {
	int m_Buffer[512];
	int m_Top{ -1 };
public:
	void Push(int x) { m_Buffer[++m_Top] = x; }

	void Pop() { --m_Top; }

	int Top() const { return m_Buffer[m_Top]; }

	bool isEmpty() { return m_Top == -1; }
};

int main() {
	Stack  s;
	s.Push(1); s.Push(2); s.Push(3); s.Push(4);
	while (!s.isEmpty()) {
		cout << s.Top() << " "; // 4 3 2 1
		s.Pop(); // Must otherwise stack overflow
	}
	return 0;
}
*/




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ref: Variadic Templates
// https://www.udemy.com/course/beg-cpp-temp/learn/lecture/6958202
#include<iostream>
#include <iomanip> // for std::setprecision()
#include "Integer.h"
using namespace std;


// In C, printf accepts variable number of args with different types using macro[NOT type safte and don't accept references].
// In C++, we can implement the same using varadic templates with type safe and also accepts reference parameters.

// Accept the variable number of arguments by initializer list BUT same type
template<typename T>
void Print_variableArg_SameType(std::initializer_list<T> args) {
	// range base for loop
	for (const auto &x : args) std::cout << x << " ";
}

// Varadic Template:

// End condition of the recurrsion
void Print_variableArg_DifferentType() {
	cout << endl;
}

/*
// template parameter pack. 
template<typename T, typename... Params> // Params - holds list of different Types. T - single element return by recurrsion
// function parameter pack
void Print_variableArg_DifferentType(T x, Params... args) { // PASS BY VALUE
	std::cout << x;

	// () must for arg and Params in sizeof...
	// cout << sizeof...(args) << " " << sizeof...(Params) << endl; // 3 3, 2 2, 1 1, 0 0
	if (sizeof...(args) != 0) cout << ",";
	
	// 1. recurrsion - helps - has a loop
	// 2. recurrsion - helps - to access the individual elements [on each call argument reduce by one, that one we can access it directly]
	Print_variableArg_DifferentType(args...); // loop by recurrsion
}


// template parameter pack. Params holds collection of different Types.
template<typename T, typename... Params>
// function parameter pack
void Print_variableArg_DifferentType(const T &x, const Params&... args) { // PASS BY REFERENCE - const reference
	std::cout << x;

	// () must for arg and Params in sizeof...
	// cout << sizeof...(args) << " " << sizeof...(Params) << endl; // 3 3, 2 2, 1 1, 0 0
	if (sizeof...(args) != 0) cout << ",";

	Print_variableArg_DifferentType(args...); // args... - passing LVALUE NOT RVALUE - so still pass by value !!!
}

*/

// template parameter pack. Params holds collection of different Types.
template<typename T, typename... Params>
// function parameter pack
void Print_variableArg_DifferentType(T &&x, Params&&... args) { // PASS BY RVALUE REFERENCE - NOT const reference
	std::cout << x;

	// () must for arg and Params in sizeof...
	// cout << sizeof...(args) << " " << sizeof...(Params) << endl; // 3 3, 2 2, 1 1, 0 0
	if (sizeof...(args) != 0) cout << ",";

	// std::forward - preserve the type of arguments passed in function parameters
	Print_variableArg_DifferentType(std::forward<Params>(args)...); // args... - passing RVALUE by Perfect forwarding - Pass by refernce !!!
}

/*
// Recurrsive call stack:
1. Print_variableArg_DifferentType(1, 2.5, 3, "4")
2. Print_variableArg_DifferentType(2.5, 3, "4")
3. Print_variableArg_DifferentType(3, "4")
4. Print_variableArg_DifferentType("4")
5. Print_variableArg_DifferentType()
*/

int main() {
	//Print_variableArg_SameType({ 1,2,3,4}); // NOTE: { } bcos it is an Initializer list
	//Print_variableArg_SameType({ 1,2.5,3,"4"}); // ERROR: All should be same type

	//Print_variableArg_DifferentType(1,2.5,3,"4" );

	Integer val{ 1 };
	Print_variableArg_DifferentType(0, val, Integer{ 2 }); // Integer{ 2 } - passing RVALUE
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include <iomanip> // for std::setprecision()
using namespace std;

/*
int Max(int x, int y) {
	return x < y ? x : y;
}
float Max(float x, float y) {
	return x < y ? x : y;
}
*/
// Function Template:
template <typename T> // Argument list: Override deduction by specifiying explicit type
T Max(T x, T y)       // Argument dedction: 'T' from 'T x' decides whole template type
{ 
	cout << typeid(T).name() << endl;
	return x > y ? x : y; 
}

// Example for 3: using 'explicit instantiation'
template char Max(char x, char y); // Template instatiated by this function declaration eventhough we did NOT called that function definition

// Example for 4: creating 'explicit specialization'.
// NOTE: This definition SHOULD be '.cpp' files NOT in '.h'. Bcos it is already instantiatied
template <> const char* Max<const char*>(const char *x, const char *y)
// template <> const char* Max(const char *x, const char *y) // same as above
{
	return strcmp(x, y) > 0 ? x : y;
}

// Non-type Template Arguments
template<int n>
void show() {
	/// n = n + 1; // ERROR: You can NOT change it
	cout << n;
	char buffer[n]; // OK
}

template<typename T>
T Sum_without_nonTypeTempArg(T *pArr, int sz) { // sz - passed by the called
	T sum{};
	for (int i = 0; i < sz; ++i) sum += pArr[i];
	return sum;
}


template<typename T, int sz> // sz - NO need to pass by the caller. It is calculated automatically by 'reference to array'. 
T Sum_with_nonTypeTempArg(T (&pArr)[sz]) {
	T sum{};
	for (int i = 0; i < sz; ++i) sum += pArr[i];
	return sum;
}

int main() {
	/*
	// Type name is resolved by 'arugment deduction'
	//auto num = Max(3.3f, 5.5f);
	//cout << num << endl;
	//num = Max(3, 5);
	//cout << num << endl;
	

	// auto mixed = Max(3, 5.5f); // function overloading error 
	// cout << mixed;

	 //auto mixed = Max(static_cast<float> (3), 5.5f); 
	 //cout << mixed;

	 // Type name is resolved by 'Argument list: Override deduction by specifiying explicit type'
	 auto explicitly = Max<float>(3, 5.5f); // explicitly tell T is float, NOT by argument deduction
	 cout << explicitly;


	 Template instantiation will take place only
		 1. a function template is invoked
		 2. taking address of a function template
		 3. using explicit instantiation
		 4. creating explicit specialization.


	 // Example for 2: taking address of a function template
	 int(*pfn) (int, int) = Max; // Template instatiated eventhough we did NOT called that function

	// Example for 4: creating explicit specialization.
	 const char *a{ "A" };
	 const char *b{ "B" };
	 auto s = Max(a, b); // explicit specialization for string comparision gets called. If don't that function definition then 
	 // regular template function gets called which give wrong result bcos it compare address values NOT the content.
	 cout << s;


	 // Non-type Template Arguments (Passing CONSTANT expression [some compile time computed constant value])
	 // show<9>(); // 9

	 // CONSTANT expression are 'addresses', 'references', 'integrals', 'nullptr', 'enums'
	 int i = 9;
	 // show<i>(); // ERROR: Should be constant
	 show<sizeof i>(); // 4
	 */
	int n = 0;
	int arr[]{ 1,2,3,4,5 };
	n = Sum_without_nonTypeTempArg(arr, 5); // without using 'Non-type Template Arguments'

	// Reference to Array - Implicitly knows the size of an array
	// int(&ref)[5] = arr; // OK
	// int(&ref)[6] = arr; // ERROR - Array size should be the exact size

	// Taking advantage of 'reference to array' and 'Non-type Template Arguments'
	auto n = Sum_with_nonTypeTempArg(arr); // NO need to specify the array size
	cout << n;

	// Note: global std library function - begin(arr) - Use the advantage of 'reference to array' and 'Non-type Template Arguments'
	auto it = std::begin(arr);
	//template<class _Ty,	size_t _Size> inline
	//constexpr _Ty *begin(_Ty(&_Array)[_Size]) _NOEXCEPT
	//{	// get beginning of array
	//	return (_Array);
	//}


	/*
	// float - 6 precision/significant digits, double - 15 precision, long double - 15 / 18 / 33 precisions
	// NOTE: cout by default uses 6 precision for both float and double

	std::cout << 1.234567890 << '\n';  // 1.23457 (ONLY 6 significant digits - double)
	std::cout << 1.234567890f << '\n'; // 1.23457 (ONLY 6 significant digits - float)


	std::cout << 12.34567890f << '\n'; // 12.3457 - Last 7 is a round of 6

	std::cout << 12345.67890f << '\n'; // 12345.7
	std::cout << 123456.7890f << '\n'; // 123457

	std::cout << 1234567.890f << '\n'; // 1.23457e+06
	std::cout << 12345678.90f << '\n'; // 1.23457e+07

	float f;

	f = 1.2345678901234567890f; // 1.23456788
	f = 12.345678901234567890f; // 12.3456793
	f = 123456.78901234567890f; // 123456.789
	f = 1234567.8901234567890f; // 1234567.88
	f = 12345678.901234567890f; // 12345679.0

	f = 123456789.01234567890f; // 123456792.
	f = 1234567890.1234567890f; // 1.23456794e+09
	f = 12345678901.234567890f; // 1.23456788e+10

	double d = 1.2345678901234567890;
	std::cout << std::setprecision(16); // show 16 digits of precision
	std::cout << 1234567.8901234567890f << '\n'; // 1234567.875
	std::cout << 1234567.8901234567890 << '\n'; // 1234567.890123457 - double




	*/
	return 0;
}

#endif