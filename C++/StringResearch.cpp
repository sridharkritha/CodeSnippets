#include<iostream>
#include<string>
#include <sstream>
#include <vector>
using namespace std;

void function(char* pS,size_t len) {
	return;
}

int main() {
	cout<<"String Research:\n";
	// Declaration
	int iResult =0,I=0, iInput =786;
	std::string sResult, S;
	char cResult, C, *pC;
	std::stringstream Sstm; // Using String stream

	// 1.
	// Char to Integer ASCII
	C = 'z';
	iResult = C;      // ASCII value of 'z'.  iResult = . No need for typecast

	// 2.
	// Char to Integer
	C = '5';
	iResult = C - '0'; // Char to Int. iResult = 5. No need for typecast

	// 3.
	// String to Const Char*
	S = "sridhar";
	const char* pcC = S.c_str(); // Useful for C - style parameter passing. Add extra '/0' Character = S.size() + 1
   
	//4.
	// String to Char* (not Const)
	// Whole content copy	
   pC = new char[S.size() + 1]; // Note: +1 for '/0'
   // Method 1:
   strcpy(pC, S.c_str());
   // Method 2:
   std::copy(S.begin(), S.end(), pC); // Copy doesn't NULL terminate. C++ Style
   pC[S.size()] = '\0'; // don't forget the terminating 0
   // do stuff 
   // don't forget to free the string after finished using it
    delete[] pC;
	// Method 3: (Safe and Recommended method)  
	std::vector<char> Vs(S.size()+1);
    std::copy(S.begin(), S.end(), Vs.begin());
    pC = &Vs[0]; // use &pC[0] as a char*   [pointer to start of vector]
	// Method 4: (Unsafe, should be passed along the string size)
	function(&S[0],S.size()); // Not NULL terminated & Non Const
	// Method 5: (Unsafe, should be passed along the string size)
	function(&S.front(),S.size()); // Not NULL terminated & Non Const

	// 5.
	// String to Char
	S = "abc";
	C = S[0];

	// 5.
	// String to Single character String	
	// Method 1:
	std::string sResult2(S.begin(),S.begin()+1); // One Char String using begin(2)
	// Method 2:
	std::string sResult(S.substr(0, 1)); // Using substr
	// Method 3:
	std::string sResult(1, S[0]); // Using constructor - string ( size_t n, char c );
	// Method 4:	
    Sstm<<S[0];
    Sstm>>sResult;

	// 6.
	// String to Integer
	S = "256";
	// Method 1:
	iResult = atoi(S.c_str()); // C version
	// Method 2:
	iResult = std::stoi( S );  // C++ version
	// Method 3:
	std::istringstream iSs(S);
    iSs >> iResult;


	// Method 1:
	Sstm.clear(); // must in case of reusing the string stream
	Sstm.str(""); // must in case of reusing the string stream
	Sstm.str(S);
	Sstm >> iResult;
	// Method 5:
	std::stringstream(S) >> iResult;

	// 7. Integer to String
	Sstm.clear(); // must in case of reusing the string stream
	Sstm.str(""); // must in case of reusing the string stream
	Sstm << iInput;
	sResult = Sstm.str();


	//7.
	// String & Int to String
	S = "John";
    I = 21;
	//Method 1:
//Sstm << S << I;
//iResult = Sstm.str();  // John21
    // Method 2:
// 6. with sprintf
char numstr[21]; // enough to hold all numbers up to 64-bits
//sprintf(numstr, "%d", I);
//iResult = S + I; // John21

#if 0
#endif



	return 0;
}

//Notes:
//------
//const char *name = "sridhar";  // Valid
//const char ary[] = "sumitha";