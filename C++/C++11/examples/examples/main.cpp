#if 1







#else
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
// Ref:
// 
#include <iostream>
using namespace std;

int main()
{


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: https://www.youtube.com/watch?v=ZBK7aZ8v6vE&list=PLE28375D4AC946CC3&index=27
// Advanced C++: Koenig Lookup and Namespace Design

/*
 * Why Koenig Lookup?
 */

// Example 1:
namespace A
{
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
   void g( ) { cout << " calling A::g() \n"; }
}

int main() {
   A::X x1;
   g(x1);   // Koenig Lookup, or Argument Dependent Lookup (ADL)
   g();     // Error
}

Two reason for using Koenig Lookup :
// 1. The Practical Reason for using Koenig Lookup
	std::operator<<(std:cout, "Hi. \n");
	// Other way of writing above by using Koenig Lookup
	std::cout << "Hi.\n"; // definition of << (std::operator<<) is found inside std namespace by Koenig Lookup
	// If there is NO Koenig Lookup then 
	std::cout std::<< "Hi.\n"; // Error

// 2. Theoretical Reason: What is the interface of a class?
namespace A
{
   class C {
      public:
	  // Inferfaces of C
      void f() = 0;
      void g() = 0;
   };
   void h(C); // ALSO Inferface of C
   ostream& operator<<( ostream&, const C& ); // ALSO Inferface of C
}
void j(C); // NOT a Inferface of C bcos outsidie the namespace A

/*
 Definition of class: 
 	A class describes a set of data, along with the functions(NOT only member function) that operate on that data.
 */

/* 
 Class Interface includes: 
	1. Functions that operate on class C and in a same namespace with C are part of C's interface.
	2. Functions that are part of C's interface should be in the same namespace as C.

 */
// C class interfaces
   A::C c; 
   c.f();
   h(c);

namespace A { 
   class C {}; 
   int operator+(int n, A::C) { return n+1; } // User defined operator +
}

int main()
{
   A::C arr[3]; 
   std::accumulate(arr, arr+3, 0);  // return 3
}

// accumulate - Defined in C++ standard library <numeric>
namespace std {
   template <class InputIterator, class T>
      T accumulate ( InputIterator first, InputIterator last, T init )
   {
     while ( first!=last )
       init = init + *first++;  // calls user defined operator + using Koenig lookup instead of operator + from std namespace.
     return init;
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Namespace and Keyword "using"
// https://www.youtube.com/watch?v=YliqZh6s9ig&list=PLE28375D4AC946CC3&index=25

// 1. using namespace - directive [ONLY namespace]: to bring all namespace members into current scope
   using namespace std;


 
// 2. using - declaration [namespace / Class]:
//		a. Bring one specific namespace member to current scope. 
//		b. Bring a member from base class(NOT namespace) to current class's scope. 

   using std::cout;
   using B::f; 



using namespace std;  // case 1:   global scope
using std::cout;      // case 2.a: global scope

class B {
   public:
   void f(int a);
};
 
class D : private B { 
   public:
      void g() { 
         using namespace std;  // case 1: local scope
         cout << "From D: \n";
      }
      void h() { 
         using std::cout;     // case 2.a: local scope
         cout << "From D: \n";
      }
	  // f() is privately derived so it cann't be accessed outside. BUT 'using B::f;' brings to current scope and made it possible !
      using B::f;   // case 2.b:  class scope

	  // using std::cout;     // illegal - it cann't be in class scope
	  // using namespace std; // illegal - it cann't be in class scope
};

D d;
d.f(8); // works even it is privately derived function

/* 
	Notes:
	1. using declaration and using directive, when used on namespace, can be used in global or local scope.
	2. using declaration, when used on class members. It should be used in class scope.
 */


// Name Hiding in CLASS:
class B {
   public:
      void f(int a);
};
 
class D : public B { 
   public:
    // using B::f; // AVOIDS name hiding problem
    void f();      // Name Hidding: f() hides the base f(int a)
};

int main() {
   D d;
   d.f(8); // ERROR bcos of name hiding
}

#include<iostream>
// Anonymous Namespace - Namespace doesn't have any name.
void g() { std::cout << "global g()\n"; }

namespace {
	// Within a FILE you can access it like a global functions but it CANN'T be accessed from another FILE just 
	// like a STATIC function [ex: static void h() { std::cout << "h()\n"; } ]
	void g() { std::cout << "g()\n"; }
	void h() { std::cout << "h()\n"; g(); } // call the locall g() defined inside the namespace
}

int main() {
   h(); // calls h() inside the anonymous namespace
   g();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ref: Advance C++: Koenig Lookup - Argument Dependent Lookup (ADL)
// https://www.youtube.com/watch?v=TxgPZXe8XTo&list=PLE28375D4AC946CC3&index=26

// Increases the function name search scope



// Example 1:
// Koenig Lookup or Argument Dependent Lookup (ADL)
namespace A
{
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
}

// void g( X ) { cout << " calling A::g() \n"; } // Ambiguous

int main() {
   A::X x1;
   A::g(x1); // OK
   g(x1);    // NO error - it works !! bcos of Koenig Lookup, or Argument Dependent Lookup (ADL)
   // Compiler searches function name 'g' in 
   // 1. current scope, 
   // 2. scope where it param type has defined - by Koenig lookup and 
   // 3. global scope.
}


// Example 2:
class C {
   public:
   struct Y {};
   static void h(Y) { cout << "calling C::h() \n"; }
};

int main() {
   C::Y y;
   C:: h(y); // OK
   h(y);     // Error bcos Koenig Lookup NOT works for class. It works only for namespace.
}


// Example 3:
namespace A {
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
   void h( X ) { cout << " calling A::h() \n"; }
}

namespace C {
   void g(A::X ) { cout << "calling C::g() \n" ; }
   void j() {
      A::X x;
	  h(x); // OK by Koenig Lookup
      g(x); // ERROR - Ambiguous bcos it sees 2 versions - g( X ) by local and g(A::X ) by Koenig Lookup 
   }
};

int main() {
   C::j();
}

// Example 4:
namespace A {
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
   void h( X ) { cout << " calling A::h() \n"; }
}

class C {    // Changed from namespace to class
public:
   void g(A::X ) { cout << "calling C::g() \n" ; }
   void j() {
      A::X x;
	  h(x); // OK by Koenig Lookup
      g(x); // OK - no ambiguity. In class, once g is found in the local scope it STOPS further search.
   }
};

int main() {
	C c;
    c.j();
}


// Example 5:
namespace A
{
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
}

class B {
   void g(A::X ) { cout << "calling B::g() \n" ; }
};

class C : public B {
   public:
   void j() {
      A::X x;
      g(x); // OK - no ambiguity. calling B::g()
   }
};

int main() {
   C c;
   c.j();
}

// Name hiding for NAMESPACE
namespace A
{
   void g(int) { std::cout << " calling A::g() \n"; }

   namespace C {
	  // Name hiding: g() hides g(int)
      void g() { std::cout << "calling C:g() \n" ; }
      void j() {
         //using A::g; // solves the name hiding problem
         g(9); // Error - Ambiguous
      }
   }
}

int main() {
   A::C::j();
}


namespace A
{
   struct X {};
   void g(X) { std::cout << " calling A::g() \n"; }

   namespace C {
	  // Name hiding: g() hides g(X)
      void g( ) { std::cout << "calling C:g() \n" ; }
      void j() {
         X x;
         g(x); // NO Error by name hiding. Bcos it uses by Koenig Lookup and prints - calling A::g()
      }
   }
}

int main() {
   A::C::j();
}


/*
	  Name Lookup Resolution Sequence

	  With namespaces:
	  current namespace scope(higher priority) > next enclosed scope(lower priority) > ... > global scope(lowest priority)

	  To override the resolution sequence:
	  1. Qualifier or using declaration
	  2. Koenig lookup

	  With classes:
	  current class scope(higher priority) > parent scope(lower priority) > ... > global scope(lowest priority)

	  To override the resolution sequence:
	   - Qualifier or using declaration (CANNT use Koenig lookup)	

	  Name hiding: name in the higher priority scope overrides the same name in the next lower priority scope
 */





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Code Reuse - Inheritance vs Composition
// https://www.youtube.com/watch?v=tXFqS31ZOFM&list=PLE28375D4AC946CC3&index=24

// Code Reuse with Inheritance
class Dog {   // BaseDog - Don't use Base in the class name it breaks the implementation details
	// common activities
};

class BullDog : public Dog {
	// Call the common activities to perform more tasks.
};

class ShepherdDog : public Dog {
	// Call the common activities to perform more tasks.
};


// Code Reuse with Composition
class ActivityManager {
	void eatBiscuit() { ... } // common activities
};

class Dog {
	virtual void eatBiscuit() = 0; // Inherit only from pure abstract class
};

class BullDog : public Dog {
	ActivityManager* pActMngr;
	// Call the common activities through pActMngr
	void eatBiscuit() { pActMngr->eatBiscuit(); }
};

class ShepherdDog : public Dog {
	ActivityManager* pActMngr;
	// Call the common activities through pActMngr
	void eatBiscuit() { pActMngr->eatBiscuit(); }
};


/*
	Code reuse: Composition is better than Inheritance
	1. Less code coupling between reused code and reuser of the code 
	   a. Child class automatically inherits ALL parent class's public members.
	   b. Child class can access parent's protected members.
	      - Inheritance breaks encapsulation

	2. Dynamic binding
	   a. Inheritance is bound at compile time
	   b. Composition can be bound either at compile time or at run time.
 */

/*
Inheritance Guidline:
	Never use inheritance for code reuse!
	Inherit interfaces only; never inherit implementation!
	All base classes should be Pure Abstract Classes!
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Duality of Public Inheritance
//   - Inheritance of Interface
//   - Inheritance of Implementation

// Ref: Advanced C++: Duality Of Public Inheritance - Interface & Implementation
// https://www.youtube.com/watch?v=iFK-D13LX2U&list=PLE28375D4AC946CC3&index=23

class Dog {
public:
	// Pure Virtual Function - support ONLY Inheritance of Interface
	virtual void bark() = 0;
	// Non Virtual Function - supports BOTH Inheritance of Interface and Implementation
	void run() { cout << "I am running."; } // Don't override it. Otherwise it breaks IS-A relationship
	// Impure Virtual Function - supports Inheritance of Interface and DEFAULT Implementation
	virtual void eat() { cout << "I am eating. "; } // Can be overriden if needed.
protected:
	// protected function support ONLY Inheritance of Implementation
	void sleep() { cout << " I am sleeping. "; }
};

class Yellowdog : public Dog {
public:
	virtual void barks() { cout << "I am a yellow dog.\n";}
	void iSleep() { sleep(); }
};


/*
 	Types of Inheritance in C++:
 	1. Pure virtual public function   - inherit interface only.
 	2. Non-virtual public function    - inherit both interface and implementation.
 	3. Impure virtual public function - inherit interface and default implementation
 	4. Protected function             - inherit implementation only
 	As a software designer, it is very important to separate the concepts of interface and implementation.
 */


/*
 When to use - Interface Inheritance ?
 1. Subtyping - One type can be safely used instead of other type
 2. Polymorphism
 
 */
	virtual void bark() = 0;

/*
 * Pitfalls:
 *  -- Be careful of interface bloat.
 *  -- Interfaces do not reveal implementation.
 */


/*
 Disadvantages of Implementation Inheritance 
    - Increase code complexity
    - Not encouraged to use it
 */
public:
	// Supports both Interface and Implementation - NOT bad.
	void run() { cout << "I am running."; }
	virtual void eat() { cout << "I am eating. "; }
protected:
	// ONLY Implementation inheritance - NOT encouraged
	void sleep() { cout << " I am sleeping. "; }

/*
 Guidelines for Implementation Inheritance:
 	1. Do not use inheritance for code reuse, use composition.
 	2. Minimize the implementation in base classes. Base classes should be thin.
 	3. Minimize the level of hierarchies in implementation inheritance.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Multiple Inheritance - Devil or Angel
// https://www.youtube.com/watch?v=7APovvvftQs&list=PLE28375D4AC946CC3&index=22

// Multiple Inheritance -- A class is directly derived from more than one base classes.
class InputFile {
   private:
   		void open();
   public:
   		void read();
};

class OutputFile {
   public:
   		void open();
   		void write();
};

class IOFile : public InputFile, public OutputFile {
	// 2 different open() instances and 2 different write() instances
};

int main() {
   IOFile f;
   f.open(); // ambiguous error even though private open() is not accessible in main()
   f.OutputFile::open(); // OK
}

Move the common parts to a separate common base class.

class File {            //         File
   public:              //         /  \        -
   string name;         // InputFile  OutputFile
   void open();         //         \  /
};                      //        IOFile

class InputFile  : public File { };
class OutputFile : public File { };

// Diamond shape of hierarchy
class IOFile : public InputFile, public OutputFile {
	// STILL 2 different open() instances and 2 different name instances even though it uses common base class File
};

int main() {
   IOFile f;
   f.open(); // ambiguous error - open() from which path of the Diamond shape hierarchy
   f.InputFile::name = "File1"; 
   f.OutputFile::name = "File2"; // Why we need 2 instance of 'name' ???
}


class File {            //         File
   public:              //         /  \ 
   string name;         // InputFile  OutputFile
   void open();         //         \  /
};                      //        IOFile

class InputFile  : virtual public File { }; // Virtual Inheritance
class OutputFile : virtual public File { };

class IOFile : public InputFile, public OutputFile {
	// Only one instance of open() and name bcos of virtual inheritance
};  // Diamond shape of hierarchy

int main() {
   IOFile f;
   f.open();         // OK
   f.name = "File1"; // OK
}

// Problem by Initialization

// Virtual base class
class File {     
   public:      
   File(string fname);
};             

//  1st. File(fname) {} initialization is needed but IGNORED by the compiler 
class InputFile : virtual public File {
   InputFile(string fname) : File(fname) {}
};

//  2nd. File(fname) {} initialization is needed but ALSO IGNORED by the compiler 
class OutputFile : virtual public File {
   OutputFile(string fname) : File(fname) {}
};

// 3rd. File(fname) {} initialization USED by the compiler 
// C++ Rule: Initialization of base virtual class is the responsibility of LAST derived class
class IOFile : public InputFile, public OutputFile {
   IOFile(string fname) : OutputFile(fname), InputFile(fname), File(fname) {}
};  

int main() {
   IOFile f;
}

Better Solution would be using Pure Abstract Class it solves the problem of multiple object instances, multiple object initialization,
multiple member functions/Data and even we do NOT need virtual inheritance. 
Note: File, InputFile and OutputFile needs to change to PAC.


/*
   Abstract Class: A class has one or more pure virtural functions.
 
   Pure Abstract Classes: 
   A class containing only pure virtual functions
     - no data 
     - no concrete functions
     - no private protected functions
 */

	class OutputFile {
	public:
	void write() = 0;
	void open() = 0;
	};

// Interface Segregation Principle (ISP): Split large interfaces into smaller and more specific ones so that clients
// only need to know about the methods that are of interest to them.

class Engineer { // Pure Abstract Classes
   public:
   ...; // 40 APIs
};

class Son { // Pure Abstract Classes
   public:
   ...; // 50 APIs
};

class Andy : public Engineer, Son  // NO need for virtual inheritance
{
   public:
   ...; // 500 APIs
};

/*
 * Benefits of ISP:
 * 1. Easy-to-use interfaces
 * 2. Static type safety
 */

/*
	* Summary:
	* 1. Multiple Inheritance is an important technique, e.g. ISP
	* 2. Derive only from PACs when using Multiple Inheritance.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert Dynamic Polymorphism to Static Polymorphism
/*
	Disadvantages of Dynamic Polymorphism:
	1. Extra Memory needed to create V-table.
	2. Extra run time cost due to dynamic binding.
*/

// Ref: Advanced C++: Static Polymorphism
// https://www.youtube.com/watch?v=-WV9vWjhI3g&list=PLE28375D4AC946CC3&index=21
#include <iostream>
using namespace std;

// Dynamic Polymorphism
struct Person { 
	string name;
	int age;
};

class Profession {
   public:
   void taxBand(Person* node) {
      if (node) {
         salaryBenefits(node);
      }
   }
   private:
   virtual void salaryBenefits(Person* node) { } // Dynamic Polymorphism
};

class Doctor : public Profession {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Doctor.\n";
   }
};

class Police : public Profession {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Police.\n";
   }
};
   
int main() {
   Person* p = new Person { "Rajesh", 25 };
   Doctor doc;
   doc.taxBand(p);

   Police pol;
   pol.taxBand(p);
}
// 
/*
 3 things to be maintained in DYNAMIC to STATIC polymorphism conversion:
	* I).   is-a relationship(public inheritance) between base class and derived class
	* II).  Base class defines a "generic" algorithm(salaryBenefits) that's used by derived class
	* III). The "generic" algorithm is customized by the derived class
 */

// Static Polymorphism / Simulated Polymorphism  - Conversion technique used is - CURIOUSLY RECURRING TEMPLATE PATTERN
//		Disadvantage: Eventhough there is no usage of extra heap memory for Vtable and no run time cost of late binding.
//		Different template classes (Doctor/Police) own its separate memory space in the program image [Size of exe will bit bigger]

// TMP - Template Metaprogramming - Moving computation in runtime to compile time
// Non-virtual Interface Idiom (NVI)
template <typename T> class Profession {
   public:
   void taxBand(Person* node) {
      if (node) {
         salaryBenefits(node);
      }
   }
   private: // NO more virtual function
    void salaryBenefits(Person* node) { 
		static_cast<T*>(this)->salaryBenefits(node);  // Static Polymorphism
	}
};

class Doctor : public Profession<Doctor> {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Doctor.\n";
   }
};

class Police : public Profession<Doctor> {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Police.\n";
   }
};

