#include "Network.h"

//konstruktor
Network::Network(int numberOfNeurons, int numberOfInputs, double learningRate, double iterationsNumber) {
	this->numberOfNeurons = numberOfNeurons;
	neurons.resize(numberOfNeurons);
	//this->radius = (double)numberOfNeurons;
	this->radius = 10.0;
	this->time = iterationsNumber / this->radius;

	for (int i = 0; i < numberOfNeurons; i++)
		neurons[i].Neuron::Neuron(numberOfInputs, learningRate);
}

//zmiana wag
void Network::changeWeights(double currentIteration, bool learning) {
	getScalarProducts();
	findMinimum();
	neurons[winnerIndex].activationFunction();

	if (learning) {
		//wyznaczenie sasiadow zwycieskiego neuronu w zaleznosci od promienia i kroku czasowego
		neurons[winnerIndex].designateNeighbors(radius, currentIteration, time);
		int radius = neurons[winnerIndex].neighbors;
		int leftBorderNeuronIndex = 0;
		int rightBorderNeuronIndex = 0;

		//sprawdzenie czy dany neuron miesci sie w siatce
		if (winnerIndex - radius < 0)
			leftBorderNeuronIndex = 0;
		else
			leftBorderNeuronIndex = winnerIndex - radius;

		if (winnerIndex + radius >= numberOfNeurons)
			rightBorderNeuronIndex = numberOfNeurons - 1;
		else
			rightBorderNeuronIndex = winnerIndex + radius;

		radius = (radius <= 0) ? 0 : --radius;

		for (int i = leftBorderNeuronIndex; i < rightBorderNeuronIndex; i++) {
			//zmiana wag neuronow, ktore mieszcza sie w promieniu
			neurons[i].length = (i < winnerIndex) ? (winnerIndex - i) : (i - winnerIndex);
			neurons[i].neighbors = neurons[winnerIndex].neighbors;
			neurons[i].calculateNewWeights();
		}
	}
}

//zwraca odleglosci euklidesowe
void Network::getScalarProducts() {
	scalarProducts.clear();
	for (int i = 0; i < numberOfNeurons; i++)
		scalarProducts.push_back(neurons[i].calculateScalarProduct());
}

//szuka najmniejszej odleglosci euklidesowej
void Network::findMinimum() {
	double tmp = scalarProducts[0];
	this->winnerIndex = 0;
	for (int i = 1; i < scalarProducts.size(); i++) {
		if (tmp < scalarProducts[i]) {
			this->winnerIndex = i;
			tmp = scalarProducts[i];
		}
	}
}