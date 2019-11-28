// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "base_classes.h"
using std::cout;
using std::endl;
extern int S;
int main()
{
    /*std::cout << "Hello World!\n";*/
	std::cout << "Intial S value: " << S << '\n';
	{
		Alpha a = Alpha();
		Beta b = Beta();
		Gamma g = Gamma();

		Alpha a1 = Alpha();
		Beta b1 = Beta();
		Gamma g1 = Gamma();

		cout << "Ids:" << endl;
		cout << "a: " << a.getId() << ", a1: " << a1.getId() << endl;
		cout << "b: " << b.getId() << ", b1: " << b1.getId() << endl;
		cout << "g: " << g.getId() << ", g1: " << g1.getId() << endl << endl;


		cout << "Predicted S value: " << predictSValue(g.get_register_classes(), S) << endl << endl;
	}
	std::cout <<"\nReal S value after object destruction: " <<  S << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
