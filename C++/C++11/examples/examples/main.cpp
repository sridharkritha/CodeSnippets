#if 1


#else
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
// Ref:
// 
#include <iostream>
using namespace std;

int main()
{


	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Non-modifying Algorithms -  count, min and max, compare, linear search, attribute 

// STL Algorithms #1: Non-modifying Algorithms
// https://www.youtube.com/watch?v=eV7tVdNIw9o&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=8

vector<int> vec = {9,60,90,8,45,87,90,69,69,55,7};
vector<int> vec2 = {9,60,70,8,45,87};
vector<int>::iterator itr, itr2;
pair<vector<int>::iterator, vector<int>::iterator> pair_of_itr;

// 1. Counting
//     Algorithm   Data              Operation
int n = count(vec.begin()+2, vec.end()-1, 69);// 2 in the range (90 to 55 inclusive).Default comparison used is =
int m = count_if(vec.begin(), vec.end(), [](int x){return x==69;}); // 2 
int m = count_if(vec.begin(), vec.end(), [](int x){return x<10;}); // 3  - C++ 11 Lambda Function

// Lamda function in Normal function form
bool lessThan10(int x) {  return x<10; }

// 2.  Min and Max
itr = max_element(vec.begin()+2, vec.end());  // 90 - first max value. Default comparison used is <
// It returns the first max value in the least significant position
itr = max_element(vec.begin(), vec.end(), [](int x, int y){ return (x%10)<(y%10);}); // 9
// Most algorithms have a simple form and a generalized form

itr = min_element(vec.begin(), vec.end());  // 7 - first min value.
// Also has generalized form: min_element()

pair_of_itr = minmax_element(vec.begin(), vec.end(),  // {60, 69} 
		                      [](int x, int y){ return (x%10)<(y%10);}); 
// returns a pair, which contains FIRST of min and LAST of max (not FIRST of max)

// 3. Linear Searching (used when data is not sorted)
//    Returns the first match
itr = find(vec.begin(), vec.end(), 55);
itr = find_if(vec.begin(), vec.end(), [](int x){ return x>80; });
itr = find_if_not(vec.begin(), vec.end(), [](int x){ return x>80; });

itr = search_n(vec.begin(), vec.end(), 2, 69);  // Consecutive 2 items of 69
// Generalized form: search_n()

// Search subrange
vector<int> sub = {45, 87, 90};
itr = search( vec.begin(), vec.end(), sub.begin(), sub.end()); // search FIRST subrange
itr = find_end( vec.begin(), vec.end(), sub.begin(), sub.end()); // search LAST subrange
// Generalized form: search(), find_end()

// Search any_of
vector<int> items  = {87, 69};
itr = find_first_of(vec.begin(), vec.end(), items.begin(), items.end()); 
      // Search any one of the item in items
itr = find_first_of(vec.begin(), vec.end(), items.begin(), items.end(),
		              [](int x, int y) { return x == y*4;}); 
      // Search any one of the item in items that satisfy: x==y*4;

// Search Adjacent
itr = adjacent_find(vec.begin(), vec.end());  // find two adjacent items that are same
itr = adjacent_find(vec.begin(), vec.end(), [](int x, int y){ return x==y*4;}); 
	     // find two adjacent items that satisfy: x==y*4;


// 4. Comparing Ranges
if (equal(vec.begin(), vec.end(), vec2.begin())) {
  cout << "vec and vec2 are same.\n";
}

if (is_permutation(vec.begin(), vec.end(), vec2.begin())) {
	cout << "vec and vec2 have same items, but in differenct order.\n";	
}

pair_of_itr = mismatch(vec.begin(), vec.end(), vec2.begin());
// find first difference
// pair_of_itr.first is an iterator of vec 
// pair_of_itr.second is an iterator of vec2

//Lexicographical Comparison: one-by-one comparison with "less than"
lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end());
// {1,2,3,5} < {1,2,4,5}
// {1,2}     < {1,2,3}

// Generalized forms: 
//   equal(), is_permutation(), mismatch(), lexicographical_compare()


// 5. Check Attributes
is_sorted(vec.begin(), vec.end());  // Check if vec is sorted

itr = is_sorted_until(vec.begin(), vec.end()); 
// itr points to first place to where elements are no longer sorted
// Generalized forms: is_sorted(), is_sorted_until()

is_partitioned(vec.begin(), vec.end(), [](int x){return x>80;} );
			// Check if vec is partitioned according to the condition of (x>80)

is_heap(vec.begin(), vec.end());  // Check if vec is a heap
itr = is_heap_until(vec.begin(), vec.end());  // find the first place where it is no longer a heap
// Generalized forms: is_heap(), is_heap_until()

// All, any, none
all_of(vec.begin(), vec.end(), [](int x) {return x>80} );  
// If all of vec is bigger than 80 

any_of(vec.begin(), vec.end(), [](int x) {return x>80} );  
// If any of vec is bigger than 80 

none_of(vec.begin(), vec.end(), [](int x) {return x>80} );  
// If none of vec is bigger than 80 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Modifying Algorithms(Changes the element values) - copy, move, transform, swap, fill, replace, remove
 
// Ref: STL Algorithm #2: Modifying Algorithms
// https://www.youtube.com/watch?v=kYYm-Quj97o&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=9
vector<int> vec = {9,60,70,8,45,87,90};     // 7 items
vector<int> vec2 = {0,0,0,0,0,0,0,0,0,0,0}; // 11 items
vector<int>::iterator itr, itr2;
pair<vector<int>::iterator, vector<int>::iterator> pair_of_itr;


// 1. Copy
copy(vec.begin(), vec.end(), // Source
	  vec2.begin());          // Destination

copy_if(vec.begin(), vec.end(),      // Source
		  vec2.begin(),                // Destination
		  [](int x){ return x>80;});   // Condition 
// vec2: {87, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0}

copy_n(vec.begin(),  4, vec2.begin());  
// vec2: {9, 60, 70, 8, 0, 0, 0, 0, 0, 0, 0}

copy_backward(vec.begin(),  vec.end(),  // Source
		        vec2.end());              // Destination end() NOT begin()
// vec2: {0, 0, 0, 0, 9, 60, 70, 8, 45, 87, 90}


// 2. Move 
vector<string> vec = {"apple", "orange", "pear", "grape"}; // 4 items
vector<string> vec2 = {"", "", "", "", "", ""};            // 6 items

move(vec.begin(), vec.end(), vec2.begin());
// vec:  {"", "", "", ""}  // Undefined
// vec2: {"apple", "orange", "pear", "grape", "", ""};
//
// If move semantics are defined for the element type(string in this case), elements are MOVED over, 
// otherwise they are COPIED over with copy constructor, just like copy().

move_backward(vec.begin(), vec.end(), vec2.end());
// vec2: {"", "", "apple", "orange", "pear", "grape"};


vector<int> vec = {9,60,70,8,45,87,90};     // 7 items
vector<int> vec2 = {9,60,70,8,45,87,90};     // 7 items
vector<int> vec3 = {0,0,0,0,0,0,0,0,0,0,0}; // 11 items

// 3. Transform
transform(vec.begin(), vec.end(),    // Source
		    vec3.begin(),              // Destination
			 [](int x){ return x-1;});  // Operation 

transform(vec.begin(), vec.end(),           // Source #1
          vec2.begin(),                     // Source #2 (second input)
		    vec3.begin(),                     // Destination
  	       [](int x, int y){ return x+y;});  // Operation
         // Add items from vec and vec2 and save in vec3 
         // vec3[0] = vec[0] + vec2[0]
         // vec3[1] = vec[1] + vec2[1]
         // ...

// 4. Swap - two way copying
swap_ranges(vec.begin(), vec.end(), vec2.begin());

// 5. Fill
vector<int> vec = {0, 0, 0, 0, 0};

fill(vec.begin(), vec.end(), 9); // vec: {9, 9, 9, 9, 9}

fill_n(vec.begin(), 3, 9);       // vec: {9, 9, 9, 0, 0}

generate(vec.begin(), vec.end(), rand); // filled by the content generated by function rand.

generate_n(vec.begin(), 3, rand);

// 6. Replace
replace(vec.begin(), vec.end(),  // Data Range
		  6,                       // Old value condition
		  9);                      // new value                    

replace_if(vec.begin(), vec.end(),     // Data Range
			  [](int x){return x>80;},    // Old value condition
			  9);                         // new value                    

replace_copy(vec.begin(), vec.end(),  // Source
			  vec2.begin(),              // Destination
			  6,                         // Old value condition
			  9);                        // new value                    
  // Generalized form: replace_copy_if()


// 7. Remove
remove(vec.begin(), vec.end(), 3);   // Remove all 3's
remove_if(vec.begin(), vec.end(), [](int x){return x>80;});  
	 // Remove items bigger than 80

remove_copy(vec.begin(), vec.end(),  // Source
		      vec2.begin(),            // Destination (SAVE it)
				6);                      // Condition 
   // Remove all 6's, and copy the remain items to vec2
   // Generalized form: remove_copy_if()

unique(vec.begin(), vec.end());   // Remove consecutive equal elements

unique(vec.begin(), vec.end(), less<int>());   
        // Remove elements whose previous element is less than itself

unique_copy(vec.begin(), vec.end(), vec2.begin());   
// Remove consecutive equal elements, and then copy the uniquified items to vec2
// Generalized form: unique_copy()


Order-Changing Algorithms: reverse, rotate, permute, shuffle 
They changes the order of elements in container, but not necessarily the elements themselves.


vector<int> vec =  {9,60,70,8,45,87,90};     // 7 items
vector<int> vec2 = {0,0,0,0,0,0,0};     // 7 items

// 1. Reverse
reverse(vec.begin()+1, vec.end()-1);
// vec: {9,87,45,8,70,60,90};     // 7 items

reverse_copy(vec.begin()+1, vec.end()-1, vec2.begin());
// vec2: {87,45,8,70,60,0,0};



// 2. Rotate
rotate(vec.begin(), vec.begin()+3, vec.end());
// vec: {8,45,87,90,9,60,70};     // 7 items

rotate_copy(vec.begin(), vec.begin()+3, vec.end(),  // Source
		 vec2.begin());                               // Destination
       // Copy vec to vec2 in rotated order
       // vec is unchanged


// 3. Permute
next_permutation(vec.begin(), vec.end()); //Lexicographically next greater permutation
prev_permutation(vec.begin(), vec.end()); //Lexicographically next smaller permutation

// {1,2,3,5} < {1,2,4,4}
// {1,2}     < {1,2,3}

// Sorted in ascending order:  {8, 9, 45, 60, 70, 87, 90} - Lexicographically smallest
// Sorted in descending order: {90, 87, 70, 60, 45, 9, 8} - Lexicographically greatest

// Generalized form: next_permutation(), prev_permutation()

// 4. Shuffle  
//    - Rearrange the elements randomly 
//      (swap each element with a randomly selected element)
random_shuffle(vec.begin(), vec.end());
random_shuffle(vec.begin(), vec.end(), rand);

