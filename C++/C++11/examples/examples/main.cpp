#if 1
#include <iostream>
// Reference: C++ 11: Rvalue Reference -- Move Semantics
// https://www.youtube.com/watch?v=IOkgBrXCtfo&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=3

int main()
{
	/////////////////////////////////
	// 
	/////////////////////////////////
	// C++ 03 -  
	

	// C++ 11 - 	

	return 0;
}











































/*

#include <iostream>

int main()
{
	/////////////////////////////////
	// 
	/////////////////////////////////
	// C++ 03 -  
	

	// C++ 11 - 	

	return 0;
}

*/







#else
// Ref: C++ 11: Rvalue Reference - Argument Perfect Forwarding
// https://www.youtube.com/watch?v=0xcCNnWEMgs&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=4

#include <iostream>
void foo(sriVector arg); // sriVector has both Move constructor and Copy constructor

int main()
{
	sriVector reusable = createSriVector();
	relay(reusable); 		 // passing Lvalue - Calls Copy constructor
	relay(createSriVector()); // passing Rvalue - Calls Move constructor

	return 0;
}

// Argument Forwarding
template<typename T>
void relay(T arg) {
	// Argument Forwarding - forwarding the 'arg' from 'relay' to 'foo' but there is no guarantee of without any type change.
	foo(arg);
}

// Argument Perfect Forwarding - used to avoid costly and unnecessary copy construction
template<typename T>
void relay(T&& arg) {
	// Argument Perfect Forwarding - forwarding the 'arg' from 'relay' to 'foo' without any type change.
	// Rvalue is forwarded as Rvalue and Lvalue is forwarded as Lvalue.
	// relay(reusable)         => arg is Lvalue
	// relay(createSriVector()) => arg is Rvalue

	foo(std::forward<T> (arg));
}

// Implementation of std::forward()
template<class T>
T&& forward(typename remove_reference<T>::type& arg) {
	return static_cast<T&&> (arg);
}

// standard library - remove_reference example
template<class T>
struct remove_reference; // It removes reference on type T
remove_reference<int&>::type i; // T is int& => int i
remove_reference<int>::type i;  // T is int  => int i





/*
Reference collapsing rule for Type deduction (C++ 11):
1. T& &   => T&
2. T& &&  => T&
3. T&& &  => T&
4. T&& && => T&&
*/

// Rvalue to Rvalue reference
	// T&& variable is initialized with Rvalue => Rvalue reference
	relay(9) => relay(T&&);
	T => int&&  // passing Rvalue
	T&& => int&& && => int&& (Rvalue reference)

// Lvalue to Lvalue reference
	// T&& variable is initialized with Lvalue => Lvalue reference
	relay(x) => relay(T&&); // regardless of x is Lvalue of integer or integer reference
	T => int&  // passing Lvalue
	T&& => int& && => int& (Lvalue reference)

Note: 
/*
	1. Rvalue reference is always in the form T&&.
	2. Not all T&& is a Rvalue.
	3. All regular T&& is a Rvalue. ex: int&&, float&&
	4. Template T&& is not always Rvalue.
	5. T&& can be an Universal reference which takes Rvalue, Lvalue, const, non-const etc.,
	   only if 'T' is a Function Template type, not a regular data type or class template type.
*/





Difference between std::move() and std::forward() ?
	std::move<T>(arg);    // Turns arg into an Rvalue type
	std::forward<T>(arg); // Turns arg into an T&&
///////////////////////////////////////////////////////////////////////////
#include <iostream>
// Ref: Advanced C++: Understanding rvalue and lvalue
// https://www.youtube.com/watch?v=UTUdhjzws5g&list=PLE28375D4AC946CC3&index=20

/*
Lvalue: An object that occupies some 'identifiable address' in the RAM memory (x, y)
Rvalue: Any object that is not a Lvalue. Mostly stay in the Register memory (5, 100)
C++11 introduced Rvalue reference.
*/

class dog { };
int sum(int x, int y) { return x + y; }
int square(int& x) { return x * x; }
int squareC(const int& x) { return x * x; }

