#include <iostream>

// namespace std

#define LOG(x) std::cout << x << std::endl


void Increment(int& value) {
	value++;
}

void Increment_ptr (int* value) {
	// value++ = increment the mem address
	(*value)++;
}



int main() 
{
	/* These are on the stack
		int var = 8; // Where are you in memory?
		int* ptr = &var;
		// How to access those data?
		*ptr = 10;
	*/

	/* These are on the HEAP
		char* buffer = new char[8];
		memset(buffer, 0, 8);
		// Ptr -> ptr = 2D-array;
		char** ptr = &buffer;
		delete[] buffer; // How to free memory in the HEAP
	*/

	// References: 
	int a = 5;
	int& ref = a;// & next to type = Reference
	

	// The 2 line below are equivalent
	Increment(a);
	Increment(ref);

	// Compare to using ptr way
	Increment_ptr(&a);


	LOG(a);
	std::cin.get();
}

/*
	We don't know how big the pointer is, don't know how much data they are holding

	What is a pointer?
	-> An interger which is a memory address

	void* ptr = nullptr // This ptr are typeless and have memory address of 0;\


	// References !!!
	What? -> Sugar coating of POINTER
	Pros: make the code easier to read -> shorter to write
	
	** Things to note: 
	I can do everything a reference do with a pointer
	
	Can't modified the ref later in the program
	Therefore, Must be initialize when declare
		Ex: 
		int a = 5
		int b = 8;

		int& ref = a;
		ref = b;

		=> This will result: a = 8 and b = 8;

	On this line:
		int& ref = a;
	ref is not a var, it is a alias of a;

	
*/