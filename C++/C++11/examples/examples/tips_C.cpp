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

// Bitwise operation (&)
	if((x & MASK) == 0) // '==' has Higher precedence than '&'

// Uninary operator( &, *) binds more tightly than Arithmetic operators
	y = *ip + 1; // (*ip) + 1; increments the VALUE by 1 pointed by an pointer ip.
	*ip += 1; // *ip = (*ip) + 1; VALUE increment by 1
	++*ip; // ++(*ip); Also same as *ip += 1; VALUE increment by 1
	
	*ip++; // *(ip++); NOTE: ADDRESS incremented NOT value. Both [*, ++] have SAME precedence and [RIGHT to LEFT] associative applies.
	(*ip)++; // VALUE increment by 1

	*++ip; // Increment ip to next object first and then get the value from the new location

// Standard Idioms for pushing and popping a stack.
	*p++ = val; // push val onto stack
	val = *--p; // pop top of stack into val

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

  // Pointer:
& operator ONLY applies to object in MEMORY: variables and array elements. It CANNOT be applied to
expressions, constants or register variables.

int *ip; // Expression *ip is an int [or] Pointer to int
double *dp, atoi(char *); // *dp Pointer to double, atoi returns double(NOT pointer) which has argument Pointer to char


  // Pointer and Array:
  // Similarities
  int a[10];
  int *pa;
  pa = &a[0];
  pa = a; // same as above
  int k = 2;
  cout << &a[k]; // address of location 2
  cout << a+k; // same as above
  cout << a[i];
  cout << *(a+i); // same as above

  // Difference : 1
  pa = a;
  pa++; // Legal - moving to next location 
  a++;  // ILLEGAL - You CANN'T increment the array name

  Automatic conversion of array Name into Pointer:
  If you pass the array to a function, what is passed is the LOACATION of the first element - that is a POINTER.
  Example:
  // strlen (ver. 1): return length of string s
  int strlen(char *s) {
	  for(int n = 0; *s != '\0'; s++) ++n; // s is a pointer NOT a array NAME. so you can increment
	  return n;
  }

  // Note: Below 2 forms both are same
  int strlen(char *s)  { }
  int strlen(char s[]) { }
 
 List of possible callers are
 strlen("Hello Muthu Raman"); // string CONSTANT
 strlen(array); // char array[100]; character ARRAY
 strlen(ptr); // char *ptr

 Pointer Arithmetic:
 If 'p' and 'q' points to elements of the 'same array' and 'p < q' then 'q - p + 1' (No. of elements from 'p' to 'q' both inclusive)
  // strlen (ver. 2): return length of string s (using pointer arithmetic)
    int strlen(char *s) {
	  char *p = s;
	  while(*p) p++; //  while(*p != '\0') p++; // while automatically take care of 'null' check
	  return p - s;
  }

  // Difference : 2
  A string CONSTANT, written as "I am a string" - is an array of character with '\0' termination. So length is ONE more than
  the number of characters between the double quotes.

  char ary[] = "I am a string"; // ary - Array HOLDS sequence of characters + '\0'
  char *ptr  = "I am a string"; // ptr - Pointer which POINTS to a string CONSTANT(READ ONLY sequence of characters + '\0').
								// ptr - Here the ASSIGNMENT is NOT a string copy; only pointers are involved.

  ary - Individual characters within the array may be changed. But 'ary' always refer to the same storage.
  ptr - ptr can me moved to point some other location. But the result is undefined if you modify the string content.

	strcpy(s,t): copy t to s.
	It would be nice just to have t = s but this copies the pointer, NOT the characters. To copy the characters, we need a loop.
  // strcpy (ver. 1- array subscript version): copy t to s
  void strcpy(char *s, char *t) {
	  int i = 0;
	 while(s[i] = t[i]) ++i; // while((s[i] = t[i]) != '\0') ++i;
  }

// strcpy (ver. 2- pointer version): copy t to s
  void strcpy(char *s, char *t) {
	 while((*s = *t) != '\0') {
		 s++;
		 t++;
	 }
  }

// strcpy (ver. 2- pointer version MORE simplified): copy t to s
  void strcpy(char *s, char *t) {
	 // Standard Idiom with '=' 
	 while(*s++ = *t++); // value of '*t++' is the character that 't' pointed to before 't' was incremented.
  }

  String lexicographic compare: 
  // strcmp: negative if s<t, 0 if s==t, positive if s>t
  int strcmp(char *s, chat *t) {
	  int i = 0;
	  for(i = 0; s[i] == t[i]; ++i) {
		  if(s[i] == '\0') return 0;
	  }
	  return s[i] - t[i];
  }

