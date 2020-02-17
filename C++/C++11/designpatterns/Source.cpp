#include<iostream>
using namespace std;
int main() {

// Both || and == are [Left to Right] Associative
// But == has Higher precedence than ||
if (true || false == false)
cout << "true || (false == false)"; // Output: true || (false == false)
else
cout << "(true || false)== false";
	return 0;
}