// C++ 11
shuffle(vec.begin(), vec.end(), default_random_engine()); // Better random number generation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Sortings in STL
 */

// Sorting algorithm requires random access iterators:
//    vector, deque, container array, native array

// Ref:STL Algorithms #3: Sorting
// https://www.youtube.com/watch?v=TZv5qHU2AMQ&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=10

vector<int> vec = {9,1,10,2,45,3,90,4,9,5,8};

sort(vec.begin(), vec.end());  // sort with operator <
// vec:  1 2 3 4 5 8 9 9 10 45 90

bool lsb_less(int x, int y) {
      return (x%10)<(y%10);
}	
sort(vec.begin(), vec.end(), lsb_less);  // sort with lsb_less()
// vec: 10 90 1 2 3 4 45 5 8 9 9


// Sometime we don't need complete sorting.
// Problem #1: Finding top 5 students according to their test scores.
//  -  partial sort
vector<int> vec = {9,60,70,8,45,87,90,69,69,55,7};

partial_sort(vec.begin(), vec.begin()+5, vec.end(), greater<int>()); // greater<int> is functor
// vec: 90 87 70 69 69 8 9 45 60 55 7

// Overloaded:
partial_sort(vec.begin(), vec.begin()+5, vec.end()); // Bottom 5 students
// vec: 7 8 9 45 55 90 60 87 70 69 69


// Problem #2: Finding top 5 students according to their score, but I don't care about who is best among 5(Not sorted).
vector<int> vec = {9,60,70,8,45,87,90,69,69,55,7};

nth_element(vec.begin(), vec.begin()+5, vec.end(), greater<int>());
// vec: 69 87 70 90 69 60 55 45 9 8 7


// Problem #3: Move the students whose score is less than 10 to the front
vector<int> vec = {9,60,70,8,45,87,90,69,69,55,7};

bool lessThan10(int i) { return (i<10); }
partition(vec.begin(),  vec.end(), lessThan10);
// vec: 8 7 9 90 69 60 55 45 70 87 69 -> converts to 2 groups of unsorted elements

// To preserve the original order within each partition:
stable_partition(vec.begin(),  vec.end(), lessThan10);
// vec: 9 8 7 60 70 45 87 90 69 69 55



// Heap Algorithms
//
// Heap Properties:
// 1. First element is always the largest just like a priority Queue.
// 2. Add/remove takes O(log(n)) time
vector<int> vec = {9,1,10,2,45,3,90,4,9,5,8};

make_heap(vec.begin(), vec.end());
// vec: 90 45 10 9 8 3 9 4 2 5 1


Problem: Remove the largest element:
pop_heap(vec.begin(), vec.end());  // 1. Swap vec[0] with last item vec[size-1]. 90 to 1
                                   // 2. Heapify [vec.begin(), vec.end()-1)
// vec:  45 9 10 4 8 3 9 1 2 5 90
vec.pop_back();  // Remove the last item (the largest one). 90
// vec:  45 9 10 4 8 3 9 1 2 5

// Add a new element:
vec.push_back(100);
push_heap(vec.begin(), vec.end());  // Heapify the last item in vec
// vec:  100 45 10 4 9 3 9 1 2 5 8




// Heap Sorting:
vector<int> vec = {9,1,10,2,45,3,90,4,9,5,8};
make_heap(vec.begin(), vec.end());

sort_heap(vec.begin(), vec.end());
// vec: 1 2 3 4 5 8 9 9 10 45 100
// Note: sort_heap can only work on a heap.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Sorted Data Algorithms
   - Algorithms that require data being pre-sorted
   - Binary search, merge, set operations
Note: Every sorted data algorithm has a generalized form with a same name.
 */

// Ref: STL Algorithms #4: Sorted Data Algorithms and Numeric Algorithms
// https://www.youtube.com/watch?v=s6_meQVkwgc&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=11

vector<int> vec = {8,9,9,9,45,87,90};     // 7 items


// Search ELEMENTS
bool found = binary_search(vec.begin(), vec.end(), 9);  // check if 9 is in vec

vector<int> s = {9, 45, 66};
bool found = includes(vec.begin(), vec.end(),       // Range #1
		                s.begin(), s.end());        // Range #2 - Search multiple elements
// Return true if all elements of s is included in vec
// Both vec and s must be sorted

// Search POSITION/ITERATOR
itr = lower_bound(vec.begin(), vec.end(), 9);  // returns iterator pointing to vec[1] which is 9.  
// Find the first position(lower index) where 9 could be inserted and still keep the sorting.

itr = upper_bound(vec.begin(), vec.end(), 9);  // vec[4] 
// Find the last position(upper index) where 9 could be inserted and still keep the sorting.

pair_of_itr = equal_range(vec.begin(), vec.end(), 9); 
// Returns both first and last position where 9 could be inserted and still keep the sorting.

// 2. Merge
vector<int> vec = {8,9,9,10}; 
vector<int> vec2 = {7,9,10}; 
merge(vec.begin(), vec.end(),      // Input Range #1
		vec2.begin(), vec2.end(),    // input Range #2
		vec_out.begin());               // Output 
      // Both vec and vec2 should be sorted 
      // Nothing is dropped, all duplicates are kept. (In set_union, duplicates dropped)
// vec_out: {7,8,9,9,9,10,10}

vector<int> vec = {1,2,3,4,1,2,3,4,5}  // Merging two parts of same sorted series
inplace_merge(vec.begin(), vec.begin()+4, vec.end());  
// vec: {1,1,2,2,3,3,4,4,5}  - One step of merge sort


// 3. Set operations
//    - Both vec and vec3 should be sorted 
//    - The resulted data is also sorted
vector<int> vec = {8,9,9,10}; 
vector<int> vec2 = {7,9,10}; 
vector<int> vec_out[5];

set_union(vec.begin(), vec.end(),      // Input Range #1
		    vec2.begin(), vec2.end(),    // input Range #2
		    vec_out.begin());               // Output 
// if X is in both vec and vec2, only one X is kept in vec_out (In merge, duplicates CANN'T dropped)
// vec_out: {7,8,9,9,10}

set_intersection(vec.begin(), vec.end(),      // Input Range #1
		           vec2.begin(), vec2.end(),    // input Range #2
		           vec_out.begin());               // Output 
// Only the items that are in both vec and vec2 are saved in vec_out
// vec_out: {9,10,0,0,0}


vector<int> vec = {8,9,9,10}; 
vector<int> vec2 = {7,9,10}; 
vector<int> vec_out[5]; 
set_difference(vec.begin(), vec.end(),      // Input Range #1
		         vec2.begin(), vec2.end(),    // input Range #2
		         vec_out.begin());               // Output 
// Only the items that are in vec but not in vec2 are saved in vec_out
// vec_out: {8,9,0,0,0}

set_symmetric_difference(vec.begin(), vec.end(),      // Input Range #1
		         vec2.begin(), vec2.end(),       // input Range #2
		         vec_out.begin());               // Output 
// vec_out has items from either vec or vec2, but not from both
// vec_out: {7,8,9,0,0}






/*
 *  Numeric Algorithms (in <numeric> NOT in <algorithm>)
 *   - Accumulate, inner product, partial sum, adjacent difference
 */

// 1. Accumulate
int x = accumulate(vec.begin(), vec.end(), 10); 
// 10 + vec[0] + vec[1] + vec[2] + ...

int x = accumulate(vec.begin(), vec.end(), 10, multiplies<int>()); // Generalized form
// 10 * vec[0] * vec[1] * vec[2] * ...


// 2. Inner Product
//vector<int> vec = {9,60,70,8,45,87,90};     // 7 items
int x = inner_product(vec.begin(), vec.begin()+3,  // Range #1
		               vec.end()-3,                 // Range #2
				         10);                         // Init Value
// 10 + vec[0]*vec[4] + vec[2]*vec[5] + vec[3]*vec[6]
		
int x = inner_product(vec.begin(), vec.begin()+3,  // Range #1 [9,60,70]
		                vec.end()-3,                 // Range #2 [45,87,90]
				          10,                          // Init Value
				          multiplies<int>(),
				          plus<int>());
// 10 * (vec[0]+vec[4]) * (vec[2]+vec[5]) * (vec[3]+vec[6])



// 3. Partial Sum
partial_sum(vec.begin(), vec.end(), vec2.begin());
// vec2[0] = vec[0]
// vec2[1] = vec[0] + vec[1];
// vec2[2] = vec[0] + vec[1] + vec[2]; 
// vec2[3] = vec[0] + vec[1] + vec[2] + vec[3]; 
// ...

partial_sum(vec.begin(), vec.end(), vec2.begin(), multiplies<int>());
// vec2[0] = vec[0]
// vec2[1] = vec[0] * vec[1];
// vec2[2] = vec[0] * vec[1] * vec[2]; 
// vec2[3] = vec[0] * vec[1] * vec[2] * vec[3]; 
// ...


// 4. Adjacent Difference
adjacent_difference(vec.begin(), vec.end(), vec2.begin());
// vec2[0] = vec[0]
// vec2[1] = vec[1] - vec[0];
// vec2[2] = vec[2] - vec[1]; 
// vec2[3] = vec[3] - vec[2]; 
// ...

adjacent_difference(vec.begin(), vec.end(), vec2.begin(), plus<int>());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ref: Learn STL: Introduction of Templates
// https://www.youtube.com/watch?v=Vc1RyqWFbiA&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=1

// Function Template
template<typename T>
T square(T x) {
	return x*x;
}

int main() {
	cout << square(5) << endl; // int - detect the data type by it's parameter
	cout << square(5.1) << endl; // double (NOT float)- detect the data type by it's parameter
	// Specifying the data type is OPTIONAL in Functional template
	cout << square<int>(5) << endl; // square function of data type int
	cout << square<float>(5.1) << endl; // square function of data type float
}


// Class Template
template<typename T>
class BoVector {
	T arr[1000];
	int size;
public:
	BoVector() :size(0) {}
	void push(T x) { arr[size] = x; size++; }
	T get(int i) const { return arr[i]; }
	int getSize() const { return size; }
	void print() const {for(int i=0; i<size; i++) {cout << arr[i] << endl;}}
};

template<typename T>
BoVector<T> operator*(const BoVector<T>& rhs1, BoVector<T>& rhs2) {
	BoVector<T> ret;
	for (int i = 0; i<rhs1.getSize(); i++) {
		ret.push(rhs1.get(i)*rhs2.get(i));
	}
	return ret;
}

int main()
{
	// Specifying the data type is MUST in Class template
	BoVector<int> bv;
	bv.push(2);
	bv.push(5);
	bv.push(8);
	bv.push(9);
	bv.print();

	cout << "Print squared bv: " << endl;
	bv = square(bv);
	bv.print();
}