// Other Static Polymorphism by Template
template<typename T>
T Max(std::vector<T> v) {
	T max = v[0];
	for(typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
		if(*it > max) {
			max = *it;
		}
	}
	return max;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Maintain is-a Relation for Public Inheritance
// https://www.youtube.com/watch?v=97iK5r3zNug&list=PLE28375D4AC946CC3&index=19
#include <iostream>
using namespace std;
// Never Override Non-virtual Functions
class Dog {
   // Add virtual key word if you want polymorphism
   public: void bark() { cout << "I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public: void bark() { cout << "I am a yellow dog.\n";};
};

int main() {
   Yellowdog* py = new Yellowdog();
   py->bark();  
   Dog* pd = py;
   pd->bark(); 
}
/*
	// NOT a Polymorphism
	I am a yellow dog.
	I am just a dog.
	// Polymorphism: DIFFERENT class objects act on SAME api will behave DIFFERENTLY.
	I am a yellow dog.
	I am a yellow dog.
*/


// Never redefine default parameter for the virtual function
class Dog {
   public: 
   virtual void bark(string msg = "just a") { cout << "I am " << msg << " dog.\n";};
   virtual void run(int speed) { cout << "I am run at speed of " << speed << endl;};
};

class Yellowdog : public Dog{
 // Virtual functions are bound dynamically.
 // Default parameters are bound STATICALLY.
  public: 
  void bark(string msg = "a yellow") { cout << "I am " << msg << " dog.\n";};
  // Shadowing: After seeing the run(string), compiler STOP searching for another run() eventhough they have different args. 
  void run(string txt = "I cann't run") { cout << txt << endl;};
  using Dog::run;
};

int main() {
   Yellowdog* py = new Yellowdog();
   Dog* pd = py;
   py->bark(); // I am a yellow dog.
   pd->bark(); // I am just a dog. WRONG polymorphism. calls Yellowdog bark() BUT gets the default value from Dog NOT from Yellodog

   py->run(45); // ERROR. It don't call Dog's run(), it call yellowdog run() BUT arg mismatch
   py->run(45); // OK. If you declare 'using Dog::run;' I am run at speed of 45
   py->run();   // I cann't run
}

/* 
 * Summary of pitfalls:
 * 1. Precise definition of classes;
 * 2. Don't override non-virtual functions;
 * 3. Don't override default parameter values for virtual functions;
 * 4. Force inheritance of shadowed functions.
 * 5. Be careful of typo in function overriding.
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: https://www.youtube.com/watch?v=EYuPBkgJtCQ&list=PLE28375D4AC946CC3&index=18
// Advanced C++: Inheritance - Public, Protected, and Private
#include <iostream>
using namespace std;

	// Public, Protected, Private Inheritance 
	class B { };
	class D_pub  : public    B { };
	class D_prot : protected B { };
	class D_priv : private   B { };

/*
	They specifies different access control from the derived class to the base class.
	Access Control:
	1. NONE of the derived classes can access anything that is PRIVATE in B.
	2. D_pub  inherits public members of B as PUBLIC and the protected members of B as PROTECTED
	3. D_prot inherits the public and protected members of B as PROTECTED.
	4. D_priv inherits the public and protected members of B as PRIVATE.

	Casting:
	1. ANYONE can cast a D_pub* to B*. D_pub IS A special kind of B. [only IS-A / Derived IS A kind of Base]
	2. D_prot's MEMBERS, FRIENDS, and CHILDREN can cast a D_prot* to B*.
	3. D_priv's MEMBERS and FRIENDS can cast a D_priv* to B*. [HAS-A / ]

*/

// Detailed Example
class B { 
   public:
      void f_pub() { cout << "f_pub is called.\n"; }
   protected:
      void f_prot() { cout << "f_prot is called.\n"; }
   private:
      void f_priv() { cout << "f_priv is called.\n"; }
};


// Public Inheritance
class D_pub : public B { 
   public: 
      void foo() {
         f_pub();   // OK. D_pub's PUBLIC function
         f_prot();  // OK. D_pub's protected function
         f_priv();  // Error. B's private function 
      }
};

// Protected Inheritance
class D_prot : protected B { 
   public: 
    // using B::f_pub; // Declaration brings f_pub function into the scope D_prot
      void foo() {
         f_pub();   // OK. D_pub's protected function
         f_prot();  // OK. D_pub's protected function
         f_priv();  // Error. B's private function 
      }
};


// Private Inheritance
class D_priv : private B { 
   public:
	// using B::f_pub; // Declaration brings f_pub function into the scope D_prot
      void f() {
         f_pub();   // OK. D_priv private function
         f_prot();  // OK. D_priv private function
         f_priv();  // Error. B's private function 
      }
};

int main() {
   D_pub D1;
   D1.f_pub();  // OK. f_pub() is D_pub's public function.
   D1.f_prot(); // Error. f_prot() is D_pub's PROTECTED function you cann't access from main function.

   D_prot D2;
   D2.f_pub();  // Error. f_pub() is D_priv's private function.
   D2.f_pub();  // OK if you have a declartion 'using B::f_pub' under PUBLIC of D_prot

   D_priv D2;
   D2.f_pub();  // OK if you have a declartion 'using B::f_pub' under PUBLIC of D_priv

   B* pB = &D1; // OK
   pB = &D2;    // Error - You cann't
}






Simillarity between  Private Inheritance and Composition:

// Private inheritance: HAS-A relation.similar to COMPOSITION. one contains another.
class Ring {
   public:
   void tinkle() { }
};

// Private Inheritance == Composition
class Dog_Priv : private Ring {
   public:
   using Ring::tinkle; // Brings Dog's public interface
};

// Composition == Private Inheritance
class Dog {
   Ring m_ring;
   public:
   void tinkle() { m_ring.tinkle(); }  // call forwarding
};
// 

Difference between  Private Inheritance and Composition:

class Ring {
   virtual tremble();
   public:
   void tinkle() { tremble(); }
   protected:
   void foo() { }
};

// Private Inheritance
class Dog_Priv : private Ring {
	 // Also have an ACCESS to Dog's PROTECT members
   public:
   using Ring::tinkle; // Brings Dog's public interface
  
};

// Composition
class Dog {
	// NO access to Dog's PROTECT members
   Ring m_ring;
   Ring m_ring2;
   public:
   void tinkle() { m_ring.tinkle(); }  // call forwarding using m_ring
   void shine() { m_ring2.tinkle(); }  // call forwarding using m_ring2
};


class Ring {
   private:
   virtual void tremble() { cout<< "Ring::temble()" << endl; };
   public:
   void tinkle() { tremble(); }
   void glitter() { cout<< "Ring::glitter()" << endl; };
};

// Private Inheritance
class Dog_Priv : private Ring {
	void tremble() { cout<< "Dog_Priv::temble()" << endl; };
	void glitter() { cout<< "Dog_Priv::glitter()" << endl; };
	 // Also have an ACCESS to Dog's PROTECT members
   public:
   using Ring::tinkle; // Brings Dog's public interface
   using Ring::glitter;
};

int main() {
	Dog_Priv d;
	d.tinkle(); // Dog_Priv::temble() - INDIRECTLY ACCESSING Dog_Priv private function in main
	d.glitter(); // ERROR - Dog_Priv private function CANN'T be accessed in main
}




/*
	Preference:
	composition: Decoupled and better object oriented design. More preferred!.
	private inheritance: more elegant polymorphism.
 *
 * E.g. in class ring, add virtual function: tremble(), which is
 *    used in tinkle().
 */




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: All Castings Considered - Part II
// https://www.youtube.com/watch?v=UfrR1nNfoeY&list=PLE28375D4AC946CC3&index=17
#include <iostream>
using namespace std;
// Casting could be risky.

class dog {
public:
	// Atleast only virtual function is needed to use dynamic_cast. Having only Virtual destructor is also OK.
	virtual ~dog() {} 
	virtual void fly() {  cout<< "Dog cannot fly" << endl;  }
};

class yellowdog : public dog {
	int age = 5;
public:  
	void run()  { cout<< "I run fast"  << endl; }
	void bark() { cout<< "woof. I am " << age  << endl; }
	void fly()  { cout<< "Yellow Dog cannot fly. I am " << age  << endl; }
};

int main() {
	dog* pd = new dog();

	// STATIC CAST
	yellowdog* py_ds = static_cast<yellowdog*>(pd); // ALWAYS SUCCEED - BECAREFUL
	cout << "pd = " << pd << endl;       // 0106A2C0
	cout << "py_ds = " << py_ds << endl; // 0106A2C0 (SAME ADDRESS)
	// compiler considers run() as STATIC FUNCTION 
	py_ds->run();  // I run fast
	py_ds->bark(); // woof. I am -33686019 (some random number) - WRONG

	
	// DYNAMIC CAST - WRONG
	// NOT all dog's are yellowdog's
	yellowdog* py_dc = dynamic_cast<yellowdog*>(pd); // dynamic_cast FAIL 
	cout << "pd = " << pd << endl;       // 00EDB8B8
	cout << "py_dc = " << py_dc << endl; // 00000000
	// compiler considers run() as STATIC FUNCTION 
	py_dc->run();  // I run fast <- EVENTHOUGH py is a NULL POINTER
	py_dc->bark(); // CRASH - CANNOT consider as STATIC FUNCTION bcos it uses member variable

	// POLYMORPHIC way without any cast
	yellowdog* deriverPtr = new yellowdog();  // yellowdog* pd = new dog(); <- WRONG way of usage
	dog* basePtr = deriverPtr;
	basePtr->fly();    // YellowDog or Dog depends on existance of virtual key word
	deriverPtr->fly(); // Yellow Dog cannot fly. I am 5 <- ALWAYS YellowDog

	// Polymorphic way (STACK based objects)
	yellowdog derived;
	dog* basePtr = &derived;
	basePtr->fly();
	
	return 0;
}

// CONST CAST - casting could be a handy hack tool
class dog {
	public:
	std::string m_name;
	dog():m_name("Bob") {}
	void bark() const { // object pointer by *this is CONST so you cann't change its content.
		// m_name = "Henry";
		const_cast<dog*>(this)->m_name = "Henry"; // BUT you can change by const_cast
		std::cout << "My name is " << m_name << std::endl;
	}
};


/*
 * =========================================  C++ Style Casting ================================
 *                             Generate_Code   Generate_data      risky   data_type
 * Object Casting:            
 *    static_cast                 yes              yes             2      any types
 *                                                                       (as long as type 
 *                                                                       conversion is defined)
 * Pointer/Reference Casting:
 *    static_cast                 no               no              4     related types
 *    dynamic_cast                yes              no              3     related types(down-cast)
 *    const_cast                  no               no              1     same type
 *    reinterpret_cast            no               no              5      any types
 *
 *
 *
 *
 *
 * =========================================  C Style Casting ================================
 *                             Generate_Code  Generate_data      risky   data_type
 * Object Casting:               yes              yes             5      any types
 *                                                                       (as long as type 
 *                                                                       conversion is defined)
 * Pointer/Reference Casting:    no               no              5      any types
 *
 *
 * Notes can be downloaded at my website: boqian.weebly.com
 *
 * Note:
 * 1. const_cast, dynamic_cast and reinterpret_cast can only work on pointers/references.
 * 2. static_cast of objects is very different from static_cast of pointers. 
 * 3. reinterpret_cast basically reassigning the type information of the bit pattern. 
 *    It should only be used in low-level coding.
 * 4. dynamic_cast does static_cast plus run-time type check.
 * 5. dynamic_cast and static_cast for pointers can only work on related type (e.g., 
 *    base <-> derived).
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * All Castings Considered
 *
 *
 * Type Conversion:
 *    1. Implicit Type Conversion
 *    2. Explicit Type Conversion - Casting
 */

// Ref: Advanced C++: All Castings Considered - Part I
// https://www.youtube.com/watch?v=lglGKxNrLgM&list=PLE28375D4AC946CC3&index=16


// 1. static_cast
int i = 9;
float f = static_cast<float>(i);              // convert object from one type to another
dog d1 = static_cast<dog>(string("Bob"));     // Type conversion NEEDS to be defined.
dog* pd = static_cast<dog*>(new yellowdog()); // convert pointer/reference from one type to a RELATED type (down/up cast)


// 2. dynamic_cast
dog* pd = new yellowdog(); // static cast
yellowdog py = dynamic_cast<yellowdog*>(pd); 
// a. It convert pointer/reference from one type to a RELATED type (down cast - Base to Derived)
// b. perform run-time type check.  If succeed, py==pd; if fail, py==0;
// c. It requires the 2 types to be polymorphic (atleast have one virtual function).

// 3. const_cast
                                           // only works on pointer/reference
const char* str = "Hello, world.";         // only works on SAME type
char* modifiable = const_cast<char*>(str); // cast away constness of the object being pointed to

// 4. reinterpret_cast 
long p = 51110980;
dog* dd = reinterpret_cast<dog*>(p);  // re-interpret the bits of the object pointed to
// The ultimate cast that can cast one pointer to ANY other type of pointer.

// C-Style Casting: A mixture of static_cast, const_cast and reinterpret_cast [NO dynamic_cast] 
	short a = 2000;
	int i = (int)a;   // c-like cast notation
	int j = int(a);   // functional notation



/*
 	Generally C++ style of casts are preferred over the C-style, because:
 	1. Easier to identify in the code.
 	2. Less usage error. C++ style provides:
 	   a. Narrowly specified purpose of each cast, and
 	   b. Run-time type check capability.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//############################################################################
/* 
User Defined Implicit Type Conversion 
	Categories of Type Conversion:
	                                                              Implicit      Explicit(casting)
	Standard Type Conversion (between build in types)                 A            B
	User Defined Type Conversion (between user defined and build in)  C            D
	                                                                           
	
 */
	// Category A: Implicit Standard Type Conversion
	char c = 'A';
	int i = c;  // Integral promotion

	char*  pc = 0; // int -> Null pointer

	void f(int i) { }
	f(c);  // Integral promotion

	dog* pd = new yellowdog();  // pointer type conversion NOT user defined type conversion


/* 
	Category C: Implicit User Defined Type Conversion
	Defined inside class (user defined type)
	There are 2 methods to define implicit user defined type conversion:
		Method 1: Use constructor that can accept a single parameter.
					- convert other types of object into your class
		Method 2: Use the type conversion function  
					- convert an object of your class into other types
 */
// Ref: Advanced C++: Define Implicit Type Conversion
// https://www.youtube.com/watch?v=S7MNPX73FSQ&list=PLE28375D4AC946CC3&index=15
#include <iostream>
using namespace std;
class dog {
   public:
      // Method 1: convert other types of object into your class
      // Convert string type (name) into dog type using constructor      
      // NO explicit key word and 1 arg constuctor -> do object construction and BOTH implicit and explicit conversions
      dog(string name) {m_name = name; }  // NO explicit
	  // WITH explicit key word and 1 arg constuctor -> do object construction and explicit type conversion (NOT implicit conversion)
      // explicit dog(string name) {m_name = name; } // Avoids  inadvertent implicit type conversion.

      string getName() {return m_name;}

	  // Method 2: convert an object of your class into other types
	  operator string () const { return m_name; } // Type Conversion function
  private:
      string m_name;
};

void main ()
{
  string dogname = "Bob";
  dog dog1 = dogname; // Method 1: Convert string type ("Bob") into dog type using constructor
  printf("My name is %s.\n", dog1.getName());
  // NO need of getName() function if you have a type conversion function(Method 2)
  printf("My name is %s.\n", dog1); // Method 2: Converts dog type into string type (%s) using type conversion function
}



/*
 	DESIGN PRINCIPLE: make interface easy to use correctly and hard to use incorrectly.
 	How hard is enough?  Ideally, uncompilable.
 	   General guideline: 
 	   1. Avoid defining seemingly unexpected conversion.
 	   2. Avoid defining two-way implicit conversion.
 */




// Implicit type conversion is useful when creating numerical types of class, such as a rational class.
class Rational {
public:
	// Bcos of default values, it can take single argument as well. So it can be considered as 1 arg constructor with implicit/explicit conversions
	Rational(int numerator = 0, int denominator = 1): num(numerator),den(denominator) {}
	int num;  // Demo only, public data members are not recommended
	int den;

	// * is overloaded for Rational * Rational
	const Rational operator*(const Rational& rhs) {
		// Covert the result(internal multiplication result) into object
		return Rational(num * rhs.num, den * rhs.den); // num * rhs.num => 23 * 2
	}
	// Converts Rational Object to integer
	operator int () const { return num / den; }
};



int main ()
{
	Rational r1 = 23;
	// LEFT to RIGHT evaluation
	// rational * rational(2) => rational(2) can be done by 1 arg constructor,
	Rational r2 = r1 * 2; // * is overloaded for rational multiplication(Rational * Rational) can be done by Rational operator*
	// integer * integer(r1) => Needs Rational to Integer conversion
	Rational r3 = 3 * r1; // * is global ARITHMETIC interger multiplication(like 5x6). AMBIGUOUS to above multiplication.
	// So ONLY either of the one only works not BOTH!. Better to avoid defining two-way implicit conversion.
	return 0;
}

// Solution - Remove two-way implicit conversion and define single way NON-MEMBER rational mulitiplication operator - which works for BOTH
class Rational {
public:
	// Bcos of default values, it can take single argument as well. So it can be considered as 1 arg constructor with implicit/explicit conversions
	Rational(int numerator = 0, int denominator = 1): num(numerator),den(denominator) {}
	int num;  // Demo only, public data members are not recommended
	int den;
};

// Define NON-MEMBER rational mulitiplication operator - which works for BOTH
// Rational r2 = r1 * 2; => r1 * rational(2)
// Rational r3 = 3 * r1; => rational(3) * r1
const Rational operator*(const Rational& lhs, const Rational& rhs) {
return Rational(lhs.num*rhs.num, lhs.den*rhs.den);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Virtual Constructor - Clone() Function
// https://www.youtube.com/watch?v=UHP-DKrxgBs&list=PLE28375D4AC946CC3&index=14
#include <iostream>
using namespace std;

class Dog {
public:
	// copy constructed by itself
	virtual Dog* clone() { return (new Dog(*this));  }
};

class Yellowdog : public Dog {
private:
	// copy constructed by itself
	virtual Yellowdog* clone() { return (new Yellowdog(*this));	   
	// CO-VARIANT RETURN TYPE - that is return Yellowdog instead of Dog eventhough it is inherited from Dog.
	}
};

void foo(Dog* yell) {       // yell is a Yellowdog
	// calls default copy constructor
	Dog* x = new Dog(*yell); // But x is a Dog NOT a Yellowdog identical copy even after default copy constructor

	// Clone functions act like a VIRTUAL CONSTRUCTOR. Exact object type(Yellowdog) is created regardless of cast type (Dog).
	Dog* y = yell->clone();  // y is a Yellowdog by clone
}

int main() {
	Yellowdog yell;
	foo(&yell);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Resource Managing Class
// https://www.youtube.com/watch?v=juQBXTNz4mo&list=PLE28375D4AC946CC3&index=13
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person {
private:
	string* pName_; // Person owns the string through its pointer BUT don't have COPY Constructor/ ASSIGNMENT operator
public:
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }
};


// Solution 1: Define copy constructor and copy assignment operator for DEEP copying
class Person {
private:
	string* pName_;
public:
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }

	string* pName() const { return pName_; }
	Person(const Person& rhs) {   // deep copying by COPY constructor
		pName_ = new string(*(rhs.pName()));
	}
	Person& operator=(const Person& rhs);  // deep copying by copy ASSIGNMENT operator
};

int main() {
	vector<Person> persons;
	persons.push_back(Person("George"));
	// 1. "George" is constructed
	// 2. A copy of "George" is saved in the vector (SHALLOW copy - Copy only the pointer pointing to the resource not resource)
	// 3. "George" is destroyed.

	persons.front().printName(); // CRASH - Copied pointer points to already deleted memory
}



// Solution 2: delete the default copy constructor & copy assignment operator AND manage the object in CLIENT level
class Person {
private:
	// delete the default copy constructor and copy assignment operator by PRIVATE DECLARATION 
	Person& operator=(const Person& rhs);  // deep copying
	Person(const Person& rhs);
public:
	string* pName_; 
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }
};


int main() {
	// STL container requires containee should copiable [should have COPY constructor and copy ASSIGNMENT operator] 
	vector<Person*> persons; // workaround: Store the object POINTER instead of object itself
   persons.push_back(new Person("George")); // NOTE: creating an new object
   persons.front()->printName(); 
   // Manually delete the created objects after use
}


// Solution 3: delete the copy constructor & copy assignment operator AND define CLONE
class Person {
private:
	// delete the default copy constructor and copy assignment operator by PRIVATE DECLARATION 
	Person& operator=(const Person& rhs);  // deep copying
	Person(const Person& rhs);
public:
	string* pName_;
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }
	// Identical COPY of object itself
	Person* Clone() { return new Person(*pName_); }
};

