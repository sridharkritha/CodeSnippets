////////////////////////////////  Dog.cpp  ////////////////////////
#include "Dog.h"
#include "Cat.h"
#include <iostream>

Cat c("Smokey"); // global object creation

void Dog::bark() {
	std::cout << "Barking Dog is " << _name << std::endl;
}

Dog::Dog(char* name) {
	_name = name;
	std::cout << "Construction Dog " << _name << std::endl;

	c.meow(); // CRASH if global cat object creation haven't done yet.
}

///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  Dog.cpp  ////////////////////////
#include "Dog.h"
#include "Cat.h"
#include "Singleton.h"
#include <iostream>

// Cat c("Smokey"); // NO more global object creation

void Dog::bark() {
	std::cout << "Barking Dog is " << _name << std::endl;
}

Dog::Dog(char* name) {
	_name = name;
	std::cout << "Construction Dog " << _name << std::endl;

	// c.meow(); // CRASH if global cat object creation haven't done yet.
	Singleton::getCat()->meow();
}