Disadvantage of template:
 1. Code bloat - creates varies copies of function with different datatype as per the function usage in compile time.
    It will increase the size of the program image.


// STL: Standard Template Library -- Data Structures and Algorithms

// Ref: Introduction of STL #1: Overview
// https://www.youtube.com/watch?v=ltBdTiRgSaw&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=2

// First Example:
using namespace std;

vector<int> vec;
vec.push_back(4); vec.push_back(1); vec.push_back(8);  // vec: {4, 1, 8}

// half-open: [begin, end) - begin points to first element, end - points to an element after the end element.
vector<int>::iterator itr1 = vec.begin();  
vector<int>::iterator itr2 = vec.end();
// Iterator behave just like a POINTER but it is a CLASS
for (vector<int>::iterator itr = itr1; itr!=itr2; ++itr)
   cout << *itr << " ";  // Print out:  4 1 8

sort(itr1, itr2);  // vec: {1, 4, 8}


/*
 	 Reasons to use C++ standard library:
 	 1. Code reuse, no need to re-invent the wheel.
 	 2. Efficiency (fast and use less resources). Modern C++ compiler are usually tuned to optimize for C++ standard library code.
 	 3. Accurate, less buggy.
 	 4. Terse, readable code; reduced control flow.
 	 5. Standardization, guarenteed availability
 	 6. A role model of writing library.
 	 7. Good knowledge of data structures and algorithms.
 */

// Ref: Introduction of STL #2: Sequence Containers
// https://www.youtube.com/watch?v=gxZJ5JNuWMY&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=3
Containers:

1. Sequence Containers (Array and Linked List):
	- vector, deque, list, forward list, array
2. Associative Containers (Binary Tree -  Always SORTED):
	- set, multiset
	- map, multimap
3. Unordered Containers(Hash table):
	- Unordered set / multiset
	- Unordered map / multimap

// Ref: Introduction of STL #2: Sequence Containers
// https://www.youtube.com/watch?v=gxZJ5JNuWMY&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=3
// STL Headers
// Sequence Containers (Array and Linked List)
#include <vector>
#include <deque>
#include <list>
// Associative Containers (Binary Tree -  Always SORTED)
#include <set>   // set and multiset
#include <map>   // map and multimap
// Unordered Containers (Hash table)
#include <unordered_set>  // unordered set/multiset
#include <unordered_map>  // unordered map/multimap
#include <iterator>
#include <algorithm> // includues most of the alogorithms
#include <numeric>    // some numeric algorithms
#include <functional> // functor


// Sequence Container  -  Vector
vector<int> vec;   // vec.size() == 0
vec.push_back(4); vec.push_back(1); vec.push_back(8);  // vec: {4, 1, 8};    vec.size() == 3

// Random Access - Vector specific operations:
cout << vec[2];     // 8  (no range check)
cout << vec.at(2);  // 8  (throw range_error exception of out of range)

for (int i; i < vec.size(); i++)  cout << vec[i] << " ";

for (vector<int>::iterator itr = vec.begin(); itr!= vec.end(); ++itr)
   cout << *itr << " ";  

for (it: vec)    // C++ 11
   cout << it << " ";

// Vector is a dynamically allocated contiguous array in memory
int* p = &vec[0];   p[2] = 6;


// Common member functions of ALL containers.
// vec: {4, 1, 8}
if (vec.empty()) { cout << " Vector is Empty.\n"; }
cout << vec.size();   // 3
vector<int> vec2(vec);  // Copy constructor, vec2: {4, 1, 8}
vec.clear();    // Remove all items in vec;   vec.size() == 0
vec2.swap(vec);   // vec2 becomes EMPTY, and vec has 3 items.

/* 
 	 Properties of Vector:
 	 1. FAST insert/remove at the END: O(1)
 	 2. SLOW insert/remove at the BEGINING or in the MIDDLE: O(n)
 	 3. SLOW search: O(n)
 */

// Deque
deque<int> deq = { 4, 6, 7 };
deq.push_front(2);  // deq: {2, 4, 6, 7}
deq.push_back(3);   // deq: {2, 4, 6, 7, 3}

// Deque has similar interface like vector
cout << deq[1];  // 4


/* 
	 Properties:
	 1. FAST insert/remove at the BEGINING and the END;
	 2. SLOW insert/remove in the middle: O(n)
	 3. SLOW search: O(n)
 */


// list  -- double linked list
list<int> mylist = {5, 2, 9 }; 
mylist.push_back(6);  // mylist: { 5, 2, 9, 6}
mylist.push_front(4); // mylist: { 4, 5, 2, 9, 6}

list<int>::iterator itr = find(mylist.begin(), mylist.end(), 2); // itr -> 2
mylist.insert(itr, 8);   // mylist: {4, 5, 8, 2, 9, 6}  
                         // O(1), faster than vector/deque
itr++;                   // itr -> 9
mylist.erase(itr);       // mylist: {4, 8, 5, 2, 6}   O(1)


/* 
	Properties:
	1. fast insert/remove at any place: O(1)
	2. slow search: O(n)
	3. no random access, no [] operator.
 */


// Array Container: Thin wrapper on top of the native array. Bcos of this you can use the STL function(begin, end, swap) on arrays.
int a[3] = {3, 4, 5};
array<int, 3> a = {3, 4, 5}; // Size CANNOT be changed at later stage
array<int, 4> b = {3, 4, 5}; // a & b are considered as different TYPES bcos of its different size value
a.begin();
a.end();
a.size();
a.swap();


// Ref: Introduction of STL #3: Associative Containers
// https://www.youtube.com/watch?v=6iyzPed7FrM&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=4
 Associative Container : Always sorted, default criteria is < *
         No push_back(), push_front()











 // set - No duplicates
  set<int> myset;
  myset.insert(3);    // myset: {3}
  myset.insert(1);    // myset: {1, 3}
  myset.insert(7);    // myset: {1, 3, 7},  O(log(n))

  set<int>::iterator it;
  it = myset.find(7);  // O(log(n)), it points to 7
                  // Sequence containers don't even have find() member function
  pair<set<int>::iterator, bool> ret;
  ret = myset.insert(3);  // no new element inserted bcos it is duplicate
  if (ret.second==false) 
     it=ret.first;       // "it" now points to element 3
  // Eventhough "it" is at element 3 it wouldn't insert '9' before '3' - You cann't decide it!
  myset.insert(it, 9);  // myset:  {1, 3, 7, 9}. Here "it" is a hint for doing things faster possibily  O(log(n)) => O(1)
                         // it still points to 3
  myset.erase(it);         // myset:  {1, 7, 9}

  myset.erase(7);   // myset:  {1, 9}
  // Note: NONE of the sequence containers provide this kind of erase.



// multiset is a set that allows duplicated items(INSERTION ALWAYS PASS)
multiset<int> myset;

// set/multiset: value of the elements CANNOT be modified [READ ONLY] to maintain th sorted order
*it = 10;  // Error - *it is read-only


/* 
	 Properties:
	 1. Fast search: O(log(n))
	 2. Traversing is slow (compared to vector & deque)
	 3. No random access, no [] operator.
 */


/*
  map - No duplicated key
  In set/multiset - value is sorted. map/multimap - key is sorted
 */
map<char,int> mymap;
mymap.insert ( pair<char,int>('a',100) );
mymap.insert ( make_pair('z',200) ); // TYPES infered from the parameters

map<char,int>::iterator it = mymap.begin();
mymap.insert(it, pair<char,int>('b',300));  // "it" is a hint for doing things faster

it = mymap.find('z');  // O(log(n))

// showing contents:
for ( it=mymap.begin() ; it != mymap.end(); it++ )
  cout << (*it).first << " => " << (*it).second << endl;

// multimap is a map that allows duplicated keys
multimap<char,int> mymap;

// map/multimap: 
//  -- keys cannot be modified
//     type of *it:   pair<const char, int>
     (*it).first = 'd';  // Error - READ ONLY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ref: Introduction of STL #4: Unordered Containers
// https://www.youtube.com/watch?v=NNLvY9O7ufU&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=5

/*
   Unordered Container (C++ 11)
    - Unordered set and multiset
    - Unordered map and multimap
    Order not defined, and may change overtime
 
   Default hash function defined for fundamental types and string.
 
   No subscript operator[] or at()
   No push_back(), push_front()
 */

// unordered set
  unordered_set<string> myset = { "red","green","blue" };
  unordered_set<string>::const_iterator itr = myset.find ("green"); // O(1)
  if (itr != myset.end())   // Not found - returns iterator end()
     cout << *itr << endl;
  myset.insert("yellow");  // O(1)

  vector<string> vec = {"purple", "pink"};
  myset.insert(vec.begin(), vec.end());

// Hash table specific APIs:
  cout << "load_factor = " << myset.load_factor() << endl;// total no.element / total no.buckets
  string x = "red";
  cout << x << " is in bucket #" << myset.bucket(x) << endl; // which bucket has the element ?
  cout << "Total bucket #" << myset.bucket_count() << endl;

// unordered multiset: unordered set that allows duplicated elements
// unordered map: unordered set of pairs
// unordered multimap: unordered map that allows duplicated keys
// hash collision (many items in the same bucket) => performance degrade in search





/* Properties of Unordered Containers:
 * 1. Fastest search/insert at any place: O(1)
 *     Associative Container takes O(log(n))
 *     vector, deque takes O(n)
 *     list takes O(1) to insert, O(n) to search
 * 2. Unorderd set/multiset: element value cannot be changed.
 *    Unorderd map/multimap: element key cannot be changed.
 */



// Associative Array -  map and unordered map
unordered_map<char, string> day = {{'S',"Sunday"}, {'M',"Monday"}};

cout << day['S'] << endl;    // No range check
cout << day.at('S') << endl; // Has range check

vector<int> vec = {1, 2, 3};
vec[5] = 9;   // Compile Error - There is NO location 5

// BUT works for Associative Array
day['W'] = "Wednesday";  // Inserting {'W', "Wednesday}
day.insert(make_pair('F', "Friday"));  // Inserting {'F', "Friday"}

// insert - cann't change the existing one
day.insert(make_pair('M', "MONDAY"));  // Fail to modify, it's an unordered_map
// subscript gives WRITE access so you CAN change the existing one
day['M'] = "MONDAY";                   // Succeed to modify



void foo(const unordered_map<char, string>& m) {
   // Problem:
   m['S'] = "SUNDAY";       // Error bcos const input param
   cout << m['S'] << endl; // Error - eventhough we are not modifying compiler DONN'T allow any subscript 
   // Solution:
   auto itr = m.find('S');
   if (itr != m.end()) cout << *itr << endl; // OK
}
foo(day);

//Notes about Associative Array: 
//1. Search time: unordered_map - O(1) NOT always; map - O(log(n)) always;
//2. Unordered_map may degrade to O(n);
//3. Can't use multimap and unordered_multimap, they don't have [] operator.


