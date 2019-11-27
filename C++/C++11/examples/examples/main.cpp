#if 1











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

/* 
Regular Expression:  pattern "match" strings of text.
The C++ standard library supports multiple regular expression grammars.
ECMAScript (default) - grammar used by JavaScript and the .NET languages.(More powerful)
basic                - POSIX basic regular expressions 
extended             - POSIX extended regular expressions 
awk                  - Unix awk
grep                 - Unix grep
egrep                - Unix extended grep

*/
// Ref: C++ 11 Library: Regular Expression 1
// https://www.youtube.com/watch?v=v_8rdQjOuxw&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=13&t=0s
#include <iostream>
#include <regex>
using namespace std;


// Checking pattern is exist or not
	int main() {
	string str;
		while (true) {
			cin >> str;

			regex e("abc");

			// entire string match is must (more strict)
			bool isFullStringMatch = regex_match(str, e); // NO: aabc; YES - abc

			// any substring match is enough
			bool isSubStringMatch  = regex_search(str, e); //  NO - Abc, azbc; YES - aabc, aaaabcccc;
			
			// ignore case
			// NO: abc/n (or) abc; YES: aBcd (using regex_match)
			regex e("abc.", regex_constants::icase); // . Any 1 character except newline
			regex e("abc?");              // ? Zero or 1 preceding character               
			regex e("abc*");              // *       Zero or more preceding character
			regex e("abc+");              // +       One of more preceding character	 
			regex e("ab[cd]*");           // [...]   Any character inside the square brackets          
			regex e("ab[^cd]*");          // [...]   Any character not inside the square brackets
			regex e("ab[cd]{3}");         // only 3 characters
			regex e("ab[cd]{3,}");        // 3 or more characters
			regex e("ab[cd]{3,5}");       // 3,4 or 5 characters 
			regex e("abc|de[fg]");        // | - Or	  
			regex  e("(abc)de+\\1");      // \1 - First group, abcdeeabc
			regex  e("(ab)c(de+)\\2\\1"); // abcdeeedeeeab
			// email filter - sridharkritha@gmail.com
			regex e("[[:w:]]+@[[:w:]]+\.com"); // [[:w:]] word character: digit, number, or underscore

			regex e("abc.$");                  // $  string should 'end'   with abc.; zwerabcq
			// .+ One or more preceeding characters
			// Change the regular expression grammar to grep
			regex e("^abc.+", regex_constants::grep | regex_constants::icase); // ^  string should 'begin' with abc;
			// NO: abczy; YES: abcz+ (+ has no special meaning in grep unlike ECMAScript grammar)

			cout << (isFullStringMatch ? "Matched" : "Not matched") << endl << endl;
		}
	}

// Replace the source string by group
int main() {
	// regex_replace
	string str = "...sridhar@yahoo.com,###  ##raman@gmail.com,;;;;  ;;;;kavitha@hotmail.com;;;;";

	regex e("([[:w:]]+)@([[:w:]]+)\.com");

	// ...sridhar is on yahoo,###  ##raman is on gmail,;;;;  ;;;;kavitha is on hotmail;;;;
	cout << regex_replace(str, e, "$1 is on $2");
	// sridhar is on yahooraman is on gmailkavitha is on hotmail
	cout << regex_replace(str, e, "$1 is on $2", regex_constants::format_no_copy);
	// sridhar is on yahoo
	cout << regex_replace(str, e, "$1 is on $2", regex_constants::format_no_copy|regex_constants::format_first_only);

	std::cin >> str;
}

