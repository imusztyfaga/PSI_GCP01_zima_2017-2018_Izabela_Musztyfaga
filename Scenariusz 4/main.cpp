#include <iostream>
#include "Neuron.h"
using namespace std;

int main() {

	const double LEARNING_RATE = 0.1;
	cout << endl << "Wspolczynnik uczenia: " << LEARNING_RATE << endl << endl;


	Neuron hDontForget(LEARNING_RATE);
	hDontForget.learnDontForget();

	//Neuron hForget(LEARNING_RATE);
	//hForget.learnForget();



	system("pause");

}