int main() {
	// STL container requires containee should copiable [should have COPY constructor and copy ASSIGNMENT operator] 
	vector<Person*> persons;
	persons.push_back(Person("George").Clone());
	persons.front()->printName();
}

Which solution to use ? Prefer clonable solution 3. Bcos Copy constructor and copy Assignment operator do the deep copy operation 
IMPLICITLY (error prone) BUT using clone we can do the deep copy operation explicitly.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++.Resource Acquisition is Initialization.
// https://www.youtube.com/watch?v=ojOUIg13g3I&list=PLE28375D4AC946CC3&index=10

// Resource Acquisition is Initialization (RAII): 
// Technique used to manage resources: memory, hardware device, network handle, etc.

Mutex_t   mu = MUTEX_INITIALIZER;
 
void functionA()
{
   Mutex_lock( &mu );
   // If there is an exception then locked for ever !
   Mutex_unlock( &mu ); // This line will not be executed
}


// Solution:
class Lock {
   privat:
      Mutext_t* m_pm;
   public:
      explicit Lock(Mutex_t *pm) { Mutex_lock(pm); m_pm = pm;};
      ~Lock() { Mutex_unlock(m_pm); };
}

void functionA() {
   Lock mylock(&mu);
   // Do a bunch of things
}  // The mutex will always be released when mylock is destroied from stack



