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