// Extract ONE
// Store the matched sub group strings in a container[don't do for the entire input string]
int main() {
	string str = "<email>...sridhar@yahoo.com,###  ##raman@gmail.com,;;;;  ;;;;kavitha@hotmail.com;;;;<end>";
	smatch m;   // smatch (type) - stores the matched strings in a collection

	regex e("([[:w:]]+)@([[:w:]]+)\.com"); // (group 1) - user name, (group 2) - domain name

	bool found = regex_search(str, m, e); // extract the groups and store it


	cout << "m.size() " << m.size() << endl; // 3 - no.of matched result
	// m[0] = sridhar@yahoo.com, m[1] = sridhar, m[0] = yahoo

	// m[0].str()  - The entire match (same with m.str(), m.str(0))
	// m[1].str()  - The substring that matches the first group  (same with m.str(1))
	// m[2].str()  - The substring that matches the second group
	// m.prefix()  - Everything before the first matched character
	// m.suffix()  - Everything after the last matched character

	for (int n = 0; n< m.size(); n++) {
		cout << "m[" << n << "]: str()=" << m[n].str() << endl; 
	//    cout << "m[" << n << "]: str()=" << m.str(n) << endl; // alternate form
	//    cout << "m[" << n << "]: str()=" << *(m.begin()+n) << endl; // alternate form
	}
	cout << "m.prefix().str(): " << m.prefix().str() << endl; // <email>...
	cout << "m.suffix().str(): " << m.suffix().str() << endl; // ,###
}

// Extract ALL - by 1.  Regex Iterator and 2. Regex Token Iterator
/**************** Regex Iterator ******************/
int main() {
	string str = "<email>...sridhar@yahoo.com,###  ##raman@gmail.com,;;;;  ;;;;kavitha@hotmail.com;;;;<end>";

	regex e("([[:w:]]+)@([[:w:]]+)\.com");

	sregex_iterator pos(str.cbegin(), str.cend(), e);
	sregex_iterator end;  // Default constructor defines past-the-end iterator
	for (; pos != end; pos++) {
		cout << "Matched:  "  << pos->str(0) << endl;
		cout << "user name: " << pos->str(1) << endl;
		cout << "Domain: "    << pos->str(2) << endl;
		cout << endl;
	}
}


	Matched:  sridhar@yahoo.com
	user name: sridhar
	Domain: yahoo

	Matched:  raman@gmail.com
	user name: raman
	Domain: gmail

	Matched:  kavitha@hotmail.com
	user name: kavitha
	Domain: hotmail





/**************** Regex Token Iterator ******************/
// Ref: C++ 11 Library: Regular Expression 3 -- Iterators
// https://www.youtube.com/watch?v=_79j_-2xMrQ&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=14
int main() {

	string str = "<email>...sridhar@yahoo.com,###  ##raman@gmail.com,;;;;  ;;;;kavitha@hotmail.com;;;;<end>";
	//regex e("[[:punct:]]+");  // Printable character that is not space, digit, or letter.
	//regex e("[ [:punct:]]+"); 
	regex e("([[:w:]]+)@([[:w:]]+)\.com");

	// 0 = full, 1 = username, 2 = domainname extracted, -1 = Unmatched remaining
	sregex_token_iterator pos(str.cbegin(), str.cend(), e, 0); 
	sregex_token_iterator end;  // Default constructor defines past-the-end iterator
	for (; pos != end; pos++) {
		cout << "Matched:  " << *pos << endl; // pos->str(); - alternate form
	}
	cin >> str;

	return 0;
}


	Matched:  sridhar@yahoo.com
	Matched:  raman@gmail.com
	Matched:  kavitha@hotmail.com


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: https://stackoverflow.com/questions/2275076/is-stdvector-copying-the-objects-with-a-push-back
std::vector makes a copy of an object you want to push_back.
A vector cannot keep a reference or a pointer of an object without a copy ?

Objects are values. Assignment makes a copy. T

std::vector<T>::push_back(argument) -  creates a copy of the argument and stores it in the vector. 

// Ref: C++ 11: Resource Managing Class
// https://www.youtube.com/watch?v=xtYJgPR9iCg&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=12&t=0s

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
class Person {
public:
	void printName() { cout<< *pName_;}
	Person(string name): pName_(new string (name)) { cout << "Person is created: " << *pName_ << endl; }
	// ~Person() { cout << "Person is destroyed: " << *pName_ << endl;  delete pName_; }
private:
	// string* pName_;
	// shared_ptr<string> pName_; // smart pointer solution
	unique_ptr<string> pName_;    // light weight smart pointer solution
	
};