/*
 * Container Adaptor
 *  - Provide a restricted interface to meet special needs
 *  - Implemented with fundamental container classes
 *
 *  1. stack:  LIFO, push(), pop(), top()
 *
 *  2. queue:  FIFO, push(), pop(), front(), back() 
 *
 *  3. priority queue: first item always has the greatest priority
 *                   push(), pop(), top()
 */

/*
 * Another way of categorizing containers:
 *
 * 1. Array based containers: vector, deque
 *
 * 2. Node base containers: list + associative containers + unordered containers
 * 
 * Node base containers DONN'T invalidtes pointer (after insert and other operations)
 *
 * Array based containers invalidates pointers (after insert and other operations):
 *    - Native pointers, iterators, references
 */

 vector<int> vec = {1,2,3,4};
 int* p = &vec[2];   // p points to 3
 vec.insert(vec.begin(), 0);
 cout << *p << endl;   // 2, or random value - Don't use pointer





// Ref: Introduction of STL #5: Iterators and Algorithms
// https://www.youtube.com/watch?v=vO2AlrBf5rQ&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=6

/*
 * Iterators - 5 Types
 */
// 1. Random Access Iterator:  vector, deque, array
vector<int> itr;
itr = itr + 5;  // Addition: advance itr by 5
itr = itr - 4;  // Subtraction
if (itr2 > itr1) // Comparision
++itr;   // faster than itr++. Bcos pre-increment NO need to return any values
--itr;

// 2. Bidirectional Iterator: list, set/multiset, map/multimap
list<int> itr;
++itr; // Can do increment But you CANN'T do addition, subtraction and comparision like vector
--itr;

// 3. Forward Iterator: forward_list
forward_list<int> itr;
++itr; // Can do ONLY increment and CANN'T be decremented

// Unordered containers provide "at least" forward iterators.

// 4. Input Iterator: read and process values while iterating forward.
int x = *itr; // READ ONLY. CANN'T WRITE

// 5. Output Iterator: output values while iterating forward.
*itr = 100; // WRITE ONLY. CANN'T READ





// Every container has a iterator and a const_iterator
set<int>::iterator itr;
set<int>::const_iterator citr;  // Read_only access to container elements

set<int> myset = {2,4,5,1,9};
for (citr = myset.begin(); citr != myset.end(); ++citr) {
   cout << *citr << endl;
   //*citr = 3; // Error
}

// In C++ 11 - All containers supports additional buildin const iterator - cbegin & cend
for_each(myset.cbegin(), myset.cend(), MyFunction);  // Only in C++ 11



// Iterator Functions:
advance(itr, 5);       // Move itr forward 5 spots.Applicable all containers. Equivalent to itr += 5 if it is a random access iterator;
distance(itr1, itr2);  // Measure the distance between itr1 and itr2. Useful for non-random access iterator.




/* Iterator Adaptor (Predefined Iterator)
 *  - A special, more powerful iterator
 * 1. Insert iterator
 * 2. Stream iterator
 * 3. Reverse iterator
 * 4. Move iterator (C++ 11)
 */




// 1. Insert Iterator:
vector<int> vec1 = {4,5};
vector<int> vec2 = {12, 14, 16, 18};
vector<int>::iterator it = find(vec2.begin(), vec2.end(), 16);
insert_iterator< vector<int> > i_itr(vec2,it);
copy(vec1.begin(),vec1.end(),  // source
     i_itr);                   // destination
     //vec2: {12, 14, 4, 5, 16, 18}
// Other insert iterators: back_insert_iterator, front_insert_iterator


// 2. Stream Iterator:
vector<string> vec4;
copy(istream_iterator<string>(cin),      // standard input stream
            istream_iterator<string>(),  // end of the stream
            back_inserter(vec4)); // all stream copied to vec4

copy(vec4.begin(), vec4.end(), ostream_iterator<string>(cout, " ")); // all content is printed out through cout

// Make it terse - combine into One statement
copy(istream_iterator<string>(cin), istream_iterator<string>(), 
            ostream_iterator<string>(cout, " "));


// 3. Reverse Iterator:
vector<int> vec = {4,5,6,7};
reverse_iterator<vector<int>::iterator> ritr;
for (ritr = vec.rbegin(); ritr != vec.rend(); ritr++)
   cout << *ritr << endl;   // prints: 7 6 5 4



// Algorithms  - mostly loops
vector<int> vec = { 4, 2, 5, 1, 3, 9};

vector<int>::iterator itr = min_element(vec.begin(), vec.end()); // itr -> 1

// Note 1: Algorithm always process ranges in a half-open way: [begin, end) - begin included; end - NOT included
sort(vec.begin(), itr);  // vec: { 2, 4, 5, 1, 3, 9} - itr points to 1 but it is not included in half - open

reverse(itr, vec.end());  // vec: { 2, 4, 5, 9, 3, 1}   itr => 1 and end() => one element past 9. Range [1,3,9]
							// finally it => 9 NOT to 1


// Note 2:
vector<int> vec2(3);
copy(itr, vec.end(),  // Source
     vec2.begin());   // Destination
     //vec2 needs to have at least space for 3 elements otherwise the result is undefined (NOT SAFE).

// Note 3: Safety option is back_inserter but not efficient - insert one item at a time
vector<int> vec3; // EMPTY vector 
copy(itr, vec.end(), back_inserter(vec3));  // Inserting instead of overwriting 
                  // back_insert_iterator      Not efficient

// Safe and Efficient Solution:
vec3.insert(vec3.end(), itr, vec.end());  // Efficient and safe



// Note 4: Algorithm with function
bool isOdd(int i) {
   return i%2;
}

int main() {
   vector<int> vec = {2, 4, 5, 9, 2}
   vector<int>::iterator itr = find_if(vec.begin(), vec.end(), isOdd);  // itr -> 5
}

// Note 5: Algorithm with native C++ array
int arr[4] = {6,3,7,4};
sort(arr, arr+4); // Pointer is considered as iterator
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: How to Define new Handler
// https://www.youtube.com/watch?v=lfqiH422WUc&list=PLE28375D4AC946CC3&index=29

/* 
 	 new-handler must to do one of following things:
 	 1). Make more memory available.
 	 2). Install a different new-handler. If last handler couldn't find/allocate memory
 	 3). Uninstall the new-handler (passing a null pointer).
 	 4). Throw an exception bad_alloc or its descendent.
 	 5). Terminate the program.
 */
// Example 1:
int main() {
   int *pGiant = new int[10000000000L];
   delete[] pGiant;
}

// OUTPUT:
terminate called after throwing an instance of 'std::bad_alloc'




// Example 2: Global new-handler
void NoMoreMem() {
   std::cerr << "Unable to allocate memory, Bo." << endl;
   abort();
}
int main() {
   std::set_new_handler(NoMoreMem);
   int *pGiant = new int[10000000000L];
   delete[] pGiant;
}

// Output:
Unable to allocate memory, Bo.


// Example 3:  Class specific new-handler
class dog {
   int hair[10000000000L];
   std::new_handler origHandler;
   public:
   static void NoMemForDog() {
      std::cerr << "No more memory for doggy, Bo." << endl;
	  // Duplicate restore the origHander incase '::operator new' throws exception
      std::set_new_handler(origHandler);
      throw std::bad_alloc;
   }
   void* operator new(std::size_t size) throw(std::bad_alloc) {
      origHandler = std::set_new_handler(NoMemForDog); // get the old hander and set new handler
      void* pV = ::operator new(size);   // Call global operator new
      std::set_new_handler(origHandler); // Restore old handler
      return pV;
   }
};


