// Simple heap program
#include <iostream>

using namespace std;

int* getHeapPointerFromFunction();
void leak1();
void leak2();

int main() {
	// new keyword allocates memory on the heap and returns the address of it 
	int* pheap1 = new int();
	// set the value in the memory location to 10
	*pheap1 = 10;

	// initialize memory on the heap at the same time it's allocated
	int* pheap2 = new int(10);

	int* pheap3 = getHeapPointerFromFunction();

	cout << "pheap1: " << pheap1 << "\npheap2: " << pheap2 << "\npheap3: " << pheap3 << endl;

	// we must explicitly free heap memory with the delete keyword else that memory will still be there in the heap
	delete pheap1;
	delete pheap2;
	delete pheap3;

	// now the above pointers point to locations that no longer store heap values 
	// such pointers which point to locations which are no longer used are called dangling pointers
	// to avoid the misuse of dangling pointers always deference pointers the moment they are of no use
	pheap1 = 0;
	pheap2 = 0;
	pheap3 = 0;
}

// Heap's can be used outside the functions they are created all we need to do is to pass the pointers
int* getHeapPointerFromFunction() {
	return new int();
}

// DO NOI CALL THE BELOW FUNCTIONS

// Function demonstrates memory leak. Once the heap is created it must be deleted manually else if we lose the pointer there's no way to acess the location
// A large leak could result in crashing
// once the function is called the theap created is lost as it isn't returned but the memory allocated for the heap isn't freed
void leak1(){
	int* theap = new int();
}

// Another way of memory leak shown
// First theap points to heap location that stores 10 then it points to the heap location that stores 20
// In the process the address of the location that stores 10 is lost i.e. a memory leak
void leak2() {
	int* theap = new int(10);
	theap = new int(20);
}