int main()
{
	vector<Person> v;
	// local object created but NOT destroyed 
	v.push_back(Person("George")); // OK
	v.emplace_back("Sridhar"); // OK

	Person t("Raman");
	// v.push_back(t);    // ERROR: Unique ptr is not copiable only movable
	v.push_back(move(t)); // Unique ptr is not copiable only movable

	v.front().printName();         // OK
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
If you want to store pointers to objects in your vector, create a std::vector<whatever*> instead of std::vector<whatever>.
However, you need to make sure that the objects referenced by the pointers remain valid while the vector holds a reference 
to them (smart pointers utilizing the RAII idiom solve the problem).

Since C++11, push_back will perform a 'move' instead of a 'copy' if the argument is an 'rvalue reference'. 
(Objects can be converted to 'rvalue references' with std::move().)

From C++11 onwards, all the standard containers (std::vector, std::map, etc) support move semantics, meaning that you 
can now pass rvalues to standard containers and avoid a copy:

// Example object class.
class object
{
	private:
	int             m_val1;
	std::string     m_val2;

	public:
	object(int val1, std::string &&val2) : m_val1(val1), m_val2(std::move(val2))  { }
};

std::vector<object> myList;

// #1 Copy into the vector.
object foo1(1, "foo");
myList.push_back(foo1);

// #2 Move temporary into vector (no copy).
myList.push_back(object(453, "baz"));

// #3 Move into the vector (no copy).
object foo2(1024, "bar");
myList.push_back(std::move(foo2));

// #4 Create instance of object directly inside the vector (no copy, no move).
myList.emplace_back(453, "qux");
Alternatively you can use various smart pointers to get mostly the same effect:

// Using - std::unique_ptr
std::vector<std::unique_ptr<object>> myPtrList;

// #5a unique_ptr can NOT be copied only be 'moved'.
auto pFoo = std::make_unique<object>(1, "foo");
myPtrList.push_back(std::move(pFoo));

// #5b unique_ptr can NOT be copied only be 'moved'.
myPtrList.push_back(std::make_unique<object>(1, "foo"));
std::shared_ptr example

// Using - std::shared_ptr
std::vector<std::shared_ptr<object>> objectPtrList2;

// #6 shared_ptr can be used to retain a copy of the pointer and update both the vector value and the local copy simultaneously.
auto pFooShared = std::make_shared<object>(1, "foo");
objectPtrList2.push_back(pFooShared);
// Pointer to object stored in the vector, but pFooShared is still valid.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: C++ 11 Library: Unique Pointers
// https://www.youtube.com/watch?v=YeI6V2O5BFE&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=10
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Unique Pointers (Replaced auto_ptr in C++ 03): 
// 1. exclusive owenership of an object.
// 2. light weight smart pointer

class Dog {
	// Can also be used as a member 
	// unique_ptr<Bone> pB;  // instead of Bone* pB; Bcos it prevents memory leak even constructor fails.
	public:
		string m_name;
		void bark() { cout << "Dog " << m_name << " rules!" << endl; }
		Dog() { cout << "Nameless dog created." << endl; m_name = "nameless"; }
		Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name; }
		~Dog() { cout << "dog is destroyed: " << m_name << endl; }
};

/*
Output:	Dog is created: Gunner
		Dog Gunner rules!
		dog is destroyed: Gunner
*/
void test() {
	unique_ptr<Dog> pD(new Dog("Gunner"));
	pD->bark();
}

