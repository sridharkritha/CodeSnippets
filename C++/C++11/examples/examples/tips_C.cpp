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
// Bitwise operation
if((x & MASK) == 0) // '==' has Higher precedence than '&'

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
/////////////////////////////////////////////////////////////////////////////////////////////////////
// atoi: convert integer to string 's'
void itoa(int n, char s[]) {
	do { // generate digits in reverse order
		s[i] = n % 10 + '0'; // Last digit extracted
		n = n / 10; // Delete the last digit
	}while(n);
	s[i] = '\0';
	reverse(s); // reverse the digits	
}
