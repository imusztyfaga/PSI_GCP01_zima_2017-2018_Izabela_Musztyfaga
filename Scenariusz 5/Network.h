#include <vector>
#include "Neuron.h"
using namespace std;

class Network 
{
public:

	vector<Neuron> neurons; //wektor neuronow
	vector<double> sums; //wektor sum wejsc
	int numberOfNeurons; //liczba neuronow
	int winnerIndex; //indeks zwyciezcy

	Network();				 //konstruktor
	Network(int numberOfNeurons, int numberOfInputs, double learningRate);
	~Network();

	//zmiana wag (learning = true dla procesu uczenia, = false dla procesu testowania)
	void changeWeights(bool learning);
	void findTheLargestSum(bool learning); //szukanie zwycieskiego neuronu
	void sumOfTheLayer(); //obliczenie sumy wszystkich wejsc
};