int main() {
   std::shared_ptr<dog> pd(new dog()); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Demystifying Operator new/delete
// https://www.youtube.com/watch?v=IO0EmgOagMY&list=PLE28375D4AC946CC3&index=28

// Demystifying Operator new/delete

// What happens when following code is executed? 
 

   dog* pd = new dog();
/* 
  Step 1. operator new is called to allocate memory for dog.
  Step 2. dog's constructor is called to create dog.
  Step 3. if step 2 throws an exception, call operator delete to free the memory allocated in step 1.
  Note: if step 1 throws and exception, delete wouldn't be called bcos C++ assumes that step 1 always succeed.
 */
   delete pd;
/* 
  Step 1. dog's destructor is called.
  Step 2. operator delete is called to free the memory.
 */

//   Global 'Operator new':
//   This is how the 'operator new' may look like if you re-implement it. 
//   Note: new handler is a function invoked when operator new failed to allocate memory.
//         set_new_handler() installs a new handler and returns current new handler.
void* operator new(std::size_t size) throw(std::bad_alloc) {
   while (true) {
      void* pMem = malloc(size);   // Allocate memory
      if (pMem) 
         return pMem;              // Return the memory if successful

	  // memory allocation is NOT successful
      std::new_handler Handler = std::set_new_handler(0);  // Get new handler
      std::set_new_handler(Handler);

      if (Handler)
         (*Handler)();      // Invoke new handler and finally call the operator new again for memory allocation
      else
         throw bad_alloc(); // If new handler is null, throw exception
   }
}

// Member 'Operator new':
class dog {
   public:
   static void* operator new(std::size_t size) throw(std::bad_alloc) // User defined 'operator new'
   {
         customNewForDog(size); // PROBLEM:Dog memory size is allocated for Yellowdog
   }
};

class yellowdog : public dog { };

int main() {
   yellowdog* py= new yellowdog(); // calls user defined 'operator new' NOT a global 'operator new'
}


// Solution 1: 
class dog {
   public:
   static void* operator new(std::size_t size) throw(std::bad_alloc) // User defined 'operator new'
   {
      if (size == sizeof(dog))
         customNewForDog(size);
      else
         ::operator new(size); // call global 'operator new' for Yellowdog
   }
};

// Solution 2: Overload 'operator new' for yellowdog too
class yellowdog : public dog {
   static void* operator new(std::size_t size) throw(std::bad_alloc) 
};


// operator delete
class dog {
   // virtual static void operator delete(void* pMemory) throw() // virtual & static will NOT go together
   static void operator delete(void* pMemory) throw() // You cann't make polymorphic by adding virtual keyword
   {
      cout << "Bo is deleting a dog, \n";
      customDeleteForDog();
      free(pMemory);
   }
  // ~dog() {};
  virtural ~dog() { }; // Even it is a do nothing destructor it MUST be a virtual otherwise 
  // 1. Class will not be polymorphic 2. ONLY dog memory will get deleted (Yellowdog stay for ever in the memory). 
};

class yellowdog : public dog {
   static void operator delete(void* pMemory) throw() {
      cout << "Bo is deleting a yellowdog, \n";
      customDeleteForYellowDog();
      free(pMemory);
   }
};

int main() {
   dog* pd = new yellowdog();
   delete pd;
}


/*
 	 Why do we want to customize new/delete
	
 	 1. Usage error detection: 
 	    - Memory leak detection/garbage collection. 
 	    - Array index overrun/underrun.
 	 2. Improve efficiency:
 	    a. Clustering related objects to reduce page fault.
 	    b. Fixed size allocation (good for application with many small objects).
 	    c. Align similar size objects to same places to reduce fragmentation.
 	 3. Perform additional tasks:
 	    a. Fill the deallocated memory with 0's - security.
 	    b. Collect usage statistics.
 */

/*
 	 Writing a GOOD memory manager is HARD!	
 	 Before writing your own version of new/delete, consider:
	
 	 1. Tweak your compiler toward your needs;
 	 2. Search for memory management library, E.g. Pool library from Boost.
 */



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: https://www.youtube.com/watch?v=ZBK7aZ8v6vE&list=PLE28375D4AC946CC3&index=27
// Advanced C++: Koenig Lookup and Namespace Design

/*
 * Why Koenig Lookup?
 */

// Example 1:
namespace A
{
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
   void g( ) { cout << " calling A::g() \n"; }
}

int main() {
   A::X x1;
   g(x1);   // Koenig Lookup, or Argument Dependent Lookup (ADL)
   g();     // Error
}

Two reason for using Koenig Lookup :
// 1. The Practical Reason for using Koenig Lookup
	std::operator<<(std:cout, "Hi. \n");
	// Other way of writing above by using Koenig Lookup
	std::cout << "Hi.\n"; // definition of << (std::operator<<) is found inside std namespace by Koenig Lookup
	// If there is NO Koenig Lookup then 
	std::cout std::<< "Hi.\n"; // Error

// 2. Theoretical Reason: What is the interface of a class?
namespace A
{
   class C {
      public:
	  // Inferfaces of C
      void f() = 0;
      void g() = 0;
   };
   void h(C); // ALSO Inferface of C
   ostream& operator<<( ostream&, const C& ); // ALSO Inferface of C
}
void j(C); // NOT a Inferface of C bcos outsidie the namespace A

/*
 Definition of class: 
 	A class describes a set of data, along with the functions(NOT only member function) that operate on that data.
 */

/* 
 Class Interface includes: 
	1. Functions that operate on class C and in a same namespace with C are part of C's interface.
	2. Functions that are part of C's interface should be in the same namespace as C.

 */
// C class interfaces
   A::C c; 
   c.f();
   h(c);

namespace A { 
   class C {}; 
   int operator+(int n, A::C) { return n+1; } // User defined operator +
}

int main()
{
   A::C arr[3]; 
   std::accumulate(arr, arr+3, 0);  // return 3
}

// accumulate - Defined in C++ standard library <numeric>
namespace std {
   template <class InputIterator, class T>
      T accumulate ( InputIterator first, InputIterator last, T init )
   {
     while ( first!=last )
       init = init + *first++;  // calls user defined operator + using Koenig lookup instead of operator + from std namespace.
     return init;
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Namespace and Keyword "using"
// https://www.youtube.com/watch?v=YliqZh6s9ig&list=PLE28375D4AC946CC3&index=25

// 1. using namespace - directive [ONLY namespace]: to bring all namespace members into current scope
   using namespace std;


 
// 2. using - declaration [namespace / Class]:
//		a. Bring one specific namespace member to current scope. 
//		b. Bring a member from base class(NOT namespace) to current class's scope. 

   using std::cout;
   using B::f; 



using namespace std;  // case 1:   global scope
using std::cout;      // case 2.a: global scope

class B {
   public:
   void f(int a);
};
 
class D : private B { 
   public:
      void g() { 
         using namespace std;  // case 1: local scope
         cout << "From D: \n";
      }
      void h() { 
         using std::cout;     // case 2.a: local scope
         cout << "From D: \n";
      }
	  // f() is privately derived so it cann't be accessed outside. BUT 'using B::f;' brings to current scope and made it possible !
      using B::f;   // case 2.b:  class scope

	  // using std::cout;     // illegal - it cann't be in class scope
	  // using namespace std; // illegal - it cann't be in class scope
};

D d;
d.f(8); // works even it is privately derived function

/* 
	Notes:
	1. using declaration and using directive, when used on namespace, can be used in global or local scope.
	2. using declaration, when used on class members. It should be used in class scope.
 */


// Name Hiding in CLASS:
class B {
   public:
      void f(int a);
};
 
class D : public B { 
   public:
    // using B::f; // AVOIDS name hiding problem
    void f();      // Name Hidding: f() hides the base f(int a)
};

int main() {
   D d;
   d.f(8); // ERROR bcos of name hiding
}

#include<iostream>
// Anonymous Namespace - Namespace doesn't have any name.
void g() { std::cout << "global g()\n"; }

namespace {
	// Within a FILE you can access it like a global functions but it CANN'T be accessed from another FILE just 
	// like a STATIC function [ex: static void h() { std::cout << "h()\n"; } ]
	void g() { std::cout << "g()\n"; }
	void h() { std::cout << "h()\n"; g(); } // call the locall g() defined inside the namespace
}

int main() {
   h(); // calls h() inside the anonymous namespace
   g();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ref: Advance C++: Koenig Lookup - Argument Dependent Lookup (ADL)
// https://www.youtube.com/watch?v=TxgPZXe8XTo&list=PLE28375D4AC946CC3&index=26

// Increases the function name search scope



// Example 1:
// Koenig Lookup or Argument Dependent Lookup (ADL)
namespace A
{
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
}

// void g( X ) { cout << " calling A::g() \n"; } // Ambiguous

int main() {
   A::X x1;
   A::g(x1); // OK
   g(x1);    // NO error - it works !! bcos of Koenig Lookup, or Argument Dependent Lookup (ADL)
   // Compiler searches function name 'g' in 
   // 1. current scope, 
   // 2. scope where it param type has defined - by Koenig lookup and 
   // 3. global scope.
}


// Example 2:
class C {
   public:
   struct Y {};
   static void h(Y) { cout << "calling C::h() \n"; }
};

int main() {
   C::Y y;
   C:: h(y); // OK
   h(y);     // Error bcos Koenig Lookup NOT works for class. It works only for namespace.
}


// Example 3:
namespace A {
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
   void h( X ) { cout << " calling A::h() \n"; }
}

namespace C {
   void g(A::X ) { cout << "calling C::g() \n" ; }
   void j() {
      A::X x;
	  h(x); // OK by Koenig Lookup
      g(x); // ERROR - Ambiguous bcos it sees 2 versions - g( X ) by local and g(A::X ) by Koenig Lookup 
   }
};

int main() {
   C::j();
}

// Example 4:
namespace A {
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
   void h( X ) { cout << " calling A::h() \n"; }
}

class C {    // Changed from namespace to class
public:
   void g(A::X ) { cout << "calling C::g() \n" ; }
   void j() {
      A::X x;
	  h(x); // OK by Koenig Lookup
      g(x); // OK - no ambiguity. In class, once g is found in the local scope it STOPS further search.
   }
};

int main() {
	C c;
    c.j();
}


// Example 5:
namespace A
{
   struct X {};
   void g( X ) { cout << " calling A::g() \n"; }
}

class B {
   void g(A::X ) { cout << "calling B::g() \n" ; }
};

class C : public B {
   public:
   void j() {
      A::X x;
      g(x); // OK - no ambiguity. calling B::g()
   }
};

int main() {
   C c;
   c.j();
}

// Name hiding for NAMESPACE
namespace A
{
   void g(int) { std::cout << " calling A::g() \n"; }

   namespace C {
	  // Name hiding: g() hides g(int)
      void g() { std::cout << "calling C:g() \n" ; }
      void j() {
         //using A::g; // solves the name hiding problem
         g(9); // Error - Ambiguous
      }
   }
}

int main() {
   A::C::j();
}


namespace A
{
   struct X {};
   void g(X) { std::cout << " calling A::g() \n"; }

   namespace C {
	  // Name hiding: g() hides g(X)
      void g( ) { std::cout << "calling C:g() \n" ; }
      void j() {
         X x;
         g(x); // NO Error by name hiding. Bcos it uses by Koenig Lookup and prints - calling A::g()
      }
   }
}

int main() {
   A::C::j();
}


/*
	  Name Lookup Resolution Sequence

	  With namespaces:
	  current namespace scope(higher priority) > next enclosed scope(lower priority) > ... > global scope(lowest priority)

	  To override the resolution sequence:
	  1. Qualifier or using declaration
	  2. Koenig lookup

	  With classes:
	  current class scope(higher priority) > parent scope(lower priority) > ... > global scope(lowest priority)

	  To override the resolution sequence:
	   - Qualifier or using declaration (CANNT use Koenig lookup)	

	  Name hiding: name in the higher priority scope overrides the same name in the next lower priority scope
 */





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Code Reuse - Inheritance vs Composition
// https://www.youtube.com/watch?v=tXFqS31ZOFM&list=PLE28375D4AC946CC3&index=24

// Code Reuse with Inheritance
class Dog {   // BaseDog - Don't use Base in the class name it breaks the implementation details
	// common activities
};

class BullDog : public Dog {
	// Call the common activities to perform more tasks.
};

class ShepherdDog : public Dog {
	// Call the common activities to perform more tasks.
};


// Code Reuse with Composition
class ActivityManager {
	void eatBiscuit() { ... } // common activities
};

class Dog {
	virtual void eatBiscuit() = 0; // Inherit only from pure abstract class
};

class BullDog : public Dog {
	ActivityManager* pActMngr;
	// Call the common activities through pActMngr
	void eatBiscuit() { pActMngr->eatBiscuit(); }
};

class ShepherdDog : public Dog {
	ActivityManager* pActMngr;
	// Call the common activities through pActMngr
	void eatBiscuit() { pActMngr->eatBiscuit(); }
};


/*
	Code reuse: Composition is better than Inheritance
	1. Less code coupling between reused code and reuser of the code 
	   a. Child class automatically inherits ALL parent class's public members.
	   b. Child class can access parent's protected members.
	      - Inheritance breaks encapsulation

	2. Dynamic binding
	   a. Inheritance is bound at compile time
	   b. Composition can be bound either at compile time or at run time.
 */

/*
Inheritance Guidline:
	Never use inheritance for code reuse!
	Inherit interfaces only; never inherit implementation!
	All base classes should be Pure Abstract Classes!
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Duality of Public Inheritance
//   - Inheritance of Interface
//   - Inheritance of Implementation

// Ref: Advanced C++: Duality Of Public Inheritance - Interface & Implementation
// https://www.youtube.com/watch?v=iFK-D13LX2U&list=PLE28375D4AC946CC3&index=23

class Dog {
public:
	// Pure Virtual Function - support ONLY Inheritance of Interface
	virtual void bark() = 0;
	// Non Virtual Function - supports BOTH Inheritance of Interface and Implementation
	void run() { cout << "I am running."; } // Don't override it. Otherwise it breaks IS-A relationship
	// Impure Virtual Function - supports Inheritance of Interface and DEFAULT Implementation
	virtual void eat() { cout << "I am eating. "; } // Can be overriden if needed.
protected:
	// protected function support ONLY Inheritance of Implementation
	void sleep() { cout << " I am sleeping. "; }
};

class Yellowdog : public Dog {
public:
	virtual void barks() { cout << "I am a yellow dog.\n";}
	void iSleep() { sleep(); }
};


/*
 	Types of Inheritance in C++:
 	1. Pure virtual public function   - inherit interface only.
 	2. Non-virtual public function    - inherit both interface and implementation.
 	3. Impure virtual public function - inherit interface and default implementation
 	4. Protected function             - inherit implementation only
 	As a software designer, it is very important to separate the concepts of interface and implementation.
 */


/*
 When to use - Interface Inheritance ?
 1. Subtyping - One type can be safely used instead of other type
 2. Polymorphism
 
 */
	virtual void bark() = 0;

/*
 * Pitfalls:
 *  -- Be careful of interface bloat.
 *  -- Interfaces do not reveal implementation.
 */


/*
 Disadvantages of Implementation Inheritance 
    - Increase code complexity
    - Not encouraged to use it
 */
public:
	// Supports both Interface and Implementation - NOT bad.
	void run() { cout << "I am running."; }
	virtual void eat() { cout << "I am eating. "; }
protected:
	// ONLY Implementation inheritance - NOT encouraged
	void sleep() { cout << " I am sleeping. "; }

/*
 Guidelines for Implementation Inheritance:
 	1. Do not use inheritance for code reuse, use composition.
 	2. Minimize the implementation in base classes. Base classes should be thin.
 	3. Minimize the level of hierarchies in implementation inheritance.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Multiple Inheritance - Devil or Angel
// https://www.youtube.com/watch?v=7APovvvftQs&list=PLE28375D4AC946CC3&index=22

// Multiple Inheritance -- A class is directly derived from more than one base classes.
class InputFile {
   private:
   		void open();
   public:
   		void read();
};

class OutputFile {
   public:
   		void open();
   		void write();
};

class IOFile : public InputFile, public OutputFile {
	// 2 different open() instances and 2 different write() instances
};

int main() {
   IOFile f;
   f.open(); // ambiguous error even though private open() is not accessible in main()
   f.OutputFile::open(); // OK
}

Move the common parts to a separate common base class.

class File {            //         File
   public:              //         /  \        -
   string name;         // InputFile  OutputFile
   void open();         //         \  /
};                      //        IOFile

class InputFile  : public File { };
class OutputFile : public File { };

// Diamond shape of hierarchy
class IOFile : public InputFile, public OutputFile {
	// STILL 2 different open() instances and 2 different name instances even though it uses common base class File
};

int main() {
   IOFile f;
   f.open(); // ambiguous error - open() from which path of the Diamond shape hierarchy
   f.InputFile::name = "File1"; 
   f.OutputFile::name = "File2"; // Why we need 2 instance of 'name' ???
}


class File {            //         File
   public:              //         /  \ 
   string name;         // InputFile  OutputFile
   void open();         //         \  /
};                      //        IOFile

class InputFile  : virtual public File { }; // Virtual Inheritance
class OutputFile : virtual public File { };

class IOFile : public InputFile, public OutputFile {
	// Only one instance of open() and name bcos of virtual inheritance
};  // Diamond shape of hierarchy

int main() {
   IOFile f;
   f.open();         // OK
   f.name = "File1"; // OK
}

// Problem by Initialization

// Virtual base class
class File {     
   public:      
   File(string fname);
};             

//  1st. File(fname) {} initialization is needed but IGNORED by the compiler 
class InputFile : virtual public File {
   InputFile(string fname) : File(fname) {}
};

//  2nd. File(fname) {} initialization is needed but ALSO IGNORED by the compiler 
class OutputFile : virtual public File {
   OutputFile(string fname) : File(fname) {}
};

// 3rd. File(fname) {} initialization USED by the compiler 
// C++ Rule: Initialization of base virtual class is the responsibility of LAST derived class
class IOFile : public InputFile, public OutputFile {
   IOFile(string fname) : OutputFile(fname), InputFile(fname), File(fname) {}
};  

int main() {
   IOFile f;
}

Better Solution would be using Pure Abstract Class it solves the problem of multiple object instances, multiple object initialization,
multiple member functions/Data and even we do NOT need virtual inheritance. 
Note: File, InputFile and OutputFile needs to change to PAC.


/*
   Abstract Class: A class has one or more pure virtural functions.
 
   Pure Abstract Classes: 
   A class containing only pure virtual functions
     - no data 
     - no concrete functions
     - no private protected functions
 */

	class OutputFile {
	public:
	void write() = 0;
	void open() = 0;
	};

// Interface Segregation Principle (ISP): Split large interfaces into smaller and more specific ones so that clients
// only need to know about the methods that are of interest to them.

class Engineer { // Pure Abstract Classes
   public:
   ...; // 40 APIs
};

class Son { // Pure Abstract Classes
   public:
   ...; // 50 APIs
};

class Andy : public Engineer, Son  // NO need for virtual inheritance
{
   public:
   ...; // 500 APIs
};

/*
 * Benefits of ISP:
 * 1. Easy-to-use interfaces
 * 2. Static type safety
 */

/*
	* Summary:
	* 1. Multiple Inheritance is an important technique, e.g. ISP
	* 2. Derive only from PACs when using Multiple Inheritance.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert Dynamic Polymorphism to Static Polymorphism
/*
	Disadvantages of Dynamic Polymorphism:
	1. Extra Memory needed to create V-table.
	2. Extra run time cost due to dynamic binding.
*/

// Ref: Advanced C++: Static Polymorphism
// https://www.youtube.com/watch?v=-WV9vWjhI3g&list=PLE28375D4AC946CC3&index=21
#include <iostream>
using namespace std;

// Dynamic Polymorphism
struct Person { 
	string name;
	int age;
};

class Profession {
   public:
   void taxBand(Person* node) {
      if (node) {
         salaryBenefits(node);
      }
   }
   private:
   virtual void salaryBenefits(Person* node) { } // Dynamic Polymorphism
};

class Doctor : public Profession {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Doctor.\n";
   }
};

class Police : public Profession {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Police.\n";
   }
};
   
int main() {
   Person* p = new Person { "Rajesh", 25 };
   Doctor doc;
   doc.taxBand(p);

   Police pol;
   pol.taxBand(p);
}
// 
/*
 3 things to be maintained in DYNAMIC to STATIC polymorphism conversion:
	* I).   is-a relationship(public inheritance) between base class and derived class
	* II).  Base class defines a "generic" algorithm(salaryBenefits) that's used by derived class
	* III). The "generic" algorithm is customized by the derived class
 */

// Static Polymorphism / Simulated Polymorphism  - Conversion technique used is - CURIOUSLY RECURRING TEMPLATE PATTERN
//		Disadvantage: Eventhough there is no usage of extra heap memory for Vtable and no run time cost of late binding.
//		Different template classes (Doctor/Police) own its separate memory space in the program image [Size of exe will bit bigger]

// TMP - Template Metaprogramming - Moving computation in runtime to compile time
// Non-virtual Interface Idiom (NVI)
template <typename T> class Profession {
   public:
   void taxBand(Person* node) {
      if (node) {
         salaryBenefits(node);
      }
   }
   private: // NO more virtual function
    void salaryBenefits(Person* node) { 
		static_cast<T*>(this)->salaryBenefits(node);  // Static Polymorphism
	}
};

class Doctor : public Profession<Doctor> {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Doctor.\n";
   }
};

class Police : public Profession<Doctor> {
   private:
   void salaryBenefits(Person* node) {
       cout << "Customized salaryBenefits() for Police.\n";
   }
};

// Other Static Polymorphism by Template
template<typename T>
T Max(std::vector<T> v) {
	T max = v[0];
	for(typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
		if(*it > max) {
			max = *it;
		}
	}
	return max;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Maintain is-a Relation for Public Inheritance
// https://www.youtube.com/watch?v=97iK5r3zNug&list=PLE28375D4AC946CC3&index=19
#include <iostream>
using namespace std;
// Never Override Non-virtual Functions
class Dog {
   // Add virtual key word if you want polymorphism
   public: void bark() { cout << "I am just a dog.\n";};
};

class Yellowdog : public Dog{
   public: void bark() { cout << "I am a yellow dog.\n";};
};

int main() {
   Yellowdog* py = new Yellowdog();
   py->bark();  
   Dog* pd = py;
   pd->bark(); 
}
/*
	// NOT a Polymorphism
	I am a yellow dog.
	I am just a dog.
	// Polymorphism: DIFFERENT class objects act on SAME api will behave DIFFERENTLY.
	I am a yellow dog.
	I am a yellow dog.
*/


// Never redefine default parameter for the virtual function
class Dog {
   public: 
   virtual void bark(string msg = "just a") { cout << "I am " << msg << " dog.\n";};
   virtual void run(int speed) { cout << "I am run at speed of " << speed << endl;};
};

class Yellowdog : public Dog{
 // Virtual functions are bound dynamically.
 // Default parameters are bound STATICALLY.
  public: 
  void bark(string msg = "a yellow") { cout << "I am " << msg << " dog.\n";};
  // Shadowing: After seeing the run(string), compiler STOP searching for another run() eventhough they have different args. 
  void run(string txt = "I cann't run") { cout << txt << endl;};
  using Dog::run;
};

int main() {
   Yellowdog* py = new Yellowdog();
   Dog* pd = py;
   py->bark(); // I am a yellow dog.
   pd->bark(); // I am just a dog. WRONG polymorphism. calls Yellowdog bark() BUT gets the default value from Dog NOT from Yellodog

   py->run(45); // ERROR. It don't call Dog's run(), it call yellowdog run() BUT arg mismatch
   py->run(45); // OK. If you declare 'using Dog::run;' I am run at speed of 45
   py->run();   // I cann't run
}

/* 
 * Summary of pitfalls:
 * 1. Precise definition of classes;
 * 2. Don't override non-virtual functions;
 * 3. Don't override default parameter values for virtual functions;
 * 4. Force inheritance of shadowed functions.
 * 5. Be careful of typo in function overriding.
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: https://www.youtube.com/watch?v=EYuPBkgJtCQ&list=PLE28375D4AC946CC3&index=18
// Advanced C++: Inheritance - Public, Protected, and Private
#include <iostream>
using namespace std;

	// Public, Protected, Private Inheritance 
	class B { };
	class D_pub  : public    B { };
	class D_prot : protected B { };
	class D_priv : private   B { };

/*
	They specifies different access control from the derived class to the base class.
	Access Control:
	1. NONE of the derived classes can access anything that is PRIVATE in B.
	2. D_pub  inherits public members of B as PUBLIC and the protected members of B as PROTECTED
	3. D_prot inherits the public and protected members of B as PROTECTED.
	4. D_priv inherits the public and protected members of B as PRIVATE.

	Casting:
	1. ANYONE can cast a D_pub* to B*. D_pub IS A special kind of B. [only IS-A / Derived IS A kind of Base]
	2. D_prot's MEMBERS, FRIENDS, and CHILDREN can cast a D_prot* to B*.
	3. D_priv's MEMBERS and FRIENDS can cast a D_priv* to B*. [HAS-A / ]

*/

// Detailed Example
class B { 
   public:
      void f_pub() { cout << "f_pub is called.\n"; }
   protected:
      void f_prot() { cout << "f_prot is called.\n"; }
   private:
      void f_priv() { cout << "f_priv is called.\n"; }
};


// Public Inheritance
class D_pub : public B { 
   public: 
      void foo() {
         f_pub();   // OK. D_pub's PUBLIC function
         f_prot();  // OK. D_pub's protected function
         f_priv();  // Error. B's private function 
      }
};

// Protected Inheritance
class D_prot : protected B { 
   public: 
    // using B::f_pub; // Declaration brings f_pub function into the scope D_prot
      void foo() {
         f_pub();   // OK. D_pub's protected function
         f_prot();  // OK. D_pub's protected function
         f_priv();  // Error. B's private function 
      }
};


// Private Inheritance
class D_priv : private B { 
   public:
	// using B::f_pub; // Declaration brings f_pub function into the scope D_prot
      void f() {
         f_pub();   // OK. D_priv private function
         f_prot();  // OK. D_priv private function
         f_priv();  // Error. B's private function 
      }
};

int main() {
   D_pub D1;
   D1.f_pub();  // OK. f_pub() is D_pub's public function.
   D1.f_prot(); // Error. f_prot() is D_pub's PROTECTED function you cann't access from main function.

   D_prot D2;
   D2.f_pub();  // Error. f_pub() is D_priv's private function.
   D2.f_pub();  // OK if you have a declartion 'using B::f_pub' under PUBLIC of D_prot

   D_priv D2;
   D2.f_pub();  // OK if you have a declartion 'using B::f_pub' under PUBLIC of D_priv

   B* pB = &D1; // OK
   pB = &D2;    // Error - You cann't
}






Simillarity between  Private Inheritance and Composition:

// Private inheritance: HAS-A relation.similar to COMPOSITION. one contains another.
class Ring {
   public:
   void tinkle() { }
};

// Private Inheritance == Composition
class Dog_Priv : private Ring {
   public:
   using Ring::tinkle; // Brings Dog's public interface
};

// Composition == Private Inheritance
class Dog {
   Ring m_ring;
   public:
   void tinkle() { m_ring.tinkle(); }  // call forwarding
};
// 

Difference between  Private Inheritance and Composition:

class Ring {
   virtual tremble();
   public:
   void tinkle() { tremble(); }
   protected:
   void foo() { }
};

// Private Inheritance
class Dog_Priv : private Ring {
	 // Also have an ACCESS to Dog's PROTECT members
   public:
   using Ring::tinkle; // Brings Dog's public interface
  
};

// Composition
class Dog {
	// NO access to Dog's PROTECT members
   Ring m_ring;
   Ring m_ring2;
   public:
   void tinkle() { m_ring.tinkle(); }  // call forwarding using m_ring
   void shine() { m_ring2.tinkle(); }  // call forwarding using m_ring2
};


class Ring {
   private:
   virtual void tremble() { cout<< "Ring::temble()" << endl; };
   public:
   void tinkle() { tremble(); }
   void glitter() { cout<< "Ring::glitter()" << endl; };
};

// Private Inheritance
class Dog_Priv : private Ring {
	void tremble() { cout<< "Dog_Priv::temble()" << endl; };
	void glitter() { cout<< "Dog_Priv::glitter()" << endl; };
	 // Also have an ACCESS to Dog's PROTECT members
   public:
   using Ring::tinkle; // Brings Dog's public interface
   using Ring::glitter;
};

int main() {
	Dog_Priv d;
	d.tinkle(); // Dog_Priv::temble() - INDIRECTLY ACCESSING Dog_Priv private function in main
	d.glitter(); // ERROR - Dog_Priv private function CANN'T be accessed in main
}




/*
	Preference:
	composition: Decoupled and better object oriented design. More preferred!.
	private inheritance: more elegant polymorphism.
 *
 * E.g. in class ring, add virtual function: tremble(), which is
 *    used in tinkle().
 */




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: All Castings Considered - Part II
// https://www.youtube.com/watch?v=UfrR1nNfoeY&list=PLE28375D4AC946CC3&index=17
#include <iostream>
using namespace std;
// Casting could be risky.

class dog {
public:
	// Atleast only virtual function is needed to use dynamic_cast. Having only Virtual destructor is also OK.
	virtual ~dog() {} 
	virtual void fly() {  cout<< "Dog cannot fly" << endl;  }
};

class yellowdog : public dog {
	int age = 5;
public:  
	void run()  { cout<< "I run fast"  << endl; }
	void bark() { cout<< "woof. I am " << age  << endl; }
	void fly()  { cout<< "Yellow Dog cannot fly. I am " << age  << endl; }
};

int main() {
	dog* pd = new dog();

	// STATIC CAST
	yellowdog* py_ds = static_cast<yellowdog*>(pd); // ALWAYS SUCCEED - BECAREFUL
	cout << "pd = " << pd << endl;       // 0106A2C0
	cout << "py_ds = " << py_ds << endl; // 0106A2C0 (SAME ADDRESS)
	// compiler considers run() as STATIC FUNCTION 
	py_ds->run();  // I run fast
	py_ds->bark(); // woof. I am -33686019 (some random number) - WRONG

	
	// DYNAMIC CAST - WRONG
	// NOT all dog's are yellowdog's
	yellowdog* py_dc = dynamic_cast<yellowdog*>(pd); // dynamic_cast FAIL 
	cout << "pd = " << pd << endl;       // 00EDB8B8
	cout << "py_dc = " << py_dc << endl; // 00000000
	// compiler considers run() as STATIC FUNCTION 
	py_dc->run();  // I run fast <- EVENTHOUGH py is a NULL POINTER
	py_dc->bark(); // CRASH - CANNOT consider as STATIC FUNCTION bcos it uses member variable

	// POLYMORPHIC way without any cast
	yellowdog* deriverPtr = new yellowdog();  // yellowdog* pd = new dog(); <- WRONG way of usage
	dog* basePtr = deriverPtr;
	basePtr->fly();    // YellowDog or Dog depends on existance of virtual key word
	deriverPtr->fly(); // Yellow Dog cannot fly. I am 5 <- ALWAYS YellowDog

	// Polymorphic way (STACK based objects)
	yellowdog derived;
	dog* basePtr = &derived;
	basePtr->fly();
	
	return 0;
}

// CONST CAST - casting could be a handy hack tool
class dog {
	public:
	std::string m_name;
	dog():m_name("Bob") {}
	void bark() const { // object pointer by *this is CONST so you cann't change its content.
		// m_name = "Henry";
		const_cast<dog*>(this)->m_name = "Henry"; // BUT you can change by const_cast
		std::cout << "My name is " << m_name << std::endl;
	}
};


/*
 * =========================================  C++ Style Casting ================================
 *                             Generate_Code   Generate_data      risky   data_type
 * Object Casting:            
 *    static_cast                 yes              yes             2      any types
 *                                                                       (as long as type 
 *                                                                       conversion is defined)
 * Pointer/Reference Casting:
 *    static_cast                 no               no              4     related types
 *    dynamic_cast                yes              no              3     related types(down-cast)
 *    const_cast                  no               no              1     same type
 *    reinterpret_cast            no               no              5      any types
 *
 *
 *
 *
 *
 * =========================================  C Style Casting ================================
 *                             Generate_Code  Generate_data      risky   data_type
 * Object Casting:               yes              yes             5      any types
 *                                                                       (as long as type 
 *                                                                       conversion is defined)
 * Pointer/Reference Casting:    no               no              5      any types
 *
 *
 * Notes can be downloaded at my website: boqian.weebly.com
 *
 * Note:
 * 1. const_cast, dynamic_cast and reinterpret_cast can only work on pointers/references.
 * 2. static_cast of objects is very different from static_cast of pointers. 
 * 3. reinterpret_cast basically reassigning the type information of the bit pattern. 
 *    It should only be used in low-level coding.
 * 4. dynamic_cast does static_cast plus run-time type check.
 * 5. dynamic_cast and static_cast for pointers can only work on related type (e.g., 
 *    base <-> derived).
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * All Castings Considered
 *
 *
 * Type Conversion:
 *    1. Implicit Type Conversion
 *    2. Explicit Type Conversion - Casting
 */

// Ref: Advanced C++: All Castings Considered - Part I
// https://www.youtube.com/watch?v=lglGKxNrLgM&list=PLE28375D4AC946CC3&index=16


// 1. static_cast
int i = 9;
float f = static_cast<float>(i);              // convert object from one type to another
dog d1 = static_cast<dog>(string("Bob"));     // Type conversion NEEDS to be defined.
dog* pd = static_cast<dog*>(new yellowdog()); // convert pointer/reference from one type to a RELATED type (down/up cast)


// 2. dynamic_cast
dog* pd = new yellowdog(); // static cast
yellowdog py = dynamic_cast<yellowdog*>(pd); 
// a. It convert pointer/reference from one type to a RELATED type (down cast - Base to Derived)
// b. perform run-time type check.  If succeed, py==pd; if fail, py==0;
// c. It requires the 2 types to be polymorphic (atleast have one virtual function).

// 3. const_cast
                                           // only works on pointer/reference
const char* str = "Hello, world.";         // only works on SAME type
char* modifiable = const_cast<char*>(str); // cast away constness of the object being pointed to

// 4. reinterpret_cast 
long p = 51110980;
dog* dd = reinterpret_cast<dog*>(p);  // re-interpret the bits of the object pointed to
// The ultimate cast that can cast one pointer to ANY other type of pointer.

// C-Style Casting: A mixture of static_cast, const_cast and reinterpret_cast [NO dynamic_cast] 
	short a = 2000;
	int i = (int)a;   // c-like cast notation
	int j = int(a);   // functional notation



/*
 	Generally C++ style of casts are preferred over the C-style, because:
 	1. Easier to identify in the code.
 	2. Less usage error. C++ style provides:
 	   a. Narrowly specified purpose of each cast, and
 	   b. Run-time type check capability.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//############################################################################
/* 
User Defined Implicit Type Conversion 
	Categories of Type Conversion:
	                                                              Implicit      Explicit(casting)
	Standard Type Conversion (between build in types)                 A            B
	User Defined Type Conversion (between user defined and build in)  C            D
	                                                                           
	
 */
	// Category A: Implicit Standard Type Conversion
	char c = 'A';
	int i = c;  // Integral promotion

	char*  pc = 0; // int -> Null pointer

	void f(int i) { }
	f(c);  // Integral promotion

	dog* pd = new yellowdog();  // pointer type conversion NOT user defined type conversion


/* 
	Category C: Implicit User Defined Type Conversion
	Defined inside class (user defined type)
	There are 2 methods to define implicit user defined type conversion:
		Method 1: Use constructor that can accept a single parameter.
					- convert other types of object into your class
		Method 2: Use the type conversion function  
					- convert an object of your class into other types
 */
// Ref: Advanced C++: Define Implicit Type Conversion
// https://www.youtube.com/watch?v=S7MNPX73FSQ&list=PLE28375D4AC946CC3&index=15
#include <iostream>
using namespace std;
class dog {
   public:
      // Method 1: convert other types of object into your class
      // Convert string type (name) into dog type using constructor      
      // NO explicit key word and 1 arg constuctor -> do object construction and BOTH implicit and explicit conversions
      dog(string name) {m_name = name; }  // NO explicit
	  // WITH explicit key word and 1 arg constuctor -> do object construction and explicit type conversion (NOT implicit conversion)
      // explicit dog(string name) {m_name = name; } // Avoids  inadvertent implicit type conversion.

      string getName() {return m_name;}

	  // Method 2: convert an object of your class into other types
	  operator string () const { return m_name; } // Type Conversion function
  private:
      string m_name;
};

void main ()
{
  string dogname = "Bob";
  dog dog1 = dogname; // Method 1: Convert string type ("Bob") into dog type using constructor
  printf("My name is %s.\n", dog1.getName());
  // NO need of getName() function if you have a type conversion function(Method 2)
  printf("My name is %s.\n", dog1); // Method 2: Converts dog type into string type (%s) using type conversion function
}



/*
 	DESIGN PRINCIPLE: make interface easy to use correctly and hard to use incorrectly.
 	How hard is enough?  Ideally, uncompilable.
 	   General guideline: 
 	   1. Avoid defining seemingly unexpected conversion.
 	   2. Avoid defining two-way implicit conversion.
 */




// Implicit type conversion is useful when creating numerical types of class, such as a rational class.
class Rational {
public:
	// Bcos of default values, it can take single argument as well. So it can be considered as 1 arg constructor with implicit/explicit conversions
	Rational(int numerator = 0, int denominator = 1): num(numerator),den(denominator) {}
	int num;  // Demo only, public data members are not recommended
	int den;

	// * is overloaded for Rational * Rational
	const Rational operator*(const Rational& rhs) {
		// Covert the result(internal multiplication result) into object
		return Rational(num * rhs.num, den * rhs.den); // num * rhs.num => 23 * 2
	}
	// Converts Rational Object to integer
	operator int () const { return num / den; }
};



int main ()
{
	Rational r1 = 23;
	// LEFT to RIGHT evaluation
	// rational * rational(2) => rational(2) can be done by 1 arg constructor,
	Rational r2 = r1 * 2; // * is overloaded for rational multiplication(Rational * Rational) can be done by Rational operator*
	// integer * integer(r1) => Needs Rational to Integer conversion
	Rational r3 = 3 * r1; // * is global ARITHMETIC interger multiplication(like 5x6). AMBIGUOUS to above multiplication.
	// So ONLY either of the one only works not BOTH!. Better to avoid defining two-way implicit conversion.
	return 0;
}

// Solution - Remove two-way implicit conversion and define single way NON-MEMBER rational mulitiplication operator - which works for BOTH
class Rational {
public:
	// Bcos of default values, it can take single argument as well. So it can be considered as 1 arg constructor with implicit/explicit conversions
	Rational(int numerator = 0, int denominator = 1): num(numerator),den(denominator) {}
	int num;  // Demo only, public data members are not recommended
	int den;
};

// Define NON-MEMBER rational mulitiplication operator - which works for BOTH
// Rational r2 = r1 * 2; => r1 * rational(2)
// Rational r3 = 3 * r1; => rational(3) * r1
const Rational operator*(const Rational& lhs, const Rational& rhs) {
return Rational(lhs.num*rhs.num, lhs.den*rhs.den);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Virtual Constructor - Clone() Function
// https://www.youtube.com/watch?v=UHP-DKrxgBs&list=PLE28375D4AC946CC3&index=14
#include <iostream>
using namespace std;

class Dog {
public:
	// copy constructed by itself
	virtual Dog* clone() { return (new Dog(*this));  }
};

class Yellowdog : public Dog {
private:
	// copy constructed by itself
	virtual Yellowdog* clone() { return (new Yellowdog(*this));	   
	// CO-VARIANT RETURN TYPE - that is return Yellowdog instead of Dog eventhough it is inherited from Dog.
	}
};

void foo(Dog* yell) {       // yell is a Yellowdog
	// calls default copy constructor
	Dog* x = new Dog(*yell); // But x is a Dog NOT a Yellowdog identical copy even after default copy constructor

	// Clone functions act like a VIRTUAL CONSTRUCTOR. Exact object type(Yellowdog) is created regardless of cast type (Dog).
	Dog* y = yell->clone();  // y is a Yellowdog by clone
}

int main() {
	Yellowdog yell;
	foo(&yell);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Resource Managing Class
// https://www.youtube.com/watch?v=juQBXTNz4mo&list=PLE28375D4AC946CC3&index=13
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person {
private:
	string* pName_; // Person owns the string through its pointer BUT don't have COPY Constructor/ ASSIGNMENT operator
public:
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }
};


// Solution 1: Define copy constructor and copy assignment operator for DEEP copying
class Person {
private:
	string* pName_;
public:
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }

	string* pName() const { return pName_; }
	Person(const Person& rhs) {   // deep copying by COPY constructor
		pName_ = new string(*(rhs.pName()));
	}
	Person& operator=(const Person& rhs);  // deep copying by copy ASSIGNMENT operator
};

int main() {
	vector<Person> persons;
	persons.push_back(Person("George"));
	// 1. "George" is constructed
	// 2. A copy of "George" is saved in the vector (SHALLOW copy - Copy only the pointer pointing to the resource not resource)
	// 3. "George" is destroyed.

	persons.front().printName(); // CRASH - Copied pointer points to already deleted memory
}



// Solution 2: delete the default copy constructor & copy assignment operator AND manage the object in CLIENT level
class Person {
private:
	// delete the default copy constructor and copy assignment operator by PRIVATE DECLARATION 
	Person& operator=(const Person& rhs);  // deep copying
	Person(const Person& rhs);
public:
	string* pName_; 
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }
};


int main() {
	// STL container requires containee should copiable [should have COPY constructor and copy ASSIGNMENT operator] 
	vector<Person*> persons; // workaround: Store the object POINTER instead of object itself
   persons.push_back(new Person("George")); // NOTE: creating an new object
   persons.front()->printName(); 
   // Manually delete the created objects after use
}


// Solution 3: delete the copy constructor & copy assignment operator AND define CLONE
class Person {
private:
	// delete the default copy constructor and copy assignment operator by PRIVATE DECLARATION 
	Person& operator=(const Person& rhs);  // deep copying
	Person(const Person& rhs);
public:
	string* pName_;
	void printName() { cout << *pName_; }
	~Person() { delete pName_; }
	Person(string name) { pName_ = new string(name); }
	// Identical COPY of object itself
	Person* Clone() { return new Person(*pName_); }
};

int main() {
	// STL container requires containee should copiable [should have COPY constructor and copy ASSIGNMENT operator] 
	vector<Person*> persons;
	persons.push_back(Person("George").Clone());
	persons.front()->printName();
}

Which solution to use ? Prefer clonable solution 3. Bcos Copy constructor and copy Assignment operator do the deep copy operation 
IMPLICITLY (error prone) BUT using clone we can do the deep copy operation explicitly.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++.Resource Acquisition is Initialization.
// https://www.youtube.com/watch?v=ojOUIg13g3I&list=PLE28375D4AC946CC3&index=10

// Resource Acquisition is Initialization (RAII): 
// Technique used to manage resources: memory, hardware device, network handle, etc.

Mutex_t   mu = MUTEX_INITIALIZER;
 
void functionA()
{
   Mutex_lock( &mu );
   // If there is an exception then locked for ever !
   Mutex_unlock( &mu ); // This line will not be executed
}


// Solution:
class Lock {
   privat:
      Mutext_t* m_pm;
   public:
      explicit Lock(Mutex_t *pm) { Mutex_lock(pm); m_pm = pm;};
      ~Lock() { Mutex_unlock(m_pm); };
}

void functionA() {
   Lock mylock(&mu);
   // Do a bunch of things
}  // The mutex will always be released when mylock is destroied from stack



What happens when resource management object is copied?
   Lock mylock1(&mu);
   Lock mylock2(mylock1);

Solution 1: Do not support copying. 
			Prohibit copying by declaring(not defining) private copy constructor and copy assignment operator.

Solution 2: If you really want the resouce management object copy then support by shared_ptr.
			Reference-count the underlying resource by using shared_ptr.

// Shared pointer template example
template<class Other, class D> shared_ptr(Other * ptr, D deleter);

// The default value for D is "delete", e.g.:
std::tr1::shared_ptr<dog> pd(new dog());

class Lock {
   private:
      std:::shared_ptr<Mutex_t> pMutex;
   public:
      explicit Lock(Mutex_t *pm):pMutex(pm, Mutex_unlock) // The 2nd param of shared_ptr constructor is "deleter" function. 
	  { 
         Mutex_lock(pm);
      }
 };


   Lock mylock1(&mu);		// ref count  = 1
   Lock mylock2(mylock1);	// ref count  = 2


// Another example:

// Some classes
class dog; 
class Trick;

void train(std::shared_ptr<dog> pd, Trick dogtrick);
Trick  getTrick();

int main() {
   train(shared_ptr<dog> pd(new dog()), getTrick()); // Problem - order of param processing is undefind and compiler dependent
}

Suppose a compiler process the argument in the below order
1. new dog();
2. getTrick(); // If there is an exception then memory of 'new dog()' will leaks !!!
3. construct std::shared_ptr<dog>.

// Solution
int main() {
   std::shared_ptr<dog> pd(new dog());
   train(pd, getTrick());
}

Conclusion: Don't combine storing objects in shared pointer with other statement.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ref: Advanced C++: Static Initialization Fiasco
// https://www.youtube.com/watch?v=hE77OSTE2J0&list=PLE28375D4AC946CC3&index=11

////////////////////////////////  main.cpp  ////////////////////////
#include <iostream>
#include "Dog.h"
#include "Cat.h"
using namespace std;

Dog d("Gunner"); // global object creation
// Inside Dog.cpp we have another global object creation[ Cat c("Smokey"); ]. Because of they are 
// in different files order of creation is undefined (depends upon the compiler - maybe 'c' before 'd')

int main()
{
	d.bark();
	return 0;
}

///////////////////////////////////////////////
////////////////////////////////  main.cpp  ////////////////////////
// Dog d("Gunner"); // NO more global object creation

int main()
{
	// Singleton::getDog()->bark();
	Singleton s;
	Singleton::getCat()->meow();
	return 0;
}

#endif