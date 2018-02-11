#include "Network.h"


Network::Network()
{

}

Network::Network(int numberOfNeurons, int numberOfInputs, double learningRate)	//konstruktor
{
	this->numberOfNeurons = numberOfNeurons;
	this->neurons.resize(numberOfNeurons);
	for (int i = 0; i < numberOfNeurons; i++)
		this->neurons[i].Neuron::Neuron(numberOfInputs, learningRate);
}

Network::~Network()			//destruktor
{

}

//obliczenie sum wszystkich wejsc, poszukiwanie tego o najwiekszej sumie i aktualizacja jego wag
void Network::changeWeights(bool learning) {
	sumOfTheLayer();
	findTheLargestSum(learning);
}

//obliczenie sumy wszystkich wejsc
void Network::sumOfTheLayer() {
	this->sums.clear();
	for (int i = 0; i < this->numberOfNeurons; i++)
		this->sums.push_back(neurons[i].calculateSumOfAllInputs());
}

//poszukiwanie wejscia o najwiekszej sumie
void Network::findTheLargestSum(bool learning) {
	double tmp = this->sums[0];
	this->winnerIndex = 0;
	for (int i = 1; i < this->sums.size(); i++) {
		if (tmp < this->sums[i]) {
			this->winnerIndex = i;
			tmp = this->sums[i];
		}
	}
	this->neurons[this->winnerIndex].activationFunction();
	if (learning) //aktualizacja wag
		this->neurons[this->winnerIndex].calculateNewWeight();
}