// strcmp (Ver 2 - pointer version): negative if s<t, 0 if s==t, positive if s>t
  int strcmp(char *s, chat *t) {
	  for( ; *s == *t; s++, t++) {
		  if(*s == '\0') return 0;
	  }
	  return *s - *t;
  }

  // POINTER TO AN ARRAY 
  int m[][3]  = {{0, 1, 2}, {3, 4, 5}};
  int (*m)[3] = {{0, 1, 2}, {3, 4, 5}};

Multi-dimensional array Vs Array of Pointer [preferred]:
2d array:
int m[2][3] = { {0, 1, 2},
				{3, 4, 5} };
// POINTER TO AN ARRAY of rows, where each row is an array of 3 ints
int m[][3] = {  {0, 1, 2},		// row is Optional
				{3, 4, 5} };	
int (*m)[3] = { {0, 1, 2},	 // () must bcos [] have higher precedence.
				{3, 4, 5} }; // without () => WRONG meaning => int *a[3] - ARRAY OF 13 POINTERS to integers

Array of Pointers: Commonly used for storing the 'character strings of diverse lengths'.
int m[2][3]; // multi-dimen array. 2x3 = 6 int fixed sized location has been reserved.
// m[row][col] = 3 x row + col; Can be used to locate the elements 
int *a[2];  // array of pointer. 2 pointers location has been reserved. 
			// Advantage - Row of array may be of DIFFERENT length. Some points to 3 element array or 100 element array or none at all.
			// Suppose each element of 'a' point to a 3 element array then [2x3 = 6 int sized location + 2 cells for the pointer has been allocated]

2d array form:
char month[][3] = { "Jan", "fe", "m", "a", "may"}; // 5x3 = 15 allocation
Array of Pointers form:
char *month[] =   { "Jan", "fe", "m", "a", "may"}; // 5 pointer cells allocation + 5x3 = 15 allocation
// month in 'char *month[]' is array name NOT a pointer so you cann't increment the name month

Pointer to Array of Pointers:
Command line argument 'char *argv[]' is a - Pointer(p) to an array of pointers(aps). 
Here 'argv' is NOT a array NAME it is a pointer you can increment it.

// echo.cc - echo the command line arguments. 
// echo hello world sridhar
// hello world sridhar
// Ver 1: Keep the Pointer(p) unchanged but manipulate the array index of (aps).
int main(int argc, char *argv[]) {
	for(int i = 1; i < argc; ++i) printf("%s%s", argv[i], (i < argc-1) ? " ": ""); // hello world sridhar
}

// Ver 2: Keep the the Array index of (aps) unchanged but manipulate the Pointer(p).
int main(int argc, char *argv[]) {
	for(int i = 1; i < argc; ++i) printf("%s%s", *++argv, (i < argc-1) ? " ": ""); // hello world sridhar
}

// Print the first characters of each strings
int main(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) cout << (*++argv)[0] << " "; // h w s
}

// Print the first 3 characters of each strings
int main(int argc, char *argv[]) {
	// Must - For moving the pointer from first character of one string to first character next string
	cout << (*++argv)[0]; // h
	for(int i = 0; i < 3; ++i) cout << *++argv[0] << " "; // e l l

	cout << (*++argv)[0]; // w
	for (int i = 0; i < 3; ++i) cout << *++argv[0] << " "; // o r l
}

argv -----> p0-----> echo
			p1-----> hello 
			p2-----> world
			p3-----> sridhar
cout << *++argv; // hello NOT echo bcos it increments first.