void deallocate() {
	// release
	// Output:	Dog is created: Release
	// 			Dog Release rules!
	// 			pRls is empty.   (NOTE: Object is not deleted on out of scope)
	unique_ptr<Dog> pRls(new Dog("Release"));
	pRls->bark();

	// 1. Like shared pointer 'get()', 'release()' return the raw pointer, using that pointer you can delete the object explicitly
	// 2. Unlike shared pointer 'get()', 'release()' releases its object ownership, so no more it's responsobility to delete the
	// object when it goes out of scope	
	Dog* p = pRls.release();
	if (!pRls)  cout << "pRls is empty.\n";
	else        cout << "pRls is not empty.\n";

	// reset (or) nullptr
	// Output:	Dog is created: Reset
	// 			Dog Reset rules!
	// 			dog is destroyed: Reset
	// 			pRst is empty.
	unique_ptr<Dog> pRst(new Dog("Reset"));
	pRst->bark();
	// delete the pointed object at the point of call and then reset the pointer to nullptr.
	pRst.reset(); // (or) pRst = nullptr;
	if (!pRst)  cout << "pRst is empty.\n";
	else        cout << "pRst is not empty.\n";

	// reset to another new object:
	// Output:	Dog is created: Reset
	// 			Dog Reset rules!
	// 			Dog is created: Smokey
	// 			dog is destroyed: Reset
	// 			pRstAssg is not empty.
	// 			dog is destroyed: Smokey
	unique_ptr<Dog> pRstAssg(new Dog("Reset"));
	pRstAssg->bark();
	// delete the last pointer object at the point of call and acquire a new ownership of another object 
	pRstAssg.reset(new Dog("Smokey"));
	if (!pRstAssg)  cout << "pRstAssg is empty.\n";
	else            cout << "pRstAssg is not empty.\n";

	// move - transferring ownership from one unique pointer to another
	// Output:	Dog is created: MoveOne
	// 			Dog is created: MoveTwo
	// 			Dog MoveOne rules!
	// 			dog is destroyed: MoveOne
	// 			Dog MoveTwo rules!
	unique_ptr<Dog> pM1(new Dog("MoveOne"));
	unique_ptr<Dog> pM2(new Dog("MoveTwo"));
	pM1->bark();

	// 1. pM1 owns MoveTwo.
	// 2. pM2 becomes empty.
	// 3. MoveOne is destroyed.
	pM1 = move(pM2);
	pM1->bark();
}

void f(unique_ptr<Dog> p)
{
	// Output:	Dog PassingUniquePointer rules!
	p->bark();
} // NOTE: dog is destroyed here. Prints => dog is destroyed : PassingUniquePointer

unique_ptr<Dog> getDog()
{
	// Output:	Dog is created : ReturningUniquePointer
	unique_ptr<Dog> p(new Dog("ReturningUniquePointer"));
	return p; // NOTE: move is not needed bcos it is pass by value automatically move semantics invoked
} // NOTE: dog is NOT destroyed here

void func()
{
	// Output:	Dog is created : PassingUniquePointer	
	unique_ptr<Dog> pPassing(new Dog("PassingUniquePointer"));
	// NOTE: move is needed
	f(move(pPassing)); // NOTE: dog object is NOT destroyed here. Passing by address NOT by value
	// pPassing is empty.
	if(!pPassing) cout << "pPassing is empty.\n";

	unique_ptr<Dog> pReturning = getDog();
} // NOTE: ReturningUniquePointer object is destroyed here. Prints => dog is destroyed: ReturningUniquePointer

// Output(2 times):	Nameless dog created.
// 					Nameless dog created.
// 					Nameless dog created.
// 					dog is destroyed : nameless
// 					dog is destroyed : nameless
// 					dog is destroyed : nameless
void arrayOfObjDelection() // Deleting array of objects
{
	// shared pointer needs user defined delete function
	shared_ptr<Dog> pS(new Dog[3], [](Dog* p) {delete[] p;});

	// unique pointer DON'T need any user defined delet function
	unique_ptr<Dog[]> pU(new Dog[3]);
}

