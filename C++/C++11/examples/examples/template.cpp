#include<iostream>
#include <iomanip> // for std::setprecision()
using namespace std;
// Function Template:
int Max(int x, int y) { 
	return x > y ? x : y; }
float Max(float x, float y) { 
	return x < y ? x : y; }
// template <typename T> T Max(T x, T y) { return x > y ? x : y; }

int main() {

	
	// float - 6 precision/significant digits, double - 15 precision, long double - 15 / 18 / 33 precisions
	// NOTE: cout by default uses 6 precision for both float and double
	/*
	std::cout << 1.234567890 << '\n';  // 1.23457 (ONLY 6 significant digits - double)
	std::cout << 1.234567890f << '\n'; // 1.23457 (ONLY 6 significant digits - float)
	

	std::cout << 12.34567890f << '\n'; // 12.3457 - Last 7 is a round of 6

	std::cout << 12345.67890f << '\n'; // 12345.7
	std::cout << 123456.7890f << '\n'; // 123457	
		
	std::cout << 1234567.890f << '\n'; // 1.23457e+06
	std::cout << 12345678.90f << '\n'; // 1.23457e+07
	*/
	float f;
	/*
	f = 1.2345678901234567890f; // 1.23456788
	f = 12.345678901234567890f; // 12.3456793
	f = 123456.78901234567890f; // 123456.789
	f = 1234567.8901234567890f; // 1234567.88
	f = 12345678.901234567890f; // 12345679.0
	*/
	f = 123456789.01234567890f; // 123456792.
	f = 1234567890.1234567890f; // 1.23456794e+09
	f = 12345678901.234567890f; // 1.23456788e+10
	/*
	double d = 1.2345678901234567890;
	std::cout << std::setprecision(16); // show 16 digits of precision
	std::cout << 1234567.8901234567890f << '\n'; // 1234567.875
	std::cout << 1234567.8901234567890 << '\n'; // 1234567.890123457 - double
	*/

	/*
	auto num = Max(3.3f, 5.5f);
	cout << num;
	num = Max(3, 5);
	cout << num;
	// num = Max(3, 5.5f);
	num = 3.3f + 5.5f;
	cout << num;
	

	*/
	return 0;
}