int main()
{
	// Lvalue - Most of the variables in C++ code are Lvalues
	int i;				// i is a Lvalue
	int *p = &i;		// i's address is identifiable
	i = 2;				// Memory content is modified
	dog d;				// Lvalue of user defined type (class)

	// Rvalue
	int x = 2;			// 2 is an Rvalue; x is a Lvalue
	x = i + 2;			// (i+2) is an Rvalue. Bcos you cann't get the &(i + 2)

	int* q = &(i + 2);	// Error
	i + 2 = 4;			// Error. Bcos Rvalue (i + 2) cann't be changed
	2 = i;				// Error. Bcos Rvalue (2) cann't be changed

	dog d1;				// d1 is Lvalue
	d1 = dog(); 		// dog() - (default constructor) is Rvalue of user defined type (class)
	
	int j = sum(3, 4);	// sum(3, 4) is Rvalue

	//Rvalues: 2, 4, i+2, dog(), sum(3,4), x+y
	//Lvalues: x, i, d1, p, q
	//////////////////////////////////////////////////////////////////////////////////////////////

	// Reference (or) Lvalue Reference
	int k;
	int& r = k; // r is a Lvalue Reference. Bcos 'r' reference the Lvalue 'k'.
	int& rr = 2; // Error. Bcos 2 is a Rvalue

	// Exception: Constant Lvalue reference can be assign a Rvalue;
	const int& cr = 2; // OK

	int t = 5;
	square(t); // OK. Bcos 't' is Lvalue
	square(5); // Error. Bcos '5' is Rvalue and cann't assigned to '&x'
	// Workaround
	squareC(t); // OK. Bcos 't' is Lvalue
	squareC(5); // OK. Bcos assigning to 'cont &x'
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Lvalue can automatically change to Rvalue depends upon the context
	int e = 5; // e - Lvalue, 5 - Rvalue
	int w = e; // e - Rvalue (implicity changed from Lvalue), w - Lvalue.

	// Rvalue can change into Lvalue only by explicit conversion
	int v[3];
	*(v+1) = 5; // (v+1) - Rvalue but can be changed to Lvalue by *(v+1)

	return 0;
}

Misconception about Lvalue and Rvalue:
Wrong 1: function or operator always yields Rvalue.
int y = sum(3,4);	// yes, function yields Rvalue
int x = i + 3;		// yes, operator yields Rvalue

int myGlobal;
int& foo() { return myGlobal; }
foo() = 50; // function foo() return Lvalue not Rvalue

array[3] = 10; // Operator [] almost always generate Lvalue not Rvalue

Wrong 2: Lvalues are always modifiable.
const int c = 9; // c - Lvalue
c = 10; // Error. c is not modifiable

Wrong 3: Rvalues are not modifiable.
i + 3 = 6;		// Error. Yes, (i+3) Rvalue is not modifiable
sum(3,4) = 7;	// Error. Yes, sum(3,4) returns Rvalue is not modifiable
// But it is only applicable for build in types.

// It is not true for user defined types (class)
class dog { };
dog().bark(); 	// bark() may change the state of default constructor dog() which is Rvalue.





//////////////////////////////////////////////////////////////////////////////////
#include <iostream>

class sriVector {
public:
	int size;
	int* _arr; // A big array

			   // Default constructor
	sriVector(int sz) {
		size = sz;
		_arr = new int[size];
		for (int i = 0; i < size; ++i) {
			_arr[i] = i * 10;
		}
	}

	// Copy Constructor - Deep copy
	// Copy constructor is called on three instances
	// 1. When instantiating one object and initializing it with values from another object.
	// 2. When passing an object by value.
	// 3. When an object is returned from a function by value.
	sriVector(const sriVector& rhs) {
		size = rhs.size;
		_arr = new int[size];
		for (int i = 0; i < size; ++i) {
			_arr[i] = rhs._arr[i];
		}
	}

	// Move Constructor - inexpensive shallow copy
	sriVector(sriVector&& rhs)  // rvalue reference as the paramenter
	{
		size = rhs.size;
		_arr = rhs._arr;
		rhs._arr = nullptr;
	}

	// Destructor
	~sriVector() {
		delete[] _arr; // destroys local v's -> { _arr=0x0105a3d0 {0} }
	}
};

sriVector createSriVector()
{
	// 2 copies created - one from default and another from copy/move constructor
	sriVector v(5); // calls default constructor;         v -> {size=5 _arr=0x0105a3d0 {0} }
	return v;		// calls copy/move constructor; tempObj -> {size=5 _arr=0x01050578 {0} }					
}					// calls destructor and clears local v's-> {_arr=0x0105a3d0 {0} }

					// 1 copy created because of function's pass by value
void foo(sriVector x) // v	{size=5 _arr=0x0105a3d0 {0} }	
{
	// do something
	int a = 2;
}						// calls destructor and clears local x's-> {_arr=0x01050578 {0} }

