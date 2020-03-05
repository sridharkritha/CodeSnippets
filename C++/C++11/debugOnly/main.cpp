#include <iostream>
// http://www.gotw.ca/publications/mill17.htm

template <typename T> void foo(T) { std::cout << "void foo(T)"; };
template <typename T> void foo(T*) { std::cout << "void foo(T*)"; }; // overload of foo(T)
template <>           void foo<int*>(int*) { std::cout << "foo<int>(int*)";  }; // specialisation of foo(T*)


/*
template <typename T> void foo(T) { std::cout << "void foo(T)"; };
template <>           void foo<int*>(int*) { std::cout << "foo<int>(int*)"; }; // specialisation of foo(T*)
template <typename T> void foo(T*) { std::cout << "void foo(T*)"; }; // overload of foo(T)
*/
int main() {
	foo(new int); // calls foo<int>(int*);
	return 0;
}
/*
The fully specialized version will take precedence over the partially specialized version. 
Classes also support partial specialization, where only some of the templated parameters are specialized. Functions do not support partial specialization as of C++14.

// Ref: https://www.learncpp.com/cpp-tutorial/132-function-template-instances/
// Comparing User defined types
template <typename T>				 // this is the 'template parameter declaration'
const T &max(const T &x, const T &y) // T could be a user defind type so prefer 'const references'
{
	return (x > y) ? x : y;
}

template <class T>
T average(T *array, int length) {
	T sum(0);
	for (int count{ 0 }; count < length; ++count) sum += array[count];
	sum /= length;
	return sum;
}

class Cents {
public:
	int m_cents;
	Cents(int cents) : m_cents{cents} {}

	friend bool operator>(const Cents &c1, const Cents &c2) {
		return (c1.m_cents > c2.m_cents);
	}
	friend std::ostream& operator<< (std::ostream &out, const Cents &cents) {
		out << cents.m_cents;
		return out; // must
	}

	Cents& operator+=(const Cents &cents) {
		m_cents += cents.m_cents;
		return *this;
	}

	Cents& operator/=(int value) {
		m_cents /= value;
		return *this;
	}
};

int main() {
	int i{max(3, 7)}; // calls max(int, int)
	std::cout << i << std::endl;   // 7

	Cents sridhar{5};
	Cents kavitha{10};
	Cents bigger{max(sridhar, kavitha)};
	// std::cout << bigger.m_cents; // 10
	std::cout << bigger << std::endl; // 10

	double array2[]{ 3.12, 3.45, 9.23, 6.34 };
	std::cout << average(array2, 4) << std::endl;

	Cents array3[]{ Cents(5), Cents(10), Cents(15), Cents(14) };
	std::cout << average(array3, 4) << std::endl;

	return 0;
}


//////////////////////////////////////////////////////////////////////////////
int count(0); 
int count{ 0 }; 

int array1[]{ 5, 3, 2, 1, 4 };
int array1[4]{};

int *m_data;
assert(length > 0);
m_data = new int[length];
delete[] m_data;
m_data = nullptr;

int& operator[](int index) {
	assert(index >= 0 && index < m_length);
	return m_data[index];
}
intArray[3] = 10;

*/
