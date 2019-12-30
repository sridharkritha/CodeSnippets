////////////////////////////////  Cat.cpp  ////////////////////////
#include "Cat.h"
#include "Dog.h"
#include <iostream>

extern Dog d; // extern is NEEDED bcos 'd' is defined in another source file

void Cat::meow() {
	std::cout << "Meowing Cat is " << _name << std::endl;
}

Cat::Cat(char* name) {
	_name = name;
	std::cout << "Construction Cat " << _name << std::endl;

	d.bark();
}


/////////////////////////////////////////////////////////////////////////
////////////////////////////////  Cat.cpp  ////////////////////////
#include "Dog.h"
#include "Cat.h"
#include "Singleton.h"
#include <iostream>

// extern Dog d; // NO more global object access

void Cat::meow() {
	std::cout << "Meowing Cat is " << _name << std::endl;
}

Cat::Cat(char* name) {
	_name = name;
	std::cout << "Construction Cat " << _name << std::endl;

	// d.bark();
	Singleton::getDog()->bark();
}