int main ()
{
	// func();
	arrayOfObjDelection();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: C++ 11 Library: Weak Pointers
// https://www.youtube.com/watch?v=EWoMjuN5OH4&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=9

#include<iostream>
#include<string>
#include<memory> // shared pointers
using namespace std;

class Dog {
	weak_ptr<Dog> m_pFriend;
 // shared_ptr<Dog> m_pFriend;

public:
	string m_name;
	void bark() { cout << "Dog " << m_name << " rules!" << endl; }
	Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name; }
	~Dog() { cout << "dog is destroyed: " << m_name << endl; }

	void makeFriend(shared_ptr<Dog> f) { 
		m_pFriend = f; 
	}

	void showFriend() {
		if(!m_pFriend.expired()) // check weak pointer is empty or not
		{
			// cout<<"My friend is" << m_pFriend->m_name; // Error - weak pointer has no ownership to access

			// lock()- creates a shared pointer out of weak pointer to make sure the it will not be deleted while accessing.
			// Bcos the object is only deleted if there is no shared pointer pointing it. 
			cout<<"My friend is" << m_pFriend.lock()->m_name; // lock

			// how many shared pointers pointing to that object
			cout<<"Number of shared pointer is pointing to " << m_pFriend.use_count();
		}
	}
};

void foo() {
	shared_ptr<Dog> p1(new Dog("Gunner"));
	shared_ptr<Dog> p2(new Dog("Tank"));

	p1->makeFriend(p2);
	p2->makeFriend(p1); // cyclic reference
}

int main() {
	shared_ptr<Dog> p1(new Dog("Gunner"));
	shared_ptr<Dog> p2(new Dog("Tank"));

	p1->makeFriend(p2);
	
	p1->showFriend();
	return 0;
}

Dog is created: Gunner
Dog is created: Tank
My friend isTankNumber of shared pointer is pointing to 1
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref : https://www.youtube.com/watch?v=e8Cw17p_BiU&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=6
// C++ 11: Compiler Generated Functions

#include <iostream>

// Empty Class
class Dog { }; // all - 1,2,3,4,5,6 - are generated by the compiler.

			   // Compiler Generated Function
class Dog {
	// C++ 03
	Dog();                      // Default Constructor
	Dog(const Dog&);            // Copy Constructor
	Dog& operator=(const Dog&); // Copy Assignment Operator
	~Dog();                     // Destructor

								// C++ 11
	Dog(Dog&&);                 // Move Constructor
	Dog& operator=(Dog&&);      // Move Assignment Operator
};


// C++ 03
// 1. Default Constructor      (generated only if 2 is not declared by user [no constructor is declared by user])
// 2. Copy Constructor         (generated only if 2 is not declared by user)
// 3. Copy Assignment Operator (generated only if 3 is not declared by user)
// 4. Destructor               (generated only if 4 is not declared by user)

// C++ 11 (ignoring the additional restrictions on Copy Constructor/Assignment )
// 1. Default Constructor      (generated only if 2 and 5 are not declared by user [no constructors are declared by user])
// 2. Copy Constructor         (generated only if 5 and 6 are not declared by user)
// 3. Copy Assignment Operator (generated only if 5 and 6 are not declared by user)
// 4. Destructor               (generated only if 4 is not declared by user)
// 5. Move Constructor         (generated only if 2,3,4,6 are not declared by user)
// 6. Move Assignment Operator (generated only if 2,3,4,5 are not declared by user)

// C++ 11 (Like Move Constructor/Assignment, additional restrictions added for the generation of Copy Constructor/Assignment)
// 2. Copy Constructor         (generated only if 3,4,5 and 6 are not declared by user)
// 3. Copy Assignment Operator (generated only if 2,4,5 and 6 are not declared by user)

// Case 1: Ignoring the additional restrictions on Copy Constructor/Assignment
class Cow { // only 1,2,4 (not 5,6)
	Cow& operator=(const Cow&) = delete;
};

// Case 2: Additional restrictions added for the generation of Copy Constructor/Assignment
class Cow { // only 1,4 (2 will be decprecated)
	Cow& operator=(const Cow&) = delete;
	Cow(const Cow&) = default; // will bring back the compiler generated copy consturctor (if you want)
};


