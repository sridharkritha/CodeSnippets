
// objects are only truly equal to themselves.
var foo = [1,2,3];
var bar = [1,2,3];

console.log(foo === bar); // false
console.log(foo === foo); // true

// Difference between string and array
var arr = ['a','b','c'];
var str = "abc";

console.log(arr.length); // 3
console.log(str.length); // 3

console.log(arr[0]); // a
console.log(str[0]); // a

console.log(arr === str); // false

console.log(typeof str); // string
console.log(typeof arr); // object

splice for string type is exist ?
No, unlike array there is no splice or split functions. You have to write it on your own.





 splice() method changes the contents(in place) of an array by removing or replacing existing elements and/or adding new elements
/
var arrDeletedItems = array.splice(index[, deleteCount[, Additem1[, Additem2[, ...]]]])

// Remove 2 element from index 3
var myFish = ['angel', 'clown', 'drum', 'mandarin', 'sturgeon'];
var removed = myFish.splice(3, 2); // removed is ['mandarin', 'sturgeon']
// myFish is ["angel", "clown", "drum"]

// Remove 0 elements from index 2, and insert "drum" and "guitar"
var myFish = ['angel', 'clown', 'mandarin', 'sturgeon'];
var removed = myFish.splice(2, 0, 'drum', 'guitar'); // removed is [], no elements removed
// myFish is ["angel", "clown", "drum", "guitar", "mandarin", "sturgeon"]

// Remove 1 element from index 2, and insert "trumpet"
var myFish = ['angel', 'clown', 'drum', 'sturgeon'];
var removed = myFish.splice(2, 1, 'trumpet'); // removed is ["drum"]
// myFish is ["angel", "clown", "trumpet", "sturgeon"]

// Remove 1 element from index (-2) - 2 count from back
var myFish = ['angel', 'clown', 'mandarin', 'sturgeon'];
var removed = myFish.splice(-2, 1); // removed is ["mandarin"]
// myFish is ["angel", "clown", "sturgeon"] 

// Remove all elements after index 2 (incl.)
var myFish = ['angel', 'clown', 'mandarin', 'sturgeon'];
var removed = myFish.splice(2); // removed is ["mandarin", "sturgeon"]
// myFish is ["angel", "clown"]



function spliceSplit(str, index, deleteCount, addElement) {
	var ar = str.split('');
	ar.splice(index, deleteCount, addElement);
	return ar.join('');
}

console.log(spliceSplit("sridhar", 1, 2, 'wxyz' )); // swxyzdhar











