Summary:
*++argv      - On each call it moves to next STRING
(*++argv)[0] - On each call it moves to next STRING and extract the FIRST character.
**++argv     - Same as above.
*++argv[0]	 - On each call it moves from '2nd' CHARACTER to next CHARACTER within the SAME string. It is only valid after '(*++argv)[0]'.
*++(argv[0]) - Same as above. [] binds tighter than * and ++ so () is optional.
			 - In the above expression, the increments are happening for the 'pointer argv[0]'


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
	swap(v, left, (left + right) / 2); // middle element is chosen for partition. Move partition element(p) to v[0]. 
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
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Generic swap can be used for both numeric and string
void swap(void *v[], int i, int j) {
	void * temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

// strcmp (Ver 2 - pointer version): negative if s<t, 0 if s==t, positive if s>t
  int strcmp(char *s, chat *t) {
	  for( ; *s == *t; s++, t++) {
		  if(*s == '\0') return 0;
	  }
	  return *s - *t;
  }

  int numcmp(char *s, char *t) {
	  double a, b;
	  a = atof(s); b = atof(t);
	  if(a < b)			return -1;
	  else if ( a > b)	return 1;
	  else				return 0;
  }

void qsort(int *v[], int left, int right, int (*cmp)(void *, void *)) {
	int i, last;
	if (left >= right) return; // do nothing if array contains less than 2 elements[1 element - NO need to sort]
	swap(v, left, (left + right) / 2); // middle element is chosen for partition. Move partition element(p) to v[0]. 
	last = left;
	for (i = left + 1; i <= right; ++i) {	// partition
		if ((*cmp)(v[i], v[left]) < 0) // Numeric or String Comparision function
			swap(v, ++last, i);
	}
	swap(v, left, last); // restore partition element.
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

char *linePtr[]; // lines of string. String content may also full of numbers.
qsort((void **) linePtr, 0, nLines-1, (int (*)(void *, void *)) (isNumber ? numcmp : strcmp));

Note: int (*cmp)(void *, void *)
cmp  - is a Pointer to a funtion which takes 2 void * arguments
*cmp - is the function

Note: int *cmp(void *, void *)
cmp - is a function which return  a pointer to an int. (DIFFERENT meaning!)
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
Macro Substitution:

#define SQUARE(S)	S * S
x = SQUARE(z + 1);
x = z + 1 * z + 1; // WRONG - Use brackets

#define MAX(A, B)	( (A) > (B) ? (A) : (B) )
x = MAX( p+q, r+s);
x = ( (p+q) > (r+s) ? (p+q) : (r+s) ); // OK

BUT macro substitutions are NOT suitable for SIDE EFFECT expression such as increment operator, input or output.

x = MAX(i++, j++); // WRONG - will increment the LARGER number twice.

#define DPRINTF(expr)	printf("expr=%g\n", expr)
DPRINTF(x/y);
printf("expr=%g\n", x/y); // WRONG - Substitutions WOULDN'T work within quotes. Use #

#:
#define DPRINTF(expr)	printf(#expr      "=%g\n", expr)
DPRINTF(x/y);
printf("x/y"     "=%g\n", x/y); // step 1: Substitution
printf("x/y=%g\n", x/y);        // step 2: Strings will concatenated automatically

##:
#define PASTE(front, back)	front       ##             back
s = PASTE(name, 9); // white spaces are removed and then concatenated
s = name9;

Conditional Inclusion:
// header.h
#ifndef HDR
#define HDR
	// Contents of header.h go here
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Structure:
without structure tag:
struct { int x; int y;} a, b, c;
int a, b, c;

with structure tag:
struct point { int x; int y;};

int a, b, c;
struct point a, b, c;

structure initializer:
struct point a = {10, 20};

Structure inside an another structure:
struct rectangle {
	struct point pt1;
	struct point pt2;
};

struct rectange screen;
screen.pt1.x = 100;

Pointer to Structure:
struct point origin, *sp;
sp = &origin;
cout << origin.x;
cout << (*sp).x; // '.' higher precedence than '*'. Also *sp.x = *(sp.x) = illegal access/meaningless
cout << sp->x; // same as above but prefered way of writing.

struct rectangle screen, *sp = &screen;
cout << screen.pt1.x;
cout << (screen.pt1).x;
cout << sp->pt1.x; // Both '.' and '->' are top of precedence hierarchy. Associate from LEFT to RIGHT
cout << (sp->pt1).x;

More Examples:
struct { int len; char *str } *p;
++p->len; // increments len, NOT p
++(p->len); // same as above
(++p)->len; // increments 'p' before accessing 'len'
(p++)->len; // access 'len' and then increment 'p'
p++->len; // same as above

*p->str; // fetches wathever str points to
*p->str++; // increments 'str' and then access what it points to
(*p->str)++; // increments the content which is pointed by str.
*p++->str; // accessing whatever 'str' points to and then increment 'p'.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











