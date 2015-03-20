#include "Thread.h"
#include <iostream>
#include <string>
#include <thread> //requires visual studios 2012 or higher

using namespace std;

void function_1()
{
	cout << "Hello from parent via function 1\n" << endl; //filler implement server/client code
}

void function_2()
{
	cout << "Hello from parent via function 2\n" << endl;
}

int main()
{
	thread t1(function_1); //initializes and runs the thread
	
	t1.join(); //becomes a child of the main thread of t1
	

	thread t2(function_2);
	
	t2.join();

	system("pause");
	//return 0;
}

Thread::Thread()
{
}  

Thread::~Thread()
{
}