What happens when resource management object is copied?
   Lock mylock1(&mu);
   Lock mylock2(mylock1);

Solution 1: Do not support copying. 
			Prohibit copying by declaring(not defining) private copy constructor and copy assignment operator.

Solution 2: If you really want the resouce management object copy then support by shared_ptr.
			Reference-count the underlying resource by using shared_ptr.

// Shared pointer template example
template<class Other, class D> shared_ptr(Other * ptr, D deleter);

// The default value for D is "delete", e.g.:
std::tr1::shared_ptr<dog> pd(new dog());

class Lock {
   private:
      std:::shared_ptr<Mutex_t> pMutex;
   public:
      explicit Lock(Mutex_t *pm):pMutex(pm, Mutex_unlock) // The 2nd param of shared_ptr constructor is "deleter" function. 
	  { 
         Mutex_lock(pm);
      }
 };


   Lock mylock1(&mu);		// ref count  = 1
   Lock mylock2(mylock1);	// ref count  = 2


// Another example:

// Some classes
class dog; 
class Trick;

void train(std::shared_ptr<dog> pd, Trick dogtrick);
Trick  getTrick();

int main() {
   train(shared_ptr<dog> pd(new dog()), getTrick()); // Problem - order of param processing is undefind and compiler dependent
}

Suppose a compiler process the argument in the below order
1. new dog();
2. getTrick(); // If there is an exception then memory of 'new dog()' will leaks !!!
3. construct std::shared_ptr<dog>.

// Solution
int main() {
   std::shared_ptr<dog> pd(new dog());
   train(pd, getTrick());
}

Conclusion: Don't combine storing objects in shared pointer with other statement.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Static Initialization Fiasco
// https://www.youtube.com/watch?v=hE77OSTE2J0&list=PLE28375D4AC946CC3&index=11

////////////////////////////////  main.cpp  ////////////////////////
#include <iostream>
#include "Dog.h"
#include "Cat.h"
using namespace std;

Dog d("Gunner"); // global object creation
// Inside Dog.cpp we have another global object creation[ Cat c("Smokey"); ]. Because of they are 
// in different files order of creation is undefined (depends upon the compiler - maybe 'c' before 'd')

int main()
{
	d.bark();
	return 0;
}

///////////////////////////////////////////////
////////////////////////////////  main.cpp  ////////////////////////
// Dog d("Gunner"); // NO more global object creation

int main()
{
	// Singleton::getDog()->bark();
	Singleton s;
	Singleton::getCat()->meow();
	return 0;
}

#endif