void foo_ref(sriVector& x) // No copy operation bcos pass by reference
{
	// do something
	int a = 2;
}							// calls destructor

							// Pass by Lvalue (explicit extra variable used) -  Copy Constructor
							// Pass by Rvalue (internal temp object)         -  Move Constructor
int main()
{
	// 1. NO MOVE CONSTRUCTOR and EXTRA VARIABLE USED ON FUNCTION PASS BY VALUE
	// createSriVector():	1. Default Constructor
	//						2. Copy Constructor - When an object is returned from a function by value.
	//						3. Destructor
	sriVector reusable = createSriVector();
	// foo():				4. Copy Constructor - When passing an object by value.
	//						5. Destructor
	foo(reusable);			 // Pass by Lvalue - calls copy constructor

							 // 2. MOVE CONSTRUCTOR and EXTRA VARIABLE USED ON FUNCTION PASS BY VALUE
							 // createSriVector():	1. Default Constructor
							 //						2. Move Constructor - When an object is returned from a function by value.
							 //						3. Destructor - local object destruction on function out of scope
	sriVector reusable = createSriVector();
	// foo():				4. Copy Constructor - When passing an object by value.
	//						5. Destructor
	foo(reusable); // Pass by Lvalue

				   // Force to change Lvalue to Rvalue
	foo(std::move(reusable));// Pass by Rvalue - calls move constructor. 
							 // reusable is destroyed here

							 // 3. NO MOVE CONSTRUCTOR and INTERNAL TEMP USED ON FUNCTION PASS BY VALUE
							 // createSriVector():	1. Default Constructor
							 //						2. Copy Constructor - When an object is returned from a function by value.
							 //						3. Destructor 
							 // foo():
							 //						4. Destructor
	foo(createSriVector()); // Pass by Rvalue - Calls move constructor

	foo_ref(createSriVector()); // Calls no constructor bcos it's pass by reference

								// 4. MOVE CONSTRUCTOR and INTERNAL TEMP USED ON FUNCTION PASS BY VALUE
								// createSriVector():	1. Default Constructor
								//						2. Move Constructor - When an object is returned from a function by value.
								//						3. Destructor 
								// foo():
								//						4. Destructor
	foo(createSriVector()); // Pass by Rvalue

	return 0;
}

sriVector(const sriVector& rhs) // Copy Constructor
sriVector(sriVector&& rhs)	    // Move Constructor

sriVector& operator=(const sriVector& rhs) // Copy assignment Operator
sriVector& operator=(sriVector&& rhs)      // Move assignment Operator




/////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>

Move Constructor / Move Assignment Operator :
Avoids costly and unnecessary deep copying.
1. Particularly powerful when both passing by value / reference are needed.
2. Not needed for the case function objects are only passed by reference.

sriVector(const sriVector& rhs) // Copy Constructor
sriVector(sriVector&& rhs)	    // Move Constructor

sriVector& operator=(const sriVector& rhs) // Copy assignment Operator
sriVector& operator=(sriVector&& rhs)      // Move assignment Operator



class sriVector {
public:
	int size;
	int* _arr; // A big array

			   // Default constructor
	sriVector(int sz) {
		size = sz;
		_arr = new int[size];
		for (int i = 0; i < size; ++i) {
			_arr[i] = i * 10;
		}
	}

	// Copy Constructor - Deep copy
	// Copy constructor is called on three instances
	// 1. When instantiating one object and initializing it with values from another object.
	// 2. When passing an object by value.
	// 3. When an object is returned from a function by value.
	sriVector(const sriVector& rhs) {
		size = rhs.size;
		_arr = new int[size];
		for (int i = 0; i < size; ++i) {
			_arr[i] = rhs._arr[i];
		}
	}

	// Move Constructor - inexpensive shallow copy
	sriVector(sriVector&& rhs)  // rvalue reference as the paramenter
	{
		size = rhs.size;
		_arr = rhs._arr;
		rhs._arr = nullptr;
	}

	// Destructor
	~sriVector() {
		delete[] _arr; // destroys local v's -> { _arr=0x0105a3d0 {0} }
	}
};

sriVector createSriVector()
{
	// 2 copies created - one from default and another from copy/move constructor
	sriVector v(5); // calls default constructor;         v -> {size=5 _arr=0x0105a3d0 {0} }
	return v;		// calls copy/move constructor; tempObj -> {size=5 _arr=0x01050578 {0} }					
}					// calls destructor and clears local v's-> {_arr=0x0105a3d0 {0} }

					// 1 copy created because of function's pass by value
void foo(sriVector x) // v	{size=5 _arr=0x0105a3d0 {0} }	
{
	// do something
	int a = 2;
}						// calls destructor and clears local x's-> {_arr=0x01050578 {0} }