class Cat { // only - 3,4 - are generated by the compiler.( But 3 will be deprecated)
	Cat(const Cat&) { }       // Copy Constructor
							  // or
	Cat(const Cat&, int = 0) {} // Copy Constructor
};

class Fish { // only - 1,2,3 - are generated by the compiler.( But 2 and 3 will be deprecated)
	~Fish() { }
};

// Note: Object constructed using below class is only movable not copyable.
// Normally, mutex and socket objects are constructed using below class form.
class Duck { // only - 4 - is generated by the compiler.
	Duck(Duck&&) { } // Move Constructor
					 // or
	Duck(Duck&&, int = 0) { } // Move Constructor
};

class Frog { // Only - 2,3,4,5,6 - are generated by the compiler.
	Frog(int = 0) { } // Default Constructor
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ref: C++ 11: User Defined Literals
	// https://www.youtube.com/watch?v=2xUJTXeBZmE&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH&index=5
	#include <iostream>

	int operator"" _bin(const char* str, size_t s)
	{
		int ret = 0;
		for(int i = 0; i < s; ++i) {
			ret = ret << 1;
			if(str[i] == '1') ret += 1;
		}
		return ret;
	}

	int main()
	{
		// note: "110_bin" is wrong. "110"_bin is correct
		std::cout<< "110"_bin << std::endl; // 6
		std::cout<< "1100110"_bin << std::endl; // 102
		return 0;
	}



// 14. New String Literals
// 



  // C++ 03:
  char*     a = "string";  

  // C++ 11:
  char*     a = u8"string";  // to define an UTF-8 string. 
  char16_t* b = u"string";   // to define an UTF-16 string. 
  char32_t* c = U"string";   // to define an UTF-32 string. 
  char*     d = R"string \\"    // to define raw string. 


// Literals: 
// Literals are constants.  
	// C++ has 4 kinds of literals:
	integer         ---  45
	floating point  ---  4.5 
	character       ---  'z' 
	string          ---  "Dog"


	// Suffixes for Literals (suffix specifies type)
	45;   // int literal
	45u;  // unsigned int
	45l;  // long

	//C++ 99:
	long double height = 3.4;  // Metres? Centimeters? Inches?

	// Ideally, always attach units to the values: 
	ratio = 3.4cm / 2.1mm; //  ratio = 3.4 * 10mm / 2.1mm

	// C++ 11 - User Defined Literals - [ operator"" suffix ]:
	long double operator"" _cm(long double x) { return x * 10; }
	long double operator"" _m(long double x)  { return x * 1000; }
	long double operator"" _mm(long double x) { return x; }

	int main() {
	long double height = 3.4_cm;
	cout << height  << endl;              // 34
	cout << (height + 13.0_m)  << endl;   // 13034
	cout << (130.0_mm / 13.0_m)  << endl; // 0.01
	}

	// Note: add constexpr to make the translation happen in compile time.
	constexpr long double operator"" _cm(long double x) { return x * 10; }


	// Restriction: it can only work with following parameters:
	char const*
	unsigned long long
	long double
	char const*, std::size_t
	wchar_t const*, std::size_t
	char16_t const*, std::size_t
	char32_t const*, std::size_t
	// Note: return value can be of any types.







// Example:
constexpr int operator"" _hex(char const* str, size_t l) { 
   // Convert hexdecimal formated str to integer ret
   return ret;
}

constexpr int operator"" _oct(char const* str, size_t l) { 
   // Convert octal formated str to integer ret
   return ret;
}

int main() {
   cout << "FF"_hex << endl;  // 255
   cout << "40"_oct << endl;  // 32
   cout << "FF"_oct << endl;  // checking happens at compile time
}


// C++ went a long way to make user defined types (classes) to behave same as build-in types.
// User defined literals pushes this effort even further


/////////////////////////////////////////////////////////////////////////////////////////////////////
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


