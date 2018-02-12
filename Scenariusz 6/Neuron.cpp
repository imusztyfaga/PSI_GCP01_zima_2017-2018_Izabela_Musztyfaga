#include "Neuron.h"
#include <ctime>
#include <cmath>

//konstruktor
Neuron::Neuron() {
	this->inputs.resize(0);
	this->weights.resize(0);
	this->sumOfAllInputs = 0.0;
	this->outputValue = 0.0;
	this->learningRate = 0.0;
}

//konstruktor
Neuron::Neuron(int numberOfInputs, double learningRate) {
	createInputs(numberOfInputs);
	normalizeWeights();
	this->learningRate = learningRate;
	this->sumOfAllInputs = 0.0;
	this->outputValue = 0.0;
}

//stworzenie poczatkowych wejsc(ustawienie wejsc na 0, wykorzystanie metody calculateFirstWeights())
void Neuron::createInputs(int numberOfInputs) {
	for (int i = 0; i < numberOfInputs; i++) {
		inputs.push_back(0);
		weights.push_back(calculateFirstWeights());
	}
}

//obliczenie odleglosci skalarnych
double Neuron::calculateScalarProduct() {
	sumOfAllInputs = 0.0;
	for (int i = 0; i < getInputsSize(); i++)
		sumOfAllInputs += pow(inputs[i] - weights[i], 2);
	sumOfAllInputs = sqrt(sumOfAllInputs);

	return sumOfAllInputs;
}

//funkcja sigmoidalna obliczajaca wyjscie
void Neuron::activationFunction() {
	double beta = 1.0;
	this->outputValue = (1.0 / (1.0 + (exp(-beta * sumOfAllInputs))));
}

//obliczenie nowych wag
void Neuron::calculateNewWeights() {
	for (int i = 0; i < getWeightsSize(); i++)
		this->weights[i] += this->learningRate*this->valueOfNeighborhoodFunction*(this->inputs[i] - this->weights[i]);
	normalizeWeights();
}

//wyznaczenie odleglosci do sasiadow
void Neuron::designateNeighbors(double radius, double currentIteraton, double timeConstant) {
	this->neighbors = radius * exp(-currentIteraton / timeConstant);
}

//oblicza wartosc funkcji sasiedztwa (Gaussian neighborhood function)
void Neuron::calculateNeighbors() {
	//e^(-x^2) / 2 * y^2
	this->valueOfNeighborhoodFunction = exp(-pow(this->length, 2) / (2 * pow(this->neighbors, 2)));
}

//ustalenie poczatkowych wag dla wszystkich wejsc - zakres <0;1)
double Neuron::calculateFirstWeights() {
	double max = 1.0;
	double min = 0.0;
	double weight = ((double(rand()) / double(RAND_MAX))*(max - min)) + min;
	return weight;
}

//znormalizowanie zaktualizowanych wag
void Neuron::normalizeWeights() {
	double vectorLength = 0.0;

	for (int i = 0; i < getWeightsSize(); i++)
		vectorLength += pow(weights[i], 2);

	vectorLength = sqrt(vectorLength);

	for (int i = 0; i < getWeightsSize(); i++)
		weights[i] /= vectorLength;
}