void foo_ref(sriVector& x) // No copy operation bcos pass by reference
{
	// do something
	int a = 2;
}							// calls destructor

							// Pass by Lvalue (explicit extra variable used) -  Copy Constructor
							// Pass by Rvalue (internal temp object)         -  Move Constructor
int main()
{
	// 1. NO MOVE CONSTRUCTOR and EXTRA VARIABLE USED ON FUNCTION PASS BY VALUE
	// createSriVector():	1. Default Constructor
	//						2. Copy Constructor - When an object is returned from a function by value.
	//						3. Destructor
	sriVector reusable = createSriVector();
	// foo():				4. Copy Constructor - When passing an object by value.
	//						5. Destructor
	foo(reusable);			 // Pass by Lvalue - calls copy constructor

							 // 2. MOVE CONSTRUCTOR and EXTRA VARIABLE USED ON FUNCTION PASS BY VALUE
							 // createSriVector():	1. Default Constructor
							 //						2. Move Constructor - When an object is returned from a function by value.
							 //						3. Destructor - local object destruction on function out of scope
	sriVector reusable = createSriVector();
	// foo():				4. Copy Constructor - When passing an object by value.
	//						5. Destructor
	foo(reusable); // Pass by Lvalue

				   // Force to change Lvalue to Rvalue
	foo(std::move(reusable));// Pass by Rvalue - calls move constructor. 
							 // reusable is destroyed here

							 // 3. NO MOVE CONSTRUCTOR and INTERNAL TEMP USED ON FUNCTION PASS BY VALUE
							 // createSriVector():	1. Default Constructor
							 //						2. Copy Constructor - When an object is returned from a function by value.
							 //						3. Destructor 
							 // foo():
							 //						4. Destructor
	foo(createSriVector()); // Pass by Rvalue - Calls move constructor

	foo_ref(createSriVector()); // Calls no constructor bcos it's pass by reference

								// 4. MOVE CONSTRUCTOR and INTERNAL TEMP USED ON FUNCTION PASS BY VALUE
								// createSriVector():	1. Default Constructor
								//						2. Move Constructor - When an object is returned from a function by value.
								//						3. Destructor 
								// foo():
								//						4. Destructor
	foo(createSriVector()); // Pass by Rvalue

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
class sriVector {
public:
	int size;
	int* _arr; // A big array

			   // Default constructor
	sriVector(int sz) {
		size = sz;
		_arr = new int[size];
		for (int i = 0; i < size; ++i) {
			_arr[i] = i * 10;
		}
	}

	// Copy Constructor - Deep copy
	// Copy constructor is called on three instances
	// 1. When instantiating one object and initializing it with values from another object.
	// 2. When passing an object by value.
	// 3. When an object is returned from a function by value.
	sriVector(const sriVector& rhs) {
		size = rhs.size;
		_arr = new int[size];
		for (int i = 0; i < size; ++i) {
			_arr[i] = rhs._arr[i];
		}
	}

	// Move Constructor - inexpensive shallow copy
	sriVector(sriVector&& rhs)  // rvalue reference as the paramenter
	{
		size = rhs.size;
		_arr = rhs._arr;
		rhs._arr = nullptr;
	}

	// Destructor
	~sriVector() {
		delete[] _arr; // destroys local v's -> { _arr=0x0105a3d0 {0} }
	}
};

sriVector createSriVector()
{
	// 2 copies created - one from default and another from copy constructor
	sriVector v(5); // calls default constructor;         v -> {size=5 _arr=0x0105a3d0 {0} }
	return v;       // calls deep copy constructor; tempObj -> {size=5 _arr=0x01050578 {0} }
					// calls destructor and clears local v's-> {_arr=0x0105a3d0 {0} }
}

// 1 copy created because of function's pass by value
void foo(sriVector x) // v	{size=5 _arr=0x0105a3d0 {0} }	
{
	// do something
	int a = 2;
	// calls destructor and clears local x's-> {_arr=0x01050578 {0} }
}

int main()
{
	// 1. NO MOVE CONSTRUCTOR and EXTRA VARIABLE USED ON FUNCTION PASS BY VALUE
	// createSriVector():	1. Default Constructor
	//						2. Copy Constructor - When an object is returned from a function by value.
	//						3. Destructor
	sriVector reusable = createSriVector();
	// foo():				4. Copy Constructor - When passing an object by value.
	//						5. Destructor
	foo(reusable);

	// 2. MOVE CONSTRUCTOR and EXTRA VARIABLE USED ON FUNCTION PASS BY VALUE
	// createSriVector():	1. Default Constructor
	//						2. Move Constructor - When an object is returned from a function by value.
	//						3. Destructor - local object destruction on function out of scope
	sriVector reusable = createSriVector();
	// foo():				4. Copy Constructor - When passing an object by value.
	//						5. Destructor
	foo(reusable);

	// 3. NO MOVE CONSTRUCTOR and INTERNAL TEMP USED ON FUNCTION PASS BY VALUE
	// createSriVector():	1. Default Constructor
	//						2. Copy Constructor - When an object is returned from a function by value.
	//						3. Destructor 
	// foo():
	//						4. Destructor
	foo(createSriVector());


	// 4. MOVE CONSTRUCTOR and INTERNAL TEMP USED ON FUNCTION PASS BY VALUE
	// createSriVector():	1. Default Constructor
	//						2. Move Constructor - When an object is returned from a function by value.
	//						3. Destructor 
	// foo():
	//						4. Destructor
	foo(createSriVector());




	// Method 1: Passing object using extra variable(reusable). 3 Object copies take place.
	// 1. by Default constructor but destroyed when the createSriVector goes out of scope
	// 2. by Copy constructor when returning the object from the function createSriVector
	// 3. by Copy constructor when passing the object from the function foo
	// sriVector reusable = createSriVector();  // 2 Object Creation , 1 Object destroy from step 1.
	// foo(reusable); // 1 Object Creation, 1 Object destroy from step 3.

	// Method 2:
	// createSriVector():
	//	1. Call default constructor for object construction
	//  2. Calls move constructor instead of copy constructor on returning object from the function. 
	//     So temp object quickly shallow copied and returned to the caller
	// sriVector reusable = createSriVector();  // 2 Object Creation , 1 Object destroy from step 1.
	// foo(reusable); // 1 Object Creation, 1 Object destroy from step 3.

	// Method 2: Passing object using internal temporary variable. 2 Object copies take place.
	// 1. by Default constructor but destroyed when the createSriVector goes out of scope
	// 2. by Copy constructor when returning the object from the function createSriVector
	// No copy constructor gets called when passing by value of temp object but temp object gets
	// destroyed on the exit of function definition foo 
	//foo(createSriVector()); // 2 Object Creation, 2 Object destroy from step 1.



	///////////////// 1 new objects is created ///////////////////
	// Again another new object is constructed by calling the copy constructor 
	// instead of reusing the existing one
	//foo(reusable); // calls deep copy constructor

	// Method 2: Passing object using internal temporary variable. 2 Object copies take place.
	// 1. by Default constructor but destroyed when the createSriVector goes out of scope
	// 2. by Copy constructor when returning the object from the function createSriVector
	// createSriVector() returns rvalue that's a temporary object, then
	// deep copy construct called for creating another copy of the temporary object 
	// foo(createSriVector());

	////////////////////////////////////////////
	// sriVector v(5); // default constructor
	// for (int i = 0; i < v.size; ++i)
	// 	std::cout << v._arr[i] << " ";
	// sriVector dCopy(v); // deep copy constructor
	// for (int i = 0; i < dCopy.size; ++i)
	// 	std::cout << dCopy._arr[i] << " ";

	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

// Function overload by lvalue and rvalue references
void print(int& i)  { std::cout<< " lvalue reference " << i << std::endl; }
void print(int&& i) { std::cout<< " rvalue reference " << i << std::endl; }

// Consider both lvalue and rvalue are the same and ambiguity with both print(int&) and print(int&&)
// void print(int i)   { std::cout<< "pass by value"    << i << std::endl; }

int main()
{
	/////////////////////////////////
	// Rvalue and Lvalue References
	// It is useful for doing 
	// 1. Moving Semantics [resource management]
	// 2. Perfect Forwarding
	/////////////////////////////////
	// C++ 11 - 	
	int a = 5;  // a is a lvalue, 5 is a rvalue
	int& b = a; // b is a lvalue reference (C++ 03 - this is called just a 'reference')
	// int&& c;	// c is rvalue reference

	int x = 10;
	print(x); // calls print(int&)  - bcos x is lvalue
	print(4); // calls print(int&&) - bcos 4 is rvalue

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

template<typename func>
void filter(func f, std::vector<int> v)
{
	for(auto i: v) {
		if(f(i)) std::cout<< i << " ";
	}
}

int main()
{
	/////////////////////////////////
	// Lambda function
	/////////////////////////////////
	// C++ 11 - 	anonymous function

	std::cout << [] (int x, int y) { return x + y; } (3,4) << std::endl; // 7
	auto f =     [] (int x, int y) { return x + y; }; // storing lamda function in a variable
	std::cout << f(3,4) << std::endl; // 7

	// Functional programming approach
	std::vector<int> vec = {1, 2, 3, 4, 5, 6};
	filter([] (int x) { return x > 3; }, vec);			// 4 5 6
	filter([] (int x) { return x > 3 && x < 6; }, vec); // 4 5

	int y = 4; 
	// [&] - for accessing the local variables inside the lambda function.
	// That is telling the compiler that we want 'variable capture'.
	filter([&] (int x) { return x > y;}, vec); // 5 6

	return 0;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
//ref: https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=vs-2019
int main()
{
	///////////////////////////////////////////////
	// Additional char / string literal supports
	///////////////////////////////////////////////
	// C++ 03 - 
	// Character literals
	char    c0 =   'A'; // char
	wchar_t c2 =  L'A'; // wchar_t

	// String literals
	char* a 	= "sridhar"; // const char*
	wchar_t* b 	= L"sridhar"; // const wchar_t*

	// C++ 11 - Better support for unicode
	// Character literals
	auto c1 = u8'A'; // char
	auto c3 =  u'A'; // char16_t
	auto c4 =  U'A'; // char32_t

	// Multicharacter literals (note - single quote)
	auto m0 = 'abcd'; // int, value 0x61626364

	// String literals
	char* b 	= u8"sridhar";	// const char*, encoded as UTF-8 
	char16_t* c = u"sridhar";	// const char16_t*, encoded as UTF-16
	char32_t* d = U"sridhar";	// const char32_t*, encoded as UTF-32

	// Raw string type - All characters are the same, no special meaning of backslash, forwardslash etc.,
	char* raw = R"(sridhar \\)";// (const char*). Outputs: 'sridhar \\'  - raw string.
	auto R1 = u8R"("Hello \ world")"; // const char*, encoded as UTF-8
	auto R2 =  LR"("Hello \ world")"; // const wchar_t*
	auto R3 =  uR"("Hello \ world")"; // const char16_t*, encoded as UTF-16
	auto R4 =  UR"("Hello \ world")"; // const char32_t*, encoded as UTF-32

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
// C++ 03
unsigned int getSize03() { return 5; }

// C++ 11
// constexpr - forces the compile to do the computation at compile time
constexpr unsigned int getSize11()		{ return 5; }
constexpr unsigned int cubed(int x )	{ return x * x * x; }

int main()
{
	/////////////////////////////////
	// constexpr
	/////////////////////////////////
	// C++ 03 -  
	int arr[6]; // OK
	int ary[ getSize03() + 4 ]; // Error at Compile time
	

	// C++ 11 - 	
	int ary[ getSize11() + 4 ]; // Compile time error
	// Increase the program speed by compile time computation
	int cube = cubed(5); // computed at compile time rather than run time,

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////////
// delete - delete the automatica type conversion and copy operations
//////////////////////////////////////////////////////////////////////
// C++ 03 -  
class base03 {
public:
	base03(int age) { }
};

// C++ 11 - 
class base11 {
public:
	base11(int age) { }
	base11(double) = delete;
	base11& operator= (const base11&) = delete;
};

int main()
{
	base03 i(2);
	base03 d(5.0);	// Automatically converts double to int
	i = d;			// Assignment using compiler generated assignment operator

	base11 ii(2);
	base11 dd(5.0);	// Compile time error -  attempting to reference a deleted function
	ii = dd;		// Compile time error -  attempting to reference a deleted function

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// = default [force the compiler to generate the default constructor]
//////////////////////////////////////////////////////////////////////
// C++ 03 -  
class dog {
public:
	dog(int age) { }
};

// C++ 11 - 	
class cat {
	cat(int age) { }
public:
	cat() = default; // forces the compiler to generate the default constructor
};

int main()
{
	dog d;		// Error - default constructor is not found
	dog d(2);	// OK
	cat c;		// default constructor will create automatically	

	return 0;
}

//////////////////////////////////////////////////////////////////////////
#include <iostream>

///////////////////////////////////////////////////////////////////////////
// final - for avoiding deriving a class / overriding a virtual function
///////////////////////////////////////////////////////////////////////////
// C++ 11 
class cat final { // cat class cannot be derived

};

class dog {
	virtual void bark() final { }; // bark() virtual function cannot be overridden in the derived class 
};

int main()
{
	cat c;
	dog d;

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// override (for virtual function)
// To avoid inadvertently create a new function in derived class instead of overriding.
///////////////////////////////////////////////////////////////////////////////////////
// C++ 03 - No check for whether or not function is overrided.
class base {
	virtual void A(int);		// {} - not needed
	virtual void B() const {};	// {} - must
	void C() {};				// {} - must
};

class derived : public base {
	// different param - not overriden. A new function is created
	virtual void A(double)  {}; // No Error
	// const is missing - not overriden. A new function is created
	virtual void B()  {};		// No Error
	// virtual keyword is missing in the base function. A new function is created
	void C() {};				// No Error
};


// C++ 11 - Shows compile time error if there is no proper function override structure	
class base {
	virtual void A(int);		// {} - not needed
	virtual void B() const {};	// {} - must
	void C() {};				// {} - must
};

class derived : public base {	
	virtual void A(double) override {};	// Compile time Error -  no function to override
	virtual void B() override {};		// Compile time Error -  no function to override
	void C() override {};				// Compile time Error -  no function to override
};

int main()
{
	derived d;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// C++ 03 - Cann't call one constructor from another constructor
// Need to use a common function for code sharing
class dog03 {
public:
	void init() { std::cout << " I'm Tommy "; } // Common function 
	dog03() { init(); }
	dog03(int age)
	{
		init();
		std::cout << " My age is " << age;
	}
};

// C++ 11 - Supports calling once constructor function from another
class dog11 {
public:
	dog11() { std::cout << " I'm Tommy "; }

	// calling other constructor function directly
	dog11(int age) : dog11()
	{
		// Limitation: dog11() should be called first (not on middle or last)
		std::cout << " My age is " << age;
	}
};

int main()
{
	//////////////////////////////////////////////////////////////////////////////////
	// Delegating Constructor - reuse the constructor code from another constructor
	/////////////////////////////////////////////////////////////////////////////////

	dog03 a = 5;
	dog11 b = 9;

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>

int main()
{
	/////////////////////////////////
	// static_assert
	/////////////////////////////////

	// C++ 03 -  run time assert only supported
	int *ptr = NULL;
	int test = 9;
	// <cassert> header is needed, && / () need for printing the msg
	assert( ptr == NULL &&  "ptr should not be null"); // OK
	assert( test != 9 && "test should be 9");    // run time assert bcos test value is 4
	assert(("test should be 9", test != 9));	// run time assert bcos test value is 4	

	// C++ 11 - compile time assert	is supported. Comes with <iostream> header
	const int cont_int = 5; // Note: const is must	
	static_assert(cont_int > 2, "cont_int value must be greater than 2"); // OK
	// Compile type error - cont_test value must be greater than 10
	static_assert(cont_int > 10,"cont_int value must be greater than 10"); // 
	// static_asset only support 'constant expression' so const is must for integer

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	/////////////////////////////////
	// enum class
	/////////////////////////////////
	// C++ 03 - enum are integer type
	enum apple  { greenApple,  redApple  }; // Error: enum apple = { greenApple,  redApple  };
	enum orange { smallOrange, bigOrange };
	apple a = greenApple;
	orange o = bigOrange;
	if(a == o) std::cout << " greenApple and bigOrange are the same "; // Logical Error: greenApple and bigOrange are the same
	else std::cout<<" greenApple and bigOrange are not the same ";

	// C++ 11 - enum is a class not a integer type
	enum class apple  { greenApple,  redApple  }; // Error: enum apple = { greenApple,  redApple  };
	enum class orange { smallOrange, bigOrange };
	apple a = apple::greenApple; // Note: scope operator
	orange o = orange::bigOrange;
	// Compilation error - we haven't define == operator for (apple and orange classes)
	if(a == o) std::cout << " greenApple and bigOrange are the same ";
	else std::cout<<" greenApple and bigOrange are not the same ";
	// enum class made strongly typed

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
#include <iostream>

void foo(int i)    { std::cout << " foo_int "   << std::endl; }
void foo(char* pc) { std::cout << " foo_char* " << std::endl; }

int main()
{
	/////////////////////////////////
	// nullptr
	/////////////////////////////////

	// C++ 03 - uses NULL to represent both zero and null pointer 
	foo(NULL); // Error - Ambiguity

	// C++ 11 - Dedicated 'nullptr' to represent the null pointer
	foo(NULL);    // calls foo(int i)
	foo(nullptr); // calls foo(char* pc)

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

int main()
{
	/////////////////////////////////
	// Auto Type
	/////////////////////////////////

	std::vector<int> v = { 1,2,3,4,5 };

	// C++ 03
	// Iterator
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) { std::cout << *it; }


	// C++ 11: Uses auto type
	// Iterator
	for (auto it = v.begin(); it != v.end(); ++it) { std::cout << *it; }

	//forEach - read only
	for (int i : v) { std::cout << i; } // works on any class that has begin() and end()
										// or
	for (auto i : v) { std::cout << i; } // 1 2 3 4 5

										 //foreach - both read and write 
	for (auto& i : v) // reference type
	{
		// Changes the values in v
		std::cout << ++i; // 2 3 4 5 6
	}

	auto a = 6;   // a is a integer
	auto b = 6.0; // b is a double

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>

// To run the build task that you defined in tasks.json,
// press Ctrl+Shift+B or from the main menu choose View > Command Palette and 
// start typing "Tasks: Run Build Task". The option will appear before you finish typing.

// g++ -g -o main main.cpp

// https://code.visualstudio.com/docs/cpp/config-mingw

/////////////////////////////////////////////
// Uniform Initialization / Curly Brace Initialization:
// There are 3 type of Initialization using curly brance
// 1. Initialization_list constructor
// 2. Regular Constructor that takes the appropriate parameters   
// 3. Aggregate initializer

////////////////////////////////////////////
// 2. Uniform Initialization / Curly Brace Initialization -  Search Order
// 1. Initialization_list constructor
// 2. Regular Constructor that takes the appropriate parameters
// 3. Aggregate initializer
/*
class dog {
public:
// Priority - 3 (Aggregate initializer)
int age;

// Priority - 2 (Regular Constructor)
dog(int age) {
this->age = age;
}

// Priority - 1 (Initialization_list)
dog(const initializer_list<int>& v) {
this->age = *(v.begin());
}
};
*/
int main()
{

	// dog d{3};

	printf("sri");
	vector<int> v;


	std::cout << "dhar";

	return 0;
}


#include <iostream>
#include <vector>
#include <string>
using namespace std;

/////////////////////////////////////////////
// 2. Uniform Initialization -  Search Order
////////////////////////////////////////////
// 1. Initialization_list constructor
// 2. Regular Constructor that takes the appropriate parameters
// 3. Aggregate initializer

class dog {
	public:
	// Priority - 3 (Aggregate initializer)
	int age;

	// Priority - 2 (Regular Constructor)
	dog(int age) { 
		this->age = age;
	}

	// Priority - 1 (Initialization_list)
	dog(const initializer_list<int>& v) {
		this->age = *(v.begin());
	}
};


/////////////////////////////////
// 2. Aggregate Initialization
/////////////////////////////////
// C++ 03
class dog03 {				// Aggregate class or struct
public:
	int age;
	string name;
};

//////////////////////////////////
// 3. Constructor Initialization
//////////////////////////////////
// C++ 11 - extends the curly brace initialization to constructor arguments as well
class dog11 {
public:
	dog11(int age, string name) { 
		cout << age << name;
	}

	void test(int age, string name) {
		cout << age << name;
	}
};

int main()
{
	dog d{3};
	
	dog03 d03 = { 5, "Tommy" }; // Aggregate Initialization
	cout << d03.age << d03.name;	

	dog11 d11 = { 5, "Tommy" }; // Constructor Initialization
	//d11.test = { 10, "test" }; // Error - initializer list cannot be used as the right operand of this assignment operator

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	/*
	////////////////////////
	// 1. Initializer List
	////////////////////////

	// C++ 03 Initializer List
	// Array - Supported
	int arr[3] = { 5,6,7 };

	// Vector - Not supported
	vector<int> v3;
	v3.push_back(5);
	v3.push_back(6);
	v3.push_back(7);

	// C++ 11 Initializer List
	// Vector - Supported
	vector<int> v11 = { 5,6,7 }; // Calling initializer_list constructor
	// Similliarly all the relevant STL containers have been updated to accept 'intializer list'.
	*/

	return 0;
}

// Define your own 'initializer_list' constructor:
#include<initializer_list>
#include <iostream>
#include <vector>
using namespace std;

class sriVector {
	vector<int> m_vec;
public:
	sriVector(const initializer_list<int>& v)
	{		
		for (initializer_list<int>::iterator itr = v.begin(); itr != v.end(); ++itr) {
			m_vec.push_back(*itr);
		}
	}
	
};

int main()
{
	sriVector v = { 0,2,3,4 };
	sriVector v2{ 1,3,5,7 }; // effectively the same
	return 0;
}
#endif


