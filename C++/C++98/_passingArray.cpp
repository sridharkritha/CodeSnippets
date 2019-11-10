#include <iostream>
using namespace std;

// Passing Array to a function:
// NOTE:
// When passing array to function the Compiler automatically decays' the array into pointer pointing to first element
// of array so it doesn't have any information about the size of the array. So the user should send the array size explicitly.
void fOne(char a[100]) {
	cout<<sizeof(a); // 4
}

void fTwo(char* a) {
	cout<<sizeof(a); // 4	
}

void fThree(char a[]) {
	cout<<sizeof(a); // 4
}

// Alternative Solutions: using pointer and reference

// Forces the caller to pass an array of size 100 only. Caller: fPointer(&cAry);
// C - Version
void fPointer(char (*a)[100]) {
	cout<<sizeof(*a); // 100	
}

// C++ - Version
void fFour(char (&a)[100]) {
	cout<<sizeof(a); // 100
}

// Generic Solutions: using Template
// Forces the caller to pass an array of any size (not decays to pointer)
template< std::size_t N >
void fFive(char (&a)[N]) {
	cout<<sizeof(a); // 100
}

template <typename T, size_t N>
void fSix(const T (&a)[N]) {
	cout<<sizeof(a); // 100
	cout<<N; // 100
}

// Recommended solution
// Caller: fRecommended(cAry, sizeof(cAry));
void fRecommended(char* a, int len) {
	cout<<sizeof(a); // 4
	cout<<len; // 100
}

int main() {
	char cAry[100] = {0};
	std::cout<<sizeof(cAry); // 100
	fOne(cAry);
	fTwo(cAry);
	fThree(cAry);
	fPointer(&cAry); // Note: &
	fFour(cAry);
	fFive(cAry);
	fSix(cAry);
	fRecommended(cAry,sizeof(cAry));
	return 0;
}
