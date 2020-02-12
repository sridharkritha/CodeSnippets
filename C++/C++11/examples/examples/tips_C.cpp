///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator precedence:
// '!=' Higher precedence than '='
	while((c = getchar()) != EOF) 

// '==' Higher precedence than '||'
	// Shortcircuit - Expressions connected by '|| && ' are evaluated LEFT to RIGHT
	if(c == '\n' || c == ' ' || c == '\t') // LEFT to RIGHT

// Assignment expression evaluated RIGHT to LEFT
	a = b = c = 0; // RIGHT to LEFT
	a = (b = (c = 0)); 

// Assignment and relative operator
	while((n /= 10) > 0) { }

// Bitwise operation
	if((x & MASK) == 0) // '==' has Higher precedence than '&'

// sizeof array and relative operator
	for(int i = 0; i < sizeof v / sizeof v[0]; ++i) { }

// Mixed precedence
for(i = 0; i < lim-1 && (c = getchar())!= EOF && c!='\n'; ++i)
1. i < (lim -1)				// '-' has Higher precedence than <, !=, && (NOTE the order!!)
2. (c = getchar())			// '=' Low precedence so it need ()
3. (c = getchar())!= EOF	// '!=' has Highter precdence than '&&'
4. c!='\n'					// '!=' has Highter precdence than '&&'
5. shortcircuit && => i < lim -1 && (c = getchar())!= EOF && c!='\n' // Lowest precedence &&

// Note: 
//		'<=' Higher precedence than '!='
//		'!=' Higher precedence than '&&'
//		'&&' Higher precedence then '+='


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shortcuts:
 // 1. postfix trick
	if(c == '\n') {
		s[i] = c; // Don't forget to append the new line and do one more count
		++i;
	}

	if(c == '\n') s[i++] = c; // postfix trick

  // 2.  Assignment operator trick
  <expression1> <operator> = <expression2> 
  <expression1> = (<expression1>) <operator> (<expression2>)   NOTE: brackets
  a *= b + 1;
  a = a * (b + 1); // Correct
  a = a * b + 1; // Wrong

 


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Cautions:
  // 1. Order in which funtion arguments are evaluated is not specified
  printf("%d %d", ++n, power(2,n)); // WRONG

  ++n; // Correct
  printf("%d %d", n, power(2,n));

  // 2.
  a[i] = i++; // WRONG - a[i] might have some unexpected value - depends upon the compiler interpretation

  // 3.
  x  = f() + g(); // WRONG if value of f() and g() are interdependent. f() or g() execute fist !

  Function calls, nested assignment statements and increment and decrement operators cause "SIDE EFFECTS".
  SIDE EFFECTS - some variable is changed as a by-product of the evaluation of an expression.

  Moral - Writing code that depends on order of evaluation is a bad programming practice in any language.





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copy input to output
// Version 1:
#include <stdio.h>
int main() {
	int c; // NOT char c bcos it cann't hold 'EOF'
	c = getchar();
	while(c != EOF) {
		putchar(c);
		c = getchar();
	}
}

// Version 2:
#include <stdio.h>
int main() {
	int c;
	// '!=' Higher precedence than '='
	while((c = getchar()) != EOF) putchar(c);
}

////////////////////////////////////////////////////////////////////////////////////////

// Count characters in input
// Version 1:
#include <stdio.h>
int main() {
	long nc = 0; // 4 bytes
	while(getchar() != EOF) ++nc;
	printf("%ld", nc);
}

// Version 2:
#include <stdio.h>
int main() {
	double nc = 0; // 4 bytes - double instead of 'long' - have same effect here
	for(nc = 0; getchar() != EOF; ++nc);
	printf("%.0f", nc); // .0f suppresses printing of decimal point andd the fraction part 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// getline: Read a line into s, return its length.
int getline(char s[], int lim) {
	int c, i;
	for(i = 0; i < lim -1 && (c=getchar())!= EOF && c!='\n'; ++i)  s[i] = c;
	if(c == '\n') {
		s[i] = c; // Don't forget to append the new line and do one more count
		++i;
	}
	s[i] = '\0'; // Don't forget to append the end of string and NOT count any thing.
	return i;
}

// Usage:
#define MAXLINE 1000    // Maximum input line size
char line[MAXLINE];     // Line to be saved here
while((len = getline(line, MAXLINE)) > 0) { }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// strcat: concatenate 't' to end of 's'
void strcat(char s[], char t[]) {
	int i, j;
	i = j = 0;
	while(s[i] != '\0') i++; // find end of 's'
	while((s[i++] = t[j++]) != '\0');
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Binary Search
int binarySearch(int n, int x, int v[]) {
	int low, mid, high;
	low = 0;
	high = n - 1;
	while(low <= high) {  					// Note: <=
		mid = (low + high) / 2;
		if(x < v[mid]) high = mid - 1; 		// Note: -1
		else if(x > v[mid]) low = mid + 1;  // Note: +1
		else return mid; // match found and return the index
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void swap(int v[], int i, int j) {
	int temp;	
	temp = v[i], v[i] = v[j], v[j] = temp; // Left to Right
}

// Step 1: One element is chosen - partition element(p).
// Step 2: Remaining elements are partitioned into 2 subsets - those less than 'p' and greater than EQUAL to 'p'.
// Step 3: Repeat the same process for the subsets. STOP once subset has only ONE element - NO need to sort.
void qsort(int v[], int left, int right) {
	int i, last;
	if (left >= right) return; // do nothing if array contains less than 2 elements[1 element - NO need to sort]
	swap(v, left, (left + right) / 2); // move partition element(p) to v[0]
	last = left;
	for (i = left + 1; i <= right; ++i) {	// partition
		if (v[i] < v[left]) swap(v, ++last, i);
	}
	swap(v, left, last); // restore partition element.
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

int main() {
	int v[3] = { 4, 1, 5};
	qsort(v, 0, sizeof v / sizeof v[0] - 1); // qsort(v,0, 2) - NOTE: -1
	for(int i = 0; i < sizeof v / sizeof v[0]; ++i) // arraySize =  sizeof v / sizeof v[0]
	cout << v[i];
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Reverse the string 's' in place
void reverse(char s[]) {
	int c, i, j;
	for(i = 0, j = strlen(s) - 1; i < j; ++i, --j) // PatternNote: strlen(s) - 1 (or) array[n] - 1 
			c = s[i], s[i] = s[j], s[j] = c; // Left to Right
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// atoi: convert string 's' to integer
int atoi(char s[]) {
	int i, n = 0;
	for(i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = n * 10 + (s[i] - '0'); // Note: n = n*10 + ()
	return n;
}

// Fast Version:
int fast_atoi(const char* s) {
	int n = 0;
	while(*s) n = n * 10 + (*s++ - '0');
	return n;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// atoi: convert string 's' to double
double atoi(char s[]) {
	int i;
	double n = 0.0, power = 1.0;
	for(i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = n * 10.0 + (s[i] - '0'); // Note: n = n*10 + ()
	if(s[i] == '.') ++i;
	for(power = 1.0; s[i] >= '0' && s[i] <= '9'; ++i) {
		n = n * 10.0 + (s[i] - '0');
		power *= 10.0;
	}
	return n/power;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// atoi: convert integer to string 's'
void itoa(int n, char s[]) {
	do { // generate digits in reverse order
		s[i++] = n % 10 + '0'; // Last digit extracted
		// n = n / 10; // Delete the last digit
	}while((n /= 10) > 0);
	s[i] = '\0';
	reverse(s); // reverse the digits	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



