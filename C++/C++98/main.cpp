#if 0

#include<iostream>
#include<string>
#include <sstream>
#include <vector>
using namespace std;

//Ref: http://www.gotw.ca/publications/mill19.htm

void function(char* pS,size_t len) {
return;
}

// Order of Preference:
// istringstream/ostringstream > stringstream > snprintf > sprintf
// Note: snprintf is not supported in C90, C++98 compilers (even in Visual studio 2010) but supported in C99 and likely in C++0x 

int main() {
cout<<"String Research:\n";
// Declaration
int iResult =0,I=0, iInput =786;
std::string sResult, S;
char cResult, C, *pC;
char cAry[64] = {0};
std::stringstream Sstm; // Common String stream can be used for both input and output
std::istringstream iSstm; // Like cin>>  only useful for input - preferred over common stringstream
std::ostringstream oSstm; // like cout<< only useful for output - preferred over common stringstream

// 1.
// Char to Integer ASCII
C = 'z';
iResult = C; // ASCII value of 'z'. iResult = . No need for typecast

// 2.
// Char to Integer
C = '5';
iResult = C - '0'; // Char to Int. iResult = 5. No need for typecast

//3.
// Integer to Char 
// Method 1: [Only for Single digit integer]
I = 5;
C = '0' + I; // C = '5' [not for 10 and above numbers]
// Method 2: [For all numeric length]
oSstm << 5;
// Method 3: [Not char, it is char array]
sprintf(cAry, "%d",234);


//5.
// Char to String
// Method 1:
C = 'S';
Sstm << C;
Sstm >> sResult;
// Method 2:
sResult = "";
sResult = 'a';


// 5.
// String to Single character String
// Method 1:
std::string sResult2(S.begin(),S.begin()+1); // One Char String using begin(2)
// Method 2:
std::string sResult(S.substr(0, 1)); // Using substr
// Method 3:
std::string sResult(1, S[0]); // Using constructor - string ( size_t n, char c );
// Method 4:
    Sstm<<S[0];  // Using stringstream 
    Sstm>>sResult;
// Method 5: - preferred over common stringstream
oSstm<<S[0]; // Using output stream
sResult = oSstm.str();  // >> Can't be used 

// 5.
// String to Char
S = "abc";
C = S[0];


// 3.
// String to Const Char*
// Method 1:
S = "sridhar";
const char* pcC = S.c_str(); // Useful for C - style parameter passing. Add extra '/0' Character = S.size() + 1
// Method 2:
oSstm << "sridhar";
const char* pcC = oSstm.str().c_str(); // Logical Error: String return by str() is temp string object so store in a another variable before processing
// Solution - I
S = oSstm.str(); // Copying the temp string return by str() into S
const char* pcC = S.c_str(); // Correct
// Solution - II [Efficient] -  Using const reference to get the temporary object for extending the temp obj lifetime
std::string& sRef = oSstm.str(); // Not Coyping but extending the lifetime of temp string till the life time of reference
const char* pcC = sRef.c_str(); // Correct
   
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
    pC = &Vs[0]; // use &pC[0] as a char* [pointer to start of vector]
// Method 4: (Unsafe, should be passed along the string size)
function(&S[0],S.size()); // Not NULL terminated & Non Const
// Method 5: (Unsafe, should be passed along the string size)
function(&S.front(),S.size()); // Not NULL terminated & Non Const





// 6.
// String to Integer
S = "256";
// Method 1:
iResult = atoi(S.c_str()); // C version
// Method 2:
iResult = std::stoi( S ); // C++ version
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
// Method 1:
Sstm.clear(); // must in case of reusing the string stream
Sstm.str(""); // must in case of reusing the string stream
Sstm << iInput;
sResult = Sstm.str();
// Method 2:
sprintf(cAry,"%d",iInput); // %d - Decimal form
sResult = cAry; // Character Array to String
// Method 3: [Non Standard Conversion]
pC = itoa(iInput,cAry,10 /*decimal base*/);
sResult = pC; // Pointer to Character to String

//7.
// String & Int to String
// Note: itoa - is not in standard lib
S = "John";
I = 21;
//Method 1:
Sstm << S << I;
sResult = Sstm.str(); // John21
// Method 2: - preferred over common stringstream
oSstm << S << I; // Using output stream
sResult = oSstm.str();

// Method 2:
// 6. with sprintf
sprintf(cAry, "%d", I);
sResult = S + cAry; // John21
// Method 3:
sprintf(cAry, "%s%d", S.c_str(), I);


// String Extraction and Concatenation


return 0;
}

//Notes:
//------
//const char *name = "sridhar"; // Valid
//const char ary[] = "sumitha";

#else

#include <iostream>

class dog {
	public:
	dog() { std::cout<<" I'm Tommy "; }
	dog(int age) 
	{
		dog();
		std::cout<<" My age is "<< age;
	}
};

int main()
{
	dog a = 5;
	/////////////////////////////////
	// Delegating Constructor - reuse the constructor code from another constructor
	/////////////////////////////////
	// C++ 03 -  
	

	// C++ 11 - 	

	return 0;
}



#endif

