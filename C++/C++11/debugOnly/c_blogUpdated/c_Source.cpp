#include<iostream>
int main() {
	std::cout << "hello";
	return 0;
}


// Both || and == are [Left to Right] Associative
// But == has Higher precedence than ||
if (true || false == false)
	cout << "true || (false == false)"; // Output: true || (false == false)
else
	cout << "(true || false)== false";
	return 0;
}


3 > 2 && 2 > 1
// returns true

3 > 2 > 1
// returns false because 3 > 2 is true, then true is converted to 1 in inequality operators, 
// therefore true > 1 => 1 > 1 which is false
// Adding parentheses makes things clear: (3 > 2) > 1


Associativity
Associativity determines how operators of the same precedence are parsed. For example, consider
 an expression:

a OP b OP c
Left-associativity (left-to-right) means that it is processed as (a OP b) OP c, while 
right-associativity (right-to-left) means it is interpreted as a OP (b OP c). Assignment operators 
are right-associative, so you can write:

a = b = 5;
with the expected result that a and b get the value 5. This is because the assignment operator 
returns the value that is assigned. First, b is set to 5. Then the a is also set to 5, the 
return value of b = 5, aka right operand of the assignment.


x == 5 && x > y
!(x > y)


false || true && false

true || false && true

A || B && C			means	A || (B && C)
A && B || C && D	means	(A && B) || (C && D)
A && B && C || D	means	((A && B) && C) || D
!A && B || C		means	((!A) && B) || C


a > b && 45 <= sum || sum < a + b && d > 90
(  a > b && 45 <= sum   ) ||   (sum < a + b && d > 90  )

sum < a + b
means

sum < (a + b)

https://chortle.ccsu.edu/Java5/Notes/chap40B/ch40B_8.html
Only one of X>Y and X<=Y can be true for particular values of X and Y.
Another way to say this is !(X>Y) and X<=Y are equivalent. 



a & b || c				(a & b) || c
a = b || c				a = (b || c)
q && r || s--			(q && r) || s--


Illegal Expression				Default Grouping
p == 0 ? p += 1: p += 2			( p == 0 ? p += 1 : p ) += 2

In this expression, the equality operator (==) has the highest precedence, so p == 0 is 
grouped as an operand. The conditional-expression operator (? :) has the next-highest precedence.
 Its first operand is p == 0, and its second operand is p += 1. However, the last operand of the
  conditional-expression operator is considered to be p rather than p += 2, since this occurrence
   of p binds more closely to the conditional-expression operator than it does to the 
   compound-assignment operator. A syntax error occurs because += 2 does not have a left-hand 
   operand. You should use parentheses to prevent errors of this kind and produce more readable 
   code. For example, you could use parentheses as shown below to correct and clarify the
    preceding example:

( p == 0 ) ? ( p += 1 ) : ( p += 2 )