#include <vector>
#include "Neuron.h"
using namespace std;

class Network {
public:

	int numberOfNeurons; //liczba neuronow
	vector<Neuron> neurons; //wektor neuronow
	vector<double> scalarProducts; //wektor odleglosci euklidesowych
	int winnerIndex; //indeks zwyciezcy
	double radius; //promien wyznaczajacy obszar od zwycieskiego neuronu
	double time; //czas

	void changeWeights(double obecnaIteracja, bool testing); //zmiana wag dla aktualnej iteracji (czasu)
	void findMinimum(); //szuka najmniejszej odleglosci euklidesowej
	void getScalarProducts(); //zwraca odleglosci euklidesowe

							  //konstruktor
	Network(int numberOfNeurons, int numberOfInputs, double learningRate, double